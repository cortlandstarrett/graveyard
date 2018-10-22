#include "osu_datetime.hh"
#include <iomanip.h>
#include <time.h>

static const unsigned long DAYMILLISEC  = (24*60*60*1000);
static const unsigned long HOURMILLISEC = (60*60*1000);
static const unsigned long MINMILLISEC  = (60*1000);

osu_datetime::osu_datetime(osu_date& d, unsigned int millisec)
  : osu_date(d),
    millisecs_(millisec % DAYMILLISEC)
{
  if (millisec > DAYMILLISEC) {
    int ndays = millisec/DAYMILLISEC;
    (*this) += ndays;
  }
}

osu_datetime::hourTy osu_datetime::hour() const
{
  return millisecs_ / HOURMILLISEC;
}

osu_datetime::minTy osu_datetime::minute() const
{
  return (millisecs_ % HOURMILLISEC) / MINMILLISEC;
}


osu_datetime::secTy osu_datetime::second() const
{
  return (millisecs_ % MINMILLISEC) / 1000;
}


osu_datetime::msecTy osu_datetime::msec() const
{
  return (millisecs_  % 1000);
}



void osu_datetime::hour(osu_datetime::hourTy hr)
{
  if ((hr < 0) || (hr > 23)) {
    // invalid hour given.
    // throw exception.
    return;
  }

  long now = hour();
  millisecs_ += ((hr-now)*HOURMILLISEC);
}

void osu_datetime::minute(osu_datetime::minTy min)
{
  if ((min < 0) || (min > 59)) {
    // invalid minute.
    // throw exception
    return;
  }
  

  long now = minute();
  millisecs_ += ((min-now)*MINMILLISEC);
}

void osu_datetime::second(osu_datetime::secTy sec)
{
  if ((sec < 0) || (sec > 59)) {
    // invalid second.
    // throw exception
    return;
  }

  long now = second();
  millisecs_ += ((sec-now)*1000);
}

void osu_datetime::addMilliSecs(msecTy milli)
{
  millisecs_ += milli;
  if (milli > 0) {
    if (millisecs_ > DAYMILLISEC) {
      millisecs_ = millisecs_ % DAYMILLISEC;
      osu_date& d = (*this);
      d += (millisecs_/DAYMILLISEC);
    }
  } else {
    if (millisecs_ < 0) {
      int less = 0;
      do {
	less++;
	millisecs_ += DAYMILLISEC;
      } while (millisecs_ < 0);
      osu_date& d = (*this);
      d -= less;
    }
  }
}

void osu_datetime::printOn(ostream& strm) const
{
  osu_date::printOn(strm);
  strm << ' ' << setfill('0') << setw(2) << hour()
       << ':' << setw(2) << minute()
       << ':' << setw(2) << second()
       << '.' << setw(3) << msec();
  strm << setfill(' ');
}

void osu_datetime::scanFrom(istream& strm)
{
  osu_date::scanFrom(strm);
  // need to do the rest of the stream.

}

int osu_datetime::null()
{
  osu_date dt;
  if (dt == *(osu_date*)this) {
    return (millisecs_ == 0);
  }
  return 0;
}

osu_datetime osu_datetime::now()
{
  osu_date date;
  time_t clk = time(0);
  const struct tm* now = localtime(&clk);
  osu_datetime dt(date);
  dt.hour(now->tm_hour);
  dt.minute(now->tm_min);
  dt.second(now->tm_sec);

  return dt;
}

