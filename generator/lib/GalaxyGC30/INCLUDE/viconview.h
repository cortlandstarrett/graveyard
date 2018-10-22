/* $Id: viconview.h,v 1.40 1997/09/19 22:45:05 robert Exp $ */

/************************************************************

    viconview.h
    C Interface to icon view items

    Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef viconviewINCLUDED
#define viconviewINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdomainitemINCLUDED
#include vdomainitemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for the domain object type, for an icon's objects */

enum {
    viconviewIMAGE_TYPE        = 1,
    viconviewNAME_TYPE         = 2
};

#define viconviewICON_BORDER		3

#define viconview_ViewType	(_viconviewPredefs[_viconview_ViewType])
#define viconview_Icons		(_viconviewPredefs[_viconview_Icons])
#define viconview_Images	(_viconviewPredefs[_viconview_Images])
#define viconview_Position	(_viconviewPredefs[_viconview_Position])
#define viconview_NameIcon	(_viconviewPredefs[_viconview_NameIcon])

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct viconview          	viconview;
typedef struct viconviewClass    	viconviewClass;
typedef struct viconviewIcon	  	viconviewIcon;
typedef struct viconviewView	  	viconviewView;
typedef struct viconviewIterator        viconviewIterator;
typedef struct viconviewGridIterator    viconviewGridIterator;
typedef vdomainitemDomain		viconviewDomain;

typedef void (*viconviewSelectNoteProc)(
    viconview			*iconView,
    viconviewIcon		*icon,
    vevent			*event,
    vbool			selected
    );

typedef void (*viconviewGeometryProc)(
    viconview			*iconView,
    viconviewView		*view,
    viconviewIcon		*icon,
    vpoint			*position,
    vrect			*imageRect,
    vrect			*nameRect
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void viconviewStartup(void);


/* Icon View Class Functions */

viconviewClass *viconviewGetDefaultClass(void);

/* Initialization and allocation */

viconview *viconviewCreate(void);

viconview *viconviewCreateOfClass(
    viconviewClass	*clas
    );
    
viconview *viconviewClone(
    viconview	    	*iconview
    );

void viconviewCopy(
    viconview    	*iconview,
    viconview	    	*targetItem
    );

void viconviewCopyInit(
    viconview    	*iconview,
    viconview	    	*targetItem
    );

void viconviewInit(
    viconview	    	*iconview
    );

void viconviewInitOfClass(
    viconview		*iconview,
    viconviewClass	*clas
    );

void viconviewDestroy(
    viconview	    	*iconview
    );

viconview *viconviewLoad(
    vresource		resource
    );

void viconviewLoadInit(
    viconview		*iconview,
    vresource		resource
    );

void viconviewStore(
    viconview		*iconview,
    vresource		resource
    );

vdomainitem *viconviewGetDomainItem(
    viconview		*iconview
    );

vloadable *viconviewGetLoadable(
    viconview		*iconview
    );

/* Icon view operations */	

void viconviewCleanup(
    viconview		*iconview
    );

int viconviewGetIconCount(
    viconview           *iconView
    );

void viconviewInitIterator(
    viconviewIterator   *iterator,
    viconview           *iconView
    );

int viconviewNextIterator(
    viconviewIterator   *iterator
    );

void viconviewDestroyIterator(
    viconviewIterator   *iterator
    );

viconviewIcon *viconviewGetIteratorIcon(
    viconviewIterator   *iterator
    );

void viconviewInitGridIterator(
    viconviewGridIterator   *iterator,
    viconview               *iconView
    );

int viconviewNextGridIterator(
    viconviewGridIterator   *iterator
    );

void viconviewDestroyGridIterator(
    viconviewGridIterator   *iterator
    );

vpoint *viconviewGetGridIteratorPosition(
    viconviewGridIterator   *iterator
    );

/* Icon View attribute modification */

void viconviewSetSelectNotify(
    viconview		    *iconView,
    viconviewSelectNoteProc noteProc
    );

void viconviewSetData(
    viconview		*iconview,
    void		*data
    );

void viconviewSetView(
    viconview		*iconview,
    viconviewView       *view
    );

void viconviewSetImage(
    viconview		*iconview,
    viconviewView       *view,
    vimage		*image
    );

void viconviewSetImageOwned(
    viconview		*iconview,
    viconviewView       *view,
    vimage		*image
    );

/* Icon View attribute access */

viconviewClass *viconviewGetClass(
    viconview		*iconview
    );

viconviewSelectNoteProc viconviewGetSelectNotify(
    viconview		    *iconView
    );

void *viconviewGetData(
    viconview		*iconview
    );

viconviewView *viconviewGetView(
    viconview		*iconview
    );

vimage *viconviewGetImage(
    viconview		*iconview,
    viconviewView       *view
    );

/* Icon routines */

viconviewIcon *viconviewCreateIcon(void);

void viconviewDestroyIcon(
    viconviewIcon	*icon
    );

void viconviewAddIcon(
    viconview		*iconView,
    viconviewIcon	*icon
    );

void viconviewRemoveIcon(
    viconview		*iconView,
    viconviewIcon	*icon
    );

vimage *viconviewDetermineIconImage(
    viconviewIcon	*icon,
    viconviewView       *view
    );

/* Icon attribute modification */

void viconviewSetIconData(
    viconviewIcon	*icon,
    void	        *data
    );

void viconviewSetIconName(
    viconviewIcon	*icon,
    const vchar		*name
    );

void viconviewSetIconNameScribed(
    viconviewIcon	*icon,
    vscribe		*scribe
    );

void viconviewSetIconPosition(
    viconviewIcon	*icon,
    vpoint		*position
    );

void viconviewSetIconImage(
    viconviewIcon	*icon,
    viconviewView       *view,
    vimage		*image
    );

void viconviewSetIconImageOwned(
    viconviewIcon	*icon,
    viconviewView       *view,
    vimage		*image
    );

/* Icon attribute access */

void *viconviewGetIconData(
    viconviewIcon	*icon
    );

vchar *viconviewGetIconName(
    viconviewIcon	*icon
    );

vpoint viconviewGetIconPosition(
    viconviewIcon	*icon
    );

vimage *viconviewGetIconImage(
    viconviewIcon	*icon,
    viconviewView       *view
    );

vbool viconviewIsIconSelected(
    viconviewIcon	*icon
    );

/* Icon View routines */

viconviewView *viconviewGetIconView(void);

viconviewView *viconviewGetNameView(void);

viconviewView *viconviewCreateView(void);

viconviewView *viconviewCloneView(
    viconviewView       *view
    );

void viconviewCopyView(
    viconviewView       *view,
    viconviewView       *targetView
    );

void viconviewDestroyView(
    viconviewView       *view
    );

/* View operations */

viconviewView *viconviewLoadView(
    vresource		resource
    );

void viconviewLoadInitView(
    viconviewView	*view,
    vresource		resource
    );

void viconviewStoreView(
    viconviewView	*view,
    vresource		resource
    );

/* View attribute modification */

void viconviewSetViewImage(
    viconviewView       *view,
    vimage              *image
    );

void viconviewSetViewName(
    viconviewView       *view,
    const vchar         *name
    );

void viconviewSetViewNameScribed(
    viconviewView       *view,
    vscribe             *scribe
    );

void viconviewSetViewGrid(
    viconviewView       *view,
    vdomainGrid		*grid
    );

void viconviewSetViewGeometryProc(
    viconviewView       	*view,
    viconviewGeometryProc	proc
    );

void viconviewSetViewInset(
    viconviewView	*view,
    vpoint		*pt
    );

/* View attribute access */

vimage *viconviewGetViewImage(
    viconviewView       *view
    );

vchar *viconviewGetViewName(
    viconviewView       *view
    );

vdomainGrid *viconviewGetViewGrid(
    viconviewView       *view
    );

viconviewGeometryProc viconviewGetViewGeometryProc(
    viconviewView       *view
    );

vpoint viconviewGetViewInset(
    viconviewView	*view
    );

/* Other Routines */

void viconviewGetIconObjects(
    viconviewIcon	*icon,
    vdomainObject	**iconObject,
    vdomainObject	**nameObject
    );

vdomainObjectSet *viconviewGetIconObjectSet(
    viconviewIcon	*icon
    );

viconviewIcon *viconviewIconFromObject(
    vdomainObject	*object
    );

vdialogItem *viconviewGetItem(
    viconview		*iconview
    );

vdomainview *viconviewGetDomainView(
    viconview		*iconview
    );

vdomain *viconviewGetDomain(
    viconview		*iconview
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _viconviewOWN_NAME              = 0x0001,	/* flags for icons and views */
    _viconviewOWN_IMAGE             = 0x0002,
    _viconviewCACHE_VALID	    = 0x0001	/* flags for viconviews */
};

/*
 * Global icon view strings
 */

enum {
    _viconview_ViewType,
    _viconview_Icons,
    _viconview_Images,
    _viconview_Position,
    _viconview_NameIcon,
    _viconview_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _viconviewPair{
    viconviewView        	*view;
    const vname			*viewName;
    vimage                      *image;
    vbool			owned;
} _viconviewPair;

typedef struct _viconviewImages {
     vbyte	        count;
     union {
         _viconviewPair     image[2];
         _viconviewPair     *images;
     } u;
} _viconviewImages;

/* viconview */

struct viconview {
    vdomainitem			item;
    int				count;
    viconviewView              *view;
    viconviewSelectNoteProc   	notify;
    vpoint			cachedPosition;
    vbyte			flags;
    _viconviewImages            images;
};
 
/* viconviewIcon */

struct viconviewIcon {
    vinstance		instance;
    vdomainObject       *iconObject;
    void		*data;
    vchar		*name;
    viconview		*owner;
    vbyte               flags;
    _viconviewImages    images; 
};

#define viconviewIconCLASS(SUPER, OBJECT)				      \
    vinstanceCLASS(SUPER, OBJECT)

typedef struct viconviewIconClass	viconviewIconClass;

struct viconviewIconClass {
    viconviewIconCLASS(viconviewIconClass, viconviewIcon);
};


/* viconviewView */

struct viconviewView {
    vloadable			object;
    vchar               	*name;
    vimage              	*image;
    vdomainGrid         	grid;
    int                 	flags;
    vpoint			inset;
    viconviewGeometryProc	geometryProc;
};


#define viconviewViewCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct viconviewViewClass	viconviewViewClass;

struct viconviewViewClass {
    viconviewViewCLASS(viconviewViewClass, viconviewView);
};


/* viconviewIterator */

struct viconviewIterator {
    viconview			*iconView;
    vdomainObject		*object;
};

/* viconviewGridIterator */

struct viconviewGridIterator {
    vdomainGrid			*grid;
    vpoint			pt;
    int				maxWidth;
    int				startX, startY;
};

/*
 * Iconview Class Definition
 */

#define viconviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN, ICON)	       \
    vdomainitemCLASS(SUPER, ITEM, NOTIFY, DOMAIN);		       \
    vclassMETHOD(viconviewADD_ICON,    (ITEM *iconview, ICON *newIcon));      \
    vclassMETHOD(viconviewREMOVE_ICON, (ITEM *iconview, ICON *newIcon));      \
    vclassMETHOD(viconviewCLEANUP,     (ITEM *iconview));		      \
    vclassMETHOD(viconviewDRAW_OBJECT, (ITEM *iconview, vdomainObject *object))

struct viconviewClass {
    viconviewCLASS(viconviewClass, viconview, vdialogItemNoteProc,
		     vdomain, viconviewIcon);
};

vportALIAS(viconviewDomain, vdomainitemDomain)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _viconviewCallSelectNoteProc(viconview *iconview, viconviewIcon *icon,
				  vevent *event, vbool selected);

viconviewViewClass *_viconviewGetDefaultViewClass(void);

viconviewViewClass *_viconviewGetViewClass(
    viconviewView			*view
    );

vloadable *_viconviewGetViewLoadable(
    viconviewView			*view
    );

viconviewView *_viconviewCreateViewOfClass(
    viconviewViewClass			*clas
    );

void _viconviewInitViewOfClass(
    viconviewView			*view,
    viconviewViewClass			*clas
    );

void _viconviewCallViewGeometryProc(viconviewView *view, viconview *iconview,
				    viconviewIcon *icon, vpoint *position,
				    vrect *iconRect, vrect *nameRect);

_viconviewPair *_viconviewFindPairByView(_viconviewImages *images,
					 viconviewView *view);

viconviewIconClass *_viconviewGetDefaultIconClass(void);

viconviewIconClass *_viconviewGetIconClass(
    viconviewIcon			*icon
    );

vinstance *_viconviewGetIconInstance(
    viconviewIcon			*icon
    );

viconviewIcon *_viconviewCreateIconOfClass(
    viconviewIconClass			*clas
    );

void _viconviewInitIconOfClass(
    viconviewIcon			*icon,
    viconviewIconClass			*clas
    );

vbool _viconviewIsCacheValid(
    viconview				*iconView
    );

void _viconviewSetCacheValidity(
    viconview				*iconView,
    vbool				valid
    );

void _viconviewNudgeGridIteratorNearPosition(
    viconviewGridIterator		*iterator,
    vpoint				*position
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define viconviewGetDomainItem(i)	(vportBASE_OBJECT(i, item))
#define viconviewGetLoadable(i)		\
	vdomainitemGetLoadable(viconviewGetDomainItem(i))
#define viconviewGetItem(i)		\
	(vdomainitemGetItem(viconviewGetDomainItem(i)))
#define viconviewGetDomainView(i)	\
	(vdomainitemGetView(viconviewGetDomainItem(i)))
#define viconviewGetDomain(i)		\
	(vdomainitemGetDomain(viconviewGetDomainItem(i)))
#define viconviewCreateOfClass(c)	\
	((viconview *) vdomainitemCreateOfClass((vdomainitemClass *) (c)))
#define viconviewCreate()		\
	viconviewCreateOfClass(viconviewGetDefaultClass())
#define viconviewInitOfClass(e,c)	\
	vdomainitemInitOfClass(viconviewGetDomainItem(e),	\
			       (vdomainitemClass *) (c))
#define viconviewInit(e)		\
	viconviewInitOfClass((e), viconviewGetDefaultClass());
#define viconviewDestroy(v)		\
	vdomainitemDestroy(viconviewGetDomainItem(v))
#define viconviewClone(v)		\
	((viconview *) vloadableCloneOfSubclass(viconviewGetLoadable(v),      \
				(vloadableClass *) viconviewGetDefaultClass()))
#define viconviewCopyInit(c,t)		\
	vloadableCopyInitOfSubclass(viconviewGetLoadable(c),		      \
				    viconviewGetLoadable(t),		      \
				 (vloadableClass *) viconviewGetDefaultClass())
#define viconviewCopy(c, t)		\
	vdomainitemCopy(viconviewGetDomainItem(c), viconviewGetDomainItem(t))
#define viconviewLoad(r)		\
	((viconview *) vloadableLoadOfSubclass(r,			      \
				(vloadableClass *) viconviewGetDefaultClass()))
#define viconviewLoadInit(c,r)		\
	vloadableLoadInitOfSubclass(viconviewGetLoadable(c), r,		      \
				 (vloadableClass *) viconviewGetDefaultClass())
#define viconviewStore(i, r)		\
	vdomainitemStore(viconviewGetDomainItem(i), r)
#define viconviewGetClass(e)		\
	((viconviewClass *) vdomainitemGetClass(viconviewGetDomainItem(e)))

#define viconviewSetData(e, d)		\
	vdomainitemSetData(viconviewGetDomainItem(e), d)
#define viconviewGetData(e)		\
	vdomainitemGetData(viconviewGetDomainItem(e))
#define viconviewGetView(e)		((e)->view)
#define viconviewDestroyIterator(i)
#define viconviewGetIteratorIcon(i)	(viconviewIconFromObject((i)->object))
#define viconviewDestroyGridIterator(i)
#define viconviewGetGridIteratorPosition(i)	(&(i)->pt)
#define viconviewGetIconCount(v)	((v)->count)
#define viconviewSetSelectNotify(i,n)	((i)->notify = (n))
#define viconviewGetSelectNotify(i)	((i)->notify)

#define _viconviewGetViewLoadable(v)	(vportBASE_OBJECT(v, object))

#define _viconviewGetViewClass(v)	\
	((viconviewViewClass *) vloadableGetClass(_viconviewGetViewLoadable(v)))
#define _viconviewCreateViewOfClass(c)	\
	((viconviewView *) vloadableCreateOfClass((vloadableClass *)(c)))
#define _viconviewInitViewOfClass(v, c)	\
	vloadableInitOfClass(_viconviewGetViewLoadable(v), (vloadableClass *)(c))
#define viconviewCreateView()		\
	(_viconviewCreateViewOfClass(_viconviewGetDefaultViewClass()))
#define viconviewCloneView(v)		\
	((viconviewView *) vloadableClone(_viconviewGetViewLoadable(v)))
#define viconviewDestroyView(v)		\
	vloadableDestroy(_viconviewGetViewLoadable(v))
#define viconviewCopyView(v, r)		\
	vloadableCopy(_viconviewGetViewLoadable(v), \
		      _viconviewGetViewLoadable(r))
#define viconviewStoreView(v, r)	\
	vloadableStore(_viconviewGetViewLoadable(v), r)

#define viconviewSetViewName(v,s)	\
	viconviewSetViewNameScribed(v, vcharScribe(s))
#define viconviewSetViewGrid(v,g)	((v)->grid = *(g))
#define viconviewGetViewImage(v)	((v)->image)
#define viconviewGetViewName(v)		((v)->name)
#define viconviewGetViewGrid(v)		(&(v)->grid)
#define viconviewSetViewGeometryProc(v,p)	((v)->geometryProc = (p))
#define viconviewGetViewGeometryProc(v)		((v)->geometryProc)
#define viconviewSetViewInset(v,p)	((v)->inset = (*p))
#define viconviewGetViewInset(v)	((v)->inset)


#define _viconviewGetIconInstance(v)	\
	(vportBASE_OBJECT(v, instance))

#define _viconviewGetIconClass(v)	\
	((viconviewIconClass*)vinstanceGetClass(_viconviewGetIconInstance(v)))

#define _viconviewCreateIconOfClass(c)	\
	((viconviewIcon*)vinstanceCreateOfClass((vinstanceClass*)(c)))

#define _viconviewInitIconOfClass(v, c)	\
	vinstanceInitOfClass(_viconviewGetIconInstance(v), \
			     (vinstanceClass*)(c))

#define viconviewCreateIcon()		\
	(_viconviewCreateIconOfClass(_viconviewGetDefaultIconClass()))

#define viconviewDestroyIcon(v)		\
	vinstanceDestroy(_viconviewGetIconInstance(v))

#define viconviewSetIconData(i,d)	((i)->data = (d))
#define viconviewGetIconData(i)		((i)->data)
#define viconviewGetIconName(i)		((i)->name)
#define viconviewSetIconName(i,n)	\
	viconviewSetIconNameScribed(i, vcharScribe(n))

#define _viconviewIsCacheValid(v)	\
	(((v)->flags & _viconviewCACHE_VALID) != 0)
#define _viconviewSetCacheValidity(v, c)	\
	(c ? ((v)->flags |= _viconviewCACHE_VALID) :	\
	     ((v)->flags &= ~_viconviewCACHE_VALID))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define viconviewAddIcon(e,i)	 vclassSend(viconviewGetClass(e), \
					    viconviewADD_ICON, (e,i))
#define viconviewRemoveIcon(e,i) vclassSend(viconviewGetClass(e), \
					    viconviewREMOVE_ICON, (e,i))
#define viconviewCleanup(e)	 vclassSend(viconviewGetClass(e), \
					    viconviewCLEANUP, (e))

/*
 * * * * * * * * * ICON VIEW GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef viconviewINCLUDED */
