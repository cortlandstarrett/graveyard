
#include <stdio.h>
#include <ostore/ostore.hh>
#define OS_EMIT_BODIES 
#include "ldrhdr.h"

int main ( int argc, char** argv )
   {
   OS_ESTABLISH_FAULT_HANDLER

   objectstore::initialize();

   if(argc !=2 ) {
     fprintf(stderr,"Should be one argument\n");
     return 1;
   }

   os_database* dummy = 0;

   TIX_HANDLE(all_exceptions) {
     dummy = os_database::create(argv[1],0664,1);
   } TIX_EXCEPTION { // all_exceptions
     return 1;
   } TIX_END_HANDLE // all_exceptions

   objectstore::shutdown();
   return 0;
   OS_END_FAULT_HANDLER
}

