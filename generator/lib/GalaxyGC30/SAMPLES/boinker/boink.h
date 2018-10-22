/* $Id: boink.h,v 1.2 1995/07/28 19:03:41 simone Exp $ */
/******************************************************************************
 *                  (c) Copyright 1993-94 Visix Software Inc.                 *
 *                            All rights reserved.                            *
 *                                                                            *
 *    The following Sample Code is provided for your reference purposes in    *
 *     connection with your use of the Galaxy Application Environment (TM)    *
 *     software product which you have licensed from Visix Software, Inc.     *
 * ("Visix"). The Sample code is provided to you without any warranty of any  *
 *     kind whatsoever and you agree to be responsible for the use and/or     *
 *   incorporation of the Sample Code into any software product you develop.  *
 *  You agree to fully and completely indemnify and hold Visix harmless from  *
 * any and all loss, claim, liability or damages with respect to your use of  *
 *    the Sample Code. Subject to the foregoing, you are permitted to copy,   *
 *   modify, and distribute the Sample Code for any purpose and without fee,  *
 * provided that (i) a copyright notice in the in the form of "Copyright 1992,*
 *  93 Visix Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All *
 * Rights Reserved" appears in all copies, (ii) both the copyright notice and *
 *  this permission notice appear in supporting documentation and (iii) you   *
 *            are a valid licensee of Galaxy Application Environment.         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * Description:                                                               *
 *     Beginnings of a program to test the ttask classes. To date (9/14/94)   *
 *     it only does very superficial testing.                                 *
 *                                                                            *
 *     Managers Used:                                                         *
 *         o Exception Manager - we create one or two subclasses AND show     *
 *           how a toplevel exception handler could be written to handle      *
 *           uncaught exceptions a bit more gracefully that abort()...        *
 *         o Debugging Manager - we include several examples of how the misc  *
 *           vdebug macros and routines can be used to implement argument,    *
 *           return-value, pre-post condition, and assertion checking...      *
 *         o Class Manager - we use to class manager to implement non-GUI     *
 *           classes as well as dialog item subclasses.                       *
 *         o Event Manager - if you've ever wanted to know how to use client  *
 *           events, you're looking at the right sample...specifically, we    *
 *           use client events to implement a "progress splash window" (ie.   *
 *           a splash window that shows the current point of initialization   *
 *           via a little status message).                                    *
 *                                                                            *
 * Modification History:                                                      *
 *     o 09-14-94: ssmc, created for The Galaxy Developers Conference 1994    *
 *                                                                            *
 * Special Usage Notes:                                                       *
 *     o <none>                                                               *
 *                                                                            *
 * Text Editor Formatting:                                                    *
 *     Symantec: Tab(4), Font(Any Fixed Width)                                *
 *     Emacs: see end of file for info                                        *
 *                                                                            *
 ******************************************************************************
 */

#ifndef BoinkitemINCLUDED
#define BoinkitemINCLUDED


#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef vpointINCLUDED
#include vpointHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef ttaskINCLUDED
#include "ttask.h"
#endif


/*
 *+------------------------------------------------------------------------+
 * public consts, types, etc.
 *+------------------------------------------------------------------------+
 */


/* */
typedef struct Boinkitem Boinkitem;
typedef struct BoinkitemClass BoinkitemClass;
typedef void (*BoinkitemNoteProc)(Boinkitem*, vevent*);


typedef struct BoinkitemGeoInitializer {
	double			angle;
	vpointFloat		scale;
	vpoint			a;
}BoinkitemGeoInitializer;


/*
 *+------------------------------------------------------------------------+
 * public routines
 *+------------------------------------------------------------------------+
 */

BoinkitemClass *BoinkitemGetDefaultClass(
	void
	);

const BoinkitemGeoInitializer* BoinkitemGetDefaultGeometry(
	void
	);

Boinkitem *BoinkitemCreateOfClass(
	BoinkitemClass			*clas
	);

Boinkitem *BoinkitemCreate(
	void
	);

Boinkitem *BoinkitemLoad(
	vresource				 resource
	);

Boinkitem *BoinkitemClone(
	Boinkitem				*item
	);

void BoinkitemInitOfClass(
	Boinkitem				*item,
	BoinkitemClass			*clas
	);
	
void BoinkitemInit(
	Boinkitem				*item
	);

void BoinkitemLoadInit(
	Boinkitem				*item,
	vresource				 resource
	);

void BoinkitemCopy(
	Boinkitem				*item,
	Boinkitem				*copy
	);

void BoinkitemCopyInit(
	Boinkitem				*item,
	Boinkitem				*copy
	);

void BoinkitemDestroy(
	Boinkitem				*item
	);

void BoinkitemDestroyLater(
	Boinkitem				*item
	);

void BoinkitemStore(
	Boinkitem				*item,
	vresource				 resource
	);

void BoinkitemAutopilot(
	Boinkitem				*item
	);

void BoinkitemStopAutopilot(
	Boinkitem				*item
	);

vtimestamp BoinkitemGetPeriod(
	Boinkitem				*item
	);

void BoinkitemClear(
	Boinkitem				*item
	);

void BoinkitemSetPeriod(
	Boinkitem				*item,
	vtimestamp				*period
	);

void BoinkitemAccumulate(
	Boinkitem				*item,
	unsigned				 yes
	);

void BoinkitemRandomTranslate(
	Boinkitem				*item
	);

void BoinkitemMove(
	Boinkitem						*item,
	const BoinkitemGeoInitializer	*geometry
	);

void BoinkitemAnimate(
	Boinkitem				*item,
	unsigned				 yes
	);

void BoinkitemRandomizeGeometry(
	Boinkitem				*item,
	unsigned				 yes
	);


vdialogItem	*BoinkitemGetItem(
	Boinkitem				*item
	);

vobject *BoinkitemGetObject(
	Boinkitem				*item
	);

BoinkitemClass *BoinkitemGetClass(
	Boinkitem				*item
	);


/*
 *+------------------------------------------------------------------------+
 * private type definitions
 *+------------------------------------------------------------------------+
 */


struct Boinkitem {
	vdialogItem		base;			/* Base class's object type */
	double			angle;			/* My Stuff... */
	vpointFloat		scale;
	vpoint			a;
	vpoint			o;
	vimage		   *history;
	ttask		   *task;
	vtimestamp	    period;
	unsigned		prefAutoOn:1;
	unsigned		cumulative:1;
	unsigned		ownPeriod:1;
	unsigned		animate:1;
	unsigned		autoOn:1;
	unsigned	    randomGeo:1;
};

#define BoinkitemCLASS(argCLAS, argBITEM, argNOTEPROC)						  \
	vdialogITEM_CLASS(argCLAS, argBITEM, argNOTEPROC); 						  \
	vclassVARIABLE(BoinkitemSPEED, vtimestamp); 							  \
	vclassMETHOD(BoinkitemAUTO_FEED, (argBITEM*)); 							  \
	vclassMETHOD(BoinkitemSTOP_FEED, (argBITEM*)); 							  \
	vclassMETHOD_RET(BoinkitemGET_PERIOD, vtimestamp, (argBITEM*)); 		  \
	vclassMETHOD(BoinkitemCLEAR, (argBITEM*)); 								  \
	vclassMETHOD(BoinkitemSET_PERIOD, (argBITEM*, vtimestamp*)); 			  \
	vclassMETHOD(BoinkitemACCUMULATE, (argBITEM*, unsigned)); 				  \
	vclassMETHOD(BoinkitemRANDOM_TRANSLATE, (argBITEM*)); 					  \
	vclassMETHOD(BoinkitemMOVE, (argBITEM*, const BoinkitemGeoInitializer*)); \
	vclassMETHOD(BoinkitemANIMATE, (argBITEM*, unsigned)); 					  \
	vclassMETHOD(BoinkitemRANDOMIZE_GEO, (argBITEM*, unsigned))

struct BoinkitemClass {
	BoinkitemCLASS(BoinkitemClass, Boinkitem, BoinkitemNoteProc);
};


/*
 *+------------------------------------------------------------------------+
 * private macro definitions
 *+------------------------------------------------------------------------+
 */

#define BoinkitemGetItem(bi)	(&(bi)->base)
#define BoinkitemGetObject(bi)	vdialogGetItemObject(&(bi)->base)
#define BoinkitemGetClass(bi)	((BoinkitemClass*)vdialogGetItemClass(&(bi)->base))
#define BoinkitemSend(bi,m,a)	vclassSend(BoinkitemGetClass(bi), m,a)

#define BoinkitemCreateOfClass(c)	((Boinkitem*)vobjectCreateOfClass((vobjectClass*)(c)))
#define BoinkitemCreate()			BoinkitemCreateOfClass(BoinkitemGetDefaultClass())
#define BoinkitemClone(bi)			((Boinkitem*)vobjectClone(BoinkitemGetObject(bi)))
#define BoinkitemDestroy(bi)		BoinkitemSend(bi, vinstanceDESTROY, (bi))
#define BoinkitemLoad(r)			((Boinkitem*)vobjectLoad(r))
#define BoinkitemLoadInit(bi,r)		vobjectLoadInit(BoinkitemGetObject(bi), r)
#define BoinkitemInitOfClass(bi,c)	vobjectInitOfClass(BoinkitemGetObject(bi), (vobjectClass*)(c))
#define BoinkitemInit(bi)			BoinkitemInitOfClass(bi, BoinkitemGetDefaultClass())
#define BoinkitemDestroyLater(bi)	vobjectDestroyLater(BoinkitemGetObject(bi))
#define BoinkitemCopyInit(bi,dup)	vdialogCopyInitItem(&(bi)->base, &(dup)->base)
#define BoinkitemCopy(bi,dup)		BoinkitemSend(bi, vobjectCOPY, (bi,dup))
#define BoinkitemStore(bi,r)		BoinkitemSend(bi, vobjectSTORE, (bi,r))

#define BoinkitemAutopilot(bi)		BoinkitemSend(bi, BoinkitemAUTO_FEED, (bi))
#define BoinkitemStopAutopilot(bi)	BoinkitemSend(bi, BoinkitemSTOP_FEED, (bi))
#define BoinkitemGetPeriod(bi)		BoinkitemSend(bi, BoinkitemGET_PERIOD, (bi))
#define BoinkitemClear(bi)			BoinkitemSend(bi, BoinkitemCLEAR, (bi))
#define BoinkitemSetPeriod(bi,tm)	BoinkitemSend(bi, BoinkitemSET_PERIOD, (bi,tm))
#define BoinkitemAccumulate(bi,b)	BoinkitemSend(bi, BoinkitemACCUMULATE, (bi,b))
#define BoinkitemRandomTranslate(bi) BoinkitemSend(bi, BoinkitemRANDOM_TRANSLATE, (bi))
#define BoinkitemMove(bi,geo) 		BoinkitemSend(bi, BoinkitemMOVE, (bi,geo))
#define BoinkitemAnimate(bi,b)		BoinkitemSend(bi, BoinkitemANIMATE, (bi,b))
#define BoinkitemRandomizeGeometry(bi,b) BoinkitemSend(bi, BoinkitemRANDOMIZE_GEO, (bi,b))


/* BoinkitemINCLUDED */
#endif



/*
 *+------------------------------------------------------------------------+
 * emacs editor formatting information:
 *+------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 64 72 80 88 96 104)
 * tab-width:4
 * indent-tabs-mode:t
 * truncate-lines:t
 * End:
 */
