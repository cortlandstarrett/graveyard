/* main.cpp -- driver program for CMTL example (configuring from XML file)
 * The program does the following:
 *
 *   - configures the cache pool manager from an XML file
 *   - creates a database and database root
 *   - performs read and write virtual transactions
 */
#include "hello.h"

int main(int argc, char* argv[])
{
	OS_ESTABLISH_FAULT_HANDLER {
		const char* config_info = (argc > 1) ? argv[1] : "hello.xml";

		OS_ENTER_CMTL {
			setup(config_info);
			create_root();
			access_db_root();
			os_cache_pool_manager::get()->shutdown();
		} OS_LEAVE_CMTL
	} OS_END_FAULT_HANDLER

	return 0;
}
