/* $Id: cview.c,v 1.4 1994/10/17 17:38:50 markd Exp $ */
/* The legal types make me put this in here.
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* cview.c -- implementation for a "container" for chart drawables
 *
 * Module:
 *	gchartview
 *
 * Descriptions and docs can be found in gcview.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _gchartviewCLASS_NAME "gchartview"


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  gcviewINCLUDED
#include "gcview.h"
#endif

#ifndef  gdrawableINCLUDED
#include "gdrawble.h"
#endif

#ifndef  gaccessorINCLUDED
#include "gaccess.h"
#endif




/*
 * ----- Module macros
 */

/* "dirty" refers to the state where the margins of the chartview aren't 
 * accurate, and will need to be recalculated.
 */
#define _setDirty(v)	((v)->flags |= _gchartviewDIRTY)
#define _clearDirty(v)	((v)->flags &= ~_gchartviewDIRTY)
#define _isDirty(v)	((v)->flags & _gchartviewDIRTY)
#define _dozenDirty(v)	((v)->flags |= _gcharviewCHARLES_BRONSON)




/*
 * ----- Module private globals
 */

/* this is the class that implements the default behavior for this 
 * module.  It's setup in gchartviewGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static gchartviewClass *defaultClass = NULL;




/*
 * ----- Chartview method implementation
 */


/* _gchartviewDarw -- draw the chartview into the current graphics state.
 *		      actually, it just tells the drawables to draw themselves
 *		      into the current graphics state.
 *
 *  -> view -- the chartview to render
 */
static void _gchartviewDraw (gchartview *view)
{
    int i;

    if (_isDirty(view)) {
        gchartviewAdjustMargins (view);
    }

    for (i = 0; i < view->drawableCount; i++) {
        gdrawableDraw (view->drawables[i]);
    }

} /* _gchartviewDraw */




/* _gchartviewAdjustMargins -- change the margins of all of the drawables so
 *			       that when they draw, they draw in the right
 *			       places.  i.e. if there is one drawable with
 *			       a bottom-X axis and other with the a top-X
 *			       axis, then both of them have margins set so
 *			       their chart rects won't overlap the other guys
 *			       axis
 *
 *  -> view -- the chartview to adjust the drawable margins for
 */
static void _gchartviewAdjustMargins (gchartview *view)
{
    int i;
    int top, left, bottom, right;
    int mtop, mleft, mbottom, mright;
    gdrawable *drawable;
    int width, height;

    _clearDirty (view);

    top = left = bottom = right = 0;

    for (i = 0; i < view->drawableCount; i++) {
        drawable = gchartviewGetDrawableAt (view, i);
        gdrawableGetNaturalAxisSize (drawable, &width, &height);

        if (gdrawableGetXPos(drawable) == gdrawableTOP_X) {
            top = vMAX (top, height);
        } else {
            bottom = vMAX (bottom, height);
        }
        
        if (gdrawableGetYPos(drawable) == gdrawableLEFT_Y) {
            left = vMAX (left, width);
        } else {
            right = vMAX (right, width);
        }
    }

    for (i = 0; i < view->drawableCount; i++) {
        mtop = top;
        mleft = left;
        mbottom = bottom;
        mright= right;
        
        drawable = gchartviewGetDrawableAt (view, i);

        if (gdrawableGetDrawX (drawable)) {
            if (gdrawableGetXPos(drawable) == gdrawableTOP_X) {
                mtop = 0;
            } else {
                mbottom  = 0;
            }
        }

        if (gdrawableGetDrawY (drawable)) {
            if (gdrawableGetYPos(drawable) == gdrawableRIGHT_Y) {
                mright = 0;
            } else {
                mleft = 0;
            }
        }

        gdrawableSetRect (drawable, &view->rect);
        gdrawableSetDrawableMargins (drawable, mtop, mleft, mbottom, mright);
    }

} /* _gchartviewAdjustMargins */




/* _gchartviewSetRect -- set the size of the chartview.  The drawables will
 *			 have their rects and margins adjusted accordingly.
 *
 *  -> view -- the view to set the rect for
 *  -> rect -- the rect to set it to.
 */
static void _gchartviewSetRect (gchartview *view, const vrect *rect)
{
    view->rect = *rect;
    _setDirty (view);
} /* _gchartviewSetRect */




/* _gchartviewAddDrawable -- add an drawable to the chartview
 *
 *  -> view     -- the chartview chart thingie
 *  -> drawable -- a new drawable that will draw a chart
 *
 * Generally, drawables added first will be drawn first, hence will be on
 * the "bottom" of the stack
 *
 * Ownership of the drawable does not transfer -- it's the client's 
 * responsibility to destroy it at the end of time.
 */
static void _gchartviewAddDrawable (gchartview *view, gdrawable *drawable)
{
    /* this same code exists in drawable.c.  If bugs are found here,
     * make the appropriate change in drawable.c */
    
    /* should use a smarter memory scheme */
    
    view->drawableCount++;
    view->drawables = (gdrawable**)vmemRealloc (view->drawables,
                                                sizeof(gdrawable*)
                                                * view->drawableCount);
    view->drawables[view->drawableCount-1] = drawable;

    _setDirty (view);
    
} /* _gchartviewAddDrawable */




/* _gchartviewRemoveDrawable -- remove the drawable from the chartview
 *
 *  -> view     -- the chartview to remove the drawable from
 *  -> drawable -- the drawable to remove.  An exception will be raised if
 * 		   this drawable isn't currently associated with the 
 *		   chartview.
 */
static void _gchartviewRemoveDrawable (gchartview *view, gdrawable *drawable)
{
    /* this same code exists in drawable.c.  If bugs are found here,
     * make the appropriate change in drawable.c */
    
    gdrawable **scan, **stop;

    /* find the first drawable */
    
    scan = view->drawables;
    stop = view->drawables + view->drawableCount;
    
    view->drawableCount--;

    while (scan < stop) {
        if (*scan == drawable) {
            break;
        }
        scan++;
    }

#if (vdebugDEBUG)
    /* not found! */
    if (scan == stop) {
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE,
                     "requested drawable isn't associated with given view",
                     vexPROC_NAME, "_gchartviewRemoveDrawable",
                     vexArgPOSITION, 2, vexNULL);
    }
#endif
    
    /* scoot everybody else down */
    while (scan < (stop-1)) {
        *scan = *(scan + 1);
        scan++;
    }

    _setDirty (view);
    

} /* _gchartviewRemoveDrawable */




/* _gchartviewGetDrawableAt -- return an drawable at a particular index
 *
 *  -> view -- the chartview to get an drawable from
 *  -> at   -- the index to get the accesor from
 *
 * If at is outside of the range of valid drawables, and exception will
 * be hurled.
 */
static gdrawable *_gchartviewGetDrawableAt (gchartview *view, int at)
{
    /* this same code exists in drawable.c.  If bugs are found here,
     * make the appropriate change in drawable.c */

    gdrawable *ret;

#if (vdebugDEBUG)
    if (   (at >= view->drawableCount)
        || (at < 0)) {
        vexGenerate (vexGetArgRangeClass(),
                     vexMESSAGE, "'at' argument out of range",
                     vexPROC_NAME, "_gchartviewGetDrawableAt",
                     vexArgPOSITION, 2,
                     vexNULL);
    }
#endif

    ret = view->drawables[at];
    return (ret);
} /* _gchartviewGetDrawableAt */




/*
 * ----- Object-level duties 
 */


/* _gchartviewLowInit -- shared initialization code between the INIT and
 * 			 LOAD_INIT overrides
 *
 *  -> view -- the chartview to initialize 
 */
static void _gchartviewLowInit (gchartview *view)
{
    view->flags = _gchartviewDIRTY;
    view->drawableCount = 0;
    view->drawables = (gdrawable**) vmemAlloc (sizeof(gdrawable*));
    vrectSet (0, 0, 100, 100, &view->rect);

} /* _gchartviewLowInit */




/* _gchartviewInit -- initialize a charview defaultily
 *
 *  -> view -- the chartview to initialize
 */
static void _gchartviewInit (gchartview *view)
{
    vclassSendSuper (defaultClass, vobjectINIT, (view));
    _gchartviewLowInit (view);
    _setDirty (view);
} /* _gchartviewInit */




/* _gchartviewLoadInit -- Initialize a chartview based on a resource template
 *
 *  -> view     -- the chartview to load from a resource
 *  -> resource -- the resource template to use to initialize this thingie.
 */
static void _gchartviewLoadInit (gchartview *view, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (view, resource));
    _gchartviewLowInit (view);
    _setDirty (view);
} /* _gchartviewLoadInit */




/* _gchartviewDestroy -- Annihilate this here pupper
 *
 *  -> view -- the pupper to nuke
 */
static void _gchartviewDestroy (gchartview *view)
{
    if (view->drawables != NULL) {
        vmemFree (view->drawables);
    }
    vclassSendSuper (defaultClass, vobjectDESTROY, (view));

} /* _gchartviewDestroy */




/*
 * ----- Managerial duties
 */


/* gchartviewDump -- dumps human-readable debugging information to a particular
 *		    stream.
 *
 *  -> chartview -- the chartview to dump
 *  -> stream   -- the stream to dump it into
 */
void gchartviewDump (gchartview *view, FILE *stream)
{
#if (vdebugDEBUG)

    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }

    fprintf (stream, "chartview: %p (%s)\n", view, 
             (gchartviewGetTag(view) == NULL) 
             ? "no tag"
             : (char*)gchartviewGetTag(view));
#endif

} /* gaccessrDump */




/* gchartviewGetDefaultClass -- Returns the callss used to create new instances
 *			       of gchartview objects.
 */
gchartviewClass *gchartviewGetDefaultClass (void)
{
    if (defaultClass == NULL) {

        defaultClass = vclassSpawn (vobjectGetDefaultClass(),
                                    sizeof (gchartviewClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_gchartviewCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (gchartview));

        vclassSet (defaultClass,
                   vobjectINIT,
                   _gchartviewInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _gchartviewLoadInit);

        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _gchartviewDestroy);

        vclassSet (defaultClass,
                   gchartviewDRAW,
                   _gchartviewDraw);

        vclassSet (defaultClass,
                   gchartviewSET_RECT,
                   _gchartviewSetRect);

        vclassSet (defaultClass,
                   gchartviewADD_DRAWABLE,
                   _gchartviewAddDrawable);

        vclassSet (defaultClass,
                   gchartviewREMOVE_DRAWABLE,
                   _gchartviewRemoveDrawable);

        vclassSet (defaultClass,
                   gchartviewGET_DRAWABLE_AT,
                   _gchartviewGetDrawableAt);

        vclassSet (defaultClass,
                   gchartviewADJUST_MARGINS,
                   _gchartviewAdjustMargins);
    }
    
    return (defaultClass);

} /* gchartviewGetDefaultClass */


/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */
