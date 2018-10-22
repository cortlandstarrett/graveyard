/* $Id: vpixmap.h,v 1.47 1997/09/19 22:31:16 robert Exp $ */

/************************************************************

    vpixmap.h

    C Interface file for the Pixmap Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vpixmapINCLUDED
#define vpixmapINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED
#include vstddefHEADER
#endif

#ifndef  vlimitsINCLUDED
#include vlimitsHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vbufferINCLUDED
#include vbufferHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * pixmaps
 */

#define vpixmapDIMENSION_MIN	    1
#define vpixmapDIMENSION_MAX	    SHRT_MAX

#define vpixmapDEPTH_MIN	    1
#define vpixmapDEPTH_MAX	   (sizeof(vpixmapValue)*CHAR_BIT)

enum {
    vpixmapPRESERVE_NONE	    = 0x0000,
    vpixmapPRESERVE_HORIZ_LEFT	    = 0x0001,
    vpixmapPRESERVE_HORIZ_CENTER    = 0x0002,
    vpixmapPRESERVE_HORIZ_RIGHT	    = 0x0003,
    _vpixmapPRESERVE_HORIZ	    = 0x0003,
    vpixmapPRESERVE_VERT_TOP	    = 0x0004,
    vpixmapPRESERVE_VERT_CENTER	    = 0x0008,
    vpixmapPRESERVE_VERT_BOTTOM	    = 0x000C,
    _vpixmapPRESERVE_VERT	    = 0x000C,
    vpixmapPRESERVE_CLEAR_EXPOSED   = 0x0010
};

/*
 * deprecated pixmaps
 */

enum {
    vpixmapPAD_NONE                 = 0x0000,
    vpixmapPAD_BYTE                 = 0x0001,
    vpixmapPAD_SHORT                = 0x0002,
    vpixmapPAD_LONG                 = 0x0003,
    vpixmapL_S_BIT_FIRST            = 0x0000,
    vpixmapM_S_BIT_FIRST            = 0x0004,
    vpixmapORIGIN_LOWER_LEFT        = 0x0000,
    vpixmapORIGIN_UPPER_LEFT        = 0x0008
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef unsigned long               vpixmapValue;
typedef short                       vpixmapDimension;

typedef struct vpixmap              vpixmap;
typedef struct vpixmapClass         vpixmapClass;

typedef struct vpixmapScanner       vpixmapScanner;
typedef struct vpixmapScannerClass  vpixmapScannerClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vpixmapStartup(void);


/*
 * pixmaps
 */

vpixmapClass *vpixmapGetDefaultClass(
    void
    );

vpixmap *vpixmapGetPrototype(
    void
    );

const vbufferDevice *vpixmapGetBufferDevice(
    void
    );

vpixmap *vpixmapCreateOfClass(
    vpixmapClass                   *clas
    );

vpixmap *vpixmapCreateDefault(
    void
    );

vpixmap *vpixmapCreate(
    int                             w,
    int                             h,
    int                             depth
    );

vpixmap *vpixmapClone(
    vpixmap                        *pixmap
    );

vpixmap *vpixmapCloneWithoutBits(
    vpixmap                        *pixmap
    );

void vpixmapInitOfClass(
    vpixmap                        *pixmap,
    vpixmapClass                   *clas
    );

void vpixmapInitDefault(
    vpixmap                        *pixmap
    );

void vpixmapInit(
    vpixmap                        *pixmap,
    int                             w,
    int                             h,
    int                             depth
    );

void vpixmapDestroy(
    vpixmap                        *pixmap
    );

void vpixmapCopy(
    vpixmap                        *pixmap,
    vpixmap                        *target
    );

void vpixmapCopyWithoutBits(
    vpixmap			   *pixmap,
    vpixmap			   *target
    );

void vpixmapCopyInit(
    vpixmap                        *pixmap,
    vpixmap                        *target
    );

void vpixmapCopyInitWithoutBits(
    vpixmap                        *pixmap,
    vpixmap                        *target
    );

vpixmap *vpixmapLoad(
    vresource                       resource
    );

void vpixmapLoadInit(
    vpixmap                        *pixmap,
    vresource                       resource
    );

void vpixmapStore(
    vpixmap                        *pixmap,
    vresource                       resource
    );

void vpixmapDump(
    vpixmap                        *pixmap,
    FILE                           *stream
    );

void vpixmapClear(
    vpixmap                        *pixmap,
    vpixmapValue                    value
    );

void vpixmapCopyBits(
    vpixmap                        *pixmap,
    vpixmap                        *target
    );

void vpixmapCopyRect(
    vpixmap                        *pixmap,
    vpixmap                        *target,
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             targetX,
    int                             targetY
    );

void vpixmapMarkModified(
    vpixmap                        *pixmap
    );

vbuffer *vpixmapMakeBuffer(
    vpixmap                        *pixmap,
    const vbufferDevice            *device
    );

void vpixmapSetTag(
    vpixmap                        *pixmap,
    const vname                    *tag
    );

const void *vpixmapGetData(
    vpixmap                        *pixmap
    );

void vpixmapSetData(
    vpixmap                        *pixmap,
    const void                     *data
    );

void vpixmapSetSizeMangle(
    vpixmap                        *pixmap,
    int                             w,
    int                             h
    );

void vpixmapSetSizeNoBackground(
    vpixmap                        *pixmap,
    int                             w,
    int                             h,
    int                             preserve
    );

void vpixmapSetSizeWithBackground(
    vpixmap                        *pixmap,
    int                             w,
    int                             h,
    int                             preserve,
    vpixmapValue                    background
    );

void vpixmapSetSize(
    vpixmap                        *pixmap,
    int                             w,
    int                             h,
    int                             preserve,
    vpixmapValue                    background
    );

void vpixmapSetDepth(
    vpixmap                        *pixmap,
    int                             depth
    );

void vpixmapSetPad(
    vpixmap                        *pixmap,
    int                             pad
    );

void vpixmapSetBigEndianByte(
    vpixmap                        *pixmap,
    int                             flag
    );

void vpixmapSetCopyBits(
    vpixmap                        *pixmap,
    int                             flag
    );

void vpixmapSetInverseY(
    vpixmap                        *pixmap,
    int                             flag
    );

void vpixmapSetBits(
    vpixmap                        *pixmap,
    unsigned char                  *bits
    );

vobject *vpixmapGetObject(
    vpixmap                        *pixmap
    );

vobservable *vpixmapGetObservable(
    vpixmap                        *pixmap
    );

vloadable *vpixmapGetLoadable(
    vpixmap                        *pixmap
    );

vinstance *vpixmapGetInstance(
    vpixmap                        *pixmap
    );

vpixmapClass *vpixmapGetClass(
    vpixmap                        *pixmap
    );

const vname *vpixmapGetTag(
    vpixmap                        *pixmap
    );

void vpixmapGetSize(
    vpixmap                        *pixmap,
    int                            *width,
    int                            *height
    );

int vpixmapGetWidth(
    vpixmap                        *pixmap
    );

int vpixmapGetHeight(
    vpixmap                        *pixmap
    );

int vpixmapGetDepth(
    vpixmap                        *pixmap
    );

int vpixmapGetPad(
    vpixmap                        *pixmap
    );

int vpixmapIsBigEndianByte(
    vpixmap                        *pixmap
    );

int vpixmapHasCopyBits(
    vpixmap                        *pixmap
    );

int vpixmapIsInverseY(
    vpixmap                        *pixmap
    );

unsigned char *vpixmapGetBits(
    vpixmap                        *pixmap
    );

size_t vpixmapGetCharWidth(
    vpixmap                        *pixmap
    );

unsigned char *vpixmapGetBufferBits(
    vbuffer                        *buffer
    );

void vpixmapInitScanner(
    vpixmapScanner                 *scanner,
    vpixmap                        *pixmap
    );

void vpixmapInitScannerBits(
    vpixmapScanner                 *scanner,
    vpixmap                        *pixmap,
    unsigned char                  *bits
    );

void vpixmapDestroyScanner(
    vpixmapScanner                 *scanner
    );

void vpixmapMoveTo(
    vpixmapScanner                 *scanner,
    int                             x,
    int                             y
    );

void vpixmapMoveRight(
    vpixmapScanner                 *scanner
    );

void vpixmapMoveLeft(
    vpixmapScanner                 *scanner
    );

void vpixmapMoveUp(
    vpixmapScanner                 *scanner
    );

void vpixmapMoveDown(
    vpixmapScanner                 *scanner
    );

vpixmapValue vpixmapRead(
    vpixmapScanner                 *scanner
    );

vpixmapValue vpixmapReadMoveRight(
    vpixmapScanner                 *scanner
    );

vpixmapValue vpixmapReadAt(
    vpixmapScanner                 *scanner,
    int                             x,
    int                             y
    );

void vpixmapWrite(
    vpixmapScanner                 *scanner,
    vpixmapValue                    value
    );

void vpixmapWriteMoveRight(
    vpixmapScanner                 *scanner,
    vpixmapValue                    value
    );

void vpixmapWriteAt(
    vpixmapScanner                 *scanner,
    int                             x,
    int                             y,
    vpixmapValue                    value
    );

void vpixmapGetLocation(
    vpixmapScanner                 *scanner,
    int                            *x,
    int                            *y
    );

vbool vpixmapIsFinished(
    vpixmapScanner                 *scanner
    );

vpixmap *vpixmapGetScannerPixmap(
    vpixmapScanner                 *scanner
    );

void vpixmapSetScannerPixmap(
    vpixmapScanner                 *scanner,
    vpixmap			   *pixmap
    );

unsigned char *vpixmapGetScannerBits(
    vpixmapScanner                 *scanner
    );

void vpixmapSetScannerBits(
    vpixmapScanner                 *scanner,
    vpixmap			   *pixmap,
    unsigned char		   *bits
    );

long vpixmapGetScannerIncrementY(
    vpixmapScanner                 *scanner
    );

unsigned char *vpixmapGetScannerScan(
    vpixmapScanner                 *scanner
    );

/*
 * deprecated pixmaps
 */

vpixmap *vpixmapCreateSpecific(
    int                             w,
    int                             h,
    int                             depth,
    int                             flags,
    unsigned char                  *bits
    );

void vpixmapInitSpecific(
    vpixmap                        *pixmap,
    int                             w,
    int                             h,
    int                             depth,
    int                             flags,
    unsigned char                  *bits
    );

vpixmap *vpixmapCloneNoBits(
    vpixmap                        *pixmap
    );

void vpixmapCopyInitNoBits(
    vpixmap                        *pixmap,
    vpixmap                        *target
    );

vpixmapScanner *vpixmapGetScanner(
    vpixmap                        *pixmap
    );

vpixmapValue vpixmapSetLocation(
    vpixmapScanner                 *scanner,
    int                             x,
    int                             y
    );

void vpixmapSetPixel(
    vpixmapScanner                 *scanner,
    int                             x,
    int                             y,
    vpixmapValue                    value
    );

vpixmapValue vpixmapGetPrev(
    vpixmapScanner                 *scanner
    );

vpixmapValue vpixmapSetPrev(
    vpixmapScanner                 *scanner,
    vpixmapValue                    value
    );

vpixmapValue vpixmapGetNext(
    vpixmapScanner                 *scanner
    );

vpixmapValue vpixmapSetNext(
    vpixmapScanner                 *scanner,
    vpixmapValue                    value
    );

int vpixmapBeforeFirstPixel(
    vpixmapScanner                 *scanner
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vpixmapPAD_1                   = 0x0000,
    _vpixmapPAD_8                   = 0x0001,
    _vpixmapPAD_16                  = 0x0002,
    _vpixmapPAD_32                  = 0x0003,
    _vpixmapPAD_FLAGS               = 0x0003,
    _vpixmapBIG_ENDIAN_BYTE         = 0x0004,
    _vpixmapINVERSE_Y               = 0x0008,
    _vpixmapFORMAT_FLAGS            = 0x000F,
    _vpixmapPREFERRED_FORMAT        = 0x0010,
    _vpixmapDONT_COPY_BITS	    = 0x0020
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vpixmapScannerFuncs _vpixmapScannerFuncs;

struct vpixmap {
    vobject                         object;
    vbuffer                        *buffers;
    const void                     *data;
    vpixmapDimension		    width, height;
    short			    depth;
    unsigned short		    flags;
};

#define vpixmapCLASS(SUPER, PIXMAP)                                           \
    vobjectCLASS(SUPER, PIXMAP);                                              \
    vclassMETHOD(vpixmapCLEAR, (PIXMAP *pixmap, vpixmapValue value));         \
    vclassMETHOD(vpixmapCOPY_BITS, (PIXMAP *pixmap, PIXMAP *target));         \
    vclassMETHOD(vpixmapCOPY_RECT,                                            \
		 (PIXMAP *pixmap, PIXMAP *target,                             \
		  int x, int y, int w, int h, int targetX, int targetY));     \
    vclassMETHOD(vpixmapMARK_MODIFIED, (PIXMAP *pixmap));                     \
    vclassMETHOD_RET(vpixmapMAKE_BUFFER, vbuffer*,                            \
		     (PIXMAP *pixmap, const vbufferDevice *device));          \
    vclassMETHOD(vpixmapSET_SIZE,                                             \
		 (PIXMAP *pixmap, int w, int h, int preserve,                 \
		  vpixmapValue background));                                  \
    vclassMETHOD(vpixmapSET_DEPTH, (PIXMAP *pixmap, int depth));              \
    vclassMETHOD(vpixmapSET_PAD, (PIXMAP *pixmap, int pad));                  \
    vclassMETHOD(vpixmapSET_DATA, (PIXMAP *pixmap, const void *data));        \
    vclassMETHOD(vpixmapSET_BIG_ENDIAN_BYTE, (PIXMAP *pixmap, int flag));     \
    vclassMETHOD(vpixmapSET_INVERSE_Y, (PIXMAP *pixmap, int flag));	      \
    vclassMETHOD(vpixmapSET_COPY_BITS, (PIXMAP *pixmap, int flag))

struct vpixmapClass {
    vpixmapCLASS(vpixmapClass, vpixmap);
};


struct _vpixmapScannerFuncs {
    vbool	 (*IsFinished)(vpixmapScanner *scanner);
    void         (*GetLocation)(vpixmapScanner *scanner, int *x, int *y);
    void         (*MoveTo)(vpixmapScanner *scanner, int x, int y);
    void         (*MoveRight)(vpixmapScanner *scanner);
    void         (*MoveLeft)(vpixmapScanner *scanner);
    void         (*MoveUp)(vpixmapScanner *scanner);
    void         (*MoveDown)(vpixmapScanner *scanner);
    vpixmapValue (*Read)(vpixmapScanner *scanner);
    vpixmapValue (*ReadMoveRight)(vpixmapScanner *scanner);
    vpixmapValue (*ReadAt)(vpixmapScanner *scanner, int x, int y);
    void         (*Write)(vpixmapScanner *scanner, vpixmapValue value);
    void         (*WriteMoveRight)(vpixmapScanner *scanner, 
				   vpixmapValue value);
    void         (*WriteAt)(vpixmapScanner *scanner, int x, int y, 
			    vpixmapValue value);
};

struct vpixmapScanner {
    vinstance			    super;

    _vpixmapScannerFuncs            funcs;
    vpixmap                        *pixmap;
    vbuffer                        *buffer;
    unsigned char	           *bits;
    long		            incrementY;
    unsigned char	           *scan;
    unsigned char	           *left, *right;
    unsigned int		    mask, rightMask;
    int                             shift, rightShift;
};

#define vpixmapSCANNER_CLASS(CLASS, SCANNER)				\
    vinstanceCLASS(CLASS, SCANNER)

struct vpixmapScannerClass
{
    vpixmapSCANNER_CLASS(vpixmapScannerClass, vpixmapScanner);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vbufferDevice          _vpixmapBufferDevice;
extern vportLINK vpixmapValue                 _vpixmapValue;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * pixmaps
 */

#define vpixmapGetBufferDevice()   (&_vpixmapBufferDevice)

#define vpixmapGetObject(p)         vportBASE_OBJECT(p, object)
#define vpixmapGetObservable(o) \
	vobjectGetObservable(vpixmapGetObject(o))
#define vpixmapGetLoadable(o) \
	vobservableGetLoadable(vpixmapGetObservable(o))
#define vpixmapGetInstance(o) \
	vloadableGetInstance(vpixmapGetLoadable(o))

#define vpixmapCreateOfClass(c) \
    ((vpixmap*)vloadableCreateOfClass((vloadableClass*)(c)))
#define vpixmapCreateDefault() \
    vpixmapCreateOfClass(vpixmapGetDefaultClass())
#define vpixmapInitOfClass(p, c) \
    vloadableInitOfClass(vpixmapGetLoadable(p), (vloadableClass*)(c))
#define vpixmapInitDefault(p) \
    vpixmapInitOfClass(p, vpixmapGetDefaultClass())
#define vpixmapDestroy(p) \
    vloadableDestroy(vpixmapGetLoadable(p))
#define vpixmapCopy(p, t) \
    vloadableCopy(vpixmapGetLoadable(p), vpixmapGetLoadable(t))
#define vpixmapStore(p, r) \
    vloadableStore(vpixmapGetLoadable(p), r)
#define vpixmapDump(p, s) \
    vloadableDump(vpixmapGetLoadable(p), s)
#define vpixmapSetTag(p, t) \
    vloadableSetTag(vpixmapGetLoadable(p), t)

#define vpixmapClone(o) \
    ((vpixmap *)vloadableCloneOfSubclass(vpixmapGetLoadable(o), \
				 (vloadableClass*) vpixmapGetDefaultClass()))
#define vpixmapCopyInit(o,t) \
    vloadableCopyInitOfSubclass(vpixmapGetLoadable(o), vpixmapGetLoadable(t), \
				(vloadableClass*) vpixmapGetDefaultClass())
#define vpixmapLoad(r) \
    	((vpixmap *) vloadableLoadOfSubclass(r, \
				 (vloadableClass*) vpixmapGetDefaultClass()))
#define vpixmapLoadInit(o,r) \
    	vloadableLoadInitOfSubclass(vpixmapGetLoadable(o), (r), \
				    (vloadableClass*) vpixmapGetDefaultClass())

#define vpixmapGetClass(p) \
    ((vpixmapClass*)vloadableGetClass(vpixmapGetLoadable(p)))
#define vpixmapGetTag(p)            vloadableGetTag(vpixmapGetLoadable(p))
#define vpixmapGetData(p)          ((p)->data)
#define vpixmapGetWidth(p)         ((p)->width)
#define vpixmapGetHeight(p)        ((p)->height)
#define vpixmapGetDepth(p)         ((p)->depth)
#define vpixmapIsBigEndianByte(p) (((p)->flags&_vpixmapBIG_ENDIAN_BYTE)!=0)
#define vpixmapIsInverseY(p)      (((p)->flags&_vpixmapINVERSE_Y)!=0)
#define vpixmapHasCopyBits(p)      (((p)->flags&_vpixmapDONT_COPY_BITS)==0)

#define vpixmapSetSizeMangle(p, w, h) \
    vpixmapSetSize(p, w, h, vpixmapPRESERVE_NONE, (vpixmapValue) 0)
#define vpixmapSetSizeNoBackground(p, w, h, f) \
    vpixmapSetSize(p, w, h, (f) & ~vpixmapPRESERVE_CLEAR_EXPOSED, \
		   (vpixmapValue) 0)
#define vpixmapSetSizeWithBackground(p, w, h, f, v) \
    vpixmapSetSize(p, w, h, (f) | vpixmapPRESERVE_CLEAR_EXPOSED, v)

#define vpixmapMoveRight(s)         (*(s)->funcs.MoveRight)(s)
#define vpixmapMoveLeft(s)          (*(s)->funcs.MoveLeft)(s)
#define vpixmapMoveUp(s)            (*(s)->funcs.MoveUp)(s)
#define vpixmapMoveDown(s)          (*(s)->funcs.MoveDown)(s)
#define vpixmapRead(s)              (*(s)->funcs.Read)(s)
#define vpixmapReadMoveRight(s)     (*(s)->funcs.ReadMoveRight)(s)
#define vpixmapWrite(s, v)          (*(s)->funcs.Write)(s, v)
#define vpixmapWriteMoveRight(s, v) (*(s)->funcs.WriteMoveRight)(s, v)
#define vpixmapGetLocation(s, x, y) (*(s)->funcs.GetLocation)(s, x, y)
#define vpixmapIsFinished(s)	    (*(s)->funcs.IsFinished)(s)

#if (!vdebugDEBUG)
#define vpixmapMoveTo(s, x, y)      (*(s)->funcs.MoveTo)(s, x, y)
#define vpixmapReadAt(s, x, y)      (*(s)->funcs.ReadAt)(s, x, y)
#define vpixmapWriteAt(s, x, y, v)  (*(s)->funcs.WriteAt)(s, x, y, v)
#endif

#define vpixmapGetScannerPixmap(s)     ((s)->pixmap)
#define vpixmapGetScannerBits(s)       ((s)->bits)
#define vpixmapGetScannerIncrementY(s) ((s)->incrementY)
#define vpixmapGetScannerScan(s)       ((s)->scan)

/*
 * deprecated pixmaps
 */

#define vpixmapSetLocation(s, x, y) \
    (vpixmapMoveTo(s, x, y), vpixmapRead(s))
#define vpixmapSetPixel(s, x, y, v) \
    (vpixmapMoveTo(s, x, y), vpixmapWrite(s, v))
#define vpixmapGetPrev(s) \
    (_vpixmapValue = vpixmapRead(s), vpixmapMoveLeft(s), _vpixmapValue)
#define vpixmapSetPrev(s, v) \
    (vpixmapWrite(s, v), vpixmapMoveLeft(s), vpixmapRead(s))
#define vpixmapGetNext(s)           vpixmapReadMoveRight(s)
#define vpixmapSetNext(s, v) \
    (vpixmapWriteMoveRight(s, v), vpixmapRead(s))
#define vpixmapBeforeFirstPixel(s) ((s)->scan<(s)->bits)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vpixmapClear(p, v) \
    vclassSend(vpixmapGetClass(p), vpixmapCLEAR, (p, v))
#define vpixmapCopyBits(p, t) \
    vclassSend(vpixmapGetClass(p), vpixmapCOPY_BITS, (p, t))
#define vpixmapCopyRect(p, t, x, y, w, h, tx, ty) \
    vclassSend(vpixmapGetClass(p), vpixmapCOPY_RECT, \
	       (p, t, x, y, w, h, tx, ty))
#define vpixmapMarkModified(p) \
    vclassSend(vpixmapGetClass(p), vpixmapMARK_MODIFIED, (p))
#define vpixmapMakeBuffer(p, d) \
    vclassSend(vpixmapGetClass(p), vpixmapMAKE_BUFFER, (p, d))
#define vpixmapSetSize(p, w, h, pr, b) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_SIZE, (p, w, h, pr, b))
#define vpixmapSetDepth(p, d) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_DEPTH, (p, d))
#define vpixmapSetPad(p, n) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_PAD, (p, n))
#define vpixmapSetData(p, d) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_DATA, (p, d))
#define vpixmapSetBigEndianByte(p, f) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_BIG_ENDIAN_BYTE, (p, f))
#define vpixmapSetInverseY(p, f) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_INVERSE_Y, (p, f))
#define vpixmapSetCopyBits(p, f) \
    vclassSend(vpixmapGetClass(p), vpixmapSET_COPY_BITS, (p, f))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vpixmapINCLUDED */

