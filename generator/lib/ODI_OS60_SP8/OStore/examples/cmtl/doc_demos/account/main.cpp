/* main.cpp:  This is the main application for accessing account
 * information.  Before running this program, you must run init_db.exe
 * to create and populate the account database.  After you invoke this
 * application, you can enter the following command strings on standard
 * input:
 *
 * balance <id>
 * deposit <id> <amount>
 * withdraw <id> <amount>
 * quit
 *
 * The application does some error checking to illustrate the use of
 * user-defined TIX exceptions and TIX exception handlind with virtual
 * transactions.  But to keep the program simple, error-checking is minimal.
 */


#include "account.h"

#define BUFSIZE 200
#define MAXTOKENS 4

// variables local to this file
static os_cache_pool_manager_config* cfg;
static os_cache_pool_manager* cpm;
static os_basic_transaction_context* read_ctx =
	os_basic_transaction_context::create(os_transaction_context::read_only, os_transaction_context::read_committed);
static os_basic_transaction_context* update_ctx =
	os_basic_transaction_context::create();

// functions defined in this file
int tokenize(char* s, char* t_list[], int n);
int withdraw(char* id, int amount);
int deposit(char* id, int amount);
int get_account_balance(char* id);
void list_accounts();
Account* get_account(char* id);

// TIX exceptions
DEFINE_EXCEPTION(err_account, "Unknown exception", &err_objectstore);
DEFINE_EXCEPTION(err_insuff_bal, "Insufficient balance", &err_account);
DEFINE_EXCEPTION(err_bad_acct_id, "Illegal account id", &err_account);

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {

		char cmd_buf[BUFSIZE]; // user input
		int n_toks; // number of tokens in user input
		char* toks[MAXTOKENS]; // tokens

		// name of XML file that contains information for configuring CMTL
		const char* config_info = (argc > 1) ? argv[1] : "account.xml";

		OS_ENTER_CMTL {
			ifstream xml_file(config_info, ios::nocreate | ios::in);

			// configure CMTL's transactional caches from XML file
			setup(xml_file, cfg, cpm);

			do {
				cout << "Enter a command:  ";
				cin.getline(cmd_buf, BUFSIZE); // get command string
				if (!(n_toks = tokenize(cmd_buf, toks, MAXTOKENS)))
					continue;

				// command processor
				switch (tolower(*toks[0])) {
				case 'b': // get account balance
					if (n_toks < 2) // check for legal command string
						cout << "USAGE: balance <account-id>\n";
					else
						TIX_HANDLE(err_account) {
							cout << "Balance: " << get_account_balance(toks[1])
								<< endl;
						} TIX_EXCEPTION {
							cout << tix_handler::get_report() << endl;
						} TIX_END_HANDLE
					break;
				case 'w': // withdraw from account
					if (n_toks < 3)
						cout << "USAGE: withdrawal <account-id> <amount>\n";
					else
						TIX_HANDLE(err_account) {
							cout << "Balance after withdrawal: "
								<< withdraw(toks[1], atoi(toks[2])) << endl;
						} TIX_EXCEPTION {
							cout << tix_handler::get_report() << endl;
						} TIX_END_HANDLE
					break;
				case 'd': // deposit amount to account
					if (n_toks < 3) // check for legal command string
						cout << "USAGE: deposit <account-id> <amount>\n";
					else
						TIX_HANDLE(err_account) {
							cout << "Balance after deposit: "
								<< deposit(toks[1], atoi(toks[2])) << endl;
						} TIX_EXCEPTION {
							cout << tix_handler::get_report() << endl;
						} TIX_END_HANDLE
					break;
				case 'l': // list account information for each account
					list_accounts();
					break;
				case 'q': // quit
					break;
				default:
					cout << toks[0] << ": unknown command.\n";
					break;
				}
			} while (cmd_buf[0] != 'q');
			cpm->shutdown();
		} OS_LEAVE_CMTL
	} OS_END_FAULT_HANDLER

	return 0;
}

// returns the number of space-separated tokens found in s.
// Reads up to n tokens into t_list[].
int tokenize(char* s, char* tok_list[], int n)
{
	char *tok;
	int i;

	for (i = 0; i < n; i++)
		if (tok = strtok((i ? NULL : s), " "))
			tok_list[i] = tok; // found a token
		else
			break;

	return i;
}

/*
// see headnote for the commented-out version of this function, below
int withdraw(char* id, int amount)
{
	int new_bal = 0;

	OS_BEGIN_VT (vt1, *update_ctx) {
		Account* a = get_account(id);

		if (!a) // account id in database?
			err_bad_acct_id.signal("Account %s not found in database", id);
		else { // try a withdrawal
			new_bal = a->debit(amount);
			if (new_bal < 0)
				err_insuff_bal.signal("$%d exceeds balance", amount);
		}
	} OS_END_VT (vt1)
	return new_bal;
}
*/

// This version of withdraw() is functionally the same as the one above.
// The difference between them is that the preceding version uses the
// transaction macros to set up a static transaction, whereas this version
// uses member functions of the CMTL class os_virtual_transaction to set up
// a dynamic transaction.  This version also includes a TIX exception
// handler to retry a restartable abort.  Static transactions are
// automatically retried. To use this version, remove the comments and
// comment out the preceding version.
int withdraw(char* id, int amount)
{
	int new_bal = 0;
	int retry; // test for transaction retry
	int retry_limit = 10; // maximum number of retries
	int retry_count = retry_limit;

	do { // retry loop
		retry = 0; // false
		os_virtual_transaction* vt = os_virtual_transaction::begin(*update_ctx);
		TIX_HANDLE(err_objectstore) {
			Account* a = get_account(id);

			if (!a) // account id in database? 
				err_bad_acct_id.signal("");
			else { // try a withdrawal 
				new_bal = a->debit(amount);
				if (new_bal < 0)
					err_insuff_bal.signal("");
				else 
					vt->commit(); 
			}

		} TIX_EXCEPTION { // handle restartable aborts
			if (vt->is_active()) // if txn not already aborted, abort it now
				vt->abort();

			// release os_virtual_transaction here in case we signal another
			// exception, preventing the delete statement from executing below
			delete vt;

			tix_exception *e = tix_handler::get_exception();
			// was this a restartable exception?
			if (err_restartable.ancestor_of(e) ||  e == &err_cmtl_retry) {
				if (--retry_count)
					retry = 1;
				else
					err_too_many_retries.signal(
						"Transaction retried more than %d times", retry_limit);
			}
			// re-signal user-defined exceptions, handled by caller
			else if (e == &err_bad_acct_id)
				e->signal("Account %s not found in database", id); 
			else if (e == &err_insuff_bal)
				e->signal("$%d exceeds balance", amount); 
		} TIX_END_HANDLE
		delete vt;
	} while (retry);
	return new_bal;
}

int get_account_balance(char* id)
{
	int bal = 0;

	OS_BEGIN_VT (vt2, *read_ctx) {
		Account* a = get_account(id);

		if (!a) // account id in database?
			err_bad_acct_id.signal("Account %s not found in database", id);
		bal = a->get_balance();
	} OS_END_VT (vt2)
	return bal;
}

int deposit(char* id, int amount)
{
	int bal = 0;

	OS_BEGIN_VT (vt3, *update_ctx) {
		Account* a = get_account(id);

		if (!a) // account id in database?
			err_bad_acct_id.signal("Account %s not found in database", id);
		bal = a->credit(amount);
	} OS_END_VT (vt3)
	return bal;
}

void list_accounts()
{
	Account* a;

	OS_BEGIN_VT (vt3, *read_ctx) {
		os_database* db =
			os_cache::get_current()->get_database(LOGICAL_DB_NAME);

		// get pointer to collection of accounts
		os_set* accts =
			(os_set*)((cpm->get_root(LOGICAL_ROOT_NAME))->get_root_value());

		os_cursor* c = new os_cursor(*accts);

		// check for at least one restaurant in the collection
		if (a = (Account*)c->first())
			// list all restaurants in the collection
			for (; c->more(); a = (Account*)c->next())
				cout << *a;
		delete c; // os_cursor object

		db->release_pointer();
	} OS_END_VT (vt3)
}

Account* get_account(char* id)
{
	os_database* db =
		os_cache::get_current()->get_database(LOGICAL_DB_NAME);

	// get pointer to collection of accounts
	os_set* accts =
		(os_set*)((cpm->get_root(LOGICAL_ROOT_NAME))->get_root_value());

	// query for the account
	Account* a = Account::query_by_id(id, db, accts);

	db->release_pointer();

	return a;
}

