#include "osu_timer.hh"

#ifdef _MSC_VER 

#include <time.h>
#include <sys/timeb.h>
#include <math.h>
#include <windows.h>
#include <windef.h>
#include <winbase.h>

static void FILETIME2microsecs(FILETIME& time, long& secs, long& microsecs)
{
  DWORDLONG adjust = 0x19db1ded53e8000i64;

  ULARGE_INTEGER _100ns = {time.dwLowDateTime,
                           time.dwHighDateTime};
  _100ns.QuadPart -= adjust;

  // Convert 100ns units to seconds;
  secs = long (_100ns.QuadPart / (10000 * 1000));

  // Convert remainder to microseconds;
  microsecs = long ((_100ns.QuadPart % (10000 * 1000)) / 10);
}


void osu_wall_timer::getwalltime(osu_timeval* time)
{
  //  gettime(time->secs, time->microsecs);
  FILETIME   tfile;
  ::GetSystemTimeAsFileTime (&tfile);

  FILETIME2microsecs(tfile,time->secs,time->usecs);
}

void osu_proc_timer::getproctimes(osu_timeval* user, osu_timeval* kernel)
{
  FILETIME dummy;
  FILETIME _Kernel;
  FILETIME _User;

  GetProcessTimes(GetCurrentProcess(), &dummy, &dummy,
		  &_Kernel, &_User);

  FILETIME2microsecs(_User,   user->secs,   user->usecs);
  FILETIME2microsecs(_Kernel, kernel->secs, kernel->usecs);
}


#else

// need getrusage and gettimeofday

#include <sys/resource.h>
#ifdef  __hpux
#include <sys/syscall.h>
#endif

#include <sys/time.h>

void osu_wall_timer::getwalltime(osu_timeval* time)
{
  struct timeval t_time;
  gettimeofday(&t_time,0);
  time->secs      = t_time.tv_sec;
  time->usecs  = t_time.tv_usec;
}

void osu_proc_timer::getproctimes(osu_timeval* user, osu_timeval* kernel)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF,&usage);

  user->secs         = usage.ru_utime.tv_sec;
  user->usecs        = usage.ru_utime.tv_usec;
  kernel->secs       = usage.ru_stime.tv_sec;
  kernel->usecs      = usage.ru_stime.tv_usec;
}

#endif

