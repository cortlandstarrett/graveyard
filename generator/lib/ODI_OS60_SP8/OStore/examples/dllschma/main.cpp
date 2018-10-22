//
// Flights DB examples
//
// This file demonstrates some usages of the ObjectStore component
// schema feature.  We have packaged the application code and database 
// schema for an Airport Flights application into a component which
// is loaded and used by this example.  There are two versions of this 
// component for demonstration purposes which are called 'flight_cs' & 
// 'flight_cs2'.  The 'flight_cs' component is used to demonstrate 
// automatic loading and the 'flight_cs2' is used to demonstrate 
// manual loading.   
//
// This file must be compiled with one of the following macro 
// definitions:
//
//       CS_STATIC_LINK   - Define for examples that are static
//                          linked to the flight_cs component or
//                          object files. (flights & flights2)
// 
//       CS_DYNAMIC_LOAD  - Define for example that use explicit
//                          run-time DLL loading of the flight_cs 
//                          component. (flights3)
//
//       CS_MANUAL_LOAD   - Define for example that use explicit
//                          run-time DLL loading of the flight_cs
//                          component with automatic load reporting
//                          disabled. (flights4)
//  

#if !defined(CS_DYNAMIC_LOAD) && \
    !defined(CS_MANUAL_LOAD) && \
    !defined(CS_STATIC_LINK)
#error You must define CS_STATIC_LINK or CS_DYNAMIC_LINK or CS_MANUAL_LOAD
#endif

#include <iostream.h>
//#ifdef __SVR4
//#include <unistd.h> 
//#endif
//#ifdef WIN32
//#include <windows.h>
//#endif
#include <ostore/ostore.hh>
#include "common.hh"
#ifdef CS_MANUAL_LOAD
#include <ostore/nreloc/schftyps.hh>
#endif


// Flight component function pointer
typedef int (*flight_component_fp)(const char *);


int main ( int argc, char** argv )
{
  int rval = 0;

  // check the command line arguments.
  if(argc != 2) {
    cerr << "Usage: " << argv[0] << " <db_path> " << endl;
    return 1;
  }

  
  OS_ESTABLISH_FAULT_HANDLER
  objectstore::initialize();
  flight_component_fp cfp = NULL;  // pointer to flight component entry point


//
// load the component
//
#ifdef CS_STATIC_LINK 
  cfp = (flight_component_fp)flight_db_component;
#endif

#ifdef CS_DYNAMIC_LOAD
  const char *flight_cs_id = "DLL:flight_cs";  // DLL Identifer
#endif

#ifdef CS_MANUAL_LOAD
  const char *flight_cs_id = "DLL:flight_cs2";  // DLL Identifer
  os_DLL_schema_info *flight_cs2_sch_inf = NULL;
  os_schema_handle *cs2_sh; 
#endif

#if defined(CS_DYNAMIC_LOAD) || defined(CS_MANUAL_LOAD)
  const char *flight_cs_symname = "flight_db_component"; 
  os_DLL_handle dll_handle = os_null_DLL_handle;
  os_boolean caught_except = false;

  // Load the flight_cs component. 
  TIX_HANDLE(err_DLL_not_loaded) {
      // This is equivalent to calling 'dlopen' on Solaris2 or 
      // 'LoadLibrary' on WIN32 platforms.  objectstore::load_DLL
      // is provided as a convenience for application developers.
      dll_handle = objectstore::load_DLL(flight_cs_id, true); 
    }
  TIX_EXCEPTION {
      caught_except = true;
    }
  TIX_END_HANDLE
  if (caught_except || (dll_handle == os_null_DLL_handle)) {
      cout << "Error: " << tix_handler::get_report() << '\n';
      cout << "Cannot load component: " << flight_cs_id << '\n';
      return 2;
    }

  // Lookup the components entry point
  caught_except = false;
  TIX_HANDLE(err_DLL_symbol_not_found) {
      // Same as calling 'dlsym' on Solaris2 or 'GetProcAddress' on 
      // WIN32 platforms.  Provided as a convenience for application 
      // developers.
      cfp = (int(*)(const char*))
	objectstore::lookup_DLL_symbol(dll_handle, 
				       flight_cs_symname);
    } 
  TIX_EXCEPTION {
      caught_except = true;
    }
  TIX_END_HANDLE
  if (caught_except || !cfp) {
      cout << "Error: " << tix_handler::get_report() << '\n';
      cout << "Cannot locate symbol: " << flight_cs_symname << '\n';
      return 3;
    }
#endif

#ifdef CS_MANUAL_LOAD
  // Via a macro in the schema source file, we aranged for the 
  // schema generator to place a symbol name that we specified to 
  // be the name of the schema info structure (os_DLL_schema_info *).  
  // We simply lookup the symbol in the DLL to get at it.
  caught_except = false;
  TIX_HANDLE(err_DLL_symbol_not_found) {
      flight_cs2_sch_inf = (os_DLL_schema_info *)
	objectstore::lookup_DLL_symbol(dll_handle, 
				       "flight_cs2_dll_schema_info");
    } 
  TIX_EXCEPTION {
      caught_except = true;
    }
  TIX_END_HANDLE
  if (caught_except || !flight_cs2_sch_inf) {
      cout << "Error: " << tix_handler::get_report() << '\n';
      cout << "Cannot locate symbol: flight_cs2_dll_schema_info\n";
      return 4;
    }

  // Automatic load reporting has been disabled for this component
  // schema(flight_cs2).  Which means that the schema for this DLL 
  // does not automatically load when put in use.  So we must 
  // manually setup the loading process here.  

  // Tell ObjectStore that this DLL has been loaded.
  cs2_sh = flight_cs2_sch_inf->DLL_loaded();
#endif


//
// Use the flight component.
//
  rval = (*cfp)(argv[1]);


  objectstore::shutdown();

//
// Unload the component
//
#ifdef CS_MANUAL_LOAD
  // Tell ObjectStore that this DLL is about to be unloaded.
  flight_cs2_sch_inf->DLL_unloaded();
#endif

#if defined(CS_DYNAMIC_LOAD) || defined(CS_MANUAL_LOAD)
  objectstore::unload_DLL(dll_handle);
#endif

  OS_END_FAULT_HANDLER

  return rval;
}


