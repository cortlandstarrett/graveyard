/* main.cpp -- driver program for CMTL example
 * The program does the following:
 *   - configures the cache pool manager, using the CMTL API
 *   - creates a database and database root
 *   - performs read and write virtual transactions
*/
#include "hello.h"

int main(int argc, char* argv[])
{
	OS_ESTABLISH_FAULT_HANDLER {
		const char* db_name = (argc > 1) ? argv[1] : "helloworld.db";
		const char* root_name = (argc > 2) ? argv[2] : "string";

		OS_ENTER_CMTL {
			setup(db_name, root_name);
			create_root();
			access_db_root();
			os_cache_pool_manager::get()->shutdown();
		} OS_LEAVE_CMTL
	} OS_END_FAULT_HANDLER

	return 0;
}
