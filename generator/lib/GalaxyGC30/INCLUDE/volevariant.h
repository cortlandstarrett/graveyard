/* $Id: volevariant.h,v 1.14 1997/09/23 22:41:55 alex Exp $ */

/************************************************************

    volevariant.h

    C Interface for OLE variant and related objects object
	(c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef volevariantINCLUDED
#define volevariantINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vlonglongINCLUDED
#include vlonglongHEADER 
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef voleINCLUDED
#include voleHEADER 
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct volevariant            volevariant;
typedef struct volevariantClass       volevariantClass;
typedef struct volevariantList        volevariantList;
typedef struct volevariantListClass   volevariantListClass;
typedef struct voledispatch           voledispatch;
typedef struct voledispatchClass      voledispatchClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 *  voledispatch
 */
voledispatchClass *voledispatchGetDefaultClass(
    void
);

vinstance *voledispatchGetInstance(
    voledispatch *disp
);

voledispatch *voledispatchCreate(
    void
);

void *voledispatchDestroy(
    voledispatch *disp
);

int voledispatchInvoke(
    voledispatch    *disp,
    int              dispid,
    int              flags,
    volevariantList *variantList,
    volevariant     *variant
);

void voledispatchAttachInterface(
    voledispatch *disp,
	LPDISPATCH    pDispatch
);

LPDISPATCH voledispatchDetachInterface(
    voledispatch  *disp
);

LPDISPATCH voledispatchGetInterface(
    voledispatch *disp
);

vfont *voledispatchGetFont(
    voledispatch *disp
);

void voledispatchSetFont(
    voledispatch *disp,
	vfont        *font
);

/*
 * volevariant
 */

void volevariantStartup(
    void
);

volevariantClass *volevariantGetDefaultClass(
    void
);

vinstance *volevariantGetInstance(
    volevariant  *variant
);

vobject *volevariantGetObject(
    volevariant *variant
);

volevariant *volevariantCreate(
    void
);

volevariant *volevariantCreateOfClass(
    volevariantClass *clas
);

void volevariantDestroy(
    volevariant *variant
);

void volevariantInit(
    volevariant *variant
);

void volevariantInitOfClass(
    volevariant *variant,
    volevariantClass *clas
);

void volevariantCopyInit(
    volevariant *source,
    volevariant *target
);

void volevariantCopy(
    volevariant *source,
    volevariant *target
);

void volevariantClear(
    volevariant *variant
);

int volevariantGetType(
    volevariant *variant
);

void volevariantChangeType(
    volevariant *variant,
    short        vartype
);


/*
 * unsigned char  VT_UI1
 */
void  volevariantSetChar(
    volevariant   *variant,
    unsigned char val
);

unsigned char volevariantGetChar(
    volevariant *variant
);

void volevariantSetCharRefVal(
    volevariant  *variant,
    unsigned char val
);

void volevariantSetCharRef(
    volevariant   *variant,
    unsigned char *val);

unsigned char *volevariantGetCharRef(
    volevariant *variant
);


/*
 * short  VT_I2
 */
void  volevariantSetShort(
    volevariant *variant,
    short        val
);

short volevariantGetShort(
    volevariant *variant
);

void volevariantSetShortRefVal(
    volevariant  *variant,
    short         val
);

void volevariantSetShortRef(
    volevariant *variant,
    short       *val);

short *volevariantGetShortRef(
    volevariant *variant
);

/*
 *  int  VT_I4
 */
void volevariantSetInt(
    volevariant *variant,
    int val
); 

int  volevariantGetInt(
    volevariant *variant
);

void volevariantSetIntRefVal(
    volevariant  *variant,
    int           val
);

void volevariantSetIntRef(
    volevariant *variant,
    int         *pval
);

int *volevariantGetIntRef(
    volevariant *variant
);

/*
 *  float  VT_R4
 */
void volevariantSetFloat(
    volevariant *variant,
    float val
);

float volevariantGetFloat(
    volevariant *variant
);

void volevariantSetFloatRefVal(
    volevariant  *variant,
    float         val
);

void volevariantSetFloatRef(
    volevariant *variant,
    float *pval
);

float *volevariantGetFloatRef(
    volevariant *variant
);

/*
 * double VT_R8
 */
void volevariantSetDouble(
    volevariant  *variant,
    double        val
);

double volevariantGetDouble(
    volevariant  *variant
);

void volevariantSetDoubleRefVal(
    volevariant  *variant,
    double        val
);

void volevariantSetDoubleRef(
    volevariant  *variant,
    double       *pval
);

double *volevariantGetDoubleRef(
    volevariant  *variant
);

/*
 * vbool VT_BOOL
 */
void volevariantSetBool(
    volevariant  *variant,
    vbool         val
);

vbool volevariantGetBool(
    volevariant  *variant
);

void volevariantSetBoolRefVal(
    volevariant  *variant,
    vbool         val
);

void volevariantSetBoolRef(
    volevariant  *variant,
    short        *pval
);

short *volevariantGetBoolRef(
    volevariant  *variant
);

/*
 *  SCODE (int)  VT_ERROR
 */
void volevariantSetError(
    volevariant *variant,
    int val
); 

int  volevariantGetError(
    volevariant *variant
);

void volevariantSetErrorRefVal(
    volevariant  *variant,
    int           val
);

void volevariantSetErrorRef(
    volevariant *variant,
    int         *pval
);

int *volevariantGetErrorRef(
    volevariant *variant
);


/*
 * DATE (double) VT_DATE
 */
void volevariantSetDate(
    volevariant  *variant,
    double        val
);

double volevariantGetDate(
    volevariant  *variant
);

void volevariantSetDateRefVal(
    volevariant  *variant,
    double        val
);

void volevariantSetDateRef(
    volevariant  *variant,
    double       *pval
);

double *volevariantGetDateRef(
    volevariant  *variant
);


/*
 * CY Currency(vlonglong) VT_CY
 */
void volevariantSetCurrency(
    volevariant  *variant,
    vlonglong     val
);

vlonglong volevariantGetCurrency(
    volevariant  *variant
);

void volevariantSetCurrencyRefVal(
    volevariant  *variant,
    vlonglong     val
);

void volevariantSetCurrencyRef(
    volevariant  *variant,
    CY           *pval
);

CY *volevariantGetCurrencyRef(
    volevariant  *variant
);



/*
 * vstr   VT_BSTR
 */
void volevariantSetString(
    volevariant  *variant,
    vchar        *str
);

vstr *volevariantGetString(
    volevariant  *variant
);

void volevariantSetStringRefVal(
    volevariant  *variant,
    vchar        *str
);

void volevariantSetStringRef(
    volevariant  *variant,
    BSTR         *pbstr
);

BSTR *volevariantGetStringRef(
    volevariant  *variant
);

/*
 * volevariant   VT_VARIANT|VT_BYREF
 */
void volevariantSetVariant(
    volevariant  *variant,
    volevariant  *v
);

volevariant *volevariantGetVariant(
    volevariant  *variant
);


/*
 *  IUnknown    VT_UNKNOWN
 */
void volevariantSetUnknown(
    volevariant *variant,
    LPUNKNOWN    pUnknown
);

LPUNKNOWN volevariantGetUnknown(
    volevariant *variant
);

void volevariantSetUnknownRefVal(
    volevariant *variant,
    LPUNKNOWN    pUnknown
);

void volevariantSetUnknownRef(
    volevariant  *variant,
    LPUNKNOWN    *ppUnknown
);

LPUNKNOWN *volevariantGetUnknownRef(
    volevariant  *variant
);

/*
 * void*   VT_VOID|VT_BYREF  always by reference
 */
void volevariantSetVoid(
    volevariant *variant,
    void        *p
);

void *volevariantGetVoid(
    volevariant *variant
);


/* 
 * voledispatch   VT_DISPATCH
 */
void volevariantSetDispatch(
    volevariant  *variant,
    voledispatch *disp);

voledispatch *volevariantGetDispatch(
    volevariant  *variant
);

void volevariantSetDispatchRefVal(
    volevariant *variant,
    voledispatch *disp
);

void volevariantSetDispatchRef(
    volevariant *variant,
    LPDISPATCH *pDispatch
);

LPDISPATCH  *volevariantGetDispatchRef(
    volevariant *variant
);


/*
 *  SAFEARRAY    | VT_ARRAY
 */
void volevariantSetSafeArray(
    volevariant *variant,
    SAFEARRAY   *pSafeArray,
    int          elemType
);

SAFEARRAY *volevariantGetSafeArray(
    volevariant *variant,
    int         *elemType
);

void volevariantSetSafeArrayRef(
    volevariant  *variant,
    SAFEARRAY    **ppSafeArray,
    int          elemType);

SAFEARRAY **volevariantGetSafeArrayRef(
    volevariant  *variant,
    int          *elemType
);


/*
 *  variant list
 */
volevariantListClass *volevariantGetDefaultListClass(
    void
);

vobjectList *volevariantGetListObjectList(
    volevariantList *variantList
);

volevariantList *volevariantCreateList(
void
);

void volevariantDestroyList(
    volevariantList *list
); 

void volevariantAppendList(
    volevariantList *variantList,
	volevariant     *variant
);

void volevariantDeleteListIndex(
    volevariantList *variantList,
    int              index
);

int volevariantGetListIndex(
    volevariantList *variantList,
    volevariant     *variant
);

volevariant *volevariantGetListAt(
    volevariantList *variantList,
    int              index
);

void *volevariantSetListAt(
    volevariantList *variantList,
    int              index,
    volevariant     *variant
);

int volevariantGetListCount(
    volevariantList *variantList
);

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


struct volevariant  {
    vobject          object;  
#if vportOLE     
    VARIANT          variant;      
    VARIANT          data;
#else
    void            *variant;
#endif    
};


#define volevariantCLASS(SUPER, OBJECT)                         \
    vobjectCLASS(SUPER, OBJECT)                                
   
struct volevariantClass {
    volevariantCLASS(volevariantClass, volevariant);
};


struct volevariantList {
    vobjectList      list;
};

#define volevariantLIST_CLASS(SUPER, LIST, OBJECT)    \
     vobjectLIST_CLASS(SUPER, LIST, OBJECT)
 
struct volevariantListClass{
    volevariantLIST_CLASS(volevariantListClass, volevariantList, volevariant);
};


struct voledispatch  {
    vinstance        instance;
    LPDISPATCH       pDispatch;      
};

#define voledispatchCLASS(SUPER, OBJECT)              \
    vinstanceCLASS(SUPER, OBJECT);                     
 
struct voledispatchClass {
    voledispatchCLASS(voledispatchClass, voledispatch)
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */
#if (vportOLE)
VARIANT *_volevariantGetVARIANT(volevariant *variant);

VARIANT  _volevariantDetach(volevariant *variant);
void _volevariantAttach(volevariant *variant, VARIANT *v);

voleResult _vdispatchInvokeHelper(LPDISPATCH pDispatch, DISPID dispid,
	unsigned short flags,
	volevariantList *variantList, volevariant *variant);
#endif


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */


#define volevariantGetObject(v)       vportBASE_OBJECT(v, object)
#define volevariantGetInstance(v)     vobjectGetInstance(volevariantGetObject(v))

#define volevariantCreateOfClass(c) \
    ((volevariant*)vinstanceCreateOfClass((vinstanceClass *)(c)))
#define volevariantCreate() \
    volevariantCreateOfClass(volevariantGetDefaultClass())

#define volevariantInitOfClass(v, c) \
    vintsnaceInitItemOfClass(volevariantGetInstance(v), (vinstanceClass*)(c))
#define volevariantInit(v) \
    volevariantInitOfClass(v, volevariantGetDefaultClass())

#define volevariantDestroy(v)  vinstanceDestroy(volevariantGetInstance(v))
#define volevariantCopy(s,d)   \
    vobjectCopy(volevariantGetObject(s), volevariantGetObject(d))
#define volevariantCopyInit(s,d)   \
    vobjectCopyInit(volevariantGetObject(s), volevariantGetObject(d))

#define volevariantGetClass(v) \
    ((volevariantClass*)vinstanceGetClass(volevariantGetInstance(v)))


#define voledispatchGetInstance(d)   vportBASE_OBJECT(d, instance)
#define voledispatchCreate()  \
   ((voledispatch *)vinstanceCreateOfClass((vinstanceClass *)voledispatchGetDefaultClass()))
#define voledispatchDestroy(d)       vinstanceDestroy(voledispatchGetInstance(d))

/*
 * volevariantList
 */
#define volevariantGetListObjectList(l)    vportBASE_OBJECT(l, list)
#define volevariantCreateList()   \
    ((volevariantList *)vobjectCreateListOfClass((vobjectListClass *)volevariantGetDefaultListClass()))
#define volevariantDestroyList(l)  vobjectDestroyList(volevariantGetListObjectList(l)) 

#define volevariantAppendList(l, v)   \
    vobjectAppendList(volevariantGetListObjectList(l), volevariantGetObject(v)) 

#define volevariantDeleteListIndex(l, i)   \
    vobjectDeleteListIndex(volevariantGetListObjectList(l), i) 

#define volevariantGetListIndex(l, v)  \
    vobjectGetListIndex(volevariantGetListObjectList(l), volevariantGetObject(v))

#define volevariantGetListAt(l, i)    \
    ((volevariant *)vobjectGetListAt(volevariantGetListObjectList(l), i))

#define volevariantSetListAt(l, i, v)  \
    vobjectSetListAt(volevariantGetListObjectList(l), i, volevariantGetObject(v)) 

#define volevariantGetListCount(l) vobjectGetListCount(volevariantGetListObjectList(l))

#if (vportOLE)
#define volevariantGetType(v)   (V_VT(&((v)->variant)))   
#else
#define volevariantGetType(v)   (0)   
#endif

#if (vportOLE)
#define _volevariantGetVARIANT(v)   (&((v)->variant))
#endif

#if __BORLANDC__ && !defined(__cplusplus) && !defined(_ANONYMOUS_UNION) || defined(NONAMELESSUNION)
#if __BORLANDC__ < 0x502
#define _voleDEREF_VARIANT_VT(base, arg)(base->arg)
#define _voleDEREF_VARIANT_UNION(base, arg)(base->u.arg)
#else
#define _voleDEREF_VARIANT_VT(base, arg)(base->n1.n2.arg)
#define _voleDEREF_VARIANT_UNION(base, arg)(base->n1.n2.n3.arg)
#endif
#else
#define _voleDEREF_VARIANT_VT(base, arg)(base->arg)
#define _voleDEREF_VARIANT_UNION(base, arg)(base->arg)
#endif

#if __BORLANDC__ && !defined(_ANONYMOUS_UNION) || defined(NONAMELESSUNION)
#define _voleDEREF_CY_UNION(base, arg)(base->s.arg)
#else
#define _voleDEREF_CY_UNION(base, arg)(base->arg)
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef volevariantINCLUDED */

