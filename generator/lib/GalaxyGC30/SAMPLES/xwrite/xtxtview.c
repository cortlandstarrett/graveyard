/* $Id: xtxtview.c,v 1.7 1997/09/23 17:59:57 dimitri Exp $ */

/************************************************************

    xtxtview.c
    C Source to xtxtview

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  xtxtviewINCLUDED
#include "xtxtview.h"
#endif

#if vdebugDEBUG
#define vdebugTAG "xtxtview"
#endif

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/* 
 * Command selectors 
 */

enum {
   _xtxtviewKEYBOARD_ASCII       =  0,
   _xtxtviewKEYBOARD_GREEK,
   _xtxtviewKEYBOARD_CYRILLIC,
   _xtxtviewKEYBOARD_HIRAGANA,
   _xtxtviewKEYBOARD_HEX
};


/*
 * Compose state
 */

enum 
{
   _xtxtviewCOMPOSE_OFF      =  0,
   _xtxtviewCOMPOSE_ON_QU,              /* starting with QUOTE */
   _xtxtviewCOMPOSE_ON_UQ               /* starting with other than QUOTE */
};

/*
 *  The internal special characters representation
 */

#define _xtxtviewQUOTE                  (vcharFromLiteral('\\'))
#define _xtxtviewTONOS                  (vcharFromLiteral('`'))
#define _xtxtviewDIALYTIKA              (vcharFromLiteral('='))

#define vALT_COMMAND(k) \
    vkeyComputeStroke(k, vkeyMODIFIER_KEY_ALT|vkeyMODIFIER_KEY_COMMAND)


#define        _xtxtviewGetDataComposeState(f)     \
                                    ((f)->composeState)
#define        _xtxtviewSetDataComposeState(f, n)  \
                                    ((f)->composeState = (n))

#define        _xtxtviewResetDataBuffer(f)         \
                                    ((f)->bufferLength = 0)

#define        _xtxtviewGetDataBuffer(f)           \
                                    ((f)->buffer)

#define        _xtxtviewGetDataKeyboardStatus(f)       \
                                    ((f)->currentStatus)
#define        _xtxtviewSetDataKeyboardStatus(f, s)    \
                                    ((f)->currentStatus = (s))

#define        _xtxtviewSaveDataKeyboardStatus(f)      \
                                    ((f)->savedStatus = (f)->currentStatus)
#define        _xtxtviewRestoreDataKeyboardStatus(f)   \
                                    ((f)->currentStatus = (f)->savedStatus)

/* 
 * * * * * * * * * * * * * private types* * * * * * * * * * * * * * * * * * 
 */

typedef struct commandInitializer commandInitializer;

struct commandInitializer 
{
   const char *tag;
   short       value;
   vkeyStroke  key;
   vbool       state;
   vbool       dispatch;
};

typedef struct composeRecord composeRecord;

struct composeRecord{
   const char      *key;
   vbool           erase;
   vbyte           nextState;
   unsigned short  emit;
};


typedef struct composeDriver composeDriver;

struct composeDriver
{
   vchar              (*appendTransformer)(int ch);
   vchar              (*outputTransformer)(int ch);
   vbool              (*composeKeyCheck)(int ch);
   vdict               *composeDict;
   composeRecord       *composeDefs;
};



typedef struct _xtxtviewData _xtxtviewData;

struct _xtxtviewData
{
    int    savedStatus;
    int    currentStatus;
    int    composeState;         
    vchar  buffer[5];            /* more? */
    int    bufferLength;
};

typedef int  (*textviewHandleFunc)(vtextview *, vevent *);

typedef void (*textviewGenericFunc)(vtextview *);


/*
 * * * * * * * * * * * * * prototypes * * * * * * * * * * * 
 */


#if vdebugDEBUG
static _xtxtviewData *_xtxtviewDataCreateDebug(const char *tag, 
						 const char *file, int line);
#define _xtxtviewDataCreate()    \
   _xtxtviewDataCreateDebug(vmemTAG, __FILE__, __LINE__)

#else
static _xtxtviewData *_xtxtviewDataCreate(void);
#endif

vchar _xtxtviewIdentity(int ch);
vchar _xtxtviewToLowerCase(int ch);
vchar _xtxtviewMapGreek(int ch);
vbool _xtxtviewComposeKeyCheckGreek(int ch);
vbool _xtxtviewComposeKeyCheckHiragana(int ch);

/*
 * * * * * * * * * * * * * public variables * * * * * * * * * * * * * * * * 
 */


/*
 *  The external special characters representation
 */

vchar xtxtviewQuote;
vchar xtxtviewTonos;
vchar xtxtviewDialytika;

/*
 * * * * * * * * * * * * * private variables * * * * * * * * * * * * * * * * 
 */

/*
 *  The following table maps keys A through Z of the US keyboard
 *  to the letters of the Greek alphabet following the layout of
 *  the greek typewriter:
 *
 *  A -->  Alpha                 Alpha   -->  A
 *  B -->  Beta                  Beta    -->  B
 *  C -->  Psi                   Gamma   -->  G
 *  D -->  Delta                 Delta   -->  D
 *  E -->  Epsilon               Epsilon -->  E
 *  F -->  Phi                   Zeta    -->  Z
 *  G -->  Gamma                 Eta     -->  H
 *  H -->  Eta                   Theta   -->  U
 *  I -->  Iota                  Iota    -->  I
 *  J -->  Ksi                   Kappa   -->  K
 *  K -->  Kappa                 Lambda  -->  L
 *  L -->  Lambda                Mu      -->  M
 *  M -->  Mu                    Nu      -->  N
 *  N -->  Nu                    Ksi     -->  J
 *  O -->  Omicron               Omicron -->  O
 *  P -->  Pi                    Pi      -->  P
 *  Q -->  note:                 Rho     -->  R
 *  R -->  Rho                   Sigma   -->  S, note:
 *  S -->  Sigma                 Tau     -->  T
 *  T -->  Tau                   Ypsilon -->  Y
 *  U -->  Theta                 Phi     -->  F
 *  V -->  Omega                 Khi     -->  X
 *  W -->  note:                 Psi     -->  C
 *  X -->  Khi                   Omega   -->  V
 *  Y -->  Ypsilon
 *  Z -->  Zeta
 *
 *  note:
 *         w  <---> lower case final sigma
 *
 *  and non-standard mappings:
 *
 *         W  <---> upper case Ypsilon-dialytika
 *
 *         q  <---> lower case iota-tonos-dialytika
 *         Q  <---> lower case upsilon-tonos-dialytika
 *
 *
 */

static const unsigned short _xtxtviewASCIIToGreekTable[] = 
{
       /*     0       1	      2	      3	      4	      5	      6	      7  */
       /*     8       9	      A	      B	      C	      D	      E	      F  */
/*0x00*/   0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,
	   0x08,   0x09,   0x0a,   0x0b,   0x0c,   0x0d,   0x0e,   0x0f,   
/*0x10*/   0x10,   0x11,   0x12,   0x13,   0x14,   0x15,   0x16,   0x17,   
	   0x18,   0x19,   0x1a,   0x1b,   0x1c,   0x1d,   0x1e,   0x1f,   
/*0x20*/   0x20,   0x21,   0x22,   0x23,   0x24,   0x25,   0x26,   0x27,   
	   0x28,   0x29,   0x2a,   0x2b,   0x2c,   0x2d,   0x2e,   0x2f,   
/*0x30*/   0x30,   0x31,   0x32,   0x33,   0x34,   0x35,   0x36,   0x37,   
	   0x38,   0x39,   0x3a,   0x3b,   0x3c,   0x3d,   0x3e,   0x3f,   
/*0x40*/   0x40, 0x0391, 0x0392, 0x03a8, 0x0394, 0x0395, 0x03a6, 0x0393, 
         0x0397, 0x0399, 0x039e, 0x039a, 0x039b, 0x039c, 0x039d, 0x039f,
/*0x50*/ 0x03a0, 0x03b0, 0x03a1, 0x03a3, 0x03a4, 0x0398, 0x03a9, 0x03AB,   
	 0x03a7, 0x03a5, 0x0396,   0x5b,   0x5c,   0x5d,   0x5e,   0x5f,   
/*0x60*/   0x60, 0x03B1, 0x03B2, 0x03C8, 0x03B4, 0x03B5, 0x03C6, 0x03B3, 
         0x03B7, 0x03B9, 0x03Be, 0x03Ba, 0x03Bb, 0x03Bc, 0x03Bd, 0x03Bf,
/*0x70*/ 0x03C0, 0x0390, 0x03C1, 0x03C3, 0x03C4, 0x03B8, 0x03C9, 0x03c2,   
	 0x03C7, 0x03C5, 0x03B6,   0x7b,   0x7c,   0x7d,   0x7e,   0x7f
};

/*
 *
 *  Two alternatives are offered for a russian keyboard:
 *  one that matches the Russian typewriter (JCUKENG)
 *  and one that is closer "visually" to the English keyboard
 *  (YAWERTY).  In this code, the first one is activated.
 *
 *        ----------------------------------------------
 *        | English        Russian         Mixed      |
 *        | keyboard       keyboard       keyboard    |
 *        |                                           |
 *        |  qwerty         jcuken        yawerty     |
 *        |-------------------------------------------|
 *        |   q Q      i-short I-short     ya Ya      |
 *        |   w W          tse Tse         ve ve      |
 *        |   e E            u U           ie Ie      |
 *        |   r R           ka Ka          ar Er      |
 *        |   t T           ie Ie          te Te      |
 *        |   y Y           en En        iery Iery    |
 *        |   u U          ghe Ghe          u U       |
 *        |   i I          sha Sha          i I       |
 *        |   o O        shcha Shcha        o O       |
 *        |   p P            z Z           pe Pe      |
 *        |   a A           ef Ef           a A       |
 *        |   s S         iery Iery        es Es      |
 *        |   d D           ve ve          de De      |
 *        |   f F            a A           ef Ef      |
 *        |   g G           pe Pe          ge Ge      |
 *        |   h H           er Er         kha Kha     |
 *        |   j J            o O      i-short I-short |
 *        |   k K           el El          ka Ka      |
 *        |   l L           de De          el El      |
 *        |   z Z           ya Ya           z Z       |
 *        |   x X          che Che        ier Ier     |
 *        |   c C           es Es         tse Tse     |
 *        |   v V           em Em         zhe Zhe     |
 *        |   b B            i I           be Be      |
 *        |   n N           te Te          en En      |
 *        |   m M        ierik Ierik       em Em      |
 *        |                                           |
 *        |   [ {          kha Kha        sha Sha     |
 *        |   ] }          ier Ier      shcha Shcha   |
 *        |   ; :          zhe Zhe                    |
 *        |   ' "        e-rev E-rev                  |
 *        |   , <           be Be                     |
 *        |   . >           yu Yu                     |
 *        |   ` ~           yo Yo          yu Yu      |
 *        |   3 #                           3 ier     |
 *        |   4 $            4 "                      |
 *        |   5 %            5 :                      |
 *        |   6 ^            6 ,                      |
 *        |   7 &            7 .                      |
 *        |   = +                         che Che     |
 *        |   \ |                       e-rev E-rev   |
 *        ---------------------------------------------
 *
 */


/*********************************************************************
 *
 * ASCII to Cyrillic JCUKENG
 *
 */

static unsigned short _xtxtviewASCIIToJCUKENGCyrillicTable[] = 
{
  0x00,     0x01,     0x02,     0x03,     0x04,     0x05,     0x06,     0x07,
  0x08,     0x09,     0x0A,     0x0B,     0x0C,     0x0D,     0x0E,     0x0F,  
  0x10,     0x11,     0x12,     0x13,     0x14,     0x15,     0x16,     0x17,  
  0x18,     0x19,     0x1A,     0x1B,     0x1C,     0x1D,     0x1E,     0x1F,  
  0x20,     0x21,   0x042D,     0x23,     0x22,     0x3A,     0x2E,   0x044D,  
  0x28,     0x29,     0x2A,     0x2B,   0x0431,     0x2D,   0x044E,     0x2F,  
  0x30,     0x31,     0x32,     0x33,     0x34,     0x35,     0x36,     0x37,  
  0x38,     0x39,   0x0416,   0x0436,   0x0411,     0x3D,   0x042E,     0x3F,  
  0x40,   0x0424,   0x0418,   0x0421,   0x0412,   0x0423,   0x0410,   0x041F,  
0x0420,   0x0428,   0x041E,   0x041B,   0x0414,   0x042C,   0x0422,   0x0429,  
0x0417,   0x0419,   0x041A,   0x042B,   0x0415,   0x0413,   0x041C,   0x0426,  
0x0427,   0x041D,   0x042F,   0x0445,     0x5C,   0x044A,     0x2C,     0x5F,  
0x0451,   0x0444,   0x0438,   0x0441,   0x0432,   0x0443,   0x0430,   0x043F,  
0x0440,   0x0448,   0x043E,   0x043B,   0x0434,   0x044C,   0x0442,   0x0449,  
0x0437,   0x0439,   0x043A,   0x044B,   0x0435,   0x0433,   0x043C,   0x0446,  
0x0447,   0x043D,   0x044F,   0x0425,     0x7C,   0x042A,   0x0401,     0x7F 
};

/******************************************************************
 *
 * ASCII to Cyrillic YAWERTY
 *
 *

static unsigned short _xtxtviewASCIIToYAWERTYCyrillicTable[] = 
{
  0x00,     0x01,     0x02,     0x03,     0x04,     0x05,     0x06,     0x07,
  0x08,     0x09,     0x0A,     0x0B,     0x0C,     0x0D,     0x0E,     0x0F,
  0x10,     0x11,     0x12,     0x13,     0x14,     0x15,     0x16,     0x17,
  0x18,     0x19,     0x1A,     0x1B,     0x1C,     0x1D,     0x1E,     0x1F,
  0x20,     0x21,     0x22,   0x044A,   0x042A,     0x25,     0x26,     0x27,
  0x28,     0x29,     0x2A,   0x0427,     0x2C,     0x2D,     0x2E,     0x2F,
  0x30,     0x31,     0x32,     0x33,     0x34,     0x35,     0x36,     0x37,
  0x38,     0x39,     0x3A,     0x3B,     0x3C,   0x0447,     0x3E,     0x3F,
  0x40,   0x0410,   0x0411,   0x0426,   0x0414,   0x0415,   0x0424,   0x0413,
0x0425,   0x0418,   0x0419,   0x041A,   0x041B,   0x041C,   0x041D,   0x041E,
0x041F,   0x042F,   0x0420,   0x0421,   0x0422,   0x0423,   0x0416,   0x0412,
0x042C,   0x042B,   0x0417,   0x0448,   0x044D,   0x0449,     0x5E,     0x5F,
0x044E,   0x0430,   0x0431,   0x0446,   0x0434,   0x0435,   0x0444,   0x0433,
0x0445,   0x0438,   0x0439,   0x043A,   0x043B,   0x043C,   0x043D,   0x043E,
0x043F,   0x044F,   0x0440,   0x0441,   0x0442,   0x0443,   0x0436,   0x0432,
0x044C,   0x044B,   0x0437,   0x0428,   0x042D,   0x0429,   0x042E,     0x7F
};

*******************************************************************/

static vpool                     *_xtxtviewPool                        = NULL;
static vdict                     *_xtxtviewDict                        = NULL;
static vdict                     *_xtxtviewComposeDictGreek            = NULL;
static vdict                     *_xtxtviewComposeDictHiragana         = NULL;

static textviewHandleFunc         defaultTextviewKeyDownHandler;
static textviewHandleFunc         defaultTextviewButtonDownHandler;

static textviewGenericFunc        defaultTextviewFocusLose;
static textviewGenericFunc        defaultTextviewDestroy;

static vcommandSelectorClass     *_xtxtviewSelectorClass = NULL;

static vbool                      _xtxtviewRemapKeyboard = 
                                       (vcharMAX < 256) ? vFALSE : vTRUE; 



static vbyte                      _xtxtviewHexMax = (vcharMAX < 256) ? 2 : 4;

/*
 * HEX input is done per application;
 * at any point in time, only one textview can be in HEX input mode;
 * HEX input is silently aborted on focus lose, button down events
 * and restarted on "switch to HEX" commands.
 *
 * _xtxtviewHexMax   : the number of hex digits required to input a vchar;
 *                      2 for 8-bit libraries, 4 for Unicode libraries.
 * _xtxtviewHexCount : the number of hex digits still remaining for
 *                      the vchar in input progress.
 * _xtxtviewHexFail  : TRUE if one of the characters keyed in is not
 *                      a hex digit.
 * _xtxtviewHexLock  : flipped when a textview first goes into hex input mode,
 *                      useful in the KeyDownHandler.
 * _xtxtviewHexChar  : accumulator for the vchar currently being inputed.
 *
 */
static vbyte                      _xtxtviewHexCount;
static vbool                      _xtxtviewHexFail        = vFALSE;
static vbool                      _xtxtviewHexLock        = vFALSE;
static vchar                      _xtxtviewHexChar        = vcharNULL;

static commandInitializer         _xtxtviewCommands[] = 
{
   {
      "keyboardASCII",    _xtxtviewKEYBOARD_ASCII,    vALT_COMMAND('a'),  
      vTRUE,              vTRUE
   },
   {
      "keyboardGREEK",    _xtxtviewKEYBOARD_GREEK,    vALT_COMMAND('g'),
      vTRUE,              vTRUE
   },
   {
      "keyboardCYRILLIC", _xtxtviewKEYBOARD_CYRILLIC, vALT_COMMAND('c'),
      vTRUE,              vTRUE
   },
   {
      "keyboardHIRAGANA", _xtxtviewKEYBOARD_HIRAGANA, vALT_COMMAND('h'),
      vTRUE,              vTRUE
   },
   {
      "keyboardHEX",      _xtxtviewKEYBOARD_HEX,      vALT_COMMAND('x'),
      vTRUE,              vTRUE
   },

   {NULL}
};

/*
 * compose string definitions; the entry at position 0 is a throwaway
 * because we cannot store index 0 in a vdict.
 */


static composeRecord                _xtxtviewComposeDefsGreek[] =
{
   {"zzzz",    0, _xtxtviewCOMPOSE_OFF,    vcharUNDEFINED},

   {"\\",      0, _xtxtviewCOMPOSE_ON_QU,  vcharUNDEFINED},
   {"\\#",     0, _xtxtviewCOMPOSE_OFF,    0x00AD        },
   {"\\\'",    0, _xtxtviewCOMPOSE_OFF,    0x2019        },
   {"\\+",     0, _xtxtviewCOMPOSE_ON_QU,  0x002B        },
   {"\\+-",    1, _xtxtviewCOMPOSE_OFF,    0x00B1        },
   {"\\-",     0, _xtxtviewCOMPOSE_OFF,    0x00AD        },
   {"\\.",     0, _xtxtviewCOMPOSE_OFF,    0x00B7        },
   {"\\0",     0, _xtxtviewCOMPOSE_OFF,    0x00B0        },
   {"\\1",     0, _xtxtviewCOMPOSE_ON_QU,  0x0031        },
   {"\\12",    1, _xtxtviewCOMPOSE_OFF,    0x00BD        },
   {"\\2",     0, _xtxtviewCOMPOSE_OFF,    0x00B2        },
   {"\\3",     0, _xtxtviewCOMPOSE_OFF,    0x00B3        },
   {"\\:",     0, _xtxtviewCOMPOSE_OFF,    0x00A8        },
   {"\\<",     0, _xtxtviewCOMPOSE_OFF,    0x00AB        },
   {"\\>",     0, _xtxtviewCOMPOSE_OFF,    0x00BB        },
   {"\\C",     0, _xtxtviewCOMPOSE_OFF,    0x00A9        },
   {"\\S",     0, _xtxtviewCOMPOSE_OFF,    0x00A7        },
   {"\\_",     0, _xtxtviewCOMPOSE_OFF,    0x2015        },
   {"\\`",     0, _xtxtviewCOMPOSE_OFF,    0x201B        },
   {"\\c",     0, _xtxtviewCOMPOSE_OFF,    0x00A2        },
   {"\\|",     0, _xtxtviewCOMPOSE_OFF,    0x00A6        },
   {"\\~",     0, _xtxtviewCOMPOSE_OFF,    0x00AC        },

   {"`",       0, _xtxtviewCOMPOSE_ON_UQ,  0x0384        },
   {"`=",      1, _xtxtviewCOMPOSE_ON_UQ,  0x0385        },
   {"`=i",     1, _xtxtviewCOMPOSE_OFF,    0x0390        },
   {"`=y",     1, _xtxtviewCOMPOSE_OFF,    0x03B0        },
   {"`A",      1, _xtxtviewCOMPOSE_OFF,    0x0386        },
   {"`E",      1, _xtxtviewCOMPOSE_OFF,    0x0388        },
   {"`H",      1, _xtxtviewCOMPOSE_OFF,    0x0389        },
   {"`I",      1, _xtxtviewCOMPOSE_OFF,    0x038A        },
   {"`O",      1, _xtxtviewCOMPOSE_OFF,    0x038C        },
   {"`V",      1, _xtxtviewCOMPOSE_OFF,    0x038F        },
   {"`Y",      1, _xtxtviewCOMPOSE_OFF,    0x038E        },
   {"`a",      1, _xtxtviewCOMPOSE_OFF,    0x03AC        },
   {"`e",      1, _xtxtviewCOMPOSE_OFF,    0x03AD        },
   {"`h",      1, _xtxtviewCOMPOSE_OFF,    0x03AE        },
   {"`i",      1, _xtxtviewCOMPOSE_OFF,    0x03AF        },
   {"`o",      1, _xtxtviewCOMPOSE_OFF,    0x03CC        },
   {"`v",      1, _xtxtviewCOMPOSE_OFF,    0x03CE        },
   {"`y",      1, _xtxtviewCOMPOSE_OFF,    0x03CD        },

   {"=",       0, _xtxtviewCOMPOSE_ON_UQ,  0x00A8        },
   {"=`",      1, _xtxtviewCOMPOSE_ON_UQ,  0x0385        },
   {"=`i",     1, _xtxtviewCOMPOSE_OFF,    0x0390        },
   {"=`y",     1, _xtxtviewCOMPOSE_OFF,    0x03B0        },
   {"=I",      1, _xtxtviewCOMPOSE_OFF,    0x03AA        },
   {"=Y",      1, _xtxtviewCOMPOSE_OFF,    0x03AB        },
   {"=i",      1, _xtxtviewCOMPOSE_OFF,    0x03CA        },
   {"=y",      1, _xtxtviewCOMPOSE_OFF,    0x03CB        },

   { NULL }
};



static composeRecord                _xtxtviewComposeDefsHiragana[] =
{
   {"zzzz",    0, _xtxtviewCOMPOSE_OFF,    vcharUNDEFINED},

   {"\\",      0, _xtxtviewCOMPOSE_ON_QU,  vcharUNDEFINED},

   {"k",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"g",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"s",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"z",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"t",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"d",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"h",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"b",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"p",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"m",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"y",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"r",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"w",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"v",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },

   {"x",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"xt",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"xy",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"xw",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },

   {"xa",      1, _xtxtviewCOMPOSE_OFF,    0x3041        },
   {"a",       0, _xtxtviewCOMPOSE_OFF,    0x3042        },
   {"xi",      1, _xtxtviewCOMPOSE_OFF,    0x3043        },
   {"i",       0, _xtxtviewCOMPOSE_OFF,    0x3044        },
   {"xu",      1, _xtxtviewCOMPOSE_OFF,    0x3045        },
   {"u",       0, _xtxtviewCOMPOSE_OFF,    0x3046        },
   {"xe",      1, _xtxtviewCOMPOSE_OFF,    0x3047        },
   {"e",       0, _xtxtviewCOMPOSE_OFF,    0x3048        },
   {"xo",      1, _xtxtviewCOMPOSE_OFF,    0x3049        },
   {"o",       0, _xtxtviewCOMPOSE_OFF,    0x304A        },

   {"ka",      1, _xtxtviewCOMPOSE_OFF,    0x304B        },
   {"ga",      1, _xtxtviewCOMPOSE_OFF,    0x304C        },
   {"ki",      1, _xtxtviewCOMPOSE_OFF,    0x304D        },
   {"gi",      1, _xtxtviewCOMPOSE_OFF,    0x304E        },
   {"ku",      1, _xtxtviewCOMPOSE_OFF,    0x304F        },
   {"gu",      1, _xtxtviewCOMPOSE_OFF,    0x3050        },
   {"ke",      1, _xtxtviewCOMPOSE_OFF,    0x3051        },
   {"ge",      1, _xtxtviewCOMPOSE_OFF,    0x3052        },
   {"ko",      1, _xtxtviewCOMPOSE_OFF,    0x3053        },
   {"go",      1, _xtxtviewCOMPOSE_OFF,    0x3054        },
   {"sa",      1, _xtxtviewCOMPOSE_OFF,    0x3055        },
   {"za",      1, _xtxtviewCOMPOSE_OFF,    0x3056        },
   {"si",      1, _xtxtviewCOMPOSE_OFF,    0x3057        },
   {"zi",      1, _xtxtviewCOMPOSE_OFF,    0x3058        },
   {"su",      1, _xtxtviewCOMPOSE_OFF,    0x3059        },
   {"zu",      1, _xtxtviewCOMPOSE_OFF,    0x305A        },
   {"se",      1, _xtxtviewCOMPOSE_OFF,    0x305B        },
   {"ze",      1, _xtxtviewCOMPOSE_OFF,    0x305C        },
   {"so",      1, _xtxtviewCOMPOSE_OFF,    0x305D        },
   {"zo",      1, _xtxtviewCOMPOSE_OFF,    0x305E        },
   {"ta",      1, _xtxtviewCOMPOSE_OFF,    0x305F        },
   {"da",      1, _xtxtviewCOMPOSE_OFF,    0x3060        },
   {"ti",      1, _xtxtviewCOMPOSE_OFF,    0x3061        },
   {"di",      1, _xtxtviewCOMPOSE_OFF,    0x3062        },
   {"xtu",     2, _xtxtviewCOMPOSE_OFF,    0x3063        },
   {"tu",      1, _xtxtviewCOMPOSE_OFF,    0x3064        },
   {"du",      1, _xtxtviewCOMPOSE_OFF,    0x3065        },
   {"te",      1, _xtxtviewCOMPOSE_OFF,    0x3066        },
   {"de",      1, _xtxtviewCOMPOSE_OFF,    0x3067        },
   {"to",      1, _xtxtviewCOMPOSE_OFF,    0x3068        },
   {"do",      1, _xtxtviewCOMPOSE_OFF,    0x3069        },
   {"na",      1, _xtxtviewCOMPOSE_OFF,    0x306A        },
   {"ni",      1, _xtxtviewCOMPOSE_OFF,    0x306B        },
   {"nu",      1, _xtxtviewCOMPOSE_OFF,    0x306C        },
   {"ne",      1, _xtxtviewCOMPOSE_OFF,    0x306D        },
   {"no",      1, _xtxtviewCOMPOSE_OFF,    0x306E        },
   {"ha",      1, _xtxtviewCOMPOSE_OFF,    0x306F        },
   {"ba",      1, _xtxtviewCOMPOSE_OFF,    0x3070        },
   {"pa",      1, _xtxtviewCOMPOSE_OFF,    0x3071        },
   {"hi",      1, _xtxtviewCOMPOSE_OFF,    0x3072        },
   {"bi",      1, _xtxtviewCOMPOSE_OFF,    0x3073        },
   {"pi",      1, _xtxtviewCOMPOSE_OFF,    0x3074        },
   {"hu",      1, _xtxtviewCOMPOSE_OFF,    0x3075        },
   {"bu",      1, _xtxtviewCOMPOSE_OFF,    0x3076        },
   {"pu",      1, _xtxtviewCOMPOSE_OFF,    0x3077        },
   {"he",      1, _xtxtviewCOMPOSE_OFF,    0x3078        },
   {"be",      1, _xtxtviewCOMPOSE_OFF,    0x3079        },
   {"pe",      1, _xtxtviewCOMPOSE_OFF,    0x307A        },
   {"ho",      1, _xtxtviewCOMPOSE_OFF,    0x307B        },
   {"bo",      1, _xtxtviewCOMPOSE_OFF,    0x307C        },
   {"po",      1, _xtxtviewCOMPOSE_OFF,    0x307D        },
   {"ma",      1, _xtxtviewCOMPOSE_OFF,    0x307E        },
   {"mi",      1, _xtxtviewCOMPOSE_OFF,    0x307F        },
   {"mu",      1, _xtxtviewCOMPOSE_OFF,    0x3080        },
   {"me",      1, _xtxtviewCOMPOSE_OFF,    0x3081        },
   {"mo",      1, _xtxtviewCOMPOSE_OFF,    0x3082        },
   {"xya",     2, _xtxtviewCOMPOSE_OFF,    0x3083        },
   {"ya",      1, _xtxtviewCOMPOSE_OFF,    0x3084        },
   {"xyu",     2, _xtxtviewCOMPOSE_OFF,    0x3085        },
   {"yu",      1, _xtxtviewCOMPOSE_OFF,    0x3086        },
   {"xyo",     2, _xtxtviewCOMPOSE_OFF,    0x3087        },
   {"yo",      1, _xtxtviewCOMPOSE_OFF,    0x3088        },
   {"ra",      1, _xtxtviewCOMPOSE_OFF,    0x3089        },
   {"ri",      1, _xtxtviewCOMPOSE_OFF,    0x308A        },
   {"ru",      1, _xtxtviewCOMPOSE_OFF,    0x308B        },
   {"re",      1, _xtxtviewCOMPOSE_OFF,    0x308C        },
   {"ro",      1, _xtxtviewCOMPOSE_OFF,    0x308D        },
   {"xwa",     2, _xtxtviewCOMPOSE_OFF,    0x308E        },
   {"wa",      1, _xtxtviewCOMPOSE_OFF,    0x308F        },
   {"wi",      1, _xtxtviewCOMPOSE_OFF,    0x3090        },
   {"we",      1, _xtxtviewCOMPOSE_OFF,    0x3091        },
   {"wo",      1, _xtxtviewCOMPOSE_OFF,    0x3092        },
   {"n",       0, _xtxtviewCOMPOSE_ON_UQ,  0x3093        },
   {"vu",      1, _xtxtviewCOMPOSE_OFF,    0x3094        },

   {"sh",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"shi",     2, _xtxtviewCOMPOSE_OFF,    0x3057        },

   {"j",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"ji",      1, _xtxtviewCOMPOSE_OFF,    0x3058        },

   {"c",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"ch",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"chi",     2, _xtxtviewCOMPOSE_OFF,    0x3061        },

   {"xts",     0, _xtxtviewCOMPOSE_ON_QU,  0             },
   {"xtsu",    3, _xtxtviewCOMPOSE_OFF,    0x3063        },

   {"ts",      0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"tsu",     2, _xtxtviewCOMPOSE_OFF,    0x3064        },

   {"f",       0, _xtxtviewCOMPOSE_ON_UQ,  0             },
   {"fu",      1, _xtxtviewCOMPOSE_OFF,    0x3075        },

   { NULL }
};

/*
 *   Keys that start a compose sequence:
 *
 *   "aiueo kg sz td n hbp m y r w v j c f x"
 */



static vbool _xtxtviewComposeKeyCheckHiraganaTable[] =
{
   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 
   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 

   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 
   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 

   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 
   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 

   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 
   vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 

   vFALSE, vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE, 
   vTRUE,  vTRUE,  vTRUE,  vTRUE,  vFALSE, vTRUE,  vTRUE,  vTRUE, 

   vTRUE,  vFALSE, vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE, 
   vTRUE,  vTRUE,  vTRUE,  vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 

   vFALSE, vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE, 
   vTRUE,  vTRUE,  vTRUE,  vTRUE,  vFALSE, vTRUE,  vTRUE,  vTRUE, 

   vTRUE,  vFALSE, vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE,  vTRUE, 
   vTRUE,  vTRUE,  vTRUE,  vFALSE, vFALSE, vFALSE, vFALSE, vFALSE, 
};


composeDriver greekDriver =
{
   _xtxtviewIdentity, _xtxtviewMapGreek, 
   _xtxtviewComposeKeyCheckGreek,
   NULL, _xtxtviewComposeDefsGreek
};

composeDriver hiraganaDriver =
{
   _xtxtviewToLowerCase, _xtxtviewIdentity, 
   _xtxtviewComposeKeyCheckHiragana,
   NULL, _xtxtviewComposeDefsHiragana
};


/************************************************************************/

void _xtxtviewAppendDataBuffer(_xtxtviewData *focusData, vchar ch, 
				int quoteFlag)
{
   if (quoteFlag == vFALSE)
      {
	 /*
	  * map the character according to preferences
	  */
	 if (ch == xtxtviewTonos)
	    ch = _xtxtviewTONOS;
	 else if (ch == xtxtviewDialytika)
	    ch = _xtxtviewDIALYTIKA;
	 else if (ch == xtxtviewQuote)
	    ch = _xtxtviewQUOTE;
      }

   focusData->buffer[focusData->bufferLength++] = ch;
   focusData->buffer[focusData->bufferLength] = vcharNULL;
}

/*
 **********  Driver functions ***************
 */

/*
 * identity
 */

vchar _xtxtviewIdentity(int ch)
{
   return ((vchar)ch);
}

/*
 * to lower case
 */

vchar _xtxtviewToLowerCase(int ch)
{
   return (vcharToLowerCase((vchar)ch));
}

/*
 *    map greek
 */
vchar _xtxtviewMapGreek(int ch)
{
   if ((ch < 128) && (ch > 0))
      return (vcharFromUnicode(_xtxtviewASCIIToGreekTable[ch]));
   else
      return ((vchar)ch);
}

/*
 *    check greek
 */
vbool _xtxtviewComposeKeyCheckGreek(int ch)
{
   return ((ch == xtxtviewTonos) 
	   || (ch == xtxtviewDialytika));

}


/*
 *    check hiragana
 */
vbool _xtxtviewComposeKeyCheckHiragana(int ch)
{
   if ((ch < 128) && (ch > 0))
      return (_xtxtviewComposeKeyCheckHiraganaTable[ch]);
   else 
      return (vFALSE);

}

/*
 ******************* private hash function ******************
 */

static unsigned long hashIdent(const void *key)
{
    
    return (unsigned long)key;
    
} /* hashIdent */


/*
 ******************* compose dictionary create ******************
 */

/*
 *  composeCreateDict:
 *
 *  Create and initialize a compose dictionary.
 *
 */

vdict *composeCreateDict (composeRecord *composeDefs)
{
   composeRecord       *selectScan;
   vdict               *composeDict = vdictCreate (vnameHash);
   int                  i;

   for (selectScan = composeDefs, i = 0; selectScan->key != NULL; 
	selectScan++, i++) 
      {
	 vdictStore(composeDict, 
		    vnameInternGlobalLiteral(selectScan->key), 
		    (void *)i);
      }
   
   return composeDict;
}

/*
 ******************* command dictionary create ******************
 */

/*
 *  commandCreateCommandDict:
 *
 *  Create and initialize a command dictionary.
 *
 */

vdict *commandCreateCommandDict(commandInitializer *commands, 
				vcommandSelectorClass *_xtxtviewSelectorClass)
{
   commandInitializer  *selectScan;
   vcommandSelector    *selector;
   vdict               *commandDict = vdictCreate (vnameHash);

   for (selectScan = commands; selectScan->tag != NULL; selectScan++) 
      {
	 selector = vcommandCreateSelectorOfClass(_xtxtviewSelectorClass);
	 vcommandSetSelector(selector, selectScan->value);
	 vdictStore(commandDict, 
		    vnameInternGlobalLiteral(selectScan->tag), 
		    selector);
      }
   
   return commandDict;
}

/*
 *  commandCreateKeyDict:
 *
 *  Create and initialize a key dictionary.
 *
 */

vdict *commandCreateKeyDict(commandInitializer *commands)
{
   vdict       *keyDict = vdictCreate(vnameHash);
   vcommandKey *key;

   while (commands->tag != NULL) 
      {
	 if (commands->key != 0) 
	    {
	       key = vcommandCreateKey();
	       vcommandAddKeyStroke(key, commands->key);
	       vdictStore(keyDict, vnameInternGlobalLiteral(commands->tag), 
			  key);
	    }
	 commands++;
      }
   
   return keyDict;
}

/*
 *  commandCreateStateDict:
 *
 *  Create and initialize a state dictionary.
 *
 */

vdict *commandCreateStateDict(commandInitializer *commands)
{
   vdict       *stateDict = vdictCreate(vnameHash);

   while (commands->tag != NULL) 
      {
	 vdictStore(stateDict, vnameInternGlobalLiteral(commands->tag), 
		    (commands->state ? vname_Enabled : vname_Disabled));
	 commands++;
      }
   
   return stateDict;
}

/*
 *  commandCreateKeyDict:
 *
 *  Create and initialize a key dictionary.
 *
 */

vdict *commandCreateDispatchDict(commandInitializer *commands)
{
   vdict       *dispatchDict = vdictCreate(vnameHash);

   while (commands->tag != NULL) 
      {
	 vdictStore(dispatchDict, vnameInternGlobalLiteral(commands->tag), 
		    (commands->dispatch ? vname_Enabled : vname_Disabled));
	 commands++;
      }
   
   return dispatchDict;
}


static int _xtxtviewIssueFunc(vcommandSelector *command, vdict *context)

{
   int             selector;
   vtextview      *textview;
   _xtxtviewData *focusData;

   textview = (vtextview *)vdictLoad(context, vname_Operator);

   /*
    * get focus data for current item; create if necessary
    */

   if ((focusData = (_xtxtviewData *)vdictLoad(_xtxtviewDict, 
					       (const void *)textview))
       == NULL)
      {
	 focusData = _xtxtviewDataCreate();
	 vdictStore(_xtxtviewDict, (const void *)textview,
		    (const void *)focusData);
      }
   
   selector = vcommandGetSelector(command);

   switch (selector) 
      {
       case _xtxtviewKEYBOARD_ASCII:
	 _xtxtviewSetDataKeyboardStatus(focusData, _xtxtviewKEYBOARD_ASCII);
	 break;

       case _xtxtviewKEYBOARD_GREEK:
	 if ((_xtxtviewRemapKeyboard) && (_xtxtviewComposeDictGreek == NULL))
	    {
	       greekDriver.composeDict = _xtxtviewComposeDictGreek = 
		  composeCreateDict(_xtxtviewComposeDefsGreek);
	    }	
	 _xtxtviewSetDataKeyboardStatus(focusData, _xtxtviewKEYBOARD_GREEK);
    	
	 break;

       case _xtxtviewKEYBOARD_CYRILLIC:
	 _xtxtviewSetDataKeyboardStatus(focusData, 
					 _xtxtviewKEYBOARD_CYRILLIC);
	 break;

       case _xtxtviewKEYBOARD_HIRAGANA:
	 if ((_xtxtviewRemapKeyboard) && 
	     (_xtxtviewComposeDictHiragana == NULL))
	    {
	       hiraganaDriver.composeDict = _xtxtviewComposeDictHiragana = 
		  composeCreateDict(_xtxtviewComposeDefsHiragana);
	    }	
    	
	 _xtxtviewSetDataKeyboardStatus(focusData, 
					 _xtxtviewKEYBOARD_HIRAGANA);
	 break;

       case _xtxtviewKEYBOARD_HEX:
	 if (_xtxtviewGetDataKeyboardStatus(focusData)
	     != _xtxtviewKEYBOARD_HEX)
	    _xtxtviewSaveDataKeyboardStatus(focusData);
	 _xtxtviewSetDataKeyboardStatus(focusData, _xtxtviewKEYBOARD_HEX);

	 _xtxtviewHexCount       = _xtxtviewHexMax;
	 _xtxtviewHexLock        = vTRUE;
	 _xtxtviewHexFail        = vFALSE;

	 break;

       default:
	 return FALSE;
      }
   return TRUE;
}

/*
 * _vtextviewButtonDownHandler
 *
 * Handle the beginning of text selection
 */
static int _xtxtviewButtonDownHandler(vtextview *textview,vevent *event)
{
   _xtxtviewData *focusData;

   if ((focusData = (_xtxtviewData *)vdictLoad(_xtxtviewDict, 
					       (const void *)textview))
       != NULL)
      {
	 if (_xtxtviewGetDataKeyboardStatus(focusData) 
	     == _xtxtviewKEYBOARD_HEX) 
	    {
	       /*
		* interrupt hex digit input
		*/
	       _xtxtviewRestoreDataKeyboardStatus(focusData);
	    }
	 _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
      }

   return ((*defaultTextviewButtonDownHandler)(textview, event));
}



vbool _xtxtviewDictDriver(vtextview *textview, _xtxtviewData *focusData,
			   vchar *ch, composeDriver driver)
{
   vbool                     value = vFALSE; /* do not emit */
   vchar                     ch1 = *ch;
   int                       index, i;
   composeRecord             entry;

   if (_xtxtviewGetDataComposeState(focusData) != _xtxtviewCOMPOSE_OFF)
      {
	 /*
	  *  composing ...
	  */

	 if (_xtxtviewGetDataComposeState(focusData) 
	     == _xtxtviewCOMPOSE_ON_QU)
	    _xtxtviewAppendDataBuffer(focusData, 
				       driver.appendTransformer(ch1), vTRUE);
	 else
	    _xtxtviewAppendDataBuffer(focusData, 
				       driver.appendTransformer(ch1), vFALSE);

	 if ((index = (int)vdictLoad
	      (driver.composeDict,
	       vnameInternGlobal(_xtxtviewGetDataBuffer(focusData))))
	     != 0)
	    {
	       entry = (driver.composeDefs)[index];

	       if (entry.nextState == _xtxtviewCOMPOSE_OFF)
		  {
		     _xtxtviewSetDataComposeState(focusData, 
						   _xtxtviewCOMPOSE_OFF);
		     _xtxtviewResetDataBuffer(focusData);
		  }

	       if (entry.emit == 0)
		  {
		     /*
		      * emit unchanged
		      */
		     value = vTRUE;
		  }
	       else if (entry.emit != vcharUNDEFINED)
		  {
		     *ch = vcharFromUnicode(entry.emit);
		     value = vTRUE;
		  }

	       if (entry.erase)
		  {
		     for (i = 0; i < entry.erase; i++)
			vtextKey(vtextviewGetTextData(textview),
				 vtextviewGetSelection(textview),
				 vtextBACKSPACE);
		  }
	    }
	 else
	    {
	       _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
	       _xtxtviewResetDataBuffer(focusData);
	       
	       /*
		* recursion!
		*/
	       value = _xtxtviewDictDriver(textview, focusData, ch, driver);
	    }
      }
   else if  ((driver.composeKeyCheck(ch1))
	     || (xtxtviewQuote == ch1))
      {
	 _xtxtviewResetDataBuffer(focusData);

	 _xtxtviewAppendDataBuffer(focusData, 
				    driver.appendTransformer(ch1), vFALSE);

	 if (ch1 == xtxtviewQuote)
	    _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_ON_QU);
	 else
	    _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_ON_UQ);

	 index = (int)vdictLoad
	    (driver.composeDict,
	     vnameInternGlobal(_xtxtviewGetDataBuffer(focusData)));
	 
	 entry = (driver.composeDefs)[index];
	 
	 if (entry.emit == 0)
	    {
	       /*
		* emit unchanged
		*/
	       value = vTRUE;
	    }
	 else if (entry.emit != vcharUNDEFINED)
	    {
	       *ch = vcharFromUnicode(entry.emit);
	       value = vTRUE;
	    }
      }
   else
      {
	 /*
	  * emit simple mapping
	  */
	 *ch = (driver.outputTransformer)(ch1);
	 value = vTRUE;
      }

   return (value);
}

/*
 * xtxtviewKeyDownHandler:
 *
 * Handle keystrokes in a textview
 */
static int _xtxtviewKeyDownHandler(register vtextview *textview,
				    register vevent *event)
{
   vchar 	        ch;
   vkeyStroke           keyStroke;
   vkey                 key;
   vkeyModifiers        modifiers;

   unsigned short       temp;

   _xtxtviewData      *focusData;
   
   vdebugIF ((textview == NULL || event == NULL), vexGenerateArgNull ());

   /*
    * get focus data for current item; create if necessary
    */

   if ((focusData = (_xtxtviewData *)vdictLoad(_xtxtviewDict, 
					       (const void *)textview))
       == NULL)
      {
	 focusData = _xtxtviewDataCreate();
	 vdictStore(_xtxtviewDict, (const void *)textview,
		    (const void *)focusData);
      }
   
   /*
    * handle key down
    */

   if (vclassSendSuper(vtextviewGetDefaultClass(), 
		       vdialogHANDLE_ITEM_KEY_DOWN,
		       (textview, event)))
      {
	 if (_xtxtviewGetDataKeyboardStatus(focusData) 
	      == _xtxtviewKEYBOARD_HEX) 
	    {
	       if (_xtxtviewHexLock == vTRUE)
		  {
		     /*
		      * reset lock, first time around
		      */

		     _xtxtviewHexLock = vFALSE;
		  }
	       else
		  {
		     /*
		      * interrupt hex digit input, 
		      */
		     _xtxtviewRestoreDataKeyboardStatus(focusData);
		     
		     _xtxtviewSetDataComposeState(focusData, 
						   _xtxtviewCOMPOSE_OFF);
		  }
	    }
	 else
	    {
	       /*
		* turn off compose state
		*/
	       _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
	    }
	 return TRUE;
      }
   else
      {
	 ch  = veventGetKeyChar(event);
	 keyStroke = veventGetKeyStroke(event);
	 key = vkeyGetStrokeKey(keyStroke);

	 modifiers = vkeyGetStrokeModifiers(keyStroke);

	 if (((modifiers == 0) || (modifiers == vkeyMODIFIER_KEY_SHIFT))
		  && ((ch > 0) && (ch < 128)))
	    {
	       /*
		* interpret if needed
		*/
	       switch (_xtxtviewGetDataKeyboardStatus(focusData))
		  {
		   case _xtxtviewKEYBOARD_GREEK:
		     if (_xtxtviewRemapKeyboard)
			{
			   if (_xtxtviewDictDriver(textview, focusData, 
						    &ch, greekDriver))
			      veventSetKeyChar(event, ch);
			   else 
			      return(vTRUE);
			   
			}
		     break;
		   case _xtxtviewKEYBOARD_CYRILLIC:
		     if (_xtxtviewRemapKeyboard)
			/*
			 * later, use tables
			 */
			if (ch < 128)
			   veventSetKeyChar
			      (event, 
			       _xtxtviewASCIIToJCUKENGCyrillicTable[ch]);
		     break;

		   case _xtxtviewKEYBOARD_HIRAGANA:
		     if (_xtxtviewRemapKeyboard)
			{
			   if (_xtxtviewDictDriver(textview, focusData, 
						    &ch, hiraganaDriver))
			      veventSetKeyChar(event, ch);
			   else 
			      return(vTRUE);
			   
			}
		     break;
		   case _xtxtviewKEYBOARD_HEX:
		     if (_xtxtviewHexFail || (!vcharIsHexDigit(ch)))
			_xtxtviewHexFail = vTRUE;
		     else
			{
			   temp = vcharToLowerCase(ch) - 0x30;
			   _xtxtviewHexChar = (_xtxtviewHexChar << 4) +
			      ((temp > 9) ? (temp - 0x27) : temp );
			}

		     /*
		      * turn compose state on
		      */
		     _xtxtviewSetDataComposeState
			(focusData, _xtxtviewCOMPOSE_ON_QU);

		     if (--_xtxtviewHexCount == 0)
			{
			   /*
			    * interrupt hex digit input
			    */
			   _xtxtviewRestoreDataKeyboardStatus(focusData);

			   /*
			    * turn compose state off
			    */
			   _xtxtviewSetDataComposeState(focusData, 
							_xtxtviewCOMPOSE_OFF);
			   if (_xtxtviewHexFail)
			      {
				 /*
				  * failure
				  */
				 return (TRUE);
			      }
			   else
			      veventSetKeyChar(event, _xtxtviewHexChar);
			}
		     else
			return (TRUE);
		     break;
		   default:
		     break;
		  }
	    }
	 else if ((ch != 0) && (_xtxtviewGetDataKeyboardStatus(focusData) 
				== _xtxtviewKEYBOARD_HEX))
	    {
	       /*
		* interrupt hex digit input
		*/
	       _xtxtviewRestoreDataKeyboardStatus(focusData);

	       /*
		* turn compose state off
		*/
	       _xtxtviewSetDataComposeState(focusData, 
					     _xtxtviewCOMPOSE_OFF);

	    }
	 

	 return ((*defaultTextviewKeyDownHandler)(textview, event));
      }

   return FALSE;
}

/*
 * _xtxtviewFocusLose
 *
 */

static void _xtxtviewFocusLose(vtextview *textview)
{
   _xtxtviewData      *focusData;

   vdebugIF ((textview == NULL), vexGenerateArgNull ());

   if ((vdialogItemIsFocused(vtextviewGetItem(textview)))
       && (focusData = (_xtxtviewData *)vdictLoad
	   (_xtxtviewDict, (const void *)textview)))
      {
	 if (_xtxtviewGetDataKeyboardStatus(focusData) 
	     == _xtxtviewKEYBOARD_HEX)
	    {
	       /*
		* interrupted hex entry, clear
		*/
	       _xtxtviewRestoreDataKeyboardStatus(focusData);
	       _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
	    }
	 else if (_xtxtviewGetDataComposeState(focusData)
		  == _xtxtviewCOMPOSE_ON_QU)
	    {
	       _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
	    }
      }

   (*defaultTextviewFocusLose)(textview);
}


static void _xtxtviewDestroy(vtextview *textview)
{
   _xtxtviewData *focusData;

#if vdebugDEBUG
  if (textview == NULL)
     vexGenerateArgNull();
#endif

   if ((focusData = (_xtxtviewData *)vdictLoad
	(_xtxtviewDict, (const void *)textview)))
      {
	vpoolFree(_xtxtviewPool, (void *)focusData);
	vdictStore(_xtxtviewDict, (const void *)textview, (const void *)NULL);
      }

   (*defaultTextviewDestroy)(textview);
}


#if vmemBALANCE

/*
 * _xtxtviewShutdown:
 *
 * Un-initializes the xtxtview module.
 *
 */

static void _xtxtviewShutdown(void)
{
   if (_xtxtviewPool == NULL)
      return;
   
   vpoolDestroy(_xtxtviewPool);
   _xtxtviewPool = NULL;

   if (_xtxtviewDict)
      {
	 vdictDestroy(_xtxtviewDict);
	 _xtxtviewDict = NULL;
      }

   if (_xtxtviewComposeDictGreek)
      {
	 vdictDestroy(_xtxtviewComposeDictGreek);
	 _xtxtviewComposeDictGreek = NULL;
      }

   if (_xtxtviewComposeDictHiragana)
      {
	 vdictDestroy(_xtxtviewComposeDictHiragana);
	 _xtxtviewComposeDictHiragana = NULL;
      }
}
#endif


#if vdebugDEBUG
static _xtxtviewData *_xtxtviewDataCreateDebug(const char *tag, const char *file, int line)
#else
static _xtxtviewData *_xtxtviewDataCreate(void)
#endif

{
   _xtxtviewData  *focusData;

#if vdebugDEBUG
   focusData = vpoolAllocDebug(_xtxtviewPool, tag, file, line);
#else
   focusData = vpoolAlloc(_xtxtviewPool);
#endif
   
   _xtxtviewSetDataKeyboardStatus(focusData, _xtxtviewKEYBOARD_ASCII);
   _xtxtviewSaveDataKeyboardStatus(focusData);
   _xtxtviewResetDataBuffer(focusData);
   _xtxtviewSetDataComposeState(focusData, _xtxtviewCOMPOSE_OFF);
   return focusData;
}


void xtxtviewStartup()
{
   vdict                            *commandDict;
   vdict                            *keyDict;
   vdict                            *stateDict;
   vdict                            *dispatchDict;
   vcommandSpace                    *_xtxtviewSpace = NULL;
   
   xtxtviewQuote        = vcharFromLiteral('\\');
   xtxtviewTonos        = vcharFromLiteral('`');
   xtxtviewDialytika    = vcharFromLiteral('=');

   /* 
    * get the textview command space 
    */
   _xtxtviewSpace = vclassGet(vtextviewGetDefaultClass(),
			       vobjectSPACE);

  /* 
   * create our selector class 
   */
   _xtxtviewSelectorClass = vclassReproduce (vobjectGetCommandClass());
   vclassSet(_xtxtviewSelectorClass, vcommandISSUE, _xtxtviewIssueFunc);

   /* 
    * create our command dictionary, add to the textview space
    */
   commandDict = commandCreateCommandDict(_xtxtviewCommands, 
					  _xtxtviewSelectorClass);
   vcommandAddSpaceDictOwned(_xtxtviewSpace, vname_Command, commandDict);
   
   /* 
    * create our key dictionary, add to the textview space
    */
   keyDict = commandCreateKeyDict(_xtxtviewCommands);
   vcommandAddSpaceDictOwned(_xtxtviewSpace, vname_Key, keyDict);
   
   /* 
    * create our state dictionary, add to the textview space
    */

   stateDict = commandCreateStateDict(_xtxtviewCommands);
   vcommandAddSpaceDictOwned(_xtxtviewSpace, vname_State, stateDict);
   
   /* 
    * create our dispatch dictionary, add to the textview space
    * necessary for non-GUI triggered commands
    */

   dispatchDict = commandCreateDispatchDict(_xtxtviewCommands);
   vcommandAddSpaceDictOwned(_xtxtviewSpace, vname_Dispatch, dispatchDict);
   
   /*
    * fix the textview keymap 
    */

   vcommandMapKeyDict(keyDict, vclassGet(vtextviewGetDefaultClass(),
					 vobjectKEY_MAP));


   defaultTextviewKeyDownHandler = (textviewHandleFunc) 
      vclassGet(vtextviewGetDefaultClass(), vdialogHANDLE_ITEM_KEY_DOWN);

   defaultTextviewButtonDownHandler = (textviewHandleFunc) 
      vclassGet(vtextviewGetDefaultClass(), vdialogHANDLE_ITEM_BUTTON_DOWN);

   defaultTextviewFocusLose = (textviewGenericFunc) 
      vclassGet(vtextviewGetDefaultClass(), vdialogUNFOCUS_ITEM);

   defaultTextviewDestroy = (textviewGenericFunc) 
      vclassGet(vtextviewGetDefaultClass(), vobjectDESTROY);

   vclassSet(vtextviewGetDefaultClass(), vdialogHANDLE_ITEM_KEY_DOWN,
	     _xtxtviewKeyDownHandler);	     

   vclassSet(vtextviewGetDefaultClass(), vdialogHANDLE_ITEM_BUTTON_DOWN,
	     _xtxtviewButtonDownHandler);	     

   vclassSet(vtextviewGetDefaultClass(), vdialogUNFOCUS_ITEM,
	     _xtxtviewFocusLose);	     

   vclassSet(vtextviewGetDefaultClass(), vobjectDESTROY,
	     _xtxtviewDestroy);	     

   if (_xtxtviewRemapKeyboard)
      {
	 greekDriver.composeDict = _xtxtviewComposeDictGreek = 
	    composeCreateDict(_xtxtviewComposeDefsGreek);


	 hiraganaDriver.composeDict = _xtxtviewComposeDictHiragana = 
	    composeCreateDict(_xtxtviewComposeDefsHiragana);
      }	
    	
   _xtxtviewPool = vpoolCreate(sizeof(_xtxtviewData));

   _xtxtviewDict = vdictCreate(hashIdent);
    
#if vmemBALANCE
   vclientRegisterGlobalShutdown(_xtxtviewShutdown);
#endif
}
/********************************************************************/

