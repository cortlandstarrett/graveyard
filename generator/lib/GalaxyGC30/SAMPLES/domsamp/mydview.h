/* $Id: mydview.h,v 1.8 1996/06/28 19:26:55 gregt Exp $ */
/* mydview
 *
 * my domainview subclass
 */

#ifndef mydviewINCLUDED
#define mydviewINCLUDED 1

#include <vport.h>
#include vdomainviewHEADER

typedef struct myDomainView		myDomainView;
typedef struct myDomainViewClass	myDomainViewClass;

myDomainViewClass *myDomainViewGetDefaultClass(
    void
    );

myDomainViewClass *myDomainViewGetClass(
    myDomainView	*domainview
    );

myDomainView *myDomainViewClone(
    myDomainView    	*domainview
    );

void myDomainViewDestroy(
    myDomainView	*domainview
    );

vdomainview *myDomainViewGetView(
    myDomainView	*domainview
    );

vdomain *myDomainViewGetDomain(
    myDomainView	*domainview
    );

vdialogItem *myDomainViewGetItem(
    myDomainView	*domainview
    );

void myDomainViewRecalcBars(
    myDomainView	*domainview
    );

vbool myDomainViewHasSmartScrollbars(
    myDomainView	*domainview
    );

void myDomainViewSetSmartScrollbars(
    myDomainView	*domainview,
    vbool		hasSmart
    );

vbool myDomainViewIsShowingGridVertices(
    myDomainView	*domainview
    );

void myDomainViewShowGridVertices(
    myDomainView	*domainview,
    vbool		showGrid
    );

vbool myDomainViewIsLong(
    myDomainView	*domainview
    );

void myDomainViewSetLong(
    myDomainView	*domainview,
    vbool		isLong
    );

vcolor *myDomainViewGetSelColor(
    myDomainView	*domainview
    );

void myDomainViewSetSelColor(
    myDomainView	*domainview,
    vcolor		*selColor
    );

vbool myDomainViewHasDragOnUnselectables(
    myDomainView	*domainview
    );

void myDomainViewSetDragOnUnselectables(
    myDomainView	*domainview,
    vbool		hasDrag
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum {
  _myDomainViewSMART_SCROLLBARS		= 0x0001,
  _myDomainViewSHOW_GRID		= 0x0002,
  _myDomainViewDRAG_UNSELECTABLES	= 0x0004
};

struct myDomainView {
  vdomainview	dview;
  unsigned int	flags;
  vcolor	*selColor;
  vbyte		trackMode;
};

#define myDomainViewCLASS(SUPER, ITEM, NOTIFY, DOMAIN)			\
  vdomainviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN);			\
  vclassMETHOD(myDomainViewRECALC_BARS, (ITEM *domainview));		\
  vclassMETHOD(myDomainViewSET_SMART_SCROLLBARS,			\
	       (ITEM *domainview, vbool hasSmart));			\
  vclassMETHOD(myDomainViewSHOW_GRID_VERTICES,				\
	       (ITEM *domainview, vbool isShowing));			\
  vclassMETHOD(myDomainViewSET_SEL_COLOR,				\
	       (ITEM *domainview, vcolor *selColor));			\
  vclassMETHOD(myDomainViewSET_DRAG_ON_UNSELECTABLES,			\
	       (ITEM *domainview, vbool hasDrag))			\

struct myDomainViewClass {
  myDomainViewCLASS(myDomainViewClass, myDomainView, vdialogItemNoteProc,
		    vdomain);
};

#define myDomainViewGetView(d)		(vportBASE_OBJECT(d, dview))
#define myDomainViewGetLoadable(d)					      \
	vdomainviewGetLoadable(myDomainViewGetView(d))

#define myDomainViewCreateOfClass(c)	\
	((myDomainView *) vdomainviewCreateOfClass((vdomainviewClass *) (c)))
#define myDomainViewCreate()		\
	myDomainViewCreateOfClass(myDomainViewGetDefaultClass())
#define myDomainViewGetClass(v)		\
	((myDomainViewClass *) vdomainviewGetClass(myDomainViewGetView(v)))
#define myDomainViewClone(v)		\
	((myDomainView *) vloadableCloneOfSubclass(myDomainViewGetLoadable(v),\
			     (vloadableClass *) myDomainViewGetDefaultClass()))
#define myDomainViewDestroy(v)		\
	vdomainviewDestroy(myDomainViewGetView(v))

#define myDomainViewGetDomain(v)	\
	vdomainviewGetDomain(myDomainViewGetView(v))
#define myDomainViewGetItem(v)		\
	vdomainviewGetItem(myDomainViewGetView(v))

#define myDomainViewRecalcBars(v)	\
	vclassSend(myDomainViewGetClass(v), myDomainViewRECALC_BARS, (v))
#define myDomainViewHasSmartScrollbars(v)	\
	(((v)->flags & _myDomainViewSMART_SCROLLBARS)	!= 0)
#define myDomainViewSetSmartScrollbars(v, s)	\
	vclassSend(myDomainViewGetClass(v),		\
		   myDomainViewSET_SMART_SCROLLBARS,	\
		   (v, s))
#define myDomainViewIsShowingGridVertices(v)	\
	(((v)->flags & _myDomainViewSHOW_GRID)		!= 0)
#define myDomainViewShowGridVertices(v, s)		\
	vclassSend(myDomainViewGetClass(v),		\
		   myDomainViewSHOW_GRID_VERTICES,	\
		   (v, s))
#define myDomainViewIsLong(v)		\
	vdomainIsLong(vdomainviewGetDomain(myDomainViewGetView(v)))
#define myDomainViewGetSelColor(v)	\
	((v)->selColor)
#define myDomainViewSetSelColor(v, c)			\
	vclassSend(myDomainViewGetClass(v),		\
		   myDomainViewSET_SEL_COLOR, (v, c))
#define myDomainViewHasDragOnUnselectables(v)		\
	(((v)->flags & _myDomainViewDRAG_UNSELECTABLES)	!= 0)
#define myDomainViewSetDragOnUnselectables(v, d)	\
	vclassSend(myDomainViewGetClass(v),		\
		   myDomainViewSET_DRAG_ON_UNSELECTABLES, (v, d))

#endif /* mydviewINCLUDED */
