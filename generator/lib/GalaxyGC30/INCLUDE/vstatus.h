
/* $Id: vstatus.h,v 1.2 1996/09/01 06:36:28 abstine Exp $ */

/************************************************************

    vstatus.h

    C Interface file for status return information

    (c) Copyright 1996 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vstatusINCLUDED
#define vstatusINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif


/*===========================================================================*
 * * * * * * * * * * * *  PUBLIC  CONSTANT  DEFINITIONS  * * * * * * * * * * *
 *===========================================================================*/

/*
 * vstatus code severities
 */

#define vstatusWARNING        0x0       /* Warning                          */
#define vstatusSUCCESS        0x1       /* Successful completion            */
#define vstatusERROR          0x2       /* Error                            */
#define vstatusINFO           0x3       /* Information                      */
#define vstatusSEVERE         0x4       /* Severe error                     */


#define vstatusMASK_SUCCESS   0x1
#define vstatusFIELD_SUCCESS  0x00

/*
 * Some initial status codes
 */

/*
 * Warnings
 */

#define vstatusTIMED_OUT      0x10
#define vstatusINTERRUPTED    0x20
#define vstatusTRY_AGAIN      0x30
#define vstatusNULL           0x40

/*
 * Success and informational 
 */

/*
 * Errors
 */

#define vstatusIN_USE         0x12
#define vstatusNO_MEMORY      0x22

/*
 * Severe  (fatal) errors
 */

#define vstatusINVALID        0x14

/*===========================================================================*
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

/*
 * vstatus provides a formatted return result code
 * which fits into a 32 bit quantity
 *
 */
typedef union  
{
   struct
   {
      unsigned severity :  3;     /* severity code                    */
      unsigned id       : 25;     /* condition id                     */
      unsigned flags    :  4;     /* control bits                     */
   } _vstatus_bits0;

   struct
   {
      unsigned fill1    : 16;     /* skip severity and lower part     */
      unsigned _errno   : 16;     /* Unix errno                       */
   } _vstatus_bits1;

} vstatus;

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

/*===========================================================================*
 * * * * * * * * *  PUBLIC  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/


#define vstatusSuccess(code)    \
   (((code) & vstatusMASK_SUCCESS) >> vstatusFIELD_SUCCESS)

/*===========================================================================*
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
 *===========================================================================*/


/*===========================================================================*
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

#endif

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-argdecl-indent:3
 * c-brace-imaginary-offset:0
 * c-brace-offset:-3
 * c-continued-brace-offset:0
 * c-continued-statement-offset:3
 * c-indent-level:3
 * c-label-offset:-2
 * tab-width:8
 * End:
 */

