/* $Id: xcflchsr.h,v 1.2 1995/05/02 21:31:04 abstine Exp $ */

/************************************************************

    xcflchsr.h
    C Interface file for the xc filechooser

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef xcflchsrINCLUDED
#define xcflchsrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>              /* for v*HEADER */
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcomboINCLUDED
#include vcomboHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

enum{
   xcflchsrSELECT_ASCII = vfilechsrNEXT_SELECT,
   xcflchsrSELECT_LATIN_1,
   xcflchsrSELECT_MACINTOSH,
   xcflchsrSELECT_WINDOWS,
   xcflchsrSELECT_LATIN_2,

   xcflchsrSELECT_LATIN_3,
   xcflchsrSELECT_LATIN_4,
   xcflchsrSELECT_LATIN_5,
   xcflchsrSELECT_GREEK,
   xcflchsrSELECT_CYRILLIC,

   xcflchsrSELECT_KOI8,
   xcflchsrSELECT_HEBREW,
   xcflchsrSELECT_ADOBE_STD_ENC,
   xcflchsrSELECT_ADOBE_SYMBOL,
   xcflchsrSELECT_DEC_TECH,

   xcflchsrSELECT_VISCII,
   xcflchsrSELECT_JISX0201,

   xcflchsrSELECT_UNICODE,
   xcflchsrSELECT_JISX0208_83,
   xcflchsrSELECT_JISX0212,
   xcflchsrSELECT_KSC5601,
   xcflchsrSELECT_GB2312,

   xcflchsrSELECT_BIG5HKU,

   xcflchsrSELECT_SJIS,
   xcflchsrSELECT_JEUC,
   xcflchsrSELECT_UTF,

   xcflchsrSELECT_IMPLICIT,
   xcflchsrSELECT_BIG_ENDIAN,
   xcflchsrSELECT_LITTLE_ENDIAN,

   xcflchsrNEXT_SELECT
};



/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct xcflchsr       xcflchsr;
typedef struct xcflchsrClass  xcflchsrClass;

typedef int (*xcflchsrApplyFunc) 
   (xcflchsr *chooser, vfsPath *path, int charset, int byteOrder);

#if !(vportBAD_CC_SCOPING)
struct xcflchsr {
   vfilechsr                filechsr;
   void                    *encodingItem;
   void                    *byteOrderItem;
   xcflchsrApplyFunc        applyProc;
   int                      charset;
   int                      byteOrder;
   vconfirm                *splitConfirm;
};
#endif

/*
 * xc filechooser Class definition
 */

struct xcflchsrClass {
    vfilechsrCLASS(xcflchsrClass, xcflchsr, vfilechsrApplyFunc);
};

/*
 * * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

xcflchsrClass *xcflchsrGetDefaultClass(
    void
    );

xcflchsrClass *xcflchsrGetSplitClass(
    void
    );

xcflchsr *xcflchsrCreateOfClass(
    xcflchsrClass               *clas
    );

xcflchsr *xcflchsrCreate(
    void
    );

xcflchsr *xcflchsrCreateSplit(
    void
    );

void xcflchsrDestroy(
    xcflchsr                    *chooser
    );

void xcflchsrOpen(
    xcflchsr                    *chooser
    );

void xcflchsrClose(
    xcflchsr                    *chooser
    );

void xcflchsrSetApply(
    xcflchsr                    *chooser,
    xcflchsrApplyFunc            applyFunc
    );

void xcflchsrSetData(
    xcflchsr                    *chooser,
    void                        *data
    );

void xcflchsrSetTitle(
    xcflchsr                    *chooser,
    const vchar                 *title
    );

void xcflchsrSetTitleScribed(
    xcflchsr                    *chooser,
    vscribe                     *title
    );

xcflchsrClass *xcflchsrGetClass(
    xcflchsr                    *chooser 
    );

void *xcflchsrGetData(
    xcflchsr                    *chooser 
    );

xcflchsrApplyFunc xcflchsrGetApply(
    xcflchsr                    *chooser
    );

vfilechsr *xcflchsrGetFilechsr(
    xcflchsr                    *chooser
    );

vdialog *xcflchsrGetDialog(
    xcflchsr                    *chooser
    );


/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define xcflchsrCreateOfClass(c)     \
  ((xcflchsr *) vfilechsrCreateOfClass((vfilechsrClass *) (c)))
#define xcflchsrGetClass(c)          \
  ((xcflchsrClass *) vfilechsrGetClass((vfilechsr *) (c)))
#define xcflchsrCreate()             \
  xcflchsrCreateOfClass(xcflchsrGetDefaultClass())
#define xcflchsrCreateSplit()        \
  xcflchsrCreateOfClass(xcflchsrGetSplitClass())

#define xcflchsrGetData(c)               (vfilechsrGetData(&(c)->filechsr))
#define xcflchsrGetDialog(c)             (vfilechsrGetDialog(&(c)->filechsr))
#define xcflchsrGetFilechsr(c)           (&(c)->filechsr)
#define xcflchsrGetApply(c)              ((c)->applyProc)

#define xcflchsrSetApply(c, proc)        ((c)->applyProc = (proc))

/*
 * * * * * * * * * FUNCTION DEFINED AS MESSAGES * * * * * * * * * *
 */

#define xcflchsrSend(m, s, a) \
  (vclassSend(xcflchsrGetClass(m), s, a))

#define xcflchsrSetData(c, d) \
  xcflchsrSend(c, vwindowSET_DATA, (c, d))
#define xcflchsrDestroy(c) \
  xcflchsrSend(c, vobjectDESTROY, (c))
#define xcflchsrOpen(c) \
  xcflchsrSend(c, vwindowOPEN, (c))
#define xcflchsrClose(c) \
  xcflchsrSend(c, vwindowCLOSE, (c))

#define xcflchsrSetTitleScribed(c,t) \
  xcflchsrSend(c, vwindowSET_TITLE_SCRIBED, (c,t))
#define xcflchsrSetTitle(c,t) \
  xcflchsrSetTitleScribed((c), (t) ? vcharScribe(t) : NULL)

#if (vportBAD_CC_SCOPING)
struct xcflchsr {
   vfilechsr                filechsr;
   void                    *encodingItem;
   void                    *byteOrderItem;
   xcflchsrApplyFunc        applyProc;
   int                      charset;
   int                      byteOrder;
   vconfirm                *splitConfirm;
};
#endif

vportEND_CPLUSPLUS_EXTERN_C

#endif /* xcflchsrINCLUDED */
