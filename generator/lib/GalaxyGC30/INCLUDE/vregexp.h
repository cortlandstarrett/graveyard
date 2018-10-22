/* $Id: vregexp.h,v 1.25 1997/02/21 02:33:32 robert Exp $ */

/************************************************************

    vregexp.h
    C Interface file for the Regular Expression Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vregexpINCLUDED
#define vregexpINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#define vregexpEOLN	    	    10
#define _vregexpCODE_INCREMENT	    20
/* #define GENERATE_ASSEMBLY 1 */

/* Values for 'direction' parameter to vregexpSetDirection() */

enum {
    vregexpFORWARD		= 0,
    vregexpBACKWARD		= 1
};

/* Op Codes */	

enum {
    _vregexpRANGE 		= 1,
    _vregexpEND   		= 2,
    _vregexpTAG   		= 3,
    _vregexpONE_OF		= 4,
    _vregexpNOT_ONE_OF		= 5,
    _vregexp0_OR_MORE		= 6,
    _vregexp0_OR_1		= 7,
    _vregexpEND_ONE_OF		= 8,
    _vregexpOR_PAT		= 9,
    _vregexpEND_ALL		= 10
};

/* Literals */

enum {
    _vregexpLITERAL		= 11,
    _vregexpLINE_START		= 12,
    _vregexpLINE_END		= 13,
    _vregexpLIT_STRING		= 14,
    _vregexpLIT_ANY		= 15,
    _vregexpLINE_START_END	= 16,
    _vregexpNO_OP		= 17
};

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vregexp {
    vloadable	object;
    short	numPatterns;
    vbyte	direction;
    vbool	caseSensitive;
    int		endOfLineChar;
    vstr	*text;
    void	*data;
    size_t	codeCount;
    vchar	*code;
    vchar	*segments[10];
} vregexp;

#define vregexpCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct vregexpClass	vregexpClass;

struct vregexpClass {
    vregexpCLASS(vregexpClass, vregexp);
};


/*
 * * * * * * REGULAR EXPRESSION MANAGER FUNCTION PROTOTYPES * * * * * * *
 */
 
void vregexpStartup(void);


vregexp *vregexpCreate(
    vchar		*pattern
    );
    
vregexp *vregexpCreateScribed(
    vscribe		*scribe
    );
    
vregexp *vregexpClone(
    vregexp		*regExpression
    );

void vregexpCopy(
    vregexp		*regExpression,
    vregexp		*target
    );

void vregexpDestroy(
    vregexp		*regExpression
    );
    
vregexp *vregexpLoad(
    vresource		resource
    );

void vregexpStore(
    vregexp		*regExpression,
    vresource		resource
    );

/* Regular Expression attribute modification */

void vregexpSetPattern(
    vregexp			   *regexp,
    const vchar 		   *pattern
    );

void vregexpSetPatternScribed(
    vregexp			   *regexp,
    vscribe			   *pattern
    );

void vregexpSetData(
    vregexp		*regExpression,
    void		*data
    );

void vregexpSetCaseSensitive(
    vregexp		*regExpression,
    int			caseSensitive
    );

void vregexpSetDirection(
    vregexp		*regExpression,
    int			direction
    );

/* Regular Expression attribute access */

const vchar *vregexpGetPattern(
    vregexp			   *regexp
    );

void *vregexpGetData(
    vregexp		*regExpression
    );

vbool vregexpIsCaseSensitive(
    vregexp		*regExpression
    );

int vregexpGetDirection(
    vregexp		*regExpression
    );

/* Searching and Matching */

vchar *vregexpSearch(
    vregexp		*regExpression,
    const vchar		*text,
    int			length,
    int			*resultLength
    );

vbool vregexpMatch(
    vregexp		*regExpression,
    vchar		ch
    );
    
vchar *vregexpSearchLiteral(
    const vchar		*literalTarget,
    const vchar		*text,
    int			length,
    int			caseSensitive,
    int			direction
    );

vchar *vregexpGetSegment(
    vregexp		*regExpression,
    int			segment
    );

void vregexpClearAllSegments(
    vregexp		*regExpression
    );

/*
 * * * * * * * * * P_R_I_V_A_T_E FUNCTION PROTOTYPES * * * * * * * * * *
 */


vregexpClass *_vregexpGetDefaultClass(void);

vregexpClass *_vregexpGetClass(
    vregexp			   *regexp
    );

vloadable *_vregexpGetObject(
    vregexp			   *regexp
    );

vregexp *_vregexpCreateOfClass(
    vregexpClass                   *clas
    );

void _vregexpInitOfClass(
    vregexp                        *regexp,
    vregexpClass                   *clas
    );

void _vregexpAssemble(vregexp *regexp);
void _vregexpDisassemble(vregexp *regexp);

void _vregexpSetEndOfLineChar(vregexp *regexp, int eol);
int _vregexpGetEndOfLineChar(vregexp *regexp);


/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */

#define _vregexpGetObject(e) \
    (vportBASE_OBJECT(e, object))

#define _vregexpGetClass(e) \
    ((vregexpClass*)vloadableGetClass(_vregexpGetObject(e)))

#define _vregexpCreateOfClass(c) \
    ((vregexp*)vloadableCreateOfClass((vloadableClass*)(c)))

#define _vregexpInitOfClass(e, c) \
    vloadableInitOfClass(_vregexpGetObject(e), (vloadableClass*)(c))

#define vregexpClone(e) \
    ((vregexp*)vloadableClone(_vregexpGetObject(e)))

#define vregexpCreate(s) \
    vregexpCreateScribed(vcharScribe(s)) 

#define vregexpDestroy(e) \
    vloadableDestroy(_vregexpGetObject(e))

#define vregexpCopy(e, t) \
    vclassSend(_vregexpGetClass(e), vloadableCOPY, (e, t))

#define vregexpStore(e, r) \
    vclassSend(_vregexpGetClass(e), vloadableSTORE, (e, r))

#define vregexpGetPattern(r) \
    ((r)->text)
#define vregexpSetPattern(r, p) \
    vregexpSetPatternScribed(r, vcharScribe(p))

#define vregexpSetData(e,d)		((e)->data = (d))
#define vregexpGetData(e)		((e)->data)
#define vregexpSetDirection(e,d)	((e)->direction = (d))
#define vregexpGetDirection(e)		((e)->direction)
#define vregexpSetCaseSensitive(e,s)	((e)->caseSensitive = (s))
#define vregexpIsCaseSensitive(e)	((e)->caseSensitive)

#define vregexpGetSegment(e,i)		((e)->segments[i])

#define _vregexpSetEndOfLineChar(e,l)	((e)->endOfLineChar = (l))
#define _vregexpGetEndOfLineChar(e)	((e)->endOfLineChar)

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vregexpINCLUDED */

