// hello.h
// declares functions implemented in hello.cpp

#include <ostore/ostore.hh>
#include <ostore/cmtl.hh>

void setup(const char* physical_db, const char* physical_root);
void create_root();
void access_db_root();
void read_db_root();
void write_db_root();
