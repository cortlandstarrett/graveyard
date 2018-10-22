#ifndef OSU_BASE_HH
#define OSU_BASE_HH

#include <ostore/osreleas.hh>

/* Microsoft VC++ 4.2 and above set _DEBUG when /MDd is specified, to mean
** "link with msvcrtd.lib and the debug C runtime".  We do the same.  If
** you use _DEBUG for your own debugging, you can define _ODI_FORCE_OSUMON_LIB
** to force the use of osumon.lib instead of osumond.lib
*/
#ifdef _MSC_VER
#if defined(_DEBUG) && !defined(_ODI_FORCE_OSUMON_LIB)
#if OS_MAJOR_RELEASE == 6
#pragma comment(lib, "dsu6mon.lib")
#else
#pragma comment(lib, "dsu5mon.lib")
#endif
#else
#if OS_MAJOR_RELEASE == 6
#pragma comment(lib, "osu6mon.lib")
#else
#pragma comment(lib, "osu5mon.lib")
#endif
#endif
#define OSUEXPORT __declspec(dllexport)
#else
#define OSUEXPORT
#endif

#endif

