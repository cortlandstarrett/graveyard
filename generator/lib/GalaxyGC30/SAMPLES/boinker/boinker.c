/* $Id: boinker.c,v 1.7 1996/08/21 15:39:24 david Exp $ */
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
 *     o 05-04-95: ssmc, a. updated to filter rotated fonts from prefs font   *
 *                          chooser and boinking label item                   *
 *                       b. updated to not change colors if monochrome        *
 *                       c. saves/restores position of main window in prefs   *
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

/*
 *+------------------------------------------------------------------------+
 * dependencies:
 *+------------------------------------------------------------------------+
 */

#include <vport.h>
#include vstdlibHEADER
#include vstdioHEADER
#include vmathHEADER
#include vlimitsHEADER
#include vtimeHEADER
#include vdebugHEADER
#include vexHEADER
#include vscribeHEADER
#include vnameHEADER
#include vdictHEADER
#include vresourceHEADER
#include vtimestampHEADER
#include veventHEADER
#include vclientHEADER
#include vclassHEADER
#include vinstanceHEADER
#include vstdHEADER
#include vfontHEADER
#include vobjectHEADER
#include vcommandHEADER
#include vnumHEADER
#include vprefHEADER
#include vapplicationHEADER
#include vdialogHEADER
#include vtextitemHEADER
#include vcontrolHEADER
#include vconfirmHEADER
#include vnoticeHEADER
#include vfontchsrHEADER
#include vstartupHEADER
#include vtestHEADER

#include "ttask.h"
#include "boink.h"



#if (vdebugDEBUG)
static const char *const _debugTag = "BOinKeR";
#define vdebugTAG _debugTag
#endif



/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */


enum {
	_HUNK    = 1,
	_LOOPS   = 100000,
	_chgSTR  = 0x01,
	_chgFONT = 0x02,
	_chgGEO  = 0x04
};

enum {
	strTitle,
	strBusy,
	strLoadingWindows,
	strLoadingFonts,
	strLoadingColors,
	strBoinking
};




/* */
typedef struct ABoinkerPrefs ABoinkerPrefs;
typedef struct ABoinker ABoinker;

struct ABoinker {
	ttaskExternalClass	*startuptaskClass;
	ttaskClass			*boinktaskClass;
	vfontchsrClass		*fontchsrClass;

	vapplication		*vapp;
	vresource			 resources;
	
	unsigned long		 loops;
	double				 IEEEbits;
	ttaskExternal		*pending;

	vdialog				*splash;
	vdialog				*dialog;

	vconfirm			*prefs;
	ABoinkerPrefs		*prefvalues;

	vcolorPalette		*palette;
	unsigned 	 		 numcolors;
	unsigned long		 nextcolor;
	
	vfont		   	   **fonts;
	unsigned			 numfonts;
	ttask		 		*task;

	vnotice				*errUI;
	const char			*errLoc, *errWhy;
	char				 errBuf[1024]; /* !snort <weeze> */

	vstr				*userstring;
	vstr				*titleTemplate;
	unsigned			 enumfonts:1;
	unsigned			 randomcolors:1;
	unsigned			 randomgeo:1;
	unsigned 			 teehee:1;
	unsigned			 silent:1;
	unsigned			 accumulate:1;
};


struct ABoinkerPrefs {
	ABoinker	*boinker;
	vstr		*userstring;
	vfont		*font;
	vfontchsr	*chizler;
	unsigned 	 randomgeo:1;
	unsigned	 changes:5;
};



/* */
static ABoinker     gBoinker= {0};
static const vname *tag_iBoink, 
	               *tag_iBoinkTNG,
	               *tag_sReplace;


/* */
static void AHelp(ABoinker*);
static void AStartup(ABoinker*);
static void AShutdown(ABoinker*);
static void ABoinkTaskExecute(ttask*);
static void ABoinkTaskIgnoreAdvance(ttask*, unsigned short);
static unsigned ABoinkTaskForever(ttask*);
static void ATauntUser(ttaskExternal*,const void*);
static void ATaskInform(ABoinker*, const vchar*);
static void ASaveLayout(ABoinker*);

/*
 *+-------------------------------------------------------------------------+
 * Our Boink Exception Class
 *
 * We create a special subclass of the vexAbandonException to signal
 * stoppage if the user only wants help (ala the -help option) at
 * startup.
 *
 *+-------------------------------------------------------------------------+
 */

#define AGetOnlyHelpException() 		\
	vexGetExceptionOfClass(&__ABoinkerNoRunExceptionClass)

#define AGenerateOnlyHelpException()	\
	vexGenerate(&__ABoinkerNoRunExceptionClass, vexNULL)

#define AInitializeExceptionClasses() \
	vexInitClass(&__ABoinkerNoRunExceptionClass, vexGetAbandonClass(), \
				 "Only Want Help", sizeof(ABoinkerNoRunException),     \
				 (vexDumper)NULL)

typedef vexAbandonException ABoinkerNoRunException;
static vexClass __ABoinkerNoRunExceptionClass = {0};



/*
 *+-------------------------------------------------------------------------+
 * Useful Macros:
 *
 * 	ACenterDialog() - position the given dialog in the center of the primary
 *	  display.
 *
 *  AForceConfirmVisible() - force the given confirm window to be visible;
 *    this implies uniconifying (sp?!) and raising the window if necessary.
 *
 *  TAG(), SCRIBE() - cause i hate typing
 *
 *  TheBoinker() - return reference to the global ABoinker structure (would
 *     be nice if we could actually use a subclass of vapplication...)
 *
 *+-------------------------------------------------------------------------+
 */

/*  */
#define TAG(_l) 		vnameInternGlobalLiteral(_l)
#define SCRIBE(_l) 		vcharScribeLiteral(_l)
#define TheBoinker()	(&gBoinker)


/* */
#define ACenterDialog(argDLOG)	\
	vdialogPlaceWindow((argDLOG), vwindowGetRoot(), \
			     vrectPLACE_CENTER, vrectPLACE_CENTER)

#define AForceConfirmVisible(argCONF)	\
	( vwindowUniconify(vdialogGetWindow(vconfirmGetDialog(argCONF))), \
	  vwindowRaise(vdialogGetWindow(vconfirmGetDialog(argCONF))) )


/*
 *+-------------------------------------------------------------------------+
 * Handling Exceptions:
 *
 * We provide a simple exception handler mechanism to capture exceptions.
 * Note: this is not a portable or language/OS independent mechanism. It
 * does however, give the user a better clue about the exception's cause.
 *
 * 	ANoteTRY() - register a location and optional reason before trying
 *	  something that could generate an exception.
 *
 *  AHandleError() - for uncaught top-level exception, prints our 
 *    location and reason information. Called by main()'s exception 
 *	  handler. !Woot-Woot! this routine has some *BIG-FAT-n-HAIRY* 
 *    assumptions about the runtime character set...
 *
 *  AInitErrorUI() - creates a error notice either from resource or
 *    from scratch
 *
 *+-------------------------------------------------------------------------+
 */

/* */
#define ANoteTRY(_LOC, _WHY) \
	(gBoinker.errLoc = _LOC, gBoinker.errWhy = _WHY)

#define ANoteLOC(_LOC) 	ANoteTRY(_LOC, NULL)



/* */
static void AHandleError(ABoinker *boinker)
{
	if (AGetOnlyHelpException()) /* this is okidoki to ignore */
		return;

	if (boinker->errLoc && boinker->errWhy)
		(void)sprintf(boinker->errBuf, "Because of %s BOiNkeR has fallen %s.",
					  boinker->errWhy, boinker->errLoc);
	else
	if (boinker->errLoc)
		(void)sprintf(boinker->errBuf, "BOiNkeR has fallen %s.",
					  boinker->errLoc);
	else
	if (vexGetRootException())
	{
		const char *msg = vexGetMessage(vexGetRootException());
		if (!msg || !*msg) 
			msg = "X-(";
		(void)sprintf(boinker->errBuf, "Red Alert! %s", msg);
	}
	else
		(void)strcpy(boinker->errBuf, 
			"BOiNkeR has fallen and it can't get up!");

	if (boinker->errUI)
		{
			register vnotice *notice = boinker->errUI;
			vnoticeSetTextScribed(notice, SCRIBE(boinker->errBuf));
			ACenterDialog(vnoticeGetDialog(notice));
			(void)vnoticeProcess(notice);
		}
	else
		{
			register FILE *fp = vdebugGetWarningStream();
			fprintf(fp, "%s\n", boinker->errBuf);
			fflush(fp);
		}
}



/* */
static void AInitErrorUI(ABoinker *boinker, const vname *tag)
{
	vresource res;

	ANoteTRY("loading error notice", "bad resources");

	if (vresourceTestGet(boinker->resources, tag, &res) &&
		vresourceType(res)==vresourceDICT)
		{
			boinker->errUI = vnoticeLoad(res);
		}
	else
		{
			register vnotice *notice = vnoticeCreate();
			vnoticeSetTitleScribed(notice, SCRIBE("Ooops"));
			boinker->errUI = notice;
		}
}



/*
 *+-------------------------------------------------------------------------+
 * Our Task Classes
 *
 * We override the default external class st we don't ignore any required 
 * starup tasks (like loading the windows). We create a subclass of the 
 * standard ttask class for boinkisizing our main window.
 *
 *  AStartupTaskNoteError() - regenerates an exception if the failed 
 *	  task is a "required" task (as in required for application to work)
 *
 *  ATaskMakeClasses() - fills in the class mangler's slots for our
 * 	  task subclasses
 *
 *+-------------------------------------------------------------------------+
 */


/* */
static void AStartupTaskNoteError(ttaskExternal *task, 
			ttaskExternalProcPtr proc, const void *data, const vchar *name)
{
	if (proc != ATauntUser)
		{
			ANoteTRY(NULL, NULL);
			ttaskGenerateState(task, "required task failed.");
		}
	else
		vclassSendSuper(TheBoinker()->startuptaskClass, 
				ttaskExternalNOTE_ERROR, (task, proc, data, name));
}



/* */
static void ATaskMakeClasses(ABoinker *boinker)
{
	register ttaskExternalClass *eclas;
	register ttaskClass *tclas;

	srand((unsigned int)time((time_t)NULL));
	(void)BoinkitemGetDefaultClass();

	ANoteLOC("initializing startup task class");
	eclas = vclassReproduce(ttaskExternalGetDefaultClass());
	vclassSetNameScribed(eclas, SCRIBE("StartupTasks"));
	vclassSet(eclas, ttaskExternalNOTE_ERROR, AStartupTaskNoteError);
	boinker->startuptaskClass = eclas;
	
	ANoteLOC("initializing boink task class");
	tclas = vclassReproduce(ttaskGetDefaultClass());
	vclassSetNameScribed(tclas, SCRIBE("BOinK"));
	vclassSet(tclas, ttaskEXECUTE, ABoinkTaskExecute);
	vclassSet(tclas, ttaskGET_AGAIN, ABoinkTaskForever);
	vclassSet(tclas, ttaskADVANCE, ABoinkTaskIgnoreAdvance);
	boinker->boinktaskClass = tclas;
}



/*
 *+-------------------------------------------------------------------------+
 * Utility Procedures:
 *
 * Routines to set the user-configurable boink properties: font and string.
 * User can set font/string at startup or through preferences.
 *
 *	ASetBaseFont() - update the base font family (boink uses random font
 *	  from family)
 *
 *  ASetString() - update the boink-string
 *
 *  AUseFont() - return non-zero if can display the given font
 *
 *+-------------------------------------------------------------------------+
 */

/* */
#define AUseFont(argFONT) \
	(vfontIsUpright(argFONT) && vfontIsSquare(argFONT))



/* */
static void ASetBaseFont(ABoinker *boinker, vfont *itemFont)
{
	register vfontFace	*nextFace;
	register int		 i,j;
	vfontFamily			*family;
	register int		 numFaces, numFonts;
	register vfont	   **fonts;

	ANoteLOC("calculating buffer size for boink fonts");
	family   = vfontGetFaceFamily(vfontGetFace(itemFont));
	numFaces = vfontGetFamilyFaceCount(family);
	for (i=0, numFonts=0; i<numFaces; i++)
		{
			nextFace  = vfontGetFamilyFaceAt(family, i);
			numFonts += vfontGetFaceFontCount(nextFace);
		}

	ANoteLOC("allocating buffer for boink fonts");
	fonts = (vfont**)vmemAllocAndClear(numFonts*sizeof(vfont*));
  	boinker->fonts    = fonts;
  	boinker->numfonts = (unsigned)numFonts;

	ANoteLOC("retrieving vfonts for boink fonts");
	for (i=0; i<numFaces; i++)
		{
			nextFace = vfontGetFamilyFaceAt(family, i);
			numFonts = vfontGetFaceFontCount(nextFace);
			for (j=0; j<numFonts; j++)
				{
					*fonts = vfontGetFaceFontAt(nextFace, j);
					if (AUseFont(*fonts)) {
						if (boinker->enumfonts) {
							ATaskInform(boinker, vfontGetName(*fonts));
							vwindowFlushRequests();
						}
						fonts++;
					}
					else {
						boinker->numfonts--;
					}
				}
		}
}



/* */
static void ASetString(ABoinker *boinker, const vchar *str)
{
	vdialogItem	*item;
	vscribe 	*scribe;
	vstr    	*rtitle;
	
	ANoteLOC("processing -str preference");
	item = vdialogFindItem(boinker->dialog, tag_iBoink);
	vdialogSetItemTitle(item, str);
	item = vdialogFindItem(boinker->dialog, tag_iBoinkTNG);
	vdialogSetItemTitle(item, str);
	
	rtitle = vstrClone(boinker->titleTemplate);
	scribe = vcharScribeReplace
		(rtitle, tag_sReplace, str);
	vdialogSetTitleScribed(boinker->dialog, scribe);
	vstrDestroy(rtitle);
}



/*
 *+-------------------------------------------------------------------------+
 * Initialization Procedures:
 *
 * Do the misc initialization associated with Boink AS WELL AS waste CPU
 * time to allow user time to "see" how the splash dialog works!
 *
 *	ATaskInform() - update string in splash, telling user what part
 *	  we're currently doing...
 *
 *  ADetermineHunkOfTime() - does a weeny determination of wasting
 *	  about "Hunk" secs of CPU time...can use -hunk preference to
 *    tune at runtime
 *
 *	AWasteHunkOfTime() - does just this...wastes CPU time. We use
 *	  this to create a portable delay mechanism.
 *
 *	ATauntUser() - display a  string telling user what part of our
 *    morning we're currently doing (wastes a hunk of time). A real 
 *	  application would have something useful(?) to do here...
 *
 *	ALoadTaunters() - this loads the initialization strings that
 *	  will be displayed in the splash dialog.
 *
 *	AInitFonts() - yippee a *real* initialization routine! inits
 *	  all the fonts used by the application. We locate all the fonts
 *	  associated with the boink-item's default font (all available
 *	  styles and sizes for the font's family). The fonts are saved
 *	  in the global boinker object.
 *
 *	AInitColors() - initializes all the colors used by the application
 *	  We create a palette of colors covering all the primary colors (rgb)
 *	  with a ramp between each. The palette is stored in the global 
 *	  ABoinker structure.
 *
 *	AStartBOiNkTask() - this installs the task which "boinkisizes"
 *	  our dialog item. The task is coded to go off every 1/3 second 
 *	  although the actual time between updates depends on the user's
 *	  system, display, etc.
 *
 *+-------------------------------------------------------------------------+
 */


/* */
static void ATaskInform(ABoinker *boinker, const vchar *description)
{
	vdialogItem *item;

	if (boinker->silent || !boinker->splash)
		return;

	ANoteTRY(NULL, NULL);

	item = vdialogFindItem(boinker->splash, TAG("iTaunt"));
	vdebugIF(item==NULL, vexGenerate(vexGetValueNullClass(),
			 vexMESSAGE, "task-inform: NULL taunt item!", vexNULL));
	
	vdialogSetItemTitle(item, description);
	vdialogInvalItem(item, vwindowINVAL_UPDATE);
}



/* */
static void ADetermineHunkOfTime(ABoinker *boinker, unsigned hunks)
{
	vtimestamp		  		a, b;
	unsigned long volatile  i;		/* try to prevent optimizations */
	long					secs;
	unsigned long			x;

	hunks = vMAX(_HUNK, hunks);

	a = vtimestampGetNow();
	for (i=0, boinker->IEEEbits= vmath2PI; i<_LOOPS; i++)
		boinker->IEEEbits += vmathPI;
	b = vtimestampGetNow();
	
	vtimestampDiffer(b, a, &secs, &x);
	if (!secs) secs= 1; 			/* oooouu...fast! */
	
	boinker->loops = (unsigned long)
		((double)_LOOPS * ((double)hunks/(double)secs));
}



/* */
static void AWasteHunkOfTime(ABoinker *boinker)
{
	unsigned long volatile  i;		/* try to prevent optimizations */
	unsigned long			n = boinker->loops;

	for (i=0, boinker->IEEEbits= vmath2PI; i<n; i++)
		boinker->IEEEbits += vmathPI;
}



/* */
static void ATauntUser(ttaskExternal *task, const void *data)
{
	ABoinker *boinker = (ABoinker*)data;

	ATaskInform(boinker, ttaskExternalGetDescription(task));

	ANoteTRY("taunting user", "continental drift");
	AWasteHunkOfTime(boinker);
}



/* */
static void ALoadTaunters(ABoinker *boinker, ttaskExternal *task)
{
	const vname	*taunt;
	vresource 	 res;
	unsigned	 i,num;

	ANoteTRY("loading the taunts", "kaput resources");
	res = vresourceGet(boinker->resources, TAG("Taunts"));
	num = vresourceCountComponents(res);

	for (i=0; i<num; i++)
		{
			taunt = vresourceGetTagAt(res, i);
			ttaskExternalAdd(task, ATauntUser, boinker, taunt);
		}
}



/* */
static void AInitFonts(ttaskExternal *task, const void *data)
{
	ABoinker 			*boinker = (ABoinker*)data;
	vdialogItem			*item;

	ATaskInform(boinker, ttaskExternalGetDescription(task));

#if (vdebugDEBUG)
	ANoteTRY("initializing fonts", "missing boink item(s)");
	if (vdialogFindItem(boinker->dialog, tag_iBoinkTNG)==NULL ||
		vdialogFindItem(boinker->dialog, tag_iBoink)==NULL)
		vexGenerate(vexGetValueNullClass(), vexMESSAGE, 
					"init-fonts: NULL boink item(s)!", vexNULL);
#endif

	item = vdialogFindItem(boinker->dialog, tag_iBoink);
	ASetBaseFont(boinker, vdialogDetermineItemFont(item));
	
	item = vdialogFindItem(boinker->dialog, tag_iBoinkTNG);
	if (boinker->userstring)
		ASetString(boinker, boinker->userstring);
	else {
		vstr *s= vstrClone(vdialogGetItemTitle(item));
		ASetString(boinker, s);
		vstrDestroy(s);
	}
	BoinkitemRandomizeGeometry((Boinkitem*)item, boinker->randomgeo);
}



/* */

#define NUM_FOR_BOINK_MAGIC	  5 /* 3 primaries + 2 transitions */
#define NUM_GRADIATIONS		  10


static void AInitColors(ttaskExternal *task, const void *data)
{
	register ABoinker		*boinker= (ABoinker*)data;
	register unsigned int	 i,j;
	register vcolorSpec		*cspec;
	register vcolorPalette	*pal;
	int						 palsize;
	register float	         nudge;
	vdialogItem				*item;

	ATaskInform(boinker, ttaskExternalGetDescription(task));

	/* 
	 * WHY: The boink item will be colored in sequence with the
	 * palette color (black->b->g->r); then the process will
	 * be done going in the opposite direction (r->g->b->black);
	 * then we start the whole thing over...way cool huh!?!
	 *
	 * METHOD: To git a primary color we must first add it
	 * to the existing color, then subtract the color that was
	 * there in the first place. We always have at least one
	 * primary color "there" to that we get the transfer 
	 * from one primary color to the next without first going
	 * back to black.
	 *
	 * We choose the color "blue" as the starting primary color,
	 * so initially we must convert our blank slate (black)
	 * to blue.
	 *
	 * We only need to create the black->b->g->r palette. We
	 * use NUM_GRADIATIONS to ramp from one primary to the next
	 * so the transitions aren't so dramatic.
	 *
	 */

	ANoteLOC("creating boink colors");
	pal = vcolorCreatePalette();
	palsize = NUM_FOR_BOINK_MAGIC*NUM_GRADIATIONS;
	vcolorSetPaletteSize(pal, palsize);

	/* "difference" between palette entries */
	nudge = 1.0/(float)NUM_GRADIATIONS;

	/* starting from black (no colors) */
	cspec = vcolorGetPaletteSpecAt(pal, 0);
	vcolorFSetSpecRGB(cspec, 0.0, 0.0, 0.0);
	i=1; /* !!! NOT 0 !!! */
	
	/* to b by: adding b to no colors(ie, black) */
	for (j=1; j<=NUM_GRADIATIONS; i++,j++)
		{
			cspec = vcolorGetPaletteSpecAt(pal,i);
			vcolorFSetSpecRGB(cspec, 0.0, 0.0, (float)j*nudge);
		}

	/* to g by: adding g then removing b */
	for (j=1; j<=NUM_GRADIATIONS; i++,j++)
		{
			cspec = vcolorGetPaletteSpecAt(pal,i);
			vcolorFSetSpecRGB(cspec, 0.0, (float)j*nudge, 1.0);
		}
	for (j=NUM_GRADIATIONS-1; j; i++,j--)
		{
			cspec = vcolorGetPaletteSpecAt(pal,i);
			vcolorFSetSpecRGB(cspec, 0.0, 1.0, (float)j*nudge);
		}
	
	/* to r by: adding r then removing g */
	for (j=1; j<=NUM_GRADIATIONS; i++,j++)
		{
			cspec = vcolorGetPaletteSpecAt(pal,i);
			vcolorFSetSpecRGB(cspec, (float)j*nudge, 1.0, 0.0);
		}
	for (j=NUM_GRADIATIONS-1; j; i++,j--)
		{
			cspec = vcolorGetPaletteSpecAt(pal,i);
      		vcolorFSetSpecRGB(cspec, 1.0, (float)j*nudge, 0.0);
		}

	/* let paranoia reigh...*/
	vdebugMessagedAssert((i==(unsigned)palsize-1),
			"Checksum Palette Size -- Incorrect Tabulation!");

	boinker->palette   = pal;
	boinker->numcolors = palsize;


	/* we want to start at black, so make sure our item's color
	 * is black */
	ANoteTRY("initializing boink color", "missing boink item");

	item = vdialogFindItem(boinker->dialog, tag_iBoink);
	vdebugIF(item==NULL, vexGenerate(vexGetValueNullClass(),
			 vexMESSAGE, "load-fonts: NULL boink item!", vexNULL));

	vdialogSetItemForeground(item, vcolorGetBlack());
}



/* */

#define _NSECS_INTERVAL 330000000	/* boink every ~1/3 sec */

static void AStartBOiNkTask(ttaskExternal *task, const void *data)
{
	ABoinker		*boinker = (ABoinker*)data;
	register ttask	*boink;
	vtimestamp		 delay;

	/* Create boink task */
	ANoteLOC("initializing boink task");
	boink = ttaskCreateOfClass(boinker->boinktaskClass);

	delay = vtimestampMake(0, _NSECS_INTERVAL);
	ttaskSetMinDelay(boink, &delay);
	ttaskSetMaxIterations(boink, USHRT_MAX-1);

	ttaskDescribeAs(boink, ttaskExternalGetDescription(task)); 

	/* Store our task for later destruction. 
	 * Start boinkisizing soon...
	 */
	boinker->task      = boink;
	boinker->nextcolor = 0;
	boinker->pending   = NULL;

	ttaskPost(boink);
}



/*
 *+--------------------------------------------------------------------------+
 * BOINK! BOINK! BOINK! BOINK! BLORF!...?!
 *
 * Change the boink-item's font and color to one of our values. We choose
 * randomly from our global tables. Called by boink task.
 *
 *+--------------------------------------------------------------------------+
 */


/* */
static void ABoinkTaskIgnoreAdvance(ttask *task, unsigned short ignored)
{
	/*
	 * No-Op...
	 */
}



/* */
static unsigned ABoinkTaskForever(ttask *task)
{
	/*
	 * Go forever...
	 */
	return vTRUE;
}



/* */
static void ABoinkTaskExecute(ttask *task)
{
    ABoinker		*boinker = TheBoinker();
    int		 		 next;
    vdialogItem		*item;

    /*
     * Find item to "boinkisize" 
     * NOTE: If the dialog hasn't opened yet, don't do
     * anything!
     */
    ANoteLOC("preparing to Boink attributes");

    if (!vdialogIsOpen(boinker->dialog) || !boinker->fonts)
        return;

    item= vdialogFindItem(boinker->dialog, tag_iBoink);


    /*
     * Switch colors...
     */
    if (!vwindowIsMonochrome() && boinker->palette)
        {
            vcolorSpec *cspec;
            int index;
            ANoteLOC("Boinkisizing color");
            index = boinker->randomcolors ? rand()%boinker->numcolors
            	   : (boinker->nextcolor++ % boinker->numcolors);
            cspec = vcolorGetPaletteSpecAt(boinker->palette, index);
            vdialogSetItemForeground(item, vcolorInternSpec(cspec));
        }


    /*
     * Switch fonts. Select randomly from what we loaded.
     */
	if (boinker->numfonts>0)
		{
			ANoteLOC("Boinkisizing font");
			next = rand() % boinker->numfonts;
			vdialogSetItemFont(item, boinker->fonts[next]);
		}

	ANoteTRY(NULL,NULL);
}



/*
 *+-------------------------------------------------------------------------+
 * Commands We Understand (and their Utils):
 *
 * We understand a couple o' commands (just to spice up the sample :))
 *
 *	AQuit() - stops event processing for our application.
 *	  Called if user closes the boink window or selection "Quit" from
 *	  the UI.
 *
 *	APrematureQuit() - basically quit but from the initial splash window.
 *	  Called if user closes the splash window during startup.
 *
 *	AClear() - clears the current boink canvas; query determines whether
 *	  this command applies (No if not a cumulative canvas...)
 *
 *  AAccumulate() - toggles accumulation on/off for boink canvas; query
 *	  determines value based on the global ABoinker information.
 *
 *  AAbout() - opens the "Help" window (same as with -help option)
 *
 *  AEditPrefs() - opens the boinker Preferences window
 *  AUpdatePrefs() - updates boinker items with the user's new preferences
 *
 *  AUsePrecannedStr() - use a precanned string for boinker item
 *
 *  AInitDialogCommands() - utility routine to setup a command space in
 *    a window based on vcommandFunctionTemplates.
 * 
 *  APrefsFontChooserFilter - filter scaled/rotated fonts from the
 *    font chooser.
 *+-------------------------------------------------------------------------+
 */

/* */
static void AInitDialogCommands(vdialog *dialog, 
					const vcommandFunctionTemplate* tmpls, unsigned size)
{
	vdict *dict;
	vcommandSpace *space;

	dict  = vcommandCreateDictFunctionTemplates(tmpls, size);
	space = vcommandCreateSpace();
	vcommandAddSpaceDictOwned(space, vname_Command, dict);
	vwindowSetSpaceOwned(vdialogGetWindow(dialog), space);
}



/* */
static int APrematureQuit(vdialog *splash, vevent *ignored)
{
	veventStopProcessing();
	return vFALSE;
}



/* */
static int AQuit(vcommandFunction *cmd, vdict *context)
{
	ASaveLayout(TheBoinker());
	veventStopProcessing();
	return vTRUE;
}



/* */
static int AClear(vcommandFunction *cmd, vdict *context)
{
	vdialogItem *item = vdialogFindItem(TheBoinker()->dialog, tag_iBoinkTNG);
	
	BoinkitemClear((Boinkitem*)item);
	vdialogInvalItem(item, 0);

	return vTRUE;
}

static int AClearQuery(vcommandFunction *cmd, vdict *context)
{
	ABoinker *boinker = TheBoinker();
	
	vdictStore(context, vname_State, 
			   boinker->accumulate ? vname_Enabled : vname_Disabled);
	return vTRUE;
}



/* */
static int AAccumulate(vcommandFunction *cmd, vdict *context)
{
	ABoinker *boinker = TheBoinker();
	unsigned on = vdictLoad(context, vname_Toggle)==vname_On;
	vdialogItem *item = vdialogFindItem(boinker->dialog, tag_iBoinkTNG);

	if (on != boinker->accumulate)
		{
			BoinkitemAccumulate((Boinkitem*)item, on);
			boinker->accumulate = on;
			
			vapplicationPropagateChange(boinker->vapp, vname_State, 
				TAG("Clear"), on ? vname_Enabled : vname_Disabled);
		}
	return vTRUE;
}

static int AAccumulateQuery(vcommandFunction *cmd, vdict *context)
{
	ABoinker *boinker = TheBoinker();
	
	vdictStore(context, vname_Toggle, 
			   boinker->accumulate ? vname_On : vname_Off);
	return vTRUE;
}



/* */
static int AAbout(vcommandFunction *cmd, vdict *context)
{
	AHelp(TheBoinker());
	return vTRUE;
}



/* */
static int AUsePrecannedStr(vcommandFunction *cmd, vdict *context)
{
	vobjectAttributed *source;
	const vchar *title;

	source = (vobjectAttributed*)vdictLoad(context, vname_Operator);
	title  = (const vchar*)vobjectGetAttribute(source, vname_Title);
	if (title)
		ASetString(TheBoinker(), title);

	return vTRUE;
}



/* */
static vbool APrefsFontChooserFilter(vfontchsr *chsr, vfont *font)
{
	return AUseFont(font);
}



/* */
static void APrefsPutdownValues(vconfirm *con, ABoinker *boinker)
{
	vdialogItem		*item, *bitem;

	ANoteLOC("setting string preference");
	item  = vdialogFindItem(vconfirmGetDialog(con), TAG("iString"));
	bitem = vdialogFindItem(boinker->dialog, tag_iBoink);
	vtextitemSetText((vtextitem*)item, vdialogGetItemTitle(bitem));

	ANoteLOC("setting font preference");
	vdialogSetItemFont(item, NULL);

	ANoteLOC("setting random geo preference");
	item = vdialogFindItem(vconfirmGetDialog(con), TAG("cRandomGeo"));
	vcontrolSetValue((vcontrol*)item, boinker->randomgeo ? 1 : 0);
}



/* */
static int APrefsUseFont(vfontchsr *chizler, vfont *choice)
{
	ABoinkerPrefs	*prefs;
	vdialogItem		*item;

	prefs = (ABoinkerPrefs*)vfontchsrGetData(chizler);
	vdebugMessagedAssert(prefs!=NULL, "use-font: NULL prefs!?");

	item = vdialogFindItem(vconfirmGetDialog(prefs->boinker->prefs), 
						   TAG("iString"));
	if (choice != vdialogGetItemFont(item))
		vdialogSetItemFont(item, choice);
	
	return vTRUE;
}



/* */
static int APrefsPickFont(vcommandFunction *ignored, vdict *context)
{
	ABoinkerPrefs	*prefs;
	vfontchsr		*chizler;
	vconfirm		*prefswin;
	
	ANoteLOC("making font chizler");
	prefswin = (vconfirm*)vdictLoad(context, vname_Dialog);
	prefs = (ABoinkerPrefs*)vconfirmGetData(prefswin);

	if (!(chizler = prefs->chizler))
		{
			ABoinker *boinker = prefs->boinker;
			if (boinker->fontchsrClass==NULL)
				{
					register vfontchsrClass *clas;
					clas= (vfontchsrClass*)vclassReproduce
						(vfontchsrGetDefaultClass());
					vclassSetNameScribed(clas, SCRIBE("BoinkerFontChooser"));

					vclassSet(clas, vfontchsrFILTER, APrefsFontChooserFilter);
					boinker->fontchsrClass = clas;
				}

			chizler = prefs->chizler = vfontchsrCreateOfClass
				(prefs->boinker->fontchsrClass);
			vwindowSetLeader(vdialogGetWindow(vfontchsrGetDialog(chizler)),
							 vdialogGetWindow(vconfirmGetDialog(prefswin)));
			vfontchsrSetApply(chizler, APrefsUseFont);
			vfontchsrSetData(chizler, prefs);
		}

	if (vdialogIsOpen(vfontchsrGetDialog(chizler)))
		AForceConfirmVisible((vconfirm*)chizler); /* missing C-API... */
	else
		{
			vwindowPlace(vdialogGetWindow(vfontchsrGetDialog(chizler)),
						 vdialogGetWindow(vconfirmGetDialog(prefswin)),
						 vrectPLACE_HALF|vrectPLACE_RIGHT,
						 vrectPLACE_INSET|vrectPLACE_TOP);
			vfontchsrOpen(chizler);
		}

	return vTRUE;
}

static vcommandFunctionTemplate __APrefsCommandsTemplate[] = {
	{"cPickFont",    APrefsPickFont,   (vcommandFunc)NULL}
};
#define __APrefsCommandsTemplateSIZE() \
	(sizeof(__APrefsCommandsTemplate) / sizeof(vcommandFunctionTemplate))




/* */
static int APrefsCommit(vconfirm *con, vevent *ignored)
{
	register ABoinker		*boinker;
	vdialogItem				*item;
	vstr					*astr;
	register ABoinkerPrefs	*prefs;
	vfont					*font;

	prefs = (ABoinkerPrefs*)vconfirmGetData(con);
	vdebugMessagedAssert(prefs!=NULL, "prefs-commit: NULL prefs!?");

	boinker = prefs->boinker;
	prefs->changes = 0;

	ANoteLOC("reading new string");
	item = vdialogFindItem(vconfirmGetDialog(con), TAG("iString"));
	astr = vtextitemGetTextAsString((vtextitem*)item);
	if (*astr && (!boinker->userstring || 
		vcharCompare(astr, boinker->userstring)!=0))
		{
			prefs->userstring = astr;
			prefs->changes |= _chgSTR;
		}
	else
		vstrDestroy(astr);


	ANoteLOC("setting new font");
	font = vdialogGetItemFont(item);
	if (font)
		{
			prefs->font = font;
			prefs->changes |= _chgFONT;
		}


	ANoteLOC("reading random geo");
	item = vdialogFindItem(vconfirmGetDialog(con), TAG("cRandomGeo"));
	if (vcontrolGetValue((vcontrol*)item) != boinker->randomgeo)
		{
			prefs->randomgeo = vcontrolGetValue((vcontrol*)item) ? 1 : 0;
			prefs->changes |= _chgGEO;
		}


	if (prefs->changes != 0)
		{
			ttaskCmdDispatcher *task;
			task = ttaskCmdDispatcherCreateLinked
				(vdialogGetObject(boinker->dialog), TAG("cUpdatePrefs"));
			ttaskCmdDispatcherSetData(task, prefs);
			ttaskCmdDispatcherAutoDelete(task, vTRUE);
			ttaskCmdDispatcherSetMaxIterations(task,1);
			ttaskCmdDispatcherPost(task);
		}

	return vTRUE;
}




/* */
static int AUpdatePrefs(vcommandFunction *ignored, vdict *context)
{
	ttaskCmdDispatcher			*task;
	register ABoinkerPrefs		*prefs;
	
	task  = (ttaskCmdDispatcher*)vdictLoad(context, 
			ttaskCmdDispatcherGetContextIdentifier());
	vdebugMessagedAssert((task!=NULL), "update-prefs: NULL task!");

	prefs = (ABoinkerPrefs*)ttaskCmdDispatcherGetData(task);

	if ((prefs->changes & _chgFONT) != 0)
		{
			vdialogItem *item;
			vfont **oldfonts;
			unsigned oldnumfonts;

			oldfonts = prefs->boinker->fonts;
			oldnumfonts = prefs->boinker->numfonts;

			ASetBaseFont(prefs->boinker, prefs->font);

			if (prefs->boinker->numfonts==0 || prefs->boinker->fonts==NULL)
				{
					if (prefs->boinker->fonts!=NULL)
						vmemFree((void*)prefs->boinker->fonts);

					prefs->boinker->fonts    = oldfonts;
					prefs->boinker->numfonts = oldnumfonts;
				}
			else
			if (oldfonts!=NULL)
				vmemFree((void*)oldfonts);

			item = vdialogFindItem(prefs->boinker->dialog, tag_iBoinkTNG);
			vdialogSetItemFont(item, prefs->font);
		}

	if ((prefs->changes & _chgSTR) != 0)
		{
			if (prefs->boinker->userstring)
				vstrDestroy(prefs->boinker->userstring);

			ASetString(prefs->boinker, prefs->userstring);
			vstrDestroy(prefs->userstring);
			prefs->boinker->userstring = NULL;
		}
	
	if ((prefs->changes & _chgGEO) != 0)
		{
			vdialogItem *item;
			item = vdialogFindItem(prefs->boinker->dialog, tag_iBoinkTNG);
			BoinkitemRandomizeGeometry((Boinkitem*)item, prefs->randomgeo);
			prefs->boinker->randomgeo = prefs->randomgeo;
		}
	
	return vTRUE;
}



/* */
static int AEditPrefs(vcommandFunction *cmd, vdict *context)
{
	register vconfirm 	*prefswin;
	register ABoinker	*boinker = TheBoinker();

	ANoteLOC("loading preferences");
	
	prefswin = boinker->prefs;
	if (!prefswin)
		{
			boinker->prefs = prefswin = vconfirmLoad
				(vresourceGet(boinker->resources, TAG("Prefs")));

			vconfirmSetApplyHook(prefswin, APrefsCommit);
			vconfirmSetApply(prefswin, vFALSE);
			vwindowSetLeader(vdialogGetWindow(vconfirmGetDialog(prefswin)),
							 vdialogGetWindow(boinker->dialog));

			if (!boinker->prefvalues)
				{
					boinker->prefvalues = (ABoinkerPrefs*)
						vmemAlloc(sizeof(ABoinkerPrefs));
					boinker->prefvalues->boinker = boinker;
					boinker->prefvalues->chizler = NULL;
				}
			vconfirmSetData(prefswin, boinker->prefvalues);

			AInitDialogCommands(vconfirmGetDialog(prefswin), 
				__APrefsCommandsTemplate, __APrefsCommandsTemplateSIZE());
		}

	
	if (vdialogIsOpen(vconfirmGetDialog(prefswin)))
		AForceConfirmVisible(prefswin);
	else
		{
			APrefsPutdownValues(prefswin, boinker);
			ACenterDialog(vconfirmGetDialog(prefswin));
			vconfirmOpen(prefswin);
		}

	return vTRUE;
}



/* */
static vcommandFunctionTemplate __ACommandsTemplate[]= {
	{"Quit",         AQuit,            (vcommandFunc)NULL},
	{"Close",        AQuit,            (vcommandFunc)NULL},
	{"Clear",        AClear,           AClearQuery},
	{"cAccumulate",  AAccumulate,      AAccumulateQuery},
	{"About",		 AAbout,	       (vcommandFunc)NULL},
	{"cUseString",   AUsePrecannedStr, (vcommandFunc)NULL},
	{"cPrefs",       AEditPrefs,       (vcommandFunc)NULL},
	{"cUpdatePrefs", AUpdatePrefs,     (vcommandFunc)NULL}
};

#define __ACommandsTemplateSIZE() \
	(sizeof(__ACommandsTemplate) / sizeof(vcommandFunctionTemplate))



/*
 *+-------------------------------------------------------------------------+
 * Opening The BOiNk Window:
 *
 * Open our Splash Window and post the task list that will iterate over 
 * our other initialization routines (being the useful things
 * they are). Note the ordering of the initialization is determined by 
 * the order in which the tasks are added to the list...
 *
 *  ALoadWindows() - 1st task doing at initialization! This loads both
 *    the boink and splash windows from the resource file. Opens Splash.
 *
 *	ACloseSplashWindow - closes our startup splash window. The splash 
 *    contains an optional progress string that can be changed to reflect 
 *	  what's happening during startup. Splash is closed before opening 
 *    the main boink window.
 *
 *	AOpenBoinkWindow() - Opens the main boink window. Must be done before
 *	  the boink timer is started!
 *
 *  ADetermineStartupOptions() - Load/Interpret the user's startup 
 *	   options (ie. command line and preferences options)
 *
 *	AStartup() - called to initialize the basic application environment
 *	  (resources, etc.) and get the ball rolling. 
 *
 *	AShutdown() - anti-startup. Cleans up our dynamic memory allocation 
 *    iff we're checking for memory leakage. Provides closure...yeh 
 *    that's it...closure.
 *
 *+-------------------------------------------------------------------------+
 */


/* */
static void ASaveLayout(ABoinker *boinker)
{
	vresource res;
	vrect r;

	res = vapplicationGetPreferences(boinker->vapp);
	if ((res!=vresourceNULL)    && 
		(boinker->dialog!=NULL) && vdialogIsOpen(boinker->dialog))
		vexWITH_HANDLING
		{
			r = *vwindowGetRect(vdialogGetWindow(boinker->dialog));
	        	vresourceStoreRect(&r, vresourceMake(res, TAG("location")));
		}
		vexON_EXCEPTION
		{
			/* burp */
		}
		vexEND_HANDLING;
}



/* */
static void ALoadOldLayout(ABoinker *boinker)
{
	vresource res;
	vrect r;
	vbool volatile done= vFALSE;
	vdialog *volatile dialog= boinker->dialog;

	res = vapplicationGetPreferences(boinker->vapp);
	if (vresourceTestGet(res, TAG("location"), &res))
		vexWITH_HANDLING
		{
			vresourceLoadInitRect(&r, res);
	        	vwindowSetRect(vdialogGetWindow(dialog), &r);
	        	done = vTRUE;
		}
		vexON_EXCEPTION
		{
			/* burp */
		}
		vexEND_HANDLING;

	if (!done)
		ACenterDialog(dialog);
}



/* */
static void ALoadWindows(ttaskExternal *task, const void *data)
{
	ABoinker	*boinker = (ABoinker*)data;
	vresource	 res;

	ANoteTRY("loading BOinKeR dialog", "the booboohead");

	res = vresourceGet(boinker->resources, TAG("Boinker"));
	boinker->dialog = vdialogLoad(res);
	boinker->titleTemplate = vstrClone(vdialogGetTitle(boinker->dialog));
	ALoadOldLayout(boinker);

	ANoteTRY("loading SpLaSh dialog", "the booboohead");

	res = vresourceGet(boinker->resources, TAG("Splash"));
	boinker->splash = vdialogLoad(res);
	vdialogSetCloseHook(boinker->splash, APrematureQuit);

	ANoteLOC("opening splash");

	ACenterDialog(boinker->splash);
	vdialogOpen(boinker->splash);
	vwindowBlock(vdialogGetWindow(boinker->splash));
}



/* */
static void ACloseSplashWindow(ABoinker *boinker)
{
	if (boinker->splash)
		{
			vdialogDestroy(boinker->splash);
			boinker->splash = NULL;
		}
}



/* */
static void AOpenBoinkWindow(ttaskExternal *task, const void *data)
{
	ABoinker	*boinker = (ABoinker*)data;

	ANoteLOC("initializing command space");
	AInitDialogCommands(boinker->dialog, __ACommandsTemplate, 
						__ACommandsTemplateSIZE());

	ANoteTRY(NULL,NULL);

	ACloseSplashWindow(boinker);
	vdialogOpen(boinker->dialog);
}



/* */
static void AHelp(ABoinker *boinker)
{
	register vconfirm *helpwin;

	ANoteTRY("loading help", "missing resource");
	
	helpwin = vconfirmLoad(vresourceGet(boinker->resources, TAG("Overview")));
	vconfirmSetCancel(helpwin, vFALSE);
	vconfirmSetApply(helpwin, vFALSE);
	vconfirmSetOverride(helpwin, vTRUE);
	vconfirmSetOkTitleScribed(helpwin, vnameScribeGlobal(vname_Close));

	ACenterDialog(vconfirmGetDialog(helpwin));
	(void)vconfirmProcess(helpwin);

	vconfirmDestroy(helpwin);
}



/* */
static void ADetermineStartupOptions(ABoinker *volatile boinker,
									 unsigned *help)
{
#define isOn(l) ((v = vprefLoadScribed(SCRIBE(l))) && \
				 vcharCompare(v,vname_On)==0)

	const vchar	*volatile v;
	unsigned	 volatile hunk;

	/*
	 * If user only want help for us...
	 */
	*help = isOn("help") ? 1 : 0;
	if (*help)
		return;


	/*
	 * Process startup preferences/options that affect how and
	 * which tasks get performed...
	 */
	ANoteTRY(NULL,NULL);
	boinker->enumfonts    = isOn("fonts");
	boinker->randomcolors = isOn("norandomcolors") ? 0 : 1;
	boinker->teehee       = isOn("noteehee") ? 0 : 1;
	boinker->silent       = isOn("silent")   ? 1 : 0;
	boinker->accumulate   = 1;
	boinker->randomgeo    = isOn("randomgeo") ? 1 : 0;
 
	hunk = _HUNK;
	if ((v = vprefLoadScribed(SCRIBE("hunk"))))
		vexWITH_HANDLING
		{
			hunk = vnumParseUInt(v,NULL);
		}
		vexON_EXCEPTION
		{
			if (vnumGetSyntaxException() || vnumGetRangeException()) {
				vdebugMWarn(("boink! ignoring invalid hunk option...\n"));
				hunk = _HUNK;
			}
			else
				vexPropagate(NULL,vexNULL);
		}
		vexEND_HANDLING;
	ADetermineHunkOfTime(boinker, hunk);
	
	if ((v = vprefLoadScribed(SCRIBE("str"))) && vcharCompare(v, vname_Default)!=0)
		boinker->userstring = vstrClone(v);
	else
	if (isOn("spam"))
		boinker->userstring = vstrCloneScribed(SCRIBE("Spamoids Rule!"));

#undef isOn
}



/* */
static void AStartup(ABoinker *boinker)
{
	const vname		*tag;
	vresource		 res;
	ttaskExternal	*task;
	vtimestamp		 delay;
	unsigned		 help;

	/*
	 * Intern these before anybody might use 'em
	 */
	tag_iBoink    = TAG("iBoink");
	tag_iBoinkTNG = TAG("iBoinkTNG");
	tag_sReplace  = TAG("%1s");


	/*
	 * Very basic. Where's my stuff?!
	 */
	ANoteTRY("loading main resources", "dems missing!");
	boinker->vapp = vapplicationGetCurrent();
	boinker->resources = vapplicationGetResources(boinker->vapp);

	AInitErrorUI(boinker, TAG("Error"));


	/*
	 * Process startup preferences/options that affect how and
	 * which tasks get performed...if user only wants help then
	 * just show help and abandon (don't run!)
	 */
	ADetermineStartupOptions(boinker, &help);
	if (help)
		{
			AHelp(boinker);
			AGenerateOnlyHelpException(); /* => bye bye */
		}

	/*
	 * Beautify Me:
	 */
	ANoteTRY("making itself gorgeous", "missing resources");
	res = vresourceGet(boinker->resources, TAG("Icon"));
	vapplicationSetIconOwned(boinker->vapp, vimageLoad(res));
	
	res = vresourceGet(boinker->resources, TAG("Titles"));
	tag = vresourceGetTagAt(res, strTitle);
	vapplicationSetTitle(boinker->vapp, tag);


	/*
	 * Setup our startup st. it doesn't block the event
	 * loop and we can do a cool splash window thingy...
	 */
	ATaskMakeClasses(boinker);
	task = ttaskExternalCreateOfClass(boinker->startuptaskClass);

	ANoteLOC("loading task list");
	ttaskExternalAutoDelete(task, vTRUE);
	boinker->pending = task;

	delay = vtimestampMake(1,0);
	ttaskExternalSetMinDelay(task, &delay);
	ttaskExternalDescribeAs(task, vresourceGetTagAt(res, strBusy));
	
	tag = vresourceGetTagAt(res, strLoadingWindows);
	ttaskExternalAdd(task, ALoadWindows, boinker, tag);

	if (boinker->teehee)
		ALoadTaunters(boinker, task);
	
	tag = vresourceGetTagAt(res, strLoadingFonts);
	ttaskExternalAdd(task, AInitFonts, boinker, tag);
	
	tag = vresourceGetTagAt(res, strLoadingColors);
	ttaskExternalAdd(task, AInitColors, boinker, tag);
	
	ttaskExternalAdd(task, AOpenBoinkWindow, boinker, NULL);
	tag = vresourceGetTagAt(res, strBoinking);
	ttaskExternalAdd(task, AStartBOiNkTask, boinker, tag);

	/*
	 * Splash, Sploosh, Spliish, Boink...
	 */
	ANoteLOC("posting task list");
	ttaskExternalPost(task);	
}



/* */
static void AShutdown(ABoinker *boinker)
{
	ANoteTRY(NULL, NULL);

#if (vmemBALANCE)

	if (boinker->dialog)
		vdialogDestroy(boinker->dialog);
	
	if (boinker->palette)
		vcolorDestroyPalette(boinker->palette);
	
	if (boinker->fonts)
		vmemFree((void*)boinker->fonts);

	if (boinker->splash)
		vdialogDestroy(boinker->splash);
	
	if (boinker->prefs)
		vconfirmDestroy(boinker->prefs);

	if (boinker->userstring)
		vstrDestroy(boinker->userstring);
	if (boinker->titleTemplate)
		vstrDestroy(boinker->titleTemplate);
	
	if (boinker->prefvalues)
		{
			if (boinker->prefvalues->chizler)
				vfontchsrDestroy(boinker->prefvalues->chizler);
			vmemFree((void*)boinker->prefvalues);
		}

	if (boinker->errUI)
		vnoticeDestroy(boinker->errUI);
	
	if (boinker->pending)
		ttaskExternalDestroy(boinker->pending);
#endif

	if (boinker->task)
		ttaskDestroy(boinker->task);
}



/*
 *+-------------------------------------------------------------------------+
 * main()
 *
 * Our application's main thingy. We initialize Galaxy the easy way, start
 * our initialization process, and we're off!
 *
 *+-------------------------------------------------------------------------+
 */
int main(int argc, char *argv[])
{
	int volatile exitcode = EXIT_SUCCESS;


	/*
	 * Initialize our exception subclass before any application
	 * startup...
	 */
	AInitializeExceptionClasses();



	vexUNWIND_PROTECT
	{
		/*
		 * Initialize the Galaxy Application Environment (runtime)
		 */
		vstartup(argc, argv);

		/*
		 * Connect to any running testing tools
		 */
		vtestStartup();

		/*
		 * Our initialization
		 */
		AStartup(TheBoinker());

		/*
		 * The main event loopy...
		 */
		veventProcess();

	}
	vexON_UNWIND
	{
		/*
		 * Did we die for some cosmic reason?
		 */
		if (vexGetRootException())
			{
				if (!AGetOnlyHelpException())
					{
						AHandleError(TheBoinker());
						exitcode = EXIT_FAILURE;
					}
				vexClear();
			}

		/*
		 * Cleanup
		 */
		AShutdown(TheBoinker());

	}
	vexEND_UNWIND
	
	exit(exitcode);
	return EXIT_FAILURE; /* not reached */
}


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
