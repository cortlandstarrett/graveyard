/* $Id: statitem.c,v 1.4 1996/11/05 20:37:15 lis Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module implements the graphic/text status box item used by the  *
 *     isnoop application. it is _not_ a general purpose status item!       *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#include <vport.h>
#include vstdioHEADER
#include vstdlibHEADER
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vresourceHEADER
#include vclassHEADER
#include vimageHEADER
#include vrectHEADER
#include vfontHEADER
#include vdrawHEADER
#include veventHEADER
#include vclientHEADER
#include vstdHEADER
#include vdialogHEADER

#include "names.h"
#include "statitem.h"


/* define our vdebug module tag */
#if vdebugDEBUG
static const char *const _boxTag = "statusbox";
#define vdebugTAG _boxTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private class definition
 *+------------------------------------------------------------------------+
 */
typedef struct statusbox {
  vdialogItem		item;		/* super */
  vstr         	       *message;	/* string message */
  int			number;		/* number of images in graphic */
  vimage       	       *image;		/* offscreen graphic */
  vimage	       *wholeimage, *pieceimage; /* graphic images */
  unsigned short	delay;		/* delay before flash message erased */
  unsigned short	flashes;	/* used to "flash" temporary message */
  unsigned		gmode:1;	/* vTRUE if in graphics "mode" */
  unsigned		wholeshared:1;	/* vTRUE if image shared */
  unsigned		pieceshared:1;	/* vTRUE if image shared */
}statusbox;

typedef struct statusboxClass statusboxClass;

#define statusboxCLASS(CLASS, BOX)					\
  vdialogITEM_CLASS(CLASS, BOX, vdialogItemNoteProc);			\
  vclassMETHOD(statusboxZERO, (BOX*));					\
  vclassMETHOD(statusboxSET_NUMBER, (BOX*, int));			\
  vclassMETHOD(statusboxSET_MESSAGE, (BOX*, vstr*));			\
  vclassMETHOD(statusboxFLASH_MESSAGE, (BOX*, vstr*));			\
  vclassMETHOD(statusboxSET_FLASH_DELAY, (BOX*, unsigned short));	\
  vclassMETHOD(statusboxSET_IMAGE, (BOX*,int,vimage*,int))

struct statusboxClass {
  statusboxCLASS(statusboxClass, statusbox);
};

#define sendsuper(m,a)		\
  vclassSendSuper(_defaultClass, m,a)
#define getclass(b)		\
  ((statusboxClass*)vdialogGetItemClass(&(b)->item))
#define send(b,m,a)		\
  vclassSend(getclass(b),m,a)

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */
#define H_MARGIN		5
#define V_MARGIN		2
#define I_SPACING		2

static vstr		*_ellipses = NULL;
static vimage		*_whole = NULL;
static vimage		*_piece = NULL;
static statusboxClass	*_defaultClass = NULL;
static int		 _initialized = vFALSE;

static void		startup(vresource);
static void		registerclass(void);
#if vmemBALANCE
static void		statitemshutdown(void);
#endif

static void		setdefaults(statusbox*);
static void		init(statusbox*);
static void		nuke(statusbox*);
static void		load(statusbox*, vresource);
static void		copy(statusbox*, statusbox*);
static void		copyinit(statusbox*, statusbox*);
static void		clear(statusbox*);
static void		minsize(statusbox*, int*, int*);
static void		naturalsize(statusbox*, int*, int*);
static void		setrect(statusbox*, const vrect*);
static void		formimage(statusbox*);
static void		makeimage(statusbox*);
static void		draw(statusbox*);
static void		setnumber(statusbox*, int);
static void		setmessage(statusbox*, vstr*);
static int		handleflash(vevent*);
static void		flash(statusbox*, vstr*);
static void		setdelay(statusbox*, unsigned short);
static void		setimage(statusbox*, int, vimage*, int);

/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

void
statusboxStartupManager(vresource imagesdata)
{
  vdebugIF((imagesdata==vresourceNULL), 
	   vexGenerate(vexGetModuleStartupClass(), vexMESSAGE, 
		       "startup manager: invalid images resource!",
		       vexERRNO, 0, vexNULL));
  if (!_initialized)
    startup(imagesdata);

#if vdebugDEBUG
  else
    vdebugTrace("multiple init attempted...ignoring!\n");
#endif

  return;
}



const vdialogItemClass *
statusboxGetDefaultClass(void)
{
  vdebugIF((!_initialized), vexGenerate(vexGetModuleStateClass(), vexMESSAGE,
	   "get default class: NOT initialized!", vexERRNO, 0,
           vexNULL));

  return (const vdialogItemClass*)_defaultClass;
}



void
statusboxFlashMessageOwned(vdialogItem *item, vstr *message)
{
  register statusbox *box;

#if vdebugDEBUG
  if (!item || !message)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "flash message owned: "
                "NULL argument(s)!", vexERRNO, 0, vexNULL);
  if (!vobjectIsKindOf(vdialogGetItemObject(item), _defaultClass))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "flash message owned: given "
                "item is not a statusbox item!", vexERRNO, 0, vexNULL);
#endif

  box = (statusbox*)item;
  if (!box->gmode) {
    box->flashes++;
    send(box, statusboxFLASH_MESSAGE, (box,message));
  }
  else
    vstrDestroy(message);
  return;
}



void
statusboxTurnOnGraphicsMode(vdialogItem *item)
{
  register statusbox *box;
  unsigned short flashes;

#if vdebugDEBUG
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "turn on graphics: "
                "NULL argument!", vexERRNO, 0, vexNULL);
  if (!vobjectIsKindOf(vdialogGetItemObject(item), _defaultClass))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "turn on graphics: given "
                "item is not a statusbox item!", vexERRNO, 0, vexNULL);
#endif

  box = (statusbox*)item;
  vdebugIF((box->gmode), vdebugTrace("multiple graphic modes"));

  flashes = box->flashes;
  send(box, statusboxZERO, (box));
  box->flashes = flashes;
  box->gmode = vTRUE;

  vdialogInvalItem(&box->item, 0);

  return;
}



void
statusboxUpdateImageCount(vdialogItem *item, int delta)
{
  register statusbox *box;

#if vdebugDEBUG
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "update image count: "
                "NULL argument!", vexERRNO, 0, vexNULL);
  if (!vobjectIsKindOf(vdialogGetItemObject(item), _defaultClass))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "update image count: given "
                "item is not a statusbox item!", vexERRNO, 0, vexNULL);
#endif

  if (delta) {
    box = (statusbox*)item;
    if (!box->gmode) 
      statusboxTurnOnGraphicsMode(item);
    if (delta<0 && (box->number+delta<0)) 
      vexGenerate(vexGetValueRangeClass(), vexMESSAGE, 
		  "delta will put value to negative", vexNULL);
    send(box, statusboxSET_NUMBER, (box, box->number+delta));
  }
  return;
}



void
statusboxTurnOffGraphicsMode(vdialogItem *item)
{
  register statusbox *box;
  unsigned short flashes;

#if vdebugDEBUG
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "turn off graphics: "
                "NULL argument!", vexERRNO, 0, vexNULL);
  if (!vobjectIsKindOf(vdialogGetItemObject(item), _defaultClass))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "turn off graphics: given "
                "item is not a statusbox item!", vexERRNO, 0, vexNULL);
#endif

  box = (statusbox*)item;
  vdebugIF(!box->gmode, 
	   vdebugTrace("unmatched graphic mode pop"));

  flashes = box->flashes;
  send(box, statusboxZERO, (box));
  box->flashes = flashes;
  vdialogInvalItem(&box->item, 0);

  return;
}



void
statusboxSetGraphicImages(vdialogItem *item, vimage *whole, vimage *piece)
{
  register statusbox *box;


#if vdebugDEBUG
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "turn off graphics: "
                "NULL argument!", vexERRNO, 0, vexNULL);
  if (!vobjectIsKindOf(vdialogGetItemObject(item), _defaultClass))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "turn off graphics: given "
                "item is not a statusbox item!", vexERRNO, 0, vexNULL);
#endif

  box = (statusbox*)item;
  send(box, statusboxSET_IMAGE, (box, statusboxWHOLE_IMAGE, whole, vTRUE));
  send(box, statusboxSET_IMAGE, (box, statusboxPIECE_IMAGE, piece, vTRUE));

  return;
}


/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

static void
startup(vresource data)
{
  register vresource img;

  vexWITH_HANDLING {
    _ellipses = vresourceGetString(data, appname_StatusBoxIdleString);
    img = vresourceGet(data, appname_StatusBoxWholeImage);
    _whole = vimageLoad(img);
    img = vresourceGet(data, appname_StatusBoxPieceImage);
    _piece = vimageLoad(img);
    registerclass();
  }
  vexON_EXCEPTION {
#if vmemBALANCE
    statitemshutdown();
#endif
    vexPropagate(vexGetModuleStartupClass(), vexMESSAGE, 
		 "Missing required resources", vexERRNO, 0,
		 vexNULL);
  }
  vexEND_HANDLING;

#if vmemBALANCE
  vclientRegisterGlobalShutdown(statitemshutdown);
#endif

  _initialized = vTRUE;
  return;
}



static void
registerclass(void)
{
  register statusboxClass *clas;

  clas = vclassSpawn(vdialogGetDefaultItemClass(), sizeof(statusboxClass));
  vclassSetNameScribed(clas, vcharScribeLiteral("statusbox"));
  vclassSetObjectSize(clas, sizeof(statusbox));

  vclassSet(clas, vobjectINIT, init);
  vclassSet(clas, vobjectLOAD_INIT, load);
  vclassSet(clas, vobjectDESTROY, nuke);
  vclassSet(clas, vobjectCOPY, copy);
  vclassSet(clas, vobjectCOPY_INIT, copyinit);
  vclassSet(clas, vdialogDRAW_ITEM, draw);
  vclassSet(clas, vdialogGET_ITEM_MIN_SIZE, minsize);
  vclassSet(clas, vdialogGET_ITEM_NATURAL_SIZE, naturalsize);
  vclassSet(clas, vdialogSET_ITEM_RECT, setrect);
  vclassSet(clas, statusboxZERO, clear);
  vclassSet(clas, statusboxSET_NUMBER, setnumber);
  vclassSet(clas, statusboxSET_MESSAGE, setmessage);
  vclassSet(clas, statusboxFLASH_MESSAGE, flash);
  vclassSet(clas, statusboxSET_FLASH_DELAY, setdelay);
  vclassSet(clas, statusboxSET_IMAGE, setimage);

  _defaultClass = clas;
  return;
}



#if vmemBALANCE
static void
statitemshutdown(void)
{
  if (_ellipses) vstrDestroy(_ellipses);
  if (_whole) vimageDestroy(_whole);
  if (_piece) vimageDestroy(_piece);
  return;
}
#endif




static void
setdefaults(register statusbox *box)
{
  box->message    = NULL;
  box->image      = NULL;
  box->number     = 0;
  box->flashes    = 0;
  box->delay      = 5; /*seconds*/
  box->gmode      = vFALSE;
  return;
}




static void
init(statusbox *box)
{
  sendsuper(vobjectINIT,(box));
  setdefaults(box);
  box->wholeimage  = box->pieceimage = NULL;
  box->wholeshared = box->pieceshared = vFALSE;
  return;
}




static void
load(statusbox *box, vresource res)
{
  sendsuper(vobjectLOAD_INIT,(box,res));
  setdefaults(box);
  box->wholeimage  = box->pieceimage = NULL;
  box->wholeshared = box->pieceshared = vFALSE;
  return;
}




static void
clear(statusbox *box)
{
  if (box->image) vimageDestroy(box->image);
  if (box->message) vstrDestroy(box->message);
  setdefaults(box);
  return;
}




static void
nuke(statusbox *box)
{
  send(box, statusboxZERO, (box));
  if (box->wholeimage && !box->wholeshared) 
    vimageDestroy(box->wholeimage);
  if (box->pieceimage && !box->pieceshared) 
    vimageDestroy(box->pieceimage);
  sendsuper(vobjectDESTROY,(box));
  return;
}




static void
copy(statusbox *box, statusbox *dup)
{
  sendsuper(vobjectCOPY,(box,dup));
  send(box, statusboxZERO, (dup));

  if (box->message) 
    dup->message = vstrClone(box->message);

  dup->wholeshared = vFALSE;
  if (box->wholeimage)
    dup->wholeimage = vimageClone(box->wholeimage);
  else
    dup->wholeimage = NULL;

  dup->pieceshared = vFALSE;
  if (box->pieceimage)
    dup->pieceimage = vimageClone(box->pieceimage);
  else
    dup->pieceimage = NULL;

  if ((dup->number = box->number)) 
    makeimage(dup); /* after check images */

  dup->gmode   = box->gmode;
  dup->flashes = 0;
  dup->delay   = box->delay;

  return;
}




static void
copyinit(statusbox *box, statusbox *dup)
{
  init(dup);
  copy(box,dup);
  return;
}




static int
calcwidth(statusbox *box, int number)
{
  const vchar	*prompt;
  register int	 w, iw;
  vimage	*whole;

  w = 0;

  prompt = vdialogGetItemTitle(&box->item);
  if (prompt) {
    vfont *fn = vdialogDetermineItemFont(&box->item);
    w = vfontStringWidthX(fn, prompt);
    if (number)
      w += H_MARGIN;
  }

  whole = box->wholeimage ? box->wholeimage : _whole;
  
  if (number) {
    iw = vimageGetWidth(whole) + I_SPACING;
    w += (number-1)*iw + vimageGetWidth(whole);
  }

  return w;
}




static void
minsize(statusbox *box, int *w, int *h)
{	
  vfont *fn;
  register int d0,d1;
  vimage	*whole, *piece;

  whole = box->wholeimage ? box->wholeimage : _whole;
  piece = box->pieceimage ? box->pieceimage : _piece;

  fn = vdialogDetermineItemFont(&box->item);
  d0 = vimageGetWidth(whole);
  d1 = vimageGetWidth(piece);
  *w = vMAX(d0,d1);
  d0 = vfontStringWidthX(fn, _ellipses);
  *w = vMAX(*w, d0);
  *w += 2*H_MARGIN;

  d0 = vimageGetHeight(whole);
  d1 = vimageGetHeight(piece);
  *h = vMAX(d0,d1);
  d0 = vfontHeight(fn);
  *h = vMAX(*h, d0);
  *h += 2*V_MARGIN;

  return;
}




static void
naturalsize(statusbox *box, register int *w, register int *h)
{
  int minw,minh;

  vdialogGetItemMinSize(&box->item, &minw, &minh);
  if (box->message) {
    vfont *fn = vdialogDetermineItemFont(&box->item);
    *w = 2*H_MARGIN + vfontStringWidthX(fn, box->message);
    *h = 2*V_MARGIN + vfontHeight(fn);
    if (*w<minw) *w = minw;
    if (*h<minh) *h = minh;
  }
  else 
  if (box->gmode)   {
    *w = 2*H_MARGIN + calcwidth(box, box->number);
    *h = minh;
    if (*w<minw) *w = minw;
  }
  else {
    *w = minw;
    *h = minh;
  }
  return;
}




static void
setrect(statusbox *box, const vrect *r)
{
  sendsuper(vdialogSET_ITEM_RECT, (box,r));
  if (box->image) {
    vimageDestroy(box->image);
    box->image = NULL;
    makeimage(box);
  }
  return;
}




static void
eraseimage(register statusbox *box)
{
  vcolor *color;
  vdrawGSave();
  vdrawImageDevice(box->image);
  color = vdrawGetColor();
  vdrawSetColor(vdialogDetermineItemBackground(&box->item));
  vdrawRectFill(0,0,vimageGetWidth(box->image), vimageGetHeight(box->image));
  vdrawSetColor(color);
  vdrawGRestore();
  return;
}




static void
formimage(statusbox *box)
{
  register int	x,iw,i,n;
  int		y, sw;
  int		pw;
  const vchar	*prompt;
  vfont		*fn = NULL;
  vbool		drawpiece;
  vimage	*whole, *piece;

  vdebugIF((!box || !box->image), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "form image: NULL box ref!", vexERRNO, 0, vexNULL));

  sw = vdialogGetItemW(&box->item) - 2*H_MARGIN;
  pw = 0;

  prompt = vdialogGetItemTitle(&box->item);
  if (prompt) {
    fn = vdialogDetermineItemFont(&box->item);
    pw = vfontStringWidthX(fn, prompt);
    sw -= pw + H_MARGIN;
  }

  whole = box->wholeimage ? box->wholeimage : _whole;
  piece = box->pieceimage ? box->pieceimage : _piece;

  drawpiece = vFALSE;
  iw = vimageGetWidth(whole) + I_SPACING;
  n  = sw/iw;
  if (box->number<n) n= box->number;
  else if (box->number>n) {
    /* make sure we have room for piece */
    if ((sw%iw)<vimageGetWidth(piece)) n--;
    drawpiece = vTRUE;
  }

  vdrawGSave();
  vdrawImageDevice(box->image);

  x = 0;
  y = 0;

  if (prompt) {
    vdrawSetFont(vdialogDetermineItemFont(&box->item));
    vdrawMoveTo(0,vfontDescent(fn));
    vdrawShow(prompt);
    x = pw + H_MARGIN;
  }

  for (i=0; i<n; i++,x+=iw) {
    vdrawMoveTo(x,y);
    vdrawImageCompositeIdent(whole);
  }
  if (drawpiece) {
    vdrawMoveTo(x,y);
    vdrawImageCompositeIdent(piece);
  }

  vdrawGRestore();
  return;
}




static void
makeimage(statusbox *box)
{
  int sw,sh;

  sw = vdialogGetItemW(&box->item) - 2*H_MARGIN;
  sh = vdialogGetItemH(&box->item) - 2*V_MARGIN;

  box->image = vwindowCreateBufferImage(sw,sh);

  eraseimage(box), formimage(box);

  return;
}




static void
draw(register statusbox *box)
{
  vfont	*fn;
  register const vrect *r;

  fn = vdialogDetermineItemFont(&box->item);
  r  = vdialogGetItemRect(&box->item);

  if (box->message)  {
    vdrawMoveTo(r->x + H_MARGIN, r->y + V_MARGIN + vfontDescent(fn));
    vdrawShow(box->message);
  }
  else 
  if (box->image) {
    vdrawMoveTo(r->x + H_MARGIN, r->y + V_MARGIN);
    vdrawImageIdent(box->image);
  }
  else {
    vdrawMoveTo(r->x + H_MARGIN, r->y + V_MARGIN + vfontDescent(fn));
    vdrawShow(_ellipses);
  }
  return;
}




static void
setnumber(register statusbox *box, int number)
{
  if (!box->image) {
    box->number = number;
    makeimage(box);
  }
  else
  if (number!=box->number) {
    box->number = number;
    eraseimage(box), formimage(box);
  }
  vdialogInvalItem(&box->item, vwindowINVAL_OPAQUE);
  return;
}




static void
setmessage(register statusbox *box, vstr *message)
{
  if (box->message)
    vstrDestroy(box->message);
  box->message = message;
  vdialogInvalItem(&box->item, 0);
  return;
}




static int
handleflash(vevent *event)
{
  statusbox *box;
  box = (statusbox*)veventGetClientData(event);
  vdebugIF((!box->flashes), vexGenerate(vexGetValueNullClass(), vexMESSAGE,
	   "handling flash with 0 flashes pending?!", vexNULL));
  box->flashes--;
  if (!box->gmode && !box->flashes)
    send(box, statusboxSET_MESSAGE,(box,NULL));
  return vTRUE;
}




static void
flash(register statusbox *box, vstr *message)
{
  register vevent *event;
  event = veventCreateClient();
  veventSetPriority(event, veventPRIORITY_MIN);
  veventSetTarget(event, handleflash);
  veventSetClientData(event, box);
  send(box, statusboxSET_MESSAGE, (box,message));
  veventPostFuture(event, (unsigned long)box->delay, 0);
  return;
}




static void
setdelay(register statusbox *box, unsigned short delay)
{
  box->delay = delay;
  return;
}




static void
setimage(register statusbox *box, int which, vimage *image, int shared)
{
  vdebugIF((which<0||which>2), vexGenerate(vexGetArgRangeClass(),
           vexMESSAGE, "which selector is invalid (1 or 2)", vexERRNO, 0,
           vexNULL));

  if (image && which==statusboxBOTH_IMAGES)
    shared = vTRUE; /* otherwise it's barfola */

  if (which==statusboxBOTH_IMAGES || which==statusboxWHOLE_IMAGE) {
    if (box->wholeimage && !box->wholeshared)
      vimageDestroy(box->wholeimage);
    if (image) {
      box->wholeimage  = image;
      box->wholeshared = shared;
    }
    else {
      box->wholeimage  = NULL;
      box->wholeshared = vFALSE;
    }
  }

  if (which==statusboxBOTH_IMAGES || which==statusboxPIECE_IMAGE) {
    if (box->pieceimage && !box->pieceshared)
      vimageDestroy(box->pieceimage);
    if (image) {
      box->pieceimage  = image;
      box->pieceshared = shared;
    }
    else {
      box->pieceimage  = NULL;
      box->pieceshared = vFALSE;
    }
  }

  return;
}

/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */
