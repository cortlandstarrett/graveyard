/* $Id: vfield.h,v 1.22 1997/10/24 17:31:36 robert Exp $ */

/************************************************************

    vfield.h

    C Interface file for the Field Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vfieldINCLUDED
#define vfieldINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdateINCLUDED
#include vdateHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vformatINCLUDED
#include vformatHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vstdioHEADER
#include vstdioHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

#define vfield_BooleanInterface      (_vfieldPredefs [_vfield_BooleanInterface])
#define vfield_DateInterface         (_vfieldPredefs [_vfield_DateInterface])
#define vfield_DoubleInterface       (_vfieldPredefs [_vfield_DoubleInterface])
#define vfield_LongInterface         (_vfieldPredefs [_vfield_LongInterface])
#define vfield_ScribeInterface       (_vfieldPredefs [_vfield_ScribeInterface])
#define vfield_UnsignedLongInterface (_vfieldPredefs [_vfield_UnsignedLongInterface])

#define vfield_ErrorMessage     (_vfieldPredefs [_vfield_ErrorMessage])
#define vfield_Format           (_vfieldPredefs [_vfield_Format])
#define vfield_Maximum          (_vfieldPredefs [_vfield_Maximum])
#define vfield_Minimum          (_vfieldPredefs [_vfield_Minimum])
#define vfield_Null             (_vfieldPredefs [_vfield_Null])
#define vfield_NullAllowed      (_vfieldPredefs [_vfield_NullAllowed])
#define vfield_Title		(_vfieldPredefs [_vfield_Title])
#define vfield_Value		(_vfieldPredefs [_vfield_Value])


/* vfield attribute id's */
enum {
  vfieldID_ATTRIBUTE_ERROR_MESSAGE      = vobjectNEXT_ID_ATTRIBUTE,
  vfieldID_ATTRIBUTE_FORMAT,
  vfieldID_ATTRIBUTE_NULL,
  vfieldID_ATTRIBUTE_NULL_ALLOWED,
  vfieldID_ATTRIBUTE_TITLE,
  vfieldNEXT_ID_ATTRIBUTE
};

/* vfieldBoolean attribute id's */
enum {
  vfieldBooleanID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldBooleanNEXT_ID_ATTRIBUTE
};

/* vfieldDate attribute id's */
enum {
  vfieldDateID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldDateID_ATTRIBUTE_MIN,
  vfieldDateID_ATTRIBUTE_MAX,
  vfieldDateNEXT_ID_ATTRIBUTE
};

/* vfieldDouble attribute id's */
enum {
  vfieldDoubleID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldDoubleID_ATTRIBUTE_MIN,
  vfieldDoubleID_ATTRIBUTE_MAX,
  vfieldDoubleNEXT_ID_ATTRIBUTE
};

/* vfieldLong attribute id's */
enum {
  vfieldLongID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldLongID_ATTRIBUTE_MIN,
  vfieldLongID_ATTRIBUTE_MAX,
  vfieldLongNEXT_ID_ATTRIBUTE
};

/* vfieldString attribute id's */
enum {
  vfieldStringID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldStringNEXT_ID_ATTRIBUTE
};

/* vfieldUnsignedLong attribute id's */
enum {
  vfieldUnsignedLongID_ATTRIBUTE_VALUE          = vfieldNEXT_ID_ATTRIBUTE,
  vfieldUnsignedLongID_ATTRIBUTE_MIN,
  vfieldUnsignedLongID_ATTRIBUTE_MAX,
  vfieldUnsignedLongNEXT_ID_ATTRIBUTE
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vfield			    vfield;
typedef struct vfieldAttributesChanged      vfieldAttributesChanged;
typedef struct vfieldBoolean                vfieldBoolean;
typedef struct vfieldDate                   vfieldDate;
typedef struct vfieldDouble                 vfieldDouble;
typedef struct vfieldLong                   vfieldLong;
typedef struct vfieldString                 vfieldString;
typedef struct vfieldUnsignedLong           vfieldUnsignedLong;

typedef struct vfieldAttributesChangedClass vfieldAttributesChangedClass;
typedef struct vfieldBooleanClass           vfieldBooleanClass;
typedef struct vfieldClass		    vfieldClass;
typedef struct vfieldDateClass              vfieldDateClass;
typedef struct vfieldDoubleClass            vfieldDoubleClass;
typedef struct vfieldLongClass              vfieldLongClass;
typedef struct vfieldStringClass            vfieldStringClass;
typedef struct vfieldUnsignedLongClass      vfieldUnsignedLongClass;

typedef struct vfieldBooleanInterface       vfieldBooleanInterface;
typedef struct vfieldDateInterface          vfieldDateInterface;
typedef struct vfieldDoubleInterface        vfieldDoubleInterface;
typedef struct vfieldLongInterface          vfieldLongInterface;
typedef struct vfieldScribeInterface        vfieldScribeInterface;
typedef struct vfieldUnsignedLongInterface  vfieldUnsignedLongInterface;

typedef vbool (*vfieldValidationProc)(vfield *field);

typedef struct vfieldConversionException     vfieldConversionException;
typedef struct vfieldMaximumException        vfieldMaximumException;
typedef struct vfieldMinimumException        vfieldMinimumException;
typedef struct vfieldNullNotAllowedException vfieldNullNotAllowedException;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * field classes
 */

vfieldClass *vfieldGetDefaultClass (
  void
);

vfieldBooleanClass *vfieldGetDefaultBooleanClass (
  void
);

vfieldDateClass *vfieldGetDefaultDateClass (
  void
);

vfieldDoubleClass *vfieldGetDefaultDoubleClass (
  void
);

vfieldLongClass *vfieldGetDefaultLongClass (
  void
);

vfieldStringClass *vfieldGetDefaultStringClass (
  void
);

vfieldUnsignedLongClass *vfieldGetDefaultUnsignedLongClass (
  void
);

/*
 * field
 */

void vfieldAnnounce (
  vfield                        *field,
  voccurrence                   *occurrence
);

void vfieldAnnounceAttributeChanged (
  vfield                        *field,
  const vname			*attr
);

void vfieldAnnounceAttributesChanged (
  vfield                        *field,
  vfieldAttributesChanged       *occurrence
);

vfield *vfieldClone (
  vfield                        *field
);

void vfieldCopy (
  vfield                        *field,
  vfield                        *target
);

void vfieldCopyInit (
  vfield                        *field,
  vfield                        *target
);

vfield *vfieldCreate (
  void
);

vfield *vfieldCreateBoolean (
  void
);

vfield *vfieldCreateDate (
  void
);

vfield *vfieldCreateDouble (
  void
);

vfield *vfieldCreateLong (
  void
);

vfield *vfieldCreateOfClass (
  vfieldClass                   *clas
);

vfield *vfieldCreateString (
  void
);

vfield *vfieldCreateUnsignedLong (
  void
);

void vfieldDestroy (
  vfield                        *field
);

void vfieldDestroyLater (
  vfield                        *field
);

void vfieldDump (
  vfield                        *field,
  FILE                          *stream
);

vbool vfieldGetBoolean (
  vfield                        *field
);

vfieldBooleanInterface *vfieldGetBooleanInterface (
  vfield                        *field
);

vfieldClass *vfieldGetClass (
  vfield                        *field
);

vdate *vfieldGetDate (
  vfield                        *field
);

vfieldDateInterface *vfieldGetDateInterface (
  vfield                        *field
);

vdate *vfieldGetDateMax (
  vfield                        *field
);

vdate *vfieldGetDateMin (
  vfield                        *field
);

double vfieldGetDouble (
  vfield                        *field
);

vfieldDoubleInterface *vfieldGetDoubleInterface (
  vfield                        *field
);

double vfieldGetDoubleMax (
  vfield                        *field
);

double vfieldGetDoubleMin (
  vfield                        *field
);

const vchar *vfieldGetErrorMessage (
  vfield                        *field
);

vformat *vfieldGetFormat (
  vfield                        *field
);

const void *vfieldGetIDAttribute (
  vfield                        *field,
  int                            id
);

long vfieldGetLong (
  vfield                        *field
);

vfieldLongInterface *vfieldGetLongInterface (
  vfield                        *field
);

long vfieldGetLongMax (
  vfield                        *field
);

long vfieldGetLongMin (
  vfield                        *field
);

vobject *vfieldGetObject (
  vfield                        *field
);

vobservable *vfieldGetObservable (
  vfield                        *field
);

vscribe *vfieldGetScribe (
  vfield                        *field
);

vfieldScribeInterface *vfieldGetScribeInterface (
  vfield                        *field
);

const vname *vfieldGetTag (
  vfield                        *field
);

const vchar *vfieldGetTitle (
  vfield                        *field
);

unsigned long vfieldGetUnsignedLong (
  vfield                        *field
);

vfieldUnsignedLongInterface *vfieldGetUnsignedLongInterface (
  vfield                        *field
);

unsigned long vfieldGetUnsignedLongMax (
  vfield                        *field
);

unsigned long vfieldGetUnsignedLongMin (
  vfield                        *field
);

vfieldValidationProc vfieldGetValidationProc (
  vfield                        *field
);

void vfieldInit (
  vfield                        *field
);

void vfieldInitOfClass (
  vfield                        *field,
  vfieldClass                   *clas
);

void vfieldInstallObserver (
  vfield			*field,
  vobservable			*observer
);

vbool vfieldIsFormatOwned (
  vfield                       *field
);

vbool vfieldIsLocked (
  vfield                       *field
);

vbool vfieldIsNull (
  vfield                       *field
);

vbool vfieldIsNullAllowed (
  vfield                       *field
);

vbool vfieldIsValid (
  vfield                       *field
);

vfield *vfieldLoad (
  vresource                     resource
);

void vfieldLoadInit (
  vfield                        *field,
  vresource                      resource
);

void vfieldLock (
  vfield                        *field
);

void vfieldSetBoolean (
  vfield                        *field,
  vbool                          b
);

void vfieldSetIDAttribute (
  vfield                        *field,
  int                            id,
  const void                    *attribute
);

void vfieldSetDate (
  vfield                        *field,
  vdate                         *date
);

void vfieldSetDateMax (
  vfield                        *field,
  vdate                         *date
);

void vfieldSetDateMin (
  vfield                        *field,
  vdate                         *date
);

void vfieldSetDouble (
  vfield                        *field,
  double                         d
);

void vfieldSetDoubleMax (
  vfield                        *field,
  double                         d
);

void vfieldSetDoubleMin (
  vfield                        *field,
  double                         d
);

void vfieldSetErrorMessage (
  vfield                        *field,
  const vchar                   *message
);

void vfieldSetErrorMessageScribed (
  vfield                        *field,
  vscribe                       *scribe
);

void vfieldSetFormat (
  vfield                        *field,
  vformat                       *format
);

void vfieldSetFormatOwned (
  vfield                        *field,
  vformat                       *format
);

void vfieldSetLong (
  vfield                        *field,
  long                           l
);

void vfieldSetLongMax (
  vfield                        *field,
  long                           l
);

void vfieldSetLongMin (
  vfield                        *field,
  long                           l
);

void vfieldSetNull (
  vfield                        *field,
  vbool                          onOff
);

void vfieldSetNullAllowed (
  vfield                        *field,
  vbool                          onOff
);

void vfieldSetScribed (
  vfield                        *field,
  vscribe                       *s
);

void vfieldSetString (
  vfield                        *field,
  const vchar                   *s
);

void vfieldSetTag (
  vfield                        *field,
  const vname                   *tag
);

void vfieldSetTitle (
  vfield                        *field,
  const vchar                   *title
);

void vfieldSetTitleScribed (
  vfield                        *field,
  vscribe                       *title
);

void vfieldSetUnsignedLong (
  vfield                        *field,
  unsigned long                  u
);

void vfieldSetUnsignedLongMax (
  vfield                        *field,
  unsigned long                  u
);

void vfieldSetUnsignedLongMin (
  vfield                        *field,
  unsigned long                  u
);

void vfieldSetValidationProc (
  vfield                        *field,
  vfieldValidationProc           validator
);

void vfieldStartup (
  void
);

void vfieldStore (
  vfield                        *field,
  vresource                      resource
);

void vfieldUninstallObserver (
  vfield			*field,
  vobservable			*observer
);

void vfieldUnlock (
  vfield                        *field
);


/*
 *  Abstract interface (mixin) classes
 */

vfieldBooleanInterface *vfieldGetDefaultBooleanInterface (
  void
);

vfieldDateInterface *vfieldGetDefaultDateInterface (
  void
);

vfieldDoubleInterface *vfieldGetDefaultDoubleInterface (
  void
);

vfieldLongInterface *vfieldGetDefaultLongInterface (
  void
);

vfieldScribeInterface *vfieldGetDefaultScribeInterface (
  void
);

vfieldUnsignedLongInterface *vfieldGetDefaultUnsignedLongInterface (
  void
);


/*
 *  vfieldBoolean
 */

vfieldBooleanClass *vfieldGetBooleanClass (
  vfieldBoolean                 *field
);

vfield *vfieldGetBooleanField (
  vfieldBoolean                 *field
);

void vfieldBooleanStartup (
  void
);


/*
 *  vfieldDate
 */

vfieldDateClass *vfieldGetDateClass (
  vfieldDate                    *field
);

vfield *vfieldGetDateField (
  vfieldDate                    *field
);

void vfieldDateStartup (
  void
);


/*
 *  vfieldDouble
 */

vfieldDoubleClass *vfieldGetDoubleClass (
  vfieldDouble                  *field
);

vfield *vfieldGetDoubleField (
  vfieldDouble                  *field
);


void vfieldDoubleStartup (
  void
);


/*
 *  vfieldLong
 */

vfieldLongClass *vfieldGetLongClass (
  vfieldLong                    *field
);

vfield *vfieldGetLongField (
  vfieldLong                    *field
);

void vfieldLongStartup (
  void
);


/*
 *  vfieldString
 */

vfieldStringClass *vfieldGetStringClass (
  vfieldString                   *field
);

vfield *vfieldGetStringField (
  vfieldString                   *field
);

void vfieldStringStartup (
  void
);


/*
 *  vfieldUnsignedLong
 */

vfieldUnsignedLongClass *vfieldGetUnsignedLongClass (
  vfieldUnsignedLong                    *field
);

vfield *vfieldGetUnsignedLongField (
  vfieldUnsignedLong                    *field
);

void vfieldUnsignedLongStartup (
  void
);


/*
 * Occurrence Class
 */

vfieldAttributesChangedClass *vfieldGetDefaultAttributesChangedClass (
  void
);


/*
 * Occurrence
 */

void vfieldAddAttributesChanged (
  vfieldAttributesChanged          *occurrence,
  const vname                      *attribute
);

vfieldAttributesChanged *vfieldCreateAttributesChanged (
  void
);

void vfieldDestroyAttributesChanged (
  vfieldAttributesChanged          *occurrence
);

vfieldAttributesChangedClass *vfieldGetAttributesChangedClass (
  vfieldAttributesChanged          *occurrence
);

voccurrence *vfieldGetAttributesChangedOccurrence (
  vfieldAttributesChanged          *occurrence
);

vbool vfieldHasAttributesChanged (
  vfieldAttributesChanged          *occurrence,
  const vname                      *attribute
);

void vfieldRemoveAttributesChanged (
  vfieldAttributesChanged          *occurrence,
  const vname                      *attribute
);

/*
 * Exceptions
 */

vfieldConversionException *vfieldGetConversionException (
  void
);

vfieldMaximumException *vfieldGetMaximumException (
  void
);

vfieldMinimumException *vfieldGetMinimumException (
  void
);

vfieldNullNotAllowedException *vfieldGetNullNotAllowedException (
  void
);


/*
 * Exception Classes
 */

const vexClass *vfieldGetConversionExceptionClass (
  void
);

const vexClass *vfieldGetMaximumExceptionClass (
  void
);

const vexClass *vfieldGetMinimumExceptionClass (
  void
);

const vexClass *vfieldGetNullNotAllowedExceptionClass (
  void
);


/*
 * * * * * * * * * * PRIVATE CONSTANTS * * * * * * * * * *
 */

enum {
  _vfield_BooleanInterface,
  _vfield_DateInterface,
  _vfield_DoubleInterface,
  _vfield_LongInterface,
  _vfield_ScribeInterface,
  _vfield_UnsignedLongInterface,

  _vfield_ErrorMessage,
  _vfield_Format,
  _vfield_Maximum,
  _vfield_Minimum,
  _vfield_Null,
  _vfield_NullAllowed,
  _vfield_Title,
  _vfield_Value,
  _vfieldNUM_NAMES
};

enum {
  _vfieldFORMAT_OWNED
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * boolean mixin
 */

#define vfieldBooleanINTERFACE(SUPER,FIELD)                                 \
  vinterfaceROOT (SUPER);                                                   \
  vinterfaceMETHOD_RET (vfieldGET_BOOLEAN, vbool, (FIELD *));               \
  vinterfaceMETHOD (vfieldSET_BOOLEAN, (FIELD *, vbool))

struct vfieldBooleanInterface {
  vfieldBooleanINTERFACE (vfieldBooleanInterface, vfield);
};


/*
 * date mixin
 */

#define vfieldDateINTERFACE(SUPER,FIELD)                                   \
  vinterfaceROOT (SUPER);                                                  \
  vinterfaceMETHOD_RET (vfieldGET_DATE, vdate *, (FIELD *));               \
  vinterfaceMETHOD_RET (vfieldGET_DATE_MAX, vdate *, (FIELD *));           \
  vinterfaceMETHOD_RET (vfieldGET_DATE_MIN, vdate *, (FIELD *));           \
  vinterfaceMETHOD (vfieldSET_DATE, (FIELD *, vdate *));                   \
  vinterfaceMETHOD (vfieldSET_DATE_MAX, (FIELD *, vdate *));               \
  vinterfaceMETHOD (vfieldSET_DATE_MIN, (FIELD *, vdate *))

struct vfieldDateInterface {
  vfieldDateINTERFACE (vfieldDateInterface, vfield);
};


/*
 * double mixin
 */

#define vfieldDoubleINTERFACE(SUPER,FIELD)                                 \
  vinterfaceROOT (SUPER);                                                  \
  vinterfaceMETHOD_RET (vfieldGET_DOUBLE, double, (FIELD *));              \
  vinterfaceMETHOD_RET (vfieldGET_DOUBLE_MAX, double, (FIELD *));          \
  vinterfaceMETHOD_RET (vfieldGET_DOUBLE_MIN, double, (FIELD *));          \
  vinterfaceMETHOD (vfieldSET_DOUBLE, (FIELD *, double));                  \
  vinterfaceMETHOD (vfieldSET_DOUBLE_MAX, (FIELD *, double));              \
  vinterfaceMETHOD (vfieldSET_DOUBLE_MIN, (FIELD *, double))

struct vfieldDoubleInterface {
  vfieldDoubleINTERFACE (vfieldDoubleInterface, vfield);
};


/*
 * long mixin
 */

#define vfieldLongINTERFACE(SUPER,FIELD)                                    \
  vinterfaceROOT (SUPER);                                                   \
  vinterfaceMETHOD_RET (vfieldGET_LONG, long, (FIELD *));                   \
  vinterfaceMETHOD_RET (vfieldGET_LONG_MAX, long, (FIELD *));               \
  vinterfaceMETHOD_RET (vfieldGET_LONG_MIN, long, (FIELD *));               \
  vinterfaceMETHOD (vfieldSET_LONG, (FIELD *, long));                       \
  vinterfaceMETHOD (vfieldSET_LONG_MAX, (FIELD *, long));                   \
  vinterfaceMETHOD (vfieldSET_LONG_MIN, (FIELD *, long))

struct vfieldLongInterface {
  vfieldLongINTERFACE (vfieldLongInterface, vfield);
};


/*
 * scribe mixin
 */

#define vfieldScribeINTERFACE(SUPER,FIELD)                                  \
  vinterfaceROOT (SUPER);                                                   \
  vinterfaceMETHOD_RET (vfieldGET_SCRIBE, vscribe *, (FIELD *));            \
  vinterfaceMETHOD (vfieldSET_SCRIBED, (FIELD *, vscribe *))

struct vfieldScribeInterface {
  vfieldScribeINTERFACE (vfieldScribeInterface, vfield);
};


/*
 * unsigned long mixin
 */

#define vfieldUnsignedLongINTERFACE(SUPER,FIELD)                           \
  vinterfaceROOT (SUPER);                                                  \
  vinterfaceMETHOD_RET (vfieldGET_UNSIGNED_LONG, unsigned long, (FIELD *));\
  vinterfaceMETHOD_RET (vfieldGET_UNSIGNED_LONG_MAX, unsigned long,        \
		    (FIELD *));                                            \
  vinterfaceMETHOD_RET (vfieldGET_UNSIGNED_LONG_MIN, unsigned long,        \
		    (FIELD *));                                            \
  vinterfaceMETHOD (vfieldSET_UNSIGNED_LONG, (FIELD *, unsigned long));    \
  vinterfaceMETHOD (vfieldSET_UNSIGNED_LONG_MAX, (FIELD *, unsigned long));\
  vinterfaceMETHOD (vfieldSET_UNSIGNED_LONG_MIN, (FIELD *, unsigned long))

struct vfieldUnsignedLongInterface {
  vfieldUnsignedLongINTERFACE (vfieldUnsignedLongInterface, vfield);
};


/*
 * field
 */

struct vfield {
  vobject                  object;
  vfieldValidationProc     validationProc;
  vstr                    *title;
  vstr                    *errorMessage;
  vbool                    null;
  vbool                    nullAllowed;
  int                      lockCount;
  vfieldAttributesChanged *occurrence;
  unsigned int             flags;
  vformat                 *format;
};

#define vfieldCLASS(SUPER, FIELD)                                           \
  vobjectCLASS (SUPER, FIELD);                                              \
  vclassMETHOD_RET (vfieldIS_VALID, vbool, (FIELD *));                      \
  vclassMETHOD     (vfieldLOCK, (FIELD *));                                 \
  vclassMETHOD     (vfieldSET_ERROR_MESSAGE_SCRIBED, (FIELD *, vscribe *)); \
  vclassMETHOD     (vfieldSET_FORMAT_OWNED, (FIELD *, vformat *));          \
  vclassMETHOD     (vfieldSET_NULL, (FIELD *, vbool));                      \
  vclassMETHOD     (vfieldSET_NULL_ALLOWED, (FIELD *, vbool));              \
  vclassMETHOD     (vfieldSET_TITLE_SCRIBED, (FIELD *, vscribe *));         \
  vclassMETHOD     (vfieldSET_VALIDATION_PROC,                              \
		    (FIELD *, vfieldValidationProc));                       \
  vclassMETHOD     (vfieldUNLOCK, (FIELD *))

struct vfieldClass {
  vfieldCLASS (vfieldClass, vfield);
};


/*
 * boolean field
 */

struct vfieldBoolean {
  vfield             field;
  vbool              value;
};

#define vfieldBooleanCLASS(SUPER, FIELD)                                  \
  vfieldCLASS  (SUPER, FIELD)


struct vfieldBooleanClass {
  vfieldBooleanCLASS (vfieldBooleanClass, vfieldBoolean);
};


/*
 * date field
 */

struct vfieldDate {
  vfield             field;
  vdate             *value;
  vdate             *min;
  vdate             *max;
};

#define vfieldDateCLASS(SUPER, FIELD)                                  \
  vfieldCLASS  (SUPER, FIELD)


struct vfieldDateClass {
  vfieldDateCLASS (vfieldDateClass, vfieldDate);
};


/*
 * double field
 */

struct vfieldDouble {
  vfield             field;
  double             value;
  double             min;
  double             max;
};

#define vfieldDoubleCLASS(SUPER, FIELD)                                  \
  vfieldCLASS  (SUPER, FIELD)


struct vfieldDoubleClass {
  vfieldDoubleCLASS (vfieldDoubleClass, vfieldDouble);
};


/*
 * long field
 */

struct vfieldLong {
  vfield             field;
  long               value;
  long               min;
  long               max;
};

#define vfieldLongCLASS(SUPER, FIELD)                                  \
  vfieldCLASS  (SUPER, FIELD)


struct vfieldLongClass {
  vfieldLongCLASS (vfieldLongClass, vfieldLong);
};


/*
 * string field
 */

struct vfieldString {
  vfield             field;
  vstr              *value;
};

struct vfieldStringClass {
  vfieldCLASS (vfieldStringClass, vfieldString);
};


/*
 * unsigned long field
 */

struct vfieldUnsignedLong {
  vfield             field;
  unsigned long      value;
  unsigned long      min;
  unsigned long      max;
};

#define vfieldUnsignedLongCLASS(SUPER, FIELD)                          \
  vfieldCLASS  (SUPER, FIELD)


struct vfieldUnsignedLongClass {
  vfieldUnsignedLongCLASS (vfieldUnsignedLongClass, vfieldUnsignedLong);
};


/*
 * Attributes Changed Occurrence
 */

struct vfieldAttributesChanged {
    voccurrence			 occurrence;
    vdict                       *dict;
};

#define vfieldATTRIBUTES_CHANGED_CLASS(SUPER, OCCURRENCE)                \
    voccurrenceCLASS (SUPER, OCCURRENCE);			         \
    vclassMETHOD (vfieldADD_ATTRIBUTES_CHANGED,				 \
		  (OCCURRENCE *occurrence, const vname *attributeName)); \
    vclassMETHOD_RET (vfieldHAS_ATTRIBUTES_CHANGED, vbool,               \
		      (OCCURRENCE *occurrence, const vname *attribute)); \
    vclassMETHOD (vfieldREMOVE_ATTRIBUTES_CHANGED,		         \
		 (OCCURRENCE *occurrence, const vname *attributeName))

struct vfieldAttributesChangedClass {
    vfieldATTRIBUTES_CHANGED_CLASS(vfieldAttributesChangedClass,
				   vfieldAttributesChanged);
};


/*
 * Exceptions
 */

struct vfieldConversionException {
  vexException     parent;
};

struct vfieldMaximumException {
  vexException     parent;
};

struct vfieldMinimumException {
  vexException     parent;
};

struct vfieldNullNotAllowedException {
  vexException     parent;
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vname *_vfieldPredefs[];

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vfieldValidate (
  vfield                *field
);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * vfield
 */

#define vfieldGetObject(f) \
  vportBASE_OBJECT(f, object)

#define vfieldGetObservable(f) \
  vobjectGetObservable(vfieldGetObject(f))

#define vfieldGetClass(f) \
  ((vfieldClass*)vobjectGetClass (vfieldGetObject (f)))

#define vfieldAnnounce(f,o) \
  vobjectAnnounce (vfieldGetObject (f), o)

#define vfieldAnnounceAttributesChanged(f,o) \
  vfieldAnnounce (f, vfieldGetAttributesChangedOccurrence (o))

#define vfieldClone(f) \
  ((vfield *) vobjectClone (vfieldGetObject (f)))

#define vfieldCopy(f,t) \
  vobjectCopy (vfieldGetObject (f), vfieldGetObject (t))

#define vfieldCopyInit(f,t) \
  vobjectCopyInit (vfieldGetObject (f), vfieldGetObject (t))

#define vfieldCreate() \
  vfieldCreateOfClass (vfieldGetDefaultClass ())

#define vfieldCreateBoolean() \
  vfieldCreateOfClass (vfieldGetDefaultBooleanClass ())

#define vfieldCreateDate() \
  vfieldCreateOfClass (vfieldGetDefaultDateClass ())

#define vfieldCreateDouble() \
  vfieldCreateOfClass (vfieldGetDefaultDoubleClass ())

#define vfieldCreateLong() \
  vfieldCreateOfClass (vfieldGetDefaultLongClass ())

#define vfieldCreateOfClass(c) \
  ((vfield *) vobjectCreateOfClass((vobjectClass *)(c)))

#define vfieldCreateString() \
  vfieldCreateOfClass (vfieldGetDefaultStringClass ())

#define vfieldCreateUnsignedLong() \
  vfieldCreateOfClass (vfieldGetDefaultUnsignedLongClass ())

#define vfieldGetTitle(f) \
  ((f)->title)

#define vfieldDestroy(f) \
  vobjectDestroy (vfieldGetObject (f))

#define vfieldDestroyLater(f) \
  vobjectDestroyLater (vfieldGetObject (f))

#define vfieldDump(o,f) \
  vobjectDump (vfieldGetObject (o), (f))

#define vfieldGetBooleanInterface(f) \
  ((vfieldBooleanInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_BooleanInterface))

#define vfieldGetDateInterface(f) \
  ((vfieldDateInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_DateInterface))

#define vfieldGetDoubleInterface(f) \
  ((vfieldDoubleInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_DoubleInterface))

#define vfieldGetErrorMessage(f) \
  ((f)->errorMessage)

#define vfieldGetFormat(f) \
  ((f)->format)

#define vfieldGetIDAttribute(f,i) \
  vobjectGetIDAttribute (vfieldGetObject (f), (i))

#define vfieldGetLongInterface(f) \
  ((vfieldLongInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_LongInterface))

#define vfieldGetScribeInterface(f) \
  ((vfieldScribeInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_ScribeInterface))

#define vfieldGetTag(f) \
  vobjectGetTag (vfieldGetObject (f))

#define vfieldGetUnsignedLongInterface(f) \
  ((vfieldUnsignedLongInterface *) vclassBindToInterfaceName (vfieldGetClass (f), vfield_UnsignedLongInterface))

#define vfieldGetValidationProc(f) \
  ((f)->validationProc)

#define vfieldInit(f) \
  vfieldInitOfClass (f, vfieldGetDefaultClass ())

#define vfieldInitOfClass(f,c) \
  vobjectInitOfClass(vfieldGetObject (f), (vfieldClass *)(c))

#define vfieldInstallObserver(f,b) \
  vobjectInstallObserver (vfieldGetObject (f), (b))

#define vfieldIsFormatOwned(f) \
  ((vbool) ((f)->flags & _vfieldFORMAT_OWNED))

#define vfieldIsLocked(f) \
  ((f)->lockCount != 0)

#define vfieldIsNull(f) \
  ((f)->null)

#define vfieldIsNullAllowed(f) \
  ((f)->nullAllowed)

#define vfieldLoad(r) \
  ((vfield *) vobjectLoad (r))

#define vfieldLoadInit(f,r) \
  vobjectLoadInit (vfieldGetObject (f), (r))

#define vfieldSetIDAttribute(f,i,a) \
  vobjectSetIDAttribute (vfieldGetObject (f), (i), (a))

#define vfieldSetTag(f,t) \
  vobjectSetTag (vfieldGetObject (f), (t))

#define vfieldStore(f,r) \
  vobjectStore (vfieldGetObject (f), (r))

#define vfieldUninstallObserver(f,b) \
    vobjectUninstallObserver (vfieldGetObject (f), (b))

#if !vdebugDEBUG
#define _vfieldValidate(f)
#endif

/*
 * vfieldBoolean
 */

#define vfieldGetBooleanClass(f) \
  ((vfieldBooleanClass*)vfieldGetClass (vfieldGetBooleanField (f)))

#define vfieldGetBooleanField(f) \
  vportBASE_OBJECT ((f), field)

/*
 * vfieldDate
 */

#define vfieldGetDateClass(f) \
  ((vfieldDateClass*)vfieldGetClass (vfieldGetDateField (f)))

#define vfieldGetDateField(f) \
  vportBASE_OBJECT ((f), field)

/*
 * vfieldDouble
 */

#define vfieldGetDoubleClass(f) \
  ((vfieldDoubleClass*)vfieldGetClass (vfieldGetDoubleField (f)))

#define vfieldGetDoubleField(f) \
  vportBASE_OBJECT ((f), field)

/*
 * vfieldLong
 */

#define vfieldGetLongClass(f) \
  ((vfieldLongClass*)vfieldGetClass (vfieldGetLongField (f)))

#define vfieldGetLongField(f) \
  vportBASE_OBJECT ((f), field)


/*
 * vfieldString
 */

#define vfieldGetStringClass(f) \
  ((vfieldStringClass*)vfieldGetClass (vfieldGetStringField (f)))

#define vfieldGetStringField(f) \
  vportBASE_OBJECT ((f), field)


/*
 * vfieldUnsignedLong
 */

#define vfieldGetUnsignedLongClass(f) \
  ((vfieldUnsignedLongClass*)vfieldGetClass (vfieldGetUnsignedLongField (f)))

#define vfieldGetUnsignedLongField(f) \
  vportBASE_OBJECT ((f), field)


/*
 * vfieldAttributesChanged
 */

#define vfieldCreateAttributesChanged() \
  (vfieldAttributesChanged *) voccurrenceCreateOfClass (vfieldGetDefaultAttributesChangedClass ())

#define vfieldDestroyAttributesChanged(o) \
  voccurrenceDestroy (vfieldGetAttributesChangedOccurrence (o))

#define vfieldGetAttributesChangedClass(o) \
  ((vfieldAttributesChangedClass*)voccurrenceGetClass (vfieldGetAttributesChangedOccurrence (o)))

#define vfieldGetAttributesChangedOccurrence(o) \
  vportBASE_OBJECT ((o), occurrence)

/*
 * Exceptions
 */

#define vfieldGetConversionException() \
  ((vfieldConversionException *)       \
    vexGetExceptionOfClass (vfieldGetConversionExceptionClass ()))

#define vfieldGetMaximumException() \
  ((vfieldMaximumException *)       \
    vexGetExceptionOfClass (vfieldGetMaximumExceptionClass ()))

#define vfieldGetMinimumException() \
  ((vfieldMinimumException *)       \
    vexGetExceptionOfClass (vfieldGetMinimumExceptionClass ()))

#define vfieldGetNullNotAllowedException() \
  ((vfieldNullNotAllowedException *)       \
    vexGetExceptionOfClass (vfieldGetNullNotAllowedExceptionClass ()))

 
/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * vfield
 */

#define vfieldIsValid(f) \
  vclassSend (vfieldGetClass (f), vfieldIS_VALID, (f))

#define vfieldLock(f) \
  vclassSend (vfieldGetClass (f), vfieldLOCK, (f))

#define vfieldSetErrorMessageScribed(f,t) \
  vclassSend (vfieldGetClass (f), vfieldSET_ERROR_MESSAGE_SCRIBED, (f,t))

#define vfieldSetFormatOwned(f,fmt) \
  vclassSend (vfieldGetClass (f), vfieldSET_FORMAT_OWNED, (f, fmt))

#define vfieldSetNull(f,b) \
  vclassSend (vfieldGetClass (f), vfieldSET_NULL, (f,b))

#define vfieldSetNullAllowed(f,b) \
  vclassSend (vfieldGetClass (f), vfieldSET_NULL_ALLOWED, (f,b))

#define vfieldSetTitleScribed(f,t) \
  vclassSend (vfieldGetClass (f), vfieldSET_TITLE_SCRIBED, (f,t))

#define vfieldSetValidationProc(f,p) \
  vclassSend (vfieldGetClass (f), vfieldSET_VALIDATION_PROC, (f,p))

#define vfieldUnlock(f) \
  vclassSend (vfieldGetClass (f), vfieldUNLOCK, (f))

/*
 * vfieldAttributesChanged
 */

#define vfieldAddAttributesChanged(o,a) \
  vclassSend (vfieldGetAttributesChangedClass (o), \
	      vfieldADD_ATTRIBUTES_CHANGED, (o,a))

#define vfieldHasAttributesChanged(o,a) \
  vclassSend (vfieldGetAttributesChangedClass (o), \
	      vfieldHAS_ATTRIBUTES_CHANGED, (o,a))

#define vfieldRemoveAttributesChanged(o,a) \
  vclassSend (vfieldGetAttributesChangedClass (o), \
	      vfieldREMOVE_ATTRIBUTES_CHANGED, (o,a))

/*
 * vfield interfaces
 */

#define vfieldGetBoolean(f) \
  vinterfaceSend (vfieldGetBooleanInterface (f), vfieldGET_BOOLEAN, (f))

#define vfieldGetDate(f) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldGET_DATE, (f))

#define vfieldGetDateMax(f) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldGET_DATE_MAX, (f))

#define vfieldGetDateMin(f) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldGET_DATE_MIN, (f))

#define vfieldGetDouble(f) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldGET_DOUBLE, (f))

#define vfieldGetDoubleMax(f) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldGET_DOUBLE_MAX, (f))

#define vfieldGetDoubleMin(f) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldGET_DOUBLE_MIN, (f))

#define vfieldGetLong(f) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldGET_LONG, (f))

#define vfieldGetLongMax(f) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldGET_LONG_MAX, (f))

#define vfieldGetLongMin(f) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldGET_LONG_MIN, (f))

#define vfieldGetScribe(f) \
  vinterfaceSend (vfieldGetScribeInterface (f), vfieldGET_SCRIBE, (f))

#define vfieldGetUnsignedLong(f) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldGET_UNSIGNED_LONG, (f))

#define vfieldGetUnsignedLongMax(f) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldGET_UNSIGNED_LONG_MAX, (f))

#define vfieldGetUnsignedLongMin(f) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldGET_UNSIGNED_LONG_MIN, (f))

#define vfieldSetBoolean(f,d) \
  vinterfaceSend (vfieldGetBooleanInterface (f), vfieldSET_BOOLEAN, (f, d))

#define vfieldSetDate(f,d) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldSET_DATE, (f, d))

#define vfieldSetDateMax(f,d) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldSET_DATE_MAX, (f, d))

#define vfieldSetDateMin(f,d) \
  vinterfaceSend (vfieldGetDateInterface (f), vfieldSET_DATE_MIN, (f, d))

#define vfieldSetDouble(f,d) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldSET_DOUBLE, (f, d))

#define vfieldSetDoubleMax(f,d) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldSET_DOUBLE_MAX, (f, d))

#define vfieldSetDoubleMin(f,d) \
  vinterfaceSend (vfieldGetDoubleInterface (f), vfieldSET_DOUBLE_MIN, (f, d))

#define vfieldSetLong(f,l) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldSET_LONG, (f,l))

#define vfieldSetLongMax(f,l) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldSET_LONG_MAX, (f,l))

#define vfieldSetLongMin(f,l) \
  vinterfaceSend (vfieldGetLongInterface (f), vfieldSET_LONG_MIN, (f,l))

#define vfieldSetScribed(f,s) \
  vinterfaceSend (vfieldGetScribeInterface (f), vfieldSET_SCRIBED, (f,s))

#define vfieldSetUnsignedLong(f,l) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldSET_UNSIGNED_LONG, (f,l))

#define vfieldSetUnsignedLongMax(f,l) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldSET_UNSIGNED_LONG_MAX, (f,l))

#define vfieldSetUnsignedLongMin(f,l) \
  vinterfaceSend (vfieldGetUnsignedLongInterface (f), vfieldSET_UNSIGNED_LONG_MIN, (f,l))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vfieldINCLUDED */

