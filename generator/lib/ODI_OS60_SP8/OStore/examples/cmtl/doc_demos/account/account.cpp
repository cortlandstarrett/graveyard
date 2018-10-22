// account.cpp: implements members of Account and defines globals
#include "account.h"
#define QS_SIZE 100

// logical names
const char* LOGICAL_DB_NAME = "Account Database";
const char* LOGICAL_ROOT_NAME = "Account Root";
const char* CACHE_POOL_NAME = "Account Cache Pool";

// create an Account object
Account::Account(const char* n, const char* id, int b):
	name(dupl_string(n)), account_id(dupl_string(id))
{
	balance = b;
}

// return a pointer to a new Account object
Account* Account::create(const char* id, const char* n, int b, os_database* db)
{
	// get a pointer to typespec for Account class
	os_typespec* ts = Account::get_os_typespec();
	// create an Account object
	return new(db, ts) Account(n, id, b);
}

// allocate storage to hold the string in s, copy s to the
// newly allocated persistent storage, and return a pointer to the storage
char* Account::dupl_string(const char* s)
{
	int len = strlen(s)+1;
	char* p = new(os_cluster::with(this), os_typespec::get_char(),
		len) char [len];
	return strcpy(p, s);
}

// withdraw amount from account balance and return new balance; if
// balance is less than amount, do nothing and return negative value
int Account::debit(int amount)
{
	if ( (balance - amount) >= 0 )
		return balance -= amount;
	else
		return balance - amount;
}

// add amount to balance and return new balance
int Account::credit(int amount)
{
	return balance += amount;
}

Account* Account::query_by_id(const char* id, os_database* db, os_set* coll)
{
	char qstr[QS_SIZE];

	sprintf(qstr, "!strcmp(account_id, \"%s\")", id);
	return (Account*)coll->query_pick((char*)"Account*", qstr, db);
}

///////////////////////////////
// global functions

// overloading of << for displaying information about an account
ostream& operator<<(ostream& os, Account& a)
{
	cout << "Account id: " << a.get_account_id() << endl;
	cout << "Name: " << a.get_name() << endl;
	cout << "Balance: " << a.get_balance() <<  endl;
	return os;
}

// configures and creates a cache pool manager, using an XML-based
// configuration file; also initializes collections facility
void setup(ifstream& xml_config,
	os_cache_pool_manager_config*& cfg, os_cache_pool_manager*& cpm)
{
	// configure and create cache pool manager from XML
	cfg = os_cache_pool_manager_config::create_from_xml_stream(xml_config);
	cpm = os_cache_pool_manager::create(*cfg);

	// initialize collections
	cpm->initialize_collections();
}

