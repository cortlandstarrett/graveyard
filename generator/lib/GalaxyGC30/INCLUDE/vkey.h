/* $Id: vkey.h,v 1.31 1997/11/14 15:36:25 gregt Exp $ */

/************************************************************

    vkey.h
    C Interface file for keyboard codes

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vkeyINCLUDED
#define vkeyINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * Keys
 *
 * A vkey is an actual key that was pressed.
 * vkeyModifiers is the set of all modifiers active when that key was pressed
 * vkeyStroke is (vkeyModifiers << 16) | vkey
 */

typedef unsigned short	vkey;
typedef unsigned short	vkeyModifiers;
typedef unsigned long	vkeyStroke;


/* 
 * vkeyMODIFIER_BUTTON_n are deprecated, use LEFT/MIDDLE/RIGHT.
 */

enum {
    vkeyMODIFIER_KEY_ALT	= 0x0001,
    vkeyMODIFIER_KEY_CTRL	= 0x0002,
    vkeyMODIFIER_KEY_SHIFT	= 0x0004,
    vkeyMODIFIER_KEY_COMMAND	= 0x0008,
    vkeyMODIFIER_BUTTON_LEFT    = 0x0010,
    vkeyMODIFIER_BUTTON_0	= vkeyMODIFIER_BUTTON_LEFT,
    vkeyMODIFIER_BUTTON_MIDDLE  = 0x0020,
    vkeyMODIFIER_BUTTON_1	= vkeyMODIFIER_BUTTON_MIDDLE,
    vkeyMODIFIER_BUTTON_RIGHT   = 0x0040,
    vkeyMODIFIER_BUTTON_2	= vkeyMODIFIER_BUTTON_RIGHT,
    vkeyMODIFIER_BUTTON_3	= 0x0080,
    vkeyMODIFIER_BUTTON_4	= 0x0100
};

enum {
    vkeySPACE			= 0x0020,

    vkeyCUT			= 0xF901,
    vkeyCOPY			= 0xF902,
    vkeyPASTE			= 0xF903,
    vkeyFRONT			= 0xF904,
    vkeyOPEN			= 0xF905,
    vkeyPROPERTIES		= 0xF906,

    vkeyPAGE_UP			= 0xFA41,
    vkeyPAGE_DOWN		= 0xFA42,
    
    vkeyBACKSPACE		= 0xFC08,
    vkeyTAB			= 0xFC09,
    vkeyLINEFEED		= 0xFC0A,
    vkeyCLEAR			= 0xFC0B,
    vkeyRETURN			= 0xFC0D,
    vkeyPAUSE			= 0xFC13,
    vkeySCROLL_LOCK		= 0xFC14,
    vkeySYSTEM_REQUEST		= 0xFC15,
    vkeyESCAPE			= 0xFC1B,
    
    vkeyHOME			= 0xFC50,
    vkeyLEFT			= 0xFC51,
    vkeyUP			= 0xFC52,
    vkeyRIGHT			= 0xFC53,
    vkeyDOWN			= 0xFC54,
    vkeyPRIOR			= 0xFC55,
    vkeyNEXT			= 0xFC56,
    vkeyEND			= 0xFC57,
    vkeyBEGIN			= 0xFC58,

    vkeySELECT			= 0xFC60,
    vkeyPRINT			= 0xFC61,
    vkeyEXECUTE			= 0xFC62,
    vkeyINSERT			= 0xFC63,
    vkeyUNDO			= 0xFC65,
    vkeyREDO			= 0xFC66,
    vkeyMENU			= 0xFC67,        /* Application key on Microsoft keyboard */
    vkeyFIND			= 0xFC68,
    vkeyCANCEL			= 0xFC69,
    vkeyHELP			= 0xFC6A,
    vkeyBREAK			= 0xFC6B,
    vkeyMODE_SWITCH		= 0xFC7E,
    vkeySCRIPT_SWITCH		= 0xFC7E,
    vkeyNUM_LOCK		= 0xFC7F,

    vkeyKEYPAD_SPACE		= 0xFC80,
    vkeyKEYPAD_TAB		= 0xFC89,
    vkeyENTER			= 0xFC8D,	/* usually on the keypad */
    vkeyKEYPAD_F1		= 0xFC91,
    vkeyKEYPAD_F2		= 0xFC92,
    vkeyKEYPAD_F3		= 0xFC93,
    vkeyKEYPAD_F4		= 0xFC94,
    vkeyKEYPAD_EQUAL		= 0xFCBD,
    vkeyKEYPAD_MULTIPLY		= 0xFCAA,
    vkeyKEYPAD_ADD		= 0xFCAB,
    vkeyKEYPAD_SEPARATOR	= 0xFCAC,	/* usually a comma */
    vkeyKEYPAD_SUBTRACT		= 0xFCAD,
    vkeyKEYPAD_DECIMAL		= 0xFCAE,
    vkeyKEYPAD_DIVIDE		= 0xFCAF,

    vkeyKEYPAD_0		= 0xFCB0,
    vkeyKEYPAD_1		= 0xFCB1,
    vkeyKEYPAD_2		= 0xFCB2,
    vkeyKEYPAD_3		= 0xFCB3,
    vkeyKEYPAD_4		= 0xFCB4,
    vkeyKEYPAD_5		= 0xFCB5,
    vkeyKEYPAD_6		= 0xFCB6,
    vkeyKEYPAD_7		= 0xFCB7,
    vkeyKEYPAD_8		= 0xFCB8,
    vkeyKEYPAD_9		= 0xFCB9,

    vkeyF1			= 0xFCBE,
    vkeyF2			= 0xFCBF,
    vkeyF3			= 0xFCC0,
    vkeyF4			= 0xFCC1,
    vkeyF5			= 0xFCC2,
    vkeyF6			= 0xFCC3,
    vkeyF7			= 0xFCC4,
    vkeyF8			= 0xFCC5,
    vkeyF9			= 0xFCC6,
    vkeyF10			= 0xFCC7,
    vkeyF11			= 0xFCC8,
    vkeyF12			= 0xFCC9,
    vkeyF13			= 0xFCCA,
    vkeyF14			= 0xFCCB,
    vkeyF15			= 0xFCCC,
    vkeyF16			= 0xFCCD,
    vkeyF17			= 0xFCCE,
    vkeyF18			= 0xFCCF,
    vkeyF19			= 0xFCD0,
    vkeyF20			= 0xFCD1,
    vkeyF21			= 0xFCD2,
    vkeyF22			= 0xFCD3,
    vkeyF23			= 0xFCD4,
    vkeyF24			= 0xFCD5,
    vkeyF25			= 0xFCD6,
    vkeyF26			= 0xFCD7,
    vkeyF27			= 0xFCD8,
    vkeyF28			= 0xFCD9,
    vkeyF29			= 0xFCDA,
    vkeyF30			= 0xFCDB,
    vkeyF31			= 0xFCDC,
    vkeyF32			= 0xFCDD,
    vkeyF33			= 0xFCDE,
    vkeyF34			= 0xFCDF,
    vkeyF35			= 0xFCE0,

    vkeyCAPS_LOCK		= 0xFCE5,
    vkeySHIFT_LOCK		= 0xFCE6,
    
    vkeySHIFT_L			= 0xFCE1,
    vkeySHIFT_R			= 0xFCE2,
    vkeyCONTROL_L		= 0xFCE3,
    vkeyCONTROL_R		= 0xFCE4,
    vkeyMETA_L			= 0xFCE7, /* logically same as vkeyCOMMAND */
    vkeyMETA_R			= 0xFCE8, /* logically same as vkeyCOMMAND */
    vkeyALT_L			= 0xFCE9,
    vkeyALT_R			= 0xFCEA,
    vkeyCOMMAND_L		= 0xFCEB,
    vkeyCOMMAND_R		= 0xFCEC,
    vkeyHYPER_L			= 0xFCED,
    vkeyHYPER_R			= 0xFCEE,
    
    vkeyWINDOWS_L       = 0xFCF0,   /* Microsoft keyboard keys */         
    vkeyWINDOWS_R       = 0xFCF1,

    vkeyDELETE			= 0xFCFF
};

#define vkeyMODIFIER_BUTTON \
  (vkeyMODIFIER_BUTTON_0 | \
   vkeyMODIFIER_BUTTON_1 | \
   vkeyMODIFIER_BUTTON_2 | \
   vkeyMODIFIER_BUTTON_3 | \
   vkeyMODIFIER_BUTTON_4)

#define vkeyNULL		((vkey) 0)
#define vkeyNULL_CHAR           ((vchar) 0)
#define vkeyNULL_STROKE		((vkeyStroke) 0)
#define vkeyNULL_MODIFIERS	((vkeyModifiers) 0)

vkey		 vkeyGetStrokeKey( vkeyStroke stroke );
vkeyModifiers	 vkeyGetStrokeModifiers( vkeyStroke stroke );

vkeyStroke	 vkeyComputeStroke( vkey key, vkeyModifiers modifiers );

vchar		 vkeyToChar( vkey key );
vkey		 vkeyFromChar( vchar c );

unsigned long	 vkeyHashModifiers( vkeyModifiers modifiers );
void		*vkeyInternModifiers( vkeyModifiers modifiers );
vkeyModifiers	 vkeyUninternModifiers( void *internedModifiers );

unsigned long	 vkeyHashStroke( vkeyStroke stroke );
void		*vkeyInternStroke( vkeyStroke stroke );
vkeyStroke	 vkeyUninternStroke( void *internedStroke );

vkeyModifiers    vkeyParseModifiers(const vchar *s);

void		 vkeyDumpStroke(vkeyStroke stroke, FILE *fp);

/*
 ************************ Private ***************************
 */

#define vkeyGetStrokeKey( stroke )		((vkey)((stroke) >> 16))
#define vkeyGetStrokeModifiers( stroke )	((vkeyModifiers)((stroke) & \
								 0xFFFF))

#define vkeyComputeStroke( key, modifiers )	(((vkeyStroke)(key) << 16) | \
						 (modifiers))

#define vkeyToChar( key )    (sizeof(vchar) >= sizeof(vkey) ? (vchar)(key) : \
			      (((key) & (vchar)~0) == (key) ? (vchar)(key) : \
			       vkeyNULL_CHAR))

#define vkeyFromChar( c ) (sizeof(vkey) >= sizeof(vchar) ? (vkey)(c) : \
			      (((c) & (vkey)~0) == (c) ? (vkey)(c) : \
			       vkeyNULL))

#define vkeyHashModifiers vdictHashGeneric
#define vkeyInternModifiers(m) ((void*)((m)+1+(char*)NULL))
#define vkeyUninternModifiers(p) ((vkeyModifiers)((char*)(p)-1-(char*)NULL))

#define vkeyHashStroke vdictHashGeneric
#define vkeyInternStroke(s) ((void*)((s)+1+(char*)NULL))
#define vkeyUninternStroke(p) ((vkeyStroke)((char*)(p)-1-(char*)NULL))

 /* this was a typo, left for backward compatibility */
#define vkeyKEYPAD_SEPERATOR  vkeyKEYPAD_SEPARATOR 

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vkeyINCLUDED */

