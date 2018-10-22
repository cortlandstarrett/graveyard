#ifndef OSU_MONITOR_HH
#define OSU_MONITOR_HH

#include "base.hh"

class  OSUEXPORT osu_monitor {
public:
  static void initialize();
  static void initialize_all();
  static void log(const char* format,...);
protected:
  osu_monitor();
  ~osu_monitor();
};

#endif
