/* $Id: xctrans.c,v 1.7 1997/08/14 14:59:41 alexey Exp $ */

/************************************************************

    xctrans.c
    C Implementation file for the xc trans module

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vportINCLUDED
#include <vport.h> 
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef xctransINCLUDED
#include "xctrans.h"
#endif

#if vdebugDEBUG
#define vdebugTAG "xctrans"
#endif

/* ----------------------------------------------------------------------------
 * private constants
 * ------------------------------------------------------------------------- */

#define      _xctransCR                  0x0D
#define      _xctransLF                  0x0A

#define      _xctransBYTE_ORDER_MARK     0xFEFF
#define      _xctransSWAP_ORDER_MARK     0xFFFE

enum 
{
   _xctransCODESET_NULL         = xctransCODESET_ASCII,
   _xctransCODESET_SINGLE_BYTE  = xctransCODESET_UNICODE,
   _xctransCODESET_TWO_BYTE     = xctransCODESET_SJIS,
   _xctransCODESET_MULTI_BYTE   = _xctransCODESET_COUNT
};

/*
 * private constants used for swapping shorts
 */

enum 
{
   _xctransFLIP_NOT_CHECKED    = 0,
   _xctransFLIP_SWAP,
   _xctransFLIP_DONT_SWAP
};

/*
 * private constants used for accessing messages;
 */

enum 
{
   _xctransMSG_UNKNOWN_CHARSET        = 0,
   _xctransMSG_USING_SYSTEM,
   _xctransMSG_NO_BYTE_ORDER_MARK,
   _xctransMSG_ASSUME_NO_SWAP,
   _xctransMSG_UNKNOWN_BYTE_ORDER,
   _xctransMSG_USING_IMPLICIT,
   _xctransMSG_USING_BIG_ENDIAN,
   _xctransMSG_SKIP_BYTE_ORDER_MARK,
   _xctransMSG_COUNT
};

/* ----------------------------------------------------------------------------
 * private types
 * ------------------------------------------------------------------------- */

typedef struct _xctransGlobals _xctransGlobals;

struct _xctransGlobals 
{
   xctransClass	*defaultClass;
};

/* ----------------------------------------------------------------------------
 * private variables
 * ------------------------------------------------------------------------- */

static void            **_xctransMaster = NULL;

vstr                    *_xctransMessages[_xctransMSG_COUNT];

static const char       *_xctransPredefLiterals[_xctransCODESET_COUNT] = 
{
   "no info",

   "ascii",
   "latin1",
   "macintosh",
   "windows",
   "latin2",

   "latin3",
   "latin4",
   "latin5",
   "greek",
   "cyrillic",

   "koi8",
   "hebrew",
   "adobestdenc",
   "adobesymbol",
   "dectech",

   "viscii",
   "jisx0201",

   "codepage437",
   "codepage850",

   "unicode",
   "jisx0208_83",
   "jisx0212",
   "ksc5601",
   "gb2312",

   "big5hku",

   "sjis",
   "jeuc",
   "utf"
};

/* ----------------------------------------------------------------------------
 * private external variables
 * ------------------------------------------------------------------------- */

const vname *_xctransPredefs[_xctransCODESET_COUNT];


/* ----------------------------------------------------------------------------
 * private macros
 * ------------------------------------------------------------------------- */

#define master()                         ((_xctransGlobals*)*_xctransMaster)

#define _xctransSetImplicitFlip(t, f)    ((t)->flip = (f))

#define _xctransGetImplicitFlip(t)       ((t)->flip)


/* ----------------------------------------------------------------------------
 * prototypes 
 * --------------------------------------------------------------------------*/

static void _xctransSetupGlobal(void);
static void _xctransSetupGlobalAndClient(void);

#if vmemBALANCE
static void _xctransGlobalShutdown(void);
static void _xctransClientShutdown(void);
#endif

static void _xctransSwapBytes(unsigned short *buffer, size_t count);
static vbool _xctransSetImplicitFlipUnicode(xctrans *trans, 
    unsigned short sh);

static vchar *_xctransReadFromFileSingleByte(xctrans *trans, 
    vfsFile *inputFile, vchar *string, size_t size, vchar **lastEOL);
static vchar *_xctransReadFromFileTwoByte(xctrans *trans, 
    vfsFile *inputFile, vchar *string, size_t size, vchar **lastEOL);
static vchar *_xctransReadFromFileMultiByte(xctrans *trans, 
    vfsFile *inputFile, vchar *string, size_t size, vchar **lastEOL);

static int _xctransWriteLineToFileSingleByte(xctrans *trans,
    vfsFile *inputFile, vchar *string, size_t size);
static int _xctransWriteLineToFileTwoByte(xctrans *trans,
    vfsFile *inputFile, vchar *string, size_t size);
static int _xctransWriteLineToFileMultiByte(xctrans *trans,
    vfsFile *inputFile, vchar *string, size_t size);

/* ----------------------------------------------------------------------------
 * wrapper functions; needed for the arrays of functions defined below.
 * ------------------------------------------------------------------------- */

static vscribe *_xctransSizedScribeASCII(char *string, size_t size);
static vscribe *_xctransSizedScribeLatin1(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeMacintosh(unsigned char *string, 
					     size_t size);
static vscribe *_xctransSizedScribeWindows(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeLatin2(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeLatin3(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeLatin4(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeLatin5(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeGreek(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeCyrillic(unsigned char *string, 
					    size_t size);
static vscribe *_xctransSizedScribeKoi8(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeHebrew(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeAdobeStdEnc(unsigned char *string, 
					       size_t size);
static vscribe *_xctransSizedScribeAdobeSymbol(unsigned char *string, 
					       size_t size);
static vscribe *_xctransSizedScribeDecTech(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeViscii(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeJISX0201(unsigned char *string, 
					    size_t size);
static vscribe *_xctransSizedScribeCodepage437(unsigned char *string, 
					       size_t size);
static vscribe *_xctransSizedScribeCodepage850(unsigned char *string, 
					       size_t size);

static vscribe *_xctransSizedScribeUnicode(unsigned short *string, 
					   size_t size);
static vscribe *_xctransSizedScribeJISX0208_83(unsigned short *string, 
					       size_t size);
static vscribe *_xctransSizedScribeJISX0212(unsigned short *string, 
					    size_t size);
static vscribe *_xctransSizedScribeKSC5601(unsigned short *string, 
					   size_t size);
static vscribe *_xctransSizedScribeGB2312(unsigned short *string, size_t size);
static vscribe *_xctransSizedScribeBig5hku(unsigned short *string, 
					   size_t size);

static vscribe *_xctransSizedScribeSJIS(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeJEUC(unsigned char *string, size_t size);
static vscribe *_xctransSizedScribeUTF(unsigned char *string, size_t size);

static size_t   _xctransSizedNormalizeSJIS(unsigned char *string, 
					   size_t length);
static size_t   _xctransSizedNormalizeJEUC(unsigned char *string, 
					   size_t length);
static size_t   _xctransSizedNormalizeUTF(unsigned char *string, 
					  size_t length);


static vscribe *_xctransSizedScribeASCIIExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeLatin1Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeMacintoshExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeWindowsExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeLatin2Export(vchar *string, size_t size);

static vscribe *_xctransSizedScribeLatin3Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeLatin4Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeLatin5Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeGreekExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeCyrillicExport(vchar *string, size_t size);

static vscribe *_xctransSizedScribeKoi8Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeHebrewExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeAdobeStdEncExport(vchar *string, 
						     size_t size);
static vscribe *_xctransSizedScribeAdobeSymbolExport(vchar *string, 
						     size_t size);
static vscribe *_xctransSizedScribeDecTechExport(vchar *string, size_t size);

static vscribe *_xctransSizedScribeVisciiExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeJISX0201Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeCodepage437Export(vchar *string, 
						     size_t size); 
static vscribe *_xctransSizedScribeCodepage850Export(vchar *string, 
						     size_t size); 

static vscribe *_xctransSizedScribeUnicodeExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeJISX0208_83Export(vchar *string, 
						     size_t size);
static vscribe *_xctransSizedScribeJISX0212Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeKSC5601Export(vchar *string, size_t size);
static vscribe *_xctransSizedScribeGB2312Export(vchar *string, size_t size);

static vscribe *_xctransSizedScribeBig5hkuExport(vchar *string, size_t size);

static vscribe *_xctransSizedScribeSJISExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeJEUCExport(vchar *string, size_t size);
static vscribe *_xctransSizedScribeUTFExport(vchar *string, size_t size);


static vscribe *(*_xctransSizedScribeFrom[_xctransCODESET_COUNT])() = 
{
   NULL,

   _xctransSizedScribeASCII,
   _xctransSizedScribeLatin1,
   _xctransSizedScribeMacintosh,
   _xctransSizedScribeWindows,
   _xctransSizedScribeLatin2,

   _xctransSizedScribeLatin3,
   _xctransSizedScribeLatin4,
   _xctransSizedScribeLatin5,
   _xctransSizedScribeGreek,
   _xctransSizedScribeCyrillic,

   _xctransSizedScribeKoi8,
   _xctransSizedScribeHebrew,
   _xctransSizedScribeAdobeStdEnc,
   _xctransSizedScribeAdobeSymbol,
   _xctransSizedScribeDecTech,

   _xctransSizedScribeViscii,
   _xctransSizedScribeJISX0201,

   _xctransSizedScribeCodepage437,
   _xctransSizedScribeCodepage850,

   _xctransSizedScribeUnicode,
   _xctransSizedScribeJISX0208_83,
   _xctransSizedScribeJISX0212,
   _xctransSizedScribeKSC5601,
   _xctransSizedScribeGB2312,

   _xctransSizedScribeBig5hku,

   _xctransSizedScribeSJIS,
   _xctransSizedScribeJEUC,
   _xctransSizedScribeUTF
};

/* ----------------------------------------------------------------------------
 * array of normalize functions, necessary for multi-byte encodings
 * ------------------------------------------------------------------------- */


static size_t (*_xctransSizedNormalize
	       [_xctransCODESET_MULTI_BYTE - _xctransCODESET_TWO_BYTE])() =
{
   _xctransSizedNormalizeSJIS,
   _xctransSizedNormalizeJEUC,
   _xctransSizedNormalizeUTF
};



static vscribe *(*_xctransSizedScribeTo[_xctransCODESET_COUNT])() = 
{
   NULL,

   _xctransSizedScribeASCIIExport,
   _xctransSizedScribeLatin1Export,
   _xctransSizedScribeMacintoshExport,
   _xctransSizedScribeWindowsExport,
   _xctransSizedScribeLatin2Export,

   _xctransSizedScribeLatin3Export,
   _xctransSizedScribeLatin4Export,
   _xctransSizedScribeLatin5Export,
   _xctransSizedScribeGreekExport,
   _xctransSizedScribeCyrillicExport,

   _xctransSizedScribeKoi8Export,
   _xctransSizedScribeHebrewExport,
   _xctransSizedScribeAdobeStdEncExport,
   _xctransSizedScribeAdobeSymbolExport,
   _xctransSizedScribeDecTechExport,

   _xctransSizedScribeVisciiExport,
   _xctransSizedScribeJISX0201Export,

   _xctransSizedScribeCodepage437Export,
   _xctransSizedScribeCodepage850Export,

   _xctransSizedScribeUnicodeExport,
   _xctransSizedScribeJISX0208_83Export,
   _xctransSizedScribeJISX0212Export,
   _xctransSizedScribeKSC5601Export,
   _xctransSizedScribeGB2312Export,

   _xctransSizedScribeBig5hkuExport,

   _xctransSizedScribeSJISExport,
   _xctransSizedScribeJEUCExport,
   _xctransSizedScribeUTFExport
};

/* ----------------------------------------------------------------------------
 * wrapper functions for the arrays
 * ------------------------------------------------------------------------- */


static vscribe *_xctransSizedScribeASCII(char *string, size_t size)
{
   return vcharSizedScribeASCII(string, size);
}

static vscribe *_xctransSizedScribeLatin1(unsigned char *string, size_t size)
{
   return vcharSizedScribeLatin1(string, size);
}

static vscribe *_xctransSizedScribeMacintosh(unsigned char *string, 
					     size_t size)
{
   return vcharSizedScribeMacintosh(string, size);
}

static vscribe *_xctransSizedScribeWindows(unsigned char *string, size_t size)
{
   return vcharSizedScribeWindows(string, size);
}

static vscribe *_xctransSizedScribeLatin2(unsigned char *string, size_t size)
{
   return vcharSizedScribeLatin2(string, size);
}

static vscribe *_xctransSizedScribeLatin3(unsigned char *string, size_t size)
{
   return vcharSizedScribeLatin3(string, size);
}

static vscribe *_xctransSizedScribeLatin4(unsigned char *string, size_t size)
{
   return vcharSizedScribeLatin4(string, size);
}

static vscribe *_xctransSizedScribeLatin5(unsigned char *string, size_t size)
{
   return vcharSizedScribeLatin5(string, size);
}

static vscribe *_xctransSizedScribeGreek(unsigned char *string, size_t size)
{
   return vcharSizedScribeGreek(string, size);
}

static vscribe *_xctransSizedScribeCyrillic(unsigned char *string, size_t size)
{
   return vcharSizedScribeCyrillic(string, size);
}

static vscribe *_xctransSizedScribeKoi8(unsigned char *string, size_t size)
{
   return vcharSizedScribeKoi8(string, size);
}

static vscribe *_xctransSizedScribeHebrew(unsigned char *string, size_t size)
{
   return vcharSizedScribeHebrew(string, size);
}

static vscribe *_xctransSizedScribeAdobeStdEnc(unsigned char *string, 
					       size_t size)
{
   return vcharSizedScribeAdobeStdEnc(string, size);
}

static vscribe *_xctransSizedScribeAdobeSymbol(unsigned char *string, 
					       size_t size)
{
   return vcharSizedScribeAdobeSymbol(string, size);
}

static vscribe *_xctransSizedScribeDecTech(unsigned char *string, size_t size)
{
   return vcharSizedScribeDecTech(string, size);
}

static vscribe *_xctransSizedScribeViscii(unsigned char *string, size_t size)
{
   return vcharSizedScribeViscii(string, size);
}

static vscribe *_xctransSizedScribeJISX0201(unsigned char *string, size_t size)
{
   return vcharSizedScribeJISX0201(string, size);
}

static vscribe *_xctransSizedScribeCodepage437(unsigned char *string, 
					       size_t size) 
{
   return _vcharSizedScribeCodepage437ToUnicode(string, size);
}

static vscribe *_xctransSizedScribeCodepage850(unsigned char *string, 
					       size_t size) 
{
   return _vcharSizedScribeCodepage850ToUnicode(string, size);
}

static vscribe *_xctransSizedScribeUnicode(unsigned short *string, size_t size)
{
   return vcharSizedScribeUnicode(string, size);
}

static vscribe *_xctransSizedScribeJISX0208_83(unsigned short *string, 
					       size_t size)
{
   return vcharSizedScribeJISX0208_83(string, size);
}

static vscribe *_xctransSizedScribeJISX0212(unsigned short *string, 
					    size_t size)
{
   return vcharSizedScribeJISX0212(string, size);
}

static vscribe *_xctransSizedScribeKSC5601(unsigned short *string, size_t size)
{
   return vcharSizedScribeKSC5601(string, size);
}

static vscribe *_xctransSizedScribeGB2312(unsigned short *string, size_t size)
{
   return vcharSizedScribeGB2312(string, size);
}

static vscribe *_xctransSizedScribeBig5hku(unsigned short *string, size_t size)
{
   return vcharSizedScribeBig5hku(string, size);
}

static vscribe *_xctransSizedScribeSJIS(unsigned char *string, size_t size)
{
   return vcharSizedScribeSJIS(string, size);
}

static vscribe *_xctransSizedScribeJEUC(unsigned char *string, size_t size)
{
   return vcharSizedScribeJEUC(string, size);
}

static vscribe *_xctransSizedScribeUTF(unsigned char *string, size_t size)
{
   return vcharSizedScribeUTF(string, size);
}

static size_t   _xctransSizedNormalizeSJIS(unsigned char *string, 
					   size_t length)
{
   return vcharSizedNormalizeSJIS(string, length);
}

static size_t   _xctransSizedNormalizeJEUC(unsigned char *string, 
					   size_t length)
{
   return vcharSizedNormalizeJEUC(string, length);
}

static size_t   _xctransSizedNormalizeUTF(unsigned char *string, size_t length)
{
   return vcharSizedNormalizeUTF(string, length);
}


static vscribe *_xctransSizedScribeASCIIExport(vchar *string, size_t size)
{
   return vcharSizedScribeASCIIExport(string, size);
}

static vscribe *_xctransSizedScribeLatin1Export(vchar *string, size_t size)
{
   return vcharSizedScribeLatin1Export(string, size);
}

static vscribe *_xctransSizedScribeMacintoshExport(vchar *string, size_t size)
{
   return vcharSizedScribeMacintoshExport(string, size);
}

static vscribe *_xctransSizedScribeWindowsExport(vchar *string, size_t size)
{
   return vcharSizedScribeWindowsExport(string, size);
}

static vscribe *_xctransSizedScribeLatin2Export(vchar *string, size_t size)
{
   return vcharSizedScribeLatin2Export(string, size);
}


static vscribe *_xctransSizedScribeLatin3Export(vchar *string, size_t size)
{
   return vcharSizedScribeLatin3Export(string, size);
}

static vscribe *_xctransSizedScribeLatin4Export(vchar *string, size_t size)
{
   return vcharSizedScribeLatin4Export(string, size);
}

static vscribe *_xctransSizedScribeLatin5Export(vchar *string, size_t size)
{
   return vcharSizedScribeLatin5Export(string, size);
}

static vscribe *_xctransSizedScribeGreekExport(vchar *string, size_t size)
{
   return vcharSizedScribeGreekExport(string, size);
}

static vscribe *_xctransSizedScribeCyrillicExport(vchar *string, size_t size)
{
   return vcharSizedScribeCyrillicExport(string, size);
}


static vscribe *_xctransSizedScribeKoi8Export(vchar *string, size_t size)
{
   return vcharSizedScribeKoi8Export(string, size);
}

static vscribe *_xctransSizedScribeHebrewExport(vchar *string, size_t size)
{
   return vcharSizedScribeHebrewExport(string, size);
}

static vscribe *_xctransSizedScribeAdobeStdEncExport(vchar *string, 
						     size_t size)
{
   return vcharSizedScribeAdobeStdEncExport(string, size);
}

static vscribe *_xctransSizedScribeAdobeSymbolExport(vchar *string, 
						     size_t size)
{
   return vcharSizedScribeAdobeSymbolExport(string, size);
}

static vscribe *_xctransSizedScribeDecTechExport(vchar *string, size_t size)
{
   return vcharSizedScribeDecTechExport(string, size);
}


static vscribe *_xctransSizedScribeVisciiExport(vchar *string, size_t size)
{
   return vcharSizedScribeVisciiExport(string, size);
}

static vscribe *_xctransSizedScribeJISX0201Export(vchar *string, size_t size)
{
   return vcharSizedScribeJISX0201Export(string, size);
}

static vscribe *_xctransSizedScribeCodepage437Export(vchar *string, 
						     size_t size)
{
   return _vcharSizedScribeUnicodeToCodepage437((unsigned short*)string, size);
}

static vscribe *_xctransSizedScribeCodepage850Export(vchar *string, 
						     size_t size)
{
   return _vcharSizedScribeUnicodeToCodepage850((unsigned short*)string, size);
}

static vscribe *_xctransSizedScribeUnicodeExport(vchar *string, size_t size)
{
   return vcharSizedScribeUnicodeExport(string, size);
}

static vscribe *_xctransSizedScribeJISX0208_83Export(vchar *string, 
						     size_t size)
{
   return vcharSizedScribeJISX0208_83Export(string, size);
}

static vscribe *_xctransSizedScribeJISX0212Export(vchar *string, size_t size)
{
   return vcharSizedScribeJISX0212Export(string, size);
}

static vscribe *_xctransSizedScribeKSC5601Export(vchar *string, size_t size)
{
   return vcharSizedScribeKSC5601Export(string, size);
}

static vscribe *_xctransSizedScribeGB2312Export(vchar *string, size_t size)
{
   return vcharSizedScribeGB2312Export(string, size);
}


static vscribe *_xctransSizedScribeBig5hkuExport(vchar *string, size_t size)
{
   return vcharSizedScribeBig5hkuExport(string, size);
}


static vscribe *_xctransSizedScribeSJISExport(vchar *string, size_t size)
{
   return vcharSizedScribeSJISExport(string, size);
}

static vscribe *_xctransSizedScribeJEUCExport(vchar *string, size_t size)
{
   return vcharSizedScribeJEUCExport(string, size);
}

static vscribe *_xctransSizedScribeUTFExport(vchar *string, size_t size)
{
   return vcharSizedScribeUTFExport(string, size);
}


/* ---------------------------------------------------------------------------
 * xcharset entry points
 * ------------------------------------------------------------------------- */


/*
 * xcharsetFindByName: 
 * find the charset value matching the character set with name s.
 */

int xcharsetFindByName(const vchar *s)
{
   int           lp;
   
   /*
    * Startup and create the class, if necessary
    */

   if (_xctransMaster == NULL)
       _xctransSetupGlobal();

   for (lp = xctransCODESET_NO_INFO; lp < _xctransCODESET_COUNT; lp++)
      if (vcharCompareBase(_xctransPredefs[lp], s) == 0)
	 return(lp);
	 
   return xctransCODESET_NO_INFO;

}


/*
 * xcharsetFindSystem: 
 * find the charset value matching the system character set.
 */

int xcharsetFindSystem(void)
{
   switch (vcharGetSystemCharacterSet())
      {
       case vcharSET_ASCII:
	 return xctransCODESET_ASCII;
       case vcharSET_LATIN_1:
	 return xctransCODESET_LATIN_1;
       case vcharSET_MACINTOSH:
	 return xctransCODESET_MACINTOSH;
       case vcharSET_WINDOWS:
	 return xctransCODESET_WINDOWS;

       case vcharSET_CODEPAGE_437:
	 return xctransCODESET_CODEPAGE_437;
       case vcharSET_CODEPAGE_850:
	 return xctransCODESET_CODEPAGE_850;

       case vcharSET_UNICODE:
	 return xctransCODESET_UNICODE;

       case vcharSET_SJIS:
	 return xctransCODESET_SJIS;
       case vcharSET_JEUC:
	 return xctransCODESET_JEUC;
       case vcharSET_UTF:
	 return xctransCODESET_UTF;
       default:
	 vexGenerateArgRange();
      }

   return xctransCODESET_NO_INFO;
}

/*
 * xcharsetGetType:
 * return the type of the charset value passed in.
 * 
 * Possible return values are single-byte, two-byte, multi-byte, no-info.
 */


int xcharsetGetType(int charset)
{

#if vdebugDEBUG
   if ((charset < xctransCODESET_NO_INFO) 
       || (charset >= _xctransCODESET_COUNT))
      vexGenerateArgRange();
#endif

   if (charset < _xctransCODESET_SINGLE_BYTE)
      return xctransCHAR_SIZE_SINGLE_BYTE;
   else if (charset < _xctransCODESET_TWO_BYTE)
      return xctransCHAR_SIZE_TWO_BYTE;
   else if (charset < _xctransCODESET_MULTI_BYTE)
      return xctransCHAR_SIZE_MULTI_BYTE;

   return xctransCHAR_SIZE_NO_INFO;
}


/* 
 * xctrans methods
 *
 */

static void _xctransInit(xctrans *trans)
{

   /*
    * Startup and create the class, if necessary
    */

   if (_xctransMaster == NULL || *_xctransMaster == NULL)
       _xctransSetupGlobalAndClient();


   vclassSendSuper(master()->defaultClass, vinstanceINIT, (trans));

    /*
     * our local stuff
     */
   trans->data = NULL;

   trans->noteProc = NULL;
   trans->verbose = xctransLEVEL_INFO;

   trans->charset = xcharsetFindSystem();
   trans->byteOrder = xctransORDER_IMPLICIT;
   trans->flip = _xctransFLIP_NOT_CHECKED;
   trans->skipLF = vFALSE;
   trans->remainByteCount = 0;
   trans->EOL = vcharEOL;

} /* _xctransInit */


static void _xctransDestroy(xctrans *trans)
{
    vclassSendSuper(master()->defaultClass, vinstanceDESTROY, (trans));
    
} /* _xctransDestroy */

/*
 * xctransReadFromFile:
 *
 * trans     -> the xctrans object
 * inputFile -> the file to read from
 * string    -> the vchar buffer where the input data is deposited
 * size      -> the maximum number of vchars to be demposited in string
 * lastEOL  <-> points past the last EOL character placed in string
 *
 * returns   <-  pointer past the last vchar placed in the string
 */

vchar *_xctransReadFromFile(xctrans *trans, vfsFile *inputFile,
			    vchar *string, size_t size, vchar **lastEOL)
{
   int            charset;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (inputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(string);

   charset = xctransGetCharset(trans);

#if vdebugDEBUG
   if ((charset < xctransCODESET_NO_INFO) 
       || (charset >= _xctransCODESET_COUNT))
      vexGenerateArgRange();
#endif

   /*
    * lastEOL should point just passed the last xcharEOL deposited
    * in the string; in the beginning set to the head of the string
    * (no xcharEOLs written out yet).
    */

   *lastEOL = string; 

   switch (xcharsetGetType(charset))
      {
       case xctransCHAR_SIZE_SINGLE_BYTE:
	 return (_xctransReadFromFileSingleByte(trans, inputFile,
						string, size, lastEOL));
       case xctransCHAR_SIZE_TWO_BYTE:
	 return (_xctransReadFromFileTwoByte(trans, inputFile,
					     string, size, lastEOL));

       case xctransCHAR_SIZE_MULTI_BYTE:
	 return (_xctransReadFromFileMultiByte(trans, inputFile,
					       string, size, lastEOL));

       case xctransCHAR_SIZE_NO_INFO:
	 xctransNotifyString(trans, xctransLEVEL_WARNING, 
			     _xctransMessages[_xctransMSG_UNKNOWN_CHARSET]);
	 xctransNotifyString(trans, xctransLEVEL_WARNING, 
			     _xctransMessages[_xctransMSG_USING_SYSTEM]);

	 xctransSetCharset(trans, xcharsetFindSystem());
	 xctransReadFromFile(trans, inputFile, string, size, lastEOL);
       default:
	 vexGenerateModuleState();
      }	 

   return string;
	 
} /* xctransReadFromFile */


/*
 * xctransWriteLineToFile:
 *
 * trans     -> the xctrans object
 * outputFile-> the file to write to
 * string    -> the vchar buffer where the data is read from
 * size      -> the maximum number of valid vchars in the buffer;
 *              note that the actual number of vchars to write maybe 
 *              smaller (read up to xcharEOL).
 *
 * returns   <-  numbers of vchars actually scanned and exported.
 */

int _xctransWriteLineToFile(xctrans *trans, vfsFile *outputFile,
			    vchar *string, size_t size)
{
   int            charset;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (outputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(0);

   charset = xctransGetCharset(trans);

#if vdebugDEBUG
   if ((charset < xctransCODESET_NO_INFO) 
       || (charset >= _xctransCODESET_COUNT))
      vexGenerateArgRange();
#endif

   switch (xcharsetGetType(charset))
      {
       case xctransCHAR_SIZE_SINGLE_BYTE:
	 return (_xctransWriteLineToFileSingleByte(trans, outputFile,
						   string, size));
       case xctransCHAR_SIZE_TWO_BYTE:
	 return (_xctransWriteLineToFileTwoByte(trans, outputFile,
						string, size));

       case xctransCHAR_SIZE_MULTI_BYTE:
	 return (_xctransWriteLineToFileMultiByte(trans, outputFile,
						  string, size));

       case xctransCHAR_SIZE_NO_INFO:
	 xctransNotifyString(trans, xctransLEVEL_WARNING,
			     _xctransMessages[_xctransMSG_UNKNOWN_CHARSET]);
	 xctransNotifyString(trans, xctransLEVEL_WARNING,
			     _xctransMessages[_xctransMSG_USING_SYSTEM]);

	 xctransSetCharset(trans, xcharsetFindSystem());
	 xctransWriteLineToFile(trans, outputFile, string, size);
       default:
	 vexGenerateModuleState();
      }	 

   return 0;
	 
} /* xctransWriteLineToFile */


/***********
 * utilities
 ***********/

/*
 *  _xctransSwapBytes:
 *            swaps byte order for unsigned shorts in place
 *
 * buffer  -> the string of unsigned shorts
 * count   -> the numnber of shorts in the string
 */

static void _xctransSwapBytes(unsigned short *buffer, size_t count)
{
   vbyte  *temp, *end, ch;

   end = (vbyte *)buffer + sizeof(unsigned short) * count;

   for (temp = (vbyte *)buffer; temp < end; temp++ )
      {
	ch = *temp;
	*temp = *(temp + 1);
	*++temp = ch;
      }
   return;
   
} /* _xctransSwapBytes */

/*****************************************************************************/
static vbool _xctransSetImplicitFlipUnicode(xctrans *trans, unsigned short sh)
{
   if (sh == _xctransBYTE_ORDER_MARK)
      {
	 _xctransSetImplicitFlip(trans, _xctransFLIP_DONT_SWAP);

	 return TRUE;
      }
   else if (sh == _xctransSWAP_ORDER_MARK)
      {
	 _xctransSetImplicitFlip(trans, _xctransFLIP_SWAP);
	 return TRUE;
      }
   else
      {
	 /*
	  * assume no swapping
	  */
	 xctransNotifyString(trans, xctransLEVEL_WARNING,
			     _xctransMessages[_xctransMSG_NO_BYTE_ORDER_MARK]);
	 xctransNotifyString(trans, xctransLEVEL_WARNING,
			     _xctransMessages[_xctransMSG_ASSUME_NO_SWAP]);

	 _xctransSetImplicitFlip(trans, _xctransFLIP_DONT_SWAP);
      }
   return FALSE;
}

/*
 * _xctransReadFromFileSingleByte:
 *
 * trans     -> the xctrans state
 * inputFile -> the file to read from
 * string    -> the vchar buffer where the input data is deposited
 * size      -> the maximum number of vchars to be demposited in string
 * lastEOL  <-> points past the last EOL character placed in string
 *
 * returns   <-  pointer past the last vchar placed in the string
 */


static vchar *_xctransReadFromFileSingleByte(xctrans *trans, 
					     vfsFile *inputFile,
					     vchar *string, 
					     size_t size, 
					     vchar **lastEOL)
{
   vbyte          firstBuffer[xctransBUFFER_SIZE];
   vbyte          *inputBuffer;
   vbyte          *currentbyte, *startbyte, *endbyte;
   vbyte          ch;            
   vbool          skipLF;           

   size_t         inputLength;

   int            charset;
   vscribe        *scribe;
   vchar          xcharEOL;           
   vchar          *copy;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (inputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(string);

   charset = xctransGetCharset(trans);

   /* 
    * at most size bytes will be translated into at most size vchars;
    * allocate a bigger input buffer if nesessary 
    */

   if (size > xctransBUFFER_SIZE)
      inputBuffer = (vbyte *)vmemAlloc(size * sizeof(vbyte));
   else
      inputBuffer = firstBuffer;
    
   inputLength = vfsReadFile(inputBuffer, sizeof(vbyte), size, inputFile);

   /* 
    * scan input buffer for LF, CR, CR-LF; 
    * isolated CRs and LFs will be translated to xcharEOL;
    * pairs of CR-LF will be mapped to a single xcharEOL;
    * scribing is done between xcharEOLs.
    * if final byte is CR, set skipLF to vTRUE for next visit to file.
    */

   xcharEOL = trans->EOL;
   skipLF = trans->skipLF;
   
   startbyte = currentbyte = inputBuffer;
   endbyte = inputBuffer + inputLength;
   
   copy = string;

   while (currentbyte < endbyte)
      {
	 ch = *currentbyte;
	 if (ch == _xctransCR)
	    {
	       /*
		* emit previous substring followed by xcharEOL;
		* init next substring, set skipLF
		*/
	       scribe = (_xctransSizedScribeFrom[charset])
		  (startbyte, currentbyte - startbyte);
	       
	       copy = vcharSizedCopyScribed(scribe, copy);
	       *copy++ = xcharEOL;
	       *lastEOL = copy;
	       
	       startbyte = currentbyte + 1;
	       skipLF = vTRUE;
	    }
	 else if (ch == _xctransLF)
	    {
	       /*
		* if skipLF is vTRUE, ignore LF, update next substring;
		* else, emit substring followed by xcharEOL, 
		* init next substring
		*/
	       if (!skipLF)
		  {

	       
		     scribe = (_xctransSizedScribeFrom[charset])
			(startbyte, currentbyte - startbyte);
	       
		     copy = vcharSizedCopyScribed(scribe, copy);
		     *copy++ = xcharEOL;
		     *lastEOL = copy;
		     
		     startbyte = currentbyte + 1;
		     /* skipLF == vFALSE */
		  }
	       else
		  {
		     startbyte = currentbyte + 1;
		     skipLF = vFALSE;
		  }
	    }
	 else
	    {
	       /* other bytes */
	       skipLF = vFALSE;
	    }

	 
	 currentbyte++;
      }

   /* 
    * exhausted input, only need to scribe if startbyte < endbyte
    */

   if (startbyte < endbyte)
      {
	 scribe = (_xctransSizedScribeFrom[charset])
	    (startbyte, currentbyte - startbyte);
	       
	 copy = vcharSizedCopyScribed(scribe, copy);
		     
      }

   /*
    * store the skipLF value in trans
    */

   trans->skipLF = skipLF;

   /* 
    * free the input buffer if dynamically allocated 
    */
   
   if (inputBuffer != firstBuffer)
      vmemFree(inputBuffer);
   
   return (copy);
   
} /* _xctransReadFromFileSingleByte */

/*
 * _xctransReadFromFileTwoByte:
 *
 * trans     -> the xctrans state
 * inputFile -> the file to read from
 * string    -> the vchar buffer where the input data is deposited
 * size      -> the maximum number of vchars to be demposited in string
 * lastEOL  <-> points past the last EOL character placed in string
 *
 * returns   <-  pointer past the last vchar placed in the string
 */

static vchar *_xctransReadFromFileTwoByte(xctrans *trans, 
					  vfsFile *inputFile,
					  vchar *string, 
					  size_t size, 
					  vchar **lastEOL)
{
   int            charset;
   int            byteOrder;

   unsigned short  firstBuffer[xctransBUFFER_SIZE];
   unsigned short *inputBuffer;
   unsigned short *currentshort, *startshort, *endshort;

   vchar          *copy;
   vchar           xcharEOL;           
   vscribe        *scribe;

   vbool           skipLF;
   size_t          inputLength;
   int             adjustedLength;
   unsigned short  ch;
   int             remainByteCount;

   vbool           skipOne = vFALSE;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (inputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(string);

   skipLF = trans->skipLF;
   xcharEOL = trans->EOL;

   charset = xctransGetCharset(trans);

   /* 
    * at most size shorts will be translated into at most size vchars;
    * allocate a bigger input buffer if nesessary 
    */

   if (size > xctransBUFFER_SIZE)
      inputBuffer = (unsigned short *)vmemAlloc(size * sizeof(unsigned short));
   else
      inputBuffer = firstBuffer;
    
   /* 
    * adjust number of shorts to be read to be placed in the string buffer;
    * be conservative by 1, because of possible stray byte at EOF.
    */
   if (size > 1) 
      {
	 adjustedLength = size - 1;
      } 
   else 
      {
	 adjustedLength = size;
      }
   
   inputLength = vfsReadFile((vbyte *)inputBuffer, sizeof(unsigned short), 
			     (size_t) adjustedLength, 
			     inputFile);

   /* 
    * set the endOfFile flag if input buffer empty; read extra byte if there
    */
   
   remainByteCount = 0;            

   if ((inputLength == 0) || (inputLength < adjustedLength))
      {

	 /* 
	  * move the remaining bytes back into the input buffer 
	  */

	 remainByteCount = vfsReadFile((vbyte *)(inputBuffer + inputLength),
				       sizeof(vbyte), 1, inputFile);
      }		       

   /* 
    * byte swapping 
    */
   byteOrder = xctransGetByteOrder(trans);

   if (inputLength > 0)
      {
	 switch(byteOrder)
	    {
	     case xctransORDER_NO_INFO:
	       xctransNotifyString
		  (trans, xctransLEVEL_WARNING,
		   _xctransMessages[_xctransMSG_UNKNOWN_BYTE_ORDER]);

	       if (charset == xctransCODESET_UNICODE)
		  {
		     xctransNotifyString
			(trans, xctransLEVEL_WARNING,
			 _xctransMessages[_xctransMSG_USING_IMPLICIT]);

		     xctransSetByteOrder(trans, xctransORDER_IMPLICIT);
		  }
	       else
		  {
		     xctransNotifyString
			(trans, xctransLEVEL_WARNING,
			 _xctransMessages[_xctransMSG_USING_BIG_ENDIAN]);

		     xctransSetByteOrder(trans, xctransORDER_BIG_ENDIAN);
		  }

	       /* fall through */

	     case xctransORDER_IMPLICIT:
	       /* 
		* check byte order mark for tagged Unicode, 
		* fall-through to BIG_ENDIAN for rest
		*/
	       
	       if (charset == xctransCODESET_UNICODE)
		  {
		     switch(_xctransGetImplicitFlip(trans))
			{
			 case _xctransFLIP_NOT_CHECKED:
			   if (_xctransSetImplicitFlipUnicode
			       (trans, *inputBuffer))
			      {
				 /*
				  * need to skip the first character 
				  */
				 if ((_xctransGetImplicitFlip(trans))
				     == _xctransFLIP_SWAP)
				    {
				       xctransNotifyString
					  (trans, xctransLEVEL_WARNING,
			   _xctransMessages[_xctransMSG_SKIP_BYTE_ORDER_MARK]);

				       _xctransSwapBytes(inputBuffer + 1, 
							 inputLength - 1);
				    }
				 /* otherwise don't swap */
				 skipOne = vTRUE;
			      }
			   break;
			   
			 case _xctransFLIP_SWAP:
			   _xctransSwapBytes(inputBuffer, inputLength);
			   break;
			   
			 case _xctransFLIP_DONT_SWAP:
			   break;
			   
			 default:
			   vexGenerateModuleState();
			}
		     break;
		  }
	       /*
		* else fall through to BIG-ENDIAN
		*/
	       
	     case xctransORDER_BIG_ENDIAN:	       
#if (vportLITTLE_ENDIAN_SHORT)
	       _xctransSwapBytes(inputBuffer, inputLength);
#endif
	       break;
	       
	     case xctransORDER_LITTLE_ENDIAN:	       
#if (vportBIG_ENDIAN_SHORT)
	       _xctransSwapBytes(inputBuffer, inputLength);
#endif
	       break;
	       
	     default:
	       vexGenerateModuleState();
	    }
      }
   /* 
    * scan input buffer for LF, CR, CR-LF shorts; scribe between newlines.
    * if last vchar is CR, set skipLF; skip one at startup 
    * if Unicode byte order mark in effect.
    */

   startshort = currentshort = inputBuffer + (skipOne ? 1 : 0);
   endshort = inputBuffer + inputLength;
   
   skipLF = trans->skipLF;
   copy = string;

   while (currentshort < endshort)
      {
	 ch = *currentshort;
	 if (ch == _xctransCR)
	    {
	       /*
		* emit previous substring followed by xcharEOL;
		* init next substring, set skipLF
		*/
	       scribe = (_xctransSizedScribeFrom[charset])
		  (startshort, currentshort - startshort);
	       
	       copy = vcharSizedCopyScribed(scribe, copy);
	       *copy++ = xcharEOL;
	       *lastEOL = copy;
	       
	       startshort = currentshort + 1;
	       skipLF = vTRUE;
	    }
	 else if (ch == _xctransLF)
	    {
	       /*
		* if skipLF is vTRUE, ignore LF, update next substring;
		* else, emit substring followed by xcharEOL, 
		* init next substring
		*/
	       if (!skipLF)
		  {

	       
		     scribe = (_xctransSizedScribeFrom[charset])
			(startshort, currentshort - startshort);
	       
		     copy = vcharSizedCopyScribed(scribe, copy);
		     *copy++ = xcharEOL;
		     *lastEOL = copy;
		     
		     startshort = currentshort + 1;
		     /* skipLF == vFALSE */
		  }
	       else
		  {
		     startshort = currentshort + 1;
		     skipLF = vFALSE;
		  }
	    }
	 else
	    {
	       /* other bytes */
	       skipLF = vFALSE;
	    }
	 
	 currentshort++;
      }

   /* 
    * exhausted input, only need to scribe if startshort < endshort
    */

   if (startshort < endshort)
      {
	 scribe = (_xctransSizedScribeFrom[charset])
	    (startshort, currentshort - startshort);
	       
	 copy = vcharSizedCopyScribed(scribe, copy);
		     
      }

   /*
    * extra byte at the end
    */
   if (remainByteCount > 0)
      {
	 *copy++ = vcharUNDEFINED;
      }
   
   /*
    * store the skipLF value in trans
    */

   trans->skipLF = skipLF;

   /* 
    * free the input buffer if dynamically allocated 
    */
   
   if (inputBuffer != firstBuffer)
      vmemFree(inputBuffer);
   
   return (copy);

} /* _xctransReadFromFileTwoByte */

/*
 * _xctransReadFromFileMultiByte:
 *
 * trans     -> the xctrans state
 * inputFile -> the file to read from
 * string    -> the vchar buffer where the input data is deposited
 * size      -> the maximum number of vchars to be demposited in string
 * lastEOL  <-> points past the last EOL character placed in string
 *
 * returns   <-  pointer past the last vchar placed in the string
 */

static vchar *_xctransReadFromFileMultiByte(xctrans *trans, 
					    vfsFile *inputFile,
					    vchar *string, 
					    size_t size, 
					    vchar **lastEOL)
{
   int            charset;
   vbool          endOfFile = vFALSE;
   vbyte          firstBuffer[xctransBUFFER_SIZE];
   vbyte          *inputBuffer;
   vchar          *current, *copy, *end;
   
   vscribe        *scribe;
   size_t         inputLength, normLength;
   int            adjustedLength;

   size_t         length;
   vchar          ch;
   vbyte          remainByteCount;            
   vbool          skipLF;           
   vbyte          *remainByteBuffer;   
   vchar          xcharEOL;           

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (inputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(string);

   remainByteCount = trans->remainByteCount;

   remainByteBuffer = trans->remainByteBuffer;
   
   charset = xctransGetCharset(trans);

   /* 
    * at most size bytes will be translated into at most size vchars;
    * allocate a bigger input buffer if nesessary 
    */

   if (size > xctransBUFFER_SIZE)
      inputBuffer = (vbyte *)vmemAlloc(size * sizeof(vbyte));
   else
      inputBuffer = firstBuffer;
    
   /* 
    * move the remaining bytes back into the input buffer 
    */
   (void)vmemMove(remainByteBuffer, inputBuffer, remainByteCount);

   /* 
    * adjust number of bytes to be read by remaining bytes already in 
    * the input buffer, and remaining vchar to be placed in the 
    * string buffer later; be conservative.
    */
   adjustedLength = vMAX(0, (int)((int)size - remainByteCount));
   
   /* 
    * don't overwrite the remaining bytes !! 
    */

   inputLength = vfsReadFile(inputBuffer + remainByteCount, sizeof(vbyte), 
			     (size_t) adjustedLength, 
			     inputFile)
      + remainByteCount;

   endOfFile = 
      (inputLength < adjustedLength + remainByteCount)? vTRUE : vFALSE;

   /* 
    * normalize length; move excess bytes in the remainByteBuffer
    */
   normLength = (_xctransSizedNormalize
		 [charset - _xctransCODESET_TWO_BYTE])
      (inputBuffer, inputLength);
   remainByteCount = trans->remainByteCount
      = inputLength - normLength;
   if (remainByteCount)
      (void)vmemMove(inputBuffer + normLength, remainByteBuffer, 
		     remainByteCount);

   /*
    * create the scribe fot the normalized length buffer
    */

   scribe = (_xctransSizedScribeFrom[charset])
      (inputBuffer, normLength);
	 
   /* 
    * compute length of string written out by the scribe
    */
   
   length = vcharLengthScribed(scribe);

   /*
    * scribe it.
    */
   (void) vcharSizedCopyScribed(scribe, string);
   
   /* 
    * scan string for LF, CR, CR-LF; replace with xcharEOL.
    * if final character is CR, set skipLF to vTRUE for next visit to file.
    */
   
   current = copy = string;
   end = current + length;
   
   xcharEOL = trans->EOL;
   skipLF = trans->skipLF;
   
   while (current < end)

      {
	 ch = *current;
	 if (ch == _xctransCR)
	    {
	       /*
		* emit xcharEOL; set skipLF
		*/
	       *copy++ = xcharEOL;
	       *lastEOL = copy;
	       skipLF = vTRUE;
	    }
	 else if (ch == _xctransLF)
	    {
	       /*
		* if skipLF is vTRUE, ignore LF, reset skipLF.
		* else, emit xcharEOL.
		*/
	       if (!skipLF)
		  {
		     *copy++ = xcharEOL;
		     *lastEOL = copy;
		     /* skipLF == vFALSE */
		  }
	       else
		  {
		     skipLF = vFALSE;
		  }
	    }
	 else
	    {
	       *copy++ = *current;
	       skipLF = vFALSE;
	    }
	 
	 current++;
      }

   if (endOfFile)
      {
	 while (remainByteCount-- > 0)
	    {
	       /* emit illegal bytes */
	       *copy++ = vcharUNDEFINED;
	    }
	 remainByteCount = trans->remainByteCount = 0;
      }
   
   /*
    * store the skipLF value in trans
    */

   trans->skipLF = skipLF;

   /* 
    * free the input buffer if dynamically allocated 
    */
   
   if (inputBuffer != firstBuffer)
      vmemFree(inputBuffer);
   
   return (copy);
   
} /* _xctransReadFromFileMultiByte */

/*****************************************************************************/

/*
 * _xctransWriteLineToFileSingleByte:
 *
 * trans     -> the xctrans object
 * outputFile-> the file to write to
 * string    -> the vchar buffer where the data is read from
 * size      -> the maximum number of valid vchars in the buffer;
 *              note that the actual number of vchars to write maybe 
 *              smaller (read up to xcharEOL).
 *
 * returns   <-  numbers of vchars actually scanned and exported.
 */

static int _xctransWriteLineToFileSingleByte(xctrans *trans, 
					     vfsFile *outputFile,
					     vchar *string, 
					     size_t size)

{
   vbyte           firstBuffer[xctransBUFFER_SIZE + 2];
   vbyte          *outputBuffer;
   int             numchars, allocated;

   int             charset;
   vchar          *start;
   vchar           xcharEOL;           

   vbyte          *copy;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (outputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(0);

   charset = xctransGetCharset(trans);
   xcharEOL = trans->EOL;

   numchars = 0;
   start = string;
   while ((numchars < size) 
	  && (*start != xcharEOL))
      {
	 start++;
	 numchars++;
      }

   /*
    * take the newline characters into account
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   allocated = numchars + 2;
#else
   allocated = numchars + 1;
#endif

   /*
    * enough space allocated for xctransBUFFER_SIZE vchars
    * plus two newline bytes; allocate buffer if more needed
    */

   if (allocated > (xctransBUFFER_SIZE + 2))
      outputBuffer = (vbyte *)vmemAlloc(allocated * sizeof(vbyte));
   else
      outputBuffer = firstBuffer;

	       
   copy = vcharExport((_xctransSizedScribeTo[charset])(string, numchars), 
		      outputBuffer);
   
   /*
    * add the newline characters
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   *copy++ = _xctransCR;
   *copy++ = _xctransLF;
#else
   *copy++ = (vbyte) vcharEOL;
#endif

   vfsWriteFile(outputBuffer, sizeof(vbyte), copy - outputBuffer, outputFile);

   /* 
    * free the output buffer if dynamically allocated 
    */
   
   if (outputBuffer != firstBuffer)
      vmemFree(outputBuffer);
   
   return (numchars);
   
} /* _xctransWriteLineToFileSingleByte */

/*
 * _xctransWriteLineToFileTwoByte:
 *
 * trans     -> the xctrans object
 * outputFile-> the file to write to
 * string    -> the vchar buffer where the data is read from
 * size      -> the maximum number of valid vchars in the buffer;
 *              note that the actual number of vchars to write maybe 
 *              smaller (read up to xcharEOL).
 *
 * returns   <-  numbers of vchars actually scanned and exported.
 */

static int _xctransWriteLineToFileTwoByte(xctrans *trans, 
					  vfsFile *outputFile,
					  vchar *string, 
					  size_t size)

{
   unsigned short  firstBuffer[xctransBUFFER_SIZE + 3];
   unsigned short *outputBuffer, *out;
   int             numchars, allocated;

   vbool           swapIt        = vFALSE;
   vbool           emitByteOrder = vFALSE;

   int             charset;
   int             byteOrder;
   vchar           xcharEOL;           
   vchar          *start;
   unsigned short *copy;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (outputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(0);

   charset = xctransGetCharset(trans);
   xcharEOL = trans->EOL;

   numchars = 0;
   start = string;
   while ((numchars < size) 
	  && (*start != xcharEOL))
      {
	 start++;
	 numchars++;
      }

   /*
    * take the newline characters into account
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   allocated = numchars + 2;
#else
   allocated = numchars + 1;
#endif

   /* 
    * byte swapping, leading byte order mark for Unicode
    */
   byteOrder = xctransGetByteOrder(trans);

   switch(byteOrder)
      {
       case xctransORDER_NO_INFO:
	 xctransNotifyString
	    (trans, xctransLEVEL_WARNING,
	     _xctransMessages[_xctransMSG_UNKNOWN_BYTE_ORDER]);

	 if (charset == xctransCODESET_UNICODE)
	    {
	       xctransNotifyString
		  (trans, xctransLEVEL_WARNING,
		   _xctransMessages[_xctransMSG_USING_IMPLICIT]);

	       xctransSetByteOrder(trans, xctransORDER_IMPLICIT);
	    }
	 else
	    {
	       xctransNotifyString
		  (trans, xctransLEVEL_WARNING,
		   _xctransMessages[_xctransMSG_USING_BIG_ENDIAN]);

	       xctransSetByteOrder(trans, xctransORDER_BIG_ENDIAN);
	    }
	 
	 /* fall through */
	 
       case xctransORDER_IMPLICIT:
	 /* 
	  * no swapping for tagged Unicode
	  * fall-through to BIG_ENDIAN for rest
	  */
	 
	 if (charset == xctransCODESET_UNICODE)
	    {
	       switch(_xctransGetImplicitFlip(trans))
		  {
		   case _xctransFLIP_NOT_CHECKED:
		     /*
		      * need to produce the byte order character 
		      */
		     _xctransSetImplicitFlip(trans, _xctransFLIP_SWAP);
		     emitByteOrder = vTRUE;
		     break;
			   
		   case _xctransFLIP_SWAP:
		     break;
		     
		   case _xctransFLIP_DONT_SWAP:
		     break;
		     
		   default:
		     vexGenerateModuleState();
		  }
	       break;
	    }
	 /*
	  * else fall through to BIG-ENDIAN
	  */
	 
       case xctransORDER_BIG_ENDIAN:	       
#if (vportLITTLE_ENDIAN_SHORT)
	 swapIt = vTRUE;
#endif
	 break;
	 
       case xctransORDER_LITTLE_ENDIAN:	       
#if (vportBIG_ENDIAN_SHORT)
	 swapIt = vTRUE;
#endif
	 break;
	 
       default:
	 vexGenerateModuleState();
      }

   /*
    * take the unicode byte order mark into account
    */

   if (emitByteOrder)
      allocated++;

   /*
    * enough space allocated for xctransBUFFER_SIZE vchars plus 
    * byte order mark plus two newline bytes; allocate buffer if more needed
    */

   if (allocated > (xctransBUFFER_SIZE + 3))
      outputBuffer = (unsigned short *)
	 vmemAlloc(allocated * sizeof(unsigned short));
   else
      outputBuffer = firstBuffer;

   out = outputBuffer;

   /*
    * emit the unicode byte order mark
    */

   if (emitByteOrder)
      {
	 *out++ = _xctransBYTE_ORDER_MARK;
      }
   copy = vcharExport((_xctransSizedScribeTo[charset])(string, numchars), 
		      out);
   
   /*
    * add the newline characters
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   *copy++ = _xctransCR;
   *copy++ = _xctransLF;
#else
   *copy++ = (unsigned short) vcharEOL;
#endif

   if (swapIt)
      {
	_xctransSwapBytes(outputBuffer, copy - outputBuffer); 
      }

   vfsWriteFile((vbyte *)outputBuffer, sizeof(unsigned short), 
		copy - outputBuffer, outputFile);

   /* 
    * free the output buffer if dynamically allocated 
    */
   
   if (outputBuffer != firstBuffer)
      vmemFree(outputBuffer);
   
   return (numchars);
   
} /* _xctransWriteLineToFileSingleByte */

/*
 * _xctransWriteLineToFileMultiByte:
 *
 * trans     -> the xctrans object
 * outputFile-> the file to write to
 * string    -> the vchar buffer where the data is read from
 * size      -> the maximum number of valid vchars in the buffer;
 *              note that the actual number of valid vchars maybe 
 *              smaller (read up to xcharEOL).
 *
 * returns   <-  numbers of vchars actually scanned and exported.
 */

static int _xctransWriteLineToFileMultiByte(xctrans *trans, 
					    vfsFile *outputFile,
					    vchar *string, 
					    size_t size)

{
   vbyte           firstBuffer[xctransBUFFER_SIZE + 2];
   vbyte          *outputBuffer;
   int             numchars, allocated;
   vscribe        *scribe;
   int             charset;
   vchar           xcharEOL;           
   vchar          *start;

   vbyte          *copy;

#if (vdebugDEBUG)
   if (string == NULL)
      vexGenerateArgNull();

   if (trans == NULL)
      vexGenerateArgNull();

   if (outputFile == NULL)
      vexGenerateArgNull();
#endif

   if (size == 0)
      return(0);

   charset = xctransGetCharset(trans);
   xcharEOL = trans->EOL;

   numchars = 0;
   start = string;
   while ((numchars < size) 
	  && (*start != xcharEOL))
      {
	 start++;
	 numchars++;
      }

   scribe = (_xctransSizedScribeTo[charset])(string, numchars);

   allocated = vscribeGetLength(scribe);

   /*
    * take the newline characters into account
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   allocated += 2;
#else
   allocated += 1;
#endif

   /*
    * enough space allocated for xctransBUFFER_SIZE + 2 bytes
    * plus two newline bytes; allocate buffer if more needed
    */

   if (allocated > (xctransBUFFER_SIZE + 2))
      outputBuffer = (vbyte *)vmemAlloc(allocated * sizeof(vbyte));
   else
      outputBuffer = firstBuffer;

	       
   copy = vcharExport(scribe, outputBuffer);
   
   /*
    * add the newline characters
    */

#if (vportWIN_MS_WINDOWS || vportWIN_PM)
   *copy++ = _xctransCR;
   *copy++ = _xctransLF;
#else
   *copy++ = (vbyte) vcharEOL;
#endif

   vfsWriteFile(outputBuffer, sizeof(vbyte), copy - outputBuffer, outputFile);

   /* 
    * free the output buffer if dynamically allocated 
    */
   
   if (outputBuffer != firstBuffer)
      vmemFree(outputBuffer);
   
   return (numchars);
   
} /* _xctransWriteLineToFileSingleByte */


/*
 *   sundry
 */

void xctransSetEOL(xctrans *trans, int xcharEOL)
{

#if (vdebugDEBUG)
   if (!trans)
      vexGenerateArgNull();
#endif

   trans->EOL = (vchar)xcharEOL;
   
} /* xctransSetEOL */


void xctransSetCharset(xctrans *trans, int charset)
{

#if (vdebugDEBUG)
   if (!trans)
      vexGenerateArgNull();

   if ((charset < xctransCODESET_NO_INFO) 
       || (charset >= _xctransCODESET_COUNT))
      vexGenerateArgRange();
#endif


   trans->charset = charset;
   
} /* xctransSetCharset */


void xctransSetByteOrder(xctrans *trans, int byteOrder)
{

#if (vdebugDEBUG)
   if (!trans)
      vexGenerateArgNull();

   if ((byteOrder < xctransORDER_NO_INFO) 
       || (byteOrder > xctransORDER_LITTLE_ENDIAN))
      vexGenerateArgRange();
#endif

   trans->byteOrder = byteOrder;
   
} /* xctransSetByteOrder */


/*
 * notify 
 */

void xctransSetVerbose(xctrans *trans, int level)
{

#if (vdebugDEBUG)
   if (!trans)
      vexGenerateArgNull();

   if ((level < xctransLEVEL_WARNING) 
       || (level > xctransLEVEL_INFO))
      vexGenerateArgRange();
#endif

   trans->verbose = level;
   
} /* xctransSetVerbose */


void xctransSetNotify(xctrans *trans, xctransNoteProc proc)
{

#if (vdebugDEBUG)
    if (!trans)
      vexGenerateArgNull();
#endif

    trans->noteProc = proc;

} /* xctransSetNotify */


void xctransNotify(xctrans *trans, int level, vscribe *msg)
{
   
#if (vdebugDEBUG)
   if (!trans || !msg)
      vexGenerateArgNull();
   
   if ((level < xctransLEVEL_WARNING) 
       || (level > xctransLEVEL_INFO))
      vexGenerateArgRange();
#endif
   
   if ((level <= trans->verbose) 
       && (trans->noteProc != NULL))
      (*trans->noteProc)(trans, level, msg);
   else
      vscribeDestroy(msg);
   
} /* xctransNotify */


void xctransNotifyFormat(xctrans *trans, int level,
			 const char *format, ...)
{
   va_list		 args;
   vscribe		*scribe;
   
#if (vdebugDEBUG)
   if (!trans || !format)
      vexGenerateArgNull();
   
   if ((level < xctransLEVEL_WARNING) 
       || (level > xctransLEVEL_INFO))
      vexGenerateArgRange();
#endif
   
   /*
    * process the args
    */
   va_start(args, format);
   scribe =
      vcharScribeFormatScribedVarargs(vcharScribeLiteral(format), args);
   va_end(args);
   
   /*
    * notify it
    */
   xctransNotify(trans, level, scribe);
   
} /* xctransNotifyFormat */


/* ----------------------------------------------------------------------------
 * initialization functions
 * ------------------------------------------------------------------------- */

#if (vmemBALANCE)

static void _xctransGlobalShutdown(void)
{
   ;
} /* _xctransGlobalShutdown */


static void _xctransClientShutdown(void)
{
   int                   lp;

   for (lp = 0; lp < _xctransMSG_COUNT; lp++)
      vstrDestroy(_xctransMessages[lp]);

} /* _xctransClientShutdown */

#endif


static void _xctransStartupGlobal(void)
{
    int			 lp;
    
    for (lp = xctransCODESET_NO_INFO ; lp < _xctransCODESET_COUNT ; 
	 lp++)
       _xctransPredefs[lp] =
	  vnameInternGlobalLiteral(_xctransPredefLiterals[lp]);

} /* _xctransStartupGlobal */


static void _xctransStartupClient(void)
{
    _xctransGlobals		*vars;
    xctransClass		*clas;
    vresource                    msgResource;
    int                          lp;

    vars = master();
    
    /*
     * set up for xctrans
     */
    
    clas =
      vclassSpawn(vinstanceGetDefaultClass(), sizeof(xctransClass));
    
    vclassSetNameScribed(clas, vcharScribeLiteral("xctrans"));
    vclassSetObjectSize(clas, sizeof(xctrans));
    
    vclassSet(clas, vinstanceINIT, _xctransInit);
    vclassSet(clas, vinstanceDESTROY, _xctransDestroy);
    vclassSet(clas, xctransREAD_FROM_FILE, _xctransReadFromFile);
    vclassSet(clas, xctransWRITE_LINE_TO_FILE, _xctransWriteLineToFile);
    
    vars->defaultClass = clas;
    
    /*
     * Get the string arrays 
     */

    msgResource = vresourceGet
       (vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
		     vnameInternGlobalLiteral("Xctrans")),
	vnameInternGlobalLiteral("Messages"));

    for (lp = 0; lp < _xctransMSG_COUNT; lp++)
       _xctransMessages[lp] = vresourceGetStringAt(msgResource, lp);

} /* _xctransStartupClient */


static void _xctransSetupGlobal(void)
{
   if (_xctransMaster == NULL) 
      {
	 _xctransMaster = vclientRegisterModule();
	 _xctransStartupGlobal();
#if (vmemBALANCE)
	 vclientRegisterGlobalShutdown(_xctransGlobalShutdown);
#endif
	 
      }
   
} /* _xctransSetupGlobal */

static void _xctransSetupGlobalAndClient(void)
{
   _xctransSetupGlobal();
   
   if (*_xctransMaster == NULL) 
      {
	 vclientAllocateModule(_xctransMaster, sizeof(_xctransGlobals));
	 _xctransStartupClient();
#if (vmemBALANCE)
	 vclientRegisterShutdown(_xctransClientShutdown);
#endif
      }

} /* _xctransSetupGlobalAndClient */

xctransClass *xctransGetDefaultClass(void)
{
    _xctransSetupGlobalAndClient();

    return master()->defaultClass;
    
} /* xctransGetDefaultClass */
