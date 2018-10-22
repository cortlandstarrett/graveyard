/* $Id: micdas.c,v 1.6 1996/04/15 16:19:38 david Exp $ */

/************************************************************

    micdas.c
    C Implementation file for the MicroDraw sample DAS parts

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

/*----------------------------------------------------------------------------
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.
 *
 * Subject to the foregoing, you are permitted to copy, modify, and
 * distribute the Sample Code for any purpose and without fee,
 * provided that (i) a copyright notice in the form of "Copyright
 * 1992, 1993, 1994 Visix Software Inc., 11440 Commerce Park Drive,
 * Reston, VA 22091. All Rights Reserved" appears in all copies, (ii)
 * both the copyright notice and this permission notice appear in
 * supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

#include  <vport.h>
#include  "micdraw.h"

#if (mdrawUSE_DAS)

#ifndef  vservicechsrINCLUDED
#include  vservicechsrHEADER
#endif
#ifndef  vsessionINCLUDED
#include  vsessionHEADER
#endif
#ifndef vdasservINCLUDED
#include  vdasservHEADER
#endif
#ifndef  vclientINCLUDED
#include  vclientHEADER
#endif


enum {
    _mdrawSIG_ID_DELETE_TEXT,
    _mdrawSIG_ID_INSERT_TEXT,
    _mdrawSIG_ID_ADD_OBJECTS,
    _mdrawSIG_ID_HIDE_OBJECTS,
    _mdrawSIG_ID_MOVE_OBJECTS,
    _mdrawSIG_ID_REMOVE_OBJECTS,
    _mdrawSIG_ID_UPDATE_OBJECTS,
    _mdrawSIG_ID_LAYER_OBJECT,
    _mdrawNUM_SIGS
};

/**  These types arent complete because this is just a sketch.
 **
 **  It would be better to send a vmdrawObject as a resource and use
 **  the same code for storing a document.  (For now we'll just send
 **  the objects as compounds.)
 **
 **  If this were done, I would try to give the compound datatag a
 **  scrap class that sent the resource as an implementation detail.
 **  This way SetArgs and GetArgs would operate on vmdrawObject, and
 **  not vres.  the only problem here is that vdomain doesn't let
 **  vdomainObject free stand.  they have to be in a domain, so i'm
 **  not sure how that would completely work...
 **/
typedef struct {
    vbyte		valid;
    unsigned int	red, green, blue;
} _mdrawRGBColor;


typedef struct {
    short		pat[vmdrawMAX_PENPAT_SIZE];
    vbyte		size;
    vbyte		arrows;
    vbyte		thickness;
    _mdrawRGBColor	color;
} _mdrawPen;


typedef struct {
    unsigned int	type;
    unsigned int	id;
    _mdrawPen		pen;
    vrect		rect;
    vstr		*sText;
    short		startCorner;
} _mdrawObject;
    

static vservice  		 *_servicePrivate = NULL;
static vsignature		  _arraySignatures[_mdrawNUM_SIGS];
static vdatatag			 *_datatagRect;
static vdatatag			 *_datatagRGBColor;
static vdatatag			 *_datatagPen;
static vdatatag			 *_datatagObject;
static vdatatag			 *_datatagArrayObjects;
static vdatatag			 *_datatagPenPat;
static vdatatag			 *_datatagArrayIDs;


static vdomainObserverClass	 *_classObserverDomain	= NULL;
static vtextObserverClass	 *_classObserverText	= NULL;
static vservicechsr		 *_chooserService	= NULL;
static const char  		 *_literalServiceTitle	= "Collaborative Draw";
static int	     		  _bInitialized		= FALSE;



static void  _mdrawUpdateObjects(
	vmdrawDocument		*document,
	vdomainObjectSet	*set
	);

static void  _mdrawAddObjects(
	vmdrawDocument		*document,
	vdomainObjectSet	*set
	);


/*===========================================================================*\
 * * * * * * * * * * * * * *    TEXT OBSERVER    * * * * * * * * * * * * * * *
\*===========================================================================*/
static void  _mdrawTextObserveInsert(
    vtextObserver	*observer,
    long		 pos,
    long		 delta
    )
{
    vdomainObject	*obj;
    vmdrawObjectData	*data;
    vchar		*buf;
    vsessionStatement	*statement;
    vmdrawDocument	*document;

    document = (vmdrawDocument *)vtextGetObserverData(observer);
    obj = document->editingObject;
    data = vdomainGetObjectData(vdomainviewGetDomain(document->domainView),
				obj);
    buf = vmemAlloc((delta + 1) * sizeof(vchar));
    vtextGetTextRange(data->text, pos, pos + delta, buf, delta);
    buf[delta] = vcharNULL;

    statement = vsessionCreateStatement();
    vsessionSetStatementSession(statement, document->session);
    vsessionSetStatementSignature(statement,
				  &_arraySignatures[_mdrawSIG_ID_INSERT_TEXT]);
    vsessionSetStatementArgs(statement, data->id, (int)pos, buf);
    vsessionSetDestroyStatementWhenFinished(statement, TRUE);
    vsessionSendStatement(statement);

    vmemFree(buf);
}  /**  end  _mdrawTextObserveInsert  **/


static void  _mdrawTextObserveDelete(
    vtextObserver	*observer,
    long		 pos,
    long		 delta
    )
{
    vmdrawDocument	*document;
    vdomainObject	*obj;
    vmdrawObjectData	*data;
    vsessionStatement	*statement;
    
    document = (vmdrawDocument *)vtextGetObserverData(observer);
    obj = document->editingObject;
    data = vdomainGetObjectData(vdomainviewGetDomain(document->domainView),
				obj);
    
    statement = vsessionCreateStatement();
    vsessionSetStatementSession(statement, document->session);
    vsessionSetStatementSignature(statement,
				  &_arraySignatures[_mdrawSIG_ID_DELETE_TEXT]);
    vsessionSetStatementArgs(statement, data->id, (int)pos, (int)delta);
    vsessionSetDestroyStatementWhenFinished(statement, TRUE);
    vsessionSendStatement(statement);
}  /**  end  _mdrawTextObserveDelete  **/



/*===========================================================================*\
 * * * * * * * * * * * * * *    DOMAIN OBSERVER    * * * * * * * * * * * * * *
\*===========================================================================*/
static void _mdrawObserveAdd(
    vdomainObserver	*observer,
    vdomainObject	*obj
    )
{
    /* data isnt set yet, so this method isnt interesting
     * will add object in hide observer
     */
}  /**  end  _mdrawObserveAdd  **/



/*---------------------------------------------------------------------------*\
    static void  _mdrawObserveHide
\*---------------------------------------------------------------------------*/
static void _mdrawObserveHide(
    vdomainObserver	*observer,
    vdomainObjectSet	*set,
    int			 hide
    )
{
    vdomainObjectSetIterator	 iterator;
    vdomainObject		*obj;
    vmdrawObjectData		*data;
    vdomain			*domain;
    int				  nArray = 0;
    unsigned int		 *array;
    vsessionStatement		 *statement;
    vmdrawDocument		 *document;
    
    array = vmemAlloc(vdomainGetObjectSetCount(set) * sizeof(unsigned int));
    nArray = 0;

    vdomainInitObjectSetIterator(&iterator, set);
    domain = vdomainGetObserverOwner(observer);
    document = (vmdrawDocument *)vdomainGetData(domain);
   
    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	if (vdictLoad(document->dictObjectMap, (const vname *)data->id)) {
	    array[nArray++] = data->id;
	}
	else {
	    vdomainObjectSet	*setTemp;

	    setTemp = vdomainCreateObjectSet(obj);  /* TVL */
	    _mdrawAddObjects(document, setTemp);
	    vdictStore(document->dictObjectMap, (const vname *)data->id, obj);
	    vdomainDestroyObjectSet(setTemp);
	}
    }
    vdomainDestroyObjectSetIterator(&iterator);

    if (nArray > 0) {
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, document->session);
	vsessionSetStatementSignature(statement,
				 &_arraySignatures[_mdrawSIG_ID_HIDE_OBJECTS]);
	vsessionSetStatementArgs(statement, nArray, array, hide);
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSendStatement(statement);
    }
    vmemFree(array);
}  /**  end  _mdrawObserveHide  **/



static void _mdrawObserveLayer(
    vdomainObserver	*observer,
    vdomainObject	*obj,
    vdomainObject	*wasBehind
    )
{
    vdomainObject		*objFront;
    vmdrawObjectData		*data, *dataFront;
    unsigned int		 objFrontId;
    vsessionStatement		*statement;
    vmdrawDocument		*document;
    vdomain			*domain;

    domain = vdomainGetObserverOwner(observer);
    document = (vmdrawDocument *)vdomainGetData(domain);
    data = vdomainGetObjectData(domain, obj);
    
    if (objFront = vdomainNextObjectInFront(obj)) {
	dataFront = vdomainGetObjectData(domain, objFront);
	objFrontId = dataFront->id;
    } else
      objFrontId = 0;
    
    statement = vsessionCreateStatement();
    vsessionSetStatementSession(statement, document->session);
    vsessionSetStatementSignature(statement,
			  &_arraySignatures[_mdrawSIG_ID_LAYER_OBJECT]);
    vsessionSetStatementArgs(statement, data->id, objFrontId);
    vsessionSetDestroyStatementWhenFinished(statement, TRUE);
    vsessionSendStatement(statement);

}  /**  end  _mdrawObserveLayer  **/



static void _mdrawObserveMove(
    vdomainObserver	*observer,
    vdomainObjectSet	*set,
    vpoint		*delta,
    int 		 positioning,
    int			 before
    )
{
    vdomainObjectSetIterator	 iterator;
    vdomainObject		*obj;
    vmdrawObjectData		*data;
    vdomain			*domain;
    unsigned int		*array;
    int				 nArray;
    vsessionStatement		*statement;
    vmdrawDocument		*document;

    if (before)
	return;

    array = vmemAlloc(vdomainGetObjectSetCount(set) * sizeof(unsigned int));
    nArray = 0;

    vdomainInitObjectSetIterator(&iterator, set);
    domain = vdomainGetObserverOwner(observer);
    document = (vmdrawDocument *)vdomainGetData(domain);

    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	array[nArray++] = data->id;
    }
    vdomainDestroyObjectSetIterator(&iterator);
    if (nArray > 0) {
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, document->session);
	vsessionSetStatementSignature(statement,
				 &_arraySignatures[_mdrawSIG_ID_MOVE_OBJECTS]);
	vsessionSetStatementArgs(statement,
				 nArray, array,
				 (int)delta->x, (int)delta->y, positioning);
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSendStatement(statement);
    }
    vmemFree(array);
}  /**  end  _mdrawObserveMove  **/



static void _mdrawObserveRemove(
    vdomainObserver	*observer,
    vdomainObjectSet	*set
    )
{
    vdomainObjectSetIterator	 iterator;
    vdomainObject		*obj;
    vmdrawObjectData		*data;
    vdomain			*domain;
    unsigned int		*array;
    int				 nArray;
    vsessionStatement		*statement;
    vmdrawDocument		*document;
    
    array = vmemAlloc(vdomainGetObjectSetCount(set) * sizeof(unsigned int));
    nArray = 0;

    vdomainInitObjectSetIterator(&iterator, set);
    domain = vdomainGetObserverOwner(observer);
    document = (vmdrawDocument *)vdomainGetData(domain);

    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	array[nArray++] = data->id;
	if (vdictLoad(document->dictObjectMap, (const vname *)data->id))
	    vdictRemove(document->dictObjectMap, (const vname *)data->id);
    }
    vdomainDestroyObjectSetIterator(&iterator);
    if (nArray > 0) {
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, document->session);
	vsessionSetStatementSignature(statement,
			 &_arraySignatures[_mdrawSIG_ID_REMOVE_OBJECTS]);
	vsessionSetStatementArgs(statement, nArray, array);
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSendStatement(statement);
    }
    vmemFree(array);
}  /**  end  _mdrawObserveRemove  **/



static void _mdrawObserveResize(
    vdomainObserver	*observer,
    vdomainObjectSet	*set,
    int			 before
    )
{
    vdomain		*domain;
    vmdrawDocument	*document;

    if (!before) {
	domain = vdomainGetObserverOwner(observer);
	document = (vmdrawDocument *)vdomainGetData(domain);

	_mdrawUpdateObjects(document, set);
    }
}  /**  end  _mdrawObserveResize  **/



/*===========================================================================*\
 * * * * * * * * * * * * * * * *    MISC  FUNCTIONS    * * * * * * * * * * * *
\*===========================================================================*/
#if  (vmemBALANCE)
static void  _mdrawDASShutdown(void)
{
    vsignature	*sig;

    if (_chooserService != NULL)
	vservicechsrDestroy(_chooserService);
    if (_servicePrivate != NULL)
	vserviceDestroy(_servicePrivate);

    sig = &_arraySignatures[_mdrawNUM_SIGS];
    while (--sig >= _arraySignatures)
	vsignatureDestroy(sig);
    vdatatagDestroy(_datatagRect);
    vdatatagDestroy(_datatagArrayIDs);
    vdatatagDestroy(_datatagArrayObjects);
    vdatatagDestroy(_datatagPenPat);
    vdatatagDestroy(_datatagObject);
    vdatatagDestroy(_datatagPen);
    vdatatagDestroy(_datatagRGBColor);
}
#endif


static void  _mdrawDASStartup(void)
{
    vsignature	*sig;
    vdatatag	*dtagShort, *dtagInt, *dtagUInt, *dtagByte;

    _classObserverDomain = vclassSpawn(vdomainGetDefaultObserverClass(),
				 sizeof(vdomainObserverClass));
    vclassSetNameScribed(_classObserverDomain,
			 vcharScribeLiteral("vmdrawCollaborativeObserverD"));
    vclassSet(_classObserverDomain, vdomainObserverADD,	  _mdrawObserveAdd);
    vclassSet(_classObserverDomain, vdomainObserverHIDE,  _mdrawObserveHide);
    vclassSet(_classObserverDomain, vdomainObserverLAYER, _mdrawObserveLayer);
    vclassSet(_classObserverDomain, vdomainObserverMOVE,  _mdrawObserveMove);
    vclassSet(_classObserverDomain, vdomainObserverREMOVE,_mdrawObserveRemove);
    vclassSet(_classObserverDomain, vdomainObserverRESIZE,_mdrawObserveResize);

    _classObserverText = vclassSpawn(vtextGetDefaultObserverClass(),
				     sizeof(vtextObserverClass));
    vclassSetNameScribed(_classObserverText,
			 vcharScribeLiteral("vmdrawCollaborativeObserverT"));
    vclassSet(_classObserverText, vtextObserverINSERT,_mdrawTextObserveInsert);
    vclassSet(_classObserverText, vtextObserverDELETE,_mdrawTextObserveDelete);


    dtagShort = vdatatagGetShort();
    dtagInt = vdatatagGetInteger();
    dtagUInt = vdatatagGetUnsignedInteger();
    dtagByte = vdatatagGetUnsignedByte();

    _datatagPenPat = vdatatagCreateSizedArray();
    vdatatagSetSizedArrayCount(_datatagPenPat, vmdrawMAX_PENPAT_SIZE);
    vdatatagSetSizedArrayDatatag(_datatagPenPat, dtagShort);

    
    _datatagArrayIDs = vdatatagCreateArray();
    vdatatagSetArrayDatatag(_datatagArrayIDs, dtagUInt);

    _datatagRect = vdatatagCreateCompound(); /* vrect */
    vdatatagConstructCompound(_datatagRect, dtagShort, dtagShort,
			      dtagShort, dtagShort, NULL);

    _datatagRGBColor = vdatatagCreateCompound(); /* _mdrawRGBColor */
    vdatatagConstructCompound(_datatagRGBColor,
			      dtagByte,
			      dtagUInt,
			      dtagUInt,
			      dtagUInt,
			      NULL);

    _datatagPen = vdatatagCreateCompound(); /* _mdrawPen */
    vdatatagConstructCompound(_datatagPen,
			      _datatagPenPat, /* pat */
			      dtagByte,	/* size */
			      dtagByte, /* arrows */
			      dtagByte, /* thickness */
			      _datatagRGBColor, /* color */
			      NULL);


    _datatagObject = vdatatagCreateCompound(); /* _mdrawObject */
    vdatatagConstructCompound(_datatagObject,
			      vdatatagGetUnsignedInteger(),  /* type */
			      vdatatagGetUnsignedInteger(),  /* id */
			      _datatagPen,
			      _datatagRect,
			      vdatatagGetString(),
			      dtagShort,
			      NULL);

    _datatagArrayObjects = vdatatagCreateArray();
    vdatatagSetArrayDatatag(_datatagArrayObjects, _datatagObject);

    sig = &_arraySignatures[_mdrawNUM_SIGS];
    while (--sig >= _arraySignatures)
	vsignatureInit(sig);


    sig = &_arraySignatures[_mdrawSIG_ID_INSERT_TEXT];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("InsertText"));
    vsignatureConstructArgs(sig,
			    vdatatagGetUnsignedInteger(),
			    vdatatagGetInteger(),
			    vdatatagGetString(),
			    NULL);
    
    sig = &_arraySignatures[_mdrawSIG_ID_DELETE_TEXT];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("DeleteText"));
    vsignatureConstructArgs(sig,
			    vdatatagGetUnsignedInteger(),
			    vdatatagGetInteger(),
			    vdatatagGetInteger(),
			    NULL);
    

    sig = &_arraySignatures[_mdrawSIG_ID_ADD_OBJECTS];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("AddObjects"));
    vsignatureConstructArgs(sig, _datatagArrayObjects, NULL);
    
    sig = &_arraySignatures[_mdrawSIG_ID_HIDE_OBJECTS];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("HideObjects"));
    vsignatureConstructArgs(sig, _datatagArrayIDs, dtagInt, NULL);

    sig = &_arraySignatures[_mdrawSIG_ID_MOVE_OBJECTS];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("MoveObjects"));
    vsignatureConstructArgs(sig, _datatagArrayIDs,
			    dtagInt, dtagInt, dtagInt,
			    NULL);

    sig = &_arraySignatures[_mdrawSIG_ID_REMOVE_OBJECTS];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("RemoveObjects"));
    vsignatureConstructArgs(sig, _datatagArrayIDs, NULL);

    sig = &_arraySignatures[_mdrawSIG_ID_UPDATE_OBJECTS];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("UpdateObjects"));
    vsignatureConstructArgs(sig, _datatagArrayObjects, NULL);
 
    sig = &_arraySignatures[_mdrawSIG_ID_LAYER_OBJECT];
    vsignatureSetTag(sig, vnameInternGlobalLiteral("LayerObject"));
    vsignatureConstructArgs(sig,
			    dtagUInt, /* obj to update */
			    dtagUInt, /* obj infront */
			    NULL);
    
#if (vmemBALANCE)
    vclientRegisterShutdown(_mdrawDASShutdown);
#endif
    _bInitialized = TRUE;
}  /**  end  _mdrawDASStartup  **/


static unsigned long _mdrawHashIdentity(const void *p)
{
    return  (unsigned long)p;
}



/*---------------------------------------------------------------------------*\
    static void  _mdrawInitDocumentSession
\*---------------------------------------------------------------------------*/
static void  _mdrawInitDocumentSession(
    vmdrawDocument	*document,
    vsession		*session
    )
{
    vdomain			*domain;
    vdomainSelection		 sel;
    vdomainObjectSet		*set;
    vdomainObjectSetIterator	 iterator;
    vdomainObject		*obj;
    vmdrawObjectData		*data;
    
    domain = vdomainviewGetDomain(document->domainView);

    document->session = session;
    document->observerSessionDomain =
	vdomainCreateObserverOfClass(_classObserverDomain);
    vdomainSetObserverData(document->observerSessionDomain, document);
    vdomainInstallObserver(domain,  document->observerSessionDomain);

    document->observerSessionText =
	vtextCreateObserverOfClass(_classObserverText);
    vtextSetObserverData(document->observerSessionText, document);
    if (document->editingObject != NULL) {
	vmdrawObjectData	*data;
	data = vdomainGetObjectData(vdomainviewGetDomain(document->domainView),
				    document->editingObject);
	vtextInstallObserver(data->text,  document->observerSessionText);
    }

    document->dictObjectMap = vdictCreate(_mdrawHashIdentity);

    sel = vdomainCreateSelection(domain);
    set = vdomainGetObjectSet(domain, sel, vdomainALL, NULL);
    vdomainInitObjectSetIterator(&iterator, set);
    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	vdictStore(document->dictObjectMap, (void *)data->id, obj);
    }
    vdomainDestroyObjectSetIterator(&iterator);
    vdomainDestroyObjectSet(set);
    vdomainDestroySelection(domain, sel);
    
}  /**  end  _mdrawInitDocumentSession  **/


/*---------------------------------------------------------------------------*\
    static void  _mdrawUninitDocumentSession
\*---------------------------------------------------------------------------*/
static void  _mdrawUninitDocumentSession(
    vmdrawDocument	*document,
    vsession		*session
    )
{
    vdomain	*domain;

    domain = vdomainviewGetDomain(document->domainView);

    document->session = NULL;

    vdomainUninstallObserver(domain, document->observerSessionDomain);
    vdomainDestroyObserver(document->observerSessionDomain);
    document->observerSessionDomain = NULL;

    if (document->editingObject != NULL) {
	vmdrawObjectData	*data;
	data = vdomainGetObjectData(vdomainviewGetDomain(document->domainView),
				    document->editingObject);
	vtextUninstallObserver(data->text, document->observerSessionText);
    }
    vtextDestroyObserver(document->observerSessionText);
    document->observerSessionText = NULL;

    vdictDestroy(document->dictObjectMap);
    document->dictObjectMap = NULL;
}  /**  end  _mdrawUninitDocumentSession  **/


static void  _mdrawProviderSessionNotify(vsession *session,
					 vsessionEvent *event)
{
    vmdrawDocument	*document;
    vdomain		*domain;
    vdomainObjectSet	*set;
    vdomainSelection	 sel;
	
    document = (vmdrawDocument *)vsessionGetData(session);
    switch (vsessionGetEventCode(event)) {
	case  vsessionEVENT_BEGIN:
	   domain = vdomainviewGetDomain(document->domainView);
	   _mdrawInitDocumentSession(document, session);
	   sel = vdomainCreateSelection(domain);
	   set = vdomainGetObjectSet(domain, sel, vdomainALL, NULL);
	   _mdrawAddObjects(document, set);
	   mdrawUnregisterDocument(document);
	   vdomainDestroyObjectSet(set);
	   vdomainDestroySelection(domain, sel);
	   break;

	case  vsessionEVENT_END:
	   _mdrawUninitDocumentSession(document, session);
	   mdrawRegisterDocument(document);
	   break;

	case  vsessionEVENT_CANNOT_BEGIN:
	default:
	    break;
    }
}  /**  end  _mdrawProviderSessionNotify  **/


static void  _mdrawUpdateObjects(
    vmdrawDocument	*document,
    vdomainObjectSet	*set
    )
{
    vdomainObjectSetIterator	 iterator;
    vsessionStatement		*statement;
    vmdrawObjectData		*data;
    vdomain			*domain;
    vdomainObject		*obj;
    int				  nArray = 0;
    _mdrawObject		*array;

    if (document->session == NULL)
	return;

    array = vmemAlloc(vdomainGetObjectSetCount(set) * sizeof(_mdrawObject));
    nArray = 0;

    domain = vdomainviewGetDomain(document->domainView);
    vdomainInitObjectSetIterator(&iterator, set);
    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	if ((data->id != 0)
	    &&(vdictLoad(document->dictObjectMap, (const vname *)data->id))) {
	    _mdrawObject	*elem = &array[nArray++];
	    
	    elem->id = data->id;
	    elem->type = vdomainGetObjectType(domain, obj);
	    elem->pen.size = data->pen.size;
	    elem->pen.arrows = data->pen.arrows;
	    elem->pen.thickness = data->pen.thickness;
	    if (data->pen.color) {
		elem->pen.color.valid = TRUE;
		elem->pen.color.red =
		  vcolorGetSpecRGBRed(vcolorGetSpec(data->pen.color));
		elem->pen.color.green =
		  vcolorGetSpecRGBGreen(vcolorGetSpec(data->pen.color));
		elem->pen.color.blue =
		  vcolorGetSpecRGBBlue(vcolorGetSpec(data->pen.color));
	    } else
		elem->pen.color.valid = FALSE;

	    elem->rect = *vdomainGetObjectBounds(domain, obj);
	    (void)vmemCopy(data->pen.pat, elem->pen.pat,sizeof(data->pen.pat));
	    if (data->text != NULL) {
		long length = vtextLength(data->text);
		elem->sText = vstrCreateSized((size_t)length);
		vtextGetTextRange(data->text, 0, length, elem->sText, length);
	    }
	    else
		elem->sText = vstrCloneScribed(vcharScribeLiteral(""));
	    elem->startCorner = data->startCorner;
	}
    }  /**  end iterating  **/
    vdomainDestroyObjectSetIterator(&iterator);

    if (nArray > 0) { 
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, document->session);
	vsessionSetStatementSignature(statement,
			&_arraySignatures[_mdrawSIG_ID_UPDATE_OBJECTS]);
	vsessionSetStatementArgs(statement, nArray, array);
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSendStatement(statement);
	while (--nArray >= 0)
	    if (array[nArray].sText != NULL)
		vstrDestroy(array[nArray].sText);
    }
    vmemFree(array);
}  /**  end  _mdrawUpdateObjects  **/



/*---------------------------------------------------------------------------*\
    static void  _mdrawAddObjects
\*---------------------------------------------------------------------------*/
static void
_mdrawAddObjects(
    vmdrawDocument	*document,
    vdomainObjectSet	*set
    )
{
    int				 nArray;
    vdomainObjectSetIterator	 iterator;
    _mdrawObject		*array, *elem;
    vsessionStatement		*statement;
    vdomainObject		*obj;
    vmdrawObjectData		*data;
    vdomain			*domain;
    
    array = vmemAlloc(vdomainGetObjectSetCount(set) * sizeof(_mdrawObject));
    nArray = 0;

    vdomainInitObjectSetIterator(&iterator, set);
    domain = vdomainviewGetDomain(document->domainView);

    while (vdomainNextObjectSetIterator(&iterator)) {
	obj = vdomainGetObjectSetIteratorObject(&iterator);
	data = vdomainGetObjectData(domain, obj);
	elem = &array[nArray++];
	elem->id = data->id;
	elem->type = vdomainGetObjectType(domain, obj);
	vrectInset(vdomainGetObjectBounds(domain, obj),
		   vmdrawJOINT_SIZE, vmdrawJOINT_SIZE,
		   &elem->rect);
	(void)vmemCopy(data->pen.pat, elem->pen.pat,sizeof(data->pen.pat));
	elem->pen.size = data->pen.size;
	elem->pen.arrows = data->pen.arrows;
	elem->pen.thickness = data->pen.thickness;
	if (data->pen.color) {
	    elem->pen.color.valid = TRUE;
	    elem->pen.color.red =
	      vcolorGetSpecRGBRed(vcolorGetSpec(data->pen.color));
	    elem->pen.color.green =
	      vcolorGetSpecRGBGreen(vcolorGetSpec(data->pen.color));
	    elem->pen.color.blue =
	      vcolorGetSpecRGBBlue(vcolorGetSpec(data->pen.color));
	} else
	  elem->pen.color.valid = FALSE;

	if (data->text != NULL) {
	    long	length = vtextLength(data->text);
	    elem->sText = vstrCreateSized((size_t)length);
	    vtextGetTextRange(data->text, 0, length, elem->sText, length);
	}
	else
	    elem->sText = vstrCloneScribed(vcharScribeLiteral(""));
	elem->startCorner = data->startCorner;
    }
    vdomainDestroyObjectSetIterator(&iterator);
    if (nArray > 0) {
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, document->session);
	vsessionSetStatementSignature(statement,
			      &_arraySignatures[_mdrawSIG_ID_ADD_OBJECTS]);
	vsessionSetStatementArgs(statement, nArray, array);
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSendStatement(statement);

	while (--nArray >= 0)
	    if (array[nArray].sText != NULL)
		vstrDestroy(array[nArray].sText);
    }
    vmemFree(array);
}  /**  end  _mdrawAddObjects  **/




/*===========================================================================*\
 * * * * * * * * * * * * * *   PRIMITIVE  HANDLERS   * * * * * * * * * * * * *
\*===========================================================================*/
/*---------------------------------------------------------------------------*\
    static vscrap *_mdrawDeleteTextPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawDeleteTextPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    unsigned int	id;
    int			pos, delta;
    vmdrawDocument	*document;
    vdomain		*domain;
    vdomainObject	*obj;
    vmdrawObjectData	*data;
    vtext		*text;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &id, &pos, &delta);

    document = (vmdrawDocument *)vsessionGetData(session);
    if ((obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)id)) != NULL) {
	domain = vdomainviewGetDomain(document->domainView);
	data = vdomainGetObjectData(domain, obj);
	if ((text = data->text) != NULL) {
	    vtextSelection *sel;
	    if (document->editingObject == obj)
		vtextDisableObserver(document->observerSessionText);
	    sel = vtextCreateSelection(text);
	    vtextSelectRange(text, sel, pos, pos + delta);
	    vtextDelete(text, sel);
	    vtextDestroySelection(text, sel);
	    vdomainviewInvalObjects(document->domainView,
				    vdomainObjectToSet(obj),
				    vwindowINVAL_IMMEDIATE);
	    if (document->editingObject == obj)
		vtextEnableObserver(document->observerSessionText);
	}
    }

    return  NULL;
}  /**  end  _mdrawDeleteTextPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap *_mdrawInsertTextPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawInsertTextPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    unsigned int	id;
    int			pos;
    vmdrawDocument	*document;
    vdomain		*domain;
    vstr		*s;
    vdomainObject	*obj;
    vmdrawObjectData	*data;
    vtext		*text;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &id, &pos, &s);

    document = (vmdrawDocument *)vsessionGetData(session);
    if ((obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)id)) != NULL) {
	vtextSelection *sel;

	domain = vdomainviewGetDomain(document->domainView);
	data = vdomainGetObjectData(domain, obj);
	if ((text = data->text) != NULL) {
	    sel = vtextCreateSelection(text);
	}
	else {
	    pos = 0;
	    vmdrawCreateTextObject(data);
	    text = data->text;
	    sel = vtextCreateSelection(text);
	}
	if (document->editingObject == obj)
	    vtextDisableObserver(document->observerSessionText);
	vtextSelectRange(text, sel, pos, pos);
	vtextInsert(text, sel, s, vcharLength(s));
	vdomainviewInvalObjects(document->domainView,
				vdomainObjectToSet(obj),
				vwindowINVAL_IMMEDIATE);
	vtextDestroySelection(text, sel);
	if (document->editingObject == obj)
	    vtextEnableObserver(document->observerSessionText);
    }
    if (s != NULL)
	vstrDestroy(s);
    return  NULL;
}  /**  end  _mdrawInsertTextPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawAddObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawAddObjectsPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    _mdrawObject	*array, *elem;
    int			 i, nArray;
    vdomain		*domain;
    vmdrawDocument	*document;
    vmdrawObjectData	*data;
    vdomainObject	*obj;
    vdomainObjectSet	*set;
    
    vserviceGetPrimitiveArgs(prim, scrapArgs, &nArray, &array);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);
    set = NULL;

    vdomainDisableObserver(document->observerSessionDomain);

    for (i = nArray - 1; i >= 0; i--) {
	_mdrawPen	*pen;
	
	elem = &array[i];
	pen = &elem->pen;
	obj = vmdrawAddObject(document, &elem->rect, elem->type, elem->id);
	vdomainUnselectObjects(domain,
			       vdomainviewGetSelection(document->domainView),
			       vdomainObjectToSet(obj));
	data = vdomainGetObjectData(domain, obj);
	(void)vmemCopy(elem->pen.pat, data->pen.pat, sizeof(data->pen.pat));
	data->pen.size = pen->size;
	data->pen.arrows = pen->arrows;
	data->pen.thickness = pen->thickness;
	if (pen->color.valid) {
	    vcolorSpec	*spec;
	    
	    spec = vcolorCreateSpec();
	    vcolorSetSpecRGB(spec, pen->color.red, pen->color.green,
			     pen->color.blue);
	    data->pen.color = vcolorInternSpec(spec);
	    vcolorDestroySpec(spec);
	} else
	  data->pen.color = NULL;

	if (elem->sText != NULL) {
	    vtextSelection	sel;
	    vstr		*s = elem->sText;
	    vtext		*text = data->text; 

	    if ((text != NULL) || (s[0] != vcharNULL)) {
		if (text == NULL) {
		    vmdrawCreateTextObject(data);
		    text = data->text;
		}
		vtextInitSelection(text, &sel);
		vtextSelectRange(text, &sel, 0, vtextLength(text));
		vtextInsert(text, &sel, s, vcharLength(s));
		vtextDestroySelection(text, &sel);
	    }
	    vstrDestroy(s);
	}
	data->startCorner = elem->startCorner;

	vdictStore(document->dictObjectMap,(const vname *)elem->id, obj);
	if (set == NULL)
	    set = vdomainCreateObjectSet(obj);
	else
	    vdomainAddToObjectSet(&set, obj);

    }
    
    if (set) {
	vdomainviewInvalObjects(document->domainView,
				set, vwindowINVAL_IMMEDIATE);
	vdomainDestroyObjectSet(set);
    }

    vdomainEnableObserver(document->observerSessionDomain);

    if (array != NULL)
	vmemFree(array);
    
    return  NULL;
}  /**  end  _mdrawAddObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawHideObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawHideObjectsPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    int			 bHide;
    int			 nArray;
    unsigned int	*array;
    vdomain		*domain;
    vmdrawDocument	*document;
    vdomainObject	*obj;
    vdomainObjectSet	*set;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &nArray, &array, &bHide);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);
    set = NULL;

    while (--nArray >= 0) {
	obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)array[nArray]);
	if (obj != NULL) {
	    if (set == NULL)
		set = vdomainCreateObjectSet(obj);
	    else
		vdomainAddToObjectSet(&set, obj);
	}
    }

    if (set) {
	
	vdomainDisableObserver(document->observerSessionDomain);
	
	if (bHide)
	  vdomainHideObjects(domain, set);
	else
	  vdomainShowObjects(domain, set);
	
	vdomainEnableObserver(document->observerSessionDomain);
	
    }

    if (array != NULL)
	vmemFree(array);
    return  NULL;
}  /**  end  _mdrawHideObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawMoveObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawMoveObjectsPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    int			 positioning;
    int			 dx, dy;
    int			 nArray;
    unsigned int	*array;
    vdomain		*domain;
    vmdrawDocument	*document;
    vdomainObject	*obj;
    vdomainObjectSet	*set;

    vserviceGetPrimitiveArgs(prim, scrapArgs,
			     &nArray, &array, &dx, &dy, &positioning);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);
    set = NULL;

    while (--nArray >= 0) {
	obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)array[nArray]);
	if (obj != NULL) {
	    if (set == NULL)
		set = vdomainCreateObjectSet(obj);
	    else
		vdomainAddToObjectSet(&set, obj);
	}
    }

    if (set) {
	vdomainDisableObserver(document->observerSessionDomain);
	vdomainMoveObjects(domain, set, dx, dy, positioning);
	vdomainDestroyObjectSet(set);
	vdomainEnableObserver(document->observerSessionDomain);
    }
    
    if (array != NULL)
	vmemFree(array);
    return  NULL;
}  /**  end  _mdrawMoveObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawRemoveObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawRemoveObjectsPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    int			 nArray;
    unsigned int	*array;
    vdomain		*domain;
    vmdrawDocument	*document;
    vdomainObject	*obj;
    vdomainObjectSet	*set;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &nArray, &array);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);
    set = NULL;

    while (--nArray >= 0) {
	obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)array[nArray]);
	if (obj != NULL) {
	    vdictRemove(document->dictObjectMap, (const vname *)array[nArray]);
	    if (set == NULL)
		set = vdomainCreateObjectSet(obj);
	    else
		vdomainAddToObjectSet(&set, obj);
	}
    }

    if (set) {
	vdomainDisableObserver(document->observerSessionDomain);
	vdomainRemoveObjects(domain, set);
	vdomainDestroyObjectSet(set);
	vdomainEnableObserver(document->observerSessionDomain);
    }

    if (array != NULL)
	vmemFree(array);
    return  NULL;
}  /**  end  _mdrawRemoveObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawUpdateObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawUpdateObjectsPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    _mdrawObject	*array;
    _mdrawPen		*pen;
    int			 nArray;
    vdomain		*domain;
    vmdrawObjectData	*data;
    vmdrawDocument	*document;
    vdomainObject	*obj;
    vdomainObjectSet	*set, *setTemp;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &nArray, &array);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);
    set = NULL;

    vdomainDisableObserver(document->observerSessionDomain);
    while (--nArray >= 0) {
	obj = (vdomainObject *)vdictLoad(document->dictObjectMap,
					 (const vname *)array[nArray].id);
	if (obj != NULL) {
	    if (set == NULL)
		set = vdomainCreateObjectSet(obj);
	    else
		vdomainAddToObjectSet(&set, obj);

	    data = vdomainGetObjectData(domain, obj);
	    pen = &array[nArray].pen;
	    (void)vmemCopy(pen->pat, data->pen.pat, sizeof(data->pen.pat));
	    data->pen.size = pen->size;
	    data->pen.thickness = pen->thickness;
	    data->pen.arrows = pen->arrows;
	    if (pen->color.valid) {
		vcolorSpec	*spec;
		
		spec = vcolorCreateSpec();
		vcolorSetSpecRGB(spec, pen->color.red, pen->color.green,
				 pen->color.blue);
		data->pen.color = vcolorInternSpec(spec);
		vcolorDestroySpec(spec);
	    } else
	      data->pen.color = NULL;
	    if (array[nArray].sText != NULL) {
		vtextSelection	 sel;
		vstr		*s = array[nArray].sText;
		vtext		*text = data->text;
		
		if ((text != NULL) || (s[0] != vcharNULL)) {
		    if (text == NULL) {
			vmdrawCreateTextObject(data);
			text = data->text;
		    }
		    vtextInitSelection(text, &sel);
		    vtextSelectRange(text, &sel, 0, vtextLength(data->text));
		    vtextInsert(text, &sel, s, vcharLength(s));
		    vtextDestroySelection(text, &sel);
		}
		vstrDestroy(s);
	    }
	    data->startCorner = array[nArray].startCorner;
	    setTemp = vdomainCreateObjectSet(obj); /* TVL */
	    vdomainSetObjectBounds(domain, setTemp, &array[nArray].rect);
	    vdomainDestroyObjectSet(setTemp);
	}
    }

    if (set) {
	vdomainviewInvalObjects(document->domainView, set, 0);
	vdomainDestroyObjectSet(set);
    }
    vdomainEnableObserver(document->observerSessionDomain);

    if (array != NULL)
	vmemFree(array);
    
    return  NULL;
}  /**  end  _mdrawUpdateObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static vscrap  *_mdrawUpdateObjectsPrimHandler
\*---------------------------------------------------------------------------*/
static vscrap
*_mdrawLayerObjectPrimHandler(
    vservicePrimitive	*prim,
    vsession		*session,
    vscrap		*scrapArgs
    )
{
    unsigned int	 objId, objFrontId;
    vdomainObject	*obj, *objFront;
    vdomain		*domain;
    vmdrawDocument	*document;

    vserviceGetPrimitiveArgs(prim, scrapArgs, &objId, &objFrontId);

    document = (vmdrawDocument *)vsessionGetData(session);
    domain = vdomainviewGetDomain(document->domainView);

    obj = (vdomainObject *)vdictLoad(document->dictObjectMap, (void *)objId);
    if (objFrontId)
      objFront = (vdomainObject *)vdictLoad(document->dictObjectMap,
					    (void *)objFrontId);
    else
      objFront = NULL;

    if (obj) {
	vdomainDisableObserver(document->observerSessionDomain);
	vdomainShuffleObjects(domain, obj, objFront, (objFront != NULL));
	vmdrawRecalcLayering(document);
	vdomainEnableObserver(document->observerSessionDomain);
    }

    return  NULL;
}  /**  end  _mdrawUpdateObjectsPrimHandler  **/



/*---------------------------------------------------------------------------*\
    static  vservice  *_mdrawCreateService
\*---------------------------------------------------------------------------*/
static vservice  *_mdrawCreateService(void)
{
    vservice		*service;
    vsession		*session;
    vservicePrimitive	*prim;

    service = vserviceCreate();
    session = vserviceGetTemplateSession(service);
    vsessionSetNotify(session, _mdrawProviderSessionNotify);
    vserviceSetAttributeTag(service, vname_Title,
			vnameInternGlobalLiteral(_literalServiceTitle));
    vserviceSetAttributeTag(service, vname_Name,
				vapplicationGetName(vapplicationGetCurrent()));

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
				&_arraySignatures[_mdrawSIG_ID_DELETE_TEXT]);
    vserviceSetPrimitiveHandler(prim, _mdrawDeleteTextPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
				&_arraySignatures[_mdrawSIG_ID_INSERT_TEXT]);
    vserviceSetPrimitiveHandler(prim, _mdrawInsertTextPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);


    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
				&_arraySignatures[_mdrawSIG_ID_ADD_OBJECTS]);
    vserviceSetPrimitiveHandler(prim, _mdrawAddObjectsPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
				&_arraySignatures[_mdrawSIG_ID_HIDE_OBJECTS]);
    vserviceSetPrimitiveHandler(prim, _mdrawHideObjectsPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
			&_arraySignatures[_mdrawSIG_ID_MOVE_OBJECTS]);
    vserviceSetPrimitiveHandler(prim, _mdrawMoveObjectsPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
			&_arraySignatures[_mdrawSIG_ID_REMOVE_OBJECTS]);
    vserviceSetPrimitiveHandler(prim, _mdrawRemoveObjectsPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
			&_arraySignatures[_mdrawSIG_ID_UPDATE_OBJECTS]);
    vserviceSetPrimitiveHandler(prim, _mdrawUpdateObjectsPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    prim = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(prim,
			&_arraySignatures[_mdrawSIG_ID_LAYER_OBJECT]);
    vserviceSetPrimitiveHandler(prim, _mdrawLayerObjectPrimHandler);
    vserviceAddPrimitiveOwned(service, prim);

    return service;
}  /**   end  _mdrawCreateService  **/


static void  _mdrawConsumerSessionNotify(vsession *session,
					 vsessionEvent *event)
{
    vmdrawDocument	*document;
    vstr		*str;

    document = (vmdrawDocument *)vsessionGetData(session);
    switch (vsessionGetEventCode(event)) {
	case  vsessionEVENT_BEGIN:
	   /**  !!! If 'save' feature used a resource file, we could
	    **  !!! implement an initialization primitive that gave us a
	    **  !!! resource of what the provider looked like, and initialize
	    **  !!! ourselves off that.  In such a case, I would not unblock
	    **  !!! this window until the statement notify from that init
	    **  !!! message to avoid a race condition.
	    **/
	   vwindowUnblock(vdialogGetWindow(&document->dialog));
	   _mdrawInitDocumentSession(document, session);
	   break;
	
	case  vsessionEVENT_END:
	   str = vstrCloneScribed(vcharScribeLiteral("Session terminated"));
	   vmdrawAlert(&document->dialog, str);
	   vstrDestroy(str);
	   _mdrawUninitDocumentSession(document, session);
	   vmdrawDestroyDocument(document);
	   break;

	case  vsessionEVENT_CANNOT_BEGIN:
	   vdialogDestroy(&document->dialog);
	   break;

	default:
	    break;
    }
}  /**  end  _mdrawConsumerSessionNotify  **/

    
static int  _mdrawApplyChooser(vservicechsr *chooser, vscrap *scrap)
{
    vsession		*volatile session;
    vmdrawDocument	*document;
    vscribe		*scribe;
    
    session = vsessionCreate();
    vsessionSetAttributesFromScrap(session, scrap);
    if ((scribe = vsessionFindAttributeScribe(session, vname_Document)) ==NULL)
	scribe = vcharScribeLiteral("<unknown>");

    wrtDialog = vservicechsrGetDialog(chooser);
    document = vmdrawNewDocument();
    document->idNext = 0xffffffff;
    document->flags |= vmdrawDOC_READ_ONLY;  /* so it won't prompt for save */
    vdialogSetTitleScribed(&document->dialog,
			   vcharScribeFormatLiteral("Consumer:%S", scribe));
							
    vwindowBlock(vdialogGetWindow(&document->dialog));
    vsessionSetData(session, (void *)document);
    vsessionSetNotify(session, _mdrawConsumerSessionNotify);
    vsessionSetDestroyWhenInactive(session, TRUE);
    if (_servicePrivate == NULL)
	_servicePrivate = _mdrawCreateService();
    vsessionSetService(session, _servicePrivate);
    vsessionBegin(session);

    return TRUE;
}  /**  end _mdrawApplyChooser  **/




/*---------------------------------------------------------------------------*\
    void  mdrawOpenServiceChooser
\*---------------------------------------------------------------------------*/
void  mdrawOpenServiceChooser()
{
    vdialog	*dialog;

    if (_chooserService != NULL) {
	dialog = vservicechsrGetDialog(_chooserService);
	if (!vdialogIsOpen(dialog))
	    vdialogOpen(dialog);
	else
	    vwindowRaise(vdialogGetWindow(dialog));
    }
    else {
	vscrap	*scrapSpec;
	
	_chooserService = vservicechsrCreate();
	vservicechsrSetApply(_chooserService, _mdrawApplyChooser);

	scrapSpec = vscrapCreateDictionary();
	vscrapStoreElement(scrapSpec, vname_Title,
		vscrapFromTag(vnameInternGlobalLiteral(_literalServiceTitle)));
	vservicechsrSetMatchScrap(_chooserService, scrapSpec);
	vservicechsrOpen(_chooserService);
	if (!_bInitialized)
	    _mdrawDASStartup();
    }
}  /**  end  mdrawOpenServiceChooser  **/




/*---------------------------------------------------------------------------*\
    void  vmdrawInvalObjects
\*---------------------------------------------------------------------------*/
void  vmdrawInvalObjects(
    vmdrawDocument	*document,
    vdomainObjectSet	*set
    )
{
    vdomainviewInvalObjects(document->domainView, set, 0);
    _mdrawUpdateObjects(document, set);
}


/*---------------------------------------------------------------------------*\
    void  mdrawRegisterDocument
\*---------------------------------------------------------------------------*/
void mdrawRegisterDocument(vmdrawDocument *document)
{
    if (document->service == NULL) {
	vsession	*session;

	if (!_bInitialized)
	    _mdrawDASStartup();
	document->service = _mdrawCreateService();
	session = vserviceGetTemplateSession(document->service);
	vsessionSetData(session, (void *)document);
	vserviceSetAttributeScribe(document->service,
				   vname_Document,vcharScribe(document->name));
    }
    if (!vserviceIsEnabled(document->service)) {
	vserviceEnable(document->service);
	vdasservRegisterService(document->service);
    }
}  /**  end  mdrawRegisterDocument  **/



/*---------------------------------------------------------------------------*\
    void  mdrawUnregisterDocument
\*---------------------------------------------------------------------------*/
void mdrawUnregisterDocument(vmdrawDocument *document)
{
    if (document->service != NULL) {
	vdasservUnregisterService(document->service);
	vserviceDisable(document->service);
    }
}  /**  end  mdrawUnregisterDocument  **/

#endif /* mdrawUSE_DAS */
