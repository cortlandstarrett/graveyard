/* $Id: vinput.h,v 1.18 1997/10/17 21:47:31 dimitri Exp $ */

/************************************************************

    vinput.h

    C Interface file for the Input Method Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vinputINCLUDED
#define vinputINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportCPLUSPLUS_SOURCE)
#define _vinputSTRUCT              
class vportCLASS_LINK vwindow;
#else
#define _vinputSTRUCT struct
struct vwindow;
#endif

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vinputPRIMARY_HILITE            = 0x01,
    vinputSECONDARY_HILITE          = 0x02,
    vinputTERTIARY_HILITE           = 0x04
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vinput               vinput;
typedef struct vinputClass          vinputClass;
typedef struct vinputPreedit        vinputPreedit;

typedef void (*vinputDriverProc)(vinput *input);

typedef unsigned char               vinputHilite;

struct vinputPreedit {
    long                            position;
    long                            oldLength;
    long                            newLength;
    long                            confirmLength;
    long                            totalLength;
    vchar                          *string;
    vinputHilite                   *hilite;
    long                            caret;
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vinputStartup(
    void
    );


vinputClass *vinputGetDefaultClass(
    void
    );

vinput *vinputCreate(
    void
    );

vinput *vinputCreateOfClass(
    vinputClass			   *clas
    );

void vinputDestroy(
    vinput			   *input
    );

vinputClass *vinputGetClass(
    vinput			   *input
    );

vinstance *vinputGetInstance(
    vinput			   *input
    );

void vinputSetWindow(
    vinput			   *input,
    _vinputSTRUCT vwindow          *window
    );

void vinputOpen(
    vinput			   *input
    );

void vinputClose(
    vinput			   *input
    );

void vinputFocus(
    vinput			   *input
    );

void vinputUnfocus(
    vinput			   *input
    );

void vinputReset(
    vinput			   *input
    );

void vinputSetPoint(
    vinput			   *input,
    int				    x,
    int				    y,
    int				    height,
    int				    base
    );

void vinputSetRect(
    vinput			   *input,
    int				    rx,
    int				    ry,
    int				    rw,
    int				    rh
    );

int vinputIsOpen(
    vinput                         *input
    );

void vinputPreeditStart(
    vinput			   *input
    );

void vinputPreeditDraw(
    vinput			   *input, 
    vinputPreedit		   *preedit
   );

void vinputRegisterDriverFuncs(
    vinputDriverProc		  create,
    vinputDriverProc		  destroy,
    vinputDriverProc		  open,
    vinputDriverProc		  close,
    vinputDriverProc		  focus,
    vinputDriverProc		  unfocus,
    vinputDriverProc		  reset,
    vinputDriverProc		  setPoint,
    vinputDriverProc		  setRect
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vinputOPEN	            = 0x0001
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vinputsys           _vinputsys;

struct vinput {
    vinstance                       instance;
    _vinputSTRUCT vwindow          *window;
    int                             x;
    int                             y;
    int                             height;
    int                             base;
    int                             rx;
    int                             ry;
    int                             rw;
    int                             rh;
    _vinputsys                     *sys;
    unsigned short		    flags;
};

#define vinputINIT                  vinstanceINIT
#define vinputDESTROY               vinstanceDESTROY

#define vinputCLASS(SUPER, INPUT)                                             \
    vinstanceCLASS(SUPER, INPUT);                                             \
    vclassMETHOD(vinputPREEDIT_START, (INPUT *input));                        \
    vclassMETHOD(vinputPREEDIT_DRAW, (INPUT *input, vinputPreedit *preedit))

struct vinputClass {
    vinputCLASS(vinputClass, vinput);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vinputGetInstance(i) \
	vportBASE_OBJECT(i, instance)

#define vinputCreateOfClass(c) \
	((vinput *) vinstanceCreateOfClass((vinstanceClass *) (c)))
#define vinputCreate() vinputCreateOfClass(vinputGetDefaultClass())
#define vinputDestroy(i) \
	vinstanceDestroy(vinputGetInstance(i))

#define vinputGetClass(o) \
	((vinputClass *) vinstanceGetClass(vinputGetInstance(o)))

#define vinputIsOpen(i)	  (((i)->flags&_vinputOPEN)      !=0)

#define vinputPreeditStart(i) \
	vclassSend(vinputGetClass(i), vinputPREEDIT_START, (i))

#define vinputPreeditDraw(i, p) \
	vclassSend(vinputGetClass(i), vinputPREEDIT_DRAW, (i, p))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vinputINCLUDED */
