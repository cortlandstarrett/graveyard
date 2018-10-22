/* $Id: statwin.c,v 1.1 1994/08/19 00:08:33 simone Exp $ */
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
 * Three objects make up a "graphic set:" the label, the searching status   *
 * box, and the found items status box. the three objects are laid out      *
 * wrt to each other as follows:                                            *
 *                                                                          *
 *           + dialog top border ...==============================+         *
 *           |                                                    |         *
 *           |                             *                      |         *
 *           |                             * (other sets)         |         *
 *           |                             *                      |         *
 *           |    +-------+     +----------------------------+    |         *
 *           |    | label | ... |  searching status graphic  |    |         *
 *           |    +-------+     +----------------------------+    |         *
 *           |                  +----------------------------+    |         *
 *           |                  | found items status graphic |    |         *
 *           |                  +----------------------------+    |         *
 *           |                             *                      |         *
 *           |                             * (other sets)         |         *
 *           |                             *                      |         *
 *           |                                                    |         *
 *           + dialog bottom border ...===========================+         *
 *                                                                          *
 * the layout constants (H_SPACE, V_SPACE, etc.) describe the misc.         *
 * fixed (strut) distances between the three objects. for objects sides     *
 * connected to dialog borders there is a "buffer" margin st we have        *
 * space between the border and the item when the dialog is at it's min     *
 * height or width.                                                         *
 *                                                                          *
 * since we dynamically create this graphic sets we have to do the          *
 * laborious task of creating, updating, and destroying the status          *
 * dialog's spring solution at runtime. (at this time we should all take    *
 * time and thank our lucky stars that the galaxy resource builder          *
 * eliminates the need for this type of manipulation for most application   *
 * dialogs!)                                                                *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vfsHEADER
#include veventHEADER
#include vspringHEADER
#include vdialogHEADER
#include vdomainHEADER
#include vspringdomHEADER
#include vstdHEADER

/* Our headers */
#include "tarray.h"
#include "names.h"
#include "statitem.h"
#include "isnf.h"
#include "utils.h"
#include "statwin.h"


/* Define our debug tag for the vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "status-window";
#define vdebugTAG _moduleTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

/* because i hate typing */
#define EX_LFT		vspringdomLEFT_OUTSIDE
#define EX_TOP		vspringdomTOP_OUTSIDE
#define EX_RGT		vspringdomRIGHT_OUTSIDE
#define EX_BOT		vspringdomBOTTOM_OUTSIDE
#define IN_LFT		vspringdomLEFT_INSIDE
#define IN_TOP		vspringdomTOP_INSIDE
#define IN_RGT		vspringdomRIGHT_INSIDE
#define IN_BOT		vspringdomBOTTOM_INSIDE
#define LFT		vspringdomLEFT
#define RGT		vspringdomRIGHT
#define TOP		vspringdomTOP
#define BOT		vspringdomBOTTOM

/* our layout spacing and dimensions */
#define H_MARGIN	10
#define V_MARGIN	10
#define V_SPACE		5
#define H_SPACE		5
#define T_WIDTH		70

/* our ordering (layering) of the elements in a "status set" */
enum {
  INDEX_TEXT,	/* well a label really */
  INDEX_LOOK,	/* look status box */
  INDEX_FIND,	/* find status box */
  SETSIZE
};

/* used when disconnecting a graphic from dialog */
typedef struct setlocation {
  int			i;	  /* text item index in dialog's itemlist */
  vdomainObject		*obj;	  /* text object match in spring domain */
  int			iprev;	  /* text item index preceding in itemlist */
  vdomainObject		*objprev; /* text object PRECEDING in spring domain */
  vspringdomObjectSet	*set;	  /* convenience for removal */
}setlocation;


static int	closeIfNoProcessing(vdialog*,vevent*);
static void	connectInternals(vspringdom*,vspringdomObject*, 
				 vspringdomObject*, vspringdomObject*);
static void	connectAs1st(vspringdom*,vspringdomObject*, 
			     vspringdomObject*, vspringdomObject*);
static void	connectAsNth(vspringdom*,vspringdomObject*, vspringdomObject*,
			     vspringdomObject*, vspringdomObject*);
static void	connectBottom(vspringdom*, vspringdomObject*);
static void	disconnectNth(vspringdom*, vdialog*, setlocation*);
static tarray  *getBottom(vspringdom*);
static void	newObjects(vspringdom*, vspringdomObject**, vspringdomObject**,
			   vspringdomObject**);
static void	locate(vspringdom*, statusgraphic*, setlocation*);
static void	attach(statusgraphic*);
static void	detach(statusgraphic*);


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

/********
 * isnfNewStatusDialogGraphic
 *
 * -> 
 * <- graphic, newly created graphic (append to end)
 ********/
statusgraphic *
isnfNewStatusDialogGraphic(const vchar *filepath, vdialog *behind)
{
  isnifferApp	*app;
  vbool		 open, isNew;
  statusgraphic	*graphic;

  vdebugIF((!filepath), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "new status graphic: NULL file path!", vexERRNO, 0, vexNULL));

  app  = isnfGet();
  open = vFALSE;

  /* if 1st time, load and setup the global status dialog */
  if (!app->status) {
    vresource res, ires;
    register vdialog *dialog;

    res = vresourceGet(app->resources, appname_StatusDialog);
    app->status = dialog = vdialogLoad(res);
    vdebugIF(vdialogGetItemCount(dialog), vexGenerate(vexGetValueClass(),
             vexMESSAGE, "new status graphic: dialog contains items!",
             vexERRNO, 0, vexNULL));

    vdialogPlace(dialog, behind ? behind : app->requestor, 
		 vrectPLACE_CENTER, vrectPLACE_BOTTOM);
    vwindowSetLeader(vdialogGetWindow(dialog), vdialogGetWindow(app->requestor));
    vdialogSetCloseHook(dialog, closeIfNoProcessing);

    ires = vresourceGet(app->resources, appname_StatusFindImages);
    res  = vresourceGet(ires, appname_StatusBoxWholeImage);
    app->wholeimage = vimageLoad(res);
    res  = vresourceGet(ires, appname_StatusBoxPieceImage);
    app->pieceimage = vimageLoad(res);

    open  = vTRUE;
    isNew = vTRUE;
  }
  else {
    open  = !vdialogIsOpen(app->status);
    isNew = vFALSE;
  }

  graphic = (statusgraphic*)vmemAlloc(sizeof(statusgraphic));
  graphic->path   = vfsPathFromStr(filepath);
  graphic->label  = NULL;
  graphic->search = NULL;
  graphic->find   = NULL;
  attach(graphic);


  /* make sure the dialog is open */
  if (open) 
    vdialogOpen(app->status);
  if (!isNew && !vwindowIsVisible(vdialogGetWindow(app->status)))
    vwindowRaise(vdialogGetWindow(app->status));


  /* done */
  return graphic;
}


/********
 * isnfDeleteStatusDialogGraphic
 *
 * -> graphic, the graphic to nuke
 * <- void
 ********/
void
isnfDeleteStatusDialogGraphic(statusgraphic *graphic)
{
  vdebugIF((!graphic), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "delete status graphic: NULL argument!", vexERRNO, 0, vexNULL));

  detach(graphic);
  vfsDestroyPath(graphic->path);
  vmemFree(graphic);

  return;
}


/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

/* Find the (visually) bottommost graphic set in the status dialog. 
    if things have been setup correctly the bottommost objects
    are layered last in the spring domain. */

static tarray* 
getBottom(vspringdom *sprdom)
{
  vdomain			*dom;
  tarray			*a;
  register vdomainObject	*firstOf3;
  vdomainObject			*thirdOf3, *textobj, *lookobj, *findobj;

  dom = vspringdomGetDomain(sprdom);

  textobj = lookobj = findobj = NULL;
  for (firstOf3= vdomainTopObject(dom);
       firstOf3;
       firstOf3= vdomainNextObjectBehind(thirdOf3)) {
    textobj = firstOf3;
    lookobj = vdomainNextObjectBehind(textobj);
    vdebugIF((!lookobj), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "getBotton: ack, items not in 3's!", vexERRNO, 0, vexNULL));
    findobj = thirdOf3 = vdomainNextObjectBehind(lookobj);
    vdebugIF((!findobj), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "getBotton: ack, items not in 3's!", vexERRNO, 0, vexNULL));
  }

  a = tarrayCreateSized(sizeof(vspringdomObject*), 3);
  tarrayAppendItem(a, &textobj);
  tarrayAppendItem(a, &lookobj);
  tarrayAppendItem(a, &findobj);

  return a;
}



/* Add the three new graphic objects to the spring domain AND layer
    them correctly st they match the ordering of the dialog's itemlist after 
    three new dialog items have been appended */

static void
newObjects(vspringdom *sprdom, vspringdomObject **lookobj, 
	   vspringdomObject **findobj, vspringdomObject **textobj)
{
  vdomainObjectSet *set;

  /* when items are added to a domain they are placed in the 0th layer.
   * this isn't correct for our purposes, since their matching dialog items
   * are appended to the END of the dialog item list. we want the domain's
   * object layering synchronized with the dialog's itemlist. We use 
   * brute force and explicitly put the objects where we want them. NOTE:
   * this knowledge is deemed from observation -- we have no guarantee that 
   * this default layering won't change in the future. bummer. */
  *findobj = vspringdomAddObject(sprdom);
  *lookobj = vspringdomAddObject(sprdom);
  *textobj = vspringdomAddObject(sprdom);

  /* now force the set to the back of ALL other objects */
  set = vdomainCreateObjectSet(vspringdomGetDomainObject(sprdom, *textobj));
  vdomainAddToObjectSet(&set, vspringdomGetDomainObject(sprdom, *lookobj));
  vdomainAddToObjectSet(&set, vspringdomGetDomainObject(sprdom, *findobj));
  vdomainLayerObjects(vspringdomGetDomain(sprdom), set, vdomainLAYER_TOBACK);
  vdomainDestroyObjectSet(set);

  return;
}




/* Setup all the internal connections for the three graphic objects.
    All the objects have natural heights. the text label is restricted
    to a fixed struct width (no spring), the statusbox items stretch
    horizontally (0 strut length). */

static void
connectInternals(register vspringdom *sprdom, vspringdomObject *lookobj, 
		 vspringdomObject *findobj, vspringdomObject *textobj)
{
  register vspringdomConnection *con;

  /* 0- natural sized vertical dimensions */
  con = vspringdomGetObjectConnection(sprdom, lookobj, IN_TOP);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);
  con = vspringdomGetObjectConnection(sprdom, lookobj, IN_BOT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);

  con = vspringdomGetObjectConnection(sprdom, findobj, IN_TOP);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);
  con = vspringdomGetObjectConnection(sprdom, findobj, IN_BOT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);

  con = vspringdomGetObjectConnection(sprdom, textobj, IN_TOP);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);
  con = vspringdomGetObjectConnection(sprdom, textobj, IN_BOT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vTRUE);

  /* 1- pure spring horizontal dimensions for look + find */
  con = vspringdomGetObjectConnection(sprdom, lookobj, IN_RGT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vTRUE);
  con = vspringdomGetObjectConnection(sprdom, lookobj, IN_LFT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vTRUE);

  con = vspringdomGetObjectConnection(sprdom, findobj, IN_RGT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vTRUE);
  con = vspringdomGetObjectConnection(sprdom, findobj, IN_LFT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vTRUE);

  /* 2- fixed horizontal dimensions for text */
  con = vspringdomGetObjectConnection(sprdom, textobj, IN_RGT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vFALSE);
  vspringdomSetConnectionFixedBase(sprdom, con, T_WIDTH);
  con = vspringdomGetObjectConnection(sprdom, textobj, IN_LFT);
  vspringdomUseConnectionNaturalBase(sprdom, con, vFALSE);
  vspringdomSetConnectionStretches(sprdom, con, vFALSE);
  vspringdomSetConnectionFixedBase(sprdom, con, T_WIDTH);

  return;
}



/* Connect a graphic set as though it's the only set in the dialog.*/

static void
connectAs1st(register vspringdom *sprdom, vspringdomObject *lookobj, 
	     vspringdomObject *findobj, vspringdomObject *textobj)
{
  register vspringdomConnection *con;

  /* ALL */
  /* 0- internals */
  connectInternals(sprdom, lookobj, findobj, textobj);


  /* TEXT-LABEL */
  /* 1- set left H_MARGIN fixed/locked and connect to left border */
  con = vspringdomGetObjectConnection(sprdom, textobj, EX_LFT);
  vspringdomSetConnectionFixedBase(sprdom, con, H_MARGIN);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);

  /* 1- set top all spring and connect to top of lookobj */
  con = vspringdomGetObjectConnection(sprdom, textobj, EX_TOP);
  vspringdomSetConnectionFixedBase(sprdom, con, 0);
  vspringdomSetConnectionStretches(sprdom, con, vTRUE);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, TOP);

  /* 1- set bot 0 fixed/locked and connect to bot of lookobj */
  con = vspringdomGetObjectConnection(sprdom, textobj, EX_BOT);
  vspringdomSetConnectionFixedBase(sprdom, con, 0);
  vspringdomSetConnectionStretches(sprdom, con, vFALSE);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, BOT);

  /* 1- connect rgt to left of lookobj -- we want this to get the 
   * attributes of the lookobj's left connection when it's connected 
   * later! */
  con = vspringdomGetObjectConnection(sprdom, textobj, EX_RGT);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, LFT);  


  /* LOOK-COUNTER */
  /* 2- set lft H_SPACE fixed/locked and connect to rgt of text */
  con = vspringdomGetObjectConnection(sprdom, lookobj, EX_LFT);
  vspringdomSetConnectionFixedBase(sprdom, con, H_SPACE);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);
  vspringdomConnectToObjectEdge(sprdom, con, textobj, RGT);

  /* 2- set top V_MARGIN fixed/lock and connect to top border */
  con = vspringdomGetObjectConnection(sprdom, lookobj, EX_TOP);
  vspringdomSetConnectionFixedBase(sprdom, con, V_MARGIN);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);

  /* 2- set rgt H_MARGIN fixed/lock and connect to rgt border */
  con = vspringdomGetObjectConnection(sprdom, lookobj, EX_RGT);
  vspringdomSetConnectionStretches(sprdom, con, vFALSE);
  vspringdomSetConnectionFixedBase(sprdom, con, H_MARGIN);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);

  /* 2- connect bot border to findobj's top -- we want this
   * to get the attributes of the findobj's top connection
   * when it's connected to us! */
  con = vspringdomGetObjectConnection(sprdom, lookobj, EX_BOT);
  vspringdomConnectToObjectEdge(sprdom, con, findobj, TOP);


  /* FIND-COUNTER */
  /* 3- connect left to left of lookobj, 0 length  */
  con = vspringdomGetObjectConnection(sprdom, findobj, EX_LFT);
  vspringdomSetConnectionFixedBase(sprdom, con, 0);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, LFT);

  /* 3- connect right to right of lookobj, 0 length  */
  con = vspringdomGetObjectConnection(sprdom, findobj, EX_RGT);
  vspringdomSetConnectionFixedBase(sprdom, con, 0);
  vspringdomSetConnectionStretches(sprdom, con, vFALSE);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, RGT);

  /* 3- make top V_SPACE in length and locked, and connect to
   * bottom of lookobj. lookobj's bot is already connected by
   * findobj's top so it'll automatically be updated with our
   * attributes */
  con = vspringdomGetObjectConnection(sprdom, findobj, EX_TOP);
  vspringdomSetConnectionFixedBase(sprdom, con, V_SPACE);
  vspringdomSetConnectionLocked(sprdom, con, vTRUE);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, BOT);

  /* whew! */
  connectBottom(sprdom,findobj);
  return;
}



/* Connect a graphic set as the nth (or bottommost) set in the dialog.
    We pass in the domain object for the current bottommost found-item's
    object. this object's bottom is connected to the top of the new
    graphic set */

static void
connectAsNth(register vspringdom *sprdom, vspringdomObject *lookobj, 
	     vspringdomObject *findobj, vspringdomObject *textobj,
	     vspringdomObject *botfindobj)
{
  register vspringdomConnection *con;

  /* 0- first connect the objects as though they were the only
   * items in the domain. this gets all the relative connections
   * between the items initialized */
  connectAs1st(sprdom, lookobj, findobj, textobj);

  /* 1- adjust the bottom of the current bottom findobj to connect
   * to the top of our lookobj -- we want this to get the attributes
   * of the lookobj's top connection when it's connected later! */
  con = vspringdomGetObjectConnection(sprdom, botfindobj, EX_BOT);
  vspringdomSetConnectionFixedBase(sprdom, con, 0);
  vspringdomConnectToObjectEdge(sprdom, con, lookobj, TOP);

  /* 2- adjust the top of the new lookobj to connect to the bottom
   * of the current bottom findobj. this will automatically update 
   * the bottom findobj's bottom connection */
  con = vspringdomGetObjectConnection(sprdom, lookobj, EX_TOP);
  vspringdomSetConnectionFixedBase(sprdom, con, V_SPACE);
  vspringdomConnectToObjectEdge(sprdom, con, botfindobj, BOT);

  /* whew! */
  return;
}



/* Setup the connection between the bottommost found-item object and the
    the dialog's bottom border. we leave a "buffer" space st if the dialog
    is forced to its min height its border won't jam against the bottom 
    border of the dialog item */

static void
connectBottom(register vspringdom *sprdom, register vspringdomObject *findobj) 
{
  vspringdomConnection *con;

  /* 0- leave a little space between lower object and the border. 
   * just looks better if dialog forced to its min height 
   */
  con = vspringdomGetObjectConnection(sprdom, findobj, EX_BOT);
  vspringdomSetConnectionFixedBase(sprdom, con, V_MARGIN);
  vspringdomConnectToObjectEdge(sprdom, con, vspringdomGetBorder(sprdom), BOT);
  return;
}



/* Disconnect a graphic set from the dialog. A description of the set's
    location is found in the setlocation structure. This routine shouldn't
    be used if there is only one set int the status dialog (just nuke the
    spring solution). */

static void
disconnectNth(vspringdom *sprdom, vdialog *dialog, setlocation *loc)
{
  register vdomainObject	*obj;
  vspringdomObject		*prev, *next;
  int				max;
  vspringdomConnection		*con;

  /* 
   * WARNING: we want to adjust all connections BEFORE we
   * nuke the objects from the domain. this way we don't get
   * any unwanted "side-effect" reconnections for objects
   * still connected to the removed items
   */

  /* if none after set, adjust prev to anchor to bottom. note there
   * must be a previous set since this routine isn't called if only
   * one set in dialogue! */
  max = vdialogGetItemCount(dialog);
  if (loc->i==(max-3)) {
    obj = vdomainNextObjectBehind(loc->objprev);/* prev-lookobj */
    obj = vdomainNextObjectBehind(obj);		/* prev-findobj */
    connectBottom(sprdom, vspringdomGetFromDomainObject(sprdom,obj));
  }

  /* else if prev above, adjust it to attach to the next set
   * below. we know there's something below our set */
  else if (loc->objprev) {
    /* find findobj of prev */
    obj = vdomainNextObjectBehind(loc->objprev);/* prev-lookobj */
    prev = vspringdomGetFromDomainObject(sprdom, vdomainNextObjectBehind(obj));
    /* find lookobj of next */
    obj = vdomainNextObjectBehind(loc->obj);	/* this-lookobj */
    obj = vdomainNextObjectBehind(obj);		/* this-findobj */
    obj = vdomainNextObjectBehind(obj);		/* next-textobj */
    next = vspringdomGetFromDomainObject(sprdom, vdomainNextObjectBehind(obj));
    /* connect the prev to the next */
    con = vspringdomGetObjectConnection(sprdom, prev, EX_BOT);
    vspringdomConnectToObjectEdge(sprdom, con, next, TOP);
    con = vspringdomGetObjectConnection(sprdom, next, EX_TOP);
    vspringdomConnectToObjectEdge(sprdom, con, prev, BOT);
  }

  /* else adjust set below me to anchor to the top. we know there's
   * something below me. */
  else {
    obj = vdomainNextObjectBehind(loc->obj);	/* this-lookobj */
    obj = vdomainNextObjectBehind(obj);		/* this-findobj */
    obj = vdomainNextObjectBehind(obj);		/* next-textobj */
    next = vspringdomGetFromDomainObject(sprdom, vdomainNextObjectBehind(obj));
    con = vspringdomGetObjectConnection(sprdom, next, EX_TOP);
    vspringdomConnectToObjectEdge(sprdom, con, vspringdomGetBorder(sprdom), TOP);
    vspringdomSetConnectionFixedBase(sprdom, con, V_MARGIN);
  }

  /* grunt */
  return;
}




/* Locate a graphic set within the status dialog. Note the "locating" is
    wrt to the dialog's spring solution's domain not the dialog item 
    list. */

static void
locate(vspringdom *sprdom, statusgraphic *graphic, setlocation *loc)
{
  isnifferApp			*app = isnfGet();
  vdomain			*dom;
  register vdomainObject	*obj;
  register int			i,max;
  vdomainObjectSet		*set;

  loc->iprev   = -1;
  loc->objprev = NULL;
  loc->i = vdialogGetItemIndex(app->status, graphic->label);

  /* jump by 3s to find match in domain */
  dom = vspringdomGetDomain(sprdom);
  for (i=0, max=loc->i, obj=vdomainTopObject(dom); i<max;) {
    vdebugIF((!obj), vexGenerateReturnNull());
    loc->iprev = i;
    i += 3;
    loc->objprev = obj;
    obj = vdomainNextObjectBehind(obj); /*look*/
    vdebugIF((!obj), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "locate: ack, items not in 3's!", vexERRNO, 0, vexNULL));
    obj = vdomainNextObjectBehind(obj); /*find*/
    vdebugIF((!obj), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "locate: ack, items not in 3's!", vexERRNO, 0, vexNULL));
    obj = vdomainNextObjectBehind(obj); /*next-text*/
  }

  loc->obj = obj;
  set = vdomainCreateObjectSet(obj);
  obj = vdomainNextObjectBehind(obj);
  vdomainAddToObjectSet(&set, obj);
  obj = vdomainNextObjectBehind(obj);
  vdomainAddToObjectSet(&set, obj);
  loc->set = (vspringdomObjectSet*)set; /* !!eek!! */

  return;
}




/* Attach a graphic set to the status dialog. graphic sets are always
    appended to the dialog (ie. are attached to the bottommost set
    in the dialog). we make two assumptions when attaching/detaching graphic
    sets: a. the dialog's itemlist ordering must match it's solution
    domain's layering; in other words the 0th item in the dialog item
    list is in the 0th layer in the spring domain. b. when items are
    added to a spring domain, they are placed in the topmost (0th)
    layer. Note the status dialog is automatically resized st the new
    set is visible. */

static void
attach(statusgraphic *graphic)
{
  isnifferApp		*app = isnfGet();
  vdialog		*dialog = app->status;
  vspringdom		*sprdom;
  const vdialogItemClass *boxclass;
  vchar			*leafname;
  vdialogItem		*textitem, *lookitem, *finditem;
  vspringdomObject	*textobj, *lookobj, *findobj, *botfindobj;
  int			empty;
  vstr			*str;
  vspringSolution	*solution;
  tarray		*a;


  /* snarf stuff before we mangle the dialog's itemlist.
   * additions shouldn't nuke the spring solution but better
   * safe than sorry. Warning: the dialog may not have a
   * solution if it doesn't have any items! 
   */
  solution = vdialogGetSolution(dialog);
  if (solution) sprdom = vspringdomDecompile(solution);
  else  sprdom = vspringdomCreate();


  /* find out if only one set in dialog -- optimized for this
   * case. NOTE: the border is not part of the domain! 
   */
  empty = vdomainObjectCount(vspringdomGetDomain(sprdom))==0;


  /* create 3 new dialog item thingies: one label, two status boxes.
   * Remember to set the boxes' titles st. the graphics include a
   * descriptive label.
   */
  textitem = vdialogCreateLabelItem();
  leafname = vfsGetPathElementAt(graphic->path, 
		 vfsGetPathElementCount(graphic->path)-1);
  vdialogSetItemTitle(textitem, leafname);
  vdialogAppendItem(dialog, textitem);
  vdialogSetItemData(textitem, graphic);

  boxclass = statusboxGetDefaultClass();
  lookitem = vdialogCreateItemOfClass(boxclass);
  str = isnfStrFrom(strTitleLookStatusItem);
  vdialogSetItemTitle(lookitem, str);
  vstrDestroy(str);
  vdialogAppendItem(dialog, lookitem);
  vdialogSetItemData(lookitem, graphic);

  finditem = vdialogCreateItemOfClass(boxclass);
  str = isnfStrFrom(strTitleFindStatusItem);
  vdialogSetItemTitle(finditem, str);
  vstrDestroy(str);
  vdialogAppendItem(dialog, finditem);
  vdialogSetItemData(finditem, graphic);
  statusboxSetGraphicImages(finditem, app->wholeimage, app->pieceimage);


  /* if this is the only status set in the dialog, stuff is pretty
   * straight forward once we add the objects. otherwise we gotta find 
   * the current bottom-most item in the dialog and append the new set
   * to it. newObjects() takes care to correctly layer the objects
   * to match the dialog's itemlist.
   */
  if (!empty) {
    a = getBottom(sprdom);
    botfindobj = *(tarrayAtAs(a,INDEX_FIND,vspringdomObject**));
    tarrayDestroy(a);
  }
  else
    botfindobj = NULL;

  newObjects(sprdom, &lookobj, &findobj, &textobj);

  if (empty)
    connectAs1st(sprdom, lookobj, findobj, textobj);
  else
    connectAsNth(sprdom, lookobj, findobj, textobj, botfindobj);

  solution = vspringdomCompile(sprdom);
  vdialogSetSolution(dialog, solution);
  vspringdomDestroy(sprdom);

  /* remember new items for managment and later removal */
  graphic->label  = textitem;
  graphic->search = lookitem;
  graphic->find   = finditem;

  return;
}




/* Remove a graphic set from the status dialog. If this is the only set
    in the dialog, the dialog's spring solution is set to NULL. Note the
    dialog is NOT resized after the items have been removed. */

static void
detach(statusgraphic *graphic)
{
  vdialog		*dialog = (isnfGet())->status;
  vspringdom		*sprdom;
  int			single;
  setlocation		loc;
  vdialogItem		*item;
  vspringSolution 	*solution;


  /* can't remove somthing if empty */
  vdebugIF(!vdialogGetSolution(dialog), vexGenerate(vexGetValueNullClass(),
           vexMESSAGE, "detach: dialog has no solution!", vexERRNO, 0, 
           vexNULL));


  /* snarf stuff before we mangle the dialog's itemlist.
   * as of version 1.2x, deletions from an itemlist definitly nukes
   * any associated spring solution. this may change in future
   * versions, but for now we grab it. Note: the border is NOT part
   * of the domain's object set!
   */
  sprdom = vspringdomDecompile(vdialogGetSolution(dialog));
  single = vdomainObjectCount(vspringdomGetDomain(sprdom))<=3; 


  /* locate the set within the dialog's itemlist and the domain
   * layers -- these should match! 
   */
  locate(sprdom, graphic, &loc);


  /* disconnect the objects within the domain before removing 'em
   * from the domain! 
   */
  if (!single)
    disconnectNth(sprdom, dialog, &loc);


  /* remove items from domain and from dialog. Note we remove stuff
   * from the dialog in reverse order st. the ordering within the
   * itemlist is preserved while we delete 
   */
  if (!single) vspringdomRemoveObjects(sprdom, loc.set);
  vdomainDestroyObjectSet((vdomainObjectSet*)loc.set); /* !!eek!! */
  item = vdialogGetItemAt(dialog, loc.i+2);
  vdialogDeleteItem(dialog, item);
  vdialogDestroyItem(item);
  item = vdialogGetItemAt(dialog, loc.i+1);
  vdialogDeleteItem(dialog, item);
  vdialogDestroyItem(item);
  item = vdialogGetItemAt(dialog, loc.i);
  vdialogDeleteItem(dialog, item);
  vdialogDestroyItem(item);

  /* reset dialog's solution */
  if (single) solution = NULL;
  else solution = vspringdomCompile(sprdom);
  vdialogSetSolution(dialog, solution);
  vspringdomDestroy(sprdom);

  return;
}



/* The user has tried to close the status dialog via the window manager.
    We'll allow them to close the window iff there are no current sets
    in the dialog => nothing is being processed. Ideally there should
    be a vwindow or vdialog  call to remove the close capability from 
    the window manager adornments but...*/

static int
closeIfNoProcessing(vdialog *dialog, vevent *event)
{
  /* allow to close if nothing processing */
  return (vdialogGetItemCount(dialog)==0) ? vFALSE : vTRUE; 
}


/*
  +-------------------------------------------------------------------------+
   formatting information for emacs in c-mode
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

