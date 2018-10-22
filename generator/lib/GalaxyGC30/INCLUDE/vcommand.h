/* $Id: vcommand.h,v 1.22 1997/09/19 22:27:54 robert Exp $ */

/************************************************************

    vcommand.h

    C Interface file for the Command Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcommandINCLUDED
#define vcommandINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED
#include vstddefHEADER
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

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
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

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * commands
 */

typedef struct vcommand             vcommand;
typedef struct vcommandClass        vcommandClass;
typedef struct vcommandTemplate	    vcommandTemplate;

struct vcommandTemplate {
    const char                     *name;
    vcommandClass		   *clas;
};

typedef vcommandTemplate	    vcommandInitializer;


/*
 * function commands
 */

typedef struct vcommandFunction         vcommandFunction;
typedef struct vcommandFunctionClass    vcommandFunctionClass;
typedef struct vcommandFunctionTemplate vcommandFunctionTemplate;

typedef int (*vcommandFunc)(
    vcommandFunction               *command,
    vdict                          *attr2value
    );

struct vcommandFunctionTemplate {
    const char                     *name;
    vcommandFunc                    issueFunc, queryFunc;
};

typedef vcommandFunctionTemplate	vcommandFunctionInitializer;


/*
 * selector commands
 */

#if 0
/* Already forward declared in vobject.h: */
typedef struct vcommandSelector         vcommandSelector;
typedef struct vcommandSelectorClass    vcommandSelectorClass;
#endif

typedef struct vcommandSelectorTemplate vcommandSelectorTemplate;

struct vcommandSelectorTemplate {
    const char                     *name;
    int                             value;
};

typedef vcommandSelectorTemplate	vcommandSelectorInitializer;


/*
 * synthetic commands
 */

typedef struct vcommandSynthetic             vcommandSynthetic;
typedef struct vcommandSyntheticTagIterator  vcommandSyntheticTagIterator;
typedef struct vcommandSyntheticPairIterator vcommandSyntheticPairIterator;
typedef struct vcommandSyntheticClass        vcommandSyntheticClass;

typedef vcommandSynthetic           vcommandSyntheticName;
typedef vcommandSyntheticClass      vcommandSyntheticNameClass;

/*
 * command keys
 */

typedef struct vcommandKey          vcommandKey;
typedef struct vcommandKeyIterator  vcommandKeyIterator;

/*
 * command spaces
 */

#if 0
/* Already forward declared in vobject.h: */
typedef struct vcommandSpace	    vcommandSpace;
#endif

typedef struct vcommandSpaceClass         vcommandSpaceClass;
typedef struct vcommandSpaceOwnerIterator vcommandSpaceOwnerIterator;
typedef struct vcommandSpaceIterator      vcommandSpaceIterator;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcommandStartup(void);


/*
 * commands
 */

vcommandClass *vcommandGetDefaultClass(
    void
    );

vcommandClass *vcommandGetResourceClass(
    vresource                       resource
    );

vcommand *vcommandCreateOfClass(
    vcommandClass                  *clas
    );

void vcommandInitOfClass(
    vcommand                       *command,
    vcommandClass                  *clas
    );

void vcommandDestroy(
    vcommand                       *command
    );

vcommand *vcommandLoad(
    vresource                       resource
    );

void vcommandLoadInit(
    vcommand                       *command,
    vresource                       resource
    );

void vcommandStore(
    vcommand                       *command,
    vresource                       resource
    );

int vcommandIssue(
    vcommand                       *command,
    vdict                          *attr2value
    );

int vcommandQuery(
    vcommand                       *command,
    vdict                          *attr2value
    );

vinstance *vcommandGetInstance(
    vcommand                       *command
    );

vcommandClass *vcommandGetClass(
    vcommand                       *command
    );

void vcommandDestroyDict(
    vdict                          *dict
    );

vdict *vcommandLoadDict(
    vresource                       resource
    );

void vcommandStoreDict(
    vdict                          *dict,
    vresource                       resource
    );

vdict *vcommandCreateDictTemplates(
    const vcommandTemplate	   *templates,
    size_t                          count
    );

void vcommandStoreDictTemplates(
    vdict                          *dict,
    const vcommandTemplate	   *templates,
    size_t                          count
    );

/*
 * function commands
 */

vcommandFunctionClass *vcommandGetDefaultFunctionClass(
    void
    );

vcommandFunction *vcommandCreateFunctionOfClass(
    vcommandFunctionClass          *clas
    );

vcommandFunction *vcommandCreateFunction(
    void
    );

void vcommandInitFunctionOfClass(
    vcommandFunction               *command,
    vcommandFunctionClass          *clas
    );

void vcommandInitFunction(
    vcommandFunction               *command
    );

void vcommandSetFunctionIssue(
    vcommandFunction               *command,
    vcommandFunc                    issueFunc
    );

void vcommandSetFunctionQuery(
    vcommandFunction               *command,
    vcommandFunc                    queryFunc
    );

vcommand *vcommandGetFunctionCommand(
    vcommandFunction               *command
    );

vcommandFunc vcommandGetFunctionIssue(
    vcommandFunction               *command
    );

vcommandFunc vcommandGetFunctionQuery(
    vcommandFunction               *command
    );

vdict *vcommandCreateDictOfClassFunctionTemplates(
    vcommandFunctionClass          *clas,
    const vcommandFunctionTemplate *templates,
    size_t                          count
    );

vdict *vcommandCreateDictFunctionTemplates(
    const vcommandFunctionTemplate *templates,
    size_t                          count
    );

void vcommandStoreDictOfClassFunctionTemplates(
    vdict                          *dict,
    vcommandFunctionClass          *clas,
    const vcommandFunctionTemplate *templates,
    size_t                          count
    );

void vcommandStoreDictFunctionTemplates(
    vdict                          *dict,
    const vcommandFunctionTemplate *templates,
    size_t                          count
    );

/*
 * selector commands
 */

vcommandSelectorClass *vcommandGetDefaultSelectorClass(
    void
    );

vcommandSelector *vcommandCreateSelectorOfClass(
    vcommandSelectorClass          *clas
    );

void vcommandInitSelectorOfClass(
    vcommandSelector               *command,
    vcommandSelectorClass          *clas
    );

void vcommandSetSelector(
    vcommandSelector               *command,
    int                             value
    );

vcommand *vcommandGetSelectorCommand(
    vcommandSelector               *command
    );

int vcommandGetSelector(
    vcommandSelector               *command
    );

vdict *vcommandCreateDictOfClassSelectorTemplates(
    vcommandSelectorClass          *clas,
    const vcommandSelectorTemplate *templates,
    size_t                          count
    );

void vcommandStoreDictOfClassSelectorTemplates(
    vdict                          *dict,
    vcommandSelectorClass          *clas,
    const vcommandSelectorTemplate *templates,
    size_t                          count
    );

/*
 * synthetic commands
 */

vcommandSyntheticClass *vcommandGetDefaultSyntheticClass(
    void
    );

vcommandSyntheticNameClass *vcommandGetDefaultSyntheticNameClass(
    void
    );

vcommandSynthetic *vcommandCreateSyntheticOfClass(
    vcommandSyntheticClass         *clas
    );

vcommandSynthetic *vcommandCreateSynthetic(
    void
    );

vcommandSyntheticName *vcommandCreateSyntheticName(
    void
    );

void vcommandInitSyntheticOfClass(
    vcommandSynthetic              *command,
    vcommandSyntheticClass         *clas
    );

void vcommandInitSynthetic(
    vcommandSynthetic              *command
    );

void vcommandInitSyntheticName(
    vcommandSyntheticName          *command
    );

void vcommandAddSyntheticTag(
    vcommandSynthetic              *command,
    const vname                    *tag
    );

void vcommandAddSyntheticTags(
    vcommandSynthetic              *command,
    const vname                   **tags,
    int                             count
    );

void vcommandRemoveSyntheticTag(
    vcommandSynthetic              *command,
    const vname                    *tag
    );

void vcommandRemoveSyntheticTags(
    vcommandSynthetic              *command,
    const vname                   **tags,
    int                             count
    );

void vcommandAddSyntheticPair(
    vcommandSynthetic              *command,
    const vname                    *attr,
    const void                     *value
    );

void vcommandAddSyntheticPairs(
    vcommandSynthetic              *command,
    const vname                   **attrs,
    const void                    **values,
    int                             count
    );

void vcommandRemoveSyntheticPair(
    vcommandSynthetic              *command,
    const vname                    *attr
    );

void vcommandRemoveSyntheticPairs(
    vcommandSynthetic              *command,
    const vname                   **attrs,
    int                             count
    );

vcommand *vcommandGetSyntheticCommand(
    vcommandSynthetic              *command
    );

void vcommandInitSyntheticTagIterator(
    vcommandSyntheticTagIterator   *iterator,
    vcommandSynthetic              *command
    );

int vcommandNextSyntheticTagIterator(
    vcommandSyntheticTagIterator   *iterator
    );

void vcommandDestroySyntheticTagIterator(
    vcommandSyntheticTagIterator   *iterator
    );

const vname *vcommandGetSyntheticTagIteratorTag(
    vcommandSyntheticTagIterator   *iterator
    );

void vcommandInitSyntheticPairIterator(
    vcommandSyntheticPairIterator  *iterator,
    vcommandSynthetic              *command
    );

int vcommandNextSyntheticPairIterator(
    vcommandSyntheticPairIterator  *iterator
    );

void vcommandDestroySyntheticPairIterator(
    vcommandSyntheticPairIterator  *iterator
    );

const vname *vcommandGetSyntheticPairIteratorAttr(
    vcommandSyntheticPairIterator   *iterator
    );

const void *vcommandGetSyntheticPairIteratorValue(
    vcommandSyntheticPairIterator   *iterator
    );

/*
 * command keys
 */

vcommandKey *vcommandCreateKey(
    void
    );

void vcommandInitKey(
    vcommandKey                    *key
    );

void vcommandDestroyKey(
    vcommandKey                    *key
    );

vcommandKey *vcommandLoadKey(
    vresource                       resource
    );

void vcommandLoadInitKey(
    vcommandKey                    *key,
    vresource                       resource
    );

void vcommandStoreKey(
    vcommandKey                    *key,
    vresource                       resource
    );

void vcommandAddKeyStroke(
    vcommandKey                    *key,
    vkeyStroke                      stroke
    );

void vcommandAddKeyStrokes(
    vcommandKey                    *key,
    const vkeyStroke               *strokes,
    int                             count
    );

void vcommandRemoveKeyStroke(
    vcommandKey                    *key,
    vkeyStroke                      stroke
    );

void vcommandRemoveKeyStrokes(
    vcommandKey                    *key,
    const vkeyStroke               *strokes,
    int                             count
    );

void vcommandInitKeyIterator(
    vcommandKeyIterator            *iterator,
    vcommandKey                    *key
    );

int vcommandNextKeyIterator(
    vcommandKeyIterator            *iterator
    );

void vcommandDestroyKeyIterator(
    vcommandKeyIterator            *iterator
    );

vkeyStroke vcommandGetKeyIteratorStroke(
    vcommandKeyIterator            *iterator
    );

void vcommandMapKey(
    vcommandKey                    *key,
    const void                     *value,
    vdict                          *dict
    );

void vcommandDestroyKeyDict(
    vdict                          *dict
    );

vdict *vcommandLoadKeyDict(
    vresource                       resource
    );

void vcommandStoreKeyDict(
    vdict                          *dict,
    vresource                       resource
    );

void vcommandMapKeyDict(
    vdict                          *keys,
    vdict                          *map
    );

/*
 * command spaces
 */

vcommandSpaceClass *vcommandGetDefaultSpaceClass(
    void
    );

vcommandSpace *vcommandCreateSpaceOfClass(
    vcommandSpaceClass             *clas
    );

vcommandSpace *vcommandCreateSpace(
    void
    );

vcommandSpace *vcommandCloneSpace(
    vcommandSpace                  *space
    );

void vcommandInitSpaceOfClass(
    vcommandSpace                  *space,
    vcommandSpaceClass             *clas
    );

void vcommandInitSpace(
    vcommandSpace                  *space
    );

void vcommandDestroySpace(
    vcommandSpace                  *space
    );

void vcommandCopySpace(
    vcommandSpace                  *space,
    vcommandSpace                  *target
    );

void vcommandCopyInitSpace(
    vcommandSpace                  *space,
    vcommandSpace                  *target
    );

vcommandSpace *vcommandLoadSpace(
    vresource                       resource
    );

void vcommandLoadInitSpace(
    vcommandSpace                  *space,
    vresource                       resource
    );

void vcommandStoreSpace(
    vcommandSpace                  *space,
    vresource                       resource
    );

void vcommandAddSpaceOwner(
    vcommandSpace                  *space,
    vobjectAttributed              *owner
    );

void vcommandRemoveSpaceOwner(
    vcommandSpace                  *space,
    vobjectAttributed              *owner
    );

void vcommandAddSpaceDict(
    vcommandSpace                  *space,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vcommandAddSpaceDictOwned(
    vcommandSpace                  *space,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vcommandRemoveSpaceDict(
    vcommandSpace                  *space,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vcommandReplaceSpaceDict(
    vcommandSpace                  *space,
    const vname                    *attr,
    vdict                          *tag2valueOld,
    vdict                          *tag2valueNew
    );

vobject *vcommandGetSpaceObject(
    vcommandSpace                  *space
    );

vloadable *vcommandGetSpaceLoadable(
    vcommandSpace                  *space
    );

vcommandSpaceClass *vcommandGetSpaceClass(
    vcommandSpace                  *space
    );

void vcommandInitSpaceOwnerIterator(
    vcommandSpaceOwnerIterator     *iterator,
    vcommandSpace                  *space
    );

int vcommandNextSpaceOwnerIterator(
    vcommandSpaceOwnerIterator     *iterator
    );

void vcommandDestroySpaceOwnerIterator(
    vcommandSpaceOwnerIterator     *iterator
    );

vobjectAttributed *vcommandGetSpaceOwnerIteratorOwner(
    vcommandSpaceOwnerIterator          *iterator
    );

void vcommandInitSpaceIterator(
    vcommandSpaceIterator          *iterator,
    vcommandSpace                  *space
    );

int vcommandNextSpaceIterator(
    vcommandSpaceIterator          *iterator
    );

void vcommandDestroySpaceIterator(
    vcommandSpaceIterator          *iterator
    );

const vname *vcommandGetSpaceIteratorAttr(
    vcommandSpaceIterator          *iterator
    );

vdict *vcommandGetSpaceIteratorDict(
    vcommandSpaceIterator          *iterator
    );

const void *vcommandBindSpaceAttribute(
    vcommandSpace                  *space,
    const vname                    *attr,
    const vname                    *tag
    );

void vcommandBindAllSpaceAttributes(
    vcommandSpace                  *space,
    const vname                    *tag,
    vdict                          *attr2value
    );

vdict *vcommandFilterSpaceChangeDict(
    vcommandSpace                  *space,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vcommandMapSpaceKeys(
    vcommandSpace                  *space,
    vdict                          *map
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS  * * * * * * * * * *
 */

/*
 * command spaces
 */

#define _vcommandSTATIC_OWNER_MAX   2
#define _vcommandSTATIC_DICT_MAX    4

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * commands
 */

struct vcommand {
    vinstance                       instance;
};

#define vcommandINIT                vinstanceINIT
#define vcommandDESTROY             vinstanceDESTROY

#define vcommandCLASS(SUPER, COMMAND)                                         \
    vinstanceCLASS(SUPER, COMMAND);                                           \
    vclassMETHOD(vcommandLOAD_INIT, (COMMAND *command, vresource resource));  \
    vclassMETHOD(vcommandSTORE, (COMMAND *command, vresource resource));      \
    vclassMETHOD_RET(vcommandISSUE, int,                                      \
		     (COMMAND *command, vdict *attr2value));                  \
    vclassMETHOD_RET(vcommandQUERY, int,                                      \
		     (COMMAND *command, vdict *attr2value)) 

struct vcommandClass {
    vcommandCLASS(vcommandClass, vcommand);
};

/*
 * function commands
 */

struct vcommandFunction {
    vcommand                        command;
    vcommandFunc                    issueFunc, queryFunc;
};

#define vcommandFUNCTION_CLASS(SUPER, COMMAND)                                \
    vcommandCLASS(SUPER, COMMAND);                                            \
    vclassMETHOD(vcommandSET_FUNCTION_ISSUE,                                  \
		 (COMMAND *command, vcommandFunc issueFunc));                 \
    vclassMETHOD(vcommandSET_FUNCTION_QUERY,                                  \
		 (COMMAND *command, vcommandFunc queryFunc))

struct vcommandFunctionClass {
    vcommandFUNCTION_CLASS(vcommandFunctionClass, vcommandFunction);
};

/*
 * selector commands
 */

struct vcommandSelector {
    vcommand                        command;
    int                             value;
};

#define vcommandSELECTOR_CLASS(SUPER, COMMAND)                                \
    vcommandCLASS(SUPER, COMMAND);                                            \
    vclassMETHOD(vcommandSET_SELECTOR, (COMMAND *command, int value))

struct vcommandSelectorClass {
    vcommandSELECTOR_CLASS(vcommandSelectorClass, vcommandSelector);
};


vportALIAS(vobjectCommand, vcommandSelector)


/*
 * synthetic commands
 */

typedef struct _vcommandPair        _vcommandPair;

struct _vcommandPair {
    const vname                    *attr;
    const void                     *value;
};

struct vcommandSynthetic {
    vcommand                        command;
    short                           tagCount, pairCount;
    union {
	const vname                *tag;
	const vname               **tags;
    } ut;
    union {
	_vcommandPair               pair;
	_vcommandPair              *pairs;
    } up;
};

struct vcommandSyntheticTagIterator {
    const vname                   **scan, **stop;
};

struct vcommandSyntheticPairIterator {
    _vcommandPair                  *scan, *stop;
};

#define vcommandSYNTHETIC_CLASS(SUPER, COMMAND)                               \
    vcommandCLASS(SUPER, COMMAND);                                            \
    vclassMETHOD(vcommandADD_SYNTHETIC_TAGS,                                  \
		 (COMMAND *command, const vname **tags, int count));          \
    vclassMETHOD(vcommandREMOVE_SYNTHETIC_TAGS,                               \
		 (COMMAND *command, const vname **tags, int count));          \
    vclassMETHOD(vcommandADD_SYNTHETIC_PAIRS,                                 \
		 (COMMAND *command, const vname **attrs, const void **values, \
		  int count));                                                \
    vclassMETHOD(vcommandREMOVE_SYNTHETIC_PAIRS,                              \
		 (COMMAND *command, const vname **attrs, int count))

struct vcommandSyntheticClass {
    vcommandSYNTHETIC_CLASS(vcommandSyntheticClass, vcommandSynthetic);
};


vportALIAS(vcommandSyntheticName, vcommandSynthetic)


/*
 * command keys
 */

struct vcommandKey {
    short                           count;
    union {
	vkeyStroke                  stroke;
	vkeyStroke                 *strokes;
    } u;
};

struct vcommandKeyIterator {
    vkeyStroke                     *scan, *stop;
};

/*
 * command spaces
 */

typedef struct _vcommandDict        _vcommandDict;

struct _vcommandDict {
    const vname                    *attr;
    vdict                          *tag2value;
    short                           flags;
};

struct vcommandSpace {
    vobject                         object;
    vobjectAttributed             **owners, **ownerNext, **ownerMax;
    _vcommandDict                  *dicts, *dictNext, *dictMax;
    vobjectAttributed              *staticOwners[_vcommandSTATIC_OWNER_MAX];
    _vcommandDict                   staticDicts[_vcommandSTATIC_DICT_MAX];
};

struct vcommandSpaceOwnerIterator {
    vobjectAttributed             **scan, **stop;
};

struct vcommandSpaceIterator {
    _vcommandDict                  *scan, *stop;
};

#define vcommandSPACE_CLASS(SUPER, SPACE)                                     \
    vobjectCLASS(SUPER, SPACE);                                               \
    vclassMETHOD(vcommandADD_SPACE_OWNER,				      \
		 (SPACE *space, vobjectAttributed *owner));		      \
    vclassMETHOD(vcommandREMOVE_SPACE_OWNER,				      \
		 (SPACE *space, vobjectAttributed *owner));		      \
    vclassMETHOD(vcommandADD_SPACE_DICT,                                      \
		 (SPACE *space, const vname *attr, vdict *tag2value));        \
    vclassMETHOD(vcommandREMOVE_SPACE_DICT,                                   \
		 (SPACE *space, const vname *attr, vdict *tag2value));        \
    vclassMETHOD(vcommandREPLACE_SPACE_DICT,                                  \
		 (SPACE *space, const vname *attr, vdict *tag2valueOld,       \
		  vdict *tag2valueNew))

struct vcommandSpaceClass {
    vcommandSPACE_CLASS(vcommandSpaceClass, vcommandSpace);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

/*
 * commands
 */

vcommand *_vcommandLoadDebug(
    vresource                       resource,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

/*
 * command keys
 */

vcommandKey *_vcommandCreateKeyDebug(
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vcommandKey *_vcommandLoadKeyDebug(
    vresource                       resource,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * commands
 */

#define vcommandGetInstance(c)      vportBASE_OBJECT(c, instance)

#if (vdebugDEBUG)
#define vcommandLoad(r) \
    _vcommandLoadDebug(r, vmemTAG, __FILE__, __LINE__)
#endif

#define vcommandCreateOfClass(c) \
    ((vcommand*)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vcommandInitOfClass(c, cl) \
    vinstanceInitOfClass(vcommandGetInstance(c), (vinstanceClass*)(cl))
#define vcommandDestroy(c) \
    vinstanceDestroy(vcommandGetInstance(c))

#define vcommandGetClass(c) \
    ((vcommandClass*)vinstanceGetClass(vcommandGetInstance(c)))

/*
 * function commands
 */

#define vcommandGetFunctionCommand(c) vportBASE_OBJECT(c, command)

#define vcommandCreateFunctionOfClass(c) \
    ((vcommandFunction*)vcommandCreateOfClass((vcommandClass*)(c)))
#define vcommandCreateFunction() \
    vcommandCreateFunctionOfClass(vcommandGetDefaultFunctionClass())
#define vcommandInitFunctionOfClass(c, cl) \
    vcommandInitOfClass(vcommandGetFunctionCommand(c), (vcommandClass*)(cl))
#define vcommandInitFunction(c) \
    vcommandInitFunctionOfClass(c, vcommandGetDefaultFunctionClass())

#define vcommandGetFunctionIssue(c) ((c)->issueFunc)
#define vcommandGetFunctionQuery(c) ((c)->queryFunc)

#define vcommandCreateDictFunctionTemplates(t, n) \
    vcommandCreateDictOfClassFunctionTemplates( \
				       vcommandGetDefaultFunctionClass(), t, n)
#define vcommandStoreDictFunctionTemplates(d, t, n) \
    vcommandStoreDictOfClassFunctionTemplates(d, \
				       vcommandGetDefaultFunctionClass(), t, n)

/*
 * selector commands
 */

#define vcommandGetSelectorCommand(c) vportBASE_OBJECT(c, command)

#define vcommandCreateSelectorOfClass(c) \
    ((vcommandSelector*)vcommandCreateOfClass((vcommandClass*)(c)))
#define vcommandInitSelectorOfClass(c, cl) \
    vcommandInitOfClass(vcommandGetSelectorCommand(c), (vcommandClass*)(cl))

#define vcommandGetSelector(c)    ((c)->value)

/*
 * synthetic commands
 */

#define vcommandGetSyntheticCommand(c) vportBASE_OBJECT(c, command)

#define vcommandCreateSyntheticOfClass(c) \
    ((vcommandSynthetic*)vcommandCreateOfClass((vcommandClass*)(c)))
#define vcommandCreateSynthetic() \
    vcommandCreateSyntheticOfClass(vcommandGetDefaultSyntheticClass())
#define vcommandCreateSyntheticName() \
    vcommandCreateSyntheticOfClass(vcommandGetDefaultSyntheticNameClass())
#define vcommandInitSyntheticOfClass(c, cl) \
    vcommandInitOfClass(vcommandGetSyntheticCommand(c), (vcommandClass*)(cl))
#define vcommandInitSynthetic(c) \
    vcommandInitSyntheticOfClass(c, vcommandGetDefaultSyntheticClass())
#define vcommandInitSyntheticName(c) \
    vcommandInitSyntheticOfClass(c, vcommandGetDefaultSyntheticNameClass())

#define vcommandNextSyntheticTagIterator(i)    (--(i)->scan>=(i)->stop)
#define vcommandDestroySyntheticTagIterator(i)
#define vcommandGetSyntheticTagIteratorTag(i)   (*(i)->scan)
#define vcommandNextSyntheticPairIterator(i)   (--(i)->scan>=(i)->stop)
#define vcommandDestroySyntheticPairIterator(i)
#define vcommandGetSyntheticPairIteratorAttr(i)  ((i)->scan->attr)
#define vcommandGetSyntheticPairIteratorValue(i) ((i)->scan->value)

/*
 * command keys
 */

#if (vdebugDEBUG)
#define vcommandCreateKey() \
    _vcommandCreateKeyDebug(vmemTAG, __FILE__, __LINE__)
#define vcommandLoadKey(r) \
    _vcommandLoadKeyDebug(r, vmemTAG, __FILE__, __LINE__)
#endif

#define vcommandNextKeyIterator(i)     (--(i)->scan>=(i)->stop)
#define vcommandDestroyKeyIterator(i)
#define vcommandGetKeyIteratorStroke(i) (*(i)->scan)

/*
 * command spaces
 */

#define vcommandGetSpaceObject(s)   vportBASE_OBJECT(s, object)
#define vcommandGetSpaceLoadable(s) \
     vobjectGetLoadable(vcommandGetSpaceObject(s))

#define vcommandCreateSpaceOfClass(c) \
    ((vcommandSpace*)vloadableCreateOfClass((vloadableClass*)(c)))
#define vcommandCreateSpace() \
    vcommandCreateSpaceOfClass(vcommandGetDefaultSpaceClass())
#define vcommandCloneSpace(s) \
    ((vcommandSpace*)vloadableClone(vcommandGetSpaceLoadable(s)))
#define vcommandInitSpaceOfClass(s, c) \
    vloadableInitOfClass(vcommandGetSpaceLoadable(s), (vloadableClass*)(c))
#define vcommandInitSpace(s) \
    vcommandInitSpaceOfClass(s, vcommandGetDefaultSpaceClass())
#define vcommandDestroySpace(s) \
    vloadableDestroy(vcommandGetSpaceLoadable(s))
#define vcommandCopySpace(s, t) \
    vloadableCopy(vcommandGetSpaceLoadable(s), vcommandGetSpaceLoadable(t))
#define vcommandStoreSpace(s, r) \
    vloadableStore(vcommandGetSpaceLoadable(s), r)

#define vcommandGetSpaceClass(s) \
    ((vcommandSpaceClass*)vloadableGetClass(vcommandGetSpaceLoadable(s)))

#define vcommandNextSpaceOwnerIterator(i)    (--(i)->scan>=(i)->stop)
#define vcommandDestroySpaceOwnerIterator(i)
#define vcommandGetSpaceOwnerIteratorOwner(i) (*(i)->scan)
#define vcommandNextSpaceIterator(i)         (--(i)->scan>=(i)->stop)
#define vcommandDestroySpaceIterator(i)
#define vcommandGetSpaceIteratorAttr(i)        ((i)->scan->attr)
#define vcommandGetSpaceIteratorDict(i)        ((i)->scan->tag2value)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * commands
 */

#define vcommandStore(c, r) \
    vclassSend(vcommandGetClass(c), vcommandSTORE, (c, r))
#define vcommandIssue(c, d) \
    vclassSend(vcommandGetClass(c), vcommandISSUE, (c, d))
#define vcommandQuery(c, d) \
    vclassSend(vcommandGetClass(c), vcommandQUERY, (c, d))

/*
 * function commands
 */

#define _vcommandGetFunctionClass(c) \
    ((vcommandFunctionClass*)vcommandGetClass(vcommandGetFunctionCommand(c)))
#define vcommandSetFunctionIssue(c, f) \
    vclassSend(_vcommandGetFunctionClass(c), vcommandSET_FUNCTION_ISSUE, \
	       (c, f))
#define vcommandSetFunctionQuery(c, f) \
    vclassSend(_vcommandGetFunctionClass(c), vcommandSET_FUNCTION_QUERY, \
	       (c, f))

/*
 * selector commands
 */

#define _vcommandGetSelectorClass(c) \
    ((vcommandSelectorClass*)vcommandGetClass(vcommandGetSelectorCommand(c)))
#define vcommandSetSelector(c, n) \
    vclassSend(_vcommandGetSelectorClass(c), vcommandSET_SELECTOR, (c, n))

/*
 * synthetic commands
 */

#define _vcommandGetSyntheticClass(c) \
    ((vcommandSyntheticClass*)vcommandGetClass(vcommandGetSyntheticCommand(c)))
#define vcommandAddSyntheticTags(c, i, n) \
    vclassSend(_vcommandGetSyntheticClass(c), vcommandADD_SYNTHETIC_TAGS, \
	       (c, i, n))
#define vcommandRemoveSyntheticTags(c, i, n) \
    vclassSend(_vcommandGetSyntheticClass(c), vcommandREMOVE_SYNTHETIC_TAGS, \
	       (c, i, n))
#define vcommandAddSyntheticPairs(c, k, v, n) \
    vclassSend(_vcommandGetSyntheticClass(c), vcommandADD_SYNTHETIC_PAIRS, \
	       (c, k, v, n))
#define vcommandRemoveSyntheticPairs(c, k, n) \
    vclassSend(_vcommandGetSyntheticClass(c), vcommandREMOVE_SYNTHETIC_PAIRS, \
	       (c, k, n))

/*
 * command spaces
 */

#define vcommandAddSpaceOwner(s, o) \
    vclassSend(vcommandGetSpaceClass(s), vcommandADD_SPACE_OWNER, (s, o))
#define vcommandRemoveSpaceOwner(s, o) \
    vclassSend(vcommandGetSpaceClass(s), vcommandREMOVE_SPACE_OWNER, (s, o))
#define vcommandAddSpaceDict(s, a, d) \
    vclassSend(vcommandGetSpaceClass(s), vcommandADD_SPACE_DICT, (s, a, d))
#define vcommandRemoveSpaceDict(s, a, d) \
    vclassSend(vcommandGetSpaceClass(s), vcommandREMOVE_SPACE_DICT, (s, a, d))
#define vcommandReplaceSpaceDict(s, a, od, nd) \
    vclassSend(vcommandGetSpaceClass(s), vcommandREPLACE_SPACE_DICT, \
	       (s, a, od, nd))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vcommandINCLUDED */

