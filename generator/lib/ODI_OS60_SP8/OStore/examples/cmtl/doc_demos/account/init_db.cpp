// init_db.cpp: Uses the CMTL API to create database for accounts program.
// To keep the program simple, application code does minimal error-checking.
#include "account.h"

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		Account* a;
		os_cache_pool_manager_config* cfg;
		os_cache_pool_manager* cpm;

		// initialization data
		struct {
			const char* id; // account id
			const char* n; // name of Account
			int b; // account balance
		}acct_info[] =
		{
			"001", "Johnson", 25776,
			"002", "Goldsmith", 12,
			"003", "Swift", 3004,
			"004", "Pope", 675,
			"005", "Gay", 67890,
			"006", "Burke", 3366,
			"007", "Reynolds", 2345,
			"008", "Smart", 5678,
			"009", "Churchill", 1234,
			NULL, NULL, 0,
		};

		// name of XML file that contains information for configuring CMTL
		const char* config_info = (argc > 1) ? argv[1] : "account.xml";

		OS_ENTER_CMTL {
			ifstream xml_file(config_info, ios::nocreate | ios::in);

			// configure CMTL's transactional caches from XML file
			setup(xml_file, cfg, cpm);

			// create a transaction context for an update transaction (default)
			os_basic_transaction_context* ctx =
				os_basic_transaction_context::create();
			OS_BEGIN_VT (vt1, *ctx) {
				// create database
				os_database* db =
					os_cache::get_current()->create_database(LOGICAL_DB_NAME);

				// create a collection object set it as the root value
				os_set* acct_set = new(db, os_set::get_os_typespec()) os_set();
				cpm->get_root(LOGICAL_ROOT_NAME)->set_root_value(acct_set);

				// populate collection
				for (int i = 0; acct_info[i].n; i++) {
					// create Account object
					a = Account::create(acct_info[i].id,
						acct_info[i].n, acct_info[i].b, db);
					// insert it in collection
					acct_set->insert(a);
				}
				db->release_pointer();
			} OS_END_VT (vt1)
			delete ctx;
			cpm->shutdown();
		} OS_LEAVE_CMTL
		delete cfg;
		delete cpm;
	} OS_END_FAULT_HANDLER

	return 0;
}

