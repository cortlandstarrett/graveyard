/* $Id: boink.c,v 1.6 1996/08/21 15:37:20 david Exp $ */
/******************************************************************************
 *                  (c) Copyright 1993-94 Visix Software Inc.                 *
 *                            All rights reserved.                            *
 *                                                                            *
 *    The following Sample Code is provided for your reference purposes in    *
 *     connection with your use of the Galaxy Application Environment (TM)    *
 *     software product which you have licensed from Visix Software, Inc.     *
 * ("Visix"). The Sample code is provided to you without any warranty of any  *
 *     kind whatsoever and you agree to be responsible for the use and/or     *
 *   incorporation of the Sample Code into any software product you develop.  *
 *  You agree to fully and completely indemnify and hold Visix harmless from  *
 * any and all loss, claim, liability or damages with respect to your use of  *
 *    the Sample Code. Subject to the foregoing, you are permitted to copy,   *
 *   modify, and distribute the Sample Code for any purpose and without fee,  *
 * provided that (i) a copyright notice in the in the form of "Copyright 1992,*
 *  93 Visix Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All *
 * Rights Reserved" appears in all copies, (ii) both the copyright notice and *
 *  this permission notice appear in supporting documentation and (iii) you   *
 *            are a valid licensee of Galaxy Application Environment.         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * Description:                                                               *
 *     Beginnings of a program to test the ttask classes. To date (9/14/94)   *
 *     it only does very superficial testing.                                 *
 *                                                                            *
 *     Managers Used:                                                         *
 *         o Exception Manager - we create one or two subclasses AND show     *
 *           how a toplevel exception handler could be written to handle      *
 *           uncaught exceptions a bit more gracefully that abort()...        *
 *         o Debugging Manager - we include several examples of how the misc  *
 *           vdebug macros and routines can be used to implement argument,    *
 *           return-value, pre-post condition, and assertion checking...      *
 *         o Class Manager - we use to class manager to implement non-GUI     *
 *           classes as well as dialog item subclasses.                       *
 *         o Event Manager - if you've ever wanted to know how to use client  *
 *           events, you're looking at the right sample...specifically, we    *
 *           use client events to implement a "progress splash window" (ie.   *
 *           a splash window that shows the current point of initialization   *
 *           via a little status message).                                    *
 *                                                                            *
 * Modification History:                                                      *
 *     o 09-14-94: ssmc, created for The Galaxy Developers Conference 1994    *
 *                                                                            *
 * Special Usage Notes:                                                       *
 *     o <none>                                                               *
 *                                                                            *
 * Text Editor Formatting:                                                    *
 *     Symantec: Tab(4), Font(Any Fixed Width)                                *
 *     Emacs: see end of file for info                                        *
 *                                                                            *
 ******************************************************************************
 */
/*
 *+------------------------------------------------------------------------+
 * dependencies:
 *+------------------------------------------------------------------------+
 */

#include <vport.h>
#include vstdlibHEADER
#include vlimitsHEADER
#include vmathHEADER
#include vdebugHEADER
#include vexHEADER
#include vscribeHEADER
#include vnameHEADER
#include vpointHEADER
#include vrectHEADER
#include vresourceHEADER
#include vclientHEADER
#include vinstanceHEADER
#include vstdHEADER
#include vclassHEADER
#include vobjectHEADER
#include vcolorHEADER
#include vfontHEADER
#include vimageHEADER
#include vdrawHEADER
#include vlafHEADER
#include vwindowHEADER
#include vdialogHEADER

#include "ttask.h"
#include "boink.h"


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */


#if (vdebugDEBUG)
static const char *const _debugTag = "Boinkitem";
#define vdebugTAG _debugTag
#endif


#define CLASSNAME "Boinkitem"
#define FRAND() ((double)rand())


typedef struct _bitemClientGlobals {
	BoinkitemClass			*defaultClass;
	ttaskClass				*taskClass;
	BoinkitemGeoInitializer	 defaultgeometry;
	unsigned				 is3D;
}_bitemClientGlobals;

static void **mGlobals = NULL;
#define mgPtr ((_bitemClientGlobals*)*mGlobals)
#define BitemSendSuper(m,a) vclassSendSuper(mgPtr->defaultClass, m,a)
#define BitemGetClass(bi)	((BoinkitemClass*)vdialogGetItemClass(&(bi)->base))
#define BitemToItem(bi)		(&(bi)->base)
#define BitemIsOpen(bi)		vdialogItemIsOpen(&(bi)->base)


static void	BitemStartupClient(void);


/*
 *+------------------------------------------------------------------------+
 * public routines
 *+------------------------------------------------------------------------+
 */


BoinkitemClass*
BoinkitemGetDefaultClass(void)
{
	if (!mGlobals)
		mGlobals = vclientRegisterModule();
	if (!*mGlobals)
		BitemStartupClient();

	return mgPtr->defaultClass;
}



/* */
const BoinkitemGeoInitializer* BoinkitemGetDefaultGeometry(void)
{
	if (!mGlobals || !*mGlobals)
		(void)BoinkitemGetDefaultClass();
	
	return &mgPtr->defaultgeometry;
}



/*
 *+------------------------------------------------------------------------+
 * private implementation routines
 *+------------------------------------------------------------------------+
 */

#if 0
/* */
static void BitemDetermineXYOf(Boinkitem *bitem, vfont *font, 
							   const vchar *title, double *x, double *y)
{
	register double extH, strW, angle, ascH;
	int len = vcharLength(title);

	ascH  = (double)vfontAscent(font) * (double)bitem->scale.y;
	extH  = ((double)len*(double)bitem->a.y) * (double)bitem->scale.y;
	strW  = ((double)vfontStringWidthX(font, title) + (double)len*(double)bitem->a.x)
			 * (double)bitem->scale.y;

	angle = bitem->angle;
	*y    = sin(angle)*(0.5*strW) + cos(angle)*(0.5*extH + ascH);
	*x    = cos(angle)*(0.5*strW) + sin(angle)*(0.5*extH + ascH);
}
#endif


/* Workaround for HP compiler bug */
#define getirect(r,i) \
	r.x = vdialogGetItemX(i), r.y = vdialogGetItemY(i), \
	r.w = vdialogGetItemW(i), r.h = vdialogGetItemH(i)


/* */
static void BitemStamp(Boinkitem *bitem, int x, int y, int lineW,
					   const vchar *str)
{
	vrect r;

	getirect(r,BitemToItem(bitem));
	r.x -= x, r.y -= y;

	if (lineW)
		vrectInset(&r, lineW, lineW, &r);

	if (bitem->animate)
		{
			vdrawRectClip(r.x,r.y,r.w,r.h);
			vdrawMoveTo(r.x+bitem->o.x, r.y+bitem->o.y);
			
			vdrawFRotate(bitem->angle);
			vdrawFScale(bitem->scale.x, bitem->scale.y);

			vexWITH_HANDLING
			{
				vdrawShow(str);
			}
			vexON_EXCEPTION
			{
				if (vexGetArgException()==NULL)
					vexPropagate(NULL, vexNULL);
#if vdebugDEBUG
				else
					vexDumpChain(vdebugGetWarningStream());
#endif	
			}
			vexEND_HANDLING;
		}
	else
		vdrawRectShowCenter(str, &r);
}



/* */
static void BitemStampBorder(Boinkitem *bitem, int x, int y)
{
	vrect r;

	getirect(r,BitemToItem(bitem));
	r.x -= x, r.y -= y;

	if (mgPtr->is3D)
		{
			vcolorScheme scheme;
			vdialogDetermineItemColorScheme(BitemToItem(bitem),
				vcolorFLAG_SHADOW_TOP|vcolorFLAG_SHADOW_BOTTOM, &scheme);
			vdrawRectsHiliteStrokeInside
				(&r, 1, vcolorGetSchemeShadowBottom(&scheme),
				 vcolorGetSchemeShadowTop(&scheme));
		}
	else
		{
			vcolor *color = vdrawGetColor();
			vdrawSetColor(vcolorGetBlack());
			vdrawRectsStrokeInside(&r, 1);
			vdrawSetColor(color);
		}
}



/* */
static void BitemFormCumulative(Boinkitem *bitem)
{
	vdialogItem		*item;
	unsigned		 erase;

	vdebugMessagedAssert(bitem->animate, "form: requires animated mode!");

	vdrawGSave();
	item = BitemToItem(bitem);

	/*
	 * (Re)Create offscreen if necessary (resized, 1st-time, etc.)
	 */
	if ((erase = !bitem->history))
		bitem->history = vwindowCreateBufferImage
			(vdialogGetItemW(item), vdialogGetItemH(item));

	/*
	 * Make the offscreen target of following draw operations
	 */
	vdrawImageDevice(bitem->history);
	if (erase)
		{
			vrect r;
			getirect(r,item);
			r.x = r.y = 0;
			vdrawSetColor(vdialogDetermineItemBackground(item));
			vdrawRectsFill(&r, 1);
		}

	/*
	 * Use the item's current drawing context (font,color,etc)
	 */
	vdrawSetColor(vdialogDetermineItemForeground(item));
	vdrawSetFont(vdialogDetermineItemFont(item));

	BitemStamp(bitem, vdialogGetItemX(item), vdialogGetItemY(item), 
			   0, vdialogGetItemTitle(item));

	vdrawGRestore();

	if (vdialogItemHasBorder(item)) {
		vdrawGSave(); /* !ack! */
		vdrawImageDevice(bitem->history);
		BitemStampBorder(bitem, vdialogGetItemX(item), vdialogGetItemY(item));
		vdrawGRestore();
	}
}



/* */
static void BitemDrawSingle(Boinkitem *bitem)
{
	vdialogItem		*item;
	vcolor			*color;

	vdrawGSave();

	item  = BitemToItem(bitem);
    color = vdrawGetColor();

	vdrawSetColor(vdrawGetComplement());
	vdrawRectsFill(vdialogGetItemRect(item), 1);
	vdrawSetColor(color); 

	BitemStamp(bitem, 0, 0, 0, vdialogGetItemTitle(item));

	vdrawGRestore();
}



/* */
static void BitemDrawCumulative(Boinkitem *bitem)
{
	register vdialogItem *item;

	if (!bitem->history)
		BitemFormCumulative(bitem);

	item = BitemToItem(bitem);
	vdrawGSave();
	
	vdrawMoveTo(vdialogGetItemX(item), vdialogGetItemY(item));
	vdrawImageIdent(bitem->history);

	vdrawGRestore();
}



/* */
static void BitemClearHistory(Boinkitem *bitem)
{
	if (bitem->history)
		{
			vimageDestroy(bitem->history);
			bitem->history = NULL;
		}
}



/* */
static void BitemChangedAttributt(Boinkitem *bitem, const vname *attr, 
								  vdict *context)
{
	if (bitem->history)
		{
			vbool border_change = vFALSE;
			vdialogItem *item = BitemToItem(bitem);
			vdict *dict = vclassGet
				(BitemGetClass(bitem), vobjectID_ATTRIBUTE_DICT);

			switch (vdictLoadScalar(dict, attr))
			{
				/* >> default method invals itemrect w/ erasing -- we don't
				      want this behavior since there are no visual changes
				      for animating cumulative boink items! << */
    			case vdialogITEM_ID_ATTRIBUTE_LINE_WIDTH:
    			case vdialogITEM_ID_ATTRIBUTE_BORDER:
					border_change = vTRUE;
					/* >> fall-through << */

				case vdialogITEM_ID_ATTRIBUTE_TITLE:
    			case vdialogITEM_ID_ATTRIBUTE_FONT:
    			{
    				if (!bitem->animate || !bitem->cumulative)
    					break;
					vdialogChangedItemAttributeNone(item, vname_MinSize);
					if (vdialogGetItemItemList(item))
						vdialogChangedItemListChildAttribute
							(vdialogGetItemItemList(item), attr, context);
					if (border_change)
						vdialogInvalItem(item, vwindowINVAL_OPAQUE);
					return;
				}

				case vdialogITEM_ID_ATTRIBUTE_RECT:
				case vdialogITEM_ID_ATTRIBUTE_STATE:
				case vdialogITEM_ID_ATTRIBUTE_BOUNDS:
				case vdialogITEM_ID_ATTRIBUTE_BACKGROUND:
				case vdialogITEM_ID_ATTRIBUTE_COLOR: /* ? what's dis ? */
				{
					if (bitem->history)
						BoinkitemClear(bitem);
					break;
				}
			}
		}

	BitemSendSuper(vobjectCHANGED_ATTRIBUTE, (bitem, attr, context));
}



/* */
static vtimestamp BitemGetPeriod(Boinkitem *bitem)
{
	vtimestamp zero;
	vtimestamp period;

	zero = vtimestampMake(0,0);
	if (bitem->ownPeriod)
		period = bitem->period;
	else
		period = vclassGet(BitemGetClass(bitem), BoinkitemSPEED);
	
	if (vtimestampEqualTo(period, zero))
		period = vtimestampMake(1, 0);
	
	return period;
}



/* */
static void BitemSetPeriod(Boinkitem *bitem, vtimestamp *period)
{
	vtimestamp zero;
	unsigned old    = bitem->ownPeriod;

	zero = vtimestampMake(0,0);
	if (!period || vtimestampEqualTo(*period, zero))
		{
			bitem->period    = zero;
			bitem->ownPeriod = 0;
		}
	else
		{
			bitem->period    = *period;
			bitem->ownPeriod = 1;
		}
	
	if ((old != bitem->ownPeriod) && bitem->task)
		ttaskSetMinDelay(bitem->task, 
						 bitem->ownPeriod ? &bitem->period : NULL);
}



/* */
static void BitemRandomize(Boinkitem *bitem, unsigned b)
{
	bitem->randomGeo = b ? 1 : 0;
}



/* */
static ttask* BitemMakeBoinkisizer(Boinkitem *bitem)
{
	register ttask *boink;
	vtimestamp delay;

	boink = ttaskCreateOfClass(mgPtr->taskClass);
	delay = BoinkitemGetPeriod(bitem);
	ttaskSetMinDelay(boink, &delay);
	ttaskSetMaxIterations(boink, USHRT_MAX-1);
	
	ttaskDescribeAsScribed(boink, vcharScribeLiteral("Boinkisizer"));
	ttaskSetData(boink, bitem);

	return boink;
}



/* */
static void BitemAutoFeed(register Boinkitem *bitem)
{
	if (!BitemIsOpen(bitem) || bitem->autoOn)
		return;

	vdebugIF(!bitem->animate, vexGenerate(vexGetValueClass(),
			 vexMESSAGE, "autofeed: requires animation mode!", 
			 vexERRNO, 0, vexNULL));

	bitem->autoOn = vTRUE;

	if (!bitem->task)
		bitem->task = BitemMakeBoinkisizer(bitem);
	else if (ttaskIsBlocked(bitem->task))
		ttaskUnBlock(bitem->task);

	ttaskPost(bitem->task);
}



/* */
static void BitemStopFeed(register Boinkitem *bitem)
{
	if (bitem->task && !ttaskIsBlocked(bitem->task))
		if (BitemIsOpen(bitem))
			ttaskBlock(bitem->task, NULL);
		else
			ttaskDestroy(bitem->task), bitem->task = NULL;
	
	bitem->autoOn = vFALSE;
}



/* */
static void BitemAnimate(Boinkitem *bitem, unsigned want)
{
	unsigned old = bitem->animate;
	bitem->animate = want ? 1 : 0;
	if (old == bitem->animate)
		return;

	if (!want && bitem->autoOn)
		BoinkitemStopAutopilot(bitem);
	
	if (!want && bitem->cumulative)
		{
			BoinkitemClear(bitem);
			vdialogInvalItem(BitemToItem(bitem), 0);
		}
}



/* */
static void BitemOpen(Boinkitem *bitem)
{
	if (BitemIsOpen(bitem))
		return;

	BitemSendSuper(vdialogOPEN_ITEM, (bitem));

	if (bitem->prefAutoOn && bitem->animate)
		BoinkitemAutopilot(bitem);
}



/* */
static void BitemClose(Boinkitem *bitem)
{
	unsigned stop = BitemIsOpen(bitem) && bitem->autoOn;
	
	BitemSendSuper(vdialogCLOSE_ITEM, (bitem));
	
	if (stop)
		BoinkitemStopAutopilot(bitem);
}



/* */
static void BitemAccumulate(Boinkitem *bitem, unsigned want)
{
	unsigned old      = bitem->cumulative;
	bitem->cumulative = want ? 1 : 0;

	if (bitem->animate && (old != bitem->cumulative))
		{
			BoinkitemClear(bitem);
			vdialogInvalItem(BitemToItem(bitem), 0);
		}
}



/* */
static void BitemDraw(Boinkitem *bitem)
{
	if (bitem->animate && bitem->cumulative)
		BitemDrawCumulative(bitem);
	else
		BitemDrawSingle(bitem);
}



/* */
static void BitemRandomTranslate(Boinkitem *bitem)
{
	if (bitem->animate)
		{
			bitem->o.x = rand() % vdialogGetItemW(BitemToItem(bitem));
			bitem->o.y = rand() % vdialogGetItemH(BitemToItem(bitem));

			if (BitemIsOpen(bitem))
				{
					if (bitem->cumulative)
						BitemFormCumulative(bitem);
					
					vdialogInvalItem(BitemToItem(bitem), bitem->cumulative
						? vwindowINVAL_OPAQUE | vwindowINVAL_UPDATE
						: vwindowINVAL_UPDATE);
				}
		}
}



/* */
static void BitemPull(Boinkitem *bitem, unsigned right)
{
	if (BitemIsOpen(bitem) && bitem->animate && bitem->cumulative)
		{
			vfont *font;
			int dx,dy;
			register int i;

			font = vdialogDetermineItemFont(BitemToItem(bitem));
			dx = vfontWidthX(font), dy = vfontHeight(font)/2;
			if (!dy) 
				dy = 7;
			if (right) 
				dy = -dy;
			for (i= 0; i<2; i++)
				{
					bitem->o.x += dx, bitem->o.y += dy;
					BitemFormCumulative(bitem);
				}
			vdialogInvalItem(BitemToItem(bitem), 
							 vwindowINVAL_OPAQUE | vwindowINVAL_UPDATE);
		}
}



/* */
static void BitemMove(Boinkitem *bitem, 
					  const BoinkitemGeoInitializer *geo)
{
	if (bitem->animate)
		{
			if (!geo) geo = &mgPtr->defaultgeometry;
			bitem->angle  = geo->angle;
			bitem->scale  = geo->scale;
			bitem->a      = geo->a;
			BoinkitemRandomTranslate(bitem);
		}
}



/* */
static void BitemCommonInit(register Boinkitem *bitem)
{
	register BoinkitemGeoInitializer *geo=
		&mgPtr->defaultgeometry;
	
	bitem->angle		= geo->angle;
	bitem->scale		= geo->scale;
	bitem->a			= geo->a;
	bitem->o.x          = bitem->o.y = 0;
	bitem->history		= NULL;
	bitem->task			= NULL;
	bitem->period		= vtimestampMake(0,0);
	bitem->prefAutoOn	= vTRUE;
	bitem->cumulative	= vTRUE;
	bitem->ownPeriod	= vFALSE;
	bitem->animate		= vTRUE;
	bitem->autoOn		= vFALSE;
	bitem->randomGeo    = vTRUE;
}



/* */
static void BitemCommonCopy(Boinkitem *from, Boinkitem *copy)
{
	copy->angle			= from->angle;
	copy->scale			= from->scale;
	copy->a				= from->a;
	copy->o         	= from->o;
	copy->history		= from->history ? vimageClone(from->history) : NULL;
	copy->task			= NULL;
	copy->period		= from->period;
	copy->prefAutoOn	= from->prefAutoOn;
	copy->cumulative	= from->cumulative;
	copy->ownPeriod		= from->ownPeriod;
	copy->animate		= from->animate;
    copy->randomGeo     = from->randomGeo;
	copy->autoOn		= vFALSE;
}



/* */
static void BitemInit(Boinkitem *bitem)
{
	BitemSendSuper(vinstanceINIT, (bitem));
	BitemCommonInit(bitem);
}



/* */
static void BitemLoadInit(Boinkitem *bitem, vresource res)
{
	BitemSendSuper(vobjectLOAD_INIT, (bitem, res));
	BitemCommonInit(bitem);
}



/* */
static void BitemCopy(Boinkitem *from, Boinkitem *copy)
{
	if (copy->autoOn)
		BoinkitemStopAutopilot(copy);
	
	if (copy->task)
		ttaskDestroy(copy->task), copy->task = NULL;

	if (copy->history)
		BoinkitemClear(copy);

	BitemSendSuper(vobjectCOPY, (from, copy));
	
	BitemCommonCopy(from, copy);
}



/* */
static void BitemCopyInit(Boinkitem *from, Boinkitem *copy)
{
	BitemSendSuper(vobjectCOPY_INIT, (from, copy));
	
	BitemCommonCopy(from, copy);
}



/* */
static void BitemDestroy(Boinkitem *bitem)
{
	if (bitem->task)
		ttaskDestroy(bitem->task);

	if (bitem->history)
		BoinkitemClear(bitem);

	BitemSendSuper(vinstanceDESTROY, (bitem));
}



/* */
static void BitemGetMinSize(Boinkitem *bitem, int *w, int *h)
{
	*w = 150, *h = 150;
}



/* */
static void BtaskIgnoreAdvance(ttask *task, unsigned short ignored)
{
	/*
	 * No-Op...
	 */
}



/* */
static unsigned BtaskGoForever(ttask *task)
{
	/*
	 * Go forever...unless stopped :)
	 */
	return !ttaskIsBlocked(task);
}



/* */
static void BtaskExecute(ttask *task)
{
#define RC() 	 ((rand() << 2) % vcolorCOMPONENT_MAX)
#define RN(f)    (rand() % (f))

    Boinkitem		*bitem = (Boinkitem*)ttaskGetData(task);
    vdialogItem		*item  = BitemToItem(bitem);
    vfontFamily		*famy;
    vfontFace		*face;
    vfont			*font;
    vcolorSpec		 sp;
	unsigned		 pull;
    BoinkitemGeoInitializer geo;

    /*
     * Assume item to "boinkisize" is stored in moi's data field
     * NOTE: If the item hasn't opened yet, don't do anything!
     */
    if (!BitemIsOpen(bitem))
        return;

    /*
     * Switch colors...(check monochrome?)
     */
    vcolorInitSpecSpecific(&sp, vcolorGetRGBClass());
    vcolorSetSpecRGB(&sp, RC(), RC(), RC());
    vdialogSetItemForeground(item, vcolorInternSpec(&sp));
    vcolorDestroySpec(&sp);


    /*
     * Switch fonts...Make sure there are faces/fonts to switch
	 * between...
     */
	font = vdialogDetermineItemFont(item);
	famy = vfontGetFaceFamily(vfontGetFace(font));
	if (vfontGetFamilyFaceCount(famy)>0)
		{
			face = vfontGetFamilyFaceAt
				(famy, RN(vfontGetFamilyFaceCount(famy)));

			if (vfontGetFaceFontCount(face)>0)
				{
					font = vfontGetFaceFontAt
						(face, RN(vfontGetFaceFontCount(face)));;
					vdialogSetItemFont(item, font);
				}
		}

    /*
     * Switch spatial orientation...
     */
	pull = 0;

	if (!bitem->randomGeo)
		{
			geo = mgPtr->defaultgeometry;
			if (bitem->cumulative)
				pull = (rand() % 7) == 0;
		}
	else
		{
			geo.a.x = geo.a.y = 0;
			
			if ((rand() % 5) == 0)
				geo.angle = 0.;
			else {
				geo.angle = fmod(FRAND(), 90.);
				if ((rand() % 5) == 0)
					geo.angle *= -1.;
			}
			if ((rand() % 2) == 0) {
				geo.scale.x = geo.scale.y = 1.;
			}
			else {
				double d = FRAND() / FRAND();
				if (d<.5) d = .5;
				else if (d>2.) d = 2.;
				geo.scale.x = d;
				d = FRAND() / FRAND();
				if (d<.5) d = .5;
				else if (d>2.) d = 2.;
				geo.scale.y = d;
			}
		}

    BoinkitemMove(bitem, &geo);
    
	if (pull)
		BitemPull(bitem, (rand() % 2)!=0);

#undef RC
#undef RN
}



/* */
static void BitemStartupClient(void)
{
	register BoinkitemGeoInitializer *geo;
	register BoinkitemClass *clas;
	register ttaskClass *tclas;

	vclientAllocateModule(mGlobals, sizeof(_bitemClientGlobals));

	clas = vclassSpawn(vdialogGetDefaultItemClass(), sizeof(BoinkitemClass));
	mgPtr->defaultClass = clas;
	vclassSetNameScribed(clas, vcharScribeLiteral("Boinkitem"));
	vclassSetObjectSize(clas, sizeof(Boinkitem));

	vclassSet(clas, vinstanceINIT, BitemInit);
	vclassSet(clas, vinstanceDESTROY, BitemDestroy);
	vclassSet(clas, vobjectLOAD_INIT, BitemLoadInit);
	vclassSet(clas, vobjectCOPY_INIT, BitemCopyInit);
	vclassSet(clas, vobjectCOPY, BitemCopy);
	vclassSet(clas, vobjectCHANGED_ATTRIBUTE, BitemChangedAttributt);
	
	vclassSet(clas, vdialogGET_ITEM_MIN_SIZE, BitemGetMinSize);
	vclassSet(clas, vdialogOPEN_ITEM, BitemOpen);
	vclassSet(clas, vdialogCLOSE_ITEM, BitemClose);
	vclassSet(clas, vdialogDRAW_ITEM, BitemDraw);
	
	vclassSet(clas, BoinkitemSPEED, vtimestampMake(1, 0));
	vclassSet(clas, BoinkitemAUTO_FEED, BitemAutoFeed);
	vclassSet(clas, BoinkitemSTOP_FEED, BitemStopFeed);
	vclassSet(clas, BoinkitemGET_PERIOD, BitemGetPeriod);
	vclassSet(clas, BoinkitemCLEAR, BitemClearHistory);
	vclassSet(clas, BoinkitemSET_PERIOD, BitemSetPeriod);
	vclassSet(clas, BoinkitemACCUMULATE, BitemAccumulate);
	vclassSet(clas, BoinkitemRANDOM_TRANSLATE, BitemRandomTranslate);
	vclassSet(clas, BoinkitemMOVE, BitemMove);
	vclassSet(clas, BoinkitemANIMATE, BitemAnimate);
	vclassSet(clas, BoinkitemRANDOMIZE_GEO, BitemRandomize);

	tclas = vclassReproduce(ttaskGetDefaultClass());
	mgPtr->taskClass = tclas;
	vclassSetNameScribed(tclas, vcharScribeLiteral("Boinktask"));
	vclassSet(tclas, ttaskEXECUTE, BtaskExecute);
	vclassSet(tclas, ttaskGET_AGAIN, BtaskGoForever);
	vclassSet(tclas, ttaskADVANCE, BtaskIgnoreAdvance);

	geo = &mgPtr->defaultgeometry;
	geo->angle   = 0.0; 
	geo->scale.x = 1.0;
	geo->scale.y = 1.0;
	geo->a.x     = 0;
	geo->a.y     = 0;
	
	mgPtr->is3D = vlaf3D();
}


/*
 *+------------------------------------------------------------------------+
 * emacs editor formatting information:
 *+------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 64 72 80 88 96 104)
 * tab-width:4
 * indent-tabs-mode:t
 * truncate-lines:t
 * End:
 */
