/* $Id: vhelphypertext.h,v 1.15 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelphypertext.h
 *
 *  Programming interface to the vhelphypertext base display class.
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelphypertextINCLUDED
#define vhelphypertextINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelpdisplayINCLUDED
#include vhelpdisplayHEADER
#endif

#ifndef  vwebbrowseINCLUDED
#include vwebbrowseHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * * *
 */

enum {
    vhelphypertextEventREQUEST_BEGIN,
    vhelphypertextEventREQUEST_SUCCEEDED,
    vhelphypertextEventREQUEST_FAILED,
    vhelphypertextEventWAIT,
    vhelphypertextEventCANNOT_LAUNCH_BROWSER,
    vhelphypertextEventCANNOT_CONTACT_BROWSER,
    vhelphypertextEventNEXT_EVENT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelphypertext		vhelphypertext;
typedef struct	vhelphypertextClass	vhelphypertextClass;

typedef int				vhelphypertextEvent;

typedef void 	(*vhelphypertextNoteProc)(
    vhelphypertext		*display,
    vhelphypertextEvent		 event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

void vhelphypertextStartup(
    void
    );

vhelphypertextClass *vhelphypertextGetDefaultClass(
    void
    );

vhelphypertextClass *vhelphypertextGetClass(
    vhelphypertextClass		*helpdisplayClass
    );

vhelphypertext *vhelphypertextCreateOfClass(
    vhelphypertextClass		*helpdisplayClass
    );

void vhelphypertextInitOfClass(
   vhelphypertext		*helpdisplay,
   vhelphypertextClass		*clas
   );

void vhelphypertextInit(
    vhelphypertext		*helpdisplay
    );

void vhelphypertextDestroy(
    vhelphypertext		*helpdisplay
    );

vhelphypertext *vhelphypertextCreate(
    void
    );

vhelpdisplay *vhelphypertextGetDisplay(
    vhelphypertext		*helpdisplay
    );

vbool vhelphypertextDisplayHelp(
    vhelphypertext		*helpdisplay,
    vhelprequest		*request
    );

void vhelphypertextUndisplayHelp(
    vhelphypertext		*helpdisplay,
    vhelprequest		*request
    );

/*
 * Class specific API.
 */

void vhelphypertextSetWebbrowseOwned(
    vhelphypertext		*helpdisplay,
    vwebbrowse			*webbrowse
    );

vwebbrowse *vhelphypertextGetWebbrowse(
    vhelphypertext		*helpdisplay
    );

void vhelphypertextSetSynchronous(
    vhelphypertext		*helpdisplay,
    vbool			 onOff
    );

vbool vhelphypertextGetSynchronous(
    vhelphypertext		*helpdisplay
    );

void vhelphypertextSetNotify(
    vhelphypertext		*helpdisplay,
    vhelphypertextNoteProc	 noteProc
    );

vhelphypertextNoteProc vhelphypertextGetNotify(
    vhelphypertext		*helpdisplay
    );

void vhelphypertextNotify(
    vhelphypertext		*helpdisplay,
    vhelphypertextEvent		 helphypertextEvent
    );


/*
 * * * * * * * * * * PRIVATE CONSTANTS * * * * * * * * * *
 */
 
/*
 * Flag values.
 */
enum 
{
    _vhelphypertextSYNCHRONOUS		= 0x0001
};
    
/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelphypertext {
    vhelpdisplay		 display;
    vhelphypertextNoteProc	 noteProc;
    unsigned short		 flags;
    vwebbrowse			*webbrowse;
};

#define vhelphypertextCLASS(SUPER, HELPDIS)		        	\
    vhelpdisplayCLASS(SUPER, HELPDIS);					\
    vclassMETHOD(vhelphypertextNOTIFY, (HELPDIS *display, 		\
		 vhelphypertextEvent event));				\
    vclassMETHOD(vhelphypertextSET_WEBBROWSE_OWNED, 			\
		 (HELPDIS *display, vwebbrowse *webbrowse));		\
    vclassMETHOD(vhelphypertextSET_SYNCHRONOUS, 			\
		 (HELPDIS *display, vbool onOff));			\
    vclassMETHOD(vhelphypertextSET_NOTIFY,				\
		 (HELPDIS *display, vhelphypertextNoteProc noteProc))

struct vhelphypertextClass {
    vhelphypertextCLASS(vhelphypertextClass, vhelphypertext);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelphypertextGetDisplay(d)	vportBASE_OBJECT((d), display)
#define vhelphypertextGetClass(d)					      \
    ((vhelphypertextClass*)						      \
     vhelpdisplayGetClass(vhelphypertextGetDisplay(d)))
#define vhelphypertextCreateOfClass(c) 					      \
    ((vhelphypertext *)							      \
     vhelpdisplayCreateOfClass((vhelpdisplayClass*)(c)))
#define vhelphypertextCreate()						      \
    vhelphypertextCreateOfClass(vhelphypertextGetDefaultClass())
#define vhelphypertextInitOfClass(d, c) 				      \
    vhelpdisplayInitOfClass(vhelphypertextGetDisplay(d),		      \
			    (vhelpdisplayClass*)(c))
#define vhelphypertextInit(d)						      \
    vhelphypertextInitOfClass(d, vhelphypertextGetDefaultClass())

#define vhelphypertextDisplayHelp(d, r)					      \
    vhelpdisplayDisplayHelp(vhelphypertextGetDisplay(d), r)
#define vhelphypertextUndisplayHelp(d, r)				      \
    vhelpdisplayUndisplayHelp(vhelphypertextGetDisplay(d), r)


#define vhelphypertextGetSynchronous(d)					      \
    ((d)->flags & _vhelphypertextSYNCHRONOUS)
#define vhelphypertextGetWebbrowse(d)	(d)->webbrowse

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelphypertextNotify(d, e)					      \
    vclassSend(vhelphypertextGetClass(d), vhelphypertextNOTIFY, (d, e))
#define vhelphypertextSetSynchronous(d, b)				      \
    vclassSend(vhelphypertextGetClass(d), 				      \
	       vhelphypertextSET_SYNCHRONOUS, (d, b))
#define vhelphypertextSetNotify(d, n)					      \
    vclassSend(vhelphypertextGetClass(d), vhelphypertextSET_NOTIFY, (d, n))
#define vhelphypertextSetWebbrowseOwned(d, n)				      \
    vclassSend(vhelphypertextGetClass(d),				      \
 	       vhelphypertextSET_WEBBROWSE_OWNED, (d, n))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelphypertextINCLUDED */




