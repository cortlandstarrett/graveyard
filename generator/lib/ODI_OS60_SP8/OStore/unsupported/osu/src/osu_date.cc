#include "osu_date.hh"
#include <iomanip.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


static osu_date::boolean NO=0;
static osu_date::boolean YES=1;

extern const int BADMODAY  = 1;
extern const int BADDAYNAM = 2;
extern const int BADMONAM  = 3;
extern const int BADMONTH  = 4;
extern const int BADDAY    = 5;


static const osu_date::dayTy first_day_of_month[12] = {
  1,32,60,91,121,152,182,213,244,274,305,335
};

static const unsigned char days_in_month[12] = {
  31,28,31,30,31,30,31,31,30,31,30,31
};

static const char* month_names[12] = {
  "January","February","March","April","May","June",
  "July","August","September","October","November","December"
};

static const char* uc_month_names[12] = {
  "JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE",
  "JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"
};

static const char* week_day_names[7] = {
  "Monday","Tuesday","Wednesday",
  "Thursday","Friday","Saturday","Sunday"
};

static const char* uc_week_day_names[7] = {
  "MONDAY","TUESDAY","WEDNESDAY",
  "THURSDAY","FRIDAY","SATURDAY","SUNDAY"
};
static const unsigned int seconds_in_day = 24*60*60;

/*
 * Convert Gregorian calendar date to the corresponding Julian day number
 * j.  Algorithm 199 from Communications of the ACM, Volume 6, No. 8,
 * (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
 * This function not valid before that.
 */
osu_date::julTy osu_date::jday(monthTy m, dayTy d, yearTy y)
{
  unsigned long c, ya;
  if (m > 2)
    m -= 3;
  else {
    m += 9;
    y--;
  } /* else */
  c = y / 100;
  ya = y - 100*c;
  return ((146097*c)>>2) + ((1461*ya)>>2) + (153*m + 2)/5 + d + 1721119;
}

/*
 * Convert a Julian day number to its corresponding Gregorian calendar
 * date.  Algorithm 199 from Communications of the ACM, Volume 6, No. 8,
 * (Aug. 1963), p. 444.  Gregorian calendar started on Sep. 14, 1752.
 * This function not valid before that.
 */
void osu_date::mdy(monthTy& mm, dayTy& dd, yearTy& yy) const
{
  julTy j = julnum - 1721119;
  unsigned long y = ((j<<2) - 1) / 146097;
  j = (j<<2) - 1 - 146097*y;
  unsigned long d = j>>2;
  j = ((d<<2) + 3) / 1461;
  d = (d<<2) + 3 - 1461*j;
  d = (d + 4)>>2;
  unsigned long m = (5*d - 3)/153;
  d = 5*d - 3 - 153*m;
  d = (d + 5)/5;
  y = 100*y + j;
  if (m < 10)
    m += 3;
  else {
    m -= 9;
    y++;
  }
  mm = (monthTy)m;
  dd = (dayTy)d;
  yy = (yearTy)y;
}

/*
 *  Construct a Date for today's osu_date.
 */
osu_date::osu_date()
{
  // Thu Jan 23 15:17:56 EST 1992 changed for portability. S.M.Orlow
  //	long clk = time(0); 
  time_t clk = time(0);
  const struct tm* now = localtime(&clk);
  julnum = jday(now->tm_mon+1, now->tm_mday, now->tm_year+1900);
}


/*
 * The base date for this computation is Dec. 31 of the previous year.  That
 * is "day zero" in relation to the addition which is to take place.  Therefore,
 * we call jday() with the base date and then perform the addition.  Note
 * that dayCount may be positive or negative and that this function will
 * work the same in either case.
 */
osu_date::osu_date(long dayCount, yearTy referenceYear)
{
  julnum = jday(12, 31, referenceYear-1) + dayCount;  
}


/*
 * Constructs a date with Jan. 1, 1901 as the "day zero".  Date(-1) = Dec. 31, 1900
 * and Date(1) = Jan. 2, 1901.
 */
osu_date::osu_date(long dayCount)
{
  julnum = jday(1, 1, 1901) + dayCount;
}

osu_date::boolean
osu_date::dayWithinMonth(monthTy month, dayTy day, yearTy year)
{
  if (day <= 0) return NO;
  unsigned daysInMonth  = days_in_month[month-1];
  if (leapYear(year) && month == 2) daysInMonth++;
  if (day > daysInMonth) return NO;
  return YES;
}

/*
 * Construct a Date for the given day, monthName, and year.
 */
osu_date::osu_date(dayTy day, const char* monthName, yearTy year)
{
  monthTy m = numberOfMonth(monthName);
  if (year <= 99) year += 1900;
  if (!dayWithinMonth(m, day, year)) {
    throw BADMODAY;
  }
  julnum = jday(m, day, year);			
}

static void skipDelim(istream& strm)
{
  char c;
  if (!strm.good()) return;
  strm >> c;
  while (strm.good() && !isalnum(c)) strm >> c;
  if (strm.good()) strm.putback(c);
}

/*
 * Parse the name of a month from input stream.
 */
static const char* parseMonth(istream& strm)
{
  static char month[10];
  register char* p = month;
  char c;
  skipDelim(strm);
  strm.get(c);
  while (strm.good() && isalpha(c) && (p != &month[10])) {
    *p++ = c;
    strm.get(c);
  }
  if (strm.good()) strm.putback(c);
  *p = '\0';
  return month;
}

/*
 * Parse a date from the specified input stream.  The date must be in one
 * of the following forms: dd-mmm-yy, mm/dd/yy, or mmm dd,yy; e.g.: 10-MAR-86,
 * 3/10/86, or March 10, 1986.  Any non-alphanumeric character may be used as
 * a delimiter.
 */
osu_date::julTy osu_date::parseDate(istream& strm)
{
  unsigned d,m,y;
  const char* mon;
  if (strm.good()) {
    skipDelim(strm);
    strm >> m;	 // try to parse day or month number 
    skipDelim(strm);
    if (strm.eof()) return 0;
    if (strm.fail()) {	// parse <monthName><day><year> 
      strm.clear();
      mon = parseMonth(strm);	// parse month name 
      skipDelim(strm);
      strm >> d;		// parse day 
    }
    else {			// try to parse day number 
      strm >> d;
      if (strm.eof()) return 0;
      if (strm.fail()) {	// parse <day><monthName><year> 
	d = m;
	strm.clear();
	mon = parseMonth(strm);		// parse month name 
      }
      else {			// parsed <monthNumber><day><year> 
	mon = nameOfMonth(m);
      }
    }
    skipDelim(strm);
    strm >> y;
  }
  if (!strm.good()) return 0;
  return osu_date(d,mon,y).julnum;
}

osu_date::osu_date(istream& strm)	{ julnum = parseDate(strm); }

/*
 * Returns the number, 1-7, of the day of the week named nameOfDay.
 */
osu_date::dayTy osu_date::dayOfWeek(const char* nameOfDay)
{
  char s[64];
  ::strncpy(s,nameOfDay,sizeof(s));
  register unsigned len = ::strlen(s);
  if (len > 2) {
    register unsigned i;
    for (i =0;i < len;i++) {
      s[i] = toupper(s[i]);
    }
    for (i =0; i<7; i++)
      if (strncmp(s,uc_week_day_names[i],len)==0) return i+1;
  }
  throw BADDAYNAM;
  return 0;
}

/*
 * How many days are in the given yearTy year?
 */
osu_date::dayTy osu_date::daysInYear(yearTy year)
{
  return (leapYear(year)) ? 366 : 365;
}

/*
 * Returns the number, 1-12, of the month named nameOfMonth.
 */
osu_date::monthTy osu_date::numberOfMonth(const char* nameOfMonth)
{
  char s[64];
  ::strncpy(s,nameOfMonth,sizeof(s));
  register unsigned len = ::strlen(s);
  if (len > 2) {
    unsigned i;
    for (i = 0;i < len;i++) {
      s[i] = toupper(s[i]);
    }
    register const char* p = s;
    for (i =0; i<12; i++)
      if (strncmp(p,uc_month_names[i],len)==0) return i+1;
  }
  throw BADMONAM;
  return 0;	// never executed 
}

/*
 *   Algorithm from K & R, "The C Programming Language", 1st ed.
 */
osu_date::boolean
osu_date::leapYear(yearTy year)
{
  if ((year&3) == 0 && year%100 != 0 || year % 400 == 0)
    return YES;
  else
    return NO;
}

osu_date::boolean
osu_date::leap() const
{
  return leapYear(year());
}

/*
 * Returns a string name for the month number.
 */
const char* osu_date::nameOfMonth(monthTy monthNumber)
{
  if (monthNumber < 1 || monthNumber > 12)
    throw BADMONTH;
  return month_names[monthNumber-1];
}

/*
 * Returns a string name for the weekday number.
 * Monday == 1, ... , Sunday == 7
 */
const char* osu_date::nameOfDay(dayTy weekDayNumber)
{
  if (weekDayNumber < 1 || weekDayNumber > 7)
    throw BADDAY;
  return week_day_names[weekDayNumber-1];
}

const char* osu_date::nameOfMonth() const	{ return nameOfMonth(month()); }

osu_date::monthTy osu_date::month() const
{
  monthTy m; dayTy d; yearTy y;
  mdy(m, d, y);
  return m;
}

osu_date::dayTy osu_date::firstDayOfMonth(monthTy month) const
{
  if (month > 12)
    throw BADMONTH;
  unsigned firstDay = first_day_of_month[month-1];
  if (month > 2 && leap()) firstDay++;
  return firstDay;
}

osu_date osu_date::previous(const char* nameOfDay) const
{
  dayTy this_day_Of_Week, desired_day_Of_Week;
  julTy j;

  //	Set the desired and current day of week to start at 0 (Monday)
  //	and end at 6 (Sunday).

  desired_day_Of_Week = dayOfWeek(nameOfDay) - 1; // These functions return a value
  this_day_Of_Week    = weekDay() - 1;		// from 1-7.  Subtract 1 for 0-6.
  j = julnum;

  //	Have to determine how many days difference from current day back to
  //	desired, if any.  Special calculation under the 'if' statement to
  //	effect the wraparound counting from Monday (0) back to Sunday (6).

  if (desired_day_Of_Week > this_day_Of_Week)
    this_day_Of_Week += 7 - desired_day_Of_Week;
  else
    this_day_Of_Week -= desired_day_Of_Week;
  j -= this_day_Of_Week; // Adjust j to set it at the desired day of week.
  return osu_date(j);
}

/*
 * Although this seems a little strange, it works.  (julnum + 1) % 7 gives the
 * value 0 for Sunday ... 6 for Saturday.  Since we want the list to start at
 * Monday, add 6 (mod 7) to this.  Now we have Monday at 0 ... Sunday at
 * 6.  Simply add 1 to the result to obtain Monday (1) ... Sunday (7).
 */
osu_date::dayTy osu_date::weekDay() const
{
  return ((((julnum + 1) % 7) + 6) % 7) + 1;
}

/*
 * Returns the year of this Date.
 */
osu_date::yearTy osu_date::year() const
{
  monthTy m; dayTy d; yearTy y;
  mdy(m, d, y);
  return y;
}

/*
 * Returns the day of the year of this Date.  First we need to find what year we
 * are talking about, and then subtract this julnum from the julnum for December 31
 * of the preceeding year.
 */
osu_date::dayTy osu_date::day() const
{
  return julnum - jday(12, 31, year()-1);
}


osu_date::dayTy osu_date::dayOfMonth() const
{
  monthTy m; dayTy d; yearTy y;
  mdy(m, d, y);
  return d;
}

void osu_date::printOn(ostream& strm) const
{
  strm << setfill(' ') << setw(2) << dayOfMonth() << '-';
  strm.write(nameOfMonth(), 3);
  strm << '-' << setfill('0') << setw(4) << year();
}

void osu_date::scanFrom(istream& strm)	{ julnum = parseDate(strm); }


