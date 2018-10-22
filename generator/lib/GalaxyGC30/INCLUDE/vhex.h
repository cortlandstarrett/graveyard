/* $Id: vhex.h,v 1.8 1997/08/22 01:47:35 robert Exp $ */

/************************************************************

    vhex.h

    C Interface file for the Hex Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vhexINCLUDED
#define vhexINCLUDED

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vtransformINCLUDED
#include vtransformHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * metrics
 */

enum {
    vhexDISPLAY_ASCII = 0,
    vhexDISPLAY_BINARY,
    vhexDISPLAY_DECIMAL,
    vhexDISPLAY_HEXIDECIMAL,
    vhexDISPLAY_OCTAL,
    vhexDISPLAY_UNICODE
};

enum {
    vhexID_ATTRIBUTE_ADDRESS = vdialogITEM_NEXT_ID_ATTRIBUTE,
    vhexID_ATTRIBUTE_BUFFER,
    vhexID_ATTRIBUTE_BUFFER_LENGTH,
    vhexID_ATTRIBUTE_BUFFER_POINTER,
    vhexID_ATTRIBUTE_BYTES_PER_WORD,
    vhexID_ATTRIBUTE_DATA_LENGTH,
    vhexID_ATTRIBUTE_DISPLAY,
    vhexID_ATTRIBUTE_HORZ_SCROLLBAR,
    vhexID_ATTRIBUTE_OFFSET,
    vhexID_ATTRIBUTE_OVERWRITE,
    vhexID_ATTRIBUTE_SCROLLBAR_MARGIN,
    vhexID_ATTRIBUTE_SPACE_BETWEEN_LINES,
    vhexID_ATTRIBUTE_SPACE_BETWEEN_WORDS,
    vhexID_ATTRIBUTE_VERT_SCROLLBAR,
    vhexID_ATTRIBUTE_VISIBLE_LINES,
    vhexID_ATTRIBUTE_VISIBLE_WORDS,
    vhexID_ATTRIBUTE_WORDS_PER_LINE,
    vhexNEXT_ID_ATTRIBUTE
};
    
enum {
    vhexNEXT_SELECT             = vdialogITEM_NEXT_SELECT
};

/*
 * for vhexNoteProc message component
 */
enum {
    vhexNOTIFY_SCROLL,
    vhexNOTIFY_DATA_CHANGE,
    vhexNOTIFY_SELECTION_CHANGE,
    vhexNOTIFY_BUFFER_FULL,
    vhexNOTIFY_OVERWRITE_CHANGE,
    vhexNEXT_NOTIFY
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * hex
 */

typedef struct vhex             vhex;
typedef struct vhexClass        vhexClass;

typedef void (*vhexNoteProc)(
    vhex                       *hex,
    vevent                     *event,
    int                         message
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vhexStartup(void);


/*
 * hex
 */

vhex *vhexClone(
    vhex                       *hex
    );

void vhexCopy(
    vhex                       *hex,
    vhex                       *target
    );

void vhexCopyInit(
    vhex                       *hex,
    vhex                       *target
    );

vhex *vhexCreate(
    void
    );

vhex *vhexCreateOfClass(
    vhexClass                  *clas
    );

void vhexDestroy(
    vhex                       *hex
    );

vhexClass *vhexGetClass(
    vhex                       *hex
    );

const void *vhexGetData(
    vhex                       *hex
    );

vhexClass *vhexGetDefaultClass(
    void
    );

vdialogItem *vhexGetItem(
    vhex                       *hex
    );

vhexNoteProc vhexGetNotify(
    vhex                       *hex
    );

const vchar *vhexGetTitle(
    vhex                       *hex
    );

void vhexInitOfClass(
    vhex                       *hex,
    vhexClass                  *clas
    );

void vhexInit(
    vhex                       *hex
    );

void vhexDelete(
    vhex                       *hex
    );

int vhexGetAddress(
    vhex                       *hex
    );

void vhexGetAddressSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

int vhexGetBufferLength(
    vhex                       *hex
    );

void *vhexGetBufferPointer(
    vhex                       *hex
    );

void vhexGetBufferSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

void vhexGetBufferViewBorderRect(
    vhex                       *hex,
    vrect                      *rect
    );

void vhexGetBufferViewRect(
    vhex                       *hex,
    vrect                      *rect
    );

int vhexGetBytesPerWord(
    vhex                       *hex
    );

void vhexGetByteSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

int vhexGetCaretEdit(
    vhex                       *hex
    );

int vhexGetCaretIndex(
    vhex                       *hex
    );

int vhexGetDataLength(
    vhex                       *hex
    );

void vhexGetDataSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

void vhexGetDecorationSizes(
    vhex                       *hex,
    int                        *top,
    int                        *left,
    int                        *bottom,
    int                        *right
    );

int vhexGetDigitsPerNBytes(
    vhex                       *hex,
    int                         bytes
    );			       

void vhexGetDigitSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

int vhexGetDisplay(
    vhex                       *hex
    );

vcontrol *vhexGetHorzScrollbar(
    vhex                       *hex
    );

void vhexGetLineSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

int vhexGetScrollbarMargin(
    vhex                       *hex
    ); 

int vhexGetSelectionEnd(
    vhex                       *hex
    );

int vhexGetSelectionLength(
    vhex                       *hex
    );

int vhexGetSelectionStart(
    vhex                       *hex
    );

int vhexGetSpaceBetweenLines(
    vhex                       *hex
    );

int vhexGetSpaceBetweenWords(
    vhex                       *hex
    );

vcontrol *vhexGetVertScrollbar(
    vhex                       *hex
    );

int vhexGetVisibleLines(
    vhex                       *hex
    );

int vhexGetVisibleWords(
    vhex                       *hex
    );

int vhexGetWordsPerLine(
    vhex                       *hex
    );

void vhexGetWordRect(
    vhex                       *hex,
    int                         index,
    vrect                      *rect);
		     
vrect *vhexGetWordRects(
    vhex                       *hex,
    int                         start,
    int                         end,
    int                        *count);
		     
void vhexGetWordSize(
    vhex                       *hex,
    int                        *width,
    int                        *height
    );

int vhexGetXOffset(
    vhex                       *hex
    );

int vhexGetYOffset(
    vhex                       *hex
    );

int vhexHasHorzScrollbar(
    vhex                       *hex
    );

int vhexHasOverwrite(
    vhex                       *hex
    );

int vhexHasVertScrollbar(
    vhex                       *hex
    );

void vhexInsert(
    vhex                       *hex,
    void                       *buffer,
    int                         length
    );

void vhexInval(
    vhex                       *hex,
    int                         start,
    int                         end,
    int                         flags
    );	        

void vhexInvalScroll(
    vhex                       *hex,
    int                         start,
    int                         end,
    int                         from,
    int                         to,
    int                         flags
    );		      

void vhexNotify(
    vhex                       *hex,
    vevent                     *event,	  
    int                         message
    );

void vhexScrollPointIntoView(
    vhex                       *hex,
    int                         x,
    int                         y
    );

void vhexScrollWordIntoView(
    vhex                       *hex,
    int                         index
    );

void vhexSetAddress(
    vhex                       *hex,
    int                         onOff
    );

void vhexSetBuffer(
    vhex                       *hex,
    void                       *buffer,
    int                         length,
    int                         dataLength
    );

void vhexSetBufferLength(
    vhex                       *hex,
    int                         length
    );

void vhexSetBufferPointer(
    vhex                       *hex,
    void                       *pointer
    );

void vhexSetBytesPerWord(
    vhex                       *hex,
    int                         bytes
    );

void vhexSetCaret(
    vhex                       *hex,
    int                         index,
    int                         editFlag
    );

void vhexSetData(
    vhex                       *hex,
    const void                 *data
    );

void vhexSetDataLength(
    vhex                       *hex,
    int                         dataLength
    );

void vhexSetDisplay(
    vhex                       *hex,
    int                         display
    );

void vhexSetHorzScrollbar(
    vhex                       *hex,
    int                         onOff
    );		   

void vhexSetNotify(
    vhex                       *hex,
    vhexNoteProc                noteProc
    );

void vhexSetOffset(
    vhex                       *hex,
    int                         xOffset,
    int                         yOffset
    );

void vhexSetOverwrite(
    vhex                       *hex,
    int                         onOff
    );

void vhexSetSelection(
    vhex                       *hex,
    int                         start,
    int                         end
    );

void vhexSetSpaceBetweenLines(
    vhex                       *hex,
    int                         spaceInPixels
    );

void vhexSetSpaceBetweenWords(
    vhex                       *hex,
    int                         spaceInPixels
    );

void vhexSetTitle(
    vhex                       *hex,
    const vchar                *title
    );

void vhexSetTitleScribed(
    vhex                       *hex,
    vscribe                    *title
    );

void vhexSetVertScrollbar(
    vhex                       *hex,
    int                         onOff
    );		   

void vhexSetVisibleLines(
    vhex                       *hex,
    int                         lines
    );
    
void vhexSetVisibleWords(
    vhex                       *hex,
    int                         words
    );
    
void vhexSetWordsPerLine(
    vhex                       *hex,
    int                         words
    );

void vhexSetXOffset(
    vhex                       *hex,
    int                         offset
    );

void vhexSetYOffset(
    vhex                       *hex,
    int                         offset
    );

vobjectAttributed *vhexGetObject(
    vhex                       *hex
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vhexFLAGS_ADDRESS              = 0x0001,
    _vhexFLAGS_VERT_SCROLLBAR       = 0x0002,
    _vhexFLAGS_HORZ_SCROLLBAR       = 0x0004,
    _vhexFLAGS_OVERWRITE            = 0x0008
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * hex
 */

struct vhex {
    vdialogItem                     item;

    unsigned short                  flags;

    int                             xOffset;
    int                             yOffset;

    vrect                           bufferViewBorderRect;
    vrect                           bufferViewRect;
    vcontrol                       *vertScrollbar;
    vcontrol                       *horzScrollbar;
    int                             scrollbarMargin;

    int                             bytesPerWord;
    int                             display;
    int                             spaceBetweenLines;
    int                             spaceBetweenWords;
    int                             wordsPerLine;
    int                             visibleLines;
    int                             visibleWords;

    void                           *bufferPointer;
    int                             bufferLength;
    int                             dataLength;

    int                             clickIndex;
    int                             selectionStartIndex;
    int                             selectionEndIndex;
    int                             selectionEdit;

    int                             addressWidth;
    int                             digitWidth;
    int                             wordWidth;
    int                             digitsPerWord;
    int                             bytesPerLine;
    int                             lineWidth;
    int                             lineHeight;

    vhexNoteProc                    proc;
};

#define vhexCLASS(SUPER, HEX, NOTIFY) \
    vdialogITEM_CLASS(SUPER, HEX, NOTIFY); \
    vclassMETHOD_RET(vhexCREATE_HORZ_SCROLLBAR, vcontrol *, (HEX *hex)); \
    vclassMETHOD_RET(vhexCREATE_VERT_SCROLLBAR, vcontrol *, (HEX *hex)); \
    vclassMETHOD(vhexDELETE, (HEX *hex)); \
    vclassMETHOD(vhexGET_ADDRESS_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexGET_BUFFER_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexGET_BUFFER_VIEW_BORDER_RECT, (HEX *hex, vrect *rect)); \
    vclassMETHOD(vhexGET_BUFFER_VIEW_RECT, (HEX *hex, vrect *rect)); \
    vclassMETHOD(vhexGET_BYTE_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexGET_DATA_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexGET_DECORATION_SIZES, \
                 (HEX *hex, int *top, int *left, int *bottom, int *right)); \
    vclassMETHOD(vhexGET_DIGIT_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD_RET(vhexGET_DIGITS_PER_NBYTES, int, (HEX *hex, int bytes)); \
    vclassMETHOD(vhexGET_HORZ_SCROLLBAR_RECT, (HEX *hex, vrect *rect)); \
    vclassMETHOD(vhexGET_LINE_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexGET_VERT_SCROLLBAR_RECT, (HEX *hex, vrect *rect)); \
    vclassMETHOD(vhexGET_WORD_RECT, (HEX *hex, int index, vrect *rect)); \
    vclassMETHOD_RET(vhexGET_WORD_RECTS, \
		     vrect *, (HEX *hex, int start, int end, int *count)); \
    vclassMETHOD(vhexGET_WORD_SIZE, (HEX *hex, int *width, int *height)); \
    vclassMETHOD(vhexINSERT, (HEX *hex, void *buffer, int length)); \
    vclassMETHOD(vhexINVAL, (HEX *hex, int start, int end, int flags)); \
    vclassMETHOD(vhexINVAL_SCROLL, \
		 (HEX *hex, int start, int end, int from, int to,int flags)); \
    vclassMETHOD(vhexNOTIFY, (HEX *hex, vevent *event, int message)); \
    vclassMETHOD(vhexSCROLL_POINT_INTO_VIEW, (HEX *hex, int x, int y)); \
    vclassMETHOD(vhexSCROLL_WORD_INTO_VIEW, (HEX *hex, int index)); \
    vclassMETHOD(vhexSET_ADDRESS, (HEX *hex, int onOff)); \
    vclassMETHOD(vhexSET_BUFFER, \
		 (HEX *hex, void *buffer, int length, int dataLength)); \
    vclassMETHOD(vhexSET_BUFFER_LENGTH, (HEX *hex, int length)); \
    vclassMETHOD(vhexSET_BUFFER_POINTER, (HEX *hex, void *buffer)); \
    vclassMETHOD(vhexSET_BYTES_PER_WORD, (HEX *hex, int bytes)); \
    vclassMETHOD(vhexSET_CARET, (HEX *hex, int index, int editFlag)); \
    vclassMETHOD(vhexSET_DATA_LENGTH, (HEX *hex, int length)); \
    vclassMETHOD(vhexSET_DISPLAY, (HEX *hex, int display)); \
    vclassMETHOD(vhexSET_HORZ_SCROLLBAR, (HEX *hex, int onOff)); \
    vclassMETHOD(vhexSET_NOTIFY, (HEX *hex, vhexNoteProc proc)); \
    vclassMETHOD(vhexSET_OFFSET, (HEX *hex, int xOffset, int yOffset)); \
    vclassMETHOD(vhexSET_OVERWRITE, (HEX *hex, int onOff)); \
    vclassMETHOD(vhexSET_SELECTION, (HEX *hex, int start, int end)); \
    vclassMETHOD(vhexSET_SPACE_BETWEEN_LINES, (HEX *hex, int space)); \
    vclassMETHOD(vhexSET_SPACE_BETWEEN_WORDS, (HEX *hex, int space)); \
    vclassMETHOD(vhexSET_VERT_SCROLLBAR, (HEX *hex, int onOff)); \
    vclassMETHOD(vhexSET_VISIBLE_LINES, (HEX *hex, int lines)); \
    vclassMETHOD(vhexSET_VISIBLE_WORDS, (HEX *hex, int words)); \
    vclassMETHOD(vhexSET_WORDS_PER_LINE, (HEX *hex, int words))

struct vhexClass {
    vhexCLASS(vhexClass, vhex, vhexNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * hexs
 */

#define vhexGetItem(c)          vportBASE_OBJECT(c, item)
#define vhexGetObject(c)        vdialogGetItemObject(vhexGetItem(c))

#define vhexCreateOfClass(c) \
    ((vhex*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vhexCreate() \
    vhexCreateOfClass(vhexGetDefaultClass())
#define vhexClone(c) \
    ((vhex*)vdialogCloneItem(vhexGetItem(c)))
#define vhexInitOfClass(i, c) \
    vdialogInitItemOfClass(vhexGetItem(i), (vdialogItemClass*)(c))
#define vhexInit(c) \
    vhexInitOfClass(c, vhexGetDefaultClass())
#define vhexCopyInit(c, t) \
    vdialogCopyInitItem(vhexGetItem(c), vhexGetItem(t))
#define vhexDestroy(c) \
    vdialogDestroyItem(vhexGetItem(c))

#define vhexSetTitle(c, s)      vdialogSetItemTitle(vhexGetItem(c), s)

#define vhexGetClass(c) \
    ((vhexClass*)vdialogGetItemClass(vhexGetItem(c)))

#define vhexGetTitle(c)             vdialogGetItemTitle(vhexGetItem(c))
#define vhexSetData(c, d)           vdialogSetItemData(vhexGetItem(c), (d))
#define vhexGetData(c)              vdialogGetItemData(vhexGetItem(c))

#define vhexGetAddress(c)           ((c)->flags&_vhexFLAGS_ADDRESS)
#define vhexGetBufferLength(c)      ((c)->bufferLength)
#define vhexGetBufferPointer(c)     ((c)->bufferPointer)
#define vhexGetBytesPerWord(c)      ((c)->bytesPerWord)
#define vhexGetCaretEdit(c)         ((c)->selectionEdit)
#define vhexGetCaretIndex(c)        ((c)->selectionStartIndex)
#define vhexGetDataLength(c)        ((c)->dataLength)
#define vhexGetDisplay(c)           ((c)->display)
#define vhexGetHorzScrollbar(c)     ((c)->horzScrollbar)
#define vhexGetNotify(c)            ((c)->proc)
#define vhexGetScrollbarMargin(c)   ((c)->scrollbarMargin)
#define vhexGetSelectionEnd(c)      ((c)->selectionEndIndex)
#define vhexGetSelectionLength(c)   ((c)->selectionEndIndex - (c)->selectionStartIndex)
#define vhexGetSelectionStart(c)    ((c)->selectionStartIndex)
#define vhexGetSpaceBetweenLines(c) ((c)->spaceBetweenLines)
#define vhexGetSpaceBetweenWords(c) ((c)->spaceBetweenWords)
#define vhexGetVertScrollbar(c)     ((c)->vertScrollbar)
#define vhexGetVisibleLines(c)      ((c)->visibleLines)
#define vhexGetVisibleWords(c)      ((c)->visibleWords)
#define vhexGetWordsPerLine(c)      ((c)->wordsPerLine)
#define vhexGetXOffset(c)           ((c)->xOffset)
#define vhexGetYOffset(c)           ((c)->yOffset)
#define vhexHasHorzScrollbar(c)     ((c)->flags&_vhexFLAGS_HORZ_SCROLLBAR)
#define vhexHasOverwrite(c)         ((c)->flags&_vhexFLAGS_OVERWRITE)
#define vhexHasVertScrollbar(c)     ((c)->flags&_vhexFLAGS_VERT_SCROLLBAR)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * hex
 */

#define vhexCopy(c, t) \
    vclassSend(vhexGetClass(c), vobjectCOPY, (c, t))

#define vhexSetTitleScribed(c, s) \
    vclassSend(vhexGetClass(c), vdialogSET_ITEM_TITLE_SCRIBED, (c, s))

#define vhexDelete(c) \
    vclassSend(vhexGetClass(c), vhexDELETE, (c))
#define vhexGetAddressSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_ADDRESS_SIZE, (c, w, h))
#define vhexGetBufferSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_BUFFER_SIZE, (c, w, h))
#define vhexGetBufferViewBorderRect(c, r) \
    vclassSend(vhexGetClass(c), vhexGET_BUFFER_VIEW_BORDER_RECT, (c, r))
#define vhexGetBufferViewRect(c, r) \
    vclassSend(vhexGetClass(c), vhexGET_BUFFER_VIEW_RECT, (c, r))
#define vhexGetByteSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_BYTE_SIZE, (c, w, h))
#define vhexGetDataSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_DATA_SIZE, (c, w, h))
#define vhexGetDigitsPerNBytes(c, b) \
    vclassSend(vhexGetClass(c), vhexGET_DIGITS_PER_NBYTES, (c, b))
#define vhexGetDigitSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_DIGIT_SIZE, (c, w, h))
#define vhexGetDecorationSizes(c, w, x, y, z) \
    vclassSend(vhexGetClass(c), vhexGET_DECORATION_SIZES, (c, w, x, y, z))
#define vhexGetLineSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_LINE_SIZE, (c, w, h))
#define vhexGetWordRect(c, p, r) \
    vclassSend(vhexGetClass(c), vhexGET_WORD_RECT, (c, p, r))
#define vhexGetWordRects(c, a, b, n) \
    vclassSend(vhexGetClass(c), vhexGET_WORD_RECTS, (c, a, b, n))
#define vhexGetWordSize(c, w, h) \
    vclassSend(vhexGetClass(c), vhexGET_WORD_SIZE, (c, w, h))
#define vhexInsert(c, b, l) \
    vclassSend(vhexGetClass(c), vhexINSERT, (c, b, l))
#define vhexInval(c, a, b, f) \
    vclassSend(vhexGetClass(c), vhexINVAL, (c, a, b, f))
#define vhexInvalScroll(c, a, b, d, e, f) \
    vclassSend(vhexGetClass(c), vhexINVAL_SCROLL, (c, a, b, d, e, f))
#define vhexNotify(c, e, m) \
    vclassSend(vhexGetClass(c), vhexNOTIFY, (c, e, m))
#define vhexScrollPointIntoView(c, x, y) \
    vclassSend(vhexGetClass(c), vhexSCROLL_POINT_INTO_VIEW, (c, x, y))
#define vhexScrollWordIntoView(c, f) \
    vclassSend(vhexGetClass(c), vhexSCROLL_WORD_INTO_VIEW, (c, f))
#define vhexSetAddress(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_ADDRESS, (c, f))
#define vhexSetBuffer(c, b, l, d) \
    vclassSend(vhexGetClass(c), vhexSET_BUFFER, (c, b, l, d))
#define vhexSetBufferLength(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_BUFFER_LENGTH, (c, p))
#define vhexSetBufferPointer(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_BUFFER_POINTER, (c, p))
#define vhexSetBytesPerWord(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_BYTES_PER_WORD, (c, f))
#define vhexSetCaret(c, p, f) \
    vclassSend(vhexGetClass(c), vhexSET_CARET, (c, p, f))
#define vhexSetDataLength(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_DATA_LENGTH, (c, p))
#define vhexSetDisplay(c, n) \
    vclassSend(vhexGetClass(c), vhexSET_DISPLAY, (c, n))
#define vhexSetHorzScrollbar(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_HORZ_SCROLLBAR, (c, f))		 
#define vhexSetNotify(c, n) \
    vclassSend(vhexGetClass(c), vhexSET_NOTIFY, (c, n))
#define vhexSetOffset(c, x, y) \
    vclassSend(vhexGetClass(c), vhexSET_OFFSET, (c, x, y))
#define vhexSetOverwrite(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_OVERWRITE, (c, f))
#define vhexSetSelection(c, s, f) \
    vclassSend(vhexGetClass(c), vhexSET_SELECTION, (c, s, f))
#define vhexSetSpaceBetweenLines(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_SPACE_BETWEEN_LINES, (c, p))
#define vhexSetSpaceBetweenWords(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_SPACE_BETWEEN_WORDS, (c, p))
#define vhexSetVertScrollbar(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_VERT_SCROLLBAR, (c, f))		 
#define vhexSetVisibleLines(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_VISIBLE_LINES, (c, p))
#define vhexSetVisibleWords(c, p) \
    vclassSend(vhexGetClass(c), vhexSET_VISIBLE_WORDS, (c, p))
#define vhexSetWordsPerLine(c, f) \
    vclassSend(vhexGetClass(c), vhexSET_WORDS_PER_LINE, (c, f))
#define vhexSetXOffset(c, x) \
    vclassSend(vhexGetClass(c), vhexSET_OFFSET, (c, x, vhexGetYOffset(c)))
#define vhexSetYOffset(c, y) \
    vclassSend(vhexGetClass(c), vhexSET_OFFSET, (c, vhexGetXOffset(c), y))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vhexINCLUDED */

