#ifndef	OSU_DATE_HH
#define	OSU_DATE_HH

#include <iostream.h>
#undef max
#undef min

//
// osu_date class was taken from Date class in NIHCL. 
//
class osu_date {
 public: // type definitions
  typedef unsigned short dayTy;
  typedef unsigned short monthTy;
  typedef unsigned short yearTy;
  typedef unsigned long  julTy;
  typedef char boolean;
 public: // static member functions
  static dayTy dayOfWeek(const char* dayName);
  static boolean dayWithinMonth(monthTy month, dayTy day, yearTy year);
  static dayTy daysInYear(yearTy year);
  static julTy jday(monthTy m, dayTy d, yearTy y);
  static boolean leapYear(yearTy year);
  static const char* nameOfDay(dayTy weekDayNumber);
  static const char* nameOfMonth(monthTy monthNumber);
  static monthTy numberOfMonth(const char* monthName);
 public: // constructors
  osu_date();
  osu_date(long dayCount);
  osu_date(long dayCount, yearTy referenceYear);
  osu_date(dayTy newDay, const char* monthName, yearTy newYear);
  osu_date(istream&);
 public: // comparison operators
  boolean operator<(const osu_date& date) const	{ return julnum < date.julnum; }
  boolean operator<=(const osu_date& date) const	{ return julnum <= date.julnum; }
  boolean operator>(const osu_date& date) const	{ return date < *this; }
  boolean operator>=(const osu_date& date) const	{ return date <= *this; }
  boolean operator==(const osu_date& date) const	{ return julnum == date.julnum; }
  boolean operator!=(const osu_date& date) const	{ return julnum != date.julnum; }
  friend osu_date operator+(const osu_date& dt, int dd)	{
    return osu_date(dt.julnum + dd); }
  friend osu_date operator+(int dd, const osu_date& dt)	{
    return osu_date(dt.julnum + dd); }
  int operator-(const osu_date& dt) const	        {
    return (int)(julnum - dt.julnum); }
  osu_date operator-(int dd) const		        {
    return osu_date(julnum - dd); }
  void operator+=(int dd)			{ julnum += dd; }
  void operator-=(int dd)			{ julnum -= dd; }
  boolean between(const osu_date& d1, const osu_date& d2) const {
    return julnum >= d1.julnum && julnum <= d2.julnum;
  }
 public: // accessors
  dayTy day() const;
  dayTy dayOfMonth() const;
  dayTy firstDayOfMonth() const		        { return firstDayOfMonth(month()); }
  dayTy firstDayOfMonth(monthTy month) const;
  boolean leap() const;
  osu_date max(const osu_date& dt) const { 
    if (dt.julnum > julnum) return dt;
    else return *this;
  }
  void mdy(monthTy&,dayTy&,yearTy&) const;
  osu_date min(const osu_date& dt) const {
    if (dt.julnum < julnum) return dt;
    else return *this;
  }
  monthTy	month() const;
  const char* nameOfMonth() const;
  osu_date previous(const char* dayName) const;
  dayTy weekDay() const;
  yearTy year() const;
 public:
  void printOn(ostream& strm) const;
  void scanFrom(istream& strm);
 private: // private member variables
  julTy julnum; 
  osu_date(julTy j)                                   { julnum = j; }
  julTy parseDate(istream&);
};

#endif
