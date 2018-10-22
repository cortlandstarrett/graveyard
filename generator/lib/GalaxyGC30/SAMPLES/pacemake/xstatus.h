/* xstatus.h -- a handy little status item.  It can show a percentage,
 * 		or just a moving "barber-pole" indicator to give the user
 *		feedback during a long operation.
 *
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

/* To use the status indicator, you'll need to do these things;
 *
 * Go into vre and make a subclass of vdialogItem called "xstatus".  Put
 * this anywhere you want, and feel free to set the foreground and background
 * colors.  These will be used in the appropriate places
 *
 * in your code,
 *
 * call xstatusGetDefaultClass(); to set up the class and register its
 * name.  You can now load dialogs that contain xstatus objects
 *
 * Get ahold of this object with vdialogFindItem
 *
 * If you want to use it in barberpole mode, cal xstatusAdvance to cause
 * the marching stripes to march on a regular basis.  It defaults to barber-
 * pole mode unless you set the maximum to a value.
 *
 * If you want to use it in percentage mode, call xstatusSetMax to set
 * a maximum value.  When you do a hunk of work, call xstatusAdvanceTo
 * to set the status object to a particular value.  The status thingie will
 * then draw a filled rectange showing the percentage the current value
 * is of the maximum.  (e.g. set the max to 75, AdvanceTo to 35, and you'll
 * get a dialog item that's about half-way filled)
 * xstatusAdvance is the same as advancing the status value by one
 */


#ifndef xstatusINCLUDED /* protect ourselves from multiple inclusion */
#define xstatusINCLUDED 1


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

#ifndef vstdINCLUDED	/* for vbool, etc... */
#include vstdHEADER
#endif

#ifndef vclassINCLUDED	/* well, we are doing subclassing here */
#include vclassHEADER
#endif

#ifndef vdialogINCLUDED	/* we're subclassing from vdialogItem */
#include vdialogHEADER
#endif




vportBEGIN_CPLUSPLUS_EXTERN_C

/*

 * ----- Public Constant Definitions -----
 */

/* this is where you export constants, symbols, enums, #defines, and
 * vnames that your clients are allowed to use
 */


/* this constant, when given to xstatusSetMax, means that there is *no* maximum
 * value, and to fall back to barbershop mode
 */
enum {
    xstatusNO_VALUE = -1
};




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


typedef struct xstatus xstatus;
typedef struct xstatusClass xstatusClass;




/*
 * ----- Public Function Prototypes -----
 */

/* your complete exported API should be placed here.  No clue as to how
 * things are implemented should be put here.  It doesn't matter if a 
 * particular call is implemented by a macro, a method, or a direct function
 * call.  It should be put here.
 */


xstatusClass *xstatusGetDefaultClass (
    void
    );

vdialogItem *xstatusGetItem (
    xstatus *status
    );

xstatusClass *xstatusGetClass (
    xstatus *status
    );


void xstatusAdvance ( /* equivalent to xstatusAdvanceTo (s, xstatusNO_VALUE) */
    xstatus *status
    );


void xstatusAdvanceTo (
    xstatus *status,
    long     value
    );

void xstatusSetMax (
    xstatus *status,
    long     max
    );

long xstatusGetMax (
    xstatus *status
    );

long xstatusGetValue (
    xstatus *status
    );

void xstatusSetBarberPole (
    xstatus *status,
    int onOff
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

struct xstatus {
    vdialogItem item;
    long        max;
    long        value;
    vtimestamp  lastUpdate;
};

#define xstatusCLASS(CLASS, STATUS, NOTIFY)                                   \
    vdialogITEM_CLASS(CLASS, STATUS, NOTIFY);                                 \
    vclassMETHOD (xstatusADVANCE_TO, (STATUS *status, long value));           \
    vclassMETHOD (xstatusSET_MAX, (STATUS *status, long value))

struct xstatusClass {
    xstatusCLASS (xstatusClass, xstatus, vdialogItemNoteProc);
};


/*
 * ----- Private Function Macro Definitions -----
 */

/* entry points that are implemented by macros belong here.  Typically,
 * "Set" calls go through methods and "Get" calls are done via macros for
 * a good tradeoff between flexibility and performance.
 */

#define xstatusGetItem(s)	( &(s)->item )
#define xstatusGetMax(s)	(  (s)->max  )
#define xstatusGetValue(s)	(  (s)->value)

#define xstatusGetClass(s)	((xstatusClass*)vdialogGetItemClass \
				 (xstatusGetItem((s))))

#define xstatusAdvance(s)	xstatusAdvanceTo((s), xstatusNO_VALUE)

#define xstatusSetBarberPole(s,o) xstatusSetMax((s),  \
						(o) ? xstatusNO_VALUE : 100)



/*
 * ----- Private Function Message Definitions -----
 */

/* Here is where method dispatch macros (the things that boil down to
 * vclassSend) are defined.
 */


#define xstatusAdvanceTo(s, v) \
	vclassSend (xstatusGetClass(s), xstatusADVANCE_TO, (s, v))

#define xstatusSetMax(s, m) \
	vclassSend (xstatusGetClass(s), xstatusSET_MAX, (s, m))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* templateINCLUDED */



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

