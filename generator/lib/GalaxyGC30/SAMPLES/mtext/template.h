/* template.h -- outline of how a typical Galaxy header file is structured.
 *		 you're encouraged to use this structure for your own headers.
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


#ifndef templateINCLUDED /* protect ourselves from multiple inclusion */
#define templateINCLUDED 1


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

#ifndef vresourceINCLUDED /* some prototypes will use resources */
#include vresourceHEADER
#endif

#ifndef veventINCLUDED	/* the notification needs an event */
#include veventHEADER
#endif

/* ... and other headers as needed ... */


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




/*
 * ----- Public Function Prototypes -----
 */

/* your complete exported API should be placed here.  No clue as to how
 * things are implemented should be put here.  It doesn't matter if a 
 * particular call is implemented by a macro, a method, or a direct function
 * call.  It should be put here.
 */




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



/*
 * ----- Private Function Macro Definitions -----
 */

/* entry points that are implemented by macros belong here.  Typically,
 * "Set" calls go through methods and "Get" calls are done via macros for
 * a good tradeoff between flexibility and performance.
 */




/*
 * ----- Private Function Message Definitions -----
 */

/* Here is where method dispatch macros (the things that boil down to
 * vclassSend) are defined.
 */



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

