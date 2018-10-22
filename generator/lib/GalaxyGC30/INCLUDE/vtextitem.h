/* $Id: vtextitem.h,v 1.72 1997/08/08 21:51:59 dimitri Exp $ */

/************************************************************

    vtextitem.h
    C Interface to static and editable text items

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vtextitemINCLUDED
#define vtextitemINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Global text view strings
 */

enum {
    _vtextitem_OneLine,
    _vtextitem_Selectable,
    _vtextitem_Modifyable,
    _vtextitem_Modifiable,
    _vtextitem_AcceptTab,
    _vtextitem_Count
};

#define vtextitem_OneLine       (_vtextitemPredefs[_vtextitem_OneLine])
#define vtextitem_Selectable    (_vtextitemPredefs[_vtextitem_Selectable])
#define vtextitem_Modifyable    (_vtextitemPredefs[_vtextitem_Modifyable])
#define vtextitem_Modifiable    (_vtextitemPredefs[_vtextitem_Modifiable])
#define vtextitem_AcceptTab     (_vtextitemPredefs[_vtextitem_AcceptTab])

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtextitem          vtextitem;
typedef struct vtextitemClass     vtextitemClass;
typedef struct vtextitemText	  vtextitemText;
typedef struct vtextitemTextClass vtextitemTextClass;
typedef vtextRuler		  vtextitemTextRuler;
typedef vtextStyle		  vtextitemTextStyle;



typedef void (*vtextitemNoteProc)(vtextitem *textItem,
				  vevent *event, int message);

struct vtextitem {
    vtextview	item;
    int		textitemFlags;
};

/*
 * Text Item Class Definition
 */

#define vtextitemCLASS(SUPER, ITEM, NOTIFY)				     \
  vtextviewCLASS(SUPER, ITEM, NOTIFY);					     \
  vclassMETHOD_RET(vtextitemSCRIBE_TEXT, vscribe *, (ITEM *textitem));	     \
  vclassMETHOD(vtextitemSET_TEXT, 	    	(ITEM *textitem,	     \
						 const vchar *text));	     \
  vclassMETHOD(vtextitemSET_TEXT_SCRIBED,   	(ITEM *textitem, 	     \
						 vscribe *scribe)); 	     \
  vclassMETHOD_RET(vtextitemCREATE_TEXT_DATA, vtext *,			     \
		                                (ITEM *textitem))

struct vtextitemClass {
    vtextitemCLASS(vtextitemClass, vtextitem, vtextitemNoteProc);
};

struct vtextitemText {
    vtext	text;
    vtextitem	*owner;
};

#define vtextitemTextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)	\
vtextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)

struct vtextitemTextClass {
    vtextitemTextCLASS(vtextitemTextClass, vtextitemText, vtextSelection, 
		       vtextRuler, vtextStyle);
};

vportALIAS(vtextitemTextRuler, vtextRuler)
vportALIAS(vtextitemTextStyle, vtextStyle)

/*
 * * * * * * * * * TEXT ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextitemStartup(void);


/* Text Item Class Functions */

vtextitemClass *vtextitemGetDefaultClass(void);

vtextitemTextClass *vtextitemGetDefaultTextDataClass(void);

/* Initialization and allocation */

vtextitem *vtextitemCreate(void);

vtextitem *vtextitemCreateOfClass(
    vtextitemClass	*clas
    );

vtextitem *vtextitemClone(
    vtextitem	    	*textItem
    );

void vtextitemCopy(
    vtextitem    	*textItem,
    vtextitem	    	*targetItem
    );

void vtextitemCopyInit(
    vtextitem    	*textItem,
    vtextitem	    	*targetItem
    );

void vtextitemInit(
    vtextitem	    	*textItem
    );

void vtextitemInitOfClass(
    vtextitem		*textItem,
    vtextitemClass	*clas
    );

void vtextitemDestroy(
    vtextitem	    	*textItem
    );

vtextitem *vtextitemLoad(
    vresource		resource
    );

void vtextitemLoadInit(
    vtextitem		*textItem,
    vresource		resource
    );

void vtextitemStore(
    vtextitem		*textItem,
    vresource		resource
    );

/* Getting and Setting Text */

void vtextitemSetText(
    vtextitem	        *textItem,
    const vchar		*text
    );

void vtextitemSetTextScribed(
    vtextitem	        *textItem,
    vscribe		*scribe
    );

void vtextitemGetText(
    vtextitem		*textItem,
    vchar		*text,
    long		length
    );

vscribe *vtextitemScribeText(
    register vtextitem	*textItem
    );

vstr *vtextitemGetTextAsString(
    vtextitem		*textItem
    );

int vtextitemGetTextAsInt(
    vtextitem		*textItem
    );

double vtextitemGetTextAsFloat(
    vtextitem		*textItem
    );

/* Text attribute modification */

void vtextitemSetData(
    vtextitem		*textItem,
    void		*data
    );

void vtextitemSetNotify(
    vtextitem		*textItem,
    vtextitemNoteProc	noteProc
    );

void vtextitemSetStatic(
    vtextitem		*textItem
    );

void vtextitemSetEditable(
    vtextitem		*textItem
    );

void vtextitemSetJustification(
    vtextitem		*textItem,
    int			justification
    );

void vtextitemSetWrap(
    vtextitem		*textItem,
    int			wrap
    );

void vtextitemSetModifiable(
    vtextitem		*textItem,
    int			modifiable
    );

void vtextitemSetSelectable(
    vtextitem		*textItem,
    int			selectable
    );

void vtextitemSetOneLine(
    vtextitem		*textItem,
    int			oneline
    );

void vtextitemSetAcceptTab(
    vtextitem		*textItem,
    int			acceptTab
    );

void vtextitemSetTextModifiable(
    vtextitem		*textItem,
    int			onOff
    );

void vtextitemSetRuler(
    vtextitem		*textItem,
    vtextRuler		*ruler
    );

/* Text attribute access */

vtextitemClass *vtextitemGetClass(
    vtextitem		*textItem
    );

void *vtextitemGetData(
    vtextitem		*textItem
    );

vtextitemNoteProc vtextitemGetNotify(
    vtextitem		*textItem
    );

vbool vtextitemIsStatic(
    vtextitem		*textItem
    );

int vtextitemGetJustification(
    vtextitem		*textItem
    );

vbool vtextitemGetWrap(
    vtextitem		*textItem
    );

vbool vtextitemIsModifiable(
    vtextitem		*textItem
    );

vbool vtextitemIsSelectable(
    vtextitem		*textItem
    );

vbool vtextitemIsOneLine(
    vtextitem		*textItem
    );

vbool vtextitemIsTextModifiable(
    vtextitem		*textItem
    );

vbool vtextitemHasAcceptTab(
    vtextitem		*textItem
    );

vtextRuler *vtextitemGetRuler(
    vtextitem		*textItem
    );

/* Other Routines */

void vtextitemSelectAll(
    vtextitem		*textItem
    );

vdialogItem *vtextitemGetItem(
    vtextitem		*textItem
    );

vtextview *vtextitemGetView(
    vtextitem		*textItem
    );

vtext *vtextitemGetTextData(
    vtextitem		*textItem
    );

vtextSelection *vtextitemGetSelection(
    vtextitem		*textItem
    );


/*
 * vtextitemText
 */
vtext *vtextitemTextGetText(
    vtextitemText	*text
    );

/*
 * * * * * * * * * * DEPRECATED PROTOTYPES * * * * * * * * * * * * *
 */


vbool vtextitemIsModifyable(
    vtextitem		*textItem
    );

void vtextitemSetModifyable(
    vtextitem		*textItem,
    int			modifiable
    );

vscribe *vtextitemGetTextScribed(
    register vtextitem	*textItem
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define _vtextitemINIT_TEXT_SIZE		256

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for textitemFlags in a textitem */

enum {
    _vtextitemMODIFIABLE		= 0x00000001,
    _vtextitemSELECTABLE		= 0x00000002,
    _vtextitemONE_LINE			= 0x00000004,
    _vtextitemACCEPT_TAB		= 0x00000008,
    _vtextitemTEXT_MODIFIABLE		= 0x00000010,
    _vtextitemCOPYING_TEXT		= 0x00000100,
    _vtextitemCALCULATE_OFF		= 0x00000200
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextitemGetView(i)             vportBASE_OBJECT(i, item)
#define vtextitemGetItem(i)		(vtextviewGetItem(vtextitemGetView(i)))

#define vtextitemCreateOfClass(c)	\
	((vtextitem *) vtextviewCreateOfClass((vtextviewClass *) (c)))
#define vtextitemClone(v)		\
	((vtextitem *) vdialogCloneItem((vdialogItem *) (v)))
#define vtextitemInitOfClass(e,c)	\
	vdialogInitItemOfClass((vdialogItem  *) (e), (vdialogItemClass *) (c))

#define vtextitemInit(e)	  vtextitemInitOfClass((e), \
				       vtextitemGetDefaultClass());
#define vtextitemCopyInit(c,t)    vtextviewCopyInit(vtextitemGetView(c), \
						        (vtextview*)(t))
#define vtextitemLoad(r)          ((vtextitem*)vdialogLoadItem(r))
#define vtextitemLoadInit(c,r)   \
                         vdialogLoadInitItem(vtextitemGetItem(c), r)
#define vtextitemDestroy(v)	 vdialogDestroyItem(vtextitemGetItem(v))

#define vtextitemGetClass(e) \
	((vtextitemClass*)vdialogGetItemClass((vdialogItem *) (e)))

#define vtextitemGetTextData(i)   vtextviewGetTextData((vtextitemGetView(i)))
#define vtextitemGetSelection(i)  vtextviewGetSelection((vtextitemGetView(i)))

#define vtextitemIsModifiable(i)	\
   ((((i)->textitemFlags) & _vtextitemMODIFIABLE) != 0)
#define vtextitemIsSelectable(i)	\
   ((((i)->textitemFlags) & _vtextitemSELECTABLE) != 0)
#define vtextitemIsOneLine(i)		\
   ((((i)->textitemFlags) & _vtextitemONE_LINE) != 0)
#define vtextitemHasAcceptTab(i)	\
   ((((i)->textitemFlags) & _vtextitemACCEPT_TAB) != 0)
#define vtextitemIsTextModifiable(i)	\
   ((((i)->textitemFlags) & _vtextitemTEXT_MODIFIABLE) != 0)

#define vtextitemIsStatic(i)		\
   (!vtextitemIsModifiable(i) && !vtextitemIsSelectable(i))

#define vtextitemGetRuler(i)		\
	 (vtextGetDefaultRuler(vtextviewGetTextData(vtextitemGetView(i))))

#define vtextitemGetData(e)      	vdialogGetItemData(vtextitemGetItem(e))

#define vtextitemSetNotify(e,p)		\
	 (vtextviewSetNotify(vtextitemGetView(e), (vtextviewNoteProc) (p)))
#define vtextitemGetNotify(e)		\
	 ((vtextitemNoteProc ) vtextviewGetNotify(vtextitemGetView(e)))

#define vtextitemSelectAll(e)	\
    vtextSelectRange(vtextitemGetTextData(e), vtextitemGetSelection(e), \
		     vtextLength(vtextitemGetTextData(e)), 0)

#define vtextitemSetModifyable(i,m)	vtextitemSetModifiable(i,m)
#define vtextitemIsModifyable(i)	vtextitemIsModifiable(i)
#define vtextitemGetTextScribed(i)	vtextitemScribeText(i)


#define vtextitemTextGetText(i)		(vportBASE_OBJECT((i), text))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vtextitemCopy(v,t)	 vclassSend(vtextitemGetClass(v), \
					    vobjectCOPY, (v, t))
#define vtextitemStore(v,t)	 vclassSend(vtextitemGetClass(v), \
					    vobjectSTORE, (v, t))
#define vtextitemSetData(v, d)	 vclassSend(vtextitemGetClass(v), \
					    vdialogSET_ITEM_DATA, (v,d))
#define vtextitemScribeText(v)   vclassSend(vtextitemGetClass(v), \
					    vtextitemSCRIBE_TEXT, (v))
#define vtextitemSetText(v,t)    vclassSend(vtextitemGetClass(v), \
					    vtextitemSET_TEXT, (v,t))
#define vtextitemSetTextScribed(v,s) vclassSend(vtextitemGetClass(v), \
					    vtextitemSET_TEXT_SCRIBED, (v,s))

/*
 * * * * * * * * * TEXT ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vchar 		*_vtextitemPredefs[];

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vtextitemINCLUDED */

