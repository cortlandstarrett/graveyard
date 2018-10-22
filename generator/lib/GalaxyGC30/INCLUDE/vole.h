/* $Id: vole.h,v 1.44 1997/09/24 20:12:55 alex Exp $ */

/************************************************************

    vole.h

    C Interface file for OLE support

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef voleINCLUDED
#define voleINCLUDED

#if (vportOLE)
/*
 * we use c-style OLE definitions 
 */
#ifndef CINTERFACE
#define CINTERFACE
#endif

#ifndef COBJMACROS
#define COBJMACROS
#endif
#endif

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#if (vportOLE)
#ifndef  vmswhdrsINCLUDED
#include vmswhdrsHEADER
#endif

#include <olectl.h>
#include <initguid.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */



/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */
#if (vportOLE)
typedef CLSID						voleObjectType;
typedef	HRESULT						voleResult;

#if (vportCPLUSPLUS_SOURCE)
typedef const CLSID * const  	        		voleObjectTypePtr;
typedef const IID * const				voleInterfaceTypePtr;
#else
typedef REFCLSID					voleObjectTypePtr;
typedef REFIID						voleInterfaceTypePtr;
#endif

typedef voleInterfaceTypePtr				voleInterfaceType;

#else

typedef	long						HRESULT;
typedef	long						voleResult;
typedef void*		                                voleObjectTypePtr;
typedef void*						voleInterfaceType;

#ifndef __IUnknown_INTERFACE_DEFINED__
typedef void*						LPUNKNOWN;
#endif

#ifndef __ITypeInfo_INTERFACE_DEFINED__
typedef void*						LPTYPEINFO;
#endif

#ifndef __IDispatch_INTERFACE_DEFINED__
typedef void*						LPDISPATCH;
#endif

#ifndef __RemVariant_INTERFACE_DEFINED__
typedef unsigned short*             BSTR;
#endif

typedef unsigned short	            VARTYPE;
typedef long                        DISPID;

#ifndef __oaidl_h__
typedef struct DISPPARAMS           DISPPARAMS;
typedef struct SAFEARRAY            SAFEARRAY;
#endif

#ifndef _CY_DEFINED
typedef struct CY                   CY;
#endif

#ifndef __IID_DEFINED__
typedef struct {         
    long   Data1;
    short  Data2;
    short  Data3;
    vbyte  Data4[8];
} CLSID;
typedef CLSID						voleObjectType;
typedef CLSID						GUID;
#endif

#ifndef E_FAIL
#define E_FAIL     0x80004005L
#endif

#ifndef DISPATCH_METHOD
#define DISPATCH_METHOD         0x1
#define DISPATCH_PROPERTYGET    0x2
#define DISPATCH_PROPERTYPUT    0x4
#define DISPATCH_PROPERTYPUTREF 0x8
#endif

#endif  /* vportOLE */

typedef struct voleException {
	vexException	parent;
	voleResult	result;		/* result code from OLE call	*/
} voleException;

typedef struct voleDispatchException {
	voleException	parent;
        unsigned short	code;           /* Object exception code, excludes result (scode) */
	char		*source;	/* ProgID of object		*/
	char		*description;	/* Text description of error	*/
	char		*helpFile;	/* Full path to a help file	*/
	unsigned long	helpContext;	/* Help context ID to display	*/
} voleDispatchException;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * OLE utility function prototypes.
 */
void voleStartup(
	void
);

vstr *voleMessage(
	voleResult code
);

vbool voleIsSupported(
	void
);

vbool voleGetCLSIDFromProgID(
	const vchar *progID,
	CLSID       *clsid
);

vbool voleGetCLSIDFromStr(
	const vchar *value,
	CLSID       *clsid
);

vstr *voleGetStrFromCLSID(
	const CLSID *clsid
);

vstr *voleGetNameFromCLSID(
	const CLSID *clsid
);

vstr *voleGetControlClassName(
    const CLSID *clsid
);

vstr *voleGetInterfaceName(
    const GUID *guid
);

BSTR voleGetBSTR(
    const vchar *str
);

vstr *voleGetString(
    const BSTR bstr
);

vcolor *voleGetColor(
    int clr
);

int voleGetOleColor(
    vcolor *color
);

void voleGetTypeInfoFromCLSID(
    const CLSID *clsid,
    LPTYPEINFO *ppTypeInfo
);

vexClass *voleGetExceptionClass(
	void
);

voleException *voleGetException(
	void
);

voleResult voleGetExceptionResult(
	voleException	*excep
);

void voleRESULT(
	void	*excep,
	va_list	*ap
);

vexClass *voleGetDispatchExceptionClass(
	void
);

voleDispatchException *voleGetDispatchException(
	void
);

voleResult voleGetDispatchExceptionResult(
	voleDispatchException	*excep
);

unsigned short voleGetDispatchExceptionCode(
	voleDispatchException	*excep
);

char *voleGetDispatchExceptionSource(
	voleDispatchException	*excep
);

char *voleGetDispatchExceptionDescription(
	voleDispatchException	*excep
);

char *voleGetDispatchExceptionHelpFile(
	voleDispatchException	*excep
);

unsigned long voleGetDispatchExceptionHelpContext(
	voleDispatchException	*excep
);


void voleDispatchCODE(
	void	*excep,
	va_list	*ap
);


void voleDispatchSOURCE(
	void	*excep,
	va_list	*ap
);

void voleDispatchDESCRIPTION(
	void	*excep,
	va_list	*ap
);

void voleDispatchHELPFILE(
	void	*excep,
	va_list	*ap
);

void voleDispatchHELPCONTEXT(
	void	*excep,
	va_list	*ap
);


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */



/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

vportALIAS(vole, void)


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define voleGetExceptionResult(e) ((e)->result)

#define voleGetDispatchExceptionResult(e)   voleGetExceptionResult(&(e)->parent)
#define voleGetDispatchExceptionCode(e)		((e)->code)
#define voleGetDispatchExceptionSource(e)	((e)->source)
#define voleGetDispatchExceptionDescription(e)	((e)->description)
#define voleGetDispatchExceptionHelpFile(e)	((e)->helpFile)
#define voleGetDispatchExceptionHelpContext(e)	((e)->helpContext)

#if (vportOLE)

#ifdef COBJMACROS

#ifndef IOleControlSite_QueryInterface

#define IOleControlSite_QueryInterface(This, riid, ppvObject)	\
        (This)->lpVtbl->QueryInterface(This, riid, ppvObject)

#define IOleControlSite_AddRef(This)	\
        (This)->lpVtbl->AddRef(This)

#define IOleControlSite_Release(This)	\
        (This)->lpVtbl->Release(This)

/* IOleControlSite methods */
#define IOleControlSite_OnControlInfoChanged(This)   \
        (This)->lpVtbl->OnControlInfoChanged(This)

#define IOleControlSite_LockInPlaceActive(This)	\
        (This)->lpVtbl->LockInPlaceActive(This)

#define IOleControlSite_GetExtendedControl(This, ppDisp)	\
        (This)->lpVtbl->GetExtendedControl(This, ppDisp)

#define IOleControlSite_TransformCoords(This, lpptlHimetric, lpptfContainer, flags)  \
        (This)->lpVtbl->TransformCoords(This, lpptlHimetric, lpptfContainer, flags)

#define IOleControlSite_TranslateAccelerator(This, lpMsg, grfModifiers)	\
        (This)->lpVtbl->TranslateAccelerator(This, lpMsg, grfModifiers)

#define IOleControlSite_OnFocus(This, fGotFocus)  \
        (This)->lpVtbl->OnFocus(This, fGotFocus)

#define IOleControlSite_ShowPropertyFrame(This)   \
        (This)->lpVtbl->ShowPropertyFrame(This)

#endif /* #ifndef IOleControlSite_QueryInterface */


#ifndef IOleControl_QueryInterface
/*
 * IOleControl interface C macros
 */
	/* IUnknown methods  */
#define IOleControl_QueryInterface(This, riid, ppvObj) \
        (This)->lpVtbl->QueryInterface(This, riid, ppvObj)
#define IOleControl_AddRef(This)   \
        (This)->lpVtbl->AddRef(This)
#define IOleControl_Release(This) \
        (This)->lpVtbl->Release(This)

	/* IOleControl methods  */
#define IOleControl_GetControlInfo(This, pCI) \
        (This)->lpVtbl->GetControlInfo(This, pCI)

#define IOleControl_OnMnemonic(This, pMsg) \
        (This)->lpVtbl->OnMnemonic(This, pMsg)

#define IOleControl_OnAmbientPropertyChange(This, dispid) \
        (This)->lpVtbl->OnAmbientPropertyChange(This, dispid)

#define IOleControl_FreezeEvents(This, bFreeze)  \
        (This)->lpVtbl->FreezeEvents(This, bFreeze)
#endif /* IOleControl_QueryInterface */


#ifndef IPropertyNotifySink_QueryInterface
/*
 * IPropertyNotifySink interface C macros
 */
	/* IUnknown methods */
#define IPropertyNotifySink_QueryInterface(This, riid, ppvObj) \
        (This)->lpVtbl->QueryInterface(This, riid, ppvObj)

#define IPropertyNotifySink_AddRef(This) \
        (This)->lpVtbl->AddRef(This)

#define IPropertyNotifySink_Release(This) \
        (This)->lpVtbl->Release(This)

    /* IPropertyNotifySink methods */
#define IPropertyNotifySink_OnChanged(This, dispid) \
        (This)->lpVtbl->OnChanged(This, dispid)

#define IPropertyNotifySink_OnRequestEdit(This, dispid) \
        (This)->lpVtbl->OnRequestEdit

#endif /* IPropertyNotifySink_QueryInterface */


#ifndef IConnectionPointContainer_QueryInterface
/*
 * IConnectionPointContainer interface C macros
 */

    /* IUnknown methods */
#define IConnectionPointContainer_QueryInterface(This, riid, ppvObj) \
        (This)->lpVtbl->QueryInterface(This, riid, ppvObj)

#define IConnectionPointContainer_AddRef(This)   \
        (This)->lpVtbl->AddRef(This)

#define IConnectionPointContainer_Release(This)  \
        (This)->lpVtbl->Release(This)

	/* IConnectionPointContainer methods */
#define	IConnectionPointContainer_EnumConnectionPoints(This, ppEnum) \
       (This)->lpVtbl->EnumConnectionPoints(This, ppEnum) 

#define	IConnectionPointContainer_FindConnectionPoint(This, iid, ppCP) \
       (This)->lpVtbl->FindConnectionPoint(This, iid, ppCP)

#endif /* #ifndef IConnectionPointContainer_QueryInterface */


/*
 * IConnectionPoint interface C macros
 */

    /* IUnknown methods */
#ifndef IConnectionPoint_QueryInterface

#define IConnectionPoint_QueryInterface(This, riid,  ppvObj) \
       (This)->lpVtbl->QueryInterface(This, riid,  ppvObj)

#define IConnectionPoint_AddRef(This) \
       (This)->lpVtbl->AddRef(This)

#define	IConnectionPoint_Release(This) \
       (This)->lpVtbl->Release(This)

	/* IConnectionPoint methods */
#define	IConnectionPoint_GetConnectionInterface(This, pIID) \
       (This)->lpVtbl->GetConnectionInterface(This, pIID)

#define	IConnectionPoint_GetConnectionPointContainer(This, ppCPC) \
       (This)->lpVtbl->GetConnectionPointContainer(This, ppCPC)	

#define	IConnectionPoint_Advise(This, pUnkSink, pdwCookie) \
       (This)->lpVtbl->Advise(This, pUnkSink, pdwCookie)	

#define	IConnectionPoint_Unadvise(This,  dwCookie) \
       (This)->lpVtbl->Unadvise(This, dwCookie)

#define	IConnectionPoint_EnumConnections(This, ppEnum) \
       (This)->lpVtbl->EnumConnections(This, ppEnum)

#endif /* IConnectionPoint_QueryInterface */

/*
 * IPersistMemory interface C macros
 */
#ifndef IPersistMemory_QueryInterface

	/* IUnknown methods */
#define IPersistMemory_QueryInterface(This, riid, ppvObj) \
       (This)->lpVtbl->QueryInterface(This, riid, ppvObj)

#define IPersistMemory_AddRef(This) \
       (This)->lpVtbl->AddRef(This)

#define IPersistMemory_Release(This) \
       (This)->lpVtbl->Release(This) \

	/* IPersist methods */
#define IPersistMemory_GetClassID(This, lpClassID) \
       (This)->lpVtbl->GetClassID(This, lpClassID)

	/* IPersistMemory methods */
#define IPersistMemory_IsDirty(This) \
       (This)->lpVtbl->IsDirty(This)

#define IPersistMemory_Load(This,lpStream, cbSize) \
       (This)->lpVtbl->Load(This,lpStream, cbSize)

#define IPersistMemory_Save(This, lpStream, fClearDirty, cbSize) \
       (This)->lpVtbl->Save(This, lpStream, fClearDirty, cbSize)

#define IPersistMemory_GetSizeMax(This, pcbSize) \
       (This)->lpVtbl->GetSizeMax(This, pcbSize) 

#define IPersistMemory_InitNew(This) \
       (This)->lpVtbl->InitNew(This)
#endif /* IPersistMemory_QueryInterface */

/*
 * ISimpleFrameSite interface C macros
 */
#ifndef ISimpleFrameSite_QueryInterface

	/* IUnknown methods */
#define ISimpleFrameSite_QueryInterface(This, riid, ppvObj) \
       (This)->lpVtbl->QueryInterface(This, riid, ppvObj)

#define ISimpleFrameSite_AddRef(This) \
       (This)->lpVtbl->AddRef(This)

#define ISimpleFrameSite_Release(This) \
       (This)->lpVtbl->Release(This) \

#define ISimpleFrameSite_PreMessageFilter(This, hwnd, msg, wp, lp, lplResult, lpdwCookie) \
       (This)->lpVtbl->PreMessageFilter(This, hwnd, msg, wp, lp, lplResult, lpdwCookie)

#define ISimpleFrameSite_PostMessageFilter(This, hwnd, msg, wp, lp, lplResult, dwCookie) \
       (This)->lpVtbl->PostMessageFilter(This, hwnd, msg, wp, lp, lplResult, dwCookie)

#endif /* ISimpleFrameSite_QueryInterface */

/*
 * IClassFactory2 interface C macros
 */
#ifndef IClassFactory2_QueryInterface

#define IClassFactory2_QueryInterface(This,  riid, ppvObj) \
       (This)->lpVtbl->QueryInterface(This,  riid, ppvObj)

#define IClassFactory2_AddRef(This) \
       (This)->lpVtbl->AddRef(This)

#define IClassFactory2_Release(This) \
       (This)->lpVtbl->Release(This)

	/* IClassFactory methods */
#define IClassFactory2_CreateInstance(This, pUnkOuter, riid, ppvObject) \
       (This)->lpVtbl->CreateInstance(This, pUnkOuter, riid, ppvObject)

#define IClassFactory2_LockServer(This, fLock) \
       (This)->lpVtbl->LockServer(This, fLock)

	/*  IClassFactory2 methods */
#define IClassFactory2_GetLicInfo(This,  pLicInfo) \
       (This)->lpVtbl->GetLicInfo(This,  pLicInfo) 

#define IClassFactory2_RequestLicKey(This, dwResrved, pbstrKey) \
       (This)->lpVtbl->RequestLicKey(This, dwResrved, pbstrKey)

#define IClassFactory2_CreateInstanceLic(This, pUnkOuter, pUnkReserved, riid, bstrKey, ppvObject) \
       (This)->lpVtbl->CreateInstanceLic(This, pUnkOuter, pUnkReserved, riid, bstrKey, ppvObject)

#endif /* IClassFactory2_QueryInterface */

/*
 * IProvideClassInfo interface C macros
 */
#ifndef IProvideClassInfo_QueryInterface

	/* IUnknown methods */
#define IProvideClassInfo_QueryInterface(This,riid,ppvObject) \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProvideClassInfo_AddRef(This)  \
    (This)->lpVtbl -> AddRef(This)

#define IProvideClassInfo_Release(This) \
    (This)->lpVtbl -> Release(This)

	/* IProvideClassInfo methods */
#define IProvideClassInfo_GetClassInfo(This, ppTI) \
	(This)->lpVtbl -> GetClassInfo(This, ppTI)

#endif /* IProvideClassInfo_QueryInterface */

#endif /* OBJMACROS */

#endif  /* (vportOLE) */


#if (vportOLE)
#define voleIsSupported()  (vTRUE)
#else
#define voleIsSupported()  (vFALSE)
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE GLOBAL DEFINITIONS * * * * * * * * * *
 */
extern vmutex	_voleMutex;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */
#if (vportOLE)
#if (vportCPLUSPLUS_SOURCE)

#define _voleREF(iid) (iid)
#define _volePTR(riid) (&(riid))
#define _volePTR_FROM_REF(riid) (&(riid))
#define _voleREF_FROM_PTR(piid) (*(piid))

#define _voleREF_CLSID_NULL                          CLSID_NULL
#define _voleREF_IID_NULL                            IID_NULL
#define _voleREF_IID_IClassFactory2                  IID_IClassFactory2
#define _voleREF_IID_IClassFactory                   IID_IClassFactory
#define _voleREF_IID_IUnknown                        IID_IUnknown
#define _voleREF_IID_IProvideClassInfo               IID_IProvideClassInfo

#define _voleREF_IID_IAdviseSink                     IID_IAdviseSink
#define _voleREF_IID_IOleClientSite                  IID_IOleClientSite
#define _voleREF_IID_IOleInPlaceSite                 IID_IOleInPlaceSite
#define _voleREF_IID_IOleControlSite                 IID_IOleControlSite
#define _voleREF_IID_ISimpleFrameSite                IID_ISimpleFrameSite

#define _voleREF_IID_IDispatch                       IID_IDispatch
#define _voleREF_IID_IFontDisp                       IID_IFontDisp
#define _voleREF_IID_IFont                           IID_IFont

#define _voleREF_IID_IViewObject                     IID_IViewObject
#define _voleREF_IID_IViewObject2                    IID_IViewObject2
#define _voleREF_IID_IOleObject                      IID_IOleObject
#define _voleREF_IID_IOleInPlaceObject               IID_IOleInPlaceObject
#define _voleREF_IID_IOleControl                     IID_IOleControl
#define _voleREF_IID_IOleInPlaceUIWindow             IID_IOleInPlaceUIWindow
#define _voleREF_IID_IOleInPlaceFrame                IID_IOleInPlaceFrame
#define _voleREF_IID_IConnectionPointContainer       IID_IConnectionPointContainer
#define _voleREF_IID_IPropertyNotifySink             IID_IPropertyNotifySink

#define _voleREF_IID_IPersistMemory                  IID_IPersistMemory
#define _voleREF_IID_IPersistStreamInit              IID_IPersistStreamInit
#define _voleREF_IID_IPersistStorage                 IID_IPersistStorage

#else

#define _voleREF(iid) (&(iid))
#define _volePTR(riid) (riid)
#define _volePTR_FROM_REF(riid) (riid)
#define _voleREF_FROM_PTR(piid) (piid)

#define _voleREF_CLSID_NULL                          &CLSID_NULL
#define _voleREF_IID_NULL                            &IID_NULL
#define _voleREF_IID_IClassFactory2                  &IID_IClassFactory2
#define _voleREF_IID_IClassFactory                   &IID_IClassFactory
#define _voleREF_IID_IUnknown                        &IID_IUnknown
#define _voleREF_IID_IProvideClassInfo               &IID_IProvideClassInfo

#define _voleREF_IID_IAdviseSink                     &IID_IAdviseSink
#define _voleREF_IID_IOleClientSite                  &IID_IOleClientSite
#define _voleREF_IID_IOleInPlaceSite                 &IID_IOleInPlaceSite
#define _voleREF_IID_IOleControlSite                 &IID_IOleControlSite
#define _voleREF_IID_ISimpleFrameSite                &IID_ISimpleFrameSite

#define _voleREF_IID_IDispatch                       &IID_IDispatch
#define _voleREF_IID_IFontDisp                       &IID_IFontDisp
#define _voleREF_IID_IFont                           &IID_IFont

#define _voleREF_IID_IViewObject                     &IID_IViewObject
#define _voleREF_IID_IViewObject2                    &IID_IViewObject2
#define _voleREF_IID_IOleObject                      &IID_IOleObject
#define _voleREF_IID_IOleInPlaceObject               &IID_IOleInPlaceObject
#define _voleREF_IID_IOleControl                     &IID_IOleControl
#define _voleREF_IID_IOleInPlaceUIWindow             &IID_IOleInPlaceUIWindow
#define _voleREF_IID_IOleInPlaceFrame                &IID_IOleInPlaceFrame
#define _voleREF_IID_IConnectionPointContainer       &IID_IConnectionPointContainer
#define _voleREF_IID_IPropertyNotifySink             &IID_IPropertyNotifySink

#define _voleREF_IID_IPersistMemory                  &IID_IPersistMemory
#define _voleREF_IID_IPersistStreamInit              &IID_IPersistStreamInit
#define _voleREF_IID_IPersistStorage                 &IID_IPersistStorage

#endif
#endif

void _voleReportError(unsigned long code, char *errmsg);

#if (vportOLE)
LPFONTDISP _voleDispFromFont(vfont *font);
vfont *_voleFontFromDisp(LPFONTDISP pFontDisp);
OLE_COLOR _voleOleColorFromColor(vcolor *color);
vcolor  *_voleColorFromOleColor(OLE_COLOR clr);

int  _voleTransformWidthInHimetricToPixels (HDC,  int);
int  _voleTransformWidthInPixelsToHimetric (HDC,  int);
int  _voleTransformHeightInHimetricToPixels (HDC, int);
int  _voleTransformHeightInPixelsToHimetric (HDC, int);

void _voleTransformRectInPixelsToHimetric (HDC, LPRECT,  LPRECT);
void _voleTransformRectInHimetricToPixels (HDC, LPRECT,  LPRECT);
void _voleTransformSizeInPixelsToHimetric (HDC, LPSIZEL, LPSIZEL);
void _voleTransformSizeInHimetricToPixels (HDC, LPSIZEL, LPSIZEL);
#endif /* vportOLE */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef voleINCLUDED */
