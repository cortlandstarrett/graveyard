/* $Id: pacemake.c,v 1.2 1995/01/19 19:32:54 chad Exp $ */
/* pacemaker.c -- implementation for the pacemaker thingie
 *
 * Info on using it can be found in xpacemaker.h
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

#include <vport.h>

#ifndef  vwindowINCLUDED /* for vwindowFlushRequests */
#include vwindowHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif


#include "xpacemak.h"



/*
 * ----- Module global variable
 */

/* this is the class for the base pacemaker class.  It's not too useful
 * in-and-of-itself, so you'll probably want to subclass it to do some
 * useful work.
 */
static xpacemakerClass *g_defaultClass;




/*
 * ----- pacemaker driver
 */


/* These are the functions that handle the periodic vevent posting until
 * the pacemaker deems itself finished.
 *
 * The data pointer of the client event contains a pointer to the pacemaker
 * object.  The pacemaker object also has a reference back to the event
 * so that the data field can be cleared out if the process is terminated.
 */


/* forward reference because _xpacemakerPost and _xpacemakerEventTarget
 * use each other.  circular references are fun!
 */
static int _xpacemakerEventTarget (vevent *event);




/* _xpacemakerPost -- utility function for posting a pacemaker heartbeat event.
 *
 *  -> pacemaker -- the pacemaker object that will be called upon to do
 * 		    some work in the the near future
 *  -> event     -- if NULL, create a new event.  If non-NULL, re-use the
 * 		    event.  This event will then be posted for later execution
 */
static void _xpacemakerPost (xpacemaker *pacemaker, vevent *event)
{
    /* we're not re-using an event, so make a new one */
    if (event == NULL) {
	event = veventCreateClient ();

	veventSetTarget (event, _xpacemakerEventTarget);

	/* so we can find ourselves later */
	veventSetClientData (event, pacemaker);

	veventSetPriority (event, veventPRIORITY_MIN);
    }

    /* keep a reference around so we can clear it the client data pointer
     * later if necessary
     */
    pacemaker->paceEvent = event;

    veventPost (event);

    /* force screen update for snappier display */
    vwindowFlushRequests ();

} /* _xpacemakerPost */




/* _xpacemakerEventTarget -- the client event handler function that turns 
 *			     around and causes the pacemaker object to do some
 *			     work.
 *
 *  -> event -- the event that triggered this function getting called
 * <-        -- TRUE if we handled it, FALSE if we didn't
 */
static int _xpacemakerEventTarget (vevent *event)
{
    xpacemaker *pacemaker = (xpacemaker*) veventGetClientData (event);

    /* make sure we weren't terminated */
    if (pacemaker != NULL) {
	xpacemakerDoWork (pacemaker);

	/* make sure there's still work to do before reposting */
	if ( !xpacemakerIsFinished(pacemaker)) {

	    /* it's OK to re-use the event */
	    _xpacemakerPost (pacemaker, event);
	}
    }

    /* ""Never, EVER call veventDestroy" - lat@jpmorgan.com" - bsb@unify.com */
    
    return (TRUE);
    
} /* _xpacemakerEventTarget */


/*
 * ----- exported function
 */




/*
 * ----- method implementation
 */


/* _xpacemakerINIT -- impelemtation of the vinstanceINIT method.  Get this
 * 		      hunk of memory into shape for being a decent pacemaker
 *
 *  -> pacemaker -- the hunk of memory to initialzie
 */
static void _xpacemakerInit (xpacemaker *pacemaker)
{
    vclassSendSuper (g_defaultClass, vinstanceINIT, (pacemaker));

    /* clean ourselves off */
    pacemaker->data = NULL;
    pacemaker->flags = 0;
    pacemaker->notify = 0;
    pacemaker->paceEvent = NULL;

} /* _xpacemakerInit */




/* _xpacemakerDestroy -- free up the memory consumed by the pacemaker.
 *			 implementation of vinstanceDESTROY
 *
 *  -> pacemaker -- the pacemaker to send to its maker
 */ 
static void _xpacemakerDestroy (xpacemaker *pacemaker)
{
    /* stop it if it's currently active.  This will clear out the heartbeat
     * event's client data pointer
     */
    if (xpacemakerIsRunning(pacemaker)) {
	xpacemakerStop (pacemaker);
    }

    /* if it hasn't been terminated, terminate it with great prejudice.
     * This will result in the notification being called with the termination
     * notification. (and no, it won't be back.)
     */
    if ( !xpacemakerIsTerminated(pacemaker)) {
	xpacemakerTerminate (pacemaker);
    }

    vclassSendSuper (g_defaultClass, vinstanceDESTROY, (pacemaker));

} /* _xpacemakerDestroy */




/* _xpacemakerStart -- start the pacemaker along its merry way
 *
 *  -> pacemaker -- the pacemaker to start making paces
 */
static void _xpacemakerStart (xpacemaker *pacemaker)
{
    /* don't start it if it's already started */
    if ( !xpacemakerIsRunning(pacemaker)) {

	/* start the ball rolling with a new event */
	_xpacemakerPost (pacemaker, NULL);

	pacemaker->flags |= _xpacemakerRUNNING;
    }

} /* _xpacemakerStart */




/* _xpacemakerStop -- suspend the pacemaker.  No more work will be done unless
 *		      xpacemakerStart is called again.
 *
 *  -> pacemaker -- the pacemaker to stop in its tracks
 */
static void _xpacemakerStop (xpacemaker *pacemaker)
{
    /* don't try to stop something that's not running */
    if (xpacemakerIsRunning(pacemaker)) {

	if (pacemaker->paceEvent != NULL) {
	    /* on the next notify, make sure we don't try to access 
	     * this object 
	     */
	    veventSetClientData (pacemaker->paceEvent, NULL);
	}

	pacemaker->flags &= ~_xpacemakerRUNNING;

    }
} /* _xpacemakerStop */




/* _xpacemakerFinish -- the trick, she is done.  Mark the pacemaker as being
 * 			finished, stop the repetitive work, and notify the
 * 			notification that we're done.  Typically this will
 *			be called by the code that's doing the calcultions
 *
 *  -> pacemaker -- the pacemaker that's done with its work.
 */
static void _xpacemakerFinish (xpacemaker *pacemaker)
{
    /* don't try to finish something that's already finished */

    if ( !xpacemakerIsFinished(pacemaker)) {

	if (xpacemakerIsRunning(pacemaker)) {
	    xpacemakerStop (pacemaker);
	}
	
	pacemaker->flags |= _xpacemakerFINISHED;
	
	xpacemakerNotify (pacemaker, xpacemakerNOTIFY_FINISHED);
    }

} /* _xpacemakerFinish */




/* _xpacemakerSetData -- stuff something into the client data pointer
 *
 *  -> pacemaker -- the pacemaker to set the data pointer for
 *  -> data      -- the data to use.
 *
 * xpacemaker doesn't use this pointer, and xpacemaker subclasses shouldn't
 * use it either.  It's for the client's use only
 */
static void _xpacemakerSetData (xpacemaker *pacemaker, const void *data)
{

    pacemaker->data = data;

} /* _xpacemakerSetData */




/* _xpacemakerSetNotify -- set the notification function for the pacemaker
 *
 *  -> pacemaker -- set the notification of the pacemaker
 *  -> notify    -- the notification function to use.  Can be NULL to indicate
 * 		    no notification should be done
 */
static void _xpacemakerSetNotify (xpacemaker *pacemaker, 
				  xpacemakerNoteProc notify)
{
    pacemaker->notify = notify;
} /* _xpacemakerSetNotify */




/* _xpacemakerNotify -- call the notification function.  Folks who OO whole
 *			hogly can override this method to get the notifications
 * 			rather than messing around with a notification function
 *
 *  -> pacemaker -- the pacemaker to notify
 *  -> message   -- what the notification is about.  Built-ins are
 *		    xpacemakerNOTIFY_FINISHED -- signaling completion
 *		    xpacemakerNOTIFY_TERMINATED -- stopped early
 *                  xpacemakerNOTIFY_WORK_PERFORMED -- a hunk of work is done
 *		    subclasses can add their own types as well.
 */
static void _xpacemakerNotify (xpacemaker *pacemaker, int message)
{
    if (xpacemakerGetNotify(pacemaker) != NULL) {
	(xpacemakerGetNotify(pacemaker)) (pacemaker, message);
    }

} /* _xpacemakerNotify */




/* _xpacemakerDoWork -- do the work the pacemaker is supposed to do.
 *			xpacemaker is really an abstract superclass, so it
 *			doesn't actually *do* anything except call the 
 *			notification saying "hey -- some work's been 
 *			done here."
 *
 *  -> pacemaker -- the pacemaker that should do a slice of work
 */
static void _xpacemakerDoWork (xpacemaker *pacemaker)
{
    if ( !xpacemakerIsFinished(pacemaker)) {
	xpacemakerNotify (pacemaker, xpacemakerNOTIFY_WORK_PERFORMED);
    }
} /* _xpacemakerDoWork */




/* _xpacemakerTerminate -- stop the pacemaker before it's finished.  This
 *			   stops the event posting and calls the notification
 *			   informing it of the termination.
 *
 *  -> pacemaker -- the pacemaker being terminated
 */
static void _xpacemakerTerminate (xpacemaker *pacemaker)
{
    if ( !xpacemakerIsTerminated(pacemaker)) {
	if (xpacemakerIsRunning(pacemaker)) {
	    xpacemakerStop (pacemaker);
	}
	
	if ( !xpacemakerIsFinished(pacemaker)) {
	    xpacemakerNotify (pacemaker, xpacemakerNOTIFY_TERMINATED);
	}
	
	pacemaker->flags |= _xpacemakerTERMINATED;
    }

} /* _xpacemakerTerminate */




/* xpacemakerGetDefaultClass -- return the default pacemaker class
 *
 * <-  -- the default pacemaker class
 */
xpacemakerClass *xpacemakerGetDefaultClass (void)
{
    if (g_defaultClass == NULL) {

	/* make the class, set the method table size, the name, and
	 * the instance size
	 */
	g_defaultClass = vclassSpawn (vinstanceGetDefaultClass(),
				      sizeof(xpacemakerClass));
	vclassSetNameScribed (g_defaultClass,
			      vcharScribeLiteral("xpacemaker"));
	vclassSetObjectSize (g_defaultClass, sizeof(xpacemaker));
	
	vclassSet (g_defaultClass, /* create */
		   vinstanceINIT,
		   _xpacemakerInit);

	vclassSet (g_defaultClass, /* destroy */
		   vinstanceDESTROY,
		   _xpacemakerDestroy);
	
	vclassSet (g_defaultClass, /* start the heartbeat */
		   xpacemakerSTART,
		   _xpacemakerStart);
	
	vclassSet (g_defaultClass, /* stop the heartbeat */
		   xpacemakerSTOP,
		   _xpacemakerStop);
	
	vclassSet (g_defaultClass, /* mark the pacemaker as being done */
		   xpacemakerFINISH,
		   _xpacemakerFinish);
	
	vclassSet (g_defaultClass, /* set client-accesable data */
		   xpacemakerSET_DATA,
		   _xpacemakerSetData);
	
	vclassSet (g_defaultClass, /* set the client notification mechanism */
		   xpacemakerSET_NOTIFY,
		   _xpacemakerSetNotify);
	
	vclassSet (g_defaultClass, /* do a hunk of work */
		   xpacemakerDO_WORK,
		   _xpacemakerDoWork);
	
	vclassSet (g_defaultClass, /* early abortion by the user */
		   xpacemakerTERMINATE,
		   _xpacemakerTerminate);

	vclassSet (g_defaultClass, /* tell the client something happened */
		   xpacemakerNOTIFY,
		   _xpacemakerNotify);
    }

    return (g_defaultClass);

} /* xpacemakerGetDefaultClass */




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
