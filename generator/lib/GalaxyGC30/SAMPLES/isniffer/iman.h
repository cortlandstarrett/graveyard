/* $Id: iman.h,v 1.2 1995/02/09 00:03:35 simone Exp $ */
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
 *     Image manager class; allows multiple references to a single vimage.  *
 *     Useful for applications like Looking Glass Professional(tm).         *
 *     Makes heavy use of the following galaxy managers: Class Manager,     *
 *        Command Manager (vcommand), and Undo Manager (vundo)              *
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

#ifndef imanagerINCLUDED
#define imanagerINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef tllistINCLUDED
#include "tllist.h"
#endif

/*
 *+------------------------------------------------------------------------+
 * image manager exceptions:
 *+------------------------------------------------------------------------+
 */

typedef vexValueException        imanagerNotRegisteredException;
typedef vexModuleStateException  imanagerNotSetupException;
typedef vexValueException        imanagerThingNotSetupException;
typedef vexValueException        imanagerThingNotFoundException;


/*
 *+------------------------------------------------------------------------+
 * image manager class:
 *+------------------------------------------------------------------------+
 */

typedef struct imanager imanager;
struct imanager {
  vinstance		 baseobject;    /* super class */
  vapplication		*app;		/* associated application */
  const vname		*tag;		/* user defineable tag */
  vimage		*genericImage;	/* used if can't find any match */
  tllist	       	*stores;	/* all registered stores */
  void			*global;	/* store associated with app resfile*/
  void			*active;	/* default image store */
  vresource		 activeRes;	/* default image store's resource */
  void			*masks;		/* optional store holding masks */
  void			*reserved;	/* internal scribbling */
};


/*
 *  Read-Only version of the image manager. Stores can be registered and
 *  unregisted. Images can be retrieved and released -- no operations
 *  specific to editing (storing, copying, additions, etc) are defined.
 *  The application must specify -- at startup -- the class of 
 *  manager it wants.
 */
#define imanagerCLASS(CLASS, MGR)					\
  vinstanceCLASS(CLASS, MGR);						\
  vclassMETHOD(imanagerSTARTUP, (MGR*, vapplication*));			\
  vclassMETHOD(imanagerSET_TAG, (MGR*, const vname*));			\
  vclassMETHOD(imanagerREGISTER_STORE, (MGR*, vresource));		\
  vclassMETHOD(imanagerUNREGISTER_STORE, (MGR*, vresource));		\
  vclassMETHOD(imanagerUNREGISTER_STORE_UNBALANCED, (MGR*,vresource));	\
  vclassMETHOD_RET(imanagerGET_ACTIVE_STORE, vresource, (MGR*));	\
  vclassMETHOD(imanagerSET_ACTIVE_STORE,(MGR*,vresource));		\
  vclassMETHOD_RET(imanagerGET_STORE, const void*, (MGR*, vresource));	\
  vclassMETHOD_RET(imanagerRETRIEVE_IMAGE, vimage*, 			\
		   (MGR*, const vchar*, int*));				\
  vclassMETHOD_RET(imanagerRETRIEVE_GLOBAL_IMAGE, vimage*,		\
		   (MGR*, const vchar*));				\
  vclassMETHOD(imanagerRELEASE_IMAGE, (MGR*, vimage*, const vchar*));	\
  vclassMETHOD(imanagerRELEASE_GLOBAL_IMAGE, 				\
	       (MGR*, vimage*, const vchar*));				\
  vclassMETHOD_RET(imanagerRETRIEVE_MASK, vimage*,			\
		   (MGR*, const vchar*));				\
  vclassMETHOD_RET(imanagerLOAD_STORE, void*, (MGR*, vresource));	\
  vclassMETHOD_RET(imanagerCOUNT_IMAGE_USERS, int, 			\
		   (MGR*, vresource, const vchar*));			\
  vclassMETHOD(imanagerDUMP, (MGR*, FILE*))

typedef struct imanagerClass imanagerClass;
struct imanagerClass {
  imanagerCLASS(imanagerClass, imanager);
};


/* 
 * Editable version of the image manager; a sub-class of the read-only
 * class. Stores can be created, destroyed, and changed. Images can be
 * added and removed from stores. The most significant of these operations
 * are undoable. The application must specify -- at startup -- the class
 * of manager it wants.
 *
 * For undodable operations, the application can provide readable 
 * undo/redo strings for the undo/redo menus.
 */
typedef enum {
  imanagerUNDO_OP_PASTE,
  imanagerUNDO_OP_ADD,
  imanagerUNDO_OP_REMOVE
}imanagerUndoOp;

typedef const vchar *(*imanagerUndoActionNamer)(imanagerUndoOp op);

#define imanagerEditableCLASS(CLASS, MGR)				\
  imanagerCLASS(CLASS, MGR);						\
  vclassMETHOD_RET(imanagerMAKE_STORE, vresource, (MGR*, vresource));	\
  vclassMETHOD(imanagerNUKE_STORE, (MGR*, vresource));			\
  vclassMETHOD(imanagerSAVE_STORE, (MGR*, vresource));			\
  vclassMETHOD(imanagerADD_IMAGE_2STORE, (MGR*, vresource, vimage*,	\
					  const vname*, void**));	\
  vclassMETHOD(imanagerREMOVE_IMAGE_FROM_STORE, (MGR*, vresource,	\
						const vname*, void**));	\
  vclassMETHOD(imanagerPASTE_IMAGES_2STORE, (MGR*, vresource,		\
					     vdict*, void**));		\
  vclassMETHOD(imanagerPASTE_RIMAGES_2STORE, (MGR*, vresource,		\
					     vresource, void**));	\
  vclassMETHOD(imanagerPRELOAD_STORE, (MGR*, vresource));		\
  vclassMETHOD(imanagerSET_UNDO_NAMER, (MGR*, imanagerUndoActionNamer namer))

typedef struct imanagerEditableClass imanagerEditableClass;
struct imanagerEditableClass {
  imanagerEditableCLASS(imanagerEditableClass, imanager);
};



/*
 *+------------------------------------------------------------------------+
 * imanager, exported routines:
 *+------------------------------------------------------------------------+
 */

imanager *imanagerCreate(
    vapplication               	*app
    );

void imanagerDestroy(
    imanager          		*mgr
    );

void imanagerSetTag(
    imanager                  	*mgr,
    const vname            	*tag
    );

void imanagerRegisterAsImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

void imanagerUnRegisterAsImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

void imanagerUnRegisterUnbalancedAsImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

vresource imanagerGetActiveImageStore(
    imanager                  	*mgr
    );

void imanagerSetActiveImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

const void *imanagerGetImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

vimage *imanagerRetrieveImage(
    imanager                  	*mgr,
    const vchar            	*tag,
    int            		*match
    );

vimage *imanagerRetrieveGlobalImage(
    imanager                  	*mgr,
    const vchar            	*tag
    );

void imanagerReleaseImage(
    imanager                  	*mgr,
    vimage            		*image,
    const vchar            	*tag
    );

void imanagerReleaseGlobalImage(
    imanager                  	*mgr,
    vimage            		*image,
    const vchar            	*tag
    );

vimage *imanagerRetrieveImageMask(
    imanager                  	*mgr,
    const vchar            	*tag
    );

int imanagerGetNumberOfImageUsers(
    imanager                  	*mgr,
    vresource            	 res,
    const vchar            	*tag
    );

const vname **imanagerCreateListingOfImageStoreImages(
    imanager              	*mgr,
    vresource                    res
    );

void imanagerDestroyListingOfImageStoreImages(
    imanager              	*mgr,
    vresource                    res,
    const vname                **listing
    );

vinstance *imanagerGetInstance(
    imanager              	*mgr
    );

const vname *imanagerGetTag(
    imanager              	*mgr
    );

vapplication *imanagerGetApp(
    imanager              	*mgr
    );

const vname *imanagerGetImageStoreResourceTag(
    imanager              	*mgr
    );

#if vdebugDEBUG
void imanagerDump(
    imanager                  	*mgr,
    FILE            		*stream
    );
#endif


/*
 *+------------------------------------------------------------------------+
 * imanager-editable, exported routines:
 *+------------------------------------------------------------------------+
 */

imanager *imanagerCreateEditable(
    vapplication               	*app
    );

void imanagerPreloadImageStoreToMemory(
    imanager                  	*mgr,
    vresource            	 res
    );

vresource imanagerMakeImageStore(
    imanager                  	*mgr,
    vresource            	 parent
    );

void imanagerSaveImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

void imanagerNukeImageStore(
    imanager                  	*mgr,
    vresource            	 res
    );

void imanagerSetUndoActionNamer(
    imanager                  	*mgr,
    imanagerUndoActionNamer    	 namer
    );

void imanagerAddImageToImageStoreUndoable(
    imanager                  	*mgr,
    vresource            	 res,
    vimage            	 	*image,
    const vname        	 	*tag,
    void        	 	**undoaction
    );

void imanagerRemoveImageFromImageStoreUndoable(
    imanager                  	*mgr,
    vresource            	 res,
    const vname        	 	*tag,
    void        	 	**undoaction
    );

void imanagerPasteImagesIntoImageStoreUndoable(
    imanager                  	*mgr,
    vresource            	 res,
    vdict          	 	*images,
    void        	 	**undoaction
    );

void imanagerPasteResourceImagesIntoImageStoreUndoable(
    imanager                  	*mgr,
    vresource            	 res,
    vresource          	 	 images,
    void        	 	**undoaction
    );


/*
 *+------------------------------------------------------------------------+
 * imanager exceptions, exported routines:
 *+------------------------------------------------------------------------+
 */

imanagerNotRegisteredException *imanagerGetNotRegisteredException(
    void
    );

imanagerNotSetupException *imanagerGetNotSetupException(
    void
    );

imanagerThingNotSetupException *imanagerGetThingNotSetupException(
    void
    );

imanagerThingNotFoundException *imanagerGetThingNotFoundException(
    void
    );

/*
 *+------------------------------------------------------------------------+
 * imanager, exported routines defined as macros :
 *+------------------------------------------------------------------------+
 */
imanager *imanagerCreateEither(vapplication*, int);

#define imanagerGetInstance(im)						\
  (&(im)->baseobject)
#define imanagerGetApp(im)						\
  ((im)->app)
#define imanagerGetTag(im)						\
  ((im)->tag)
#define imanagerGetClass(im)						\
  ((imanagerClass*)vinstanceGetClass(imanagerGetInstance(im)))
#define imanagerGetEditableClass(im)					\
  ((imanagerEditableClass*)vinstanceGetClass(imanagerGetInstance(im)))
#define imanagerCreate(a) 						\
  imanagerCreateEither(a,FALSE)
#define imanagerCreateEditable(a) 					\
  imanagerCreateEither(a,TRUE)

#define imanagerSend(im,m,a)						\
  vclassSend(imanagerGetClass(im),m,a)
#define imanagerEditableSend(im,m,a)					\
  vclassSend(imanagerGetEditableClass(im),m,a)

#define imanagerSetTag(im,t)						\
  imanagerSend(im, imanagerSET_TAG, (im,t))
#define imanagerRegisterAsImageStore(im,r)				\
  imanagerSend(im, imanagerREGISTER_STORE, (im,r))
#define imanagerUnRegisterAsImageStore(im,r)				\
  imanagerSend(im, imanagerUNREGISTER_STORE, (im,r))
#define imanagerUnRegisterUnbalancedAsImageStore(im,r)			\
  imanagerSend(im, imanagerUNREGISTER_STORE_UNBALANCED, (im,r))
#define imanagerGetActiveImageStore(im)					\
  imanagerSend(im, imanagerGET_ACTIVE_STORE, (im))
#define imanagerSetActiveImageStore(im,r)				\
  imanagerSend(im, imanagerSET_ACTIVE_STORE, (im,r))
#define imanagerGetImageStore(im,r)					\
  imanagerSend(im, imanagerGET_STORE, (im,r))
#define imanagerRetrieveImage(im,t,b)					\
  imanagerSend(im, imanagerRETRIEVE_IMAGE, (im,t,b))
#define imanagerRetrieveGlobalImage(im,t)				\
  imanagerSend(im, imanagerRETRIEVE_GLOBAL_IMAGE, (im,t))
#define imanagerReleaseImage(im,i,t)					\
  imanagerSend(im, imanagerRELEASE_IMAGE, (im,i,t))
#define imanagerReleaseGlobalImage(im,i,t)				\
  imanagerSend(im, imanagerRELEASE_GLOBAL_IMAGE, (im,i,t))
#define imanagerRetrieveImageMask(im,t)					\
  imanagerSend(im, imanagerRETRIEVE_MASK, (im,t))
#define imanagerGetNumberOfImageUsers(im,r,t)				\
  imanagerSend(im, imanagerCOUNT_IMAGE_USERS, (im,r,t))

#define imanagePreloadImageStoreToMemory(im,r)				\
  imanagerEditableSend(im, imanagerPRELOAD_STORE, (im,r))
#define imanagerMakeImageStore(im,r)					\
  imanagerEditableSend(im, imanagerMAKE_STORE, (im,r))
#define imanagerNukeImageStore(im,r)					\
  imanagerEditableSend(im, imanagerNUKE_STORE, (im,r))
#define imanagerSaveImageStore(im,r)					\
  imanagerEditableSend(im, imanagerSAVE_STORE, (im,r))
#define imanagerAddImageToImageStoreUndoable(im,r,i,t,u)		\
  imanagerEditableSend(im, imanagerADD_IMAGE_2STORE, (im,r,i,t,u))
#define imanagerRemoveImageFromImageStoreUndoable(im,r,t,u)		\
  imanagerEditableSend(im, imanagerREMOVE_IMAGE_FROM_STORE, (im,r,t,u))
#define imanagerPasteImagesIntoImageStoreUndoable(im,r,i,u)		\
  imanagerEditableSend(im, imanagerPASTE_IMAGES_2STORE, (im,r,i,u))
#define imanagerPasteResourceImagesIntoImageStoreUndoable(im,r,i,u)	\
  imanagerEditableSend(im, imanagerPASTE_RIMAGES_2STORE, (im,r,i,u))
#define imanagerSetUndoActionNamer(im,p)				\
  imanagerEditableSend(im, imanagerSET_UNDO_NAMER, (im,p))

#if vdebugDEBUG
#define imanagerDump(im,fp)						\
  imanagerSend(im, imanagerDUMP, (im,fp))
#endif

/*
 *+------------------------------------------------------------------------+
 * exception handlign
 *+------------------------------------------------------------------------+
 */

extern vexClass _imanagerNotRegisteredExceptionClass;
extern vexClass _imanagerNotSetupExceptionClass;
extern vexClass _imanagerThingNotSetupExceptionClass;
extern vexClass _imanagerThingNotFoundExceptionClass;

#define imanagerGetNotRegisteredExceptionClass()	\
  (&_imanagerNotRegisteredExceptionClass)

#define imanagerGetNotSetupExceptionClass()		\
  (&_imanagerNotSetupExceptionClass)

#define imanagerGetThingNotSetupExceptionClass()	\
  (&_imanagerThingNotSetupExceptionClass)

#define imanagerGetThingNotFoundExceptionClass()	\
  (&_imanagerThingNotFoundExceptionClass)

#define imanagerGenerateNotRegisteredException(_s)	\
  {vexGenerate( imanagerGetNotRegisteredExceptionClass(), vexMESSAGE, 	\
	        (_s), vexERRNO, 0, vexNULL ); }

#define imanagerGenerateNotSetupException(_s)		\
  {vexGenerate( imanagerGetNotSetupExceptionClass(), vexMESSAGE, 	\
	        (_s), vexERRNO, 0, vexNULL ); }

#define imanagerGenerateThingNotSetupException(_s)	\
  {vexGenerate( imanagerGetThingNotSetupExceptionClass(), vexMESSAGE, 	\
	        (_s), vexERRNO, 0, vexNULL ); }

#define imanagerGenerateThingNotFoundException(_s)	\
  {vexGenerate( imanagerGetThingNotFoundExceptionClass(), vexMESSAGE, 	\
	        (_s), vexERRNO, 0, vexNULL ); }

#define imanagerGetNotRegisteredException()		\
  ( (imanagerNotRegisteredException*) 			\
   vexGetExceptionOfClass( imanagerGetNotRegisteredExceptionClass()) )

#define imanagerGetNotSetupException()			\
  ( (imanagerNotSetupException*) 			\
   vexGetExceptionOfClass( imanagerGetNotSetupExceptionClass()) )

#define imanagerGetThingNotSetupException()		\
  ( (imanagerThingNotSetupException*) 			\
   vexGetExceptionOfClass( imanagerGetThingNotSetupExceptionClass()) )

#define imanagerGetThingNotFoundException()		\
  ( (imanagerThingNotFoundException*) 			\
   vexGetExceptionOfClass( imanagerGetThingNotFoundExceptionClass()) )


/* imanagerINCLUDED */
#endif
