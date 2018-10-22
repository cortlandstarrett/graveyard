// hello.h
// declares functions defined in hello.cpp

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <ostore/ostore.hh>
#include <ostore/cmtl.hh>

void setup(const char *xml_path);
void create_root();
void access_db_root();
void read_db_root();
void write_db_root();
