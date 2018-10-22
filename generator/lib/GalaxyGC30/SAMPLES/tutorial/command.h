#ifndef commandINCLUDED
#define commandINCLUDED

/******************************************************************************
*	$Header: /visix/vsx/arch/src/vtutor2/RCS/command.h,v 1.3 1993/12/07 05:12:35 jim Exp $
*
*       command.h
*
*       (C) Copyright 1992-1993 Visix Software Inc.
*           All Rights Reserved
*
******************************************************************************/

#include <vport.h> /* for v*HEADER */

/* Galaxy Includes */
#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

/* macros for keystroke definitions */
#define vPLAIN(k)       vkeyComputeStroke(k, 0)
#define vSHIFT(k)       vkeyComputeStroke(k, vkeyMODIFIER_KEY_SHIFT)
#define vCTRL(k)        vkeyComputeStroke(k, vkeyMODIFIER_KEY_CTRL)
#define vCOMMAND(k)     vkeyComputeStroke(k, vkeyMODIFIER_KEY_COMMAND)
#define vSHIFT_COMMAND(k) \
    vkeyComputeStroke(k, vkeyMODIFIER_KEY_SHIFT|vkeyMODIFIER_KEY_COMMAND)
#define vSHIFT_CTRL(k) \
    vkeyComputeStroke(k, vkeyMODIFIER_KEY_SHIFT|vkeyMODIFIER_KEY_CTRL)
#define vALT(k)         vkeyComputeStroke(k, vkeyMODIFIER_KEY_ALT) 

typedef struct {
  const char *tag;
  short       value;
  vkeyStroke  key;
} commandInitializer;

vdict *commandCreateCommandDict (commandInitializer *commands, 
				 vcommandSelectorClass *selectorClass);
vdict *commandCreateStateDict (commandInitializer *states);
vdict *commandCreateKeyDict (commandInitializer *keys);

#endif
