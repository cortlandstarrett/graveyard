/* $Id: vsvcchsr.h,v 1.14 1997/08/13 17:06:06 robert Exp $ */

/*******************************************************************
 *
 *    vsvcchsr.h
 *    C Interface to the Service Chooser
 *
 *    (c) Copyright Visix Software  1993
 *    All rights reserved
 *
 *******************************************************************/

#ifndef vservicechsrINCLUDED
#define vservicechsrINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef vrulerINCLUDED
#include vrulerHEADER
#endif

#ifndef vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef vserviceINCLUDED
#include vserviceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*******************************************************************
 *
 * Public constant definitions.
 *
 *******************************************************************/

enum {
   vservicechsrSET_FILTER	= vdialogNEXT_SELECT,
   vservicechsrQUERY,
   vservicechsrGET_INFO,
   vservicechsrALL_ON,
   vservicechsrALL_OFF,
   vservicechsrSHOW_ATTRIBUTE,
   vservicechsrNEXT_SELECT
   };

/*******************************************************************
 *
 * Public type definitions.
 *
 *******************************************************************/

typedef struct vservicechsr		vservicechsr;
typedef struct vservicechsrClass	vservicechsrClass;

typedef int (*vservicechsrApplyFunc)(
   vservicechsr		*serviceChooser,
   vscrap		*scrap
   );

/*******************************************************************
 *
 * Public function prototypes.
 *
 *******************************************************************/

void vservicechsrStartup(
   void
   );

vservicechsrClass *vservicechsrGetDefaultClass(
   void
   );

vservicechsr *vservicechsrCreateOfClass(
   vservicechsrClass	*clas
   );

vservicechsr *vservicechsrCreate(
   void
   );

void vservicechsrDestroy(
   vservicechsr		*serviceChooser
   );

void vservicechsrOpen(
   vservicechsr		*serviceChooser
   );

void vservicechsrClose(
   vservicechsr		*serviceChooser
   );

void vservicechsrRescan(
   vservicechsr		*serviceChooser
   );

vservicechsrApplyFunc vservicechsrGetApply(
   vservicechsr		*serviceChooser
   );

void vservicechsrSetApply(
   vservicechsr			*serviceChooser,
   vservicechsrApplyFunc	 applyFunc
   );

vscrap *vservicechsrGetMatchScrap(
   vservicechsr		*serviceChooser
   );

void vservicechsrSetMatchScrap(
   vservicechsr		*serviceChooser,
   vscrap		*scrap
   );

vservicechsrClass *vservicechsrGetClass(
   vservicechsr		*serviceChooser
   );

vconfirm *vservicechsrGetConfirm(
   vservicechsr		*serviceChooser
   );

vdialog *vservicechsrGetDialog(
   vservicechsr		*serviceChooser
   );

vwindow *vservicechsrGetWindow(
   vservicechsr		*serviceChooser
   );

vobject *vservicechsrGetObject(
   vservicechsr		*serviceChooser
   );


/*******************************************************************
 *
 * Private constant definitions.
 *
 *******************************************************************/


/*******************************************************************
 *
 * Private type definitions.
 *
 *******************************************************************/

struct vservicechsr {
   vconfirm		  confirm;
   vconfirm		 *info;
   vlist		 *list;
   vlistview		 *lview;
   vruler		 *ruler;
   vmenubar		 *menubar;
   vsession		 *session;
   vscrap		**scraps;
   int			  nscraps;
   vscrap		 *match;
   vdict		  attributes;
   vbool		  compact;
   int			  moving;
   vservicechsrApplyFunc  apply;
   };

/*******************************************************************
 *
 * Class definitions.
 *
 *******************************************************************/

#define vservicechsrCLASS(SUPER, CONFIRM, NOTIFY)			\
   vconfirmCLASS(SUPER, CONFIRM, NOTIFY);				\
   vclassMETHOD(vservicechsrRESCAN, (CONFIRM *chooser));		\
   vclassMETHOD(vservicechsrSET_APPLY, (CONFIRM *chooser,		\
				vservicechsrApplyFunc applyFunc));	\
   vclassMETHOD(vservicechsrSET_MATCH, (CONFIRM *chooser, vscrap *scrap)); \
   vclassMETHOD_RET(vservicechsrHOOK_APPLY_SERVICE, int,		\
		    (CONFIRM *chooser, vscrap *scrap))

struct vservicechsrClass {
   vservicechsrCLASS(vservicechsrClass, vservicechsr, vconfirmHookProc);
   };

/*******************************************************************
 *
 * Private function prototypes.
 *
 *******************************************************************/


/*******************************************************************
 *
 * Private function macro definitions.
 *
 *******************************************************************/

#define vservicechsrGetConfirm(f)					\
   vportBASE_OBJECT((f), confirm)

#define vservicechsrCreateOfClass(s)					\
   ((vservicechsr *)vconfirmCreateOfClass((vconfirm *)(s)))

#define vservicechsrCreate()						\
   (vservicechsrCreateOfClass(vservicechsrGetDefaultClass()))

#define vservicechsrGetClass(s)						\
   ((vservicechsrClass *)vconfirmGetClass(vservicechsrGetConfirm(s)))

#define vservicechsrDestroy(f)						\
   vconfirmDestroy(vservicechsrGetConfirm(f))

#define vservicechsrGetApply(f)						\
   ((f)->apply)

#define vservicechsrGetMatchScrap(f)					\
   ((f)->match)

#define vservicechsrGetDialog(f)					\
   (vconfirmGetDialog(vservicechsrGetConfirm(f)))

#define vservicechsrGetWindow(f)					\
   (vconfirmGetWindow(vservicechsrGetConfirm(f)))

#define vservicechsrGetObject(f)					\
   (vwindowGetObject(vservicechsrGetWindow(f)))

/*******************************************************************
 *
 * Private function message definitions.
 *
 *******************************************************************/

#define _vservicechsrSend(f, s, a)					\
   vclassSend(vservicechsrGetClass(f), s, a)

#define vservicechsrRescan(f)						\
   vclassSend(vservicechsrGetClass(f), vservicechsrRESCAN, (f))

#define vservicechsrSetApply(f, s)					\
   vclassSend(vservicechsrGetClass(f), vservicechsrSET_APPLY, (f, s))

#define vservicechsrSetMatchScrap(f, s)					\
   vclassSend(vservicechsrGetClass(f), vservicechsrSET_MATCH, (f, s))

#define vservicechsrOpen(f)						\
   vclassSend(vservicechsrGetClass(f), vwindowOPEN, (f))

#define vservicechsrClose(f)						\
   vclassSend(vservicechsrGetClass(f), vwindowCLOSE, (f))

/*******************************************************************
 *
 * Service Chooser global variables.
 *
 *******************************************************************/

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vservicechsrINCLUDED */
