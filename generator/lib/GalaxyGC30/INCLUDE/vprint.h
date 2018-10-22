/* $Id: vprint.h,v 1.46 1997/07/21 23:05:12 robert Exp $ */

/************************************************************

    vprint.h

    C Interface file for the Print Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vprintINCLUDED
#define vprintINCLUDED

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
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

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

enum {
    vprintCOMMENT_STREAM            = 0x0001,
    vprintCOMMENT_PS_DOCUMENT       = 0x0002,
    vprintCOMMENT_PS_PAGE           = 0x0004,
    vprintCOMMENT_PS_HYBRID         = 0x0008,
    vprintCOMMENT_EXTERNAL_STREAM   = 0x0010
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

typedef struct vprint               vprint;
typedef struct vprintClass          vprintClass;

typedef void (*vprintNoteProc)(
    vprint                         *printer,
    int                             flag
    );

/*
 * stream printing
 */

typedef vprint                      vprintStream;
typedef vprintClass                 vprintStreamClass;

/*
 * postscript printing
 */

typedef vprint                      vprintPS;
typedef vprintClass                 vprintPSClass;
typedef vprint                      vprintColorPS;
typedef vprintClass                 vprintColorPSClass;
typedef vprint                      vprintPS2;
typedef vprintClass                 vprintPS2Class;

/*
 * native printing
 */

#if (!vportCPLUSPLUS_SOURCE)

typedef vprint                      vprintInteractive;
typedef vprintClass                 vprintInteractiveClass;
typedef vprintInteractive           vprintNative;
typedef vprintInteractiveClass      vprintNativeClass;

#else /* if (vportCPLUSPLUS_SOURCE) */

class vprintInteractive;
typedef vkind			    vprintInteractiveClass;
typedef vprintInteractive           vprintNative;
typedef vprintInteractiveClass      vprintNativeClass;


#endif /* if (vportCPLUSPLUS_SOURCE) */

/*
 * exceptions
 */

typedef vexModuleStateException     vprintNoDefaultPrinterException;
typedef vexModuleStateException     vprintJobCanceledException;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vprintStartup(void);


/*
 * printing
 */

vprintClass *vprintGetDefaultClass(
    void
    );

vprintClass *vprintGetPreferredClass(
    void
    );

vprint *vprintCreateOfClass(
    vprintClass                    *clas
    );

vprint *vprintCreate(
    void
    );

void vprintInitOfClass(
    vprint                         *printer,
    vprintClass                    *clas
    );

void vprintInit(
    vprint                         *printer
    );

void vprintDestroy(
    vprint                         *printer
    );

vprint *vprintLoad(
    vresource                       resource
    );

void vprintLoadInit(
    vprint                         *printer,
    vresource                       resource
    );

void vprintStore(
    vprint                         *printer,
    vresource                       resource
    );

void vprintConfirmStyle(
    vprint                         *printer
    );

void vprintConfirmJob(
    vprint                         *printer
    );

void vprintOpenConnection(
    vprint                         *printer
    );

void vprintOpenDocument(
    vprint                         *printer
    );

void vprintOpenPage(
    vprint                         *printer
    );

vdrawcontext *vprintOpenPageContext(
    vprint                         *printer
    );

void vprintClosePage(
    vprint                         *printer
    );

void vprintCloseDocument(
    vprint                         *printer
    );

void vprintCloseConnection(
    vprint                         *printer
    );

void vprintWrite(
    vprint                         *printer,
    const void                     *buf,
    size_t                          count,
    size_t                          size
    );

void vprintWriteString(
    vprint                         *printer,
    const vchar                    *s
    );

void vprintSizedWriteString(
    vprint                         *printer,
    const vchar                    *s,
    size_t                          count
    );

void vprintWriteStringScribed(
    vprint                         *printer,
    vscribe                        *scribe
    );

void vprintWriteStringLiteral(
    vprint                         *printer,
    const char                     *s
    );

void vprintWriteInt(
    vprint                         *printer,
    int                             n
    );

void vprintWriteFloat(
    vprint                         *printer,
    double                          x
    );

void vprintSetSelectionEnabled(
    vprint                         *printer,
    int                             n
    );

int  vprintIsSelectionEnabled(
    vprint                         *printer
    );

void vprintSetSelection(
    vprint                         *printer,
    int                             n
    );

int  vprintIsSelection(
    vprint                         *printer
    );

void vprintSetError(
    vprint                         *printer,
    int                             n
    );

int  vprintHasError(
    vprint                         *printer
    );

void vprintSetStream(
    vprint                         *printer,
    FILE                           *stream
    );

void vprintSetFile(
    vprint                         *printer,
    vfsFile                        *file
    );

void vprintSetFilePath(
    vprint                         *printer,
    vfsPath                        *path
    );

void vprintSetCommand(
    vprint                         *printer,
    vstr                           *command
    );

void vprintSetPrinterOption(
    vprint                         *printer,
    vstr                           *printerOption
    );

void vprintSetPrinterName(
    vprint                         *printer,
    vstr                           *printerName
    );

void vprintSetDevice(
    vprint                         *printer,
    void                           *device
    );

void vprintSetLandscape(
    vprint                         *printer,
    int                             flag
    );

void vprintSetPaper(
    vprint                         *printer,
    const vrectFloat               *paper
    );

void vprintSetPage(
    vprint                         *printer,
    const vrectFloat               *page
    );

void vprintSetStyleNotify(
    vprint                         *printer,
    vprintNoteProc                  styleNoteProc
    );

void vprintSetJobNotify(
    vprint                         *printer,
    vprintNoteProc                  jobNoteProc
    );

void vprintSetData(
    vprint                         *printer,
    const void                     *data
    );

void vprintSetSpool(
    vprint                         *printer,
    int                             flag
    );

void vprintSetComment(
    vprint                         *printer,
    unsigned int                    comment
    );

void vprintSetDocumentTitle(
    vprint                         *printer,
    const vchar			   *title
    );

void vprintSetDocumentOwner(
    vprint                         *printer,
    const vobjectAttributed	   *owner
    );

void vprintSetPageNumber(
    vprint                         *printer,
    unsigned int		    pagenum
    );

void vprintSetFirstPageNumber(
    vprint                         *printer,
    unsigned int		    pagenum
    );

void vprintSetLastPageNumber(
    vprint                         *printer,
    unsigned int		    pagenum
    );

vobject *vprintGetObject(
    vprint                         *printer
    );

vprintClass *vprintGetClass(
    vprint                         *printer
    );

FILE *vprintGetStream(
    vprint                         *printer
    );

vfsFile *vprintGetFile(
    vprint                         *printer
    );

vfsPath *vprintGetFilePath(
    vprint                         *printer
    );

vstr *vprintGetCommand(
    vprint                         *printer
    );

vstr *vprintGetPrinterOption(
    vprint                         *printer
    );

vstr *vprintGetPrinterName(
    vprint                         *printer
    );

void *vprintGetDevice(
    vprint                         *printer
    );

const vrectFloat *vprintGetPaper(
    vprint                         *printer
    );

const vrectFloat *vprintGetPage(
    vprint                         *printer
    );

vprintNoteProc vprintGetStyleNotify(
    vprint                         *printer
    );

vprintNoteProc vprintGetJobNotify(
    vprint                         *printer
    );

const void *vprintGetData(
    vprint                         *printer
    );

int vprintIsLandscape(
    vprint                         *printer
    );

int vprintIsSpool(
    vprint                         *printer
    );

int vprintConnectionIsOpen(
    vprint                         *printer
    );

int vprintDocumentIsOpen(
    vprint                         *printer
    );

int vprintPageIsOpen(
    vprint                         *printer
    );

int vprintPageIsDiscarded(
    vprint                         *printer
    );

unsigned int vprintGetComment(
    vprint                         *printer
    );

const vchar *vprintGetDocumentTitle(
    vprint                         *printer
    );

const vobjectAttributed *vprintGetDocumentOwner(
    vprint                         *printer
    );

unsigned int vprintGetPageNumber(
    vprint                         *printer
    );

unsigned int vprintGetFirstPageNumber(
    vprint                         *printer
    );

unsigned int vprintGetLastPageNumber(
    vprint                         *printer
    );

void vprintEnableConfirms(
    void
    );

/*
 * stream printing
 */

vprintStreamClass *vprintGetStreamClass(
    void
    );

/*
 * postscript printing
 */

vprintPSClass *vprintGetPSClass(
    void
    );

vprintColorPSClass *vprintGetColorPSClass(
    void
    );

vprintPS2Class *vprintGetPS2Class(
    void
    );

/*
 * native printing
 */

vprintInteractiveClass *vprintGetInteractiveClass(
    void
    );

/*
 * exception classes
 */

const vexClass *vprintGetNoDefaultPrinterExceptionClass(
    void
    );

vprintNoDefaultPrinterException *vprintGetNoDefaultPrinterException(
    void
    );

const vexClass *vprintGetJobCanceledExceptionClass(
    void
    );

vprintJobCanceledException *vprintGetJobCanceledException(
    void
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

enum {
    _vprintSPOOL                    = 0x0001,
    _vprintOPEN_DOCUMENT            = 0x0002,
    _vprintOPEN_PAGE                = 0x0004,
    _vprintDISCARD_PAGE		    = 0x0008,
    _vprintOPEN_CONNECTION	    = 0x0010,
    _vprintDOCUMENT_OPENED_CONNECTION  = 0x0020,
    _vprintUSER_OPENED_CONNECTION   = 0x0040,
    _vprintUSE_NULL_DRAW_DEVICE	    = 0x0080,
    _vprintLANDSCAPE		    = 0x0100,
    _vprintSELECTION_ENABLED	    = 0x0200,
    _vprintSELECTION		    = 0x0400,
    _vprintERROR		    = 0x0800
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * exceptions
 */

extern vportLINK const vexClass               _vprintNoDefaultPrinterExceptionClass;
extern vportLINK const vexClass               _vprintJobCanceledExceptionClass;

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

struct vprint {
    vobject                         object;
    FILE                           *stream;
    vfsFile                        *file;
    void                           *device;
    vrectFloat                      paper, page;
    vprintNoteProc                  styleNoteProc, jobNoteProc;
    const void                     *data;
    unsigned int                    flags;
    unsigned int                    comment;
    const vchar			   *documentTitle;
    const vobjectAttributed	   *documentOwner;
    unsigned int		    currentPageNumber;
    unsigned int		    firstPageNumber;
    unsigned int		    lastPageNumber;
    vfsPath			   *path;
    vstr			   *command;
    vstr			   *printerOption;
    vstr			   *printerName;
};

#define vprintCLASS(SUPER, PRINT)                                             \
    vobjectCLASS(SUPER, PRINT);                                               \
    vclassVARIABLE(vprintCOMMENT, unsigned int);                              \
    vclassVARIABLE(vprintFLAGS, unsigned int);                                \
    vclassVARIABLE(vprintDYNAMIC_FUNCS, const vdrawDynamicFuncs*);            \
    vclassVARIABLE(vprintSTATIC_FUNCS, const vdrawStaticFuncs*);              \
    vclassVARIABLE(vprintDRIVER, const vdrawDriver*);                         \
    vclassMETHOD(vprintCONFIRM_STYLE, (PRINT *printer));                      \
    vclassMETHOD(vprintCONFIRM_JOB, (PRINT *printer));                        \
    vclassMETHOD(vprintOPEN_DOCUMENT, (PRINT *printer));                      \
    vclassMETHOD(vprintOPEN_PAGE, (PRINT *printer));                          \
    vclassMETHOD_RET(vprintOPEN_PAGE_CONTEXT,vdrawcontext *,(PRINT *printer));\
    vclassMETHOD(vprintCLOSE_PAGE, (PRINT *printer));                         \
    vclassMETHOD(vprintCLOSE_DOCUMENT, (PRINT *printer));                     \
    vclassMETHOD(vprintWRITE, (PRINT *printer, const void *buf, size_t count, \
			       size_t size));                                 \
    vclassMETHOD(vprintSET_STREAM, (PRINT *printer, FILE *stream));           \
    vclassMETHOD(vprintSET_FILE, (PRINT *printer, vfsFile *file));            \
    vclassMETHOD(vprintSET_FILE_PATH, (PRINT *printer, vfsPath *path));       \
    vclassMETHOD(vprintSET_COMMAND, (PRINT *printer, vstr *command));         \
    vclassMETHOD(vprintSET_PRINTER_NAME, (PRINT *printer, vstr *name));       \
    vclassMETHOD(vprintSET_PRINTER_OPTION, (PRINT *printer, vstr *option));   \
    vclassMETHOD(vprintSET_DEVICE, (PRINT *printer, void *device));           \
    vclassMETHOD(vprintSET_PAPER, (PRINT *printer, const vrectFloat *paper)); \
    vclassMETHOD(vprintSET_PAGE, (PRINT *printer, const vrectFloat *page));   \
    vclassMETHOD(vprintSET_STYLE_NOTIFY,                                      \
		 (PRINT *printer, vprintNoteProc styleNoteProc));             \
    vclassMETHOD(vprintSET_JOB_NOTIFY,                                        \
		 (PRINT *printer, vprintNoteProc jobNoteProc));               \
    vclassMETHOD(vprintSET_DATA, (PRINT *printer, const void *data));         \
    vclassMETHOD(vprintSET_SPOOL, (PRINT *printer, int flag));                \
    vclassMETHOD(vprintSET_COMMENT, (PRINT *printer, unsigned int comment));  \
    vclassMETHOD(vprintSET_DOCUMENT_TITLE, 				      \
		 (PRINT *printer, const vchar *title));   		      \
    vclassMETHOD(vprintSET_DOCUMENT_OWNER, 				      \
		 (PRINT *printer, const vobjectAttributed *owner));   	      \
    vclassMETHOD(vprintSET_PAGE_NUMBER,  				      \
		 (PRINT *printer, unsigned int pagenum));		      \
    vclassMETHOD(vprintSET_FIRST_PAGE_NUMBER,  				      \
		 (PRINT *printer, unsigned int pagenum));		      \
    vclassMETHOD(vprintSET_LAST_PAGE_NUMBER,  				      \
		 (PRINT *printer, unsigned int pagenum));                     \
    vclassMETHOD(vprintOPEN_CONNECTION, (PRINT *printer));                    \
    vclassMETHOD(vprintCLOSE_CONNECTION, (PRINT *printer));		      \
    vclassMETHOD(vprintOBSERVE_STYLE, (PRINT *printer, int confirmed));	      \
    vclassMETHOD(vprintOBSERVE_JOB, (PRINT *printer, int confirmed));         \
    vclassMETHOD(vprintSET_LANDSCAPE, (PRINT *printer, int flag));            \
    vclassMETHOD(vprintSET_SELECTION_ENABLED, (PRINT *printer, int flag));    \
    vclassMETHOD(vprintSET_SELECTION, (PRINT *printer, int flag));	      \
    vclassMETHOD(vprintSET_ERROR, (PRINT *printer, int flag))


struct vprintClass {
    vprintCLASS(vprintClass, vprint);
};


vportALIAS(vprintStream,	vprint)
vportALIAS(vprintPS,		vprintStream)
vportALIAS(vprintColorPS,	vprintPS)
vportALIAS(vprintPS2,		vprintColorPS)


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vprintSendObserveStyle(vprint *printer, int flag);
void _vprintSendObserveJob(vprint *printer, int flag);
void vprintchsrStartup(void);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

#define vprintGetObject(p)          vportBASE_OBJECT(p, object)

#define vprintCreateOfClass(c) \
    ((vprint*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vprintCreate() \
    vprintCreateOfClass(vprintGetPreferredClass())
#define vprintInitOfClass(p, c) \
    vobjectInitOfClass(vprintGetObject(p), (vobjectClass*)(c))
#define vprintInit(p) \
    vprintInitOfClass(p, vprintGetPreferredClass())
#define vprintDestroy(p) \
    vobjectDestroy(vprintGetObject(p))
#define vprintLoad(r) \
    ((vprint*)vobjectLoad(r))
#define vprintLoadInit(p, r) \
    vobjectLoadInit(vprintGetObject(p), (r))

#if (vportVCHAR_CODESET==vportCODESET_ASCII || \
     vportVCHAR_CODESET==vportCODESET_LATIN_1 || \
     vportVCHAR_CODESET==vportCODESET_MACINTOSH || \
     vportVCHAR_CODESET==vportCODESET_WINDOWS)
#define vprintSizedWriteString(p, s, n) vprintWrite(p, s, n, sizeof(vchar))
#endif

#define vprintWriteString(p, s) \
    vprintSizedWriteString(p, s, vcharLength(s))

#if (vportVCHAR_CODESET==vportCODESET_ASCII || \
     vportVCHAR_CODESET==vportCODESET_LATIN_1 || \
     vportVCHAR_CODESET==vportCODESET_MACINTOSH || \
     vportVCHAR_CODESET==vportCODESET_WINDOWS)
#define vprintWriteStringLiteral(p, s) \
    vprintWrite(p, s, strlen(s), sizeof(char))
#else
#define vprintWriteStringLiteral(p, s) \
    vprintWriteStringScribed(p, vcharScribeLiteral(s))
#endif

#define vprintWriteInt(p, n) \
    vprintWriteStringScribed(p, vnumScribeInt(n))
#define vprintWriteFloat(p, x) \
    vprintWriteStringScribed(p, \
        vnumScribeFloatFormatted(x, vnumGetDecimalDigitSet(), \
				 vnumGetNormalFormat(), (vnumFormat*)NULL, \
				 TRUE, 6))

#define vprintGetClass(p) \
    ((vprintClass*)vobjectGetClass(vprintGetObject(p)))
#define vprintGetStream(p)        ((p)->stream)
#define vprintGetFile(p)          ((p)->file)
#define vprintGetFilePath(p)      ((p)->path)
#define vprintGetCommand(p)       ((p)->command)
#define vprintGetPrinterOption(p) ((p)->printerOption)
#define vprintGetPrinterName(p)       ((p)->printerName)
#define vprintGetDevice(p)        ((p)->device)
#define vprintGetPaper(p)         ((const vrectFloat*)&(p)->paper)
#define vprintGetPage(p)          ((const vrectFloat*)&(p)->page)
#define vprintGetStyleNotify(p)   ((p)->styleNoteProc)
#define vprintGetJobNotify(p)     ((p)->jobNoteProc)
#define vprintGetData(p)          ((p)->data)
#define vprintIsSpool(p)         (((p)->flags&_vprintSPOOL)!=0)
#define vprintIsLandscape(p)     (((p)->flags&_vprintLANDSCAPE)!=0)
#define vprintConnectionIsOpen(p)  (((p)->flags&_vprintOPEN_CONNECTION)!=0)
#define vprintDocumentIsOpen(p)  (((p)->flags&_vprintOPEN_DOCUMENT)!=0)
#define vprintPageIsOpen(p)      (((p)->flags&_vprintOPEN_PAGE)!=0)
#define vprintGetComment(p)       ((p)->comment)
#define vprintGetDocumentTitle(p) ((p)->documentTitle)
#define vprintGetDocumentOwner(p) ((p)->documentOwner)
#define vprintGetPageNumber(p)    ((p)->currentPageNumber)
#define vprintGetFirstPageNumber(p)     ((p)->firstPageNumber)
#define vprintGetLastPageNumber(p)      ((p)->lastPageNumber)
#define vprintPageIsDiscarded(p)  (((p)->flags&_vprintDISCARD_PAGE)!=0)
#define vprintIsSelectionEnabled(p)  (((p)->flags&_vprintSELECTION_ENABLED)!=0)
#define vprintIsSelection(p)      (((p)->flags&_vprintSELECTION)!=0)
#define vprintHasError(p)	  (((p)->flags&_vprintERROR)!=0)
#define vprintEnableConfirms()		(vprintchsrStartup())

#define vprintGetNoDefaultPrinterExceptionClass() \
    (&_vprintNoDefaultPrinterExceptionClass)
#define vprintGetNoDefaultPrinterException() \
    ((vprintNoDefaultPrinterException*) \
         vexGetExceptionOfClass(&_vprintNoDefaultPrinterExceptionClass))

#define vprintGetJobCanceledExceptionClass() \
    (&_vprintJobCanceledExceptionClass)
#define vprintGetJobCanceledException() \
    ((vprintJobCanceledException*) \
         vexGetExceptionOfClass(&_vprintJobCanceledExceptionClass))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * printing
 */

#define vprintConfirmStyle(p) \
    vclassSend(vprintGetClass(p), vprintCONFIRM_STYLE, (p))
#define vprintConfirmJob(p) \
    vclassSend(vprintGetClass(p), vprintCONFIRM_JOB, (p))
#define vprintOpenConnection(p) \
    vclassSend(vprintGetClass(p), vprintOPEN_CONNECTION, (p))
#define vprintOpenDocument(p) \
    vclassSend(vprintGetClass(p), vprintOPEN_DOCUMENT, (p))
#define vprintOpenPage(p) \
    vclassSend(vprintGetClass(p), vprintOPEN_PAGE, (p))
#define vprintOpenPageContext(p) \
    vclassSend(vprintGetClass(p), vprintOPEN_PAGE_CONTEXT, (p))
#define vprintClosePage(p) \
    vclassSend(vprintGetClass(p), vprintCLOSE_PAGE, (p))
#define vprintCloseDocument(p) \
    vclassSend(vprintGetClass(p), vprintCLOSE_DOCUMENT, (p))
#define vprintCloseConnection(p) \
    vclassSend(vprintGetClass(p), vprintCLOSE_CONNECTION, (p))
#define vprintWrite(p, b, n, s) \
    vclassSend(vprintGetClass(p), vprintWRITE, (p, b, n, s))
#define vprintSetStream(p, s) \
    vclassSend(vprintGetClass(p), vprintSET_STREAM, (p, s))
#define vprintSetFile(p, f) \
    vclassSend(vprintGetClass(p), vprintSET_FILE, (p, f))
#define vprintSetFilePath(p, f) \
    vclassSend(vprintGetClass(p), vprintSET_FILE_PATH, (p, f))
#define vprintSetCommand(p, c) \
    vclassSend(vprintGetClass(p), vprintSET_COMMAND, (p, c))
#define vprintSetPrinterOption(p, c) \
    vclassSend(vprintGetClass(p), vprintSET_PRINTER_OPTION, (p, c))
#define vprintSetPrinterName(p, c) \
    vclassSend(vprintGetClass(p), vprintSET_PRINTER_NAME, (p, c))
#define vprintSetDevice(p, d) \
    vclassSend(vprintGetClass(p), vprintSET_DEVICE, (p, d))
#define vprintSetLandscape(p, c) \
    vclassSend(vprintGetClass(p), vprintSET_LANDSCAPE, (p, c))
#define vprintSetPaper(p, r) \
    vclassSend(vprintGetClass(p), vprintSET_PAPER, (p, r))
#define vprintSetPage(p, r) \
    vclassSend(vprintGetClass(p), vprintSET_PAGE, (p, r))
#define vprintSetStyleNotify(p, f) \
    vclassSend(vprintGetClass(p), vprintSET_STYLE_NOTIFY, (p, f))
#define vprintSetJobNotify(p, f) \
    vclassSend(vprintGetClass(p), vprintSET_JOB_NOTIFY, (p, f))
#define vprintSetData(p, d) \
    vclassSend(vprintGetClass(p), vprintSET_DATA, (p, d))
#define vprintSetSpool(p, c) \
    vclassSend(vprintGetClass(p), vprintSET_SPOOL, (p, c))
#define vprintSetComment(p, f) \
    vclassSend(vprintGetClass(p), vprintSET_COMMENT, (p, f))
#define vprintStore(p, r) \
    vclassSend(vprintGetClass(p), vobjectSTORE, (p, r))
#define vprintSetDocumentTitle(p, s) \
    vclassSend(vprintGetClass(p), vprintSET_DOCUMENT_TITLE, (p, s))
#define vprintSetDocumentOwner(p, o) \
    vclassSend(vprintGetClass(p), vprintSET_DOCUMENT_OWNER, (p, o))
#define vprintSetPageNumber(p, n) \
    vclassSend(vprintGetClass(p), vprintSET_PAGE_NUMBER, (p, n))
#define vprintSetFirstPageNumber(p, n) \
    vclassSend(vprintGetClass(p), vprintSET_FIRST_PAGE_NUMBER, (p, n))
#define vprintSetLastPageNumber(p, n) \
    vclassSend(vprintGetClass(p), vprintSET_LAST_PAGE_NUMBER, (p, n))
#define vprintSetSelectionEnabled(p, b) \
    vclassSend(vprintGetClass(p), vprintSET_SELECTION_ENABLED, (p, b))
#define vprintSetSelection(p, b) \
    vclassSend(vprintGetClass(p), vprintSET_SELECTION, (p, b))
#define vprintSetError(p, b) \
    vclassSend(vprintGetClass(p), vprintSET_ERROR, (p, b))

#define _vprintSendObserveStyle(p,f) \
    vclassSend(vprintGetClass(p), vprintOBSERVE_STYLE, (p, f))
#define _vprintSendObserveJob(p,f) \
    vclassSend(vprintGetClass(p), vprintOBSERVE_JOB, (p, f))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vprintINCLUDED */

