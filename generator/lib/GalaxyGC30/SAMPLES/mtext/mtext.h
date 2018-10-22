/* $Id: mtext.h,v 1.2 1995/01/15 22:42:56 chad Exp $ */
/* mtext.h -- Header to MiniText, a sample dialog item.
 *
 * See the file "template.h" for a high-level overview of "what goes where."
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
 *
 * Even though this header file looks like it was born fully-formed from
 * my mind, we all know it doesn't work that way.  Here's the order things
 * were done in the construction of this header:
 *
 * step zero:
 *    construct the template
 *    put in stubs for ID attributes and selector command identifiers
 *    put in the forward reference for mtext and mtextClass
 *    define the type of the note proc
 *    put in basic "class" level prototypes (such as init, destroy, clone)
 *    add the initial object structure and initial class macro (just contains
 *        vdialogItem stuff)
 *    put in the macros and methods for the "class" functions
 * step one:
 *    add vchar buffer and int counts to object
 *    add GetLength and GetText to API (defined as macros)
 *    add anchor (insertion point)
 *    add DrawCaret method to macro, prototype, and vclassSend #define
 *    add DrawCaret state constants to public constant section
 *    add Set/GetAnchor calls
 * step two:
 *    add insertChar method
 *    add selectors for backspace and delete
 *    add Dump to API
 *    add sanity-check mechanism
 * step three:
 *    add selectionEnd to instance
 *    add methods to set this field and draw selected range
 *    add macros for getting the end, as well as selected character count
 * step four:
 *    (nothing)
 * step five:
 *    add methods, macros, and ID Attributes for selectable and modifyable
 *    add vname for the select attribute
 * step six:
 *    add cursor class variable
 *    add calcCursorRect method
 *    add cursor added flag
 *    add cursor rect to instance
 * step seven:
 *    add some vnames for symbol storage
 *    fix typos
 */


#ifndef mtextINCLUDED /* protect ourselves from multiple inclusion */
#define mtextINCLUDED 1


/* #include headers *only* for things referenced in this header file. Don't
 * #include stuff that will only be used for the implementation.
 *
 * Some headers are included for documentation/completeness purposes.
 * vdialogHEADER pulls in vclass, vevent, vresource etc...  Because of
 * the vspamINCLUDED definitions, we prevent the reading and skipping over
 * of huge amounts of now-unnecessary text.
 */

#ifndef vportINCLUDED		/* get our vspamHEADER symbols */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, etc... */
#include vstdHEADER
#endif

#ifndef  vclassINCLUDED		/* well, we *are* doing subclassing here */
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED	/* we're subclassing from vdialogItem */
#include vdialogHEADER
#endif

#ifndef  vresourceINCLUDED	/* some prototypes will use resources */
#include vresourceHEADER
#endif

#ifndef  veventINCLUDED		/* the notification needs an event */
#include veventHEADER
#endif


/*
 * ----- Public Constant Definitions -----
 */

/* this is where you export constants, symbols, enums, #defines, and
 * vnames that your clients are allowed to use
 */


/* ID attribute definitions */

enum {
    mtextID_ATTRIBUTE_SELECT_TYPE = vdialogITEM_NEXT_ID_ATTRIBUTE,
    mtextNEXT_ID_ATTRIBUTE
};



/* selector command identifiers */

enum {
    mtextSELECT_BACKWARD_DELETE = vdialogITEM_NEXT_SELECT,
    mtextSELECT_FORWARD_DELETE,
    mtextNEXT_SELECT
};


/* draw states for mtextDrawCaret () */
enum {
    mtextDRAW,
    mtextREMOVE
};

/* selection states for mtextSetSelectType  () */
enum {
    mtextNO_SELECTION,
    mtextSINGLE_POSITION_ONLY,
    mtextRANGE_SELECTION,
    mtextNEXT_SELECT_TYPE /* for potential expansion by subclasses */
};


/* publically exported vnames. */

#define mtext_SelectType	(_mtextPredefs[_mtext_SelectType])




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


/* object and class forward definition */

typedef struct mtext		mtext;
typedef struct mtextClass 	mtextClass;


/* notification function definition */

typedef void (*mtextNoteProc) (
    mtext	*text,
    vevent	*event
    );




/*
 * ----- Public Function Prototypes -----
 */

/* your complete exported API should be placed here.  No clue as to how
 * things are implemented should be put here.  It doesn't matter if a 
 * particular call is implemented by a macro, a method, or a direct function
 * call.  It should be put here.
 */

/* search for "=-=-" to go to the different classes of functions found
 * within
 */

/*
 * =-=- class/object-level stuff
 */

mtextClass *mtextGetDefaultClass ( 
    void
    );

mtextClass *mtextGetClass ( 
    mtext		*text
    );

mtext *mtextCreateOfClass ( 
    mtextClass		*classToMakeAnInstanceOf
    );

mtext *mtextCreate ( 
    void
    );

mtext *mtextClone ( 
    void
    );

void mtextInitOfClass ( 
    mtext		*text,
    mtextClass		*classToMakeAnInstanceOf
    );

void mtextInit ( 
    mtext		*text
    );

void mtextDestroy ( 
    mtext		*text
    );

void mtextCopy ( 
    mtext		*text,
    mtext		*target
    );

void mtextCopyInit ( 
    mtext		*text,
    mtext		*target
    );

mtext *mtextLoad ( 
    vresource		 resource
    );

void mtextLoadInit ( 
    mtext		*text,
    vresource		 resource
    );

void mtextStore ( 
    mtext		*text,
    vresource		 resource
    );


/*
 * =-=- Query functions
 */

int mtextGetLength ( 
    mtext		*text
    );

const vchar *mtextGetText ( 
    mtext		*text
    );

void mtextDump (
    mtext		*text,
    FILE		*stream
    );


/*
 * =-=- Editing functions
 */

void mtextInsertCharacter ( 
    mtext		*text,
    vchar		 character
    );

/* deletes the char before or after the anchor, or the selected range if
 * it exists. 
 * !!! this feels like a bogus API
 */
void mtextDeleteForward ( 
    mtext		*text
    );

void mtextDeleteBackward ( 
    mtext		*text
    );



/*
 * =-=- Display functions
 */

void mtextDrawCaret ( 
    mtext		*text,
    int			 characterPosition,
    int			 state /* mtextDRAW or mtextREMOVE */
    );

/* won't straddle lines, hence the passing of start/end rather than
 * querying the instance */
void mtextDrawSelectedRange ( 
    mtext		*text,
    int			 start,
    int			 end
    );

void mtextCalcCursorRect ( 
    mtext		*text,
    vrect		rect
    );


/*
 * =-=- Selection functions
 */

void mtextSetAnchor ( 
    mtext		*text,
    int			 position
    );

int mtextGetAnchor ( 
    mtext		*text
    );

void mtextSetSelectionEnd ( 
    mtext		*text,
    int			 position
    );

int mtextGetSelectionEnd ( 
    mtext		*text
    );

int mtextGetSelectionLength ( 
    mtext		*text
    );

void mtextSetSelectType ( 
    mtext		*text,
    int			 type /* mtextNO_SELECTIION, SINGLE_POSITION_ONLY, */
    );			      /* or mtextRANGE_SELECTION */

int mtextGetSelectType ( 
    mtext		*text
    );


/*
 * =-=- Debug support
 */


#if (vdebugDEBUG)

void mtextSanityCheck ( 
    mtext		*text
    );

#endif




/*
 * ----- Private Constant Definitions -----
 */

/* semi-private flag symbols (such as flag field values) should be placed here,
 * as well as private symbols that are referenced in macros.
 */

/* how big to make the character buffer, as well as how much to grow
 * it when it overflows during typing 
 */
enum {
    _mtextALLOC_AMOUNT = 50
};

enum {
    _mtextMODIFYABLE	= 0x0001, /* for later improvement */
    _mtextCURSOR_ADDED  = 0x0002
};


enum {
    _mtext_SelectType,
    _mtext_Contents,
    _mtext_Length,
    _mtext_AllocLeft,
    _mtext_Anchor,
    _mtext_SelectionEnd,
    _mtextPredefCOUNT
};




/*
 * ----- Private Variable Declarations -----
 */

/* publically-scope, yet private access global variables go here.  Typically
 * only vname "predef" tables are put here.
 */

extern const vname *_mtextPredefs[];

/* even though these aren't preceeded with an underscore, they're still
 * considered 'private'.  Why not preceed them with an underscore?  The
 * symbols would conflict with the _mtextPredefEnum symbolage, and I don't
 * feel like coming up with YetAnotherNamingConvention right now.
 */
#define mtext_Contents		(_mtextPredefs[_mtext_Contents])
#define mtext_Length		(_mtextPredefs[_mtext_Length])
#define mtext_AllocLeft		(_mtextPredefs[_mtext_AllocLeft])
#define mtext_Anchor		(_mtextPredefs[_mtext_Anchor])
#define mtext_SelectionEnd	(_mtextPredefs[_mtext_SelectionEnd])


/*
 * ----- Private Type Definitions -----
 */

/* private structures live here, as do the structure for the objects that
 * you are creating.  The class macro and class structure live here
 * as well
 */

struct mtext {
    vdialogItem	item;    /* we're subclassing vdialogItem, so one of these
		          * must be first.  Note it's not a pointer, but a full
		          * dialogItem */

    vchar *contents;     /* where the characters being displayed live */
    int	   length;       /* how long the contents of contents are */
    int    allocLeft;    /* how much space is left at the end of the buffer */

    int    anchor;       /* where the insertion point is/anchor of selection */
    int    selectionEnd; /* where selected range ends */

    vrect  cursorRect;   /* where any displayed cursor is */

    short  selectType;   /* the selection behavior */
    unsigned short flags;  /* attribute storage, bascially */
};




/* mtextCLASS -- the macroFromhell which sets up the table of function pointers
 *		 (methods) and data items (class variables).
 *
 *  -> CLASS  -- the type of class we're defining (mtextClass in this case)
 *  -> ITEM   -- the type of dialog item we're definig (mtext)
 *  -> NOTIFY -- the type of notification function this class uses 
 *		 (mtextNoteProc)
 */
#define mtextCLASS(CLASS, ITEM, NOTIFY)                                       \
    /* include the methods and variables from our superClass. */              \
    vdialogITEM_CLASS (CLASS, ITEM, NOTIFY);                                  \
\
    vclassVARIABLE (mtextCURSOR, vcursor*);                                   \
\
    vclassMETHOD (mtextDRAW_CARET, (ITEM *text,                               \
				    int charPosition, int state));            \
    vclassMETHOD (mtextDRAW_SELECTED_RANGE, (ITEM *text,                      \
					     int start, int end));            \
    vclassMETHOD (mtextCALC_CURSOR_RECT, (ITEM *text, vrect *rect));          \
\
    vclassMETHOD (mtextSET_ANCHOR, (ITEM *text, int position));               \
    vclassMETHOD (mtextSET_SELECTION_END, (ITEM *text, int position));        \
    vclassMETHOD (mtextSET_SELECT_TYPE, (ITEM *text, int type));              \
\
    vclassMETHOD (mtextINSERT_CHARACTER, (ITEM *text, vchar character));      \
    vclassMETHOD (mtextDELETE_FORWARD, (ITEM *text));                         \
    vclassMETHOD (mtextDELETE_BACKWARD, (ITEM *text));                        \
\
    vclassMETHOD (mtextSANITY_CHECK, (ITEM *text))

/* note that the last item doesn't have a semicolon.  It will be added
 * when this macro is invoked, or when it's used in a subclass.
 */


/* here we invoke the macro to make a type of the complete class table
 */
struct mtextClass {
    mtextCLASS (mtextClass, mtext, mtextNoteProc);
};




/*
 * ----- Private Function Macro Definitions -----
 */

/* entry points that are implemented by macros belong here.  Typically,
 * "Set" calls go through methods and "Get" calls are done via macros for
 * a good tradeoff between flexibility and performance.
 */


/* equivalences for existing methods that require casting are put here.
 * Things that can be expressed as direct method dispatches are defined
 * in the next section
 */


/* first, define the macros that give access to the immediate superclass
 * (vdialogItem) as well as the most-useful base of the inheritance tree
 * (vobject), since some cool stuff works on objects directly (like 
 * vobjectIssueCommand)
 */
#define mtextGetItem(m)		(&((m)->item))
#define mtextGetObject(m)	vdialogGetItemObject(mtextGetItem(m))


/* Now for the class/object entrypoints that can't be expressed as simple
 * metod dispatches.  I usually just cut-and-paste these from a known-to-work
 * header.
 */

#define mtextCreateOfClass(c)  \
	((mtext*)vdialogCreateItemOfClass ((vdialogItemClass*)(c)))

#define mtextCreate() \
	mtextCreateOfClass (mtextGetDefaultClass())

#define mtextClone(m) \
	((mtext*)vdialogCloneItem (mtextGetItem(m)))

#define mtextInitOfClass(m, c) \
	vdialogInitItemOfClass (mtextGetItem(m), (vdialogItemClass*)(c))

#define mtextInit(m) \
	mtextInitOfClass(m, mtextGetDefaultClass())

/* vobjectCopyInit does more than just send the message vobjectCOPY_INIT, so
 * this needs to go through the call rather than use a method dispatch.
 * Likewise with vobjectLoadInit
 */
#define mtextCopyInit(m, t) \
	vdialogCopyInitItem (mtextGetItem(m), mtextGetItem(t))

#define mtextLoadInit(m, r) \
	vdialogLoadInitItem (mtextGetItem(m), (r))

#define mtextLoad(r) \
	((mtext*)vdialogLoadItem(r))

#define mtextGetClass(m) \
	((mtextClass*)vdialogGetItemClass(mtextGetItem(m)))


/*
 * now for implementation of some of the API
 */

#define mtextGetLength(m)	((m)->length)
#define mtextGetText(m)		((const vchar*)(m)->contents)

#define mtextGetAnchor(m)	((m)->anchor)
#define mtextGetSelectionEnd(m) ((m)->selectionEnd)

#define mtextGetSelectionLength(m)            \
        ((  (m)->anchor < (m)->selectionEnd ) \
	 ? ((m)->selectionEnd - (m)->anchor)  \
	 : ((m)->anchor - (m)->selectionEnd))

#define mtextGetSelectType(m)	((m)->selectType)




/*
 * ----- Private Function Message Definitions -----
 */

/* Here is where method dispatch macros (the things that boil down to
 * vclassSend) are defined. */

#define mtextDestroy(m) \
	vclassSend (mtextGetClass(m), vinstanceDESTROY, (m))

#define mtextCopy(m, t) \
	vclassSend (mtextGetClass(m), vobjectCOPY, (m, t))

#define mtextStore(m, r) \
	vclassSend (mtextGetClass(m), vobjectSTORE, (m, r))

#define mtextDump(m, s) \
	vclassSend (mtextGetClass(m), vobjectDUMP, (m, s))


/* visual stuff */

#define mtextDrawCaret(m, p, s) \
	vclassSend (mtextGetClass(m), mtextDRAW_CARET, (m, p, s))

#define mtextDrawSelectedRange(m, s, e) \
	vclassSend (mtextGetClass(m), mtextDRAW_SELECTED_RANGE, (m, s, e))

#define mtextCalcCursorRect(m, r) \
	vclassSend (mtextGetClass(m), mtextCALC_CURSOR_RECT, (m, r))


/* selection stuff */

#define mtextSetAnchor(m, p) \
	vclassSend (mtextGetClass(m), mtextSET_ANCHOR, (m, p))

#define mtextSetSelectionEnd(m, p) \
	vclassSend (mtextGetClass(m), mtextSET_SELECTION_END, (m, p))

#define mtextSetSelectType(m, t) \
	vclassSend (mtextGetClass(m), mtextSET_SELECT_TYPE, (m, t))


/* editing stuff */

#define mtextInsertCharacter(m, c) \
	vclassSend (mtextGetClass(m), mtextINSERT_CHARACTER, (m, c))

#define mtextDeleteForward(m) \
	vclassSend (mtextGetClass(m), mtextDELETE_FORWARD, (m))

#define mtextDeleteBackward(m) \
	vclassSend (mtextGetClass(m), mtextDELETE_BACKWARD, (m))


/* debugging stuff */

#if (vdebugDEBUG)
#define mtextSanityCheck(m) \
	vclassSend (mtextGetClass(m), mtextSANITY_CHECK, (m))
#else
#define mtextSanityCheck(m)
#endif




#endif /* mtextINCLUDED */




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
