/* $Id: vtextruler.h,v 1.27 1996/09/04 00:54:45 gray Exp $ */

/************************************************************

    vtextruler.h
    C Interface to the Ruler dialog item

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vtextrulerINCLUDED
#define vtextrulerINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#if (vportNEED_VMS_FILESYSTEM) && (vportCPLUSPLUS_SOURCE)
/* vtextruler conflicts with vtextRuler under OpenVMS C++ */
#define vtextruler vtextruleritem
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vtextrulerHEIGHT	36

enum {
    vtextrulerLEFT_INDENT	= 0,
    vtextrulerFIRST_INDENT	= 1,
    vtextrulerRIGHT_INDENT	= 2
};

#define vtextruler_DefaultRuler  (_vtextrulerPredefs[_vtextruler_DefaultRuler])
#define vtextruler_LeftTab  	(_vtextrulerPredefs[_vtextruler_LeftTab])
#define vtextruler_CenterTab  	(_vtextrulerPredefs[_vtextruler_CenterTab])
#define vtextruler_RightTab  	(_vtextrulerPredefs[_vtextruler_RightTab])
#define vtextruler_DecimalTab  	(_vtextrulerPredefs[_vtextruler_DecimalTab])
#define vtextruler_LeftJustify 	(_vtextrulerPredefs[_vtextruler_LeftJustify])
#define vtextruler_CenterJustify (_vtextrulerPredefs[_vtextruler_CenterJustify])
#define vtextruler_RightJustify  (_vtextrulerPredefs[_vtextruler_RightJustify])
#define vtextruler_FullJustify   (_vtextrulerPredefs[_vtextruler_FullJustify])
#define vtextruler_SingleSpace   (_vtextrulerPredefs[_vtextruler_SingleSpace])
#define vtextruler_SingleHalfSpace  (_vtextrulerPredefs[_vtextruler_SingleHalfSpace])
#define vtextruler_DoubleHalfSpace  (_vtextrulerPredefs[_vtextruler_DoubleSpace])

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtextruler 	vtextruler;
typedef struct vtextrulerClass	vtextrulerClass;

typedef void (*vtextrulerNoteProc)(
    vtextruler			*ruler,
    vevent   			*event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextrulerStartup(void);


/* Ruler Class Functions */

vtextrulerClass *vtextrulerGetDefaultClass(void);

vtextObserverClass *vtextrulerGetDefaultObserverClass(void);

/* Initialization and allocation */

vtextruler *vtextrulerCreate(void);

vtextruler *vtextrulerCreateOfClass(
    vtextrulerClass	*clas
    );
    
vtextruler *vtextrulerClone(
    vtextruler	    	*ruler
    );

void vtextrulerCopy(
    vtextruler	    	*ruler,
    vtextruler	    	*target
    );

void vtextrulerCopyInit(
    vtextruler	    	*ruler,
    vtextruler	    	*target
    );

void vtextrulerInit(
    vtextruler	    	*ruler
    );

void vtextrulerInitOfClass(
    vtextruler		*ruler,
    vtextrulerClass	*clas
    );

void vtextrulerDestroy(
    vtextruler	    	*ruler   
    );

vtextruler *vtextrulerLoad(
    vresource		resource
    );

void vtextrulerLoadInit(
    vtextruler		*ruler,
    vresource		resource
    );

void vtextrulerStore(
    vtextruler		*ruler,
    vresource		resource
    );

/* Ruler Operations */

/* Ruler attribute modification */

void vtextrulerSetNotify(
    vtextruler         	*ruler,
    vtextrulerNoteProc	noteProc
    );

void vtextrulerSetData(
    vtextruler		*ruler,
    const void		*data
    );

void vtextrulerSetTextData(
    vtextruler		*ruler,
    vtext	        *text
    );

void vtextrulerSetSelection(
    vtextruler		*ruler,
    vtextSelection	*selection
    );

void vtextrulerSetDefaultRuler(
    vtextruler		*ruler,
    vtextRuler		*defaultRuler
    );

void vtextrulerSetObserverClass(
    vtextruler		*ruler,
    vtextObserverClass	*observerClass
    );
    
void vtextrulerSetUseDefault(
    vtextruler		*ruler,
    int			useDefault
    );

void vtextrulerSetScrollOffset(
    vtextruler		*ruler,
    int			offset
    );

void vtextrulerSetLeftMargin(
    vtextruler		*ruler,
    int 	    	leftMargin
    );

/* Ruler attribute access */

vtextrulerClass *vtextrulerGetClass(
    vtextruler              *ruler
    );

vtextrulerNoteProc vtextrulerGetNotify(
    vtextruler		    *ruler
    );

const void *vtextrulerGetData(
    vtextruler              *ruler
    );

vtext *vtextrulerGetTextData(
    vtextruler              *ruler
    );

vtextSelection *vtextrulerGetSelection(
    vtextruler              *ruler
    );

vtextRuler *vtextrulerGetDefaultRuler(
    vtextruler          	*ruler
    );

vtextObserverClass *vtextrulerGetObserverClass(
    vtextruler	    	*ruler
    );

int vtextrulerGetUseDefault(
    vtextruler		*ruler
    );

int vtextrulerGetScrollOffset(
    vtextruler          *ruler
    );

short vtextrulerGetLeftMargin(
    vtextruler		*ruler
    );

/* Other */

vdialogItem *vtextrulerGetItem(
    vtextruler		*ruler
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Global ruler strings
 */

enum {
    _vtextruler_DefaultRuler,
    _vtextruler_LeftTab,
    _vtextruler_CenterTab,
    _vtextruler_RightTab,
    _vtextruler_DecimalTab,
    _vtextruler_LeftJustify,
    _vtextruler_CenterJustify,
    _vtextruler_RightJustify,
    _vtextruler_FullJustify,
    _vtextruler_SingleSpace,
    _vtextruler_SingleHalfSpace,
    _vtextruler_DoubleSpace,
    _vtextruler_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vtextrulerTrackInfo {
    vrect            dragRect;
    vpoint           oldPt;
    int              dragTabType;
    int              dragIndentType;
    vfixed           fromTabPosition;
    vbool            moved;
} _vtextrulerTrackInfo;

struct vtextruler {
    vdialogItem	    	item;

    vtext		*editRec;
    vtextSelection	*selection;
    vtextRuler		*defaultRuler;

    vtextObserverClass 	*observerClass;
    vtextObserver      	*observer;

    vbyteSigned		tabSelected;
    vbyteSigned		spacingSelected;	
    vbyteSigned		justSelected;
    int			leftMargin;
    int		    	scrollOffset;
    int			lastStartLine;
    int			lastEndLine;

    vtextRuler		displayRuler;
    vbool		different;

    vbool		useDefault;
    vbool		defaultOwned;

    vimage		*offscreenImage;

    _vtextrulerTrackInfo *trackInfo;
};

#define vtextrulerCLASS(SUPER, RULER, ITEM, NOTIFY)		              \
    vdialogITEM_CLASS(SUPER, RULER, NOTIFY);				      \
    vclassVARIABLE(vtextrulerBORDER_INSET,  short);			      \
    vclassMETHOD_RET(vtextrulerGET_DEFAULT_RULER, vtextRuler *,		      \
					      (RULER *ruler));		      \
    vclassMETHOD(vtextrulerSET_DEFAULT_RULER,				      \
			      (RULER *ruler, vtextRuler *defaultRuler));      \
    vclassMETHOD(vtextrulerDRAW_TAB, 	      (RULER *ruler, int tabType));   \
    vclassMETHOD(vtextrulerDRAW_INDENT,	      (RULER *ruler, int whichIndent));\
    vclassMETHOD(vtextrulerDRAW_TAB_WITH,                                     \
		  (RULER *ruler, int tabType, vdrawcontext *context));        \
    vclassMETHOD(vtextrulerDRAW_INDENT_WITH,	                              \
		 (RULER *ruler, int whichIndent, vdrawcontext *context))

struct vtextrulerClass {
    vtextrulerCLASS(vtextrulerClass, vtextruler, vtextrulerItem,
		    vtextrulerNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextrulerGetItem(r)		(vportBASE_OBJECT((r), item))

#define vtextrulerCreateOfClass(c)	\
	((vtextruler *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vtextrulerCreate()	vtextrulerCreateOfClass(vtextrulerGetDefaultClass())
#define vtextrulerClone(d)	\
	((vtextruler *) vdialogCloneItem(vtextrulerGetItem(d)))
#define vtextrulerInitOfClass(e,c)	\
	vdialogInitItemOfClass(vtextrulerGetItem(e), (vdialogItemClass *) (c))
#define vtextrulerInit(e)	vtextrulerInitOfClass(e, vtextrulerGetDefaultClass());
#define vtextrulerCopyInit(c,t)	\
	vdialogCopyInitItem(vtextrulerGetItem(c), vtextrulerGetItem(t))
#define vtextrulerLoad(r)	((vtextruler *) vdialogLoadItem(r))
#define vtextrulerLoadInit(c,r)	vdialogLoadInitItem(vtextrulerGetItem(c), r)
#define vtextrulerDestroy(d)	\
	vdialogDestroyItem(vtextrulerGetItem(d))

#define vtextrulerGetClass(d)	\
	((vtextrulerClass *) vdialogGetItemClass(vtextrulerGetItem(d)))
 
#define vtextrulerGetData(e)	\
	vdialogGetItemData(vtextrulerGetItem(e))
#define vtextrulerGetTextData(e)  	((e)->editRec)
#define vtextrulerGetSelection(e)	((e)->selection)
#define vtextrulerSetObserverClass(e,c)	((e)->observerClass = (c))
#define vtextrulerGetObserverClass(e)	((e)->observerClass)
#define vtextrulerSetUseDefault(e,u)	((e)->useDefault = (u))
#define vtextrulerGetUseDefault(e)	((e)->useDefault)

#define vtextrulerGetNotify(r)	\
	((vtextrulerNoteProc) vdialogGetItemNotify(vtextrulerGetItem(r)))
#define vtextrulerSetNotify(r, n) \
	vdialogSetItemNotify((vdialogItem *)(r), (vdialogItemNoteProc)(n))

#define vtextrulerSetLeftMargin(e,m)	((e)->leftMargin = (m))
#define vtextrulerGetLeftMargin(e)	((e)->leftMargin)
#define vtextrulerGetScrollOffset(r)    ((r)->scrollOffset)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define _vtextrulerSend(m,s,a)	    vclassSend(vtextrulerGetClass(m),s,a)
#define _vtextrulerSendSuper(s,a)   vclassSendSuper(((globals *)*master) \
						    ->defaultClass, s, a)

#define vtextrulerCopy(d,t)	\
	vclassSend(vtextrulerGetClass(d), vobjectCOPY, (d, t))

#define vtextrulerStore(d,r)	\
	vclassSend(vtextrulerGetClass(d), vobjectSTORE, (d, r))

#define vtextrulerSetData(e, d)	\
	vclassSend(vtextrulerGetClass(e), vdialogSET_ITEM_DATA, (e, d))

#define vtextrulerSetDefaultRuler(r,d)	\
	vclassSend(vtextrulerGetClass(r), vtextrulerSET_DEFAULT_RULER, (r, d))

#define vtextrulerGetDefaultRuler(r)	\
	vclassSend(vtextrulerGetClass(r), vtextrulerGET_DEFAULT_RULER, (r))

extern vportLINK const vchar 	*_vtextrulerPredefs[];


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtextrulerINCLUDED */

