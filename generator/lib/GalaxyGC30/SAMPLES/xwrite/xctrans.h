/* $Id: xctrans.h,v 1.2 1996/04/19 01:26:51 bill Exp $ */

/************************************************************

    xctrans.h
    C Interface file for the xc trans module

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef xctransINCLUDED
#define xctransINCLUDED 1


#ifndef vportINCLUDED
#include <vport.h> 
#endif

#ifndef vcharINCLUDED
#include  vcharHEADER
#endif

#ifndef vnameINCLUDED
#include  vnameHEADER
#endif

#ifndef vfsINCLUDED
#include  vfsHEADER
#endif

#ifndef vinstanceINCLUDED
#include  vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * size of statically allocated buffer in _xctransReadFromFile
 */

#define xctransBUFFER_SIZE	    1024

/*
 * values returned by xctransGetCharsetByName
 */

enum 
{
   xctransCODESET_NO_INFO      = 0,

   /* single-byte */
   xctransCODESET_ASCII,
   xctransCODESET_LATIN_1,
   xctransCODESET_MACINTOSH,
   xctransCODESET_WINDOWS,
   xctransCODESET_LATIN_2,

   xctransCODESET_LATIN_3,
   xctransCODESET_LATIN_4,
   xctransCODESET_LATIN_5,
   xctransCODESET_GREEK,
   xctransCODESET_CYRILLIC,

   xctransCODESET_KOI8,
   xctransCODESET_HEBREW,
   xctransCODESET_ADOBE_STD_ENC,
   xctransCODESET_ADOBE_SYMBOL,
   xctransCODESET_DEC_TECH,

   xctransCODESET_VISCII,
   xctransCODESET_JISX0201,

   xctransCODESET_CODEPAGE_437,
   xctransCODESET_CODEPAGE_850,

   /* two-byte */
   xctransCODESET_UNICODE,
   xctransCODESET_JISX0208_83,
   xctransCODESET_JISX0212,
   xctransCODESET_KSC5601,
   xctransCODESET_GB2312,

   xctransCODESET_BIG5HKU,

   /* multi-byte */
   xctransCODESET_SJIS,
   xctransCODESET_JEUC,
   xctransCODESET_UTF,

   /* the end */
   _xctransCODESET_COUNT
};

/*
 * values returned by xctransGetCharsetType
 */

enum 
{
   xctransCHAR_SIZE_NO_INFO      = 0,

   xctransCHAR_SIZE_SINGLE_BYTE,
   xctransCHAR_SIZE_TWO_BYTE,
   xctransCHAR_SIZE_MULTI_BYTE
};


/*
 * values passed for byte ordering
 */

enum 
{
   xctransORDER_NO_INFO        = 0,

   xctransORDER_IMPLICIT,
   xctransORDER_BIG_ENDIAN,
   xctransORDER_LITTLE_ENDIAN
};

/*
 * values used to set the level of info sent to the NoteProc
 */
enum 
{
   xctransLEVEL_WARNING,
   xctransLEVEL_INFO
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct xctrans         xctrans;
typedef struct xctransClass    xctransClass;

typedef void (*xctransNoteProc)(
    xctrans                        *trans,
    int                             level,
    vscribe                        *msg
    );
/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * xcharset prototypes
 */

int xcharsetFindByName(
    const vchar                    *s
    );

int xcharsetFindSystem(
    void
    );

int xcharsetGetType(
    int                             charset
    );


/*
 * xctrans prototypes
 */

xctransClass *xctransGetDefaultClass(
    void
    );

xctrans *xctransCreateOfClass(
    xctransClass		   *clas
    );

xctransClass *xctransGetClass(
    xctrans			   *trans
    );

xctrans *xctransCreate(
    void
    );

void xctransInit(
    xctrans                        *trans
    );

void xctransInitOfClass(
    xctrans                        *trans,
    xctransClass                   *clas		
    );

void xctransDestroy(
    xctrans			   *trans
    );

void xctransDestroyLater(
    xctrans			   *trans
    );

vinstance *xctransGetInstance(
    xctrans			   *trans
    );

void xctransSetVerbose(
    xctrans                        *trans,
    int                             level
    );

int xctransGetVerbose(
    xctrans                        *trans
    );

void xctransSetNotify(
    xctrans                        *trans,
    xctransNoteProc		    proc
    );

xctransNoteProc xctransGetNotify(
    xctrans			   *trans
    );

void xctransNotifyString(
    xctrans			   *trans,
    int				    level,
    const vchar			   *msg
    );

void xctransNotifyLiteral(
    xctrans			   *trans,
    int				    level,
    const char			   *msg
    );

void xctransNotifyFormat(
    xctrans			   *trans,
    int				    level,
    const char			   *format,
    ...
    );

void xctransNotify(
    xctrans			   *trans,
    int				    level,
    vscribe			   *msg
    );

const void *xctransGetData(
    xctrans			   *trans
    );

void xctransSetData(
    xctrans			   *trans,
    const void			   *data
    );

vchar *xctransReadFromFile(
    xctrans                        *trans, 
    vfsFile                        *inputFile,
    vchar                          *string, 
    size_t                          size, 
    vchar                         **lastEOL
    );


int xctransWriteLineToFile(
    xctrans                        *trans, 
    vfsFile                        *outputFile,
    vchar                          *string, 
    size_t                          size
    );


vchar xctransGetEOL(
    xctrans                        *trans
    );

void xctransSetEOL(
    xctrans                        *trans, 
    int /* vchar */                 xcharEOL
    ); 

int xctransGetCharset(
    xctrans                        *trans
    );

void xctransSetCharset(
    xctrans                        *trans, 
    int                             charset
    ); 

int xctransGetByteOrder(
    xctrans                        *trans
    );

void xctransSetByteOrder(
    xctrans                        *trans,
    int                             byteOrder
    );

void xctransReset(
    xctrans                        *trans
    );

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */


extern const vname                 *_xctransPredefs[];


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct         xctrans
{
   vinstance             instance;
   const void           *data;

   xctransNoteProc       noteProc;
   int                   verbose;

   int                   charset;              /* charset to be used        */
   int                   byteOrder;            /* byte order, 
						  for 2-bytecharsets        */ 
   int                   flip;                 /* flip switch, 
						  to be used for unicode    */
   vbool                 skipLF;               /* vTRUE if prev read ended 
						  with CR                   */
   vbyte                 remainByteCount;      /* number of bytes held over 
						  (<= 5)                    */
   vbyte                 remainByteBuffer[6];  /* actual bytes held over    */
   vchar                 EOL;                  /* vchar to be used as EOL   */
};


#define xctransCLASS(SUPER, TRANS)                                   \
    vinstanceCLASS(SUPER, TRANS);                                    \
    vclassMETHOD_RET(xctransREAD_FROM_FILE, vchar *,                 \
		     (TRANS *trans, vfsFile *inputFile,              \
		      vchar *string, size_t size, vchar **lastEOL)); \
    vclassMETHOD_RET(xctransWRITE_LINE_TO_FILE, int,                 \
		     (TRANS *trans, vfsFile *outputFile,             \
		      vchar *string, size_t size))


struct xctransClass {
    xctransCLASS(xctransClass, xctrans);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define xctransCreateOfClass(c)         \
   ((xctrans *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define xctransCreate()                 \
   xctransCreateOfClass(xctransGetDefaultClass())

#define xctransInitOfClass(t, c)        \
   vinstanceInitOfClass(&(t)->instance, (vinstanceClass *)(c)))

#define xctransDestroyLater(t)	        vinstanceDestroyLater(&(t)->instance)

#define xctransGetInstance(t)	        (&(t)->instance)
#define xctransGetClass(t)              \
   ((xctransClass *)vinstanceGetClass(&(t)->instance))

#define xctransGetNotify(t)             ((t)->noteProc)
#define xctransGetVerbose(t)            ((t)->verbose)
#define xctransGetEOL(t)                ((t)->EOL)
#define xctransGetCharset(t)            ((t)->charset)
#define xctransGetByteOrder(t)          ((t)->byteOrder)         

#define xctransNotifyString(t, l, m)    xctransNotify(t, l, vcharScribe(m))

#define xctransNotifyLiteral(t, l, m)   \
   xctransNotify(t, l, vcharScribeLiteral(m))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


#define xctransDestroy(t)	               \
   vclassSend(xctransGetClass(t), vinstanceDESTROY, (t))

#define xctransReadFromFile(t, f, s, l, e)  \
   vclassSend(xctransGetClass(t), xctransREAD_FROM_FILE, (t, f, s, l, e))

#define xctransWriteLineToFile(t, f, s, l)  \
   vclassSend(xctransGetClass(t), xctransWRITE_LINE_TO_FILE, (t, f, s, l))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef xctransINCLUDED */
