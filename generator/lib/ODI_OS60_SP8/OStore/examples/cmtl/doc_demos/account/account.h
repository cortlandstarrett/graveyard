// account.h: defines the Account class
#include <iostream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ostore/cmtl.hh>
#include <ostore/coll.hh>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

// logical names
extern const char* LOGICAL_DB_NAME;
extern const char* LOGICAL_ROOT_NAME;
extern const char* CACHE_POOL_NAME;

// forward declarations
class Account;

// global functions
ostream& operator<<(ostream& os, Account& a);
void setup(ifstream& xml_config,
	os_cache_pool_manager_config*& cfg, os_cache_pool_manager*& cpm);

class Account {
private:
	const char* name; // last name
	const char* account_id; // 3-character string
	int balance; // balance in account

	char* dupl_string(const char* s);

public:
	Account(const char* n, const char* id, int b);
	~Account() { delete [] (char*)name; delete [] (char*)account_id; }
	const char* get_name() { return name; }
	const char* get_account_id() { return account_id; }
	int get_balance() { return balance; }
	int debit(int amount);
	int credit(int amount);
	static Account* create(const char* id, const char* n, int b,
		os_database* db);
	static Account* query_by_id(const char* id, os_database* db, os_set* coll);

	// ObjectStore implements this function
	static os_typespec* get_os_typespec();

private:
	// declared but unimplemented functions to prevent
	// inadvertent calls
	Account();
	Account(const Account&);
	Account& operator=(const Account&);
};

