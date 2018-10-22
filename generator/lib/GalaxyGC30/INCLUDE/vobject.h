/* $Id: vobject.h,v 1.45 1997/09/29 20:33:39 robert Exp $ */

/************************************************************

    vobject.h

    C Interface file for the Class Manager objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vobjectINCLUDED
#define vobjectINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
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

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

enum {
    vobjectNEXT_ID_ATTRIBUTE        = 0
};

enum {
    vobjectSELECT_NULL              = 0,
    vobjectSELECT_HELP,
    vobjectSELECT_DUMP,
    vobjectNEXT_SELECT
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * objects
 */

#ifdef	__cplusplus
struct vobject {
    vobservable			 super;
};
#else
typedef struct vobject			vobject;
#endif

typedef struct vobjectClass		vobjectClass;

/*
 * attributed objects (deprecated)
 */

typedef vobject				vobjectAttributed;
typedef vobjectClass			vobjectAttributedClass;

/*
 * ID attribute templates
 */

typedef struct vobjectIDAttributeTemplate vobjectIDAttributeTemplate;
struct vobjectIDAttributeTemplate {
    const char                     *name;
    int                             id;
};

/*
 * object lists
 */

typedef struct vobjectList          vobjectList;
typedef struct vobjectListClass     vobjectListClass;

/*
 * object child iterators
 */

typedef struct vobjectChildIterator		vobjectChildIterator;
typedef struct vobjectChildIteratorClass	vobjectChildIteratorClass;

typedef vobjectChildIterator		vobjectBreadthFirstChildIterator;
typedef vobjectChildIterator		vobjectDepthFirstChildIterator;

typedef struct vobjectPartialChildIterator	vobjectPartialChildIterator;
typedef struct vobjectPartialChildIteratorClass
					vobjectPartialChildIteratorClass;

/*
 * forward declarations for types in vcommand.h
 */

typedef struct vcommandSpace		vcommandSpace;

typedef struct vcommandSelector		vcommandSelector;
typedef struct vcommandSelectorClass	vcommandSelectorClass;

/*
 * object commands
 */

#if (!vportCPLUSPLUS_SOURCE)
typedef vcommandSelector		vobjectCommand;
#endif /* if (!vportCPLUSPLUS_SOURCE) */
typedef vcommandSelectorClass		vobjectCommandClass;

/*
 * exceptions (deprecated)
 */

typedef vclassNotFoundException		vobjectUndefinedClassException;
typedef vclassUnnamedException         	vobjectUnnamedClassException;

/*
 * * * * * * * * * * DEPENDENT HEADERS * * * * * * * * * *
 */

#ifndef vhelprequestINCLUDED
#include vhelprequestHEADER
#endif


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vobjectStartup(void);


/*
 * objects
 */

vobjectClass *vobjectGetResourceClass(
    vresource                       resource
    );

vobjectClass *vobjectGetDefaultClass(
    void
    );

vinstance *vobjectGetInstance(
    vobject                        *object
    );

vloadable *vobjectGetLoadable(
    vobject                        *object
    );

vobservable *vobjectGetObservable(
    vobject                        *object
    );

vobjectClass *vobjectGetClass(
    vobject                        *object
    );

/*
 * objects
 */

vobject *vobjectCreateOfClass(
    vobjectClass                   *clas
    );

void vobjectInitOfClass(
    vobject                        *object,
    vobjectClass                   *clas
    );

void vobjectDestroy(
    vobject                        *object
    );

void vobjectDestroyLater(
    vobject                        *object
    );

vobject *vobjectClone(
    vobject                        *object
    );

void vobjectCopyInit(
    vobject                        *object,
    vobject                        *target
    );

void vobjectCopy(
    vobject                        *object,
    vobject                        *target
    );

void vobjectCopyCommon(
    vobject                        *object,
    vobject                        *target
    );

vobject *vobjectLoad(
    vresource                       resource
    );

void vobjectLoadInit(
    vobject                        *object,
    vresource                       resource
    );

void vobjectStore(
    vobject                        *object,
    vresource                       resource
    );

void vobjectDump(
    vobject                        *object,
    FILE                           *stream
    );

const vname *vobjectGetTag(
    vobject                        *object
    );

void vobjectSetTag(
    vobject                        *object,
    const vname                    *tag
    );

size_t vobjectGetSize(
    vobject                        *object
    );

int vobjectIsKindOf(
    const vobject                  *object,
    const void                     *clas
    );

/*
 * observable routines
 */

void vobjectInstallObserver(
    vobject			   *object,
    vobservable			   *observer
    );

void vobjectUninstallObserver(
    vobject			   *object,
    vobservable			   *observer
    );

void vobjectAnnounce(
    vobject			   *object,
    voccurrence			   *occurrence
    );

/*
 * attribute routines
 */

void vobjectSetAttribute(
    vobject                        *object,
    const vname                    *attr,
    const void                     *value
    );

void vobjectSetAllAttributes(
    vobject                        *object,
    vdict                          *attr2value
    );

const void *vobjectGetAttribute(
    vobject                        *object,
    const vname                    *attr
    );

void vobjectGetAllAttributes(
    vobject                        *object,
    vdict                          *attr2value
    );

void vobjectGetContextAttributes(
    vobject                        *object,
    vdict                          *attr2value
    );

void vobjectSetIDAttribute(
    vobject                        *object,
    int                             id,
    const void                     *value
    );

const void *vobjectGetIDAttribute(
    vobject                        *object,
    int                             id
    );

void vobjectChangedParentAttribute(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectChangedAttribute(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectChangedChildAttribute(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectChangedAttributeNone(
    vobject                        *object,
    const vname                    *attr
    );

void vobjectChangedAttributeValue(
    vobject                        *object,
    const vname                    *attr,
    const void                     *oldValue,
    const void                     *value
    );

void vobjectChangedAttributeMulti(
    vobject                        *object,
    const vname                    *attr,
    ...
    );

void vobjectUpdateAttribute(
    vobject                        *object,
    const vname                    *attr
    );

void vobjectUpdateAllAttributes(
    vobject                        *object
    );

int vobjectIssueSelector(
    vobject                        *object,
    int                             selector,
    vdict                          *attr2value
    );

int vobjectQuerySelector(
    vobject                        *object,
    int                             selector,
    vdict                          *attr2value
    );

int vobjectIssueCommand(
    vobject                        *object,
    const vname                    *tag,
    vdict                          *attr2value
    );

int vobjectQueryCommand(
    vobject                        *object,
    const vname                    *tag,
    vdict                          *attr2value
    );

int vobjectDispatchCommand(
    vobject                        *object,
    const vname                    *tag,
    vevent                         *event
    );

const void *vobjectBindAttribute(
    vobject                        *object,
    const vname                    *attr,
    const vname                    *tag
    );

void vobjectBindAllAttributes(
    vobject                        *object,
    const vname                    *tag,
    vdict                          *attr2value
    );

const void *vobjectAssociateAttribute(
    vobject                        *object,
    const vname                    *attr,
    const vname                    *tag
    );

void vobjectAssociateAllAttributes(
    vobject                        *object,
    const vname                    *tag,
    vdict                          *attr2value
    );

void vobjectPropagateChange(
    vobject                        *object,
    const vname                    *attr,
    const vname                    *tag,
    const void                     *value
    );

void vobjectPropagateChangeDict(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vobjectPropagateChangeDictFromParent(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *tag2value
    );

vdict *vobjectFilterChangeDict(
    vobject                        *object,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vobjectHelp(
    vobject                        *object
    );

vbool vobjectDisplayHelp(
    vobject			   *object,
    vhelprequest		   *request
    );

vobject *vobjectGetHelpParent(
    vobject                        *object
    );

const vchar **vobjectBuildHelpContext(
    vobject                        *object,
    int                            *count
    );

vcommandSpace *vobjectGetSpace(
    vobject          	           *object
    );

vcommandSpace *vobjectMakeSpace(
    vobject          	           *object
    );

vobject *vobjectGetParent(
    vobject          	           *object
    );

vobject *vobjectGetChild(
    vobject			   *object,
    const vname			   *tag,
    vobjectClass		   *childClass
    );

vobject *vobjectFindChild(
    vobject			   *object,
    const vname			   *tag,
    vobjectClass		   *childClass
    );

void vobjectAnnounceToParent(
    vobject			   *object,
    voccurrence			   *occurrence
    );

void vobjectAnnounceToChildren(
    vobject			   *object,
    voccurrence			   *occurrence
    );

void vobjectStoreDictIDAttributeTemplates(
    vdict                          *dict,
    const vobjectIDAttributeTemplate *templates,
    size_t                          count
    );

/*
 * attributed objects (deprecated)
 */

vobjectClass *vobjectGetDefaultAttributedClass(
    void
    );

vobjectClass *vobjectGetAttributedClass(
    vobject                        *object
    );

/*
 * object commands
 */

vobjectCommandClass *vobjectGetCommandClass(
    void
    );

/*
 * object child iterators
 */

vobjectChildIteratorClass *vobjectGetDefaultChildIteratorClass(
    void
    );

vobjectChildIteratorClass *vobjectGetBreadthFirstChildIteratorClass(
    void
    );

vobjectChildIteratorClass *vobjectGetDepthFirstChildIteratorClass(
    void
    );

vobjectChildIteratorClass *vobjectGetChildIteratorClass(
    vobjectChildIterator	   *iterator
    );

viteratorGroup *vobjectGetChildIteratorGroupIterator(
    vobjectChildIterator	   *iterator
    );

viterator *vobjectGetChildIteratorIterator(
    vobjectChildIterator	   *iterator
    );

void vobjectInitChildIterator(
    vobjectChildIterator	   *iterator,
    vobject          		   *parent
    );

void vobjectInitBreadthFirstChildIterator(
    vobjectBreadthFirstChildIterator *iterator,
    vobject          		   *parent
    );

void vobjectInitDepthFirstChildIterator(
    vobjectDepthFirstChildIterator *iterator,
    vobject          		   *parent
    );

void vobjectDestroyChildIterator(
    vobjectChildIterator	   *iterator
    );

vbool vobjectNextChildIterator(
    vobjectChildIterator	   *iterator
    );

vobject *vobjectGetChildIteratorChild(
    vobjectChildIterator	   *iterator
    );

int vobjectGetChildIteratorDepth(
    vobjectChildIterator	   *iterator
    );

void vobjectAddChildIteratorPart(
    vobjectChildIterator	     *iterator,
    vobjectPartialChildIteratorClass *partialIteratorClass,
    vobject			     *partParent
    );

/*
 * object partial child iterators
 */

vobjectPartialChildIteratorClass *vobjectGetDefaultPartialChildIteratorClass(
    void
    );

vobjectPartialChildIteratorClass *vobjectGetPartialChildIteratorClass(
    vobjectPartialChildIterator   	*iterator
    );

viterator *vobjectGetPartialChildIteratorIterator(
    vobjectPartialChildIterator   	*iterator
    );

vobject *vobjectGetPartialChildIteratorParent(
    vobjectPartialChildIterator   	*iterator
    );

/*
 * object lists
 */

vobjectListClass *vobjectGetDefaultListClass(
    void
    );

vobjectList *vobjectCreateListOfClass(
    vobjectListClass               *clas
    );

vobjectList *vobjectCreateList(
    void
    );

vobjectList *vobjectCloneList(
    vobjectList                    *object
    );

void vobjectInitListOfClass(
    vobjectList                    *list, 
    vobjectListClass               *clas
    );

void vobjectInitList(
    vobjectList                    *list
    );

void vobjectDestroyList(
    vobjectList                    *list
    );

void vobjectCopyList(
    vobjectList                    *list,
    vobjectList                    *targetList
    );

void vobjectCopyInitList(
    vobjectList                    *list,
    vobjectList                    *targetList
    );

vobjectList *vobjectLoadList(
    vresource                       resource
    );

void vobjectLoadInitList(
    vobjectList                    *list,
    vresource                       resource
    );

void vobjectStoreList(
    vobjectList                    *list,
    vresource                       resource
    );

void vobjectAppendList(
    vobjectList                    *list,
    vobject                        *object
    );

void vobjectInsertList(
    vobjectList                    *list,
    vobject                        *object,
    int                             index
    );

vobject *vobjectRemoveListIndex(
    vobjectList                    *list,
    int                             index
    );

vobject *vobjectRemoveList(
    vobjectList                    *list,
    vobject                        *object
    );

void vobjectSetListIndexIndex(
    vobjectList                    *list,
    int                             objectIndex,
    int                             index
    );

void vobjectSetListIndex(
    vobjectList                    *list,
    vobject                        *object,
    int                             index
    );

vobject *vobjectReplaceListAt(
    vobjectList                    *list,
    int                             index,
    vobject                        *object
    );

vobject *vobjectGetListObject(
    vobjectList                    *list
    );

vloadable *vobjectGetListLoadable(
    vobjectList                    *list
    );

vinstance *vobjectGetListInstance(
    vobjectList                    *list
    );

vobjectListClass *vobjectGetListClass(
    vobjectList                    *list
    );

vobject **vobjectGetListObjects(
    vobjectList                    *list
    );

vobject **vobjectGetListStop(
    vobjectList                    *list
    );

int vobjectGetListCount(
    vobjectList                    *list
    );

vobject *vobjectGetListAt(
    vobjectList                    *list,
    int                             index
    );

int vobjectGetListIndex(
    vobjectList                    *list,
    vobject                        *object
    );

int vobjectFindListIndex(
    vobjectList                    *list,
    const vname                    *tag
    );

vobject *vobjectFindList(
    vobjectList                    *list,
    const vname                    *tag
    );

vobject *vobjectRelocateList(
    vobjectList                    *list,
    vobject                        *object,
    vobjectList                    *target
    );

void vobjectPropagateListChangeDictFromParent(
    vobjectList                    *list,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vobjectChangedListParentAttribute(
    vobjectList                    *list,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectChangedListAttribute(
    vobjectList                    *list,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectChangedListChildAttribute(
    vobjectList                    *list,
    const vname                    *attr,
    vdict                          *context
    );

void vobjectUpdateListAttribute(
    vobjectList                    *list,
    const vname                    *attr
    );

void vobjectUpdateAllListAttributes(
    vobjectList                    *list
    );

/*
 * deprecated
 */

void vobjectDeleteListIndex(
    vobjectList                    *list,
    int                             index
    );

void vobjectDeleteList(
    vobjectList                    *list,
    vobject                        *object
    );

void vobjectSetListAt(
    vobjectList                    *list,
    int                             index,
    vobject                        *object
    );

/*
 * exceptions (deprecated)
 */

const vexClass *vobjectGetUndefinedClassExceptionClass(
    void
    );

const vexClass *vobjectGetUnnamedClassExceptionClass(
    void
    );

vobjectUndefinedClassException *vobjectGetUndefinedClassException(
    void
    );

vobjectUnnamedClassException *vobjectGetUnnamedClassException(
    void
    );

const vname *vobjectGetUndefinedClassExceptionName(
    vobjectUndefinedClassException *exception  
    );

void vobjectUndefinedClassExceptionNAME(
    void                           *exception,
    va_list                        *args
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#ifndef __cplusplus
struct vobject {
    vobservable			 super;
};
#endif

#define vobjectINIT		vinstanceINIT
#define vobjectDESTROY		vinstanceDESTROY
#define vobjectCOPY		vloadableCOPY
#define vobjectCOPY_INIT	vloadableCOPY_INIT
#define vobjectLOAD_INIT	vloadableLOAD_INIT
#define vobjectSTORE		vloadableSTORE
#define vobjectDUMP		vloadableDUMP
#define vobjectSET_TAG		vloadableSET_TAG

#define vobjectCLASS(SUPER, OBJECT)                                           \
    vobservableCLASS(SUPER, OBJECT);                                          \
    vclassVARIABLE(vobjectID_ATTRIBUTE_DICT, vdict*);                         \
    vclassVARIABLE(vobjectSPACE, vcommandSpace*);                             \
    vclassVARIABLE(vobjectKEY_MAP, vdict*);                                   \
    vclassMETHOD(vobjectSET_ATTRIBUTE,                                        \
		 (OBJECT *object, const vname *attr, const void *value));     \
    vclassMETHOD(vobjectSET_ALL_ATTRIBUTES,                                   \
		 (OBJECT *object, vdict *attr2value));                        \
    vclassMETHOD_RET(vobjectGET_ATTRIBUTE, const void*,                       \
		     (OBJECT *object, const vname *attr));                    \
    vclassMETHOD(vobjectGET_ALL_ATTRIBUTES,                                   \
		 (OBJECT *object, vdict *attr2value));                        \
    vclassMETHOD(vobjectGET_CONTEXT_ATTRIBUTES,                               \
		 (OBJECT *object, vdict *attr2value));                        \
    vclassMETHOD(vobjectSET_ID_ATTRIBUTE,                                     \
		 (OBJECT *object, int id, const void *value));                \
    vclassMETHOD_RET(vobjectGET_ID_ATTRIBUTE, const void*,                    \
		     (OBJECT *object, int id));                               \
    vclassMETHOD(vobjectCHANGED_PARENT_ATTRIBUTE,                             \
		 (OBJECT *object, const vname *attr, vdict *context));        \
    vclassMETHOD(vobjectCHANGED_ATTRIBUTE,                                    \
		 (OBJECT *object, const vname *attr, vdict *context));        \
    vclassMETHOD(vobjectCHANGED_CHILD_ATTRIBUTE,                              \
		 (OBJECT *object, const vname *attr, vdict *context));        \
    vclassMETHOD(vobjectUPDATE_ATTRIBUTE,                                     \
		 (OBJECT *object, const vname *attr));                        \
    vclassMETHOD(vobjectUPDATE_ALL_ATTRIBUTES, (OBJECT *object));             \
    vclassMETHOD_RET(vobjectISSUE_SELECTOR, int,                              \
		     (OBJECT *object, int selector, vdict *attr2value));      \
    vclassMETHOD_RET(vobjectQUERY_SELECTOR, int,                              \
		     (OBJECT *object, int selector, vdict *attr2value));      \
    vclassMETHOD_RET(vobjectBIND_ATTRIBUTE, const void*,                      \
		     (OBJECT *object, const vname *attr, const vname *tag));  \
    vclassMETHOD(vobjectBIND_ALL_ATTRIBUTES,                                  \
		 (OBJECT *object, const vname *tag, vdict *attr2value));      \
    vclassMETHOD(vobjectPROPAGATE_CHANGE_DICT,                                \
		 (OBJECT *object, const vname *attr, vdict *tag2value));      \
    vclassMETHOD_RET(vobjectFILTER_CHANGE_DICT, vdict*,                       \
		     (OBJECT *object, const vname *attr, vdict *tag2value));  \
    vclassMETHOD(vobjectHELP, (OBJECT *object));                              \
    vclassMETHOD_RET(vobjectDISPLAY_HELP, vbool,                              \
		     (OBJECT *object, vhelprequest *request));                \
    vclassMETHOD_RET(vobjectGET_HELP_PARENT, vobject *,                       \
		     (OBJECT *object));                                       \
    vclassMETHOD_RET(vobjectBUILD_HELP_CONTEXT, const vchar**,                \
		     (OBJECT *object, int *count));			      \
    vclassMETHOD_RET(vobjectGET_SPACE, vcommandSpace *,			      \
		     (OBJECT *object));					      \
    vclassMETHOD_RET(vobjectMAKE_SPACE, vcommandSpace *,		      \
		     (OBJECT *object));					      \
    vclassMETHOD_RET(vobjectGET_PARENT, vobject *,			      \
		     (OBJECT *object));					      \
    vclassMETHOD(vobjectBUILD_CHILD_ITERATOR,				      \
		 (OBJECT *object, vobjectChildIterator *iterator));	      \
    vclassMETHOD(vobjectANNOUNCE_TO_PARENT,				      \
		 (OBJECT *object, voccurrence *occurrence));		      \
    vclassMETHOD(vobjectANNOUNCE_TO_CHILDREN,				      \
		 (OBJECT *object, voccurrence *occurrence));		      \
    vclassMETHOD(vobjectOBSERVE_PARENT,					      \
		 (OBJECT *object, voccurrence *occurrence));		      \
    vclassMETHOD(vobjectOBSERVE_CHILD,					      \
		 (OBJECT *object, voccurrence *occurrence))


#define vobjectATTRIBUTED_CLASS	vobjectCLASS


struct vobjectClass {
    vobjectCLASS(vobjectClass, vobject);
};


vportALIAS(vobjectAttributed, vobject)


/*
 * object lists
 */

struct vobjectList {
    vobject                         object;
    vobject                       **objects, **stop, **max;
};

#define vobjectLIST_CLASS(SUPER, LIST, OBJECT)                                \
    vobjectCLASS(SUPER, LIST);                                                \
    vclassVARIABLE(vobjectLIST_ELEMENT_CLASS, vobjectClass *);		      \
    vclassMETHOD(vobjectAPPEND_LIST, (LIST *list, OBJECT *object));           \
    vclassMETHOD_RET(vobjectREMOVE_LIST_INDEX, OBJECT *,		      \
		     (LIST *list, int index));			              \
    vclassMETHOD(vobjectDELETE_LIST_INDEX, (LIST *list, int index));          \
    vclassMETHOD_RET(vobjectREPLACE_LIST_AT, OBJECT *,                        \
		 (LIST *list, int index, OBJECT *object));		      \
    vclassMETHOD(vobjectSET_LIST_AT,                                          \
		 (LIST *list, int index, OBJECT *object));                    \
    vclassMETHOD(vobjectSET_LIST_INDEX_INDEX,                                 \
		 (LIST *list, int objectIndex, int index))

struct vobjectListClass {
    vobjectLIST_CLASS(vobjectListClass, vobjectList, vobject);
};

/*
 * object child iterators
 */

enum {
  _vobjectNO_ITERATOR_RECURSION = 0,
  _vobjectBREADTH_FIRST_ITERATOR_RECURSION = 1,
  _vobjectDEPTH_FIRST_ITERATOR_RECURSION = 2
};

struct vobjectChildIterator {
  viteratorGroup		 super;

  vobject			*child;
  int				 depth;
  int				 recursion;
};

#define vobjectCHILD_ITERATOR_CLASS(CLASS, ITERATOR)			      \
    viteratorGROUP_CLASS(CLASS, ITERATOR)

struct vobjectChildIteratorClass {
    vobjectCHILD_ITERATOR_CLASS(vobjectChildIteratorClass,
				vobjectChildIterator);
};


vportALIAS(vobjectBreadthFirstChildIterator, vobjectChildIterator)

vportALIAS(vobjectDepthFirstChildIterator, vobjectChildIterator)


struct vobjectPartialChildIterator {
  viterator			 super;

  int				 depth;
};

#define vobjectPARTIAL_CHILD_ITERATOR_CLASS(CLASS, ITERATOR)	              \
    viteratorCLASS(CLASS, ITERATOR)

struct vobjectPartialChildIteratorClass {
    vobjectPARTIAL_CHILD_ITERATOR_CLASS(vobjectPartialChildIteratorClass,
					vobjectPartialChildIterator);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vobjectSendBuildChildIterator(
	vobject *object, vobjectChildIterator *iterator);

vobjectPartialChildIteratorClass *_vobjectGetListPartialChildIteratorClass(
	void);

/* (deprecated) */

vobjectPartialChildIterator *vobjectCreatePartialChildIteratorOfClass(
    vobjectPartialChildIteratorClass *clas);

void vobjectPrependPartialChildIterator(
    vobjectChildIterator *iterator,
    vobjectPartialChildIterator *partialIterator);

/* (deprecated) */

#define vobjectCreatePartialChildIteratorOfClass(c) \
    ((vobjectPartialChildIterator *) \
     vinstanceCreateOfClass((vinstanceClass *) c))
#define vobjectPrependPartialChildIterator(i,p) \
    { viteratorStart(vobjectGetPartialChildIteratorIterator(p), \
		     viteratorGetStarter(vobjectGetChildIteratorIterator(i)));\
      viteratorInsertGroupPartOwned(vobjectGetChildIteratorGroupIterator(i), \
			       0, vobjectGetPartialChildIteratorIterator(p)); }


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * objects
 */

#define vobjectGetResourceClass(r) \
    ((vobjectClass *) vloadableGetResourceClass(r))

#define vobjectGetObservable(o)     vportBASE_OBJECT(o, super)
#define vobjectGetLoadable(o) \
    vobservableGetLoadable(vobjectGetObservable(o))
#define vobjectGetInstance(o) \
    vloadableGetInstance(vobjectGetLoadable(o))

#define vobjectGetClass(o) \
    ((vobjectClass*)vinstanceGetClass(vobjectGetInstance(o)))

#define vobjectCreateOfClass(c) \
    ((vobject *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vobjectInitOfClass(o,c) \
    vinstanceInitOfClass(vobjectGetInstance(o), (vinstanceClass *)(c))
#define vobjectDestroy(o) \
    vinstanceDestroy(vobjectGetInstance(o))
#define vobjectDestroyLater(o) \
    vinstanceDestroyLater(vobjectGetInstance(o))

#define vobjectClone(o) \
    ((vobject *) \
     vloadableCloneOfSubclass(vobjectGetLoadable(o), \
			      (vloadableClass*) vobjectGetDefaultClass()))
#define vobjectCopyInit(o,t) \
    vloadableCopyInitOfSubclass(vobjectGetLoadable(o), vobjectGetLoadable(t), \
				(vloadableClass*) vobjectGetDefaultClass())
#define vobjectCopy(o,t) \
    vloadableCopy(vobjectGetLoadable(o), vobjectGetLoadable(t))
#define vobjectCopyCommon(o,t) \
    vloadableCopyCommon(vobjectGetLoadable(o), vobjectGetLoadable(t))

#define vobjectLoad(r) \
    ((vobject *) \
     vloadableLoadOfSubclass(r, \
			     (vloadableClass*) vobjectGetDefaultClass()))
#define vobjectLoadInit(o,r) \
    vloadableLoadInitOfSubclass(vobjectGetLoadable(o), (r), \
				(vloadableClass*) vobjectGetDefaultClass())

#define vobjectStore(o,r) \
    vloadableStore(vobjectGetLoadable(o), (r))

#define vobjectDump(o,f) \
    vloadableDump(vobjectGetLoadable(o), (f))

#define vobjectGetTag(o) \
    vloadableGetTag(vobjectGetLoadable(o))
#define vobjectSetTag(o,t) \
    vloadableSetTag(vobjectGetLoadable(o), (t))

#define vobjectGetSize(o) \
    vinstanceGetSize(vobjectGetInstance(o))
#define vobjectIsKindOf(o,c) \
    vinstanceIsKindOf(vobjectGetInstance(o), (c))

#define vobjectInstallObserver(o,b) \
    vobservableInstallObserver(vobjectGetObservable(o), (b))
#define vobjectUninstallObserver(o,b) \
    vobservableUninstallObserver(vobjectGetObservable(o), (b))
#define vobjectAnnounce(o,c) \
    vobservableAnnounce(vobjectGetObservable(o), (c))

/*
 * attributed objects (deprecated)
 */

#define vobjectGetAttributedClass(o) \
    vobjectGetClass(o)

/*
 * exceptions
 */

#define vobjectGetUndefinedClassExceptionClass() \
    vclassGetNotFoundExceptionClass()
#define vobjectGetUndefinedClassException() \
    vclassGetNotFoundException()
#define vobjectGetUndefinedClassExceptionName(e) \
    vclassGetNotFoundExceptionName(e)
#define vobjectUndefinedClassExceptionNAME \
    vclassNotFoundExceptionNAME

#define vobjectGetUnnamedClassExceptionClass() \
    vclassGetUnnamedExceptionClass()
#define vobjectGetUnnamedClassException() \
    vclassGetUnnamedException()


/*
 * object lists
 */

#define vobjectGetListObject(l)     vportBASE_OBJECT(l, object)
#define vobjectGetListLoadable(l)   vobjectGetLoadable(vobjectGetListObject(l))
#define vobjectGetListInstance(l)   vloadableGetInstance(vobjectGetListLoadable(l))

#define vobjectCreateListOfClass(c) \
    ((vobjectList*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vobjectCreateList() \
    vobjectCreateListOfClass(vobjectGetDefaultListClass())
#define vobjectInitListOfClass(l, c) \
    vobjectInitOfClass(vobjectGetListObject(l), (vobjectClass*)(c))
#define vobjectInitList(l) \
    vobjectInitListOfClass(l, vobjectGetDefaultListClass())
#define vobjectDestroyList(l) \
    vobjectDestroy(vobjectGetListObject(l))

#define vobjectCloneList(o) \
    ((vobjectList *) \
     vloadableCloneOfSubclass(vobjectGetListLoadable(o), \
			      (vloadableClass*) vobjectGetDefaultListClass()))
#define vobjectCopyInitList(o,t) \
    vloadableCopyInitOfSubclass(vobjectGetListLoadable(o), \
				vobjectGetListLoadable(t), \
				(vloadableClass*) vobjectGetDefaultListClass())

#define vobjectLoadList(r) \
    ((vobjectList *) \
     vloadableLoadOfSubclass(r, \
			     (vloadableClass*) vobjectGetDefaultListClass()))
#define vobjectLoadInitList(o,r) \
    vloadableLoadInitOfSubclass(vobjectGetListLoadable(o), (r), \
				(vloadableClass*) vobjectGetDefaultListClass())

#define vobjectGetListClass(l) \
    ((vobjectListClass*)vobjectGetClass(vobjectGetListObject(l)))
#define vobjectGetListObjects(l)  ((l)->objects)
#define vobjectGetListStop(l)     ((l)->stop)
#define vobjectGetListCount(l)    ((l)->stop-(l)->objects)

#if (!vdebugDEBUG)
#define vobjectGetListAt(l, n)    ((l)->objects[n])
#endif

/*
 * object child iterators
 */

#define vobjectGetChildIteratorGroupIterator(i) \
    vportBASE_OBJECT(i, super)
#define vobjectGetChildIteratorIterator(i) \
    viteratorGetGroupIterator(vobjectGetChildIteratorGroupIterator(i))
#define vobjectGetChildIteratorClass(i) \
    ((vobjectChildIteratorClass *) \
     viteratorGetClass(vobjectGetChildIteratorIterator(i)))

#define vobjectDestroyChildIterator(i) \
    viteratorDestroyGroup(vobjectGetChildIteratorGroupIterator(i))
#define vobjectNextChildIterator(i) \
    viteratorNext(vobjectGetChildIteratorIterator(i))
#define vobjectGetChildIteratorChild(i) \
    ((vobject *) viteratorGetElement(vobjectGetChildIteratorIterator(i)))
#define vobjectGetChildIteratorDepth(i) \
    ((i)->depth)


#define vobjectGetPartialChildIteratorIterator(i) \
    vportBASE_OBJECT(i, super)
#define vobjectGetPartialChildIteratorClass(i) \
    ((vobjectPartialChildIteratorClass *) \
     viteratorGetClass(vobjectGetPartialChildIteratorIterator(i)))

#define vobjectGetPartialChildIteratorParent(i) \
   ((vobject *) viteratorGetStarter(vobjectGetPartialChildIteratorIterator(i)))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * objects
 */

#define vobjectSetAttribute(o, a, v) \
    vclassSend(vobjectGetAttributedClass(o), vobjectSET_ATTRIBUTE, (o, a, v))
#define vobjectSetAllAttributes(o, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectSET_ALL_ATTRIBUTES, (o, d))
#define vobjectGetAttribute(o, a) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_ATTRIBUTE, (o, a))
#define vobjectGetAllAttributes(o, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_ALL_ATTRIBUTES, (o, d))
#define vobjectGetContextAttributes(o, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_CONTEXT_ATTRIBUTES, \
	       (o, d))
#define vobjectSetIDAttribute(o, a, v) \
    vclassSend(vobjectGetAttributedClass(o), vobjectSET_ID_ATTRIBUTE, \
	       (o, a, v))
#define vobjectGetIDAttribute(o, a) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_ID_ATTRIBUTE, (o, a))
#define vobjectChangedParentAttribute(o, a, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectCHANGED_PARENT_ATTRIBUTE, \
	       (o, a, d))
#define vobjectChangedAttribute(o, a, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectCHANGED_ATTRIBUTE, \
	       (o, a, d))
#define vobjectChangedChildAttribute(o, a, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectCHANGED_CHILD_ATTRIBUTE, \
	       (o, a, d))
#define vobjectUpdateAttribute(o, a) \
    vclassSend(vobjectGetAttributedClass(o), vobjectUPDATE_ATTRIBUTE, (o, a))
#define vobjectUpdateAllAttributes(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectUPDATE_ALL_ATTRIBUTES, (o))
#define vobjectIssueSelector(o, n, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectISSUE_SELECTOR, (o, n, d))
#define vobjectQuerySelector(o, n, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectQUERY_SELECTOR, (o, n, d))
#define vobjectBindAttribute(o, a, c) \
    vclassSend(vobjectGetAttributedClass(o), vobjectBIND_ATTRIBUTE, (o, a, c))
#define vobjectBindAllAttributes(o, n, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectBIND_ALL_ATTRIBUTES, \
	       (o, n, d))
#define vobjectPropagateChangeDict(o, a, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectPROPAGATE_CHANGE_DICT, \
	       (o, a, d))
#define vobjectFilterChangeDict(o, a, d) \
    vclassSend(vobjectGetAttributedClass(o), vobjectFILTER_CHANGE_DICT, \
	       (o, a, d))
#define vobjectHelp(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectHELP, (o))
#define vobjectDisplayHelp(o, r) \
    vclassSend(vobjectGetAttributedClass(o), vobjectDISPLAY_HELP, (o, r))
#define vobjectGetHelpParent(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_HELP_PARENT, (o))
#define vobjectBuildHelpContext(o, c) \
    vclassSend(vobjectGetAttributedClass(o), vobjectBUILD_HELP_CONTEXT, \
	       (o, c))
#define vobjectGetSpace(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_SPACE, (o))
#define vobjectMakeSpace(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectMAKE_SPACE, (o))
#define vobjectGetParent(o) \
    vclassSend(vobjectGetAttributedClass(o), vobjectGET_PARENT, (o))
#define _vobjectSendBuildChildIterator(o, i) \
    vclassSend(vobjectGetAttributedClass(o), vobjectBUILD_CHILD_ITERATOR, \
	       (o, i))

#define vobjectAnnounceToParent(o, c) \
    vclassSend(vobjectGetAttributedClass(o), vobjectANNOUNCE_TO_PARENT, (o, c))
#define vobjectAnnounceToChildren(o, c) \
    vclassSend(vobjectGetAttributedClass(o), vobjectANNOUNCE_TO_CHILDREN, \
	       (o, c))

/*
 * object lists
 */

#define vobjectCopyList(l, t) \
    vclassSend(vobjectGetListClass(l), vobjectCOPY, (l, t))
#define vobjectStoreList(l, r) \
    vclassSend(vobjectGetListClass(l), vobjectSTORE, (l, r))
#define vobjectChangedListParentAttribute(l, a, d) \
    vclassSend(vobjectGetListClass(l), vobjectCHANGED_PARENT_ATTRIBUTE, \
	       (l, a, d))
#define vobjectChangedListAttribute(l, a, d) \
    vclassSend(vobjectGetListClass(l), vobjectCHANGED_ATTRIBUTE, (l, a, d))
#define vobjectChangedListChildAttribute(l, a, d) \
    vclassSend(vobjectGetListClass(l), vobjectCHANGED_CHILD_ATTRIBUTE, \
	       (l, a, d))
#define vobjectUpdateListAttribute(l, a) \
    vclassSend(vobjectGetListClass(l), vobjectUPDATE_ATTRIBUTE, (l, a))
#define vobjectUpdateAllListAttributes(l) \
    vclassSend(vobjectGetListClass(l), vobjectUPDATE_ALL_ATTRIBUTES, (l))
#define vobjectAppendList(l, o) \
    vclassSend(vobjectGetListClass(l), vobjectAPPEND_LIST, (l, o))
#define vobjectRemoveListIndex(l, i) \
    vclassSend(vobjectGetListClass(l), vobjectREMOVE_LIST_INDEX, (l, i))
#define vobjectDeleteListIndex(l, i) \
    ((void) vobjectRemoveListIndex(l, i))
#define vobjectSetListIndexIndex(l, oi, i) \
    vclassSend(vobjectGetListClass(l), vobjectSET_LIST_INDEX_INDEX, (l, oi, i))
#define vobjectReplaceListAt(l, i, o) \
    vclassSend(vobjectGetListClass(l), vobjectREPLACE_LIST_AT, (l, i, o))
#define vobjectSetListAt(l, i, o) \
    ((void) vobjectReplaceListAt(l, i, o))

/*
 * object child iterators
 */

#define _vobjectSendSetPartialChildIteratorSource(i, s) \
    vclassSend(vobjectGetPartialChildIteratorClass(i), \
	       vobjectSET_PARTIAL_CHILD_ITERATOR_SOURCE, (i, s))

#define _vobjectSendNextPartialChildIterator(i) \
    vclassSend(vobjectGetPartialChildIteratorClass(i), \
	       vobjectNEXT_PARTIAL_CHILD_ITERATOR, (i))

#define _vobjectSendGetPartialChildIteratorElement(i) \
    vclassSend(vobjectGetPartialChildIteratorClass(i), \
	       vobjectGET_PARTIAL_CHILD_ITERATOR_ELEMENT, (i))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vobjectHEADER
#define vobjectHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vobjectINCLUDED */

