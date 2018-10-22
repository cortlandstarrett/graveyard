/* $Id: vdate.h,v 1.34 1997/06/19 00:53:19 robert Exp $ */

#ifndef vdateINCLUDED
#define vdateINCLUDED 1

/************************************************************

    vdate.h

    Visix internationalized date formatting and parsing routines

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vregexpINCLUDED
#include vregexpHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

typedef struct vdate			vdate;
typedef struct vdateFormat		vdateFormat;
typedef struct vdateFormatIterator	vdateFormatIterator;
typedef int				vdateNumber;
typedef int				vdateName;
typedef int				vdateFormatType;

/*
 * Exceptions:
 */
      
typedef struct vdateSyntaxException
{
  vexException	parent;
  vchar		*position;
} vdateSyntaxException;

typedef struct vdateRangeException
{
  vexException	parent;
} vdateRangeException;

/*
 * * * * * * * * * * * * * Exported constants * * * * * * * * * * * * * *
 */

/*
 * vdateNumber values:
 */

enum {
  vdateSECOND_NUMBER,
  vdateMINUTE_NUMBER,
  vdateHOUR_12_NUMBER,
  vdateHOUR_24_NUMBER,
  vdateDATE_NUMBER,
  vdateDAY_OF_YEAR_NUMBER,
  vdateMONTH_NUMBER,
  vdateYEAR_ABBREV_NUMBER,
  vdateYEAR_FULL_NUMBER,
  _vdateNUMBER_COUNT
};

/*
 * vdateName values:
 */

enum {
  vdateMERIDIAN_NAME,
  vdateWEEK_DAY_NAME,
  vdateMONTH_NAME,
  vdateTIME_ZONE_NAME,
  _vdateNAME_COUNT
};

/*
 * vdateFormatType values:
 */

enum {
  vdateFORMAT_NUMBER,
  vdateFORMAT_NAME,
  vdateFORMAT_TEXT,
  vdateFORMAT_WHITE_SPACE,
  _vdateFORMAT_TYPE_COUNT
};

/*
 * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * *
 */

void vdateStartup(void);


/*
 * Time/dates:
 */

vdate	*vdateCreate(void);
void	vdateInit(vdate *date);
void	vdateCopyInit(const vdate *from, vdate *to);
vdate	*vdateClone(const vdate *date);
void	vdateCopy(const vdate *source, vdate *dest);
void	vdateDestroy(vdate *date);

void 	vdateStore(vdate *date, vresource resource);
vdate 	*vdateLoad(vresource resource);
void 	vdateLoadInit(vdate *date, vresource resource);

void	vdateSetCurrent(vdate *date);

void 	vdateSetTimestamp(vdate *date, vtimestamp timestamp);
vtimestamp vdateGetTimestamp(vdate *date);

int	vdateGetSecond(const vdate *date);
int	vdateGetMinute(const vdate *date);
int	vdateGetHour(const vdate *date);
int	vdateGetDay(const vdate *date);
int	vdateGetDayOfWeek(vdate *date);
int	vdateGetDayOfYear(vdate *date);
int	vdateGetMonth(const vdate *date);
int	vdateGetYear(const vdate *date);
int	vdateGetTimeZoneOffset(vdate *date);
const vchar	*vdateGetTimeZoneName(vdate *date);

void	vdateSetSecond(vdate *date, int second);
void	vdateSetMinute(vdate *date, int minute);
void	vdateSetHour(vdate *date, int hour);
void	vdateSetDay(vdate *date, int day);
void	vdateSetMonth(vdate *date, int month);
void	vdateSetYear(vdate *date, int year);
void	vdateSetTimeZoneOffset(vdate *date, int minutesFromGMT);

void 	vdateAddSeconds(vdate *date, int seconds);
void 	vdateAddMinutes(vdate *date, int minutes);
void 	vdateAddHours(vdate *date, int hours);
void 	vdateAddDays(vdate *date, int days);
void 	vdateAddMonths(vdate *date, int months);
void 	vdateAddYears(vdate *date, int years);

void vdateConvertToMean(vdate *date);
void vdateConvertToLocal(vdate *date);

const vdate *vdateGetBase(void);
long vdateDifference(vdate *date1, vdate *date2);
long vdateDaysDifference(vdate *date1, vdate *date2);

/*
 * Using formats:
 */

vscribe	*vdateScribe(vdate *date);
vscribe	*vdateScribeFormatted(vdate *date, const vdateFormat *f);

void	vdateParse(const vchar *source, const vchar **end, vdate *dest); 
void	vdateSizedParse(const vchar *source, size_t length, const vchar **end,
			vdate *dest); 

void	vdateParseFormatted(const vchar *source, const vchar **end,
			    const vdateFormat *f, vdate *dest);
void	vdateSizedParseFormatted(const vchar *source, size_t length,
				 const vchar **end, const vdateFormat *f,
				 vdate *dest);

/*
 * Internationalized formats:
 */

const vdateFormat 	*vdateGetTerseTimeFormat(void);
const vdateFormat	*vdateGetTerseDateFormat(void);
const vdateFormat	*vdateGetTerseFormat(void);
const vdateFormat	*vdateGetNormalTimeFormat(void);
const vdateFormat	*vdateGetNormalDateFormat(void);
const vdateFormat 	*vdateGetNormalFormat(void);
const vdateFormat 	*vdateGetVerboseTimeFormat(void);
const vdateFormat 	*vdateGetVerboseDateFormat(void);
const vdateFormat 	*vdateGetVerboseFormat(void);

/*
 * Locale-specific data:
 */

int		vdateGetDaysInWeek(void);
int		vdateGetMonthsInYear(void);
int		vdateGetDaysInMonth(int month, int year);

const vchar 	*vdateGetDayOfWeekName(int day);
const vchar 	*vdateGetDayOfWeekNameAbbrev(int day);

const vchar 	*vdateGetMonthName(int month);
const vchar 	*vdateGetMonthNameAbbrev(int month);

const vchar	*vdateGetMeridianString(int /* vbool */ isAM);

const vchar  	*vdateGetMeanTimeZoneName(void);
const vchar  	*vdateGetLocalTimeZoneName(void);
int 	 	vdateGetLocalTimeZoneOffset(void);

/*
 * Creating/modifying formats:
 */

vdateFormat	*vdateCreateFormat(void);
void             vdateInitFormat (vdateFormat *format);
vdateFormat	*vdateCloneFormat(const vdateFormat *format);
vdateFormat 	*vdateLoadFormat(vresource resource);
void            vdateCopyInitFormat(vdateFormat *src, vdateFormat *dest);
void            vdateCopyFormat(vdateFormat *src, vdateFormat *dest);
void 		vdateLoadInitFormat(vdateFormat *format, vresource resource);
void 		vdateStoreFormat(vdateFormat *format, vresource resource);
void		vdateDestroyFormat(vdateFormat *format);



int		vdateGetFormatComponentCount(vdateFormat *format);

void 	vdateInsertFormatNumber(vdateFormat *format, int index,
				vdateNumber which, vnumFormat *number,
				vbool required, vbool shown);
void	vdateInsertFormatName(vdateFormat *format, int index,
			      vdateName which, vbool abbrev, 
			      vbool required, vbool shown);
void 	vdateInsertFormatText(vdateFormat *format, int index,
			      vchar *print, vregexp *match);
void 	vdateInsertFormatTextScribed(vdateFormat *format, int index,
				     vscribe *print, vregexp *match);
void	vdateInsertFormatWhiteSpace(vdateFormat *format, int index,
				    vbool required, vbool shown);

vbool 	vdateRemoveFormatComponentAt(vdateFormat *format, int index);

vdateFormatType vdateGetFormatTypeAt(vdateFormat *format, int index);	
vdateNumber	vdateGetFormatNumberAt(vdateFormat *format, int index);
vnumFormat 	*vdateGetFormatNumberFormatAt(vdateFormat *format, int index);
vbool		vdateIsFormatNumberRequiredAt(vdateFormat *format, int index);
vbool 		vdateIsFormatNumberShownAt(vdateFormat *format, int index);
vdateName	vdateGetFormatNameAt(vdateFormat *format, int index);
vbool		vdateIsFormatNameAbbrevAt(vdateFormat *format, int index);
vbool		vdateIsFormatNameRequiredAt(vdateFormat *format, int index);
vbool 		vdateIsFormatNameShownAt(vdateFormat *format, int index);
const vchar	*vdateGetFormatTextShowAt(vdateFormat *format, int index);
const vregexp	*vdateGetFormatTextMatchAt(vdateFormat *format, int index);
vbool		vdateIsFormatWhiteSpaceRequiredAt(vdateFormat *format,
						  int index);
vbool 		vdateIsFormatWhiteSpaceShownAt(vdateFormat *format, int index);

/*
 * Date format iterator
 */

void 		vdateInitFormatIterator(vdateFormatIterator *i,
					vdateFormat *format); 
					
vbool		vdateNextFormatIterator(vdateFormatIterator *i);
void		vdateDestroyFormatIterator(vdateFormatIterator *i);

int		vdateGetFormatIteratorIndex(const vdateFormatIterator *i);
vdateFormatType vdateGetFormatIteratorType(const vdateFormatIterator *i);
vdateNumber	vdateGetFormatIteratorNumber(const vdateFormatIterator *i);
vnumFormat 	*vdateGetFormatIteratorNumberFormat(const 
						    vdateFormatIterator *i);
vbool		vdateIsFormatIteratorNumberRequired(const 
						    vdateFormatIterator *i);
vbool 		vdateIsFormatIteratorNumberShown(const vdateFormatIterator *i);
vdateName	vdateGetFormatIteratorName(const vdateFormatIterator *i);
vbool		vdateIsFormatIteratorNameAbbrev(const vdateFormatIterator *i);
vbool		vdateIsFormatIteratorNameRequired(const 
						  vdateFormatIterator *i);
vbool 		vdateIsFormatIteratorNameShown(const vdateFormatIterator *i);
const vchar	*vdateGetFormatIteratorTextShow(const vdateFormatIterator *i);
const vregexp	*vdateGetFormatIteratorTextMatch(const vdateFormatIterator *i);
vbool		vdateIsFormatIteratorWhiteSpaceRequired(const 
						vdateFormatIterator *i);
vbool 		vdateIsFormatIteratorWhiteSpaceShown(const 
						     vdateFormatIterator *i);

/*
 * Exceptions:
 */

vdateSyntaxException *vdateGetSyntaxException(void);
const vexClass *vdateGetSyntaxExceptionClass(void);
vchar *vdateGetSyntaxExceptionPosition(vdateSyntaxException *e);

vdateRangeException *vdateGetRangeException(void);
const vexClass *vdateGetRangeExceptionClass(void);


/*
 * deprecated
 */

void 	vdateAddFormatNumber(vdateFormat *format, 
			     vdateFormatIterator *before,
			     vdateNumber which,
			     vnumFormat *number, vbool required, vbool shown);
void	vdateAddFormatName(vdateFormat *format, 
			   vdateFormatIterator *before,
			   vdateName which, vbool abbrev, 
			   vbool required, vbool shown);
void 	vdateAddFormatText(vdateFormat *format,
			   vdateFormatIterator *before,
			   vchar *print, vregexp *match);
void 	vdateAddFormatTextScribed(vdateFormat *format,
				  vdateFormatIterator *before,
				  vscribe *print, vregexp *match);
void	vdateAddFormatWhiteSpace(vdateFormat *format, 
				 vdateFormatIterator *before,
				 vbool required, vbool shown);

vbool 	vdateRemoveFormatComponent(vdateFormat *format, 
				   vdateFormatIterator *i);


/*
 * * * * * * * * * * * Privately Exported Types * * * * * * * * * * * * * * *
 */

struct vdate
{
  vloadable	object;
  vbyte 	second; 	/* 0 == 0 seconds */ 
  vbyte 	minute; 	/* 0 == 0 minutes */
  vbyte 	hour;		/* 0 == midnight */
  vbyte 	day;		/* 0 == 1st of month */
  vbyte 	month;		/* 0 == first month */

  vbyteSigned 	weekDay;	/* 0 == Sunday */

  short 	year;		/* 0 == year 1 B.C. */

  short 	yearDay;	/* 0 == first day of year */

  short 	timeZoneOffset;	/* number minutes from GMT (+ -> east) */
  vchar		*timeZoneName;
};


#define vdateCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct vdateClass	vdateClass;

struct vdateClass {
    vdateCLASS(vdateClass, vdate);
};


typedef struct _vdateFormatComponent {
  vbyte		type;
  union {
    struct {
      vnumFormat 	*format;
      vbyte 		which;
      vbyte 		required;
      vbyte 		shown;
    } 		number;
    struct {
      vbyte		which;
      vbyte		abbrev;
      vbyte 		required;
      vbyte 		shown;
    } 		name;
    struct {
      vstr		*print;
      vregexp		*match;
    }		string;
    struct {
      vbyte 		required;
      vbyte 		shown;
    }		whiteSpace;
  } u;
} _vdateFormatComponent;

struct vdateFormat
{
  vloadable		object;
  _vdateFormatComponent	*components;
};


#define vdateFormatCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct vdateFormatClass	vdateFormatClass;

struct vdateFormatClass {
    vdateFormatCLASS(vdateFormatClass, vdateFormat);
};


struct vdateFormatIterator
{
  vdateFormat		*format;
  int			 index;
};



/*
 * * * * * * * * * * * * Privately Exported Constants * * * * * * * * * * * *
 */

enum {
  _vdateSECONDS_ADD,
  _vdateMINUTES_ADD,
  _vdateHOURS_ADD,
  _vdateDAYS_ADD,
  _vdateMONTHS_ADD,
  _vdateYEARS_ADD
};

/*
 * * * * * * * * * * * Privately Exported Prototypes * * * * * * * * * * * * *
 */

vdateClass *_vdateGetDefaultClass(void);

vdateClass *_vdateGetClass(
    vdate			   *date
    );

vloadable *_vdateGetObject(
    vdate			   *date
    );

vdate *_vdateCreateOfClass(
    vdateClass                   *clas
    );

void _vdateInitOfClass(
    vdate                        *date,
    vdateClass                   *clas
    );

vdateFormatClass *_vdateGetDefaultFormatClass(void);

vdateFormatClass *_vdateGetFormatClass(
    vdateFormat			   *format
    );

vloadable *_vdateGetFormatObject(
    vdateFormat			   *format
    );

vdateFormat *_vdateCreateFormatOfClass(
    vdateFormatClass                   *clas
    );

void _vdateInitFormatOfClass(
    vdateFormat                        *format,
    vdateFormatClass                   *clas
    );

void _vdateParseFormatted(const vchar *source, const vchar **end,
			    const vdateFormat *f, vdate *dest);
void _vdateSizedParseFormatted(const vchar *source, size_t length,
				 const vchar **end, const vdateFormat *f,
				 vdate *dest);

void _vdateAdd(vdate *date, int field, int value);

vbool	_vdateGetDaylightSavings(void);

/*
 * * * * * * * * * * * * Privately Exported Variables * * * * * * * * * * * *
 */

extern vportLINK const vexClass _vdateSyntaxExceptionClass;
extern vportLINK const vexClass _vdateRangeExceptionClass;

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */

#define _vdateGetObject(d) \
    (vportBASE_OBJECT(d, object))

#define _vdateGetClass(d) \
    ((vdateClass*)vloadableGetClass(_vdateGetObject(d)))

#define _vdateCreateOfClass(c) \
    ((vdate*)vloadableCreateOfClass((vloadableClass*)(c)))

#define _vdateInitOfClass(d, c) \
    vloadableInitOfClass(_vdateGetObject(d), (vloadableClass*)(c))

#define vdateCreate() \
    (_vdateCreateOfClass(_vdateGetDefaultClass()))

#define vdateInit(d) \
    (_vdateInitOfClass(d, _vdateGetDefaultClass()))

#define vdateDestroy(d) \
    vloadableDestroy(_vdateGetObject(d))

#define vdateCopy(d, t) \
    vclassSend(_vdateGetClass(d), vloadableCOPY, (d, t))

#define vdateCopyInit(d, t) \
    vloadableCopyInit(_vdateGetObject(d), _vdateGetObject(t))

#define vdateClone(d) \
    ((vdate*)vloadableClone(_vdateGetObject(d)))

#define vdateStore(d, r) \
    vclassSend(_vdateGetClass(d), vloadableSTORE, (d, r))

#define vdateGetSecond(d)	((d)->second)
#define vdateGetMinute(d)	((d)->minute)
#define vdateGetHour(d)		((d)->hour)
#define vdateGetDay(d)		((d)->day)
#define vdateGetMonth(d)	((d)->month)
#define vdateGetYear(d)		((d)->year)
#define vdateGetTimeZoneName(d)	((d)->timeZoneName)
#define vdateGetTimeZoneOffset(d) ((d)->timeZoneOffset)

#define vdateAddSeconds(d,s)	_vdateAdd((d), _vdateSECONDS_ADD, (s))
#define vdateAddMinutes(d,m)	_vdateAdd((d), _vdateMINUTES_ADD, (m))
#define vdateAddHours(d,h)	_vdateAdd((d), _vdateHOURS_ADD, (h))
#define vdateAddDays(d,ds)	_vdateAdd((d), _vdateDAYS_ADD, (ds))
#define vdateAddMonths(d,m)	_vdateAdd((d), _vdateMONTHS_ADD, (m))
#define vdateAddYears(d,y)	_vdateAdd((d), _vdateYEARS_ADD, (y))

#define _vdateGetFormatObject(s) \
    (vportBASE_OBJECT(s, object))

#define _vdateGetFormatClass(s) \
    ((vdateFormatClass*)vloadableGetClass(_vdateGetFormatObject(s)))

#define _vdateCreateFormatOfClass(c) \
    ((vdateFormat*)vloadableCreateOfClass((vloadableClass*)(c)))

#define _vdateInitFormatOfClass(s, c) \
    vloadableInitOfClass(_vdateGetFormatObject(s), (vloadableClass*)(c))

#define vdateCreateFormat() \
    (_vdateCreateFormatOfClass(_vdateGetDefaultFormatClass()))

#define vdateInitFormat(s) \
    (_vdateInitFormatOfClass(s, _vdateGetDefaultFormatClass()))

#define vdateCopyInitFormat(s, d) \
    vloadableCopyInit (_vdateGetFormatObject(s), _vdateGetFormatObject(d))

#define vdateCopyFormat(s, d) \
    vloadableCopy (_vdateGetFormatObject(s), _vdateGetFormatObject(d))

#define vdateLoadInitFormat(s, r) \
    vloadableLoadInit(_vdateGetFormatObject(s), (r))

#define vdateDestroyFormat(s) \
    vloadableDestroy(_vdateGetFormatObject(s))

#define vdateCloneFormat(s) \
    ((vdateFormat*)vloadableClone((vloadable*)(_vdateGetFormatObject(s))))

#define vdateStoreFormat(s, r) \
    vloadableStore(_vdateGetFormatObject(s), (r))

#define vdateGetFormatTypeAt(f, i) \
    ((f)->components[i].type)
#define vdateGetFormatNumberAt(f, i) \
    ((f)->components[i].u.number.which)
#define vdateIsFormatNumberRequiredAt(f, i) \
    ((f)->components[i].u.number.required)
#define vdateIsFormatNumberShownAt(f, i) \
    ((f)->components[i].u.number.shown)
#define vdateGetFormatNameAt(f, i) \
    ((f)->components[i].u.name.which)
#define vdateIsFormatNameRequiredAt(f, i) \
    ((f)->components[i].u.name.required)
#define vdateIsFormatNameShownAt(f, i) \
    ((f)->components[i].u.name.shown)
#define vdateIsFormatNameAbbrevAt(f, i) \
    ((f)->components[i].u.name.abbrev)
#define vdateIsFormatWhiteSpaceRequiredAt(f, i) \
    ((f)->components[i].u.whiteSpace.required)
#define vdateIsFormatWhiteSpaceShownAt(f, i) \
    ((f)->components[i].u.whiteSpace.shown)

#define vdateInsertFormatText(f,i,p,m) \
    vdateInsertFormatTextScribed(f,i,vcharScribe(p),m)

#define vdateDestroyFormatIterator(i)	

#define vdateGetFormatIteratorIndex(i) \
    ((i)->index)
#define vdateGetFormatIteratorType(i) \
    vdateGetFormatTypeAt((i)->format, (i)->index)
#define vdateGetFormatIteratorNumber(i) \
    vdateGetFormatNumberAt((i)->format, (i)->index)
#define vdateGetFormatIteratorNumberFormat(i) \
    vdateGetFormatNumberFormatAt((i)->format, (i)->index)
#define vdateIsFormatIteratorNumberRequired(i) \
    vdateIsFormatNumberRequiredAt((i)->format, (i)->index)
#define vdateIsFormatIteratorNumberShown(i) \
    vdateIsFormatNumberShownAt((i)->format, (i)->index)
#define vdateGetFormatIteratorName(i) \
    vdateGetFormatNameAt((i)->format, (i)->index)
#define vdateIsFormatIteratorNameRequired(i) \
    vdateIsFormatNameRequiredAt((i)->format, (i)->index)
#define vdateIsFormatIteratorNameShown(i) \
    vdateIsFormatNameShownAt((i)->format, (i)->index)
#define vdateIsFormatIteratorNameAbbrev(i) \
    vdateIsFormatNameAbbrevAt((i)->format, (i)->index)
#define vdateGetFormatIteratorTextShow(i) \
    vdateGetFormatTextShowAt((i)->format, (i)->index)
#define vdateGetFormatIteratorTextMatch(i) \
    vdateGetFormatTextMatchAt((i)->format, (i)->index)
#define vdateIsFormatIteratorWhiteSpaceRequired(i) \
    vdateIsFormatWhiteSpaceRequiredAt((i)->format, (i)->index)
#define vdateIsFormatIteratorWhiteSpaceShown(i) \
    vdateIsFormatWhiteSpaceShownAt((i)->format, (i)->index)

#define _vdateIteratorToIndex(b) \
	((b) != NULL ? ((vdateFormatIterator *)(b))->index : -1)
#define vdateAddFormatNumber(f, b, w, n, r, s) \
    vdateInsertFormatNumber(f, _vdateIteratorToIndex(b), w, n, r, s)
#define vdateAddFormatName(f, b, w, a, r, s) \
    vdateInsertFormatName(f, _vdateIteratorToIndex(b), w, a, r, s)
#define vdateAddFormatTextScribed(f, b, p, m) \
    vdateInsertFormatTextScribed(f, _vdateIteratorToIndex(b), p, m)
#define vdateAddFormatText(f,b,p,m) \
    vdateAddFormatTextScribed(f,b,vcharScribe(p),m)
#define vdateAddFormatWhiteSpace(f, b, r, s) \
    vdateInsertFormatWhiteSpace(f, _vdateIteratorToIndex(b), r, s)

#define vdateRemoveFormatComponent(f, i) \
    vdateRemoveFormatComponentAt(f, _vdateIteratorToIndex(i))

#define vdateScribe(d) \
    vdateScribeFormatted((d), vdateGetNormalFormat())

#define vdateParseFormatted(s,e,f,d) \
    _vdateParseFormatted((s), (const vchar **)(e), (f), (d))
#define vdateSizedParseFormatted(s,l,e,f,d) \
    _vdateSizedParseFormatted((s), (l), (const vchar **)(e), (f), (d))

#define vdateParse(s,e,d) \
    vdateParseFormatted((s), (e), vdateGetNormalFormat(), (d))
#define vdateSizedParse(s,l,e,d) \
    vdateSizedParseFormatted((s), (l), (e), vdateGetNormalFormat(), (d))

#define vdateGetDaysInWeek()		(7)
#define vdateGetMonthsInYear()		(12)	

#define vdateGetSyntaxException() \
    ((vdateSyntaxException *)  \
     vexGetExceptionOfClass(&_vdateSyntaxExceptionClass))
#define vdateGetSyntaxExceptionClass() 		(&_vdateSyntaxExceptionClass)
#define vdateGetSyntaxExceptionPosition(e)  	((e)->position)

#define vdateGetRangeException() \
    ((vdateRangeException *)  \
     vexGetExceptionOfClass(&_vdateRangeExceptionClass))
#define vdateGetRangeExceptionClass() 		(&_vdateRangeExceptionClass)


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vdateINCLUDED */

