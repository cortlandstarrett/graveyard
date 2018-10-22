/* xpacemaker.h -- a handy little tool for program-level time slicing.
 *
 * This is useful for doing things like
 *   o Providing a "stop!" button to interrupt a long calculation
 *   o Allow for user interaction with the program during a long operation
 *   o Poor-person's threads.
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

/* here's the short-and-sweet on how to use this.
 *
 * xpacemaker by itself isn't useful - the method that does the work doesn't
 * actually do anything but call a notification function saying that some
 * work has been done.
 *
 * So, what you would do is subclass xpacemaker:
 *
 * xpacemakerClass *mySubclass = vclassReproduce (xpacemakerGetDefaultClass());
 *
 * vclassSet (mySubclass, xpacemakerDO_WORK, _myWorkMethod);
 *
 * and supply a _myWorkMethod to do the work: 
 *
 * void _myWorkMethod (xpacemaker *pacemaker)
 * {
 *     ... do the work ...
 *     vclassSendSuper (mySubclass, xpacemakerDO_WORK, (pacemaker));
 * } \* _myWorkMethod *\
 *
 * Then you'd make an actual object from this class:
 *  xpacemaker *thumper = xpacemakerCreateOfClass (mySubclass);
 *
 * and start it:
 * xpacemakerStart (thumper);
 *
 * Your _myWorkMethod function will then be called repeatedly until you
 * tell it to stop with xpacemakerStop (thumper);
 *
 * note - you do need to return control to the event manager (either
 * by calling veventProcess, or returning from whatever Galaxy notification
 * or handler you're currently in) to get your work method to be called.
 *
 *
 * You (or people using your pacemaker object) can attach a notification
 * procedure so that they can keep track of how things are going:
 *
 * void somePacemakerNotifyProcedure (xpacemaker *pacemaker, int message);
 * {
 *     if (message == xpacemakerNOTIFY_WORK_PERFORMED) {
 *         ... update some visual feedback to the user
 *     } else if ( ... handle other cases as desired )
 *         ... work work work. the greatest joy is the joy of duty ...
 *     }
 * } \* somePacemakerNotifyProcedure *\
 *
 * Interesting messages are
 *   xpacemakerNOTIFY_FINISHED -- someone called xpacemakerFinish to
 *                                indicate that the work is completed, and
 * 				  the final values can now be used
 *   xpacemakerNOTIFY_TERMINATED -- someone stopped the calculations early
 *				    via xpacemakerTerminate.  Time to clean
 *				    up whatever has been allocated to show
 *				    work progress (such as a dialog showing
 *				    a progress meter)
 *   xpacemakerNOTIFY_WORK_PERFORMED -- update visual feedback, or whatever
 *					else is appropriate
 *
 * You can query the pacemaker as to its current status:
 *   xpacemakerIsRunning (pacemaker) -- is it currently doing work?
 *   xpacemakerIsFinished (pacemaker) -- has it run to completion?
 *   xpacemakerIsTerminated (pacemaker) -- was it stopped early?
 *
 * There is a data pointer for clients (the people using your xpacemaker
 * subclass) to use.  This is not for your use.  If you need extra state
 * information, you'll need to increase the size of your object and 
 * keep the data there.
 *
 * xgroup.h shows subclassing along with adding extra state data (as well
 * as some extra methods to support the group operation.)
 */




#ifndef xpacemakerINCLUDED
#define xpacemakerINCLUDED


/* #include headers *only* for things referenced in this header file. Don't
 * #include stuff that will only be used for the implementation.
 *
 * Some headers are included for documentation/completeness purposes.
 * vdialogHEADER pulls in vclass, vevent, vresource etc...  Because of
 * the vspamINCLUDED definitions, we prevent the reading and skipping over
 * of huge amounts of now-unnecessary text.
 */

#ifndef vportINCLUDED /* get our vspamHEADER symbols */
#include <vport.h>
#endif

#ifndef vclassINCLUDED /* well, we *are* doing subclassing here */
#include vclassHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif



vportBEGIN_CPLUSPLUS_EXTERN_C

/*

 * ----- Public Constant Definitions -----
 */

/* this is where you export constants, symbols, enums, #defines, and
 * vnames that your clients are allowed to use
 */

enum {
    xpacemakerNOTIFY_FINISHED,
    xpacemakerNOTIFY_TERMINATED,
    xpacemakerNOTIFY_WORK_PERFORMED, /* for tracking incremental changes */
    xpacemakerNEXT_NOTIFY
};



/*
 * ----- Public Type Definitions -----
 */

/* here is where you export structures that your clients have permission
 * to touch.  (vrect is an example of this).  Think long and hard about
 * what structures you export, since you'll be forever tied to supporting
 * those structures, as well as giving bad programmers an excuse to mess
 * with your structure innards at inopportune moments.
 * IMNSO, things like the vtext exported structures are a very Bad Thing and
 * can only cause trouble.
 */

/* here is where you also export your typedefs for your objects and classes.
 * What you're doing is setting up forward references to the real structure
 * definitions that occur later in the file.  These forward references are
 * necessary so that the function prototypes make sense and will compile
 * without compiler complaints.
 * Exported in this place are types for notify functions.
 */

typedef struct xpacemaker xpacemaker;
typedef struct xpacemakerClass xpacemakerClass;

typedef void (*xpacemakerNoteProc) (xpacemaker *pacemaker, int message);



/*
 * ----- Public Function Prototypes -----
 */

/* your complete exported API should be placed here.  No clue as to how
 * things are implemented should be put here.  It doesn't matter if a 
 * particular call is implemented by a macro, a method, or a direct function
 * call.  It should be put here.
 */


xpacemakerClass *xpacemakerGetDefaultClass (
    void
    );

xpacemaker *xpacemakerCreate (
    void
    );

xpacemaker *xpacemakerCreateOfClass (
    xpacemakerClass *clas
    );				 

void xpacemakerDestroy (
    xpacemaker *pacemaker
    );

void xpacemakerDestroyLater (
    xpacemaker *pacemaker
    );

xpacemakerClass *xpacemakerGetClass (
    xpacemaker *pacemaker
    );


void xpacemakerSetNotify (
    xpacemaker *pacemaker,
    xpacemakerNoteProc notify
    );

xpacemakerNoteProc xpacemakerGetNotify (
    xpacemaker *pacemaker
    );


void xpacemakerStart (
    xpacemaker *pacemaker
    );

void xpacemakerStop ( /* call xpacemakerTerminate to abort the process */
    xpacemaker *pacemaker,
    int message
    );

void xpacemakerFinish (  /* so we know we've completed normally */
    xpacemaker *pacemaker
    );

vbool xpacemakerIsRunning (
    xpacemaker *pacemaker
    );

vbool xpacemakerIsFinished (
    xpacemaker *pacemaker
    );

vbool xpacemakerIsTerminated (
    xpacemaker *pacemaker
    );



void xpacemakerSetData (
    xpacemaker *pacemaker,
    const void *data
    );

const void *xpacemakerGetData (
    xpacemaker *pacemaker
    );



/*
 * --- stuff for you to override
 */

void xpacemakerDoWork (
    xpacemaker *pacemaker
    );

/* do clean-up here.  Will get called when the pacemaker is destroyed */
void xpacemakerTerminate (
    xpacemaker *pacemaker
    );




/*
 * ----- Private Constant Definitions -----
 */

/* semi-private flag symbols (such as flag field values) should be placed here,
 * as well as private symbols that are referenced in macros.
 */

enum {
    _xpacemakerRUNNING    = 0x0001,
    _xpacemakerTERMINATED = 0x0002,
    _xpacemakerFINISHED   = 0x0004
};



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

struct xpacemaker {
    vinstance 	       instance; /*we're a very minimal object */
    unsigned short     flags;	 /* running, terminated, or finished */
    vevent            *paceEvent;/* what's driving our work right now */
    const void        *data;     /* for client's use */
    xpacemakerNoteProc notify;   /* for client's use */
};

#define xpacemakerCLASS(CLASS, PACEMAKER, NOTIFY)                             \
    vinstanceCLASS (CLASS, PACEMAKER);                                        \
    vclassMETHOD (xpacemakerSTART, (PACEMAKER *pacemaker));                   \
    vclassMETHOD (xpacemakerSTOP, (PACEMAKER *pacemaker));                    \
    vclassMETHOD (xpacemakerSET_DATA, (PACEMAKER *pacemaker,                  \
				       const void *data));                    \
    vclassMETHOD (xpacemakerSET_NOTIFY, (PACEMAKER *pacemaker,                \
					 NOTIFY notify));                     \
    vclassMETHOD (xpacemakerNOTIFY, (PACEMAKER *pacemaker, int message));     \
    vclassMETHOD (xpacemakerFINISH, (PACEMAKER *pacemaker));                  \
    vclassMETHOD (xpacemakerDO_WORK, (PACEMAKER *pacemaker));                 \
    vclassMETHOD (xpacemakerTERMINATE, (PACEMAKER *pacemaker))

struct xpacemakerClass {
    xpacemakerCLASS (xpacemakerClass, xpacemaker, xpacemakerNoteProc);
};




/*
 * ----- Private Function Macro Definitions -----
 */

/* entry points that are implemented by macros belong here.  Typically,
 * "Set" calls go through methods and "Get" calls are done via macros for
 * a good tradeoff between flexibility and performance.
 */

#define _xpacemakerGetInstance(p) \
	(&(p)->instance)

#define xpacemakerGetClass(p) \
	((xpacemakerClass*)vinstanceGetClass(_xpacemakerGetInstance(p)))

#define xpacemakerCreateOfClass(c)  \
	((xpacemaker*)vinstanceCreateOfClass ((vinstanceClass*)(c)))

#define xpacemakerCreate() \
	xpacemakerCreateOfClass (xpacemakerGetDefaultClass())

#define xpacemakerDestroyLater(p) \
	vinstanceDestroyLater (_xpacemakerGetInstance((p)))

#define xpacemakerGetData(p) \
	((p)->data)

#define xpacemakerIsRunning(p) \
	( ((p)->flags & _xpacemakerRUNNING) != 0 )

#define xpacemakerIsFinished(p) \
	( ((p)->flags & _xpacemakerFINISHED) != 0 )

#define xpacemakerIsTerminated(p) \
	( ((p)->flags & _xpacemakerTERMINATED) != 0 )

#define xpacemakerGetNotify(p) \
	( (p)->notify )




/*
 * ----- Private Function Message Definitions -----
 */

/* Here is where method dispatch macros (the things that boil down to
 * vclassSend) are defined.
 */

#define xpacemakerDestroy(p) \
	vclassSend (xpacemakerGetClass(p), vinstanceDESTROY, (p))

#define xpacemakerStart(p) \
	vclassSend (xpacemakerGetClass(p), xpacemakerSTART, (p))

#define xpacemakerStop(p) \
	vclassSend (xpacemakerGetClass(p), xpacemakerSTOP, (p))

#define xpacemakerFinish(p) \
	vclassSend (xpacemakerGetClass(p), xpacemakerFINISH, (p))

#define xpacemakerSetData(p, d) \
	vclassSend (xpacemakerGetClass(p), xpacemakerSET_DATA, (p, d))

#define xpacemakerSetNotify(p, n) \
	vclassSend (xpacemakerGetClass(p), xpacemakerSET_NOTIFY, (p,n))

#define xpacemakerDoWork(p) \
	vclassSend (xpacemakerGetClass(p), xpacemakerDO_WORK, (p))

#define xpacemakerTerminate(p) \
	vclassSend (xpacemakerGetClass(p), xpacemakerTERMINATE, (p))

#define xpacemakerNotify(p,m) \
	vclassSend (xpacemakerGetClass(p), xpacemakerNOTIFY, (p, m))



vportEND_CPLUSPLUS_EXTERN_C



#endif /* xpacemakerINCLUDED */


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
