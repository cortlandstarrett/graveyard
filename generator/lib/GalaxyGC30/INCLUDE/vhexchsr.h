/* $Id: vhexchsr.h,v 1.3 1997/08/13 16:33:39 robert Exp $ */

/************************************************************

    vhexchsr.h
    C Interface to the Hex Chsrer

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vhexchsrINCLUDED
#define vhexchsrINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vhexINCLUDED
#include vhexHEADER
#endif
  


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vhexchsr		vhexchsr;
typedef struct vhexchsrClass		vhexchsrClass;

typedef int (*vhexchsrApplyProc) (
    vhexchsr			*chooser,
    void                        *buffer,
    int                          length,
    int                          dataLength
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vhexchsrStartup(void);

vhexchsrClass *vhexchsrGetDefaultClass(void);

void vhexchsrClose(
    vhexchsr		*chooser
    );

vhexchsr *vhexchsrCreate(void);

vhexchsr *vhexchsrCreateOfClass(
    vhexchsrClass		*clas
    );

void vhexchsrDestroy(
    vhexchsr		*chooser
    );

vhexchsrApplyProc vhexchsrGetApply(
    vhexchsr		*chooser
    );

int vhexchsrGetBufferLength(
    vhexchsr            *chooser
    );

void *vhexchsrGetBufferPointer(
    vhexchsr		*chooser
    );

vhexchsrClass *vhexchsrGetClass(
    vhexchsr		*chooser
    );

vconfirm *vhexchsrGetConfirm(
    vhexchsr		*chooser
    );

const void *vhexchsrGetData(
    vhexchsr		*chooser
    );

int vhexchsrGetDataLength(
    vhexchsr            *chooser
    );

vdialog *vhexchsrGetDialog(
    vhexchsr		*chooser
    );

int vhexchsrHasBufferResize(
    vhexchsr            *chooser
    );

void vhexchsrOpen(
    vhexchsr		*chooser
    );

const vname *vhexchsrProcess(
    vhexchsr            *chooser
    );

void vhexchsrSetApply(
    vhexchsr		*chooser,
    vhexchsrApplyProc	 applyProc
    );

void vhexchsrSetBuffer(
    vhexchsr		*chooser,
    void                *buffer,
    int                  length,
    int                  dataLength
    );

void vhexchsrSetBufferLength(
    vhexchsr            *chooser,
    int                  length
    );

void vhexchsrSetBufferPointer(
    vhexchsr		*chooser,
    void                *buffer
    );

void vhexchsrSetBufferResize(
    vhexchsr            *chooser,
    int                  onOff
    );

void vhexchsrSetData(
    vhexchsr		*chooser,
    const void		*data
    );

void vhexchsrSetDataLength(
    vhexchsr            *chooser,
    int                  dataLength
    );


/* Other Routines */



/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
  _vhexchsrFLAGS_BUFFER_RESIZE = 1,
  _vhexchsrFLAGS_IS_PROCESSED = 2
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhexchsr {
  vconfirm	       confirm;

  short                flags;

  vhex                *hex1;
  vhex                *hex2;
  vhex                *hex3;

  vhexchsrApplyProc    applyProc;

  void                *bufferPointer;
  int                  bufferLength;
  int                  dataLength;
};

/*
 * Hex Chsrer Class definition
 */

#define vhexchsrCLASS(SUPER, CONFIRM, NOTIFY, APPLY) \
    vconfirmCLASS(SUPER, CONFIRM, NOTIFY); \
    vclassMETHOD(vhexchsrSET_APPLY, \
                 (CONFIRM *chooser, APPLY applyProc)); \
    vclassMETHOD(vhexchsrSET_BUFFER, \
		 (CONFIRM *chooser, \
		  void *buffer, int length, int dataLength)); \
    vclassMETHOD(vhexchsrSET_BUFFER_LENGTH, \
		 (CONFIRM *chooser, int length)); \
    vclassMETHOD(vhexchsrSET_BUFFER_POINTER, \
		 (CONFIRM *chooser, void *buffer)); \
    vclassMETHOD(vhexchsrSET_BUFFER_RESIZE, \
		 (CONFIRM *chooser, int onOff)); \
    vclassMETHOD(vhexchsrSET_DATA_LENGTH, \
		 (CONFIRM *chooser, int dataLength)); \
    vclassMETHOD_RET(vhexchsrHOOK_APPLY, int, \
		     (CONFIRM *chooser, \
		      void *buffer, int length, int dataLength)); \
    vclassMETHOD_RET(vhexchsrPROCESS, const vname *, \
                 (CONFIRM *chooser))

struct vhexchsrClass {
    vhexchsrCLASS(vhexchsrClass, vhexchsr,
		  vconfirmHookProc, vhexchsrApplyProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vhexchsrGetConfirm(h)     vportBASE_OBJECT((h), confirm)
#define vhexchsrGetDialog(h)	  vconfirmGetDialog(vhexchsrGetConfirm(h))

#define vhexchsrClose(c) \
    vclassSend(vhexchsrGetClass(c), vwindowCLOSE, (c))
#define vhexchsrCreateOfClass(c) \
    ((vhexchsr *)vconfirmCreateOfClass((vconfirmClass*)(c)))
#define vhexchsrCreate() \
    vhexchsrCreateOfClass(vhexchsrGetDefaultClass())
#define vhexchsrDestroy(h) \
    vconfirmDestroy(vhexchsrGetConfirm(h))
#define vhexchsrGetApply(h) \
    ((h)->applyProc)
#define vhexchsrGetBufferLength(h) \
    ((h)->bufferLength)
#define vhexchsrGetBufferPointer(h) \
    ((h)->bufferPointer)
#define vhexchsrHasBufferResize(h) \
    (((h)->flags&_vhexchsrFLAGS_BUFFER_RESIZE)!=0)
#define vhexchsrGetDataLength(h) \
    ((h)->dataLength)
#define vhexchsrGetClass(h) \
    ((vhexchsrClass *) vconfirmGetClass(vhexchsrGetConfirm(h)))
#define vhexchsrGetData(h) \
    vconfirmGetData(vhexchsrGetConfirm(h))
#define vhexchsrOpen(h)	\
    vclassSend(vhexchsrGetClass(h), vwindowOPEN, (h))
#define vhexchsrProcess(h)	\
    vclassSend(vhexchsrGetClass(h), vhexchsrPROCESS, (h))
#define vhexchsrSetApply(h, p) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_APPLY, (h, p))
#define vhexchsrSetBuffer(h, b, l, d) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_BUFFER, (h, b, l, d))
#define vhexchsrSetBufferLength(h, l) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_BUFFER_LENGTH, (h, l))
#define vhexchsrSetBufferPointer(h, b) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_BUFFER_POINTER, (h, b))
#define vhexchsrSetBufferResize(h, f) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_BUFFER_RESIZE, (h, f))
#define vhexchsrSetData(h, d) \
    vclassSend(vhexchsrGetClass(h), vwindowSET_DATA, (h, d))
#define vhexchsrSetDataLength(h, l) \
    vclassSend(vhexchsrGetClass(h), vhexchsrSET_DATA_LENGTH, (h, l))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vhexchsrINCLUDED */

