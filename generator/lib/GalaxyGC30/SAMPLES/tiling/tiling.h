/* $Id: tiling.h,v 1.2 1995/01/20 23:43:02 alex Exp $ 
 ***************************************************************************
 *
 *  tiling.h
 *  C Interface to tiling
 *
 *  (c) Copyright Visix Software  1994
 *  All rights reserved
 *
 ***************************************************************************/

#define  PI 3.14159

#define  NumMaxGrid  13    /* maximal dimension of the grid  */

#define  SIZE_AUTO    0
#define  SIZE_SMALL   1
#define  SIZE_MEDIUM  2
#define  SIZE_LARGE   3

typedef double vector[3];

extern int     MaxGrid;         /* dimension of the grid                    */
extern int     MaxStep;
extern int     kdim;            /* coefficient for determination of MaxStep */
extern double  Rsize;
extern int     TilingSize;
extern vbool   bFillTiling;

extern double  alfa0;
extern double  alfa[NumMaxGrid+1];
extern double  d[NumMaxGrid+1];
extern vector  g[NumMaxGrid+1];

vbool ProcessVectors(vector, vector, double, double);
void  SetupParam(void);
void  DrawItemProc(vdialogItem *);

vbool  WriteIniFile(vresource);
vbool  ReadIniFile(vresource);





