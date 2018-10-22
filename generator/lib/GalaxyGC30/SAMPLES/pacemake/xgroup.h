/* $Id: xgroup.h,v 1.3 1995/04/27 00:52:25 abstine Exp $ */
/* xgroup.h -- interface to the coolGroupImage calculator thingie
 *
 * Gotta have some legalese:
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,.
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 */

/* This is a subclass of xpacemaker that calculates pretty pictures based
 * on calculated pixel indices.  As the group object does its work, it 
 * calls a calculation function to calculate the value of each pixel in
 * an image.  You can use the xpacemaker calls to set a notify, to start,
 * stop, and terminate the calculation.
 *
 * How to use it:
 *
 * First, you need to create a group object:
 *
 * xgroup *group = xgroupCreate();
 *
 * Right now, it's pretty worthless.  So, write and attach a calculation
 * function:
 *
 * vbyte myCalcFunction (int x, int y)
 * {
 *      return (x * y - (x + y));
 * } \* my Calcfunction *\
 *
 * xgroupSetCalcualtor (group, myCalcFunction);
 *
 * Then, set the size of the image.  (this defines the ranges that the
 * calculator function will be called over.)
 *
 * xgroupSetSize (group, 500, 1500);
 *
 * Then, to actually calculate, call xgroupCalculate. This function takes
 * a flag parameter that choose between asynchronous calculation (e.g. it
 * uses the pacemaker's event mechanism to interleave calculation with 
 * servicing the rest of the UI via the event manager) and synchronous
 * calculation (e.g. the program is blocked doing nothing but the calculation,
 * resulting in no window updating or user interaction until the process
 * is done).  asynchronous calculation can be interrupted, but synchronous
 * cannot.
 *
 * so, you'd do xgroupCalculate (group, TRUE); for event driven calcs, and
 * xgroupCalculate (group, FALSE) for blocking calcs.
 *
 *
 * To use xpacemaker functions, you'll need to get the pacemaker object
 * that underlies the xgroup object:
 *
 * xpacemaker *pacemaker = xgroupGetPacemaker (group);
 *
 * To this you can then use the xpacemaker API:
 * xpacemakerSetNotify, xpacemakerStop, etc...
 *
 * When updating status indiactors, you can query the group object to see
 * how much work it has to do, as well as how far it has progressed:
 *
 * xgroupGetWidth and xgroupGetHeight return the size of the image being
 * iterated over.  The total amount of work that needs to be done can
 * be determined by multiplying these two.
 *
 * Calculations in a x-major orientaton (e.g. an entire horizontal row
 * of pixels are calculated before moving on to the next row.) So to
 * find out how far it's gotten, you can query the current X and Y postion
 * and multiply those as such:
 *
 * int currentPosition =  xgroupGetCurrentY(group) * xgroupGetWidth(group)
 *                        + xgroupGetCurrentX(group));
 *
 * To get the image after it's calcualted, use
 * xgroupGetImage (group);
 *
 * When you're finally done, you can free the memory being consumed
 * by using xgroupDestroy or xpacemakerDestroyLater.  
 *
 * Important - don't use xgroupDestroy (or xpacemakerDestroy) when inside
 * of the pacemaker notify.  Use xpacemakerDestroylater.
 */



#ifndef xgroupINCLUDED /* protect ourselves from multiple inclusion */
#define xgroupINCLUDED 1


/* #include headers *only* for things referenced in this header file. Don't
 * #include stuff that will only be used for the implementation.
 *
 * Some headers are included for documentation/completeness purposes.
 * vdialogHEADER pulls in vclass, vevent, vresource etc...  Because of
 * the vspamINCLUDED definitions, we prevent the reading and skipping over
 * of huge amounts of now-unnecessary text.
 */

#ifndef vportINCLUDED	/* get our vspamHEADER symbols */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED	/* for vbool, etc... */
#include vstdHEADER
#endif

#ifndef  vclassINCLUDED	/* well, we are doing subclassing here */
#include vclassHEADER
#endif

#ifndef  vimageINCLUDED  /* we construct images.  Images to make us go. */
#include vimageHEADER
#endif

#ifndef  xpacemakerINCLUDED
#include "xpacemak.h"
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*

 * ----- Public Constant Definitions -----
 */

/* this is where you export constants, symbols, enums, #defines, and
 * vnames that your clients are allowed to use
 */




/*
 * ----- Public Type Definitions -----
 */

/* here is where you export structures that your clients have permission
 * to touch.  (vrect is an example of this).  Think long and hard about
 * what structures you export, since you'll be forever tied to supporting
 * those structures, as well as giving bad programmers an excuse to mess
 * with your structure innards at inopportune moments.
 */

/* here is where you also export your typedefs for your objects and classes.
 * What you're doing is setting up forward references to the real structure
 * definitions that occur later in the file.  These forward references are
 * necessary so that the function prototypes make sense and will compile
 * without compiler complaints.
 * Exported in this place are types for notify functions.
 */


typedef struct xgroup      xgroup;
typedef struct xgroupClass xgroupClass;

typedef vbyte (*xgroupCalcFunc)(int x, int y);

typedef void (*xgroupNoteProc)(xgroup *group, int message);



/*
 * ----- Public Function Prototypes -----
 */

/* your complete exported API should be placed here.  No clue as to how
 * things are implemented should be put here.  It doesn't matter if a 
 * particular call is implemented by a macro, a method, or a direct function
 * call.  It should be put here.
 */

xgroupClass *xgroupGetDefaultClass (
    void
    );

xgroup *xgroupCreate (
    void
    );

void xgroupDestroy (
    xgroup *group
    );

xgroupClass *xgroupGetClass (
    xgroup *group
    );

xpacemaker *xgroupGetPacemaker (
    xgroup *group
    );

void xgroupSetCalculator (
    xgroup *group,
    xgroupCalcFunc calculator
    );

xgroupCalcFunc xgroupGetCalculator (
    xgroup *group
    );

void xgroupCalculate (
    xgroup *group,
    int     ansynchronous  /* TRUE means it'll be event-driven */
    );

vbyte xgroupCalculatePoint (
    xgroup *group,
    int     x,
    int	    y
    );

vimage *xgroupGetImage (
    xgroup *group
    );

void xgroupSetSize (
    xgroup *group,
    int	    width,
    int	    height
    );

int xgroupGetWidth (
    xgroup *group
    );

int xgroupGetHeight (
    xgroup *group
    );

int xgroupGetCurrentX (
    xgroup *group
    );

int xgroupGetCurrentY (
    xgroup *group
    );




/*
 * ----- Private Constant Definitions -----
 */

/* semi-private flag symbols (such as flag field values) should be placed here,
 * as well as private symbols that are referenced in macros.
 */




/*
 * ----- Private Variable Declarations -----
 */

/* publically-scope, yet private access global variables go here.  Typically
 * only vname "predef" tables are put here.
 */




/*
 * ----- Private Type Definitions -----
 */

/* private structures live here, as do the structure for the objects that
 * you are creating.  The class macro and class structure live here
 * as well
 */

struct xgroup {
    xpacemaker pacemaker; /* where we're inheriting from */
    vimage    *image;
    vpixmapScanner scanner;
    int	       width, height;
#if (!vportBAD_CC_SCOPING)
    int	       x, y;
#else
    int	       X, Y;
#endif
    xgroupCalcFunc calculator;
};

#define xgroupCLASS(CLASS, GROUP, NOTIFY, CALCULATOR)                         \
    xpacemakerCLASS(CLASS, GROUP, NOTIFY);                                    \
    vclassMETHOD (xgroupSET_CALCULATOR, (GROUP *group,                        \
					 CALCULATOR calculator));             \
    vclassMETHOD (xgroupCALCULATE, (GROUP *group, int async));                \
    vclassMETHOD_RET (xgroupCALCULATE_POINT, vbyte, (GROUP *group,            \
						     int x, int y));          \
    vclassMETHOD (xgroupSET_SIZE, (GROUP *group, int width, int height))


struct xgroupClass {
    xgroupCLASS (xgroupClass, xgroup, xgroupNoteProc, xgroupCalcFunc);
};



/*
 * ----- Private Function Macro Definitions -----
 */

/* entry points that are implemented by macros belong here.  Typically,
 * "Set" calls go through methods and "Get" calls are done via macros for
 * a good tradeoff between flexibility and performance.
 */


#define xgroupCreate() ((xgroup*)vinstanceCreateOfClass \
			((vinstanceClass*)xgroupGetDefaultClass()))

#define xgroupGetPacemaker(g)	( &(g)->pacemaker )

#define xgroupGetClass(g) ((xgroupClass*)xpacemakerGetClass \
			   (xgroupGetPacemaker((g))))

#if (!vportBAD_CC_SCOPING)
#define xgroupGetCurrentX(g)	( (g)->x )
#define xgroupGetCurrentY(g)	( (g)->y )
#else
#define xgroupGetCurrentX(g)	( (g)->Y )
#define xgroupGetCurrentY(g)	( (g)->Y )
#endif

#define xgroupGetImage(g)	( (g)->image )
#define xgroupGetWidth(g)	( (g)->width )
#define xgroupGetHeight(g)	( (g)->height )


/*
 * ----- Private Function Message Definitions -----
 */

/* Here is where method dispatch macros (the things that boil down to
 * vclassSend) are defined.
 */

#define xgroupDestroy(g) \
	vclassSend (xgroupGetClass((g)), vinstanceDESTROY, (g))

#define xgroupSetCalculator(g, c) \
	vclassSend (xgroupGetClass((g)), xgroupSET_CALCULATOR, (g, c))

#define xgroupCalculate(g, a) \
	vclassSend (xgroupGetClass((g)), xgroupCALCULATE, (g, a))

#define xgroupCalculatePoint(g, x, y) \
	vclassSend (xgroupGetClass((g)), xgroupCALCULATE_POINT, (g, x, y))

#define xgroupSetSize(g, w, h) \
	vclassSend (xgroupGetClass((g)), xgroupSET_SIZE, (g, w, h))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* xgroupINCLUDED */



/* stuff that tells my editor (GNU emacs) how I like my code formatted */

/* Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */

