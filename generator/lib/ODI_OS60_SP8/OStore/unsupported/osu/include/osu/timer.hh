#ifndef OSU_TIMER_HH
#define OSU_TIMER_HH

#include "base.hh"

class OSUEXPORT osu_timeval {
public:
  osu_timeval() { zero(); }
  void zero() { secs = usecs = 0; }
  osu_timeval& operator -=(osu_timeval& v)
  {
    secs -= v.secs;
    usecs -= v.usecs;
    if (usecs < 0) {
      usecs += 1000000;
      secs--;
    }
    if (usecs >= 1000000) {
      secs++;
      usecs -= 1000000;
    }
    return *this;
  }
  osu_timeval& operator +=(osu_timeval& v)
  {
    secs += v.secs;
    usecs += v.usecs;
    if (usecs >= 1000000) {
      usecs -= 1000000;
      secs++;
    }
    if (usecs < 0) {
      usecs += 1000000;
      secs--;
    }
    return *this;
  }
public:
  long secs;  /* seconds */
  long usecs; /* and microseconds */
};

//
//       class:  osu_wall_timer
//
// description:  used to extract wallclock times between (reset and stop)...
//
//        note:  wallclock time is not a very good measurement of performance.
//               A processes ability to get CPU cycles, disk control, swapping,
//               etc. can greatly affect the wallclock time of a process
//               run...
//
class OSUEXPORT osu_wall_timer  {
protected:
  void getwalltime(osu_timeval*);
private:
  osu_timeval t_start;
  osu_timeval t_total;
public:
  osu_wall_timer() { reset();   }
  unsigned msecs() { 
    return t_total.secs*1000 + t_total.usecs/1000;
  }
  void     start() { getwalltime(&t_start); }
  void     reset() { start(); t_total.zero(); }
  void     stop()  {
    osu_timeval t_end;
    getwalltime(&t_end);
    t_total += t_end;
    t_total -= t_start;
    t_start = t_end;
  }
};


//
//       class:  osu_proc_timer
//
// description:  used to extract CPU time used in a running process
//               between reset and stop...  CPU time for user time and
//               system time in millisecond can be retrieved...
//

class OSUEXPORT osu_proc_timer {
protected:
  void getproctimes(osu_timeval* user, osu_timeval* kernel);
public:
  osu_proc_timer()  { reset(); }
  unsigned user()   {
    return tu_total.secs*1000 + tu_total.usecs/1000;
  }
  unsigned kernel() {
    return tk_total.secs*1000 + tk_total.usecs/1000;
  }
  void     start()  {
    getproctimes(&tu_start, &tk_start);
  }
  void     reset()  { start(); tu_total.zero(); tk_total.zero(); }

  void     stop()   {
    osu_timeval tu_end;
    osu_timeval tk_end;
    getproctimes(&tu_end, &tk_end);
    tu_total += tu_end;
    tu_total -= tu_start;
    tk_total += tk_end;
    tk_total -= tk_start;
    tu_start = tu_end;
    tk_start = tk_end;
  }
public:
  osu_timeval   tu_start;
  osu_timeval   tk_start;
  osu_timeval   tu_total;
  osu_timeval   tk_total;
};


//
//       class:  osu_sys_timer
//
// description:  combines wallclock timer and process timer into one
//               class...
//
//     methods:  start()   - start timer
//               stop()    - stop timer (adds time since start to timer)
//               reset()   - reset timer (reset to 0 and starts timer)
//               msecs()   - returns wallclock time in millisecs
//               kernel()  - returns system time in millisecs
//               user()    - returns user time in millisecs

class OSUEXPORT osu_sys_timer :public osu_wall_timer, public osu_proc_timer {
public:
  osu_sys_timer() : osu_wall_timer(), osu_proc_timer() { ; }
  void     reset() {
    osu_wall_timer::reset();
    osu_proc_timer::reset();
  }
  void     start() {
    osu_wall_timer::start();
    osu_proc_timer::start();
  }
  void     stop()  {
    osu_wall_timer::stop();
    osu_proc_timer::stop();
  }
};

#endif

