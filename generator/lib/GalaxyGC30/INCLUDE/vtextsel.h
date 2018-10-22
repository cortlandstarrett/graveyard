/* $Id: vtextsel.h,v 1.3 1996/09/09 18:23:31 dimitri Exp $ */

/************************************************************

    vtextselection.h
    C Interface to the Text Manager's selection module

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vtextselectionINCLUDED
#define vtextselectionINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for 'selectMethod' parameter to 'vtextselectionSetSelectMethod' */

enum {
    vtextselectionSELECT_NORMAL		= 0,
    vtextselectionSELECT_RECTANGULAR	= 1,
    vtextselectionSELECT_LINES		= 2,
    vtextselectionSELECT_UNION		= 3,
    vtextselectionSELECT_DISCONTIGUOUS	= 4	/* Not implemented */
};

enum {
    vtextselectionCARET_IMPLIED		= 0,
    vtextselectionCARET_AT_START	= 1,
    vtextselectionCARET_AT_END		= 2,
    vtextselectionCARET_INDEPENDENT	= 3
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtextselection		  vtextselection;
typedef struct vtextselectionClass	  vtextselectionClass;

typedef struct vtextselectionPosition {
    long	start;
    long	end;
    long	length;
} vtextselectionPosition;


/* Forward declared for references */
typedef struct vtext			  vtext;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextselectionStartup(void);


vtextselectionClass *vtextselectionGetDefaultClass(
    void
    );

vtextselectionClass *vtextselectionGetClass(
    vtextselection	*selection
    );

vobservable *vtextselectionGetObservable(
    vtextselection	*selection
    );

vloadable *vtextselectionGetLoadable(
    vtextselection	*selection
    );

vinstance *vtextselectionGetInstance(
    vtextselection	*selection
    );

vtextselection *vtextselectionCreate(
    void
    );

vtextselection *vtextselectionCreateOfClass(
    vtextselectionClass	*clas
    );

void vtextselectionInit(
    vtextselection	*selection
    );

void vtextselectionInitOfClass(
    vtextselection	*selection,
    vtextselectionClass	*clas
    );

void vtextselectionDestroy(
    vtextselection	*selection
    );

vtextselection *vtextselectionClone(
    vtextselection 	*selection
    );

void vtextselectionCopyInit(
    vtextselection 	*source,
    vtextselection 	*destination
    );

void vtextselectionCopy(
    vtextselection 	*source,
    vtextselection 	*destination
    );

vtextselection *vtextselectionLoad(
    vresource		 resource
    );

void vtextselectionLoadInit(
    vtextselection 	*selection,
    vresource		 resource
    );

void vtextselectionStore(
    vtextselection 	*selection,
    vresource		 resource
    );

void vtextselectionDump(
    vtextselection 	*selection,
    FILE 		*stream
    );

void vtextselectionSetText(
    vtextselection	*selection,
    vtext		*text
    );

vtext *vtextselectionGetText(
    vtextselection	*selection
    );

void vtextselectionSetSelectMethod(
    vtextselection	*selection,
    int			 method
    );
    
int vtextselectionGetSelectMethod(
    vtextselection	*selection
    );

void vtextselectionSetCaretBehavior(
    vtextselection	*selection,
    int			 behavior
    );
    
int vtextselectionGetCaretBehavior(
    vtextselection	*selection
    );

void vtextselectionSelectRange(
    vtextselection	*selection,
    long		 startPosition,
    long		 endPosition
    );   

void vtextselectionSelectLineRange(
    vtextselection	*selection,
    long		 startLine,
    long		 endLine
    );

void vtextselectionSelectRectangularRange(
    vtextselection	*selection,
    long		 startLine,
    long		 endLine,
    int			 leftPoint,
    int			 rightPoint
    );

void vtextselectionPreadjustText(
    vtextselection	*selection,
    long		 position,
    long		 delta
    );

void vtextselectionAdjustText(
    vtextselection	*selection,
    long		 position,
    long		 delta
    );

void vtextselectionSetCaret(
    vtextselection	*selection,
    long		 position
    );

vbool vtextselectionIsPositionSelected(
    vtextselection 	*selection,
    long                 position
    );

vbool vtextselectionIsEmpty(
    vtextselection 	*selection
    );

long vtextselectionGetCaret(
    vtextselection	*selection
    );

long vtextselectionGetStart(
    vtextselection	*selection
    );

long vtextselectionGetEnd(
    vtextselection	*selection
    );

long vtextselectionGetLength(
    vtextselection	*selection
    );

long vtextselectionGetStartLine(
    vtextselection	*selection
    );

long vtextselectionGetEndLine(
    vtextselection	*selection
    );

long vtextselectionGetLineCount(
    vtextselection	*selection
    );

int vtextselectionGetLeftPoint(
    vtextselection	*selection
    );

int vtextselectionGetRightPoint(
    vtextselection	*selection
    );

int vtextselectionGetPoint(
    vtextselection	*selection,
    long		 position
    );

long vtextselectionGetPointPosition(
    vtextselection	*selection,
    long		 line,
    int			 point
    );

long vtextselectionGetLine(
    vtextselection	*selection,
    long		 position
    );

long vtextselectionGetLineStart(
    vtextselection	*selection,
    long		 line
    );

long vtextselectionGetLineEnd(
    vtextselection	*selection,
    long		 line
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum {
    _vtextselectionDONT_PRE_OBSERVE_SELECT = 0x01,
    _vtextselectionDONT_OBSERVE_SELECT	   = 0x02,
    _vtextselectionPRE_EXISTING		   = 0x04
};

/*
 * vtextselection
 */

struct vtextselection {
    vobservable		    super;

    vtext		   *text;
    short		    index;
    vbyte		    flags;
    vbyte		    selectMethod;
    vbyte		    caretBehavior;

    long		    caret;
    vtextselectionPosition  position;
    long		    startLine;
    long		    endLine;
    int			    leftPoint;
    int			    rightPoint;

    const void		   *data;
};

#define vtextselectionCLASS(CLASS, SELECTION)				\
    vobservableCLASS(CLASS, SELECTION)

struct vtextselectionClass
{
  vtextselectionCLASS(vtextselectionClass, vtextselection);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vtextselectionPosition *_vtextselectionGetPositionInfo(
						vtextselection *selection);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextselectionGetObservable(s)	vportBASE_OBJECT(s, super)
#define vtextselectionGetLoadable(s) \
    vobservableGetLoadable(vtextselectionGetObservable(s))
#define vtextselectionGetInstance(s) \
    vloadableGetInstance(vtextselectionGetLoadable(s))
#define vtextselectionGetClass(s) \
    ((vtextselectionClass*)vloadableGetClass(vtextselectionGetLoadable(s)))

#define vtextselectionCreateOfClass(c) \
    ((vtextselection *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextselectionCreate() \
    vtextselectionCreateOfClass(vtextselectionGetDefaultClass())
#define vtextselectionInitOfClass(s,c) \
    vloadableInitOfClass(vtextselectionGetLoadable(s), (vloadableClass *)(c))
#define vtextselectionInit(s) \
    vtextselectionInitOfClass((s), vtextselectionGetDefaultClass())
#define vtextselectionDestroy(s) \
    vloadableDestroy(vtextselectionGetLoadable(s))

#define vtextselectionClone(s) \
    ((vtextselection *) vloadableClone(vtextselectionGetLoadable(s)))
#define vtextselectionCopy(s,t) \
    vloadableCopy(vtextselectionGetLoadable(s), vtextselectionGetLoadable(t))
#define vtextselectionCopyInit(s,t) \
    vloadableCopyInitOfSubclass(vtextselectionGetLoadable(s), \
				vtextselectionGetLoadable(t), \
			(vloadableClass *) vtextselectionGetDefaultClass())

#define vtextselectionLoad(r) \
    ((vtextselection *) vloadableLoadOfSubclass(r, \
			(vloadableClass *) vtextselectionGetDefaultClass()))
#define vtextselectionLoadInit(s,r) \
    vloadableLoadInitOfSubclass(vtextselectionGetLoadable(s), (r), \
			(vloadableClass *) vtextselectionGetDefaultClass())
#define vtextselectionStore(s,r) \
    vloadableStore(vtextselectionGetLoadable(s), (r))

#define vtextselectionDump(s,f) \
    vloadableDump(vtextselectionGetLoadable(s), (f))

#define vtextselectionGetText(s) \
    ((s)->text)
#define vtextselectionGetSelectMethod(s) \
    ((s)->selectMethod)
#define vtextselectionGetCaretBehavior(s) \
    ((s)->caretBehavior)

#define vtextselectionGetCaret(s) \
    ((s)->caret)
#define vtextselectionGetStart(s) \
    ((s)->position.start)
#define vtextselectionGetEnd(s) \
    ((s)->position.end)
#define vtextselectionGetLength(s) \
    ((s)->position.end - (s)->position.start)
#define vtextselectionGetLeftPoint(s) \
    ((s)->leftPoint)
#define vtextselectionGetRightPoint(s) \
    ((s)->rightPoint)

#define vtextselectionIsEmpty(s) \
    ((s)->position.end == (s)->position.start)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtextselectionINCLUDED */
