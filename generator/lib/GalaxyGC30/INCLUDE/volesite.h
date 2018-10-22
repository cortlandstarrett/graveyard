/* $Id: volesite.h,v 1.37 1997/09/11 23:24:03 robert Exp $ */

/************************************************************

    volesite.h

    C Interface file for voleControlSite Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef volesiteINCLUDED
#define volesiteINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef voleINLUDED
#include voleHEADER
#endif

#ifndef volevariantINCLUDED
#include volevariantHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * Public type definitions
 */
typedef struct voleControlSite		voleControlSite;
typedef struct voleControlSiteClass	voleControlSiteClass;

typedef void (*voleControlSiteEventNoteProc)(
    voleControlSite	*site,
    DISPID	         dispid,
    volevariantList	*variantList
    );

typedef void (*voleControlSitePropertyNoteProc)(
    voleControlSite	*site,
    DISPID		dispid
    );

/*
 * Public function prototypes
 */

/*
 * control site definitions
 */
voleControlSiteClass *voleGetDefaultControlSiteClass( 
    void
);

voleControlSiteClass *voleGetControlSiteClass(
    voleControlSite	*site
);

voleControlSite *voleCreateControlSiteOfClass(
    voleControlSiteClass  *clas
);


voleControlSite *voleCreateControlSite(
    void
);

void voleDestroyControlSite(
    voleControlSite *site
);

vdialogItem *voleGetControlSiteItem(
	voleControlSite	*site
);

void voleSetControlSiteObjectType(
    voleControlSite	*site,
    voleObjectTypePtr	type
);

void voleSetControlSiteDistributedObjectType(
    voleControlSite	*site,
    voleObjectTypePtr	 type,
    const vchar		*machineName
);

voleObjectTypePtr voleGetControlSiteObjectType(
    voleControlSite *site
);
    
const vchar *voleGetControlSiteMachineName(
    voleControlSite *site
);

void voleSetControlSiteObjectTypeString(
    voleControlSite *site,
    const vchar     *type
);

void voleSetControlSiteDistributedObjectTypeString(
    voleControlSite *site,
    const vchar     *type,
    const vchar     *machineName
);

vstr *voleGetControlSiteObjectTypeString(
    voleControlSite *site
);

LPUNKNOWN voleGetControlSiteObjectUnknown(
    voleControlSite *site
);

void voleSetControlSiteLicenseKey(
    voleControlSite *site,
    const vchar     *license
);

vstr *voleGetControlSiteLicenseKey(
    voleControlSite *site
);

void voleSetControlSiteLicenseKeyOpaque(
    voleControlSite *site,
    const void      *license,
    size_t           size
);

void voleGetControlSiteLicenseKeyOpaque(
    voleControlSite  *site,
    void            **license,
    size_t           *size
);

vbool voleControlSiteIsEmpty(
    voleControlSite	*site
);

voleResult voleControlSiteQueryInterface(
    voleControlSite    *site,
    voleInterfaceType	itype,
    void	      **ifPtrPtr
);

voleResult voleDoControlSiteVerb(
    voleControlSite    *site,
    long                verb,
    vevent             *vevent
);

void voleSetControlSiteDefaultUserMode(
    vbool set
);

vbool voleGetControlSiteDefaultUserMode(
    void
);

vbool voleGetControlSiteUserMode(
    voleControlSite    *site
);

void voleSetControlSiteUserMode(
    voleControlSite    *site,
    vbool               set
);

vbool voleGetControlSiteUIDead(
    voleControlSite    *site
);

void voleSetControlSiteUIDead(
    voleControlSite    *site,
    vbool		set
);

vbool voleGetControlSiteMessageReflect(
    voleControlSite    *site
);

void voleSetControlSiteMessageReflect(
    voleControlSite    *site,
    vbool				set
);

vbool voleGetControlSiteSupportsMnemonics(
    voleControlSite    *site
);

void voleSetControlSiteSupportsMnemonics(
    voleControlSite    *site,
    vbool				set
);

vbool voleGetControlSiteShowGrabHandles(
    voleControlSite    *site
);

void voleSetControlSiteShowGrabHandles(
    voleControlSite    *site,
    vbool		set
);

vbool voleGetControlSiteShowHatching(
    voleControlSite    *site
);

void voleSetControlSiteShowHatching(
    voleControlSite    *site,
    vbool		set
);

vbool voleGetControlSiteDisplayAsDefault(
    voleControlSite    *site
);

void voleSetControlSiteDisplayAsDefault(
	voleControlSite    *site,
	vbool		    set
);

vbool voleGetControlSiteNotifyEvent(
    voleControlSite    *site,
    DISPID		dispid
);

void voleSetControlSiteNotifyEvent(
    voleControlSite    *site,
    DISPID		dispid,
    vbool		set
);

void voleSetControlSiteNotifyAllEvents(
    voleControlSite    *site,
    vbool               set
);

voleControlSiteEventNoteProc voleGetControlSiteEventNotify(
	voleControlSite			*site
);

void voleSetControlSiteEventNotify(
    voleControlSite			*site,
    voleControlSiteEventNoteProc	notify
);

void voleNotifyControlSiteEventDirect(
    voleControlSite    *site,
    DISPID              dispid,
    DISPPARAMS         *params            
);

void voleNotifyControlSiteEvent(
    voleControlSite    *site,
    DISPID              dispid,
    volevariantList    *variantList
);

void voleUseControlSiteEventNotifyDirect(
    voleControlSite   *site,
    vbool              direct
);

vbool voleControlSiteIsEventNotifyDirect(
    voleControlSite   *site
);

voleControlSitePropertyNoteProc voleGetControlSitePropertyNotify(
	voleControlSite			*site
);

void voleSetControlSitePropertyNotify(
    voleControlSite			*site,
    voleControlSitePropertyNoteProc	notify
);

void voleNotifyControlSiteProperty(
    voleControlSite     *site,
    DISPID               dispid
);

vbool voleControlSiteOnRequestEdit(
    voleControlSite *site,
    DISPID           dispid
);

void voleStartupControlSite(
    void
);


voleResult voleInvokeControlSite(
    voleControlSite *site,
    int              dispid,
    int              flags, 
    volevariantList *variantList,
    volevariant     *variant
);

voleResult voleInvokeControlSiteMethod(
    voleControlSite *site,
    int              dispid,
    volevariantList *variantList,
    volevariant     *variant
);

voleResult voleGetControlSiteProperty(
    voleControlSite *site,
    int              dispid,
    volevariant     *variant
);

voleResult volePutControlSiteProperty(
    voleControlSite *site,
    int              dispid,
    volevariant     *variant
);

voleResult voleInvokeControlSiteSimpleMethod(
    voleControlSite *site,
    int              dispid
);

vbool voleGetControlSiteIDOfName(
    voleControlSite *site,
    const vchar     *name,
    DISPID          *result
);

/*
 * Private type definitions
 */

/*
 * Ambient property settings - stored in "flags".
 */
#define _voleAMBIENT_USER_MODE          0x0001
#define _voleAMBIENT_UI_DEAD            0x0002
#define _voleAMBIENT_MESSAGE_REFLECT    0x0004
#define _voleAMBIENT_SUPPORTS_MNEMONICS 0x0008
#define _voleAMBIENT_SHOW_GRAB_HANDLES  0x0010
#define _voleAMBIENT_SHOW_HATCHING      0x0020
#define _voleAMBIENT_DISPLAY_AS_DEFAULT	0x0040
#define _voleCONTROL_SITE_NOTIFY_DIRECT 0x0100


#define _voleAMBIENT_ALL_FLAGS (    \
	_voleAMBIENT_USER_MODE          |   \
	_voleAMBIENT_UI_DEAD		|   \
	_voleAMBIENT_MESSAGE_REFLECT    |   \
	_voleAMBIENT_SUPPORTS_MNEMONICS |   \
	_voleAMBIENT_SHOW_GRAB_HANDLES  |   \
	_voleAMBIENT_SHOW_HATCHING      |   \
	_voleAMBIENT_DISPLAY_AS_DEFAULT)

#define _voleCOPY_FLAGS \
      ((_voleAMBIENT_ALL_FLAGS & (~(_voleAMBIENT_USER_MODE | _voleAMBIENT_UI_DEAD))) | \
        _voleCONTROL_SITE_NOTIFY_DIRECT)

enum {
    _voleSTATE_PASSIVE               = 0x0001,
    _voleSTATE_LOADED                = 0x0002,
    _voleSTATE_RUNNING               = 0x0004,
    _voleSTATE_ACTIVE                = 0x0008,
    _voleSTATE_UI_ACTIVE             = 0x0010,
    _voleCHANGING_SITE_RECT          = 0x0100,
    _voleCHANGING_CONTROL_RECT       = 0x0200,
    _voleCHANGING_SITE_ATTRIBUTE     = 0x0400,
    _voleCHANGING_CONTROL_PROPERTY   = 0x0800,
    _voleCHANGING_SITE_FORGROUND     = 0x1000,
    _voleCHANGING_CONTROL_FORGROUND  = 0x2000,
    _voleCHANGING_SITE_BACKGROUND    = 0x4000,
    _voleCHANGING_CONTROL_BACKGROUND = 0x8000
};

/*
 * The OLE control site houses an OLE control.
 */
struct voleControlSite {
    vdialogItem	    item;	    /* base dialog item	  	*/
    int		    flags;
    unsigned short *licKey;         /* license Key - Unicode string */
    unsigned int    licSize;
    vstr           *machine;        /* remote machine name for DCOMM */
    int             persistType;
    void           *persistData;
    size_t	    persistSize;
    vdict	   *eventDict;
    voleControlSiteEventNoteProc	eventNotify;
    voleControlSitePropertyNoteProc	propertyNotify;

#if(vportOLE)
    voleObjectType  type;	
    int             state;
    int             oleMiscStatus;
    IID		    eventIID;
    unsigned int    eventSinkID;
    unsigned int    propSinkID;
    LCID            localeID;
    CONTROLINFO     controlInfo;
    ACCEL          *accel;
    int             accelCount;
	/* OLE interface implementatons */
    LPUNKNOWN			pImpUnknown;
    LPOLECLIENTSITE		pImpOleClientSite;
    LPADVISESINK		pImpAdviseSink;
    LPOLEINPLACESITE		pImpOleInPlaceSite;
    LPOLECONTROLSITE		pImpOleControlSite;
    LPSIMPLEFRAMESITE		pImpSimpleFrameSite;
    LPDISPATCH			pImpEventDispatch;
    LPDISPATCH			pImpAmbientPropsDispatch;
    LPPROPERTYNOTIFYSINK	pImpPropertyNotifySink;
	/* OLE interface pointers from object */
    LPUNKNOWN			pUnknown; 
    LPOLEOBJECT			pOleObject;
    LPOLEINPLACEOBJECT		pOleInPlaceObject;
    LPOLECONTROL       		pOleControl;
    LPDISPATCH			pDispatch;
#else
    vstr			*type;
    unsigned long		localeID;	
#endif /* vportOLE */
};

#define voleControlSite_CLASS(SUPER, ITEM, NOTIFY) \
	vdialogITEM_CLASS(SUPER, ITEM, NOTIFY); \
	vclassMETHOD_RET(voleCONTROL_SITE_QUERY_INTERFACE, voleResult, \
		(ITEM *item, voleInterfaceType itype, \
		void **ifPtrPtr)); \
    vclassMETHOD(voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE, \
	    (ITEM *item, voleObjectTypePtr type, const vchar *machineName));   \
    vclassMETHOD(voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE_STRING, \
	    (ITEM *item, const vchar *type, const vchar *machineName));   \
    vclassMETHOD(voleSET_CONTROL_SITE_LICENSE_KEY, \
	    (ITEM *item, const vchar *license));   \
    vclassMETHOD(voleSET_CONTROL_SITE_LICENSE_KEY_OPAQUE, \
	    (ITEM *item, const void *license, size_t size));   \
    vclassMETHOD(voleSET_CONTROL_SITE_USER_MODE, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_UI_DEAD, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_MESSAGE_REFLECT, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_SUPPORTS_MNEMONICS, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_SHOW_GRAB_HANDLES, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_SHOW_HATCHING, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_DISPLAY_AS_DEFAULT, \
		(ITEM *item, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_NOTIFY_EVENT, \
		(ITEM *item, DISPID dispid, vbool set));	\
	vclassMETHOD(voleSET_CONTROL_SITE_EVENT_NOTIFY, \
		(ITEM *item, voleControlSiteEventNoteProc notify));	\
	vclassMETHOD(voleNOTIFY_CONTROL_SITE_EVENT_DIRECT, \
		(ITEM *item, DISPID dispid, DISPPARAMS *params));	\
	vclassMETHOD(voleNOTIFY_CONTROL_SITE_EVENT, \
		(ITEM *item, DISPID dispid, volevariantList *variantList));	\
	vclassMETHOD(voleUSE_CONTROL_SITE_EVENT_NOTIFY_DIRECT, \
		(ITEM *item, vbool direct));	                   \
        vclassMETHOD(voleSET_CONTROL_SITE_PROPERTY_NOTIFY, \
		(ITEM *item, voleControlSitePropertyNoteProc notify));	\
	vclassMETHOD(voleNOTIFY_CONTROL_SITE_PROPERTY, \
		(ITEM *item, DISPID dispid));	\
        vclassMETHOD_RET(voleCONTROL_SITE_ON_REQUEST_EDIT, vbool, \
		(ITEM *item, DISPID dispid));	\
        vclassMETHOD_RET(voleDO_CONTROL_SITE_VERB, voleResult, \
		(ITEM *item, long verb, vevent *event));           \
 	vclassMETHOD_RET(voleINVOKE_CONTROL_SITE, voleResult,  \
                    (ITEM *item, int dispid,  int flags,   \
                       volevariantList *variantList,  volevariant *variant)) 

struct voleControlSiteClass {
	voleControlSite_CLASS(voleControlSiteClass, voleControlSite,
		vdialogItemNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vportOLE)

HWND _voleControlSiteDetermineMSWWindow(voleControlSite *site);

void _voleControlSiteGetMSWRect(voleControlSite *site, LPRECT mswRect);

void _viunk_Create(voleControlSite *site, LPUNKNOWN *ppUnk);
void _vias_Create(voleControlSite *site, LPADVISESINK *ppSink);
void _viocs_Create(voleControlSite *site, LPOLECLIENTSITE *ppSite);
void _vioips_Create(voleControlSite *site, LPOLEINPLACESITE *ppSite);
void _vioctls_Create(voleControlSite *site, LPOLECONTROLSITE *ppi);
void _vsfs_Create(voleControlSite *site, LPSIMPLEFRAMESITE *ppi);
       
void _vievdisp_Create(voleControlSite *site, LPDISPATCH *ppi);
void _vipns_Create(voleControlSite *site, LPPROPERTYNOTIFYSINK *ppi);
void _viapdisp_Create(voleControlSite *site, LPDISPATCH *ppi);

#endif  /* vportOLE */

/*
 * Macro implementations
 */
#define voleGetControlSiteObjectType(s) (&(s)->type)

#define voleGetControlSiteClass(s) \
	(voleControlSiteClass *) vdialogGetItemClass(voleGetControlSiteItem(s))

#define voleGetControlSiteItem(s) (vportBASE_OBJECT((s), item))

#define voleCreateControlSiteOfClass(c) \
    ((voleControlSite*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))

#define voleCreateControlSite()  \
    voleCreateControlSiteOfClass(voleGetDefaultControlSiteClass())

#define voleDestroyControlSite(s)  \
    vdialogDestroyItem(voleGetControlSiteItem(s))

#define voleGetControlSiteMachineName(s)    \
	((s)->machine)

#define voleGetControlSiteUserMode(s)	\
	((((s)->flags) & _voleAMBIENT_USER_MODE) != 0)

#define voleGetControlSiteUIDead(s)	\
	((((s)->flags) & _voleAMBIENT_UI_DEAD) != 0)

#define voleGetControlSiteMessageReflect(s)	\
	((((s)->flags) & _voleAMBIENT_MESSAGE_REFLECT) != 0)

#define voleGetControlSiteSupportsMnemonics(s)	\
	((((s)->flags) & _voleAMBIENT_SUPPORTS_MNEMONICS) != 0)

#define voleGetControlSiteShowGrabHandles(s)	\
	((((s)->flags) & _voleAMBIENT_SHOW_GRAB_HANDLES) != 0)

#define voleGetControlSiteShowHatching(s)	\
	((((s)->flags) & _voleAMBIENT_SHOW_HATCHING) != 0)

#define voleGetControlSiteDisplayAsDefault(s)	\
	((((s)->flags) & _voleAMBIENT_DISPLAY_AS_DEFAULT) != 0)

#define voleGetControlSiteEventNotify(s)	\
	((s)->eventNotify)

#define voleControlSiteIsEventNotifyDirect(s) \
	((((s)->flags) &  _voleCONTROL_SITE_NOTIFY_DIRECT) != 0)

#define voleGetControlSitePropertyNotify(s)	\
	((s)->propertyNotify)

#define voleInvokeControlSiteMethod(s, d, l, v)   \
	voleInvokeControlSite(s, d, DISPATCH_METHOD, l, v)

#define voleInvokeControlSiteSimpleMethod(s, d)   \
	voleInvokeControlSite(s, d, DISPATCH_METHOD, NULL, NULL)

#define voleGetControlSiteProperty(s, d, v)   \
	voleInvokeControlSite(s, d, DISPATCH_PROPERTYGET, NULL, v)

/*
 *         PRIVATE FUNCTION MESSAGE DEFINITIONS 
 */
#define voleSetControlSiteObjectType(s, t) \
	vclassSend(voleGetControlSiteClass(s), \
	voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE, (s, t, NULL))

#define voleSetControlSiteDistributedObjectType(s, t, m) \
	vclassSend(voleGetControlSiteClass(s), \
	voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE, (s, t, m))

#define voleSetControlSiteObjectTypeString(s, t) \
	vclassSend(voleGetControlSiteClass(s), \
	voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE_STRING, (s, t, NULL))

#define voleSetControlSiteDistributedObjectTypeString(s, t, m) \
	vclassSend(voleGetControlSiteClass(s), \
	voleSET_CONTROL_SITE_DISTRIBUTED_OBJECT_TYPE_STRING, (s, t, m))

#define voleSetControlSiteLicenseKey(s, l) \
	vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_LICENSE_KEY, (s, l))

#define voleSetControlSiteLicenseKeyOpaque(s, l, size) \
	vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_LICENSE_KEY_OPAQUE, (s, l, size))

#define voleControlSiteQueryInterface(s, t, i) \
	vclassSend(voleGetControlSiteClass(s), voleCONTROL_SITE_QUERY_INTERFACE, (s, t, i))

#define voleSetControlSiteUserMode(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_USER_MODE, (s, b))

#define voleSetControlSiteUIDead(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_UI_DEAD, (s, b))

#define voleSetControlSiteMessageReflect(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_MESSAGE_REFLECT, (s, b))

#define voleSetControlSiteSupportsMnemonics(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_SUPPORTS_MNEMONICS, (s, b))

#define voleSetControlSiteShowGrabHandles(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_SHOW_GRAB_HANDLES, (s, b))

#define voleSetControlSiteShowHatching(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_SHOW_HATCHING, (s, b))

#define voleSetControlSiteDisplayAsDefault(s, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_DISPLAY_AS_DEFAULT, (s, b))

#define voleSetControlSiteNotifyEvent(s, d, b)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_NOTIFY_EVENT, (s, d, b))

#define voleSetControlSiteEventNotify(s, f)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_EVENT_NOTIFY, (s, f))

#define voleNotifyControlSiteEventDirect(s, d, p)   \
    vclassSend(voleGetControlSiteClass(s), voleNOTIFY_CONTROL_SITE_EVENT_DIRECT, (s, d, p))

#define voleNotifyControlSiteEvent(s, d, l)   \
    vclassSend(voleGetControlSiteClass(s), voleNOTIFY_CONTROL_SITE_EVENT, (s, d, l))

#define voleUseControlSiteEventNotifyDirect(s, d)  \
    vclassSend(voleGetControlSiteClass(s), voleUSE_CONTROL_SITE_EVENT_NOTIFY_DIRECT, (s, d))

#define voleSetControlSitePropertyNotify(s, f)   \
    vclassSend(voleGetControlSiteClass(s), voleSET_CONTROL_SITE_PROPERTY_NOTIFY, (s, f))

#define voleNotifyControlSiteProperty(s, d)   \
    vclassSend(voleGetControlSiteClass(s), voleNOTIFY_CONTROL_SITE_PROPERTY, (s, d))

#define voleControlSiteOnRequestEdit(s, d) \
    vclassSend(voleGetControlSiteClass(s), voleCONTROL_SITE_ON_REQUEST_EDIT, (s, d))

#define voleDoControlSiteVerb(s, v, e)   \
    vclassSend(voleGetControlSiteClass(s), voleDO_CONTROL_SITE_VERB, (s, v, e))

#define voleInvokeControlSite(s, d, f, l, v)  \
    vclassSend(voleGetControlSiteClass(s), voleINVOKE_CONTROL_SITE, (s, d, f, l, v))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* volesiteINCLUDED */
