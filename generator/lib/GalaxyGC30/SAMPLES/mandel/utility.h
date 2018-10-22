/* $Id: utility.h,v 1.1 1994/01/25 22:52:44 ian Exp $ */

/******************************************************************************
 * include files
 *****************************************************************************/

#ifndef vimageINCLUDED
#include <vimage.h>
#endif

#ifndef vrectINCLUDED
#include <vrect.h>
#endif 

#ifndef vsignatureINCLUDED
#include <vsignature.h>
#endif

#ifndef vscribeINCLUDED
#include <vscribe.h>
#endif

#ifndef vcolorINCLUDED
#include <vcolor.h>
#endif

/******************************************************************************
 * public data structure
 *****************************************************************************/

typedef struct data {
    int		 imageW, imageH;
    int          cellX, cellY;
    int		 cellW, cellH;
    double	 minP, minQ;
    double	 maxP, maxQ;
    int         *buffer;
} utilityData;

/******************************************************************************
 * public functions
 *****************************************************************************/

vscribe		*utilityGetMandelbrotName(void);
vsignature      *utilityGetSignature(void);
void             utilityAppendCellToImage(vimage *image,
					  int cellX,
					  int cellY,
					  int cellW,
					  int cellH,
					  int *buffer);
void             utilityCalcMandelbrot(int imageW, int imageH,
				       int cellX, int cellY,
				       int cellW, int cellH,
				       double setX, double setY,
				       double setW, double setH,
				       int *buffer);



