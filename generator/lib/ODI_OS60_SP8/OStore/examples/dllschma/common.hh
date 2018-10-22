#ifndef _COMMON_HH
#define _COMMON_HH

#ifdef WIN32
#define USE_DLL_EXPORT __declspec(dllexport)
#define USE_DLL_IMPORT __declspec(dllimport)
#else
#define USE_DLL_EXPORT
#define USE_DLL_IMPORT
#endif

#define false (os_boolean)0
#define true  !false

// entry point for flight_cs component.
extern "C" USE_DLL_EXPORT int
flight_db_component(const char *flight_db_path);

#endif // end of #ifndef _COMMON_HH
