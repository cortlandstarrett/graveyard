#ifndef OSU_DATETIME_HH
#define OSU_DATETIME_HH

#include "osu_date.hh"

// osu_datetime
//   osu_date + # of millisecs into the day.
//
class osu_datetime :public osu_date
{
public:
  typedef  int hourTy;
  typedef  int minTy;
  typedef  int secTy;
  typedef  int msecTy;
public:
  osu_datetime() : osu_date(0L), millisecs_(0) { ; }
  osu_datetime(osu_date& d, unsigned int millisec = 0);
public: // accessors
  hourTy hour()   const;
  minTy  minute() const;
  secTy  second() const;
  msecTy msec()   const;
public: // settors
  void hour(hourTy);
  void minute(minTy);
  void second(secTy);
  void msec(msecTy);
  void addMilliSecs(msecTy);
public:
  void printOn(ostream& strm) const;
  void scanFrom(istream& strm);
public:
  friend ostream& operator<<(ostream& o, osu_datetime& dt) {
    dt.printOn(o);
    return o;
  }
public:
  int null();
  static osu_datetime now();
private:
  long millisecs_;
};

#endif
