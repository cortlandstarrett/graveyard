/* $Id: utility.c,v 1.2 1994/01/27 21:17:59 ian Exp $ */

/******************************************************************************
 * include files
 *****************************************************************************/

#include <vport.h>

#ifndef vdatatagINCLUDED
#include vdatatagHEADER
#endif

#ifndef vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef vsignatureINCLUDED
#include vsignatureHEADER
#endif

#include "utility.h"

/******************************************************************************
 * private constants
 *****************************************************************************/

#define NUM_COLORS           24
#define MAX_ITERATIONS     1000
#define MAX_MODULUS           4
#define UNSEED               -1

/******************************************************************************
 * private variables
 *****************************************************************************/

static int          *_colors = NULL;
static vdatatag     *_datatag = NULL;
static vsignature   *_signature = NULL;

static int           _bufferW;
static int           _bufferH;
static int          *_buffer;
static double        _setX;
static double        _setY;
static double        _deltaP;
static double        _deltaQ;

/******************************************************************************
 * private functions
 *****************************************************************************/

/*
 * utilityCalcMandelbrotPoint does the actual mendalbrot calculation for a
 *        given point.
 *  P -> the x part of the point
 *  Q -> the y part of the point
 *    <- the number of iterations it took
 */

static int _utilityCalcMandelbrotPoint(double P, double Q)
{
    register int  iterations;
    double        currentP, currentQ;
    double        lastP, lastQ;
    double        modulus;
    
    /*
     * pixel set up
     */
    
    lastP = lastQ = 0.0;
    iterations    = 0;
    modulus       = 0.0;
    
    /*
     * calculation to find number of iterations
     */
    
    while ((modulus < MAX_MODULUS) && (iterations < MAX_ITERATIONS))
    {
	currentP = lastP*lastP - lastQ*lastQ + P;
	currentQ = 2*lastP*lastQ + Q;
	iterations++;
	lastP = currentP;
	lastQ = currentQ;
	modulus = currentP*currentP + currentQ*currentQ;
    }
    
    return iterations;
}

static void _utilityCalcMandelbrotRecursively(int cellX, int cellY,
					      int cellW, int cellH)
{
    register int *bufferPtr;
    int           row, column;
    int           fill, fillSeed;
    int           iterations;
    int           cellX1, cellX2;
    int           cellY1, cellY2;
    int           cellW1, cellW2;
    int           cellH1, cellH2;
    double        P, Q;


    /*
     * Check if recursion is necessary
     */

    if (cellW <= 1 || cellH <= 1)
	return;

    /*
     * Set up all initializations for this recursion
     */

    fill      = TRUE;
    fillSeed  = UNSEED;
    
    /*
     * check the bottom edge ...
     */
    
    P = _setX + _deltaP*cellX;
    Q = _setY + _deltaQ*cellY;
    bufferPtr = _buffer + cellY*_bufferW + cellX;
    for (column = 0; column < cellW; column++)
    {
	/*
	 * if this point is not used, compute it
	 */

	if (*bufferPtr == UNSEED)
	{
	    iterations = _utilityCalcMandelbrotPoint(P, Q);
	    if (iterations == MAX_ITERATIONS)
		*bufferPtr = 0;
	    else 
		*bufferPtr = _colors[iterations%NUM_COLORS];
	}

	if (fillSeed == UNSEED)
	    fillSeed = *bufferPtr;
	else if (fillSeed != *bufferPtr)
	    fill = FALSE;

	P += _deltaP;
	bufferPtr++;
    }
    
    /*
     * check the top edge ...
     */
    
    P = _setX + _deltaP*cellX;
    Q = _setY + _deltaQ*(cellY + cellH - 1);
    bufferPtr = _buffer + (cellY + cellH - 1)*_bufferW + cellX;
    for (column = 0; column < cellW; column++)
    {
	/*
	 * if this point is not used, compute it
	 */

	if (*bufferPtr == UNSEED)
	{
	    iterations = _utilityCalcMandelbrotPoint(P, Q);

	    if (iterations == MAX_ITERATIONS)
		*bufferPtr = 0;
	    else 
		*bufferPtr = _colors[iterations%NUM_COLORS];
	}

	if (fillSeed != *bufferPtr)
	    fill = FALSE;

	P += _deltaP;
	bufferPtr++;
    }
    
    /*
     * check the left edge ...
     */
    
    P = _setX + _deltaP*cellX;
    Q = _setY + _deltaQ*(cellY + 1);
    bufferPtr = _buffer + (cellY + 1)*_bufferW + cellX;
    for (row = 1; row < cellH - 1; row++)
    {
	/*
	 * if this point is not used, compute it
	 */

	if (*bufferPtr == UNSEED)
	{
	    iterations = _utilityCalcMandelbrotPoint(P, Q);

	    if (iterations == MAX_ITERATIONS)
		*bufferPtr = 0;
	    else 
		*bufferPtr = _colors[iterations%NUM_COLORS];
	}

	if (fillSeed != *bufferPtr)
	    fill = FALSE;

	Q += _deltaQ;
	bufferPtr += _bufferW;
    }
    
    /*
     * check the right edge ...
     */
    
    P = _setX + _deltaP*(cellX + cellW - 1);
    Q = _setY + _deltaQ*(cellY + 1);
    bufferPtr = _buffer + (cellY + 1)*_bufferW + cellX + cellW - 1;
    for (row = 1; row < cellH - 1; row++)
    {
	/*
	 * if this point is not used, compute it
	 */

	if (*bufferPtr == UNSEED)
	{
	    iterations = _utilityCalcMandelbrotPoint(P, Q);

	    if (iterations == MAX_ITERATIONS)
		*bufferPtr = 0;
	    else 
		*bufferPtr = _colors[iterations%NUM_COLORS];
	}

	if (fillSeed != *bufferPtr)
	    fill = FALSE;

	Q += _deltaQ;
	bufferPtr += _bufferW;
    }
    
    /*
     * Now since the set is closed, if fill flag is still true, then we don't
     * need to calc the interior of the cell, because they are the same as
     * the boundings.
     */
    
    if (fill == TRUE)
    {
	bufferPtr = _buffer + (cellY + 1)*_bufferW + cellX + 1;
	for (row = 1; row < cellH - 1; row++)
	{
	    for (column = 1; column < cellW - 1; column++)
	    {
		*bufferPtr = fillSeed;

		bufferPtr++;
	    }
	    bufferPtr += _bufferW - cellW + 2;
	}
    }
    else
    {
	/*
	 * Recursively divide cell into 4 sub cells and conquer
	 */

	cellW1 = cellW/2;
	cellW2 = cellW - cellW1;
	cellX1 = cellX;
	cellX2 = cellX + cellW1;
	
	cellH1 = cellH/2;
	cellH2 = cellH - cellH1;
	cellY1 = cellY;
	cellY2 = cellY + cellH1;

	_utilityCalcMandelbrotRecursively(cellX1, cellY1, cellW1, cellH1);
	_utilityCalcMandelbrotRecursively(cellX2, cellY1, cellW2, cellH1);
	_utilityCalcMandelbrotRecursively(cellX1, cellY2, cellW1, cellH2);
	_utilityCalcMandelbrotRecursively(cellX2, cellY2, cellW2, cellH2);
    }
}

/*
 * _utilityShutdown cleans up
 */

static void _utilityShutdown(void)
{
    if (_signature != NULL)
    {
	vsignatureDestroy(_signature);
	_signature = NULL;
    }
    
    if (_datatag != NULL)
    {
	vdatatagDestroy(_datatag);
	_datatag = NULL;
    }

    if (_colors)
    {
	vmemFree(_colors);
	_colors = NULL;
    }

} /* _utilitySignatureShutdown */


/*
 * utilityStartup initializes utility module
 */

static void _utilityStartup(void)
{
    vcolorSpec		 spec;
    double		 hue;
    int			 loop;


    /*
     * Allocates an array of colors
     */

    _colors = (int *)vmemAllocAndClear((size_t)NUM_COLORS*sizeof(int));

    /*
     * initialize the colorSpec we are gonna use
     */

    vcolorInitSpec(&spec);
    for (loop = 0, hue = 0.0 ; loop < NUM_COLORS ; loop++)
    {
	/*
	 * build the spec
	 */
	
	vcolorSetSpecHLS(&spec,
			 hue * (vcolorCOMPONENT_MAX / 360.0),
			 vcolorCOMPONENT_MAX >> 1,
			 vcolorCOMPONENT_MAX);
	vcolorConvertSpec(&spec, vcolorGetRGBClass());
	
	/*
	 * build the true color number
	 */
	
	_colors[loop] = ((long)(vcolorGetSpecRGBRed(&spec) & 0xff00) << 8) +
	                ((long)(vcolorGetSpecRGBGreen(&spec) & 0xff00)) +
		        ((long)(vcolorGetSpecRGBBlue(&spec) & 0xff00) >> 8);
	
	/*
	 * take a color step
	 */
	
	hue += 360.0/NUM_COLORS;
    }
    
    /*
     * register to shut itself in the future-end
     */
    
    vclientRegisterShutdown(_utilityShutdown);
    
} /* utilityStartup */


/******************************************************************************
 * public functions
 *****************************************************************************/

/*
 * utilityAppendCellToImage appends cell to the image
 * image <-> image to have new cell
 * cellX  -> cell's X
 * cellY  -> cell's Y
 * cellW  -> cell's W
 * cellH  -> cell's H
 * buffer -> cell's data buffer
 */

void utilityAppendCellToImage(vimage *image,
			      int cellX, int cellY,
			      int cellW, int cellH, int *buffer)
{
    vpixmap		*pixmap;
    vpixmapScanner	 scanner;
    register int	 loopX, loopY;
    register int	*cell;
    
    /*
     * Get the pixmap and our scanner for the image
     */
    
    pixmap = vimageGetMap(image);
    vpixmapInitScanner(&scanner, pixmap);
    
    /*
     * fill the image
     */
    
    cell = buffer;
    for (loopY = 0; loopY < cellH; loopY++)
    {
	vpixmapMoveTo(&scanner, cellX, cellY + loopY);
	for (loopX = 0; loopX < cellW; loopX++)
	{
	    vpixmapWriteMoveRight(&scanner, *cell);
	    cell++;
	}
    }
    
    /*
     * Clean up from the setting
     */
    
    vpixmapDestroyScanner(&scanner);
    vpixmapMarkModified(pixmap);

} /* utilityProcessResults */

/*
 * _utilityCalcMandelbrot does the calculation for part of the mandelbrot image
 * imageW  -> the entire image width in pixels
 * imageH  -> the entire image height in pixels
 * cellX   -> cell x (lower left corner) relative to entire image
 * cellY   -> cell y (lower left corner) relative to entire image
 * cellW   -> cell width (no larger than imageW)
 * cellH   -> cell height (no larger than imageH)
 * buffer  <- the mandelbrot part enclosed in cell
 */

void utilityCalcMandelbrot(int imageW, int imageH,
			   int cellX, int cellY,
			   int cellW, int cellH,
			   double setX, double setY,
			   double setW, double setH,
			   int *buffer)
{
    int          *bufferPtr;
    
    
    /*
     * Initialization if necessary
     */

    if (_colors == NULL)
	_utilityStartup();

    /*
     * Set up 'static' initializations for recursions...
     */
    
    _deltaP = setW/imageW;
    _deltaQ = setH/imageH;
    _setX = setX + cellX*_deltaP;
    _setY = setY + cellY*_deltaQ;
    _bufferW = cellW;
    _bufferH = cellH;
    _buffer = buffer;

    /*
     * Mark all points in buffer as 'not used'
     */

    bufferPtr = buffer + cellW*cellH;
    do {
	bufferPtr--;
	*bufferPtr = UNSEED;
    } while (bufferPtr != buffer);

    /*
     * Recursively building mandelbrot part
     */

    _utilityCalcMandelbrotRecursively(0, 0, cellW, cellH);
    
} /* utilityCalcMandelbrot */

/*
 * utilityGetMandelbrotName returns the utility slave engine's name in a scribe
 * <- name of the utility engine in a scribe
 */

vscribe *utilityGetMandelbrotName(void)
{
    /*
     * Return the Image engine name
     */
    
    return vcharScribeLiteral("Mandelbrot Server");
    
} /* utilityGetSlaveName */

/*
 * utilityGetSignature returns signature for service primitive
 * <- signature 
 */

vsignature *utilityGetSignature(void)
    
{
    if (_signature != NULL)
	return _signature;
    
    _signature = vsignatureCreate();
    vsignatureSetTag(_signature, 
		     vnameInternGlobalLiteral("UtilitySignature"));
    
    if (_datatag == NULL)
    {
	_datatag = vdatatagCreateArray();
	vdatatagSetArrayDatatag(_datatag, vdatatagGetInteger());
    }
    vsignatureSetReturnDatatag(_signature, _datatag);
    
    /*
     * Set argument types
     */
    
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* imageW */
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* imageH */
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* cellX */
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* cellY */
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* cellW */
    vsignatureAppendDatatag(_signature, vdatatagGetInteger());  /* cellH */
    vsignatureAppendDatatag(_signature, vdatatagGetDoubleFloat());  /* setX */
    vsignatureAppendDatatag(_signature, vdatatagGetDoubleFloat());  /* setY */
    vsignatureAppendDatatag(_signature, vdatatagGetDoubleFloat());  /* setW */
    vsignatureAppendDatatag(_signature, vdatatagGetDoubleFloat());  /* setH */
    
    vclientRegisterShutdown(_utilityShutdown);
    
    return _signature;
}
