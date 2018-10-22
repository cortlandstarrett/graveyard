/* $Id: vchar.h,v 1.94 1997/09/17 19:17:16 dimitri Exp $ */

/******************************************
 * vchar.h
 * 
 * String buffer header file for String Manager
 *
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1992 Visix Software Inc.
 * All rights reserved.
 ******************************************/

#ifndef vcharINCLUDED
#define vcharINCLUDED 1

/*
 * Include any other files this header depends upon
 */

#ifndef   vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif
#ifndef  vstdargINCLUDED
#include vstdargHEADER
#endif
#ifndef  vctypeINCLUDED		/* for isalpha, isdigit, etc. */
#include vctypeHEADER
#endif
#ifndef  vstringINCLUDED	/* for strcpy, strcat, etc. */
#include vstringHEADER
#endif

/* Galaxy headers */

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif
#ifndef  vmemINCLUDED
#include vmemHEADER
#endif
#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

#if (vportVCHAR_CODESET == vportCODESET_ASCII)
typedef char		 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1)
typedef unsigned char	 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)
typedef unsigned char	 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS)
typedef unsigned char	 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)
typedef unsigned short	 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_MNLS)
typedef wchar_t		 vchar;
#elif (vportVCHAR_CODESET == vportCODESET_ISO_10646)
typedef unsigned long	 vchar;
#else
typedef _error _error;	/* (vportVCHAR_CODESET is unknown!) */
#endif

enum
{
  vcharFORMAT_SIGN_PREFIX 	= 0x01,
  vcharFORMAT_BLANK_PREFIX	= 0x02,
  vcharFORMAT_ALTERNATE_FORM	= 0x04,
  vcharFORMAT_LONG 		= 0x08
};

typedef vscribe *(*vcharFormatFunction)(int flags, int precision,
				       vchar **formatString, int stringLength, 
				       va_list *args);

#if (vportBAD_STDIO_CONST_CHAR_STAR)
#define vcharCLIB_STR_CONST /*empty*/
#else
#define vcharCLIB_STR_CONST const
#endif

/*
 * * * * * * * * * * * * * Exported constants * * * * * * * * * * * * * *
 */

#if !(vportBAD_WEAK_EXTERNS)
extern vportLINK const int		vcharBIT;
extern vportLINK const vchar		vcharMIN;
extern vportLINK const vchar		vcharMAX;

extern vportLINK const vchar		vcharNULL;
extern vportLINK const vchar		vcharEOL;

extern vportLINK const vchar		vcharUNDEFINED;
#endif

enum {
    vcharSET_ASCII,
    vcharSET_LATIN_1,
    vcharSET_MACINTOSH,
    vcharSET_WINDOWS,
    vcharSET_UNICODE,
    vcharSET_SJIS,
    vcharSET_JEUC,
    vcharSET_UTF,
    vcharSET_GREEK,
    vcharSET_CODEPAGE_437,
    vcharSET_CODEPAGE_850,
    vcharSET_KEUC,
    vcharSET_TEUC,
    vcharSET_CEUC,
    vcharSET_CODEPAGE_1250,
    vcharSET_CODEPAGE_1251,
    vcharSET_CODEPAGE_1253,
    vcharSET_CODEPAGE_1254,
    vcharSET_CODEPAGE_1255,
    vcharSET_CODEPAGE_1256,
    vcharSET_CODEPAGE_1257,

    vcharSET_CODEPAGE_1252 = vcharSET_WINDOWS
};

/*
 * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * *
 */

/******************************
 * Single character functions:
 ******************************/

vbool vcharIsAlphaNumeric(
    int /*vchar*/   	    	character
    );

vbool vcharIsAlphabetic(
    int /*vchar*/   	    	character
    );

vbool vcharIsBlank(
    int /* vchar */              character
    );

vbool vcharIsControl(
    int /*vchar*/   	    	character
    );

vbool vcharIsDecimal(
    int /*vchar*/   	    	character
    );

vbool vcharIsDigit(
    int /*vchar*/   	    	character
    );

vbool vcharIsGraphic(
    int /*vchar*/   	    	character
    );

vbool vcharIsHexDigit(
    int /*vchar*/   	    	character
    );

vbool vcharIsLowerCase(
    int /*vchar*/   	    	character
    );

vbool vcharIsNonSpacing(
    int /* vchar */              character
    );

vbool vcharIsNumeric(
    int /* vchar */              character
    );

vbool vcharIsPrintable(
    int /*vchar*/   	    	character
    );

vbool vcharIsPunctuation(
    int /*vchar*/   	    	character
    );

vbool vcharIsSpacing(
    int /*vchar*/   	    	character
    );

vbool vcharIsUpperCase(
    int /*vchar*/   	    	character
    );

vbool vcharIsWhiteSpace(
    int /*vchar*/   	    	character
    );

vchar vcharToLowerCase(
    int /*vchar*/   	    	character
    );

vchar vcharToUpperCase(
    int /*vchar*/   	    	character
    );

vchar vcharStripDiacritics(
    int /*vchar*/   	    	character
    );

size_t vcharToUpperCaseLength(
    int /* vchar */             character
    );

size_t vcharToUpperCaseBuffer(
    int /* vchar */             character, 
    vchar                      *buffer
    );

size_t vcharToUpperCaseBufferBounded(
    int /* vchar */             character, 
    vchar                      *buffer,
    size_t                      maxDestLength
    );


/* converters from */

vchar vcharFromLiteral(
    int     	    	    	character
    );

vchar vcharFromSystem(
    int     	    	    	character
    );

vchar vcharFromASCII(
    int     	    	    	character
    );

vchar vcharFromLatin1(
    int     	    	    	character
    );

vchar vcharFromMacintosh(
    int     	    	    	character
    );

vchar vcharFromWindows(
    int     	    	    	character
    );

vchar vcharFromUnicode(
    int     	    	    	character
    );

/* converters to */

char vcharToASCII(
    int     	    	    	character
    );

unsigned char vcharToLatin1(
    int     	    	    	character
    );

unsigned char vcharToMacintosh(
    int     	    	    	character
    );

unsigned char vcharToWindows(
    int     	    	    	character
    );

unsigned short vcharToUnicode(
    int     	    	    	character
    );

/* converters for other encodings , 8-bit */

/* from */

vchar vcharFromLatin2(
    int /* unsigned char */      character
    );

vchar vcharFromLatin3(
    int /* unsigned char */      character
    );

vchar vcharFromLatin4(
    int /* unsigned char */      character
    );

vchar vcharFromLatin5(
    int /* unsigned char */      character
    );

vchar vcharFromGreek(
    int /* unsigned char */      character
    );

vchar vcharFromHebrew(
    int /* unsigned char */      character
    );

vchar vcharFromCyrillic(
    int /* unsigned char */      character
    );

vchar vcharFromKoi8(
    int /* unsigned char */      character
    );

vchar vcharFromViscii(
    int /* unsigned char */      character
    );

vchar vcharFromAdobeSymbol(
    int /* unsigned char */      character
    );

vchar vcharFromAdobeStdEnc(
    int /* unsigned char */      character
    );

vchar vcharFromDecTech(
    int /* unsigned char */      character
    );

vchar vcharFromJISX0201(
    int /* unsigned char */     character
    );

/* to */

unsigned char vcharToLatin2(
    int /* vchar */              character
    );

unsigned char vcharToLatin3(
    int /* vchar */              character
    );

unsigned char vcharToLatin4(
    int /* vchar */              character
    );

unsigned char vcharToLatin5(
    int /* vchar */              character
    );

unsigned char vcharToGreek(
    int /* vchar */              character
    );

unsigned char vcharToHebrew(
    int /* vchar */              character
    );

unsigned char vcharToCyrillic(
    int /* vchar */              character
    );

unsigned char vcharToKoi8(
    int /* vchar */              character
    );

unsigned char vcharToViscii(
    int /* vchar */              character
    );

unsigned char vcharToAdobeSymbol(
    int /* vchar */              character
    );

unsigned char vcharToAdobeStdEnc(
    int /* vchar */              character
    );

unsigned char vcharToDecTech(
    int /* vchar */              character
    );

unsigned char vcharToJISX0201(
    int /* vchar */              character
    );

/* converters for other encodings , 16-bit, multi-byte */

/* from */

vchar vcharFromJISX0208_83(
    int /* unsigned short */     character
    );

vchar vcharFromJISX0212(
    int /* unsigned short */     character
    );

vchar vcharFromKSC5601(
    int /* unsigned short */     character
    );

vchar vcharFromGB2312(
    int /* unsigned short */     character
    );

vchar vcharFromBig5hku(
    int /* unsigned short */     character
    );

vchar vcharFromCNS11643(
    int /* unsigned int */     character
    );

vchar vcharFromJEUC(
    int                          character
    );

vchar vcharFromKEUC(
    int                          character
    );

vchar vcharFromSJIS(
    int                          character
    );

vchar vcharFromCEUC(
    int                          character
    );

vchar vcharFromTEUC(
    int                          character
    );

/* to */

unsigned short vcharToJISX0208_83(
    int /* vchar */              character
    );

unsigned short vcharToJISX0212(
    int /* vchar */              character
    );

unsigned short vcharToKSC5601(
    int /* vchar */              character
    );

unsigned short vcharToGB2312(
    int /* vchar */              character
    );

unsigned short vcharToBig5hku(
    int /* vchar */              character
    );

unsigned int vcharToCNS11643(
    int /* vchar */              character
    );

int vcharToJEUC(
    int /* vchar */              character
    );

int vcharToKEUC(
    int /* vchar */              character
    );

int vcharToSJIS(
    int /* vchar */              character
    );

int vcharToCEUC(
    int /* vchar */              character
    );

int vcharToTEUC(
    int /* vchar */              character
    );

/***********************************
 * Static character buffer functions:
 ************************************/

const vchar *vcharGetEmptyString(
    void
    );

/*
 * Copy/Append functions:
 */

void vcharCopyFast(
    const vchar     	    	*source, 
    vchar   	    	    	*dest
    );

void vcharSizedCopyFast(
    const vchar     	    	*source, 
    size_t  	    	    	sourceLength, 
    vchar   	    	    	*dest
    );

vchar *vcharCopy(
    const vchar     	    	*source, 
    vchar   	    	    	*dest
    );

vchar *vcharCopyBounded(
    const vchar     	    	*source,
    vchar   	    	    	*dest, 
    size_t  	    	    	maxDestLength
    );

vchar *vcharSizedCopy(
    const vchar     	    	*source,
    size_t  	    	    	sourceLength,
    vchar   	    	    	*dest
    );

vchar *vcharSizedCopyBounded(
    const vchar     	    	*source,
    size_t  	    	    	sourceLength, 
    vchar   	    	    	*dest,
    size_t  	    	    	maxDestLength
    );

vchar *vcharCopyScribed(
    vscribe 	    	    	*s,
    vchar   	    	    	*dest
    ); 

vchar *vcharCopyScribedBounded(
    vscribe 	    	    	*s,
    vchar   	    	    	*dest, 
    size_t  	    	    	maxDestLength
    );

vchar *vcharSizedCopyScribed(
    vscribe 	    	    	*s,
    vchar   	    	    	*dest
    ); 

vchar *vcharSizedCopyScribedBounded(
    vscribe 	    	    	*s,
    vchar   	    	    	*dest, 
    size_t  	    	    	maxDestLength
    );

vchar *vcharCopyFromLiteral(
    const char 	    	    	*source,
    vchar   	    	    	*dest
    );

vchar *vcharCopyFromSystem(
    const void 	    	    	*source,
    vchar   	    	    	*dest
    );

void vcharAppendFast(
    vchar   	    	    	*buffer,
    const vchar     	    	*appendString
    );

vchar *vcharAppend(
    vchar   	    	    	*buffer,
    const vchar     	    	*appendString
    );

vchar *vcharAppendBounded(
    vchar   	    	    	*buffer,
    size_t  	    	    	maxLength,
    const vchar     	    	*appendString
    );

vchar *vcharAppendScribed(
    vchar   	    	    	*buffer,
    vscribe 	    	    	*appendString
    );

vchar *vcharAppendScribedBounded(
    vchar   	    	    	*buffer,
    size_t  	    	    	maxLength,
    vscribe 	    	    	*appendString
    );

vchar *vcharAppendFromLiteral(
    vchar   	    	    	*buffer,
    const char 	    	    	*appendString
    );

vchar *vcharAppendFromSystem(
    vchar   	    	    	*buffer,
    const void 	    	    	*appendString
    );

size_t vcharLength(
    const vchar     	    	*string
    );

size_t vcharLengthBounded(
    const vchar     	    	*string,
    size_t  	    	    	maxLength
    );

size_t vcharLengthScribed(
    const vscribe   	    	*scribe
    );

size_t vcharLengthScribedBounded(
    const vscribe   	    	*scribe,
    size_t  	    	    	maxLength
    );

/*
 * Format functions:
 */

void vcharRegisterFormatFunction(
    int /* vchar */		letter,
    vcharFormatFunction		function
    );

vscribe *vcharScribeFormat(
    vchar 			*formatString,
    ...
    );

vscribe *vcharSizedScribeFormat(
    vchar 			*formatString,
    size_t			length,
    ...
    );

vscribe *vcharScribeFormatScribed(
    vscribe 			*formatScribe,
    ...
    );

vscribe *vcharScribeFormatLiteral(
    const char 			*formatString,
    ...
    );

vscribe *vcharScribeFormatVarargs(
    vchar 			*formatString,
    va_list			args
    );

vscribe *vcharSizedScribeFormatVarargs(
    vchar 			*formatString,
    size_t			length,
    va_list			args
    );

vscribe *vcharScribeFormatScribedVarargs(
    vscribe 			*formatScribe,
    va_list			args
    );

void *vcharCopyF(
    vchar			*dest,
    const char			*formatString,
    ...
    );

vscribe *vcharScribeF(
    const char			*formatString,
    ...
    );

void vcharDumpF(
    FILE			*stream,
    const char			*formatString,
    ...
    );


/*
 * Compare functions:
 */

int vcharCompare(
    const vchar     	    	*string1,
    const vchar     	    	*string2
    );
int vcharSizedCompare(
    const vchar     	    	*string1,
    const vchar     	    	*string2, 
    size_t  	    	    	length
    );
int vcharCompareBounded(
    const vchar     	    	*string1,
    const vchar     	    	*string2, 
    size_t  	    	    	maxLength
    );

int vcharCompareBase(
    const vchar     	    	*string1,
    const vchar     	    	*string2
    );

int vcharSizedCompareBase(
    const vchar     	    	*string1,
    const vchar     	    	*string2, 
    size_t  	    	    	length
    );

int vcharCompareBaseBounded(
    const vchar     	    	*string1,
    const vchar     	    	*string2, 
    size_t  	    	    	maxLength
    );

/*
 * Search functions:
 */

vchar *vcharSearch(
    const vchar     	    	*string,
    const vchar     	    	*substring
    );

vchar *vcharSizedSearch(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    const vchar     	    	*substring,
    size_t  	    	    	substringLength
    );

vchar *vcharSearchBackwards(
    const vchar     	    	*string,
    const vchar     	    	*substring
    );

vchar *vcharSizedSearchBackwards(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    const vchar     	    	*substring,
    size_t  	    	    	substringLength
    );

vchar *vcharSearchOneOf(
    const vchar     	    	*string,
    const vchar     	    	*characters
    );

vchar *vcharSizedSearchOneOf(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    const vchar     	    	*characters,
    size_t  	    	    	charLength
    );

vchar *vcharSearchOneOfBackwards(
    const vchar     	    	*string,
    const vchar     	    	*characters
    );

vchar *vcharSizedSearchOneOfBackwards(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    const vchar     	    	*characters, 
    size_t  	    	    	charLength
    );

vchar *vcharSearchNotOneOf(
    const vchar     	    	*string,
    const vchar     	    	*characters
    );

vchar *vcharSizedSearchNotOneOf(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    const vchar     	    	*characters,
    size_t  	    	    	charLength
    );

vchar *vcharSearchNotOneOfBackwards(
    const vchar     	    	*string, 
    const vchar     	    	*characters
    );

vchar *vcharSizedSearchNotOneOfBackwards(
    const vchar     	    	*string, 
    size_t  	    	    	stringLength, 
    const vchar     	    	*characters, 
    size_t  	    	    	charLength
    );

vchar *vcharSearchChar(
    const vchar     	    	*string,
    int /*vchar*/   	    	character
    );

vchar *vcharSizedSearchChar(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    int /*vchar*/   	    	character
    );

vchar *vcharSearchCharBackwards(
    const vchar     	    	*string,
    int /*vchar*/   	    	character
    );

vchar *vcharSizedSearchCharBackwards(
    const vchar     	    	*string,
    size_t  	    	    	stringLength, 
    int /*vchar*/   	    	character
    );

/*
 * Miscellaneous:
 */

vchar *vcharGetFirstToken(
    vchar   	    	    	*string,
    const vchar     	    	*separators
    );

vchar *vcharGetNextToken(
    const vchar     	    	*separators
    );

/*
 * Dumping:
 */

void vcharDump(
    const vchar     	    	*string,
    FILE    	    	    	*stream
    );

void vcharSizedDump(
    const vchar     	    	*string,
    size_t  	    	    	length,
    FILE    	    	    	*stream
    );

void vcharDumpScribed(
    vscribe 	    	    	*scribe,
    FILE    	    	    	*stream
    );

/*
 *  System Charset
 */

void vcharSetSystemCharacterSet(
    int     	    	    	characterSet
    );

int vcharGetSystemCharacterSet(
    void
    );

/*
 *  Normalize calls for multibyte system charsets
 */

size_t vcharSizedNormalizeSystem(
    const void 	    	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeSJIS(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeJEUC(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeKEUC(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeUTF(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeCEUC(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

size_t vcharSizedNormalizeTEUC(
    const unsigned char	    	*string,
    size_t  	    	    	length
    );

/*
 * Basic scribes:
 */

vscribe *vcharScribe(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribe(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeShared(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeShared(
    const vchar     	    	*string,
    size_t			length
    );

/*
 * Import to vchar scribes:
 */

vscribe *vcharScribeLiteral(
    const char 	    	    	*string
    );

vscribe *vcharSizedScribeLiteral(
    const char 	    	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeSystem(
    const void 	    	    	*string
    );

vscribe *vcharScribeSystemShared(
    const void 	    	    	*string
    );
		
vscribe *vcharSizedScribeSystem(
    const void 	    	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeSystemShared(
    const void 	    	    	*string,
    size_t			length
    );
		
vscribe *vcharScribeASCII(
    const char 	    	    	*string
    );

vscribe *vcharScribeASCIIShared(
    const char 	    	    	*string
    );

vscribe *vcharSizedScribeASCII(
    const char 	    	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeASCIIShared(
    const char 	    	    	*string,
    size_t			length
    );

vscribe *vcharScribeLatin1(
    const unsigned char     	*string
    );

vscribe *vcharScribeLatin1Shared(
    const unsigned char     	*string
    );

vscribe *vcharSizedScribeLatin1(
    const unsigned char     	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeLatin1Shared(
    const unsigned char     	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeMacintosh(
    const unsigned char    	*string
    );

vscribe *vcharScribeMacintoshShared(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeMacintosh(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeMacintoshShared(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeWindows(
    const unsigned char    	*string
    );

vscribe *vcharScribeWindowsShared(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeWindows(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeWindowsShared(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeUnicode(
    const unsigned short    	*string
    );

vscribe *vcharScribeUnicodeShared(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeUnicode(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharSizedScribeUnicodeShared(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *vcharScribeSJIS(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeSJIS(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJEUC(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeJEUC(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKEUC(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeKEUC(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeUTF(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeUTF(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCEUC(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeCEUC(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeTEUC(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeTEUC(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

/* scribes for other encodings */

/* 8-bit */

vscribe *vcharScribeLatin2(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeLatin2(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin3(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeLatin3(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin4(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeLatin4(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin5(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeLatin5(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeGreek(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeGreek(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeHebrew(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeHebrew(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCyrillic(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeCyrillic(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKoi8(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeKoi8(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeViscii(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeViscii(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeAdobeSymbol(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeAdobeSymbol(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeAdobeStdEnc(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeAdobeStdEnc(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeDecTech(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeDecTech(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJISX0201(
    const unsigned char    	*string
    );

vscribe *vcharSizedScribeJISX0201(
    const unsigned char    	*string,
    size_t  	    	    	length
    );

/* 16-bit */

vscribe *vcharScribeJISX0208_83(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeJISX0208_83(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJISX0212(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeJISX0212(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKSC5601(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeKSC5601(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeGB2312(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeGB2312(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeBig5hku(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeBig5hku(
    const unsigned short    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCNS11643(
    const unsigned short    	*string
    );

vscribe *vcharSizedScribeCNS11643(
    const unsigned short    	*string,
    size_t  	    	    	length
    );


/*
 * Replace scribes:
 */

vscribe *vcharScribeReplace(
    const vchar     	    	*string, 
    const vchar     	    	*match,
    const vchar     	    	*replace
    );

vscribe *vcharSizedScribeReplace(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    const vchar     	    	*replace,
    size_t  	    	    	replaceLength
    );

vscribe *vcharScribeReplaceChar(
    const vchar     	    	*string,
    int /*vchar*/   	    	match,
    int /*vchar*/   	    	replace
    );

vscribe *vcharSizedScribeReplaceChar(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    int /*vchar*/   	    	match, 
    int /*vchar*/   	    	replace
    );

vscribe *vcharScribeReplaceOneOf(
    const vchar     	    	*string, 
    const vchar     	    	*match,
    int /*vchar*/   	    	replace
    );

vscribe *vcharSizedScribeReplaceOneOf(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    int /*vchar*/   	    	replace
    );

vscribe *vcharScribeReplaceNotOneOf(
    const vchar     	    	*string, 
    const vchar     	    	*match,
    int /*vchar*/   	    	replace
    );

vscribe *vcharSizedScribeReplaceNotOneOf(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    int /*vchar*/   	    	replace
    );

vscribe *vcharScribeReplaceMap(
    const vchar     	    	*string,
    const vchar     	    	*match,
    const vchar     	    	*replace
    );

vscribe *vcharSizedScribeReplaceMap(
    const vchar     	    	*string,
    size_t  	    	    	length, 
    const vchar     	    	*match,
    const vchar     	    	*replace, 
    size_t  	    	    	matchLength
    );

/*
 * Misc. scribes:
 */

vscribe *vcharScribeToUpperCase(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeToUpperCase(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeToLowerCase(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeToLowerCase(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeStripDiacritics(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeStripDiacritics(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeStripToLowerCase(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeStripToLowerCase(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCharacter(
    int /*vchar*/   	    	character
    );

vscribe *vcharScribePadding(
    int /*vchar*/   	    	character,
    size_t			repeatCount	
    );

/*
 * Export functions:
 */

void *vcharExport(
    vscribe 	    	    	*s,
    void    	    	    	*dest
    );

void *vcharExportBounded(
    vscribe 	    	    	*s,
    void    	    	    	*dest,
    size_t  	    	    	maxLength
    );

size_t vcharGetExportLength(
    vscribe 	    	    	*s
    );

size_t vcharGetExportLengthBounded(
    vscribe 	    	    	*s,
    size_t  	    	    	maxLength
    );

void *vcharExportAlloc(
    vscribe 	    	    	*exportScribe
    );

void vcharExportFree(
    void    	    	    	*exportMemory
    );

/*
 * Export from vchar scribes:
 */

vscribe *vcharScribeSystemExport(
    const vchar     	    	*string
    );		

vscribe *vcharSizedScribeSystemExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeASCIIExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeASCIIExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin1Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeLatin1Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeMacintoshExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeMacintoshExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeWindowsExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeWindowsExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeUnicodeExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeUnicodeExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *vcharScribeSJISExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeSJISExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJEUCExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeJEUCExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKEUCExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeKEUCExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeUTFExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeUTFExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCEUCExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeCEUCExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeTEUCExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeTEUCExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

/* export scribes for other encodings */

/* 8-bit */

vscribe *vcharScribeLatin2Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeLatin2Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin3Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeLatin3Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin4Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeLatin4Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeLatin5Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeLatin5Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeGreekExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeGreekExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeHebrewExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeHebrewExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCyrillicExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeCyrillicExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKoi8Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeKoi8Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeVisciiExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeVisciiExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeAdobeSymbolExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeAdobeSymbolExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeAdobeStdEncExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeAdobeStdEncExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeDecTechExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeDecTechExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJISX0201Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeJISX0201Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

/* 16-bit */

vscribe *vcharScribeJISX0208_83Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeJISX0208_83Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeJISX0212Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeJISX0212Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeKSC5601Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeKSC5601Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeGB2312Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeGB2312Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeBig5hkuExport(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeBig5hkuExport(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

vscribe *vcharScribeCNS11643Export(
    const vchar     	    	*string
    );

vscribe *vcharSizedScribeCNS11643Export(
    const vchar     	    	*string,
    size_t  	    	    	length
    );

/*
 * Common functions for building scribes:
 */

void *vcharScribbleCopy(
    vscribe 	    	    	*scribe,
    void    	    	    	*dest,
    size_t  	    	    	maxDestLength
    );

void *vcharSizedScribbleCopy(
    vscribe 	    	    	*scribe,
    void    	    	    	*dest, 
    size_t  	    	    	maxDestLength
    );

size_t vcharGetScribbledLengthSame(
    vscribe 	    	    	*scribe,
    size_t  	    	    	maxDestLength
    );

size_t vcharSizedGetScribbledLengthSame(
    vscribe 	    	    	*scribe,
    size_t  	    	    	maxDestLength
    );

/*
 * Debugging versions of create functions -- for tracing memory leaks
 */

#if vdebugDEBUG

vscribe *vcharScribeDebug(
    const vchar     	    	*string, 
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeSharedDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSharedDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLiteralDebug(
    const char 	    	    	*literal,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLiteralDebug(
    const char 	    	    	*literal,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeSystemDebug(
    const void 	    	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeSystemSharedDebug(
    const void 	    	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSystemDebug(
    const void 	    	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSystemSharedDebug(
    const void 	    	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeASCIIDebug(
    const char 	    	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeASCIISharedDebug(
    const char 	    	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeASCIIDebug(
    const char 	    	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeASCIISharedDebug(
    const char 	    	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin1Debug(
    const unsigned char     	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin1SharedDebug(
    const unsigned char     	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin1Debug(
    const unsigned char     	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin1SharedDebug(
    const unsigned char     	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeMacintoshDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeMacintoshSharedDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeMacintoshDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeMacintoshSharedDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeWindowsDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeWindowsSharedDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeWindowsDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeWindowsSharedDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeUnicodeDebug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeUnicodeSharedDebug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeUnicodeDebug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeUnicodeSharedDebug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *vcharScribeSJISDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSJISDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeJEUCDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJEUCDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeKEUCDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKEUCDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeUTFDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeUTFDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeCEUCDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCEUCDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeTEUCDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeTEUCDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );


vscribe *vcharScribeReplaceDebug(
    const vchar     	    	*string,
    const vchar     	    	*match,
    const vchar     	    	*replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeReplaceDebug(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    const vchar     	    	*replace,
    size_t  	    	    	replaceLength,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeReplaceCharDebug(
    const vchar     	    	*string,
    int /*vchar*/   	    	match,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeReplaceCharDebug(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    int /*vchar*/   	    	match,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeReplaceOneOfDebug(
    const vchar     	    	*string,
    const vchar     	    	*match,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeReplaceOneOfDebug(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeReplaceNotOneOfDebug(
    const vchar     	    	*string,
    const vchar     	    	*match,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeReplaceNotOneOfDebug(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    const vchar     	    	*match,
    size_t  	    	    	matchLength,
    int /*vchar*/   	    	replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeReplaceMapDebug(
    const vchar     	    	*string,
    const vchar     	    	*match,
    const vchar     	    	*replace,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeReplaceMapDebug(
    const vchar     	    	*string,
    size_t  	    	    	stringLength,
    const vchar     	    	*match,
    const vchar     	    	*replace,
    size_t  	    	    	matchLength,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeToUpperCaseDebug(
    const vchar *string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );
vscribe *vcharSizedScribeToUpperCaseDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeToLowerCaseDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeToLowerCaseDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeStripDiacriticsDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeStripDiacriticsDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeStripToLowerCaseDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeStripToLowerCaseDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCharacterDebug(
    int /*vchar*/   	    	character,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribePaddingDebug(
    int /*vchar*/   	    	character,
    size_t	   	    	repeatCount,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

/* export scribes */

void *vcharExportAllocDebug(
    vscribe 	    	    	*s,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeSystemExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSystemExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeASCIIExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeASCIIExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin1ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin1ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeMacintoshExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );
vscribe *vcharSizedScribeMacintoshExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeWindowsExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );
vscribe *vcharSizedScribeWindowsExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeUnicodeExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );
vscribe *vcharSizedScribeUnicodeExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *vcharScribeSJISExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeSJISExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJEUCExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJEUCExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeKEUCExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKEUCExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeUTFExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeUTFExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCEUCExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCEUCExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeTEUCExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeTEUCExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

/* other encodings */

/* 8-bit */

vscribe *vcharScribeLatin2Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin2Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin2ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin2ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin3Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin3Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin3ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin3ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin4Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin4Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin4ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin4ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin5Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin5Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeLatin5ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeLatin5ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeGreekDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeGreekDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeGreekExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeGreekExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeHebrewDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeHebrewDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeHebrewExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeHebrewExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCyrillicDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCyrillicDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCyrillicExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCyrillicExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeKoi8Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKoi8Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeKoi8ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKoi8ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeVisciiDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeVisciiDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeVisciiExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeVisciiExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeAdobeSymbolDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeAdobeSymbolDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeAdobeSymbolExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeAdobeSymbolExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeAdobeStdEncDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeAdobeStdEncDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeAdobeStdEncExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeAdobeStdEncExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeDecTechDebug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeDecTechDebug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeDecTechExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeDecTechExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJISX0201Debug(
    const unsigned char    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0201Debug(
    const unsigned char    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJISX0201ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0201ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

/* 16-bit */

vscribe *vcharScribeJISX0208_83Debug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0208_83Debug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJISX0208_83ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0208_83ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJISX0212Debug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0212Debug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeJISX0212ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeJISX0212ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeKSC5601Debug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKSC5601Debug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeKSC5601ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeKSC5601ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeGB2312Debug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeGB2312Debug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeGB2312ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeGB2312ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeBig5hkuDebug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeBig5hkuDebug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeBig5hkuExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeBig5hkuExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCNS11643Debug(
    const unsigned short    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCNS11643Debug(
    const unsigned short    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharScribeCNS11643ExportDebug(
    const vchar     	    	*string,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

vscribe *vcharSizedScribeCNS11643ExportDebug(
    const vchar     	    	*string,
    size_t  	    	    	length,
    const char 	    	    	*tag,
    const char 	    	    	*file,
    int     	    	    	line
    );

#endif /* vdebugDEBUG */

/*
 * * * * * * * * * * * Privately Exported Prototypes * * * * * * * * * * * * *
 */

unsigned char _vcharASCIIToLatin1(int /* char */ c);
char _vcharLatin1ToASCII(int /* unsigned char */ c);

unsigned char _vcharASCIIToMacintosh(int /* char */ c);
char _vcharMacintoshToASCII(int /* unsigned char */ c);

unsigned char _vcharASCIIToWindows(int /* char */ c);
char _vcharWindowsToASCII(int /* unsigned char */ c);

unsigned short _vcharASCIIToUnicode(int /* char */ c);
char _vcharUnicodeToASCII(int /* unsigned short */ c);

unsigned char _vcharLatin1ToMacintosh(int /* unsigned char */ c);
unsigned char _vcharMacintoshToLatin1(int /* unsigned char */ c);

unsigned char _vcharLatin1ToWindows(int /* unsigned char */ c);
unsigned char _vcharWindowsToLatin1(int /* unsigned char */ c);

unsigned short _vcharLatin1ToUnicode(int /* unsigned char */ c);
unsigned char _vcharUnicodeToLatin1(int /* unsigned short */ c);

unsigned char _vcharMacintoshToWindows(int /* unsigned char */ c);
unsigned char _vcharWindowsToMacintosh(int /* unsigned char */ c);

unsigned short _vcharMacintoshToUnicode(int /* unsigned char */ c);
unsigned char _vcharUnicodeToMacintosh(int /* unsigned short */ c);

unsigned short _vcharWindowsToUnicode(int /* unsigned char */ c);
unsigned char _vcharUnicodeToWindows(int /* unsigned short */ c);

unsigned short _vcharCodepage437ToUnicode(int /* unsigned char */ c);
unsigned char _vcharUnicodeToCodepage437(int /* unsigned short */ c);

unsigned short _vcharCodepage850ToUnicode(int /* unsigned char */ c);
unsigned char _vcharUnicodeToCodepage850(int /* unsigned short */ c);

#if (vportVCHAR_CODESET == vportCODESET_UNICODE)
vbool _vcharIsSymbol(int /* vchar */ c);
#endif

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

unsigned char _vcharASCIIToLAT8(int /* char */ c);
char _vcharLAT8ToASCII(int /* unsigned char */ c);

#endif /* vportVCHAR_CODESET */

/* scribes */

vscribe *_vcharScribeASCIIToLatin1(const char *string);
vscribe *_vcharSizedScribeASCIIToLatin1(const char *string, size_t length);

vscribe *_vcharScribeLatin1ToASCII(const unsigned char *string);
vscribe *_vcharSizedScribeLatin1ToASCII(const unsigned char *string, 
					size_t length);

vscribe *_vcharScribeASCIIToMacintosh(const char *string);
vscribe *_vcharSizedScribeASCIIToMacintosh(const char *string, size_t length);

vscribe *_vcharScribeMacintoshToASCII(const unsigned char *string);
vscribe *_vcharSizedScribeMacintoshToASCII(const unsigned char *string,
					   size_t length);

vscribe *_vcharScribeASCIIToWindows(const char *string);
vscribe *_vcharSizedScribeASCIIToWindows(const char *string, size_t length);

vscribe *_vcharScribeWindowsToASCII(const unsigned char *string);
vscribe *_vcharSizedScribeWindowsToASCII(const unsigned char *string,
					   size_t length);

vscribe *_vcharScribeASCIIToUnicode(const char *string);
vscribe *_vcharSizedScribeASCIIToUnicode(const char *string, size_t length);

vscribe *_vcharScribeUnicodeToASCII(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToASCII(const unsigned short *string, 
					 size_t length);

vscribe *_vcharScribeLatin1ToMacintosh(const unsigned char *string);
vscribe *_vcharSizedScribeLatin1ToMacintosh(const unsigned char *string, 
					    size_t length);

vscribe *_vcharScribeMacintoshToLatin1(const unsigned char *string);
vscribe *_vcharSizedScribeMacintoshToLatin1(const unsigned char *string,
					    size_t length);

vscribe *_vcharScribeLatin1ToWindows(const unsigned char *string);
vscribe *_vcharSizedScribeLatin1ToWindows(const unsigned char *string, 
					    size_t length);

vscribe *_vcharScribeWindowsToLatin1(const unsigned char *string);
vscribe *_vcharSizedScribeWindowsToLatin1(const unsigned char *string,
					    size_t length);

vscribe *_vcharScribeLatin1ToUnicode(const unsigned char *string);
vscribe *_vcharSizedScribeLatin1ToUnicode(const unsigned char *string, 
					  size_t length);

vscribe *_vcharScribeUnicodeToLatin1(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToLatin1(const unsigned short *string, 
					  size_t length);

vscribe *_vcharScribeMacintoshToWindows(const unsigned char *string);
vscribe *_vcharSizedScribeMacintoshToWindows(const unsigned char *string, 
					    size_t length);

vscribe *_vcharScribeWindowsToMacintosh(const unsigned char *string);
vscribe *_vcharSizedScribeWindowsToMacintosh(const unsigned char *string,
					    size_t length);

vscribe *_vcharScribeMacintoshToUnicode(const unsigned char *string);
vscribe *_vcharSizedScribeMacintoshToUnicode(const unsigned char *string, 
					     size_t length);

vscribe *_vcharScribeUnicodeToMacintosh(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToMacintosh(const unsigned short *string,
					     size_t length);

vscribe *_vcharScribeWindowsToUnicode(const unsigned char *string);
vscribe *_vcharSizedScribeWindowsToUnicode(const unsigned char *string, 
					     size_t length);

vscribe *_vcharScribeUnicodeToWindows(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToWindows(const unsigned short *string,
					     size_t length);

vscribe *_vcharScribeCodepage437ToUnicode(const unsigned char *string);
vscribe *_vcharSizedScribeCodepage437ToUnicode(const unsigned char *string, 
					     size_t length);

vscribe *_vcharScribeUnicodeToCodepage437(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToCodepage437(const unsigned short *string,
					     size_t length);

vscribe *_vcharScribeCodepage850ToUnicode(const unsigned char *string);
vscribe *_vcharSizedScribeCodepage850ToUnicode(const unsigned char *string, 
					     size_t length);

vscribe *_vcharScribeUnicodeToCodepage850(const unsigned short *string);
vscribe *_vcharSizedScribeUnicodeToCodepage850(const unsigned short *string,
					     size_t length);

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *_vcharScribeVcharToSJIS(const vchar *string);
vscribe *_vcharSizedScribeVcharToSJIS(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeSJISToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeSJISToVchar(const unsigned char *string, 
				      size_t length);

vscribe *_vcharScribeVcharToJEUC(const vchar *string);
vscribe *_vcharSizedScribeVcharToJEUC(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeJEUCToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeJEUCToVchar(const unsigned char *string, 
				      size_t length);

vscribe *_vcharScribeVcharToKEUC(const vchar *string);
vscribe *_vcharSizedScribeVcharToKEUC(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeKEUCToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeKEUCToVchar(const unsigned char *string, 
				      size_t length);

vscribe *_vcharScribeVcharToUTF(const vchar *string);
vscribe *_vcharSizedScribeVcharToUTF(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeUTFToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeUTFToVchar(const unsigned char *string, 
				      size_t length);

vscribe *_vcharScribeVcharToCEUC(const vchar *string);
vscribe *_vcharSizedScribeVcharToCEUC(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeCEUCToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeCEUCToVchar(const unsigned char *string, 
				      size_t length);

vscribe *_vcharScribeVcharToTEUC(const vchar *string);
vscribe *_vcharSizedScribeVcharToTEUC(const vchar *string, 
				      size_t length);

vscribe *_vcharScribeTEUCToVchar(const unsigned char *string);
vscribe *_vcharSizedScribeTEUCToVchar(const unsigned char *string, 
				      size_t length);

/* other 8-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

vscribe *_vcharScribeLAT8ToASCII(const unsigned char *string);
vscribe *_vcharSizedScribeLAT8ToASCII(const unsigned char *string, 
					       size_t length);

vscribe *_vcharScribeASCIIToLAT8(const char *string);
vscribe *_vcharSizedScribeASCIIToLAT8(const char *string, 
					       size_t length);

#endif  /* vportVCHAR_CODESET */

/* other 16-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

vscribe *_vcharScribeUndefined16ToASCII(const unsigned short *string);
vscribe *_vcharSizedScribeUndefined16ToASCII(const unsigned short *string, 
					     size_t length);

#elif  (vportVCHAR_CODESET == vportCODESET_LATIN_1)

vscribe *_vcharScribeUndefined16ToLatin1(const unsigned short *string);
vscribe *_vcharSizedScribeUndefined16ToLatin1(const unsigned short *string, 
					      size_t length);

#elif  (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

vscribe *_vcharScribeUndefined16ToMacintosh(const unsigned short *string);
vscribe *_vcharSizedScribeUndefined16ToMacintosh(const unsigned short *string, 
						 size_t length);

#elif  (vportVCHAR_CODESET == vportCODESET_WINDOWS)

vscribe *_vcharScribeUndefined16ToWindows(const unsigned short *string);
vscribe *_vcharSizedScribeUndefined16ToWindows(const unsigned short *string, 
						 size_t length);

#elif  (vportVCHAR_CODESET == vportCODESET_UNICODE)

vscribe *_vcharScribeUndefined16ToUnicode(const unsigned short *string);
vscribe *_vcharSizedScribeUndefined16ToUnicode(const unsigned short *string, 
						 size_t length);

#endif /* vportVCHAR_CODESET */

#if vdebugDEBUG

vscribe *_vcharScribeASCIIToLatin1Debug(const char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeASCIIToLatin1Debug(const char *string, size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeLatin1ToASCIIDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeLatin1ToASCIIDebug(const unsigned char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeASCIIToMacintoshDebug(const char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeASCIIToMacintoshDebug(const char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeMacintoshToASCIIDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeMacintoshToASCIIDebug(const unsigned char *string,
			   	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeASCIIToWindowsDebug(const char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeASCIIToWindowsDebug(const char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeWindowsToASCIIDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeWindowsToASCIIDebug(const unsigned char *string,
			   	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeASCIIToUnicodeDebug(const char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeASCIIToUnicodeDebug(const char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToASCIIDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUnicodeToASCIIDebug(const unsigned short *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeLatin1ToMacintoshDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeLatin1ToMacintoshDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeMacintoshToLatin1Debug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeMacintoshToLatin1Debug(const unsigned char *string,
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeLatin1ToWindowsDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeLatin1ToWindowsDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeWindowsToLatin1Debug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeWindowsToLatin1Debug(const unsigned char *string,
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeLatin1ToUnicodeDebug(const unsigned char *string,
			       const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeLatin1ToUnicodeDebug(const unsigned char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToLatin1Debug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUnicodeToLatin1Debug(const unsigned short *string, 
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeMacintoshToWindowsDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeMacintoshToWindowsDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeWindowsToMacintoshDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeWindowsToMacintoshDebug(const unsigned char *string,
				size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeMacintoshToUnicodeDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeMacintoshToUnicodeDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToMacintoshDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUnicodeToMacintoshDebug(const unsigned short *string,
			     	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeWindowsToUnicodeDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeWindowsToUnicodeDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToWindowsDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUnicodeToWindowsDebug(const unsigned short *string,
			     	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToCodepage437Debug(const unsigned short *string,
			        const char *tag, const char *file, int line);

vscribe *_vcharSizedScribeUnicodeToCodepage437Debug(const unsigned short *string,
			     	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeCodepage437ToUnicodeDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeCodepage437ToUnicodeDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUnicodeToCodepage850Debug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUnicodeToCodepage850Debug(const unsigned short *string,
			     	size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeCodepage850ToUnicodeDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeCodepage850ToUnicodeDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

vscribe *_vcharScribeVcharToSJISDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToSJISDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeSJISToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharScribeVcharToSJISDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharScribeVcharToKEUCDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToKEUCDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeKEUCToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeKEUCToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeVcharToUTFDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeSJISToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeVcharToJEUCDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToJEUCDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeJEUCToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeJEUCToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeVcharToUTFDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToUTFDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeUTFToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUTFToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeVcharToCEUCDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToCEUCDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeCEUCToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeCEUCToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeVcharToTEUCDebug(const vchar *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeVcharToTEUCDebug(const vchar *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeTEUCToVcharDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeTEUCToVcharDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

/* other 8-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

vscribe *_vcharScribeLAT8ToASCIIDebug(const unsigned char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeLAT8ToASCIIDebug(const unsigned char *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

vscribe *_vcharScribeASCIIToLAT8Debug(const char *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeASCIIToLAT8Debug(const char *string, 
				size_t length,
			        const char *tag, const char *file, int line);

#endif   /* vportVCHAR_CODESET */

/* other 16-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

vscribe *_vcharScribeUndefined16ToASCIIDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUndefined16ToASCIIDebug(const unsigned short *string, 
			        size_t length,
			        const char *tag, const char *file, int line);


#elif  (vportVCHAR_CODESET == vportCODESET_LATIN_1)

vscribe *_vcharScribeUndefined16ToLatin1Debug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUndefined16ToLatin1Debug(const unsigned short *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

#elif  (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

vscribe *_vcharScribeUndefined16ToMacintoshDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUndefined16ToMacintoshDebug(const unsigned short *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

#elif  (vportVCHAR_CODESET == vportCODESET_WINDOWS)

vscribe *_vcharScribeUndefined16ToWindowsDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUndefined16ToWindowsDebug(const unsigned short *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

#elif  (vportVCHAR_CODESET == vportCODESET_UNICODE)

vscribe *_vcharScribeUndefined16ToUnicodeDebug(const unsigned short *string,
			        const char *tag, const char *file, int line);
vscribe *_vcharSizedScribeUndefined16ToUnicodeDebug(const unsigned short *string, 
			        size_t length,
			        const char *tag, const char *file, int line);

#endif /* vportVCHAR_CODESET */

#endif  /* vdebugDEBUG */

/*
 * * * * * * * * * * * * Privately Exported Constants * * * * * * * * * * * *
 */

extern vportLINK const vchar	 _vcharEmptyString;

/*
 * * * * * * * * * * * * Privately Exported Variables * * * * * * * * * * * *
 */

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */

#define 	_vcharASCII_UNDEFINED		0x20
#define 	_vcharLATIN1_UNDEFINED		0xA0
#define		_vcharMACINTOSH_UNDEFINED	0xCA
#define		_vcharWINDOWS_UNDEFINED 	0xA0
#define 	_vcharUNICODE_UNDEFINED 	0xFFFD

#define 	_vcharCODEPAGE_437_UNDEFINED	0xFF
#define 	_vcharCODEPAGE_850_UNDEFINED	0xFF
#define 	_vcharLATIN2_UNDEFINED		0xA0
#define 	_vcharLATIN3_UNDEFINED		0xA0
#define 	_vcharLATIN4_UNDEFINED		0xA0
#define 	_vcharLATIN5_UNDEFINED		0xA0
#define 	_vcharGREEK_UNDEFINED		0xA0
#define 	_vcharHEBREW_UNDEFINED		0xA0
#define 	_vcharCYRILLIC_UNDEFINED	0xA0
#define 	_vcharKOI8_UNDEFINED		0x20
#define 	_vcharVISCII_UNDEFINED		0x20
#define 	_vcharADOBE_SYMBOL_UNDEFINED	0x20
#define 	_vcharADOBE_STDENC_UNDEFINED	0x20
#define 	_vcharDEC_TECH_UNDEFINED	0x20
#define 	_vcharJISX0201_UNDEFINED	0x20

#define 	_vcharJISX0208_UNDEFINED 	0x2121
#define 	_vcharJISX0212_UNDEFINED 	0x2244
#define 	_vcharKSC5601_UNDEFINED 	0x2121
#define 	_vcharGB2312_UNDEFINED  	0xA1A1
#define 	_vcharBIG5HKU_UNDEFINED    	0xA140
#define 	_vcharCNS11643_UNDEFINED	0xfeff	

#if (vportVCHAR_CODESET == vportCODESET_ASCII)
#define	vcharUNDEFINED 		_vcharASCII_UNDEFINED
#define	vcharEOL		0x0A
#define vcharBIT 		vportCHAR_BIT
#define vcharMAX 		127
#define vcharMIN 		0
#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1)
#define vcharUNDEFINED 		_vcharLATIN1_UNDEFINED
#define	vcharEOL		0x0A
#define	vcharBIT 		vportCHAR_BIT
#define	vcharMAX 		255
#define	vcharMIN 		0
#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)
#define	vcharUNDEFINED		_vcharMACINTOSH_UNDEFINED
#define vcharEOL		0x0D
#define	vcharBIT 		vportCHAR_BIT
#define	vcharMAX 		255
#define	vcharMIN 		0
#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS)
#define	vcharUNDEFINED		_vcharWINDOWS_UNDEFINED
#define vcharEOL		0x0A
#define	vcharBIT 		vportCHAR_BIT
#define	vcharMAX 		255
#define	vcharMIN 		0
#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)
#define vcharUNDEFINED 		_vcharUNICODE_UNDEFINED
#define vcharEOL		0x0A
#define vcharBIT 		vportSHORT_BIT
#define vcharMAX 		65535
#define vcharMIN 		0
#else
typedef _error _error;	/* (vcharUNDEFINED is undefined!)
			   (vcharEOL is undefined!)
			   (vcharBIT is undefined!)
			   (vcharMAX is undefined!)
			   (vcharMIN is undefined!) */
#endif

/*
 * Constant definitions
 */

#define vcharNULL	0

#if (vportVCHAR_CODESET == vportCODESET_ASCII)

#if (vportLITERAL_CODESET == vportCODESET_ASCII)
#define vcharFromLiteral(c)	((vchar) (c))
#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)
#define vcharFromLiteral	_vcharLatin1ToASCII
#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)
#define vcharFromLiteral	_vcharMacintoshToASCII
#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)
#define vcharFromLiteral	_vcharWindowsToASCII
#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)
#define vcharFromLiteral	_vcharUnicodeToASCII
#endif

#define vcharFromASCII(c)       ((vchar)(c))
#define vcharFromLatin1 	_vcharLatin1ToASCII
#define vcharFromMacintosh	_vcharMacintoshToASCII
#define vcharFromWindows	_vcharWindowsToASCII
#define vcharFromUnicode	_vcharUnicodeToASCII

#define vcharToASCII(c)         ((char)(c))
#define vcharToLatin1           _vcharASCIIToLatin1
#define vcharToMacintosh        _vcharASCIIToMacintosh
#define vcharToWindows          _vcharASCIIToWindows
#define vcharToUnicode          _vcharASCIIToUnicode

#define vcharFromLatin2         _vcharLAT8ToASCII
#define vcharFromLatin3         _vcharLAT8ToASCII
#define vcharFromLatin4         _vcharLAT8ToASCII
#define vcharFromLatin5         _vcharLAT8ToASCII
#define vcharFromGreek          _vcharLAT8ToASCII
#define vcharFromHebrew         _vcharLAT8ToASCII
#define vcharFromCyrillic       _vcharLAT8ToASCII
#define vcharFromKoi8           _vcharLAT8ToASCII
#define vcharFromAdobeStdEnc    _vcharLAT8ToASCII

#define vcharToLatin2           _vcharASCIIToLAT8
#define vcharToLatin3           _vcharASCIIToLAT8
#define vcharToLatin4           _vcharASCIIToLAT8
#define vcharToLatin5           _vcharASCIIToLAT8
#define vcharToGreek            _vcharASCIIToLAT8
#define vcharToHebrew           _vcharASCIIToLAT8
#define vcharToCyrillic         _vcharASCIIToLAT8
#define vcharToKoi8             _vcharASCIIToLAT8
#define vcharToAdobeStdEnc      _vcharASCIIToLAT8

#define vcharFromJISX0208_83(c) _vcharASCII_UNDEFINED
#define vcharFromJISX0212(c)    _vcharASCII_UNDEFINED
#define vcharFromKSC5601(c)     _vcharASCII_UNDEFINED
#define vcharFromGB2312(c)      _vcharASCII_UNDEFINED
#define vcharFromBig5hku(c)     _vcharASCII_UNDEFINED
#define vcharFromCNS11643(c)	_vcharASCII_UNDEFINED

#define vcharToJISX0208_83(c)   _vcharJISX0208_UNDEFINED
#define vcharToJISX0212(c)      _vcharJISX0212_UNDEFINED
#define vcharToKSC5601(c)       _vcharKSC5601_UNDEFINED
#define vcharToGB2312(c)        _vcharGB2312_UNDEFINED
#define vcharToBig5hku(c)       _vcharBIG5HKU_UNDEFINED
#define vcharToCNS11643(c)	_vcharCNS11643_UNDEFINED

#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1)

#if (vportLITERAL_CODESET == vportCODESET_ASCII)
#define vcharFromLiteral	_vcharASCIIToLatin1
#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)
#define vcharFromLiteral(c)     ((vchar)(c))
#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)
#define vcharFromLiteral	_vcharMacintoshToLatin1
#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)
#define vcharFromLiteral	_vcharWindowsToLatin1
#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)
#define vcharFromLiteral	_vcharUnicodeToLatin1
#endif

#define vcharFromASCII          _vcharASCIIToLatin1
#define vcharFromLatin1(c) 	((vchar)(c))
#define vcharFromMacintosh	_vcharMacintoshToLatin1
#define vcharFromWindows	_vcharWindowsToLatin1
#define vcharFromUnicode	_vcharUnicodeToLatin1

#define vcharToASCII            _vcharLatin1ToASCII
#define vcharToLatin1(c)        ((unsigned char)(c))
#define vcharToMacintosh	_vcharLatin1ToMacintosh
#define vcharToWindows  	_vcharLatin1ToWindows
#define vcharToUnicode(c)       ((unsigned short)(c))

#define vcharFromJISX0208_83(c) _vcharLATIN1_UNDEFINED
#define vcharFromJISX0212(c)    _vcharLATIN1_UNDEFINED
#define vcharFromKSC5601(c)     _vcharLATIN1_UNDEFINED
#define vcharFromGB2312(c)      _vcharLATIN1_UNDEFINED
#define vcharFromBig5hku(c)     _vcharLATIN1_UNDEFINED
#define vcharFromCNS11643(c)	_vcharLATIN1_UNDEFINED

#define vcharToJISX0208_83(c)   _vcharJISX0208_UNDEFINED
#define vcharToJISX0212(c)      _vcharJISX0212_UNDEFINED
#define vcharToKSC5601(c)       _vcharKSC5601_UNDEFINED
#define vcharToGB2312(c)        _vcharGB2312_UNDEFINED
#define vcharToBig5hku(c)       _vcharBIG5HKU_UNDEFINED
#define vcharToCNS11643(c)	_vcharCNS11643_UNDEFINED

#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

#if (vportLITERAL_CODESET == vportCODESET_ASCII)
#define vcharFromLiteral	_vcharASCIIToMacintosh
#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)
#define vcharFromLiteral	_vcharLatin1ToMacintosh
#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)
#define vcharFromLiteral(c)	((vchar) (c))
#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)
#define vcharFromLiteral	_vcharWindowsToMacintosh
#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)
#define vcharFromLiteral	_vcharUnicodeToMacintosh
#endif

#define vcharFromASCII          _vcharASCIIToMacintosh
#define vcharFromLatin1 	_vcharLatin1ToMacintosh
#define vcharFromMacintosh(c)   ((vchar)(c))
#define vcharFromWindows 	_vcharWindowsToMacintosh
#define vcharFromUnicode        _vcharUnicodeToMacintosh

#define vcharToASCII            _vcharMacintoshToASCII
#define vcharToLatin1           _vcharMacintoshToLatin1
#define vcharToMacintosh(c)     ((unsigned char)(c))
#define vcharToWindows          _vcharMacintoshToWindows
#define vcharToUnicode	        _vcharMacintoshToUnicode

#define vcharFromJISX0208_83(c) _vcharMACINTOSH_UNDEFINED
#define vcharFromJISX0212(c)    _vcharMACINTOSH_UNDEFINED
#define vcharFromKSC5601(c)     _vcharMACINTOSH_UNDEFINED
#define vcharFromGB2312(c)      _vcharMACINTOSH_UNDEFINED
#define vcharFromBig5hku(c)     _vcharMACINTOSH_UNDEFINED
#define vcharFromCNS11643(c)	_vcharMACINTOSH_UNDEFINED

#define vcharToJISX0208_83(c)   _vcharJISX0208_UNDEFINED
#define vcharToJISX0212(c)      _vcharJISX0212_UNDEFINED
#define vcharToKSC5601(c)       _vcharKSC5601_UNDEFINED
#define vcharToGB2312(c)        _vcharGB2312_UNDEFINED
#define vcharToBig5hku(c)       _vcharBIG5HKU_UNDEFINED
#define vcharToCNS11643(c)	_vcharCNS11643_UNDEFINED

#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS)

#if (vportLITERAL_CODESET == vportCODESET_ASCII)
#define vcharFromLiteral        _vcharASCIIToWindows
#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)
#define vcharFromLiteral	_vcharLatin1ToWindows
#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)
#define vcharFromLiteral	_vcharMacintoshToWindows
#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)
#define vcharFromLiteral(c)	((vchar) (c))
#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)
#define vcharFromLiteral	_vcharUnicodeToWindows
#endif

#define vcharFromASCII          _vcharASCIIToWindows
#define vcharFromLatin1 	_vcharLatin1ToWindows
#define vcharFromMacintosh      _vcharMacintoshToWindows
#define vcharFromWindows(c) 	((vchar)(c))
#define vcharFromUnicode        _vcharUnicodeToWindows

#define vcharToASCII            _vcharWindowsToASCII
#define vcharToLatin1           _vcharWindowsToLatin1
#define vcharToMacintosh        _vcharWindowsToMacintosh
#define vcharToWindows(c)       ((unsigned char)(c))
#define vcharToUnicode	        _vcharWindowsToUnicode

#define vcharFromJISX0208_83(c) _vcharWINDOWS_UNDEFINED
#define vcharFromJISX0212(c)    _vcharWINDOWS_UNDEFINED
#define vcharFromKSC5601(c)     _vcharWINDOWS_UNDEFINED
#define vcharFromGB2312(c)      _vcharWINDOWS_UNDEFINED
#define vcharFromBig5hku(c)     _vcharWINDOWS_UNDEFINED
#define vcharFromCNS11643(c)	_vcharWINDOWS_UNDEFINED

#define vcharToJISX0208_83(c)   _vcharJISX0208_UNDEFINED
#define vcharToJISX0212(c)      _vcharJISX0212_UNDEFINED
#define vcharToKSC5601(c)       _vcharKSC5601_UNDEFINED
#define vcharToGB2312(c)        _vcharGB2312_UNDEFINED
#define vcharToBig5hku(c)       _vcharBIG5HKU_UNDEFINED
#define vcharToCNS11643(c)	_vcharCNS11643_UNDEFINED

#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)

#if (vportLITERAL_CODESET == vportCODESET_ASCII)
#define vcharFromLiteral        _vcharASCIIToUnicode
#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)
#define vcharFromLiteral(c)	((vchar) (c))
#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)
#define vcharFromLiteral	_vcharMacintoshToUnicode
#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)
#define vcharFromLiteral	_vcharWindowsToUnicode
#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)
#define vcharFromLiteral(c)	((vchar) (c))
#endif

#define vcharFromASCII          _vcharASCIIToUnicode
#define vcharFromLatin1 	_vcharLatin1ToUnicode
#define vcharFromMacintosh	_vcharMacintoshToUnicode
#define vcharFromWindows	_vcharWindowsToUnicode
#define vcharFromUnicode(c)     ((vchar)(c))

#define vcharToASCII            _vcharUnicodeToASCII
#define vcharToLatin1   	_vcharUnicodeToLatin1
#define vcharToMacintosh	_vcharUnicodeToMacintosh
#define vcharToWindows  	_vcharUnicodeToWindows
#define vcharToUnicode(c)       ((unsigned short)(c))

#endif

/*
 * Single character functions:
 */

#if (vportVCHAR_CODESET == vportCODESET_ASCII)

#define vcharIsAlphaNumeric(c)  ((vbool) (isalnum(c) != 0))
#define vcharIsAlphabetic(c)	((vbool) (isalpha(c) != 0))
#define vcharIsControl(c)	((vbool) (iscntrl(c) != 0))
#define vcharIsDecimal(c)	((vbool) (isdigit(c) != 0))
#define vcharIsDigit(c)		((vbool) (isdigit(c) != 0))
#define vcharIsNumeric(c)	((vbool) (isdigit(c) != 0))
#define vcharIsGraphic(c)	((vbool) (isgraph(c) != 0))
#define vcharIsLowerCase(c)	((vbool) (islower(c) != 0))
#define vcharIsPrintable(c)	((vbool) (isprint(c) != 0))
#define vcharIsPunctuation(c)	((vbool) (ispunct(c) != 0))
#define vcharIsSpacing(c)	vTRUE
#define vcharIsNonSpacing(c)	vFALSE
#define vcharIsWhiteSpace(c)	((vbool) (isspace(c) != 0))
#define vcharIsBlank(c)	        ((vbool) (c == 0x20))
#define vcharIsUpperCase(c)	((vbool) (isupper(c) != 0))
#define vcharIsHexDigit(c)	((vbool) (isxdigit(c) != 0))

#define vcharToLowerCase(c)	((vchar) tolower( c ))
#define vcharToUpperCase(c)	((vchar) toupper( c ))
#define vcharStripDiacritics(c)	((vchar) (c))

#define vcharToUpperCaseLength(c)    (1)

#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1) 

#define	_vcharUpperF	0x01
#define	_vcharLowerF	0x02
#define	_vcharDigitF	0x04
#define	_vcharSpaceF	0x08
#define _vcharPuncF	0x10
#define _vcharCtrlF	0x20
#define _vcharBlankF	0x40
#define	_vcharHexF	0x80

#define _vcharVector(c) (0x0001 << (c))

extern vportLINK  const unsigned short  _vcharDecimal[];
extern vportLINK  const unsigned short  _vcharNumeric[];
extern vportLINK	const unsigned char   _vcharCharTypes[];
extern vportLINK	const unsigned char   _vcharToUpper[];
extern vportLINK	const unsigned char   _vcharToLower[];
extern vportLINK	const unsigned char   _vcharStrip[];

#define vcharIsDecimal(c)	\
            ((vbool)(((_vcharDecimal)[(unsigned)(((vchar)(c)) & 0xF0u) >> 4u] \
				      & _vcharVector((vchar)(c) & 0x0F)) != 0))
#define vcharIsNumeric(c)	\
            ((vbool)(((_vcharNumeric)[(unsigned)(((vchar)(c)) & 0xF0u) >> 4u] \
				      & _vcharVector((vchar)(c) & 0x0F)) != 0))
#define	vcharIsAlphabetic(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)]&(_vcharUpperF \
						       | _vcharLowerF)) != 0))

#define vcharIsAlphaNumeric(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)]&(_vcharUpperF \
						       | _vcharLowerF)) != 0) \
					|| vcharIsNumeric(c)))
#define	vcharIsBlank(c)	        ((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharBlankF) != 0))
#define vcharIsControl(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             & _vcharCtrlF) != 0))
#define	vcharIsDigit(c)		((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharDigitF) != 0))
#define	vcharIsGraphic(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)] \
					             &(_vcharPuncF \
						       | _vcharUpperF \
						       | _vcharLowerF)) != 0) \
					|| vcharIsNumeric(c)))
#define	vcharIsHexDigit(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharHexF) != 0))
#define	vcharIsLowerCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharLowerF) != 0))
#define vcharIsNonSpacing(c)	vFALSE
#define vcharIsPrintable(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)]\
					             &(_vcharPuncF \
						       |_vcharUpperF \
						       |_vcharLowerF \
						       |_vcharBlankF)) != 0) \
					|| vcharIsNumeric(c)))
#define vcharIsPunctuation(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharPuncF) != 0))
#define vcharIsSpacing(c)	vTRUE
#define	vcharIsUpperCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharUpperF) != 0))
#define	vcharIsWhiteSpace(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharSpaceF) != 0))

#define vcharToUpperCase(c)	(_vcharToUpper[(vchar)(c)])
#define vcharToLowerCase(c)	(_vcharToLower[(vchar)(c)])
#define vcharStripDiacritics(c)	(_vcharStrip[(vchar)(c)])

#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

#define	_vcharUpperF	0x01
#define	_vcharLowerF	0x02
#define	_vcharDigitF	0x04
#define	_vcharSpaceF	0x08
#define _vcharPuncF	0x10
#define _vcharCtrlF	0x20
#define _vcharBlankF	0x40
#define	_vcharHexF	0x80

#define _vcharVector(c) (0x0001 << (c))

extern vportLINK	const unsigned char	_vcharCharTypes[];
extern vportLINK	const unsigned char	_vcharToUpper[];
extern vportLINK	const unsigned char	_vcharToLower[];
extern vportLINK	const unsigned char	_vcharStrip[];

#define	vcharIsAlphabetic(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)]&(_vcharUpperF \
						       | _vcharLowerF)) != 0))
#define	vcharIsBlank(c)	        ((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharBlankF) != 0))
#define vcharIsControl(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             & _vcharCtrlF) != 0))
#define	vcharIsDigit(c)		((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharDigitF) != 0))
#define vcharIsAlphaNumeric(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &(_vcharUpperF \
						       | _vcharLowerF \
						       | _vcharDigitF )) != 0))
#define vcharIsDecimal          vcharIsDigit
#define vcharIsNumeric          vcharIsDigit
#define	vcharIsGraphic(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &(_vcharPuncF \
						       | _vcharUpperF \
						       | _vcharLowerF \
						       | _vcharDigitF )) != 0))
#define	vcharIsHexDigit(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharHexF) != 0))
#define	vcharIsLowerCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharLowerF) != 0))
#define vcharIsNonSpacing(c)	vFALSE
#define vcharIsPrintable(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)]\
					             &(_vcharPuncF \
						       |_vcharUpperF \
						       |_vcharLowerF \
						       |_vcharBlankF)) != 0) \
					|| vcharIsNumeric(c)))

#define vcharIsPunctuation(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharPuncF) != 0))
#define vcharIsSpacing(c)	vTRUE
#define	vcharIsUpperCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharUpperF) != 0))
#define	vcharIsWhiteSpace(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharSpaceF) != 0))

#define vcharToUpperCase(c)	(_vcharToUpper[(vchar)(c)])
#define vcharToLowerCase(c)	(_vcharToLower[(vchar)(c)])
#define vcharStripDiacritics(c)	(_vcharStrip[(vchar)(c)])

#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS) 

#define	_vcharUpperF	0x01
#define	_vcharLowerF	0x02
#define	_vcharDigitF	0x04
#define	_vcharSpaceF	0x08
#define _vcharPuncF	0x10
#define _vcharCtrlF	0x20
#define _vcharBlankF	0x40
#define	_vcharHexF	0x80

#define _vcharVector(c) (0x0001 << (c))

extern vportLINK  const unsigned short  _vcharDecimal[];
extern vportLINK  const unsigned short  _vcharNumeric[];
extern vportLINK	const unsigned char   _vcharCharTypes[];
extern vportLINK	const unsigned char   _vcharToUpper[];
extern vportLINK	const unsigned char   _vcharToLower[];
extern vportLINK	const unsigned char   _vcharStrip[];

#define vcharIsDecimal(c)	\
            ((vbool)(((_vcharDecimal)[(unsigned)(((vchar)(c)) & 0xF0u) >> 4u] \
				      & _vcharVector((vchar)(c) & 0x0F)) != 0))
#define vcharIsNumeric(c)	\
            ((vbool)(((_vcharNumeric)[(unsigned)(((vchar)(c)) & 0xF0u) >> 4u] \
				      & _vcharVector((vchar)(c) & 0x0F)) != 0))
#define	vcharIsAlphabetic(c)	\
  ((vbool)(((_vcharCharTypes)[(vchar)(c)]&(_vcharUpperF | _vcharLowerF)) != 0))

#define vcharIsAlphaNumeric(c)	\
   ((vbool)((((_vcharCharTypes)[(vchar)(c)]&(_vcharUpperF|_vcharLowerF)) != 0)\
					|| vcharIsNumeric(c)))
#define	vcharIsBlank(c)	        ((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharBlankF) != 0))
#define vcharIsControl(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             & _vcharCtrlF) != 0))
#define	vcharIsDigit(c)		((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharDigitF) != 0))
#define	vcharIsGraphic(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)] \
					             &(_vcharPuncF \
						       | _vcharUpperF \
						       | _vcharLowerF)) != 0) \
					|| vcharIsNumeric(c)))
#define	vcharIsHexDigit(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharHexF) != 0))
#define	vcharIsLowerCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharLowerF) != 0))
#define vcharIsNonSpacing(c)	vFALSE
#define vcharIsPrintable(c)	((vbool)((((_vcharCharTypes)[(vchar)(c)]\
					             &(_vcharPuncF \
						       |_vcharUpperF \
						       |_vcharLowerF \
						       |_vcharBlankF)) != 0) \
					|| vcharIsNumeric(c)))

#define vcharIsPunctuation(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharPuncF) != 0))
#define vcharIsSpacing(c)	vTRUE
#define	vcharIsUpperCase(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharUpperF) != 0))
#define	vcharIsWhiteSpace(c)	((vbool)(((_vcharCharTypes)[(vchar)(c)] \
					             &_vcharSpaceF) != 0))

#define vcharToUpperCase(c)	(_vcharToUpper[(vchar)(c)])
#define vcharToLowerCase(c)	(_vcharToLower[(vchar)(c)])
#define vcharStripDiacritics(c)	(_vcharStrip[(vchar)(c)])

#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharIsPunctuation _vcharIsSymbol

#define vcharIsAlphaNumeric(c) \
   (vcharIsAlphabetic(c) || vcharIsNumeric(c))

#define vcharIsPrintable(c) \
   (vcharIsAlphabetic(c) || vcharIsNumeric(c) \
    || _vcharIsSymbol(c) || vcharIsBlank(c))

#define	vcharIsGraphic(c) \
   (vcharIsAlphabetic(c) || vcharIsNumeric(c) || _vcharIsSymbol(c))

#define vcharIsSpacing(c) \
   (vcharIsPrintable(c) && !(vcharIsNonSpacing(c)))

#endif

/*
 * Character string functions:
 */


#define vcharGetEmptyString()	(&_vcharEmptyString)


/*
 * Copy functions:
 */

#if (!vdebugDEBUG)
#define vcharLengthScribed(_s) \
    vscribeGetLength(_s)
#define vcharLengthScribedBounded(_s, _l) \
    vscribeGetLengthBounded(_s, _l)
#endif

#define vcharSizedCopyFast(_s, _n, _d) \
    ((void) vmemCopy((_s), (_d), (_n) * sizeof(vchar)))

#define vcharSizedCopyScribed(_s, _d) \
    ((vchar *) vscribeScribble(_s, _d))

#define vcharSizedCopyScribedBounded(_s, _d, _b) \
    ((vchar *) vscribeScribbleBounded(_s, _d, _b))

#define vcharCopyFromLiteral(s, d) \
    ((vchar *) vcharCopyScribed(vcharScribeLiteral(s), (d)))
     
#define vcharCopyFromSystem(s, d) \
    ((vchar *) vcharCopyScribed(vcharScribeSystem(s), (d)))

/*
 * Append functions:
 */

#define vcharAppend(d, s) \
    ((vchar *) vcharAppendScribed((d), vcharScribe(s)))

#define vcharAppendBounded(d, l, s) \
    ((vchar *) vcharAppendScribedBounded((d), (l), vcharScribe(s)))

#define vcharAppendFromLiteral(d, s) \
    ((vchar *) vcharAppendScribed((d), vcharScribeLiteral(s)))

#define vcharAppendFromSystem(d, s) \
    ((vchar *) vcharAppendScribed((d), vcharScribeSystem(s)))

#define vcharScribeCharacter(c) \
    vcharScribePadding((c), 1)

/*
 * Character set dependent implementations:
 */

#if ((vportVCHAR_CODESET == vportCODESET_ASCII) \
     || (vportVCHAR_CODESET == vportCODESET_LATIN_1) \
     || (vportVCHAR_CODESET == vportCODESET_MACINTOSH) \
     || (vportVCHAR_CODESET == vportCODESET_WINDOWS))

/*
 * Macroable functions:
 */

#define vcharCopyFast(_s, _d) \
    ((void) strcpy((char *)(_d), (vcharCLIB_STR_CONST char *)(_s)))
#define vcharAppendFast(_d, _s) \
    ((void) strcat((char *) (_d), (vcharCLIB_STR_CONST char *) (_s)))

#define vcharLength(_s)	\
    strlen((vcharCLIB_STR_CONST char *) (_s))

#define vcharSizedCompare			vmemCompare

#define vcharCompare(_s1, _s2) \
    strcmp((vcharCLIB_STR_CONST char *) (_s1), \
	   (vcharCLIB_STR_CONST char *) (_s2))
#define vcharCompareBounded(_s1, _s2, _n) \
    strncmp((vcharCLIB_STR_CONST char *) (_s1), \
	    (vcharCLIB_STR_CONST char *) (_s2), (_n))

#if (vportVCHAR_CODESET == vportCODESET_ASCII)

#define vcharCompareBase(_s1, _s2) \
    strcasecmp((vcharCLIB_STR_CONST char *) (_s1), \
	       (vcharCLIB_STR_CONST char *) (_s2))
#define vcharCompareBaseBounded(_s1, _s2, _n)\
    strncasecmp((vcharCLIB_STR_CONST char *) (_s1), \
		(vcharCLIB_STR_CONST char *) (_s2), (_n))

#endif

#define vcharSearchChar(_s1, _c) \
    ((vchar *) strchr((vcharCLIB_STR_CONST char *) (_s1), (char) _c))
#define vcharSearchCharBackwards(_s1, _c) \
    ((vchar *) strrchr((vcharCLIB_STR_CONST char *) (_s1), (char) _c))
#define vcharSearchOneOf(_s1, _c) \
    ((vchar *) strpbrk((vcharCLIB_STR_CONST char *) (_s1), \
		       (vcharCLIB_STR_CONST char *) (_c)))

#if (!vportBAD_STRSTR)
#define vcharSearch(_s, _r) \
    ((vchar *) strstr((vcharCLIB_STR_CONST char *) (_s), \
		      (vcharCLIB_STR_CONST char *) (_r)))
#endif

#define vcharGetFirstToken(_s, _c) \
    ((vchar *) strtok((char *) (_s), (vcharCLIB_STR_CONST char *) (_c)))

#define vcharGetNextToken(_c) \
    ((vchar *) strtok((char *) NULL, (vcharCLIB_STR_CONST char *) (_c)))

#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)


/*
 * Macroable functions:
 */

#define vcharCopyFast(s,d) \
    ((void) vcharCopy((s),(d)))

#define vcharAppendFast(d,s) \
    ((void) vcharAppend((d),(s)))

#endif


/*
 * Define literal and import/export scribes:
 */

/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

#define vcharScribeSJIS 		_vcharScribeSJISToVchar
#define vcharSizedScribeSJIS		_vcharSizedScribeSJISToVchar

#define vcharScribeSJISExport   	_vcharScribeVcharToSJIS
#define vcharSizedScribeSJISExport	_vcharSizedScribeVcharToSJIS

#define vcharScribeJEUC 		_vcharScribeJEUCToVchar
#define vcharSizedScribeJEUC		_vcharSizedScribeJEUCToVchar

#define vcharScribeJEUCExport   	_vcharScribeVcharToJEUC
#define vcharSizedScribeJEUCExport	_vcharSizedScribeVcharToJEUC

#define vcharScribeKEUC 		_vcharScribeKEUCToVchar
#define vcharSizedScribeKEUC		_vcharSizedScribeKEUCToVchar

#define vcharScribeKEUCExport   	_vcharScribeVcharToKEUC
#define vcharSizedScribeKEUCExport	_vcharSizedScribeVcharToKEUC

#define vcharScribeUTF  		_vcharScribeUTFToVchar
#define vcharSizedScribeUTF		_vcharSizedScribeUTFToVchar

#define vcharScribeUTFExport    	_vcharScribeVcharToUTF
#define vcharSizedScribeUTFExport 	_vcharSizedScribeVcharToUTF

#define vcharScribeCEUC 		_vcharScribeCEUCToVchar
#define vcharSizedScribeCEUC		_vcharSizedScribeCEUCToVchar

#define vcharScribeCEUCExport   	_vcharScribeVcharToCEUC
#define vcharSizedScribeCEUCExport	_vcharSizedScribeVcharToCEUC

#define vcharScribeTEUC 		_vcharScribeTEUCToVchar
#define vcharSizedScribeTEUC		_vcharSizedScribeTEUCToVchar

#define vcharScribeTEUCExport   	_vcharScribeVcharToTEUC
#define vcharSizedScribeTEUCExport	_vcharSizedScribeVcharToTEUC

#if (vportVCHAR_CODESET == vportCODESET_ASCII)

#define vcharScribeASCII		vcharScribe
#define vcharScribeASCIIShared		vcharScribeShared
#define vcharSizedScribeASCII		vcharSizedScribe
#define vcharSizedScribeASCIIShared	vcharSizedScribeShared

#define vcharScribeASCIIExport		vcharScribe
#define vcharSizedScribeASCIIExport	vcharSizedScribe

#define vcharScribeLatin1		_vcharScribeLatin1ToASCII
#define vcharScribeLatin1Shared		_vcharScribeLatin1ToASCII
#define vcharSizedScribeLatin1		_vcharSizedScribeLatin1ToASCII
#define vcharSizedScribeLatin1Shared	_vcharSizedScribeLatin1ToASCII

#define vcharScribeLatin1Export		_vcharScribeASCIIToLatin1
#define vcharSizedScribeLatin1Export	_vcharSizedScribeASCIIToLatin1

#define vcharScribeMacintosh		_vcharScribeMacintoshToASCII
#define vcharScribeMacintoshShared	_vcharScribeMacintoshToASCII
#define vcharSizedScribeMacintosh	_vcharSizedScribeMacintoshToASCII
#define vcharSizedScribeMacintoshShared	_vcharSizedScribeMacintoshToASCII

#define vcharScribeMacintoshExport	_vcharScribeASCIIToMacintosh
#define vcharSizedScribeMacintoshExport	_vcharSizedScribeASCIIToMacintosh

#define vcharScribeWindows		_vcharScribeWindowsToASCII
#define vcharScribeWindowsShared	_vcharScribeWindowsToASCII
#define vcharSizedScribeWindows 	_vcharSizedScribeWindowsToASCII
#define vcharSizedScribeWindowsShared	_vcharSizedScribeWindowsToASCII

#define vcharScribeWindowsExport	_vcharScribeASCIIToWindows
#define vcharSizedScribeWindowsExport	_vcharSizedScribeASCIIToWindows

#define vcharScribeUnicode		_vcharScribeUnicodeToASCII
#define vcharScribeUnicodeShared	_vcharScribeUnicodeToASCII
#define vcharSizedScribeUnicode		_vcharSizedScribeUnicodeToASCII
#define vcharSizedScribeUnicodeShared	_vcharSizedScribeUnicodeToASCII

#define vcharScribeUnicodeExport	_vcharScribeASCIIToUnicode
#define vcharSizedScribeUnicodeExport	_vcharSizedScribeASCIIToUnicode

#if (vportLITERAL_CODESET == vportCODESET_ASCII)

#define vcharScribeLiteral		vcharScribeShared
#define vcharSizedScribeLiteral 	vcharSizedScribeShared

#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)

#define vcharScribeLiteral		_vcharScribeLatin1ToASCII
#define vcharSizedScribeLiteral		_vcharSizedScribeLatin1ToASCII

#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeLiteral		_vcharScribeMacintoshToASCII
#define vcharSizedScribeLiteral		_vcharSizedScribeMacintoshToASCII

#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)

#define vcharScribeLiteral		_vcharScribeWindowsToASCII
#define vcharSizedScribeLiteral		_vcharSizedScribeWindowsToASCII

#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)

#define vcharScribeLiteral		_vcharScribeUnicodeToASCII
#define vcharSizedScribeLiteral		_vcharSizedScribeUnicodeToASCII

#endif

#define vcharScribeLatin2		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeLatin2	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeLatin2Export	          vcharScribeLatin1Export
#define vcharSizedScribeLatin2Export      vcharSizedScribeLatin1Export

#define vcharScribeLatin3		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeLatin3	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeLatin3Export	          vcharScribeLatin1Export
#define vcharSizedScribeLatin3Export      vcharSizedScribeLatin1Export

#define vcharScribeLatin4		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeLatin4	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeLatin4Export	          vcharScribeLatin1Export
#define vcharSizedScribeLatin4Export      vcharSizedScribeLatin1Export

#define vcharScribeLatin5		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeLatin5	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeLatin5Export	          vcharScribeLatin1Export
#define vcharSizedScribeLatin5Export      vcharSizedScribeLatin1Export

#define vcharScribeGreek		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeGreek	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeGreekExport	          vcharScribeLatin1Export
#define vcharSizedScribeGreekExport       vcharSizedScribeLatin1Export

#define vcharScribeHebrew		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeHebrew	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeHebrewExport	          vcharScribeLatin1Export
#define vcharSizedScribeHebrewExport      vcharSizedScribeLatin1Export

#define vcharScribeCyrillic		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeCyrillic	  _vcharSizedScribeLAT8ToASCII

#define vcharScribeCyrillicExport	  vcharScribeLatin1Export
#define vcharSizedScribeCyrillicExport    vcharSizedScribeLatin1Export

#define vcharScribeKoi8	        	  _vcharScribeLAT8ToASCII
#define vcharSizedScribeKoi8	          _vcharSizedScribeLAT8ToASCII

#define vcharScribeKoi8Export	          vcharScribeLatin1Export
#define vcharSizedScribeKoi8Export        vcharSizedScribeLatin1Export

#define vcharScribeAdobeStdEnc		  _vcharScribeLAT8ToASCII
#define vcharSizedScribeAdobeStdEnc	  _vcharSizedScribeLAT8ToASCII

#define vcharScribeAdobeStdEncExport	  vcharScribeLatin1Export
#define vcharSizedScribeAdobeStdEncExport vcharSizedScribeLatin1Export

#define vcharScribeJISX0208_83		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeJISX0208_83	  _vcharSizedScribeUndefined16ToASCII

#define vcharScribeJISX0212		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeJISX0212	  _vcharSizedScribeUndefined16ToASCII

#define vcharScribeKSC5601		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeKSC5601 	  _vcharSizedScribeUndefined16ToASCII

#define vcharScribeGB2312		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeGB2312  	  _vcharSizedScribeUndefined16ToASCII

#define vcharScribeBig5hku 		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeBig5hku    	  _vcharSizedScribeUndefined16ToASCII

#define vcharScribeCNS11643		  _vcharScribeUndefined16ToASCII
#define vcharSizedScribeCNS11643 	  _vcharSizedScribeUndefined16ToASCII

#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1)

#define vcharScribeASCII		_vcharScribeASCIIToLatin1
#define vcharScribeASCIIShared		_vcharScribeASCIIToLatin1
#define vcharSizedScribeASCII		_vcharSizedScribeASCIIToLatin1
#define vcharSizedScribeASCIIShared	_vcharSizedScribeASCIIToLatin1

#define vcharScribeASCIIExport		_vcharScribeLatin1ToASCII
#define vcharSizedScribeASCIIExport	_vcharSizedScribeLatin1ToASCII

#define vcharScribeLatin1		vcharScribe
#define vcharScribeLatin1Shared		vcharScribeShared
#define vcharSizedScribeLatin1		vcharSizedScribe
#define vcharSizedScribeLatin1Shared	vcharSizedScribeShared

#define vcharScribeLatin1Export		vcharScribe
#define vcharSizedScribeLatin1Export	vcharSizedScribe

#define vcharScribeMacintosh		_vcharScribeMacintoshToLatin1
#define vcharScribeMacintoshShared	_vcharScribeMacintoshToLatin1
#define vcharSizedScribeMacintosh	_vcharSizedScribeMacintoshToLatin1
#define vcharSizedScribeMacintoshShared	_vcharSizedScribeMacintoshToLatin1

#define vcharScribeMacintoshExport	_vcharScribeLatin1ToMacintosh
#define vcharSizedScribeMacintoshExport	_vcharSizedScribeLatin1ToMacintosh

#define vcharScribeWindows		_vcharScribeWindowsToLatin1
#define vcharScribeWindowsShared	_vcharScribeWindowsToLatin1
#define vcharSizedScribeWindows 	_vcharSizedScribeWindowsToLatin1
#define vcharSizedScribeWindowsShared	_vcharSizedScribeWindowsToLatin1

#define vcharScribeWindowsExport	_vcharScribeLatin1ToWindows
#define vcharSizedScribeWindowsExport	_vcharSizedScribeLatin1ToWindows

#define vcharScribeUnicode		_vcharScribeUnicodeToLatin1
#define vcharScribeUnicodeShared	_vcharScribeUnicodeToLatin1
#define vcharSizedScribeUnicode		_vcharSizedScribeUnicodeToLatin1
#define vcharSizedScribeUnicodeShared	_vcharSizedScribeUnicodeToLatin1

#define vcharScribeUnicodeExport	_vcharScribeLatin1ToUnicode
#define vcharSizedScribeUnicodeExport	_vcharSizedScribeLatin1ToUnicode

#if (vportLITERAL_CODESET == vportCODESET_ASCII)

#define vcharScribeLiteral(_s)		_vcharScribeASCIIToLatin1((_s))
#define vcharSizedScribeLiteral(_s,_l)	_vcharSizedScribeASCIIToLatin1((_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)

#define vcharScribeLiteral(_s)		vcharScribeShared((const vchar *) (_s))
#define vcharSizedScribeLiteral(_s,_l) 	vcharSizedScribeShared((const vchar *)(_s),(_l))

#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeLiteral(_s)		_vcharScribeMacintoshToLatin1((unsigned char *)(_s))
#define vcharSizedScribeLiteral(_s,_l)	_vcharSizedScribeMacintoshToLatin1((unsigned char *)(_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)

#define vcharScribeLiteral(_s)		_vcharScribeWindowsToLatin1((unsigned char *)(_s))
#define vcharSizedScribeLiteral(_s,_l)	_vcharSizedScribeWindowsToLatin1((unsigned char *)(_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)

#define vcharScribeLiteral		_vcharScribeUnicodeToLatin1
#define vcharSizedScribeLiteral		_vcharSizedScribeUnicodeToLatin1

#endif

#define vcharScribeJISX0208_83		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeJISX0208_83	  _vcharSizedScribeUndefined16ToLatin1

#define vcharScribeJISX0212		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeJISX0212	  _vcharSizedScribeUndefined16ToLatin1

#define vcharScribeKSC5601		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeKSC5601 	  _vcharSizedScribeUndefined16ToLatin1

#define vcharScribeGB2312		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeGB2312  	  _vcharSizedScribeUndefined16ToLatin1

#define vcharScribeBig5hku 		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeBig5hku    	  _vcharSizedScribeUndefined16ToLatin1

#define vcharScribeCNS11643		  _vcharScribeUndefined16ToLatin1
#define vcharSizedScribeCNS11643 	  _vcharSizedScribeUndefined16ToLatin1

#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeASCII		_vcharScribeASCIIToMacintosh
#define vcharScribeASCIIShared		_vcharScribeASCIIToMacintosh
#define vcharSizedScribeASCII		_vcharSizedScribeASCIIToMacintosh
#define vcharSizedScribeASCIIShared	_vcharSizedScribeASCIIToMacintosh

#define vcharScribeASCIIExport		_vcharScribeMacintoshToASCII
#define vcharSizedScribeASCIIExport	_vcharSizedScribeMacintoshToASCII

#define vcharScribeLatin1		_vcharScribeLatin1ToMacintosh
#define vcharScribeLatin1Shared		_vcharScribeLatin1ToMacintosh
#define vcharSizedScribeLatin1		_vcharSizedScribeLatin1ToMacintosh
#define vcharSizedScribeLatin1Shared	_vcharSizedScribeLatin1ToMacintosh

#define vcharScribeLatin1Export		_vcharScribeMacintoshToLatin1
#define vcharSizedScribeLatin1Export	_vcharSizedScribeMacintoshToLatin1

#define vcharScribeMacintosh		vcharScribe
#define vcharScribeMacintoshShared	vcharScribeShared
#define vcharSizedScribeMacintosh	vcharSizedScribe
#define vcharSizedScribeMacintoshShared	vcharSizedScribeShared

#define vcharScribeMacintoshExport	vcharScribe
#define vcharSizedScribeMacintoshExport	vcharSizedScribe

#define vcharScribeWindows		_vcharScribeWindowsToMacintosh
#define vcharScribeWindowsShared	_vcharScribeWindowsToMacintosh
#define vcharSizedScribeWindows 	_vcharSizedScribeWindowsToMacintosh
#define vcharSizedScribeWindowsShared	_vcharSizedScribeWindowsToMacintosh

#define vcharScribeWindowsExport	_vcharScribeMacintoshToWindows
#define vcharSizedScribeWindowsExport	_vcharSizedScribeMacintoshToWindows

#define vcharScribeUnicode		_vcharScribeUnicodeToMacintosh
#define vcharScribeUnicodeShared	_vcharScribeUnicodeToMacintosh
#define vcharSizedScribeUnicode		_vcharSizedScribeUnicodeToMacintosh
#define vcharSizedScribeUnicodeShared	_vcharSizedScribeUnicodeToMacintosh

#define vcharScribeUnicodeExport	_vcharScribeMacintoshToUnicode
#define vcharSizedScribeUnicodeExport	_vcharSizedScribeMacintoshToUnicode

#if (vportLITERAL_CODESET == vportCODESET_ASCII)

#define vcharScribeLiteral(_s)		_vcharScribeASCIIToMacintosh((_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeASCIIToMacintosh((_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)

#define vcharScribeLiteral		_vcharScribeLatin1ToMacintosh
#define vcharSizedScribeLiteral		_vcharSizedScribeLatin1ToMacintosh

#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeLiteral(_s)		vcharScribeShared((unsigned char *) (_s))
#define vcharSizedScribeLiteral(_s, _l)	vcharSizedScribeShared((unsigned char *) (_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)

#define vcharScribeLiteral		_vcharScribeWindowsToMacintosh
#define vcharSizedScribeLiteral		_vcharSizedScribeWindowsToMacintosh

#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)

#define vcharScribeLiteral		_vcharScribeUnicodeToMacintosh
#define vcharSizedScribeLiteral		_vcharSizedScribeUnicodeToMacintosh

#endif

#define vcharScribeJISX0208_83		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeJISX0208_83	  _vcharSizedScribeUndefined16ToMacintosh

#define vcharScribeJISX0212		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeJISX0212	  _vcharSizedScribeUndefined16ToMacintosh

#define vcharScribeKSC5601		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeKSC5601 	  _vcharSizedScribeUndefined16ToMacintosh

#define vcharScribeGB2312		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeGB2312  	  _vcharSizedScribeUndefined16ToMacintosh

#define vcharScribeBig5hku 		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeBig5hku    	  _vcharSizedScribeUndefined16ToMacintosh

#define vcharScribeCNS11643		  _vcharScribeUndefined16ToMacintosh
#define vcharSizedScribeCNS11643 	  _vcharSizedScribeUndefined16ToMacintosh

#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS)

#define vcharScribeASCII		_vcharScribeASCIIToWindows
#define vcharScribeASCIIShared		_vcharScribeASCIIToWindows
#define vcharSizedScribeASCII		_vcharSizedScribeASCIIToWindows
#define vcharSizedScribeASCIIShared	_vcharSizedScribeASCIIToWindows

#define vcharScribeASCIIExport		_vcharScribeWindowsToASCII
#define vcharSizedScribeASCIIExport	_vcharSizedScribeWindowsToASCII

#define vcharScribeLatin1		_vcharScribeLatin1ToWindows
#define vcharScribeLatin1Shared		_vcharScribeLatin1ToWindows
#define vcharSizedScribeLatin1		_vcharSizedScribeLatin1ToWindows
#define vcharSizedScribeLatin1Shared	_vcharSizedScribeLatin1ToWindows

#define vcharScribeLatin1Export		_vcharScribeWindowsToLatin1
#define vcharSizedScribeLatin1Export	_vcharSizedScribeWindowsToLatin1

#define vcharScribeMacintosh		_vcharScribeMacintoshToWindows
#define vcharScribeMacintoshShared	_vcharScribeMacintoshToWindows
#define vcharSizedScribeMacintosh 	_vcharSizedScribeMacintoshToWindows
#define vcharSizedScribeMacintoshShared	_vcharSizedScribeMacintoshToWindows

#define vcharScribeMacintoshExport	_vcharScribeWindowsToMacintosh
#define vcharSizedScribeMacintoshExport	_vcharSizedScribeWindowsToMacintosh

#define vcharScribeWindows		vcharScribe
#define vcharScribeWindowsShared	vcharScribeShared
#define vcharSizedScribeWindows 	vcharSizedScribe
#define vcharSizedScribeWindowsShared	vcharSizedScribeShared

#define vcharScribeWindowsExport	vcharScribe
#define vcharSizedScribeWindowsExport	vcharSizedScribe

#define vcharScribeUnicode		_vcharScribeUnicodeToWindows
#define vcharScribeUnicodeShared	_vcharScribeUnicodeToWindows
#define vcharSizedScribeUnicode		_vcharSizedScribeUnicodeToWindows
#define vcharSizedScribeUnicodeShared	_vcharSizedScribeUnicodeToWindows

#define vcharScribeUnicodeExport	_vcharScribeWindowsToUnicode
#define vcharSizedScribeUnicodeExport	_vcharSizedScribeWindowsToUnicode

#if (vportLITERAL_CODESET == vportCODESET_ASCII)

#define vcharScribeLiteral(_s)		_vcharScribeASCIIToWindows((_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeASCIIToWindows((_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)

#define vcharScribeLiteral		_vcharScribeLatin1ToWindows
#define vcharSizedScribeLiteral		_vcharSizedScribeLatin1ToWindows

#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeLiteral		_vcharScribeMacintoshToWindows
#define vcharSizedScribeLiteral		_vcharSizedScribeMacintoshToWindows

#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)

#define vcharScribeLiteral(_s)		vcharScribeShared((unsigned char *) (_s))
#define vcharSizedScribeLiteral(_s, _l)	vcharSizedScribeShared((unsigned char *) (_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)

#define vcharScribeLiteral		_vcharScribeUnicodeToWindows
#define vcharSizedScribeLiteral		_vcharSizedScribeUnicodeToWindows

#endif

#define vcharScribeJISX0208_83		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeJISX0208_83	  _vcharSizedScribeUndefined16ToWindows

#define vcharScribeJISX0212		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeJISX0212	  _vcharSizedScribeUndefined16ToWindows

#define vcharScribeKSC5601		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeKSC5601 	  _vcharSizedScribeUndefined16ToWindows

#define vcharScribeGB2312		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeGB2312  	  _vcharSizedScribeUndefined16ToWindows

#define vcharScribeBig5hku 		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeBig5hku    	  _vcharSizedScribeUndefined16ToWindows

#define vcharScribeCNS11643		  _vcharScribeUndefined16ToWindows
#define vcharSizedScribeCNS11643 	  _vcharSizedScribeUndefined16ToWindows

#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeASCII		_vcharScribeASCIIToUnicode
#define vcharScribeASCIIShared		_vcharScribeASCIIToUnicode
#define vcharSizedScribeASCII		_vcharSizedScribeASCIIToUnicode
#define vcharSizedScribeASCIIShared	_vcharSizedScribeASCIIToUnicode

#define vcharScribeASCIIExport		_vcharScribeUnicodeToASCII
#define vcharSizedScribeASCIIExport	_vcharSizedScribeUnicodeToASCII

#define vcharScribeLatin1		_vcharScribeLatin1ToUnicode
#define vcharScribeLatin1Shared		_vcharScribeLatin1ToUnicode
#define vcharSizedScribeLatin1		_vcharSizedScribeLatin1ToUnicode
#define vcharSizedScribeLatin1Shared	_vcharSizedScribeLatin1ToUnicode

#define vcharScribeLatin1Export		_vcharScribeUnicodeToLatin1
#define vcharSizedScribeLatin1Export	_vcharSizedScribeUnicodeToLatin1

#define vcharScribeMacintosh		_vcharScribeMacintoshToUnicode
#define vcharScribeMacintoshShared	_vcharScribeMacintoshToUnicode
#define vcharSizedScribeMacintosh	_vcharSizedScribeMacintoshToUnicode
#define vcharSizedScribeMacintoshShared	_vcharSizedScribeMacintoshToUnicode

#define vcharScribeMacintoshExport	_vcharScribeUnicodeToMacintosh
#define vcharSizedScribeMacintoshExport	_vcharSizedScribeUnicodeToMacintosh

#define vcharScribeWindows		_vcharScribeWindowsToUnicode
#define vcharScribeWindowsShared	_vcharScribeWindowsToUnicode
#define vcharSizedScribeWindows 	_vcharSizedScribeWindowsToUnicode
#define vcharSizedScribeWindowsShared	_vcharSizedScribeWindowsToUnicode

#define vcharScribeWindowsExport	_vcharScribeUnicodeToWindows
#define vcharSizedScribeWindowsExport	_vcharSizedScribeUnicodeToWindows

#define vcharScribeUnicode		vcharScribe
#define vcharScribeUnicodeShared	vcharScribeShared
#define vcharSizedScribeUnicode		vcharSizedScribe
#define vcharSizedScribeUnicodeShared	vcharSizedScribeShared

#define vcharScribeUnicodeExport	vcharScribe
#define vcharSizedScribeUnicodeExport	vcharSizedScribe

#if (vportLITERAL_CODESET == vportCODESET_ASCII)

#define vcharScribeLiteral(_s)		_vcharScribeASCIIToUnicode((_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeASCIIToUnicode((_s), _l)

#elif (vportLITERAL_CODESET == vportCODESET_LATIN_1)

#define vcharScribeLiteral(_s)		_vcharScribeLatin1ToUnicode((unsigned char *)(_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeLatin1ToUnicode((unsigned char *)(_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_MACINTOSH)

#define vcharScribeLiteral(_s)		_vcharScribeMacintoshToUnicode((unsigned char *)(_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeMacintoshToUnicode((unsigned char *)(_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_WINDOWS)

#define vcharScribeLiteral(_s)		_vcharScribeWindowsToUnicode((unsigned char *)(_s))
#define vcharSizedScribeLiteral(_s, _l)	_vcharSizedScribeWindowsToUnicode((unsigned char *)(_s), (_l))

#elif (vportLITERAL_CODESET == vportCODESET_UNICODE)

#define vcharScribeLiteral		vcharScribeShared
#define vcharSizedScribeLiteral		vcharSizedScribeShared

#endif


#endif

/*****************************************************************************/
#if vdebugDEBUG

#define vcharScribe(_s) \
    vcharScribeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribe(_s, _l) \
    vcharSizedScribeDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribeShared(_s) \
    vcharScribeSharedDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeShared(_s, _l) \
    vcharSizedScribeSharedDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribeSystem(_s) \
    vcharScribeSystemDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharScribeSystemShared(_s) \
    vcharScribeSystemSharedDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeSystem(_s, _l) \
    vcharSizedScribeSystemDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeSystemShared(_s, _l) \
    vcharSizedScribeSystemSharedDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeReplace(_s, _m, _r) \
    vcharScribeReplaceDebug(_s, _m, _r, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeReplace(_s, _sl, _m, _ml, _r, _rl) \
    vcharSizedScribeReplaceDebug(_s, _sl, _m, _ml, _r, _rl, \
				 vmemTAG, __FILE__, __LINE__)

#define vcharScribeReplaceChar(_s, _m, _r) \
    vcharScribeReplaceCharDebug(_s, _m, _r, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeReplaceChar(_s, _sl, _m, _r) \
    vcharSizedScribeReplaceCharDebug(_s, _sl, _m, _r, \
				     vmemTAG, __FILE__, __LINE__)

#define vcharScribeReplaceOneOf(_s, _m, _r) \
    vcharScribeReplaceOneOfDebug(_s, _m, _r, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeReplaceOneOf(_s, _sl, _m, _ml, _r) \
    vcharSizedScribeReplaceOneOfDebug(_s, _sl, _m, _ml, _r, \
				      vmemTAG, __FILE__, __LINE__)

#define vcharScribeReplaceNotOneOf(_s, _m, _r) \
    vcharScribeReplaceNotOneOfDebug(_s, _m, _r, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeReplaceNotOneOf(_s, _sl, _m, _ml, _r) \
    vcharSizedScribeReplaceNotOneOfDebug(_s, _sl, _m, _ml, _r, \
					 vmemTAG, __FILE__, __LINE__)

#define vcharScribeReplaceMap(_s, _m, _r) \
    vcharScribeReplaceMapDebug(_s, _m, _r, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeReplaceMap(_s, _sl, _m, _r, _ml) \
    vcharSizedScribeReplaceMapDebug(_s, _sl, _m, _r, _ml, \
				    vmemTAG, __FILE__, __LINE__)

#define vcharScribeToUpperCase(_s) \
    vcharScribeToUpperCaseDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeToUpperCase(_s, _l) \
    vcharSizedScribeToUpperCaseDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribeToLowerCase(_s) \
    vcharScribeToLowerCaseDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeToLowerCase(_s, _l) \
    vcharSizedScribeToLowerCaseDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribeStripDiacritics(_s) \
    vcharScribeStripDiacriticsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeStripDiacritics(_s, _l) \
    vcharSizedScribeStripDiacriticsDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribeStripToLowerCase(_s) \
    vcharScribeStripToLowerCaseDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeStripToLowerCase(_s, _l) \
    vcharSizedScribeStripToLowerCaseDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharScribePadding(_c, _l) \
    vcharScribePaddingDebug(_c, _l, vmemTAG, __FILE__, __LINE__)
   
#define vcharScribeSystemExport(_s) \
    vcharScribeSystemExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeSystemExport(_s, _l) \
    vcharSizedScribeSystemExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define vcharExportAlloc(_s) \
    vcharExportAllocDebug(_s, vmemTAG, __FILE__, __LINE__)

#define vcharScribeAdobeStdEnc(_s) \
    vcharScribeAdobeStdEncDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeAdobeStdEnc(_s, _l) \
    vcharSizedScribeAdobeStdEncDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeAdobeStdEncExport(_s) \
    vcharScribeAdobeStdEncExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeAdobeStdEncExport(_s, _l) \
    vcharSizedScribeAdobeStdEncExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeAdobeSymbol(_s) \
    vcharScribeAdobeSymbolDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeAdobeSymbol(_s, _l) \
    vcharSizedScribeAdobeSymbolDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeAdobeSymbolExport(_s) \
    vcharScribeAdobeSymbolExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeAdobeSymbolExport(_s, _l) \
    vcharSizedScribeAdobeSymbolExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeBig5hku(_s) \
    vcharScribeBig5hkuDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeBig5hku(_s, _l) \
    vcharSizedScribeBig5hkuDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeBig5hkuExport(_s) \
    vcharScribeBig5hkuExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeBig5hkuExport(_s, _l) \
    vcharSizedScribeBig5hkuExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeCNS11643(_s) \
    vcharScribeCNS11643Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeCNS11643(_s, _l) \
    vcharSizedScribeCNS11643Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeCNS11643Export(_s) \
    vcharScribeCNS11643ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeCNS11643Export(_s, _l) \
    vcharSizedScribeCNS11643ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeCyrillic(_s) \
    vcharScribeCyrillicDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeCyrillic(_s, _l) \
    vcharSizedScribeCyrillicDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeCyrillicExport(_s) \
    vcharScribeCyrillicExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeCyrillicExport(_s, _l) \
    vcharSizedScribeCyrillicExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeDecTech(_s) \
    vcharScribeDecTechDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeDecTech(_s, _l) \
    vcharSizedScribeDecTechDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeDecTechExport(_s) \
    vcharScribeDecTechExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeDecTechExport(_s, _l) \
    vcharSizedScribeDecTechExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeGB2312(_s) \
    vcharScribeGB2312Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeGB2312(_s, _l) \
    vcharSizedScribeGB2312Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeGB2312Export(_s) \
    vcharScribeGB2312ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeGB2312Export(_s, _l) \
    vcharSizedScribeGB2312ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeGreek(_s) \
    vcharScribeGreekDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeGreek(_s, _l) \
    vcharSizedScribeGreekDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeGreekExport(_s) \
    vcharScribeGreekExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeGreekExport(_s, _l) \
    vcharSizedScribeGreekExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeHebrew(_s) \
    vcharScribeHebrewDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeHebrew(_s, _l) \
    vcharSizedScribeHebrewDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeHebrewExport(_s) \
    vcharScribeHebrewExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeHebrewExport(_s, _l) \
    vcharSizedScribeHebrewExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeJISX0201(_s) \
    vcharScribeJISX0201Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0201(_s, _l) \
    vcharSizedScribeJISX0201Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeJISX0201Export(_s) \
    vcharScribeJISX0201ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0201Export(_s, _l) \
    vcharSizedScribeJISX0201ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeJISX0208_83(_s) \
    vcharScribeJISX0208_83Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0208_83(_s, _l) \
    vcharSizedScribeJISX0208_83Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeJISX0208_83Export(_s) \
    vcharScribeJISX0208_83ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0208_83Export(_s, _l) \
    vcharSizedScribeJISX0208_83ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeJISX0212(_s) \
    vcharScribeJISX0212Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0212(_s, _l) \
    vcharSizedScribeJISX0212Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeJISX0212Export(_s) \
    vcharScribeJISX0212ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeJISX0212Export(_s, _l) \
    vcharSizedScribeJISX0212ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeKoi8(_s) \
    vcharScribeKoi8Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeKoi8(_s, _l) \
    vcharSizedScribeKoi8Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeKoi8Export(_s) \
    vcharScribeKoi8ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeKoi8Export(_s, _l) \
    vcharSizedScribeKoi8ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#if  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define vcharScribeKSC5601(_s) \
    vcharScribeKSC5601Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeKSC5601(_s, _l) \
    vcharSizedScribeKSC5601Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* (vportVCHAR_CODESET == vportCODESET_UNICODE) */

#define vcharScribeKSC5601Export(_s) \
    vcharScribeKSC5601ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeKSC5601Export(_s, _l) \
    vcharSizedScribeKSC5601ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin2(_s) \
    vcharScribeLatin2Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin2(_s, _l) \
    vcharSizedScribeLatin2Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin2Export(_s) \
    vcharScribeLatin2ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin2Export(_s, _l) \
    vcharSizedScribeLatin2ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin3(_s) \
    vcharScribeLatin3Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin3(_s, _l) \
    vcharSizedScribeLatin3Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin3Export(_s) \
    vcharScribeLatin3ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin3Export(_s, _l) \
    vcharSizedScribeLatin3ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin4(_s) \
    vcharScribeLatin4Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin4(_s, _l) \
    vcharSizedScribeLatin4Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin4Export(_s) \
    vcharScribeLatin4ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin4Export(_s, _l) \
    vcharSizedScribeLatin4ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin5(_s) \
    vcharScribeLatin5Debug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin5(_s, _l) \
    vcharSizedScribeLatin5Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeLatin5Export(_s) \
    vcharScribeLatin5ExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeLatin5Export(_s, _l) \
    vcharSizedScribeLatin5ExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeViscii(_s) \
    vcharScribeVisciiDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeViscii(_s, _l) \
    vcharSizedScribeVisciiDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define vcharScribeVisciiExport(_s) \
    vcharScribeVisciiExportDebug(_s, vmemTAG, __FILE__, __LINE__)
#define vcharSizedScribeVisciiExport(_s, _l) \
    vcharSizedScribeVisciiExportDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define _vcharScribeASCIIToLatin1(_s) \
    _vcharScribeASCIIToLatin1Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeASCIIToLatin1(_s, _l) \
    _vcharSizedScribeASCIIToLatin1Debug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeLatin1ToASCII(_s) \
    _vcharScribeLatin1ToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeLatin1ToASCII(_s, _l) \
    _vcharSizedScribeLatin1ToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeASCIIToMacintosh(_s) \
    _vcharScribeASCIIToMacintoshDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeASCIIToMacintosh(_s, _l) \
    _vcharSizedScribeASCIIToMacintoshDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeMacintoshToASCII(_s) \
    _vcharScribeMacintoshToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeMacintoshToASCII(_s, _l) \
    _vcharSizedScribeMacintoshToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeASCIIToWindows(_s) \
    _vcharScribeASCIIToWindowsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeASCIIToWindows(_s, _l) \
    _vcharSizedScribeASCIIToWindowsDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeWindowsToASCII(_s) \
    _vcharScribeWindowsToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeWindowsToASCII(_s, _l) \
    _vcharSizedScribeWindowsToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeASCIIToUnicode(_s) \
    _vcharScribeASCIIToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeASCIIToUnicode(_s, _l) \
    _vcharSizedScribeASCIIToUnicodeDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeUnicodeToASCII(_s) \
    _vcharScribeUnicodeToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToASCII(_s, _l) \
    _vcharSizedScribeUnicodeToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeLatin1ToMacintosh(_s) \
    _vcharScribeLatin1ToMacintoshDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeLatin1ToMacintosh(_s, _l) \
    _vcharSizedScribeLatin1ToMacintoshDebug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeMacintoshToLatin1(_s) \
    _vcharScribeMacintoshToLatin1Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeMacintoshToLatin1(_s, _l) \
    _vcharSizedScribeMacintoshToLatin1Debug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeLatin1ToWindows(_s) \
    _vcharScribeLatin1ToWindowsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeLatin1ToWindows(_s, _l) \
    _vcharSizedScribeLatin1ToWindowsDebug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeWindowsToLatin1(_s) \
    _vcharScribeWindowsToLatin1Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeWindowsToLatin1(_s, _l) \
    _vcharSizedScribeWindowsToLatin1Debug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeLatin1ToUnicode(_s) \
    _vcharScribeLatin1ToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeLatin1ToUnicode(_s, _l) \
    _vcharSizedScribeLatin1ToUnicodeDebug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeUnicodeToLatin1(_s) \
    _vcharScribeUnicodeToLatin1Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToLatin1(_s, _l) \
    _vcharSizedScribeUnicodeToLatin1Debug(_s, _l, vmemTAG, __FILE__, __LINE__)
    
#define _vcharScribeMacintoshToWindows(_s) \
    _vcharScribeMacintoshToWindowsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeMacintoshToWindows(_s, _l) \
    _vcharSizedScribeMacintoshToWindowsDebug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeWindowsToMacintosh(_s) \
    _vcharScribeWindowsToMacintoshDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeWindowsToMacintosh(_s, _l) \
    _vcharSizedScribeWindowsToMacintoshDebug(_s, _l, vmemTAG, __FILE__,__LINE__)
    
#define _vcharScribeMacintoshToUnicode(_s) \
    _vcharScribeMacintoshToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeMacintoshToUnicode(_s, _l) \
    _vcharSizedScribeMacintoshToUnicodeDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeUnicodeToMacintosh(_s) \
    _vcharScribeUnicodeToMacintoshDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToMacintosh(_s, _l) \
    _vcharSizedScribeUnicodeToMacintoshDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeWindowsToUnicode(_s) \
    _vcharScribeWindowsToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeWindowsToUnicode(_s, _l) \
    _vcharSizedScribeWindowsToUnicodeDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeUnicodeToWindows(_s) \
    _vcharScribeUnicodeToWindowsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToWindows(_s, _l) \
    _vcharSizedScribeUnicodeToWindowsDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeCodepage437ToUnicode(_s) \
    _vcharScribeCodepage437ToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeCodepage437ToUnicode(_s, _l) \
    _vcharSizedScribeCodepage437ToUnicodeDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeUnicodeToCodepage437(_s) \
    _vcharScribeUnicodeToCodepage437Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToCodepage437(_s, _l) \
    _vcharSizedScribeUnicodeToCodepage437Debug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeCodepage850ToUnicode(_s) \
    _vcharScribeCodepage850ToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeCodepage850ToUnicode(_s, _l) \
    _vcharSizedScribeCodepage850ToUnicodeDebug(_s, _l, vmemTAG,__FILE__,__LINE__)

#define _vcharScribeUnicodeToCodepage850(_s) \
    _vcharScribeUnicodeToCodepage850Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUnicodeToCodepage850(_s, _l) \
    _vcharSizedScribeUnicodeToCodepage850Debug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
/* system scribes: SJIS, JEUC, KEUC, CEUC, TEUC, UTF */

#define _vcharScribeVcharToSJIS(_s) \
    _vcharScribeVcharToSJISDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToSJIS(_s, _l) \
    _vcharSizedScribeVcharToSJISDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeSJISToVchar(_s) \
    _vcharScribeSJISToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeSJISToVchar(_s, _l) \
    _vcharSizedScribeSJISToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeVcharToJEUC(_s) \
    _vcharScribeVcharToJEUCDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToJEUC(_s, _l) \
    _vcharSizedScribeVcharToJEUCDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeJEUCToVchar(_s) \
    _vcharScribeJEUCToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeJEUCToVchar(_s, _l) \
    _vcharSizedScribeJEUCToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeVcharToKEUC(_s) \
    _vcharScribeVcharToKEUCDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToKEUC(_s, _l) \
    _vcharSizedScribeVcharToKEUCDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeKEUCToVchar(_s) \
    _vcharScribeKEUCToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeKEUCToVchar(_s, _l) \
    _vcharSizedScribeKEUCToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeVcharToUTF(_s) \
    _vcharScribeVcharToUTFDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToUTF(_s, _l) \
    _vcharSizedScribeVcharToUTFDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeUTFToVchar(_s) \
    _vcharScribeUTFToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUTFToVchar(_s, _l) \
    _vcharSizedScribeUTFToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeVcharToCEUC(_s) \
    _vcharScribeVcharToCEUCDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToCEUC(_s, _l) \
    _vcharSizedScribeVcharToCEUCDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeCEUCToVchar(_s) \
    _vcharScribeCEUCToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeCEUCToVchar(_s, _l) \
    _vcharSizedScribeCEUCToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeVcharToTEUC(_s) \
    _vcharScribeVcharToTEUCDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeVcharToTEUC(_s, _l) \
    _vcharSizedScribeVcharToTEUCDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
#define _vcharScribeTEUCToVchar(_s) \
    _vcharScribeTEUCToVcharDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeTEUCToVchar(_s, _l) \
    _vcharSizedScribeTEUCToVcharDebug(_s, _l, vmemTAG,__FILE__,__LINE__)
    
/* other 8-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

#define _vcharScribeLAT8ToASCII(_s) \
    _vcharScribeLAT8ToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeLAT8ToASCII(_s, _l) \
    _vcharSizedScribeLAT8ToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#define _vcharScribeASCIIToLAT8(_s) \
    _vcharScribeASCIIToLAT8Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeASCIIToLAT8(_s, _l) \
    _vcharSizedScribeASCIIToLAT8Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif  /* vportVCHAR_CODESET */

/* other 16-bit encoding scribes */

#if  (vportVCHAR_CODESET == vportCODESET_ASCII)

#define _vcharScribeUndefined16ToASCII(_s) \
    _vcharScribeUndefined16ToASCIIDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUndefined16ToASCII(_s, _l) \
    _vcharSizedScribeUndefined16ToASCIIDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#elif  (vportVCHAR_CODESET == vportCODESET_LATIN_1)

#define _vcharScribeUndefined16ToLatin1(_s) \
    _vcharScribeUndefined16ToLatin1Debug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUndefined16ToLatin1(_s, _l) \
    _vcharSizedScribeUndefined16ToLatin1Debug(_s, _l, vmemTAG, __FILE__, __LINE__)

#elif  (vportVCHAR_CODESET == vportCODESET_MACINTOSH)

#define _vcharScribeUndefined16ToMacintosh(_s) \
    _vcharScribeUndefined16ToMacintoshDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUndefined16ToMacintosh(_s, _l) \
    _vcharSizedScribeUndefined16ToMacintoshDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#elif  (vportVCHAR_CODESET == vportCODESET_WINDOWS)

#define _vcharScribeUndefined16ToWindows(_s) \
    _vcharScribeUndefined16ToWindowsDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUndefined16ToWindows(_s, _l) \
    _vcharSizedScribeUndefined16ToWindowsDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#elif  (vportVCHAR_CODESET == vportCODESET_UNICODE)

#define _vcharScribeUndefined16ToUnicode(_s) \
    _vcharScribeUndefined16ToUnicodeDebug(_s, vmemTAG, __FILE__, __LINE__)
#define _vcharSizedScribeUndefined16ToUnicode(_s, _l) \
    _vcharSizedScribeUndefined16ToUnicodeDebug(_s, _l, vmemTAG, __FILE__, __LINE__)

#endif /* vportVCHAR_CODESET */

#endif /* vdebugDEBUG */
    
    
/*
 * Compatibility macros for old versions of string manager
 * (Don't use these!)
 */

#define vcharScribeCopy			vcharScribbleCopy
#define vcharSizedScribeCopy		vcharSizedScribbleCopy
#define vcharGetScribedLengthSame	vcharGetScribbledLengthSame
#define vcharSizedGetScribedLengthSame	vcharSizedGetScribbledLengthSame



vportEND_CPLUSPLUS_EXTERN_C


#endif /* vcharINCLUDED */
    

