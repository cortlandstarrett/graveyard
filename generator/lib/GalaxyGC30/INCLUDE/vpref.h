/* $Id: vpref.h,v 1.49 1997/06/27 17:08:31 gray Exp $ */

/************************************************************

    vpref.h

    C Interface file for the Preference Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vprefINCLUDED
#define vprefINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef	 vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vresolverINCLUDED
#include <vresolver.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * PUBLIC TYPES
 */

typedef struct vpref vpref;
typedef struct vprefClass vprefClass;

typedef struct vprefValue vprefValue;
typedef struct vprefValueClass vprefValueClass;

typedef struct vprefDict vprefDict;
typedef struct vprefDictClass vprefDictClass;

typedef struct vprefDictObserver vprefDictObserver;
typedef struct vprefDictObserverClass vprefDictObserverClass;

typedef struct vprefIterator vprefIterator;

#if (vportUSE_VMS_COMMAND_LINE)
typedef struct vprefVMSCLIqualifiers vprefVMSCLIqualifiers;
#endif

/*
 * PUBLIC FUNCTION PROTOTYPES
 */

void vprefStartup(void);


vprefClass *vprefGetDefaultClass(
    void
    );

vprefClass *vprefGetClass(
    vpref *pref
    );

vinstance *vprefGetInstance(
    vpref *pref
    );

vpref *vprefCreateOfClass(
    vprefClass *clas
    );

void vprefInitOfClass(
    vpref *pref,
    vprefClass *clas
    );

void vprefRelease(
    vpref *pref
    );			  

void vprefDestroy(
    vpref *pref
    );

void vprefRead(
    vpref *pref,
    vresource resource			
    );

void vprefWrite(
    vpref *pref,
    vresource resource
    );

vscrap *vprefGetScrap(
    vpref *pref
    );			  

vprefValueClass *vprefValueGetDefaultClass(
    void
    );

vprefValueClass *vprefValueGetClass(
    vprefValue *value
    );

vpref *vprefValueGetPref(
    vprefValue *value
    );

vprefValue *vprefValueCreate(
    vscrap *scrap		 
    );

vprefValue *vprefValueCreateOfClass(
    vprefValueClass *clas,
    vscrap *scrap			  
    );

void vprefValueInit(
    vprefValue *value,
    vscrap *scrap
    );

void vprefValueInitOfClass(
    vprefValue *value,
    vprefValueClass *clas,
    vscrap *scrap
    );

void vprefValueRelease(
    vprefValue *value
    );			  

void vprefValueDestroy(
    vprefValue *value
    );

void vprefValueRead(
    vprefValue *value,
    vresource resource			
    );

void vprefValueWrite(
    vprefValue *value,		
    vresource resource
    );

vscrap *vprefValueGetScrap(
    vprefValue *value
    );    		

vprefDictObserverClass *vprefDictObserverGetDefaultClass(
    void
    );

vprefDictObserverClass *vprefDictObserverGetClass(
    vprefDictObserver *obsvr						  
    );

vinstance *vprefDictObserverGetInstance(
    vprefDictObserver *obsvr
    );

vprefDictObserver *vprefDictObserverCreateOfClass(
    vprefDictObserverClass *clas
    );

void vprefDictObserverInitOfClass(
    vprefDictObserver *obsvr,
    vprefDictObserverClass *clas
    );

void vprefDictObserverDestroy(
    vprefDictObserver *obsvr
    );   

void vprefDictObserverObserveLoad(
    vprefDictObserver *obsvr,
    const vname *tag,
    const vpref *pref
    );
				  
void vprefDictObserverObserveStore(
    vprefDictObserver *obsvr,
    const vname *tag,
    const vpref *pref
    );

void vprefDictObserverSetData(
    vprefDictObserver *obsvr,
    void *data
    );

void *vprefDictObserverGetData(
    vprefDictObserver *obsvr
    );

vprefDictClass *vprefDictGetDefaultClass(
    void
    );

vprefDictClass *vprefDictGetClass(
    vprefDict *dict
    );

vpref *vprefDictGetPref(
    vprefDict *dict
    );

vprefDict *vprefDictCreate(
    void
    );

vprefDict *vprefDictCreateOfClass(
    vprefDictClass *clas
    );

void vprefDictInit(
    vprefDict *dict
    );

void vprefDictInitOfClass(
    vprefDict *dict,
    vprefDictClass *clas
    );

void vprefDictRelease(
    vprefDict *dict
    );			  

void vprefDictDestroy(
    vprefDict *dict
    );

void vprefDictRead(
    vprefDict *dict,
    vresource resource			
    );

void vprefDictWrite(
    vprefDict *dict,
    vresource resource
    );

vscrap *vprefDictGetScrap(
    vprefDict *dict
    );

void vprefDictStorePref(
    vprefDict *dict,
    const vname *tag,
    const vpref *pref
    );

const vpref *vprefDictLoadPref(
    vprefDict *dict,
    const vname *tag
    );

void vprefDictWritePref(
    vprefDict *dict,
    const vname *tag			   
    );

unsigned long vprefDictAddObserver(
    vprefDict *dict,
    vprefDictObserver *obsvr
    );

void vprefDictRemoveObserver(
    vprefDict *dict,
    unsigned long index
    );

/* 
 * Iterator Functions
 */

void vprefInitIterator(
    vprefIterator *iterator
    );
 
void vprefDictInitIterator(
    vprefIterator *iterator,
    vprefDict *dict
    );
 
int vprefNextIterator(
    vprefIterator *iterator
    );
 
void vprefDestroyIterator(
    vprefIterator *iterator
    );
 
const vname *vprefGetIteratorKey(
    vprefIterator *iterator
    );
 
const vpref *vprefGetIteratorPref(
    vprefIterator *iterator
    );

const vchar *vprefGetIteratorValue(
    vprefIterator *iter
    );

vresource vprefGetIteratorResource(
    vprefIterator *iter
    );

/*
 * Preference Database Functions
 */

vprefDict *vprefGetRootDict(
    void
    );

void vprefSetPreferences(
    vresource resource
    );

void vprefDictReadResource(
    vprefDict *dict,
    vresource resource
    );

void vprefSetArgs(
    int argc,
    char **argv
    );

void vprefReadArgs(
    void
    );

vbool vprefHaveArgs(
    void
    );

void vprefGetArgs(
    int *argc,
    const vchar ***argv
    );

void vprefGetRawArgs(
    int *argc,
    const vchar ***argv
    );

void vprefGetNativeArgs(
    int *argc,
    char ***argv
    );

vkeyModifiers vprefGetCommandKey(
    void
    );

void vprefReadEnvironment(
    void
    );

void vprefReadPlatformSpecificPrefs(
    void
    );

void vprefReadResolverPrefs(
    vresolver *resolver
    );

void vprefDump(
    FILE *stream
    );

/*
 * Convenience Functions
 */

void vprefStore(
    const vchar *key,
    const vchar *value
    );

void vprefStoreScribed(
    vscribe *key,
    vscribe *value
    );
   
void vprefStoreResource(
    const vchar *key,
    vresource resource
    );

void vprefStoreResourceScribed(
    vscribe *key,
    vresource resource
    );

void vprefStoreDict(
    const vchar *key,
    vprefDict *value
    );

void vprefStoreDictScribed(
    vscribe *key,
    vprefDict *value
    );	    

const vchar * vprefLoad(
    const vchar *key
    );

const vchar * vprefLoadScribed(
    vscribe *key
    );
   
vresource vprefLoadResource(
    const vchar *key
    );

vresource vprefLoadResourceScribed(
    vscribe *key
    );

vprefDict *vprefLoadDict(
    const vchar *key
    );

vprefDict *vprefLoadDictScribed(
    vscribe *key
    );	    

void vprefReadResource(
    vresource resource
    );

void vprefDictStore(
    vprefDict *dict,
    const vchar *key,
    const vchar *value
    );

void vprefDictStoreScribed(
    vprefDict *dict,
    vscribe *key,
    vscribe *value
    );
   
void vprefDictStoreResource(
    vprefDict *dict,
    const vchar *key,
    vresource resource
    );

void vprefDictStoreResourceScribed(
    vprefDict *dict,
    vscribe *key,
    vresource resource
    );

void vprefDictStoreDict(
    vprefDict *dict,
    const vchar *key,
    vprefDict *value
    );

void vprefDictStoreDictScribed(
    vprefDict *dict,
    vscribe *key,
    vprefDict *value
    );	    

const vchar *vprefDictLoad(
    vprefDict *dict,
    const vchar *key
    );

const vchar *vprefDictLoadScribed(
    vprefDict *dict,
    vscribe *key
    );
   
vresource vprefDictLoadResource(
    vprefDict *dict,
    const vchar *key
    );

vresource vprefDictLoadResourceScribed(
    vprefDict *dict,
    vscribe *key
    );

vprefDict *vprefDictLoadDict(
    vprefDict *dict,
    const vchar *key
    );

vprefDict *vprefDictLoadDictScribed(
    vprefDict *dict,
    vscribe *key
    );	    

vdict *vcommandPrefLoadKeyDict(
    vprefDict                      *prefDict
    );

void vcolorPrefMergeScheme(
    vprefDict                      *prefDict,
    unsigned long                   flags,
    vcolorScheme                   *target
    );

#if (vportUSE_VMS_COMMAND_LINE)
int vprefGetVMSCommandLineArgs (
    vprefVMSCLIqualifiers          *appQualifiers[],
    int                            *argc,
    char                           *argv[]
    );
#endif

/*
 * CLASS DECLARATION
 */

#define vprefINIT	vinstanceINIT
#define vprefDESTROY	vinstanceDESTROY

#define vprefCLASS(CLASS, PREF)                                   \
  vinstanceCLASS(CLASS,PREF);                                     \
  vclassMETHOD(vprefRELEASE, (PREF *pref));                       \
  vclassMETHOD(vprefREAD, (PREF *pref, vresource resource));      \
  vclassMETHOD(vprefWRITE, (PREF *pref, vresource resource));     \
  vclassMETHOD_RET(vprefGET_SCRAP, vscrap *, (PREF *pref))


#define vprefValueCLASS(CLASS, PREF_VALUE)                                    \
  vprefCLASS(CLASS, PREF_VALUE)

#define vprefDictCLASS(CLASS, DICT)                                           \
  vprefCLASS(CLASS, DICT);                                           \
  vclassMETHOD(vprefDictSTORE_PREF,                                        \
	       (DICT *dict, const vname *tag, const vpref *pref));   \
  vclassMETHOD_RET(vprefDictLOAD_PREF,                                     \
		   const vpref *, (DICT *dict, const vname *tag));   \
  vclassMETHOD(vprefDictWRITE_PREF, (DICT *dict, const vname *tag))

#define vprefDictObserverINIT		vinstanceINIT
#define vprefDictObserverDESTROY	vinstanceDESTROY

#define vprefDictObserverCLASS(CLASS, OBSVR)                                  \
  vinstanceCLASS(CLASS,OBSVR);                                                \
  vclassMETHOD(vprefDictObserverOBSERVE_LOAD,                                 \
	       (OBSVR *obsvr, const vname *tag, const vpref *pref));          \
  vclassMETHOD(vprefDictObserverOBSERVE_STORE,                                \
	       (OBSVR *obsvr, const vname *tag, const vpref *pref))


/*
 * PRIVATE TYPES
 */

struct vpref {
    vinstance instance;
    unsigned long refCount;
    unsigned long flags;
};

struct vprefClass {
    vprefCLASS(vprefClass, vpref);
};

struct vprefValue {
    vpref pref;
    vscrap *scrap;
};

struct vprefValueClass {
    vprefCLASS(vprefValueClass, vprefValue);
};

struct vprefDictObserver {
    vinstance	  instance;
    void *data;
};

struct vprefDictObserverClass {
    vprefDictObserverCLASS(vprefDictObserverClass, vprefDictObserver);
};

struct vprefDict {
    vpref pref;
    vprefDict *parent;
    union {
	vresource resource;
	const vname *tag;
    } identifier;
    vdict *defaultDict;
    vdict *newDict;
    vresource *stackTop, *stackBase;
    vprefDictObserver **observers;
    size_t numObservers;
};

struct vprefDictClass {
    vprefDictCLASS(vprefDictClass, vprefDict);
};

struct vprefIterator {
    vprefDict *dict;
    size_t stage;
    vdict marked;
    vdictIterator diter;
    size_t index;
};

#if (vportUSE_VMS_COMMAND_LINE)
struct vprefVMSCLIqualifiers {
            char  *VMSqualifier;
            char  *CmdLineArg;
            int   flags;

};
#endif

/*
 * PRIVATE CONSTANTS
 */

#define _vprefSHUTDOWN                     0x00000001
#define _vprefValueDEFAULT                 0x00000002
#define _vprefValueVALUE_SET               0x00000004
#define _vprefValueSTORED_AS_STRING        0x00000008
#define _vprefValueSTORED_AS_RESOURCE      0x00000010
#define _vprefDictDERIVED_STACK            0x00000020
#define _vprefDictRESOURCE_IDENTITY    	   0x00000040
#define _vprefDictNON_DEFAULT_STACK_BASE   0x00000080
#define _vprefSTRING                       0x00000100

#if (vportUSE_VMS_COMMAND_LINE)
#define vprefVMSCLI_V_HAS_VALUE           0x00000000
#define vprefVMSCLI_M_HAS_VALUE           0x00000001
#define vprefVMSCLI_V_PRESERVE_CASE       0x00000001
#define vprefVMSCLI_M_PRESERVE_CASE       0x00000002
#define vprefVMSCLI_V_REST_OF_LINE        0x00000002
#define vprefVMSCLI_M_REST_OF_LINE        0x00000004
#define vprefVMSCLI_V_LIST_VALUE          0x00000003
#define vprefVMSCLI_M_LIST_VALUE          0x00000008
#define vprefVMSCLI_V_CONCAT_VALUE        0x00000004
#define vprefVMSCLI_M_CONCAT_VALUE        0x00000010
#endif

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vprefGetInstance(e) \
  (vportBASE_OBJECT(e, instance))

#define vprefGetClass(e) \
  ((vprefClass *) vinstanceGetClass(vprefGetInstance(e)))

#define vprefInitOfClass(e, c) \
  vinstanceInitOfClass(vprefGetInstance(e), (vinstanceClass*)(c))

#define vprefCreateOfClass(c) \
  ((vpref *) vinstanceCreateOfClass((vinstanceClass*)(c)))

#define vprefDestroy(e) \
  vinstanceDestroy(vprefGetInstance(e))

#define vprefValueGetPref(p) \
  (vportBASE_OBJECT(p, pref))

#define vprefValueGetClass(p) \
  ((vprefValueClass *)vprefGetClass(vprefValueGetPref((p))))

#define vprefValueCreate(v) \
  vprefValueCreateOfClass(vprefValueGetDefaultClass(),(v))

#define vprefValueInit(p,v) \
  vprefValueInitOfClass((p), vprefValueGetDefaultClass(),(v))

#define vprefValueRelease(p) \
  vprefRelease(vprefValueGetPref((p)))

#define vprefValueDestroy(p) \
  vprefDestroy(vprefValueGetPref((p)))

#define vprefValueRead(p,r) \
  vprefRead(vprefValueGetPref((p)),(r))

#define vprefValueWrite(p,r) \
  vprefWrite(vprefValueGetPref((p)),(r))

#define vprefValueGetScrap(p) \
  vprefGetScrap(vprefValueGetPref((p)))

#define vprefDictObserverGetInstance(o) \
  (vportBASE_OBJECT(o, instance))

#define vprefDictObserverGetClass(o) \
  ((vprefDictObserverClass *) \
     vinstanceGetClass(vprefDictObserverGetInstance(o)))

#define vprefDictObserverInitOfClass(o, c) \
  vinstanceInitOfClass(vprefDictObserverGetInstance(o), (vinstanceClass*)(c))

#define vprefDictObserverCreateOfClass(c) \
  ((vprefDictObserver *) vinstanceCreateOfClass((vinstanceClass*)(c)))

#define vprefDictObserverDestroy(o) \
  vinstanceDestroy(vprefDictObserverGetInstance(o))

#define vprefDictObserverSetData(o,d) \
  ((o)->data = d)

#define vprefDictObserverGetData(o) \
  ((o)->data)

#define vprefDictGetPref(d) \
  (vportBASE_OBJECT(d, pref))

#define vprefDictGetClass(d) \
  ((vprefDictClass *)vprefGetClass(vprefDictGetPref((d))))

#define vprefDictCreateOfClass(c) \
  ((vprefDict *)vprefCreateOfClass((vprefClass *)(c)))

#define vprefDictCreate() \
  vprefDictCreateOfClass(vprefDictGetDefaultClass())

#define vprefDictInitOfClass(d,c) \
  vprefInitOfClass(vprefDictGetPref(d),(c))

#define vprefDictInit(d) \
  vprefDictInitOfClass((d), vprefDictGetDefaultClass())

#define vprefDictRelease(d) \
  vprefRelease(vprefDictGetPref((d)))

#define vprefDictDestroy(p) \
  vprefDestroy(vprefDictGetPref((p)))

#define vprefDictRead(p,r) \
  vprefRead(vprefDictGetPref((p)),(r))

#define vprefDictWrite(p,r) \
  vprefWrite(vprefDictGetPref((p)),(r))

#define vprefDictGetScrap(d) \
  vprefGetScrap(vprefDictGetPref((d)))

#define vprefDictStorePref(d,t,e) \
  vclassSend(vprefDictGetClass((d)), vprefDictSTORE_PREF, ((d),(t),(e)))

#define vprefDictLoadPref(d,t) \
  vclassSend(vprefDictGetClass((d)), vprefDictLOAD_PREF, ((d),(t)))

#define vprefDictWritePref(d,t) \
  vclassSend(vprefDictGetClass((d)), vprefDictWRITE_PREF, ((d),(t)))

#define vprefStoreScribed(k,v) \
    vprefDictStoreScribed(vprefGetRootDict(),k,v)

#define vprefStoreResourceScribed(k, r) \
    vprefDictStoreResourceScribed(vprefGetRootDict(),k,r)

#define vprefStoreDict(k,v) \
    vprefDictStorePref(vprefGetRootDict(), \
		       vnameInternGlobal((k)),vprefDictGetPref((v)));

#define vprefStoreDictScribed(k,v) \
    vprefDictStorePref(vprefGetRootDict(), \
		       vnameInternGlobalScribed((k)), vprefDictGetPref((v)));

#define vprefLoadScribed(k) \
    vprefDictLoadScribed(vprefGetRootDict(),k)

#define vprefLoadResourceScribed(k) \
    vprefDictLoadResourceScribed(vprefGetRootDict(),k)

#define vprefLoadDict(k) \
    vprefDictLoadDictScribed(vprefGetRootDict(),vcharScribe(k))

#define vprefLoadDictScribed(k) \
    vprefDictLoadDictScribed(vprefGetRootDict(),k)

#define vprefDictLoadDict(d,k) \
    vprefDictLoadDictScribed(d,vcharScribe(k))

#define vprefStore(k, v) \
    vprefStoreScribed(vcharScribe(k), vcharScribe(v))

#define vprefStoreResource(k, r) \
    vprefStoreResourceScribed(vcharScribe(k), r)

#define vprefLoad(k)                vprefLoadScribed(vcharScribe(k))

#define vprefLoadResource(k)        vprefLoadResourceScribed(vcharScribe(k))

#define vprefDictStore(d,k,v) \
    vprefDictStoreScribed(d,vcharScribe(k),vcharScribe(v))

#define vprefDictStoreResource(d,k,v) \
    vprefDictStoreResourceScribed(d,vcharScribe(k),v)

#define vprefDictStoreDict(d,k,v) \
    vprefDictStorePref((d), \
		       vnameInternGlobal((k)),vprefDictGetPref((v)));

#define vprefDictStoreDictScribed(d,k,v) \
    vprefDictStorePref((d), \
		       vnameInternGlobalScribed((k)), vprefDictGetPref((v)));

#define vprefDictLoad(d,k) \
    vprefDictLoadScribed(d,vcharScribe(k))

#define vprefDictLoadResource(d,k) \
    vprefDictLoadResourceScribed(d,vcharScribe(k))
 
#define vprefInitIterator(i) \
    vprefDictInitIterator(i,vprefGetRootDict())

#define vprefReadResource(r) \
    vprefDictReadResource(vprefGetRootDict(),r)

/*
 * FUNCTIONS IMPLEMENTED AS METHODS
 */


#define vprefRelease(e) \
  vclassSend(vprefGetClass((e)), vprefRELEASE, ((e)))

#define vprefRead(e,r) \
  vclassSend(vprefGetClass((e)), vprefREAD, ((e),(r)))

#define vprefWrite(e,r) \
  vclassSend(vprefGetClass((e)), vprefWRITE, ((e),(r)))

#define vprefGetScrap(e) \
  vclassSend(vprefGetClass((e)), vprefGET_SCRAP, ((e)))

#define vprefDictObserverObserveLoad(o,t,e) \
  vclassSend(vprefDictObserverGetClass((o)), vprefDictObserverOBSERVE_LOAD, \
	     ((o),(t),(e)))

#define vprefDictObserverObserveStore(o,t,e) \
  vclassSend(vprefDictObserverGetClass((o)), vprefDictObserverOBSERVE_STORE, \
	     ((o),(t),(e)))

vportEND_CPLUSPLUS_EXTERN_C

#endif
