/* $Id: xcflchsr.c,v 1.2 1997/01/09 00:59:42 dimitri Exp $ */

/************************************************************

    xcflchsr.c
    C Implementation file for the xc filechooser

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  xctransINCLUDED
#include "xctrans.h"
#endif

#ifndef  xcflchsrINCLUDED
#include "xcflchsr.h"
#endif

#if vdebugDEBUG
#define vdebugTAG "xcflchsr"
#endif

/*
 * * * * * * * * * * * * * * MACRO DEFINITIONS * * * * * * * * * *
 */

#define _xcflchsrGetCharset(c)            ((c)->charset)
#define _xcflchsrGetByteOrder(c)          ((c)->byteOrder)
#define _xcflchsrSetCharset(c, cset)      ((c)->charset = (cset))
#define _xcflchsrSetByteOrder(c, bo)      ((c)->byteOrder = (bo))

/*******************************
 * xc default filechooser class
 *******************************/

static xcflchsrClass                     *defaultClass           = NULL;
static vdict                              defaultCommands;
static vdict                              defaultKeys;
static vdict                              defaultKeyMap;
static vcommandSpace                      defaultSpace;

/*****************************
 * xc split filechooser class
 *****************************/

static xcflchsrClass                     *splitClass             = NULL;
static int                               *_xcflchsrCharset       = NULL;


/*
 *  the following array matches byte order option menu 
 *  contents in the resource file, to be used with native filechsr
 */

static int                                _xcflchsrByteOrder[]   = 
{
   xctransORDER_BIG_ENDIAN,
   xctransORDER_LITTLE_ENDIAN,
   xctransORDER_IMPLICIT   
};

/*
 * notify function for xc split filechsr items
 */

/*****************************************
 *  _xcflchsrByteOrderOptionMenuNotify
 *****************************************/
static void _xcflchsrByteOrderOptionMenuNotify(vcontrol *control, 
					       vevent *event)
{
   _xcflchsrSetByteOrder((xcflchsr *) vcontrolGetData(control),
			 _xcflchsrByteOrder[vcontrolGetValue(control)]);
}


/*************************************
 *  _xcflchsrEncodingComboNotify
 *************************************/
static void _xcflchsrEncodingComboNotify(vcombo *combo, vevent *event)
{
  int                    row, column;
  xcflchsr           *chooser;

  vlistGetSelectedCell(vcomboGetList(combo), 
		       vlistitemGetSelection(vcomboGetListitem(combo)),
		       &row, &column);
  
  if (row != vlistNO_CELLS_SELECTED)
     _xcflchsrSetCharset((xcflchsr *) vcomboGetData(combo),
			     _xcflchsrCharset[row]);

  chooser = (xcflchsr *)vcomboGetData(combo);

  if (xcharsetGetType(_xcflchsrGetCharset(chooser)) 
      == xctransCHAR_SIZE_TWO_BYTE)
     vcontrolEnable((vcontrol *) chooser->byteOrderItem);
  else
     vcontrolDisable((vcontrol *) chooser->byteOrderItem);

}

/******************************
 *  xc split filechooser apply
 ******************************/

int _xcflchsrFilechsrApplySplit(vfilechsr *filechsr, vfsPath *path)
{
    xcflchsr	        *chooser;
    vconfirm            *splitConfirm;
    const vname         *tag;

    chooser = (xcflchsr *) filechsr;

    /*
     *  native filechsr
     */
    
    splitConfirm = chooser->splitConfirm;
    
    vwindowSetLeader(vdialogGetWindow(vconfirmGetDialog(splitConfirm)),
		     vdialogGetWindow(xcflchsrGetDialog(chooser)));
    
    tag = vconfirmProcess(splitConfirm);
    
    if ((tag == vname_Ok) 
	|| (tag == vname_Apply))
       /* do OK code */
       {
	  if (chooser->applyProc != NULL) 
	     {
		return (*chooser->applyProc)(chooser, path,
					     _xcflchsrGetCharset(chooser),
					     _xcflchsrGetByteOrder(chooser));
	     }
       }
    else if ((tag == vname_Cancel) 
	     || (tag == vname_Reset))
       /* do RESET code */
       return vFALSE;

    return(vTRUE);

}

/*******************************
 * xc default filechooser apply
 *******************************/

int _xcflchsrFilechsrApply(vfilechsr *filechsr, vfsPath *path)
{
    xcflchsr              *chooser;

    chooser = (xcflchsr *) filechsr;

    /*
     *  Galaxy filechsr
     */
    
    if (chooser->applyProc != NULL) 
       {
	  return (*chooser->applyProc)(chooser, path, 
				       _xcflchsrGetCharset(chooser),
				       _xcflchsrGetByteOrder(chooser));
       }

    return(vTRUE);

}

/*
 * command functions to be used with Galaxy filechsr
 */

/*****************************
 * _xcflchsrIssueCommand
 *****************************/
static int _xcflchsrIssueCommand(xcflchsr *chooser, int selector,
				 vdict *attr2value)
{
   int       twoByte;

   twoByte = (xcharsetGetType(_xcflchsrGetCharset(chooser))
	      == xctransCHAR_SIZE_TWO_BYTE);
      
   switch (selector)
      {
       case xcflchsrSELECT_ASCII:
	 _xcflchsrSetCharset(chooser, xctransCODESET_ASCII);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_LATIN_1:
	 _xcflchsrSetCharset(chooser, xctransCODESET_LATIN_1);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_MACINTOSH:
	 _xcflchsrSetCharset(chooser, xctransCODESET_MACINTOSH);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_WINDOWS:
	 _xcflchsrSetCharset(chooser, xctransCODESET_WINDOWS);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_LATIN_2:
	 _xcflchsrSetCharset(chooser, xctransCODESET_LATIN_2);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_LATIN_3:
	 _xcflchsrSetCharset(chooser, xctransCODESET_LATIN_3);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_LATIN_4:
	 _xcflchsrSetCharset(chooser, xctransCODESET_LATIN_4);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_LATIN_5:
	 _xcflchsrSetCharset(chooser, xctransCODESET_LATIN_5);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_GREEK:
	 _xcflchsrSetCharset(chooser, xctransCODESET_GREEK);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_CYRILLIC:
	 _xcflchsrSetCharset(chooser, xctransCODESET_CYRILLIC);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_KOI8:
	 _xcflchsrSetCharset(chooser, xctransCODESET_KOI8);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_HEBREW:
	 _xcflchsrSetCharset(chooser, xctransCODESET_HEBREW);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_ADOBE_STD_ENC:
	 _xcflchsrSetCharset(chooser, xctransCODESET_ADOBE_STD_ENC);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_ADOBE_SYMBOL:
	 _xcflchsrSetCharset(chooser, xctransCODESET_ADOBE_SYMBOL);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_DEC_TECH:
	 _xcflchsrSetCharset(chooser, xctransCODESET_DEC_TECH);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_VISCII:
	 _xcflchsrSetCharset(chooser, xctransCODESET_VISCII);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_JISX0201:
	 _xcflchsrSetCharset(chooser, xctransCODESET_JISX0201);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_UNICODE:
	 _xcflchsrSetCharset(chooser, xctransCODESET_UNICODE);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_JISX0208_83:
	 _xcflchsrSetCharset(chooser, xctransCODESET_JISX0208_83);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_JISX0212:
	 _xcflchsrSetCharset(chooser, xctransCODESET_JISX0212);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_KSC5601:
	 _xcflchsrSetCharset(chooser, xctransCODESET_KSC5601);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_GB2312:
	 _xcflchsrSetCharset(chooser, xctransCODESET_GB2312);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_BIG5HKU:
	 _xcflchsrSetCharset(chooser, xctransCODESET_BIG5HKU);
	 if (!twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_SJIS:
	 _xcflchsrSetCharset(chooser, xctransCODESET_SJIS);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_JEUC:
	 _xcflchsrSetCharset(chooser, xctransCODESET_JEUC);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);
       case xcflchsrSELECT_UTF:
	 _xcflchsrSetCharset(chooser, xctransCODESET_UTF);
	 if (twoByte)
	    vobjectUpdateAllAttributes((vobject *)chooser->byteOrderItem);
	 return(vTRUE);

       case xcflchsrSELECT_IMPLICIT:
	 _xcflchsrSetByteOrder(chooser, xctransORDER_IMPLICIT);
	 return(vTRUE);
       case xcflchsrSELECT_BIG_ENDIAN:
	 _xcflchsrSetByteOrder(chooser, xctransORDER_BIG_ENDIAN);
	 return(vTRUE);
       case xcflchsrSELECT_LITTLE_ENDIAN:
	 _xcflchsrSetByteOrder(chooser, xctransORDER_LITTLE_ENDIAN);
	 return(vTRUE);

      }
   
   return(vclassSendSuper(defaultClass, vobjectISSUE_SELECTOR,
			  (chooser, selector, attr2value)));
}

/**************************
 *_xcflchsrQueryCommand
 *************************/
static int _xcflchsrQueryCommand(xcflchsr *chooser, int selector,
				 vdict *context)
{
  vbool		 on;
  vbool		 enabled;

  switch (selector)
    {
     case xcflchsrSELECT_ASCII:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_ASCII);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_LATIN_1:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_LATIN_1);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_MACINTOSH:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_MACINTOSH);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_WINDOWS:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_WINDOWS);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_LATIN_2:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_LATIN_2);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_LATIN_3:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_LATIN_3);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_LATIN_4:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_LATIN_4);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_LATIN_5:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_LATIN_5);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_GREEK:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_GREEK);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_CYRILLIC:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_CYRILLIC);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_KOI8:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_KOI8);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_HEBREW:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_HEBREW);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_ADOBE_STD_ENC:
       on = (_xcflchsrGetCharset(chooser) 
	     == xctransCODESET_ADOBE_STD_ENC);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_ADOBE_SYMBOL:
       on = (_xcflchsrGetCharset(chooser) 
	     == xctransCODESET_ADOBE_SYMBOL);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_DEC_TECH:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_DEC_TECH);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_VISCII:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_VISCII);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_JISX0201:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_JISX0201);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_UNICODE:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_UNICODE);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_JISX0208_83:
       on = (_xcflchsrGetCharset(chooser) 
	     == xctransCODESET_JISX0208_83);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_JISX0212:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_JISX0212);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_KSC5601:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_KSC5601);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_GB2312:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_GB2312);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_BIG5HKU:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_BIG5HKU);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 

     case xcflchsrSELECT_SJIS:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_SJIS);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_JEUC:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_JEUC);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 
     case xcflchsrSELECT_UTF:
       on = (_xcflchsrGetCharset(chooser) == xctransCODESET_UTF);
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
       break; 


    case xcflchsrSELECT_IMPLICIT:
       enabled = (xcharsetGetType(_xcflchsrGetCharset(chooser)) 
		  == xctransCHAR_SIZE_TWO_BYTE);
       vdictStore(context, vname_State, 
		  enabled ? vname_Enabled : vname_Disabled);
       on = (enabled 
	     && (_xcflchsrGetByteOrder(chooser) == xctransORDER_IMPLICIT));
       vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
      break;

    case xcflchsrSELECT_BIG_ENDIAN:
      enabled = (xcharsetGetType(_xcflchsrGetCharset(chooser)) 
		 == xctransCHAR_SIZE_TWO_BYTE);
      vdictStore(context, vname_State, 
		 enabled ? vname_Enabled : vname_Disabled);
      on = (enabled 
	    && (_xcflchsrGetByteOrder(chooser) == xctransORDER_BIG_ENDIAN));
      vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
      break;

    case xcflchsrSELECT_LITTLE_ENDIAN:
      enabled = (xcharsetGetType(_xcflchsrGetCharset(chooser)) 
		 == xctransCHAR_SIZE_TWO_BYTE);
      vdictStore(context, vname_State, 
		 enabled ? vname_Enabled : vname_Disabled);
      on = (enabled 
	    && (_xcflchsrGetByteOrder(chooser) == xctransORDER_LITTLE_ENDIAN));
      vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
      break;
    }

  return(vclassSendSuper(defaultClass, vobjectQUERY_SELECTOR,
			 (chooser, selector, context)));
}

/***********************
 *_xcflchsrInitSpace
 ***********************/
static void _xcflchsrInitSpace(void)
{
   typedef struct {
      const char *id;
      short       selector;
      vkeyStroke  keys[4];
   } selectDef;

   register int                  count;
   vcommandKey                  *key;
   register selectDef           *selectScan;
   vcommandSelector             *select;

#define vPLAIN(k)       vkeyComputeStroke(k, 0)
#define vSHIFT(k)       vkeyComputeStroke(k, vkeyMODIFIER_KEY_SHIFT)
#define vCTRL(k)        vkeyComputeStroke(k, vkeyMODIFIER_KEY_CTRL)
#define vCOMMAND(k)     vkeyComputeStroke(k, vkeyMODIFIER_KEY_COMMAND)
#define vSHIFT_CTRL(k) \
   vkeyComputeStroke(k, vkeyMODIFIER_KEY_SHIFT|vkeyMODIFIER_KEY_COMMAND)
#define vALT(k)         vkeyComputeStroke(k, vkeyMODIFIER_KEY_ALT)
      
      static selectDef selectDefs[] = {

	 {"EncodingASCII", xcflchsrSELECT_ASCII, 
	     {0}},
	 {"EncodingLatin1", xcflchsrSELECT_LATIN_1,
	     {0}},	     
	 {"EncodingMacintosh", xcflchsrSELECT_MACINTOSH,
	     {0}},
	 {"EncodingWindows", xcflchsrSELECT_WINDOWS,
	     {0}},
	 {"EncodingLatin2", xcflchsrSELECT_LATIN_2,
	     {0}},
	 {"EncodingLatin3", xcflchsrSELECT_LATIN_3,
	     {0}},
	 {"EncodingLatin4", xcflchsrSELECT_LATIN_4,
	     {0}},
	 {"EncodingLatin5", xcflchsrSELECT_LATIN_5,
	     {0}},
	 {"EncodingGreek", xcflchsrSELECT_GREEK,
	     {0}},
	 {"EncodingCyrillic", xcflchsrSELECT_CYRILLIC,
	     {0}},
	 {"EncodingKoi8", xcflchsrSELECT_KOI8,
	     {0}},
	 {"EncodingHebrew", xcflchsrSELECT_HEBREW,
	     {0}},
	 {"EncodingAdobeStdEnc",xcflchsrSELECT_ADOBE_STD_ENC,
	     {0}},
	 {"EncodingAdobeSymbol", xcflchsrSELECT_ADOBE_SYMBOL,
	     {0}},
	 {"EncodingDecTech", xcflchsrSELECT_DEC_TECH,
	     {0}},
	 {"EncodingViscii", xcflchsrSELECT_VISCII,
	     {0}},
	 {"EncodingJISX0201", xcflchsrSELECT_JISX0201,
	     {0}},
	 {"EncodingUnicode", xcflchsrSELECT_UNICODE,
	     {0}},
	 {"EncodingJISX0208_83", xcflchsrSELECT_JISX0208_83,
	     {0}},
	 {"EncodingJISX0212", xcflchsrSELECT_JISX0212,
	     {0}},
	 {"EncodingKSC5601", xcflchsrSELECT_KSC5601,
	     {0}},
	 {"EncodingGB2312", xcflchsrSELECT_GB2312,
	     {0}},
	 {"EncodingBig5hku", xcflchsrSELECT_BIG5HKU,
	     {0}},
	 {"EncodingSJIS", xcflchsrSELECT_SJIS,
	     {0}},
	 {"EncodingJEUC", xcflchsrSELECT_JEUC,
	     {0}},
	 {"EncodingUTF", xcflchsrSELECT_UTF,
	     {0}},

	 {"ByteOrderImplicit", xcflchsrSELECT_IMPLICIT,
	     {0}},
	 {"ByteOrderBigEndian", xcflchsrSELECT_BIG_ENDIAN,
	     {0}},
	 {"ByteOrderLittleEndian", xcflchsrSELECT_LITTLE_ENDIAN,
	     {0}},

	 { NULL }
      };

#undef vPLAIN
#undef vSHIFT
#undef vCTRL
#undef vCOMMAND
#undef vSHIFT_CTRL
#undef vALT

   vdictInit(&defaultCommands, vnameHash);
   vdictInit(&defaultKeys, vnameHash);
   
   for (selectScan = selectDefs; selectScan->id!=NULL; selectScan++)
      {
	 
	 if (selectScan->selector != -1)
	    {
	       
	       select = vcommandCreateSelectorOfClass
		  (vobjectGetCommandClass());
	       
	       vcommandSetSelector(select, selectScan->selector);
	       
	       vdictStore(&defaultCommands,
			  vnameInternGlobalLiteral(selectScan->id), select);
	    }
	 
	 count = 0;
	 
	 while (selectScan->keys[count] != 0)
	    count++;
	 
	 if (count != 0)
	    {
	       key = vcommandCreateKey();
	       vcommandAddKeyStrokes(key, selectScan->keys, count);
	       vdictStore(&defaultKeys,
			  vnameInternGlobalLiteral(selectScan->id), key);
	    }
      }
   
   vcommandCopyInitSpace(vclassGet(vfilechsrGetDefaultClass(),
				   vobjectSPACE), &defaultSpace);
   vcommandAddSpaceDict(&defaultSpace, vname_Command, &defaultCommands);
   vcommandAddSpaceDict(&defaultSpace, vname_Key, &defaultKeys);
   
   vdictCopyInit(vclassGet(vfilechsrGetDefaultClass(),
			   vobjectKEY_MAP),  &defaultKeyMap);
   vcommandMapKeyDict(&defaultKeys, &defaultKeyMap);
}

/****************************************************************
  _xcflchsrInit
*****************************************************************/
static void _xcflchsrInit(register xcflchsr *chooser)
{
  vresource	      	 res, res1, res2;
  int                    systemCharset;
  vmenu                 *encodingMenu;
  vmenu                 *byteOrderMenu;
  vmenubar              *menubar;
  vfilechsr             *fc;
  
  vclassSendSuper(defaultClass, vinstanceINIT, (chooser));

  fc = xcflchsrGetFilechsr(chooser);

  vfilechsrSetPreferNative(fc, vFALSE);

  vconfirmSetDisabledButtons(vfilechsrGetConfirm(fc), vTRUE);
  vfilechsrSetApply(fc, _xcflchsrFilechsrApply);

  /*
   * find the system character set
   */
  systemCharset = xcharsetFindSystem();

  /*
   * initialize the exported fields
   */
  _xcflchsrSetCharset(chooser, systemCharset);
  _xcflchsrSetByteOrder(chooser, xctransORDER_IMPLICIT);
  /* agrees with resource file */

  /*
   * load in the resources
   */

  res = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
		     vnameInternGlobalLiteral("Xcflchsr"));

  /*
   * Get and copy the menus
   */
  
  res1 = vresourceGet(res, vnameInternGlobalLiteral("XcflchsrEncodingMenu"));
  encodingMenu = vmenuLoad(res1);
  
  res2 = vresourceGet(res, vnameInternGlobalLiteral("XcflchsrByteOrderMenu"));
  byteOrderMenu = vmenuLoad(res2);
  
  /*
   *  Initialize items
   */
  vmenuSetData(encodingMenu, chooser);
  vmenuSetData(byteOrderMenu, chooser);
  
  /*
   * append menus to the filechsr menubar
   */
  
  menubar = vfilechsrGetMenuBar(fc);
  vmenubarAppendMenu(menubar, encodingMenu);
  vmenubarAppendMenu(menubar, byteOrderMenu);
  
  
  chooser->encodingItem = (void *) encodingMenu;
  chooser->byteOrderItem = (void *) byteOrderMenu;
  chooser->splitConfirm = NULL;

}

/****************************************************************
  xcflchsrDestroy
*****************************************************************/
static void _xcflchsrDestroy(register xcflchsr *chooser)
{
  vclassSendSuper(defaultClass, vinstanceDESTROY, (chooser));
}

#if (vmemBALANCE)
/****************************************************************
  xcflchsrShutdown
*****************************************************************/
static void _xcflchsrShutDown(void)
{
   vcommandDestroySpace(&defaultSpace);
   vcommandDestroyDict(&defaultCommands);
   vcommandDestroyKeyDict(&defaultKeys);
   vdictDestroy(&defaultKeyMap);
}
#endif


/****************************************************************
  _xcflchsrInitSplit
*****************************************************************/
static void _xcflchsrInitSplit(register xcflchsr *chooser)
{
  vdialog		*to;
  vresource	      	 res;
  int                    lp, count, temp;
  int                    systemCharset, initialCharset;
  vcombo                *encodingCombo;
  vcontrol              *byteOrderOptionMenu;
  vfilechsr             *fc;
  
  vclassSendSuper(splitClass, vinstanceINIT, (chooser));

  fc = xcflchsrGetFilechsr(chooser);

  vfilechsrSetPreferNative(fc, vTRUE);

  vconfirmSetDisabledButtons(vfilechsrGetConfirm(fc), vTRUE);
  vfilechsrSetApply(fc, _xcflchsrFilechsrApplySplit);

  /*
   * find the system character set
   */
  systemCharset = xcharsetFindSystem();

  /*
   * initialize the exported fields
   */
  _xcflchsrSetCharset(chooser, systemCharset);
  _xcflchsrSetByteOrder(chooser, xctransORDER_IMPLICIT);
  /* agrees with resource file */

  /*
   * load in the resources
   */

  res = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
		     vnameInternGlobalLiteral("Xcflchsr"));

  /*
   *  Get and copy other chooser dialog
   */
  
  res = vresourceGet(res, vnameInternGlobalLiteral("XcflchsrSplitConfirm"));
  
  chooser->splitConfirm = vconfirmLoad(res);
  
  /*
   *  Set up confirm
   */
  
  vconfirmSetData(chooser->splitConfirm, chooser);
  
  /*
   *  Initialize items
   */
  to = vconfirmGetDialog(chooser->splitConfirm);
  
  encodingCombo = (vcombo *)vdialogFindItem
     (to, vnameInternGlobalLiteral("CharsetPopdownCombo"));
  vcomboSetNotify(encodingCombo, _xcflchsrEncodingComboNotify);
  vcomboSetData(encodingCombo, chooser);
  
  byteOrderOptionMenu = (vcontrol *)vdialogFindItem
     (to, vnameInternGlobalLiteral("ByteOrderOptionMenu"));
  vcontrolSetNotify(byteOrderOptionMenu,  _xcflchsrByteOrderOptionMenuNotify);
  vcontrolSetData(byteOrderOptionMenu, chooser);
  
  /*
   * initialize the combo data table 
   */
  
  initialCharset = 0;
  count = vcomboGetTextCount(encodingCombo);
  _xcflchsrCharset = (int *) vmemAlloc(sizeof(int) * count);
  
  for (lp = 0; lp < count; lp++)
     {
	temp = _xcflchsrCharset[lp] = xcharsetFindByName
	   (vcomboGetTextAt(encodingCombo, lp));
	if (temp == systemCharset)
	   initialCharset = lp;
     }
  
  /*
   * set combo value to be the system charset
   */
  
  vcomboSelectTextAt(encodingCombo, initialCharset);
  chooser->encodingItem = (void *) encodingCombo;
  chooser->byteOrderItem = (void *) byteOrderOptionMenu;
  
  /*
   * disable byte order option menu if not applicable
   */
  
  if (xcharsetGetType(_xcflchsrGetCharset(chooser))
      == xctransCHAR_SIZE_TWO_BYTE)
     vcontrolEnable((vcontrol *) chooser->byteOrderItem);
  else
     vcontrolDisable((vcontrol *) chooser->byteOrderItem);
  
}

/****************************************************************
  xcflchsrDestroySplit
*****************************************************************/
static void _xcflchsrDestroySplit(register xcflchsr *chooser)
{
  if (chooser->splitConfirm != NULL)
     vconfirmDestroy(chooser->splitConfirm);

  vclassSendSuper(splitClass, vinstanceDESTROY, (chooser));

}

#if (vmemBALANCE)
/****************************************************************
  xcflchsrShutdownSplit
*****************************************************************/
static void _xcflchsrShutDownSplit(void)
{
   if (_xcflchsrCharset != NULL)
      vmemFree(_xcflchsrCharset);

}
#endif


/*
 * * * * * * * * * * * * DEFAULT CLASS REFERENCE * ** * * * * * * * *
 */


/****************************************************************
  xcflchsrGetDefaultClass
*****************************************************************/
xcflchsrClass *xcflchsrGetDefaultClass(void)
{
   xcflchsrClass		*clas;

   if (defaultClass == NULL)
      {
	 vdialogGetDefaultItemClass();
	 vcontainerGetDefaultClass();
	 vdialogGetLineItemClass();
	 vcontrolGetOptionMenuClass();
	 vconfirmGetDefaultClass();
	 vcontrolGetDefaultClass();
	 vmenuGetDefaultClass();

	 _xcflchsrInitSpace();

	 clas = vclassSpawn(vfilechsrGetDefaultClass(),
			    sizeof(xcflchsrClass));

	 vclassSetNameScribed(clas, vcharScribeLiteral("xcflchsr"));
	 vclassSetObjectSize(clas, sizeof(xcflchsr));
	 
	 vclassSet(clas, vobjectINIT, _xcflchsrInit);
	 vclassSet(clas, vobjectDESTROY, _xcflchsrDestroy);

	 vclassSet(clas, vobjectSPACE, &defaultSpace);
	 vclassSet(clas, vobjectKEY_MAP, &defaultKeyMap);
	 vclassSet(clas, vobjectISSUE_SELECTOR, 
		   _xcflchsrIssueCommand);
	 vclassSet(clas, vobjectQUERY_SELECTOR, 
		   _xcflchsrQueryCommand);

#if (vmemBALANCE)
	 vclientRegisterShutdown(_xcflchsrShutDown);
#endif
	 
	 defaultClass = clas;
      }

   return(defaultClass);
}

/****************************************************************
  xcflchsrGetDefaultClass
*****************************************************************/
xcflchsrClass *xcflchsrGetSplitClass(void)
{
   xcflchsrClass		*clas;

   if (splitClass == NULL)
      {
	 vdialogGetDefaultItemClass();
	 vcontainerGetDefaultClass();
	 vdialogGetLineItemClass();
	 vcontrolGetOptionMenuClass();
	 vconfirmGetDefaultClass();
	 vcontrolGetDefaultClass();
	 vmenuGetDefaultClass();
	 vcomboGetDefaultClass();

	 clas = vclassSpawn(vfilechsrGetDefaultClass(),
			    sizeof(xcflchsrClass));

	 vclassSetNameScribed(clas, vcharScribeLiteral("xcflchsrSplit"));
	 vclassSetObjectSize(clas, sizeof(xcflchsr));
	 
	 vclassSet(clas, vobjectINIT, _xcflchsrInitSplit);
	 vclassSet(clas, vobjectDESTROY, _xcflchsrDestroySplit);

#if (vmemBALANCE)
	 vclientRegisterShutdown(_xcflchsrShutDownSplit);
#endif
	 
	 splitClass = clas;
      }

   return(splitClass);
}

