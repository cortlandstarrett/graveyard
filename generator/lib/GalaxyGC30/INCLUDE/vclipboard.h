/* $Id: vclipboard.h,v 1.29 1997/07/14 12:16:29 gray Exp $ */

/*
 * vclipboard.h
 *
 * Clipboard Manager Header File
 *
 * Copyright (C) 1996 Visix Software, Inc.
 * All rights reserved
 */

#ifndef vclipboardINCLUDED
#define vclipboardINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef vmutexINCLUDED
#include vmutexHEADER
#endif



vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * PUBLIC TYPE DECLARATION
 */

typedef struct vclipboard vclipboard;
typedef struct vclipboardClass vclipboardClass;

typedef struct vclipboardEngine vclipboardEngine;
typedef struct vclipboardEngineClass vclipboardEngineClass;

typedef struct vclipboardFormatRegistry vclipboardFormatRegistry;
typedef struct vclipboardFormatRegistryClass vclipboardFormatRegistryClass;

typedef void (*vclipboardNoteProc)(vclipboard *clipboard, vscrap *content);
typedef void (*vclipboardQueryNoteProc)(vclipboard *clipboard, vdict *result);

typedef struct vclipboardEngineScrap vclipboardEngineScrap;
typedef struct vclipboardEngineScrapClass vclipboardEngineScrapClass;

typedef struct vclipboardException vclipboardException;
typedef vclipboardException vclipboardNoContentsException;
typedef vclipboardException vclipboardTimeoutException;

/*
 * PUBLIC CONSTANT DECLARATION
 */

/*
 * PUBLIC FUNCTION DECLARATION
 */

/*
 * Clipboard Class Functions
 */

vclipboardClass *vclipboardGetDefaultClass(
    void
    );

vinstance *vclipboardGetInstance(
    vclipboard *clipboard
    );

vclipboardClass *vclipboardGetClass(
    vclipboard *clipboard
    );

vclipboard *vclipboardCreateOfClass(
    vclipboardClass *clas
    );

vclipboard *vclipboardCreate(
    void
    );

void vclipboardInitOfClass(
    vclipboard *clipboard,
    vclipboardClass *clas
    );

void vclipboardInit(
    vclipboard *clipboard
    );
    

/*
 * Function Interface to Clipboard Methods
 */

void vclipboardDestroy(
    vclipboard *clipboard
    );

void vclipboardSetNotify(
    vclipboard *clipboard,
    vclipboardNoteProc notify
    );

void vclipboardSetQueryNotify(
    vclipboard *clipboard,
    vclipboardQueryNoteProc notify
    );

void vclipboardSetEngine(
    vclipboard *clipboard,
    vclipboardEngine *engine
    );

void vclipboardSetRequestScrap(
    vclipboard *clipboard,
    vscrap *scrap
    );

void vclipboardSetContents(
    vclipboard *clipboard,
    vscrap *contents
    );

void vclipboardSetData(
    vclipboard *clipboard,
    const void *data
    );

void vclipboardClearContents(
    vclipboard *clipboard
    );

void vclipboardRequestContents(
    vclipboard *clipboard
    );

vbool vclipboardHasContents(
    vclipboard *clipboard
    );

void vclipboardQueryContentEncodings(
    vclipboard *clipboard
    );

void vclipboardNotify(
    vclipboard *clipboard,
    vscrap *contents
    );

void vclipboardNotifyQuery(
    vclipboard *clipboard,
    vdict *results
    );

/*
 * Clipboard Engine Class Functions
 */

vclipboardEngineClass *vclipboardGetDefaultEngineClass(
    void
    );

vinstance *vclipboardGetEngineInstance(
    vclipboardEngine *engine
    );

vclipboardEngineClass *vclipboardGetEngineClass(
    vclipboardEngine *engine
    );

vclipboardEngine *vclipboardCreateEngineOfClass(
    vclipboardEngineClass *clas
    );

vclipboardEngine *vclipboardCreateEngine(
    void
    );

void vclipboardInitEngineOfClass(
    vclipboardEngine *engine,
    vclipboardEngineClass *clas
    );

void vclipboardInitEngine(
    vclipboardEngine *engine
    );

/*
 * Function Interface To Clipboard Engine Methods
 */

void vclipboardDestroyEngine(
    vclipboardEngine *engine
    );

void vclipboardSetEngineRegistry(
    vclipboardEngine *engine,
    vclipboardFormatRegistry *registry
    );

vclipboardFormatRegistry *vclipboardGetEngineRegistry(
    vclipboardEngine *engine
    );

void vclipboardClearEngineContents(
    vclipboardEngine *engine
    );

void vclipboardDestroyEngineLocalContents(
    vclipboardEngine *engine
    );

void vclipboardSetEngineContents(
    vclipboardEngine *engine,
    vscrap *contents
    );

void vclipboardConvertEngineContents(
    vclipboardEngine *engine,
    vscrap *scrap
    );

vdict *vclipboardGetEngineContentEncodings(
    vclipboardEngine *engine
    );

vbool vclipboardEngineHasContents(
    vclipboardEngine *engine
    );

void vclipboardRequestEngineContents(
    vclipboardEngine *engine,
    vclipboard *clipboard
    );

void vclipboardQueryEngineContentEncodings(
    vclipboardEngine *engine,
    vclipboard *clipboard
    );

vscrap *vclipboardCreateEngineScrap(
    vclipboardEngine *engine,
    vdict *encodings
    );

void vclipboardLockEngine(
    vclipboardEngine *engine
    );

void vclipboardUnlockEngine(
    vclipboardEngine *engine
    );

vscrap *vclipboardCreateEngineStringTransferScrap(
    vclipboardEngine *engine
    );

/*
 * Clipboard Format Registry Class Functions
 */

vclipboardFormatRegistryClass *vclipboardGetDefaultFormatRegistryClass(
    void
    );

vinstance *vclipboardGetFormatRegistryInstance(
    vclipboardFormatRegistry *registry
    );

vclipboardFormatRegistryClass *vclipboardGetFormatRegistryClass(
    vclipboardFormatRegistry *registry
    );

vclipboardFormatRegistry *vclipboardCreateFormatRegistryOfClass(
    vclipboardFormatRegistryClass *clas
    );

vclipboardFormatRegistry *vclipboardCreateFormatRegistry(
    void
    );

void vclipboardInitFormatRegistryOfClass(
    vclipboardFormatRegistry *registry,
    vclipboardFormatRegistryClass *clas
    );

void vclipboardInitFormatRegistry(
    vclipboardFormatRegistry *registry
    );


/*
 * Function Interface to Clipboard Format Registry Methods
 */

void vclipboardDestroyFormatRegistry(
    vclipboardFormatRegistry *registry
    );

void vclipboardRegisterFormat(
    vclipboardFormatRegistry *registry,
    const vname *format,
    vscrap *encoding
    );

vscrap *vclipboardGetFormatEncoding(
    vclipboardFormatRegistry *registry,
    const vname *format
    );

const vname *vclipboardGetEncodingFormat(
    vclipboardFormatRegistry *registry,
    vscrap *encoding
    );

vdict *vclipboardMatchEncodings(
    vclipboardFormatRegistry *registry,
    vscrap *scrap
    );

/*
 * Clipboard Engine Scrap Class Functions
 */

vclipboardEngineScrapClass *vclipboardGetDefaultEngineScrapClass(
    void
    );

/*
 * Exception Functions
 */

vclipboardNoContentsException *vclipboardGetNoContentsException(
    void
    );

void vclipboardGenerateNoContentsException(
    vclipboardEngine *engine
    );

vclipboardTimeoutException *vclipboardGetTimeoutException(
    void
    );

void vclipboardGenerateTimeoutException(
    vclipboardEngine *engine
    );

/*
 * Convenience Functions
 */

void vclipboardSetEngineScrapFormat(
    vscrap *scrap,
    const vname *format
    );

void vclipboardSetEngineScrapFormatStack(
    vdelegatorStack stack,					 
    const vname *format
    );

void vclipboardConvertScrapAsFormat(
    vscrap *from,
    vscrap *to,
    const vname *format
    );

const void *vclipboardGetData(
    vclipboard *clipboard
    );

vclipboardNoteProc vclipboardGetNotify(
    vclipboard *clipboard
    );

vbool vclipboardEncodingOfKind(
    vdict *encodings,
    void *clas
    );

void vclipboardGetAllRegistryEncodings(
    vclipboardFormatRegistry *registry,
    vdict *dict
    );

vclipboard *vclipboardCreateSelection(
    void
    );

vclipboard *vclipboardCreateGlobal(
    void
    );

vclipboardEngine *vclipboardGetInternalEngine(
    void
    );

vclipboardEngine *vclipboardGetGlobalEngine(
    void
    );

vclipboardEngine *vclipboardGetSelectionEngine(
    void
    );

void vclipboardSetGlobalEngine(
    vclipboardEngine *engine
    );

void vclipboardSetSelectionEngine(
    vclipboardEngine *engine
    );

vtimestamp vclipboardGetTimeoutValue(
    void
    );

void vclipboardStartup(
    void
    );

/*
 * Deprecated Functions
 */

vclipboardClass *vclipboardGetDefaultSelectionClass(
    void
    );

vclipboardClass *vclipboardGetDefaultGlobalClass(
    void
    );

/*
 * CLASS DEFINITION
 */

#define vclipboardINIT vinstanceINIT
#define vclipboardDESTROY vinstanceDESTROY

#define vclipboardCLASS(CLASS, CLIPBOARD)                                    \
  vinstanceCLASS(CLASS, CLIPBOARD);                                          \
  vclassMETHOD(vclipboardSET_NOTIFY,                                         \
	       (CLIPBOARD *clipboard, vclipboardNoteProc notify));           \
  vclassMETHOD(vclipboardSET_QUERY_NOTIFY,                                   \
	       (CLIPBOARD *clipboard, vclipboardQueryNoteProc notify));      \
  vclassMETHOD(vclipboardSET_ENGINE,                                         \
	       (CLIPBOARD *clipboard, vclipboardEngine *engine));            \
  vclassMETHOD(vclipboardSET_REQUEST_SCRAP,                                  \
	       (CLIPBOARD *clipboard, vscrap *scrap));                       \
  vclassMETHOD(vclipboardSET_CONTENTS,                                       \
	       (CLIPBOARD *clipboard, vscrap *scrap));                       \
  vclassMETHOD(vclipboardSET_DATA, (CLIPBOARD *clipboard, const void *data));\
  vclassMETHOD(vclipboardCLEAR_CONTENTS, (CLIPBOARD *clipboard));            \
  vclassMETHOD(vclipboardREQUEST_CONTENTS, (CLIPBOARD *clipboard));          \
  vclassMETHOD_RET(vclipboardHAS_CONTENTS, vbool,                            \
		   (CLIPBOARD *clipboard));                                  \
  vclassMETHOD(vclipboardQUERY_CONTENT_ENCODINGS, (CLIPBOARD *clipboard));   \
  vclassMETHOD(vclipboardNOTIFY, (CLIPBOARD *clipboard, vscrap *contents));  \
  vclassMETHOD(vclipboardNOTIFY_QUERY,                                       \
	       (CLIPBOARD *clipboard, vdict *result))
  
#define vclipboardEngineCLASS(CLASS, ENGINE)                                 \
  vinstanceCLASS(CLASS, ENGINE);                                             \
  vclassVARIABLE(vclipboardENGINE_SCRAP_CLASS,                               \
		 vclipboardEngineScrapClass *);                              \
  vclassMETHOD(vclipboardSET_ENGINE_REGISTRY,                                \
	       (ENGINE *engine, vclipboardFormatRegistry *registry));        \
  vclassMETHOD(vclipboardCLEAR_ENGINE_CONTENTS, (ENGINE *engine));           \
  vclassMETHOD(vclipboardDESTROY_ENGINE_LOCAL_CONTENTS, (ENGINE *engine));   \
  vclassMETHOD(vclipboardSET_ENGINE_CONTENTS,                                \
	       (ENGINE *engine, vscrap *scrap));                             \
  vclassMETHOD(vclipboardCONVERT_ENGINE_CONTENTS,                            \
	       (ENGINE *engine, vscrap *scrap));                             \
  vclassMETHOD_RET(vclipboardGET_ENGINE_CONTENT_ENCODINGS, vdict *,          \
		   (ENGINE *engine));                                        \
  vclassMETHOD_RET(vclipboardENGINE_HAS_CONTENTS, vbool,                     \
		   (ENGINE *engine));                                        \
  vclassMETHOD(vclipboardREQUEST_ENGINE_CONTENTS,                            \
	       (ENGINE *engine, vclipboard *clipboard));                     \
  vclassMETHOD(vclipboardQUERY_ENGINE_CONTENT_ENCODINGS,                     \
	       (ENGINE *engine, vclipboard *clipboard));                     \
  vclassMETHOD_RET(vclipboardCREATE_ENGINE_SCRAP, vscrap *,                  \
		   (ENGINE *engine, vdict *encodings));                      \
  vclassMETHOD_RET(vclipboardCREATE_ENGINE_STRING_TRANSFER_SCRAP, vscrap *,  \
		   (ENGINE *engine))
  	       
#define vclipboardFormatRegistryCLASS(CLASS, REGISTRY)                       \
  vinstanceCLASS(CLASS, REGISTRY);                                           \
  vclassMETHOD(vclipboardREGISTER_FORMAT,                                    \
	       (REGISTRY *registry, const vname *format, vscrap *encoding)); \
  vclassMETHOD_RET(vclipboardGET_FORMAT_ENCODING, vscrap *,                  \
		   (REGISTRY *registry, const vname *format));               \
  vclassMETHOD_RET(vclipboardGET_ENCODING_FORMAT, const vname *,             \
		   (REGISTRY *registry, vscrap *encoding));                  \
  vclassMETHOD_RET(vclipboardMATCH_ENCODINGS, vdict *,                       \
		   (REGISTRY *registry, vscrap *scrap))

#define vclipboardEngineScrapCLASS(CLASS, SCRAP)                             \
  vscrapBLOCK_CLASS(CLASS, SCRAP);                                           \
  vclassMETHOD(vclipboardSET_ENGINE_SCRAP_FORMAT,                            \
	       (const vdelegatorStack *stack, const vname *newFormat))

/*
 * EXCEPTION DECLARATIONS
 */

struct vclipboardException 
{
  vexException super;
  vclipboardEngine *engine;
};

void vclipboardENGINE(void *exception, va_list *ap);

/*
 * PRIVATE TYPE DECLARATIONS
 */

struct vclipboard {
  vinstance super;
  vclipboardEngine *engine;
  vscrap *requestScrap;
  vclipboardNoteProc notify;
  vclipboardQueryNoteProc queryNotify;
  void *data;
};

struct vclipboardEngine {
  vinstance super;
  vclipboardFormatRegistry *registry;
  vscrap *localContents;
  vdict *contentEncodings;
  vmutex mutex;
};

struct vclipboardFormatRegistry {
  vinstance super;
  vdictSafe *format2Encoding;
  vdictSafe *encoding2Format;
};

struct vclipboardEngineScrap {
  vscrapBlock super;
  vdictIterator *iterator;
  vdict *encodings;
};

struct vclipboardClass {
  vclipboardCLASS(vclipboardClass, vclipboard);
};

struct vclipboardEngineClass {
  vclipboardEngineCLASS(vclipboardEngineClass, vclipboardEngine);
};

struct vclipboardFormatRegistryClass {
  vclipboardFormatRegistryCLASS(vclipboardFormatRegistryClass,
				vclipboardFormatRegistry);
};

struct vclipboardEngineScrapClass {
  vclipboardEngineScrapCLASS(vclipboardEngineScrapClass,
			     vclipboardEngineScrap);
};

/*
 * PRIVATE VARIABLES
 */

extern const vexClass _vclipboardNoContentsExceptionClass;
extern const vexClass _vclipboardTimeoutExceptionClass;

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vclipboardSetEngineScrapFormat(s,f)                                  \
  vclipboardSetEngineScrapFormatStack(vdelegatorMakeObjectStack((s)),(f))

#define vclipboardGenerateNoContentsException(e) \
  vexGenerate(&_vclipboardNoContentsExceptionClass, \
	      vclipboardENGINE, (e), vexNULL)

#define vclipboardGenerateTimeoutException(e) \
  vexGenerate(&_vclipboardTimeoutExceptionClass, \
	      vclipboardENGINE, (e), vexNULL)

#define vclipboardGetInstance(c)                                             \
    vportBASE_OBJECT((c), super)

#define vclipboardGetClass(c)                                                \
    ((vclipboardClass *)vinstanceGetClass(vclipboardGetInstance((c))))

#define vclipboardCreateOfClass(c)                                           \
    ((vclipboard *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vclipboardCreate()                                                   \
    vclipboardCreateOfClass(vclipboardGetDefaultClass())

#define vclipboardInitOfClass(i,c)                                           \
    vinstanceInitOfClass(vclipboardGetInstance((i)), (vinstanceClass *)(c))

#define vclipboardInit(c)                                                    \
    vclipboardInitOfClass((c), vclipboardGetDefaultClass())

#define vclipboardGetEngineInstance(c)                                       \
    vportBASE_OBJECT((c), super)

#define vclipboardGetEngineClass(c)                                          \
    ((vclipboardEngineClass *)vinstanceGetClass(vclipboardGetEngineInstance((c))))

#define vclipboardCreateEngineOfClass(c)                                     \
    ((vclipboardEngine *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vclipboardCreateEngine()                                             \
    vclipboardCreateEngineOfClass(vclipboardGetDefaultEngineClass())

#define vclipboardInitEngineOfClass(i,c)                                     \
    vinstanceInitOfClass(vclipboardGetEngineInstance((i)),                   \
			 (vinstanceClass *)(c))

#define vclipboardInitEngine(c)                                              \
    vclipboardInitEngineOfClass((c), vclipboardGetDefaultEngineClass())

#define vclipboardGetEngineRegistry(e) ((e)->registry)

#define vclipboardGetFormatRegistryInstance(c)                               \
    vportBASE_OBJECT((c), super)

#define vclipboardGetFormatRegistryClass(c)                                  \
    ((vclipboardFormatRegistryClass *)vinstanceGetClass(vclipboardGetFormatRegistryInstance((c))))

#define vclipboardCreateFormatRegistryOfClass(c)                             \
    ((vclipboardFormatRegistry *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vclipboardCreateFormatRegistry()                                     \
    vclipboardCreateFormatRegistryOfClass(vclipboardGetDefaultFormatRegistryClass())

#define vclipboardInitFormatRegistryOfClass(i,c)                              \
    vinstanceInitOfClass(vclipboardGetFormatRegistryInstance((i)),            \
			 (vinstanceClass *)(c))

#define vclipboardInitFormatRegistry(c)                                       \
    vclipboardInitFormatRegistryOfClass((c),                                  \
					vclipboardGetDefaultFormatRegistryClass())

#define vclipboardGetNoContentsException()                                   \
    ((vclipboardNoContentsException *)                                       \
     vexGetExceptionOfClass(&_vclipboardNoContentsExceptionClass))

#define vclipboardGetTimeoutException()                                      \
    ((vclipboardTimeoutException *)                                          \
     vexGetExceptionOfClass(&_vclipboardTimeoutExceptionClass))

#define vclipboardGetData(c)                                                 \
    ((c)->data)

#define vclipboardGetNotify(c)                                               \
    ((c)->notify)

#define vclipboardGetDefaultSelectionClass()                                 \
    vclipboardGetDefaultClass()

#define vclipboardGetDefaultGlobalClass()                                    \
    vclipboardGetDefaultClass()

#define vclipboardLockEngine(c)                                              \
    vmutexLock(&((c)->mutex));
    
#define vclipboardUnlockEngine(c)                                            \
    vmutexUnlock(&((c)->mutex));
    
#define vclipboardGetTimeoutValue() vtimestampMake(1,0)

/*
 * FUNCTIONS IMPLEMENTED AS METHODS
 */

#define vclipboardDestroy(c)                                                 \
    vinstanceDestroy(vclipboardGetInstance(c))

#define vclipboardSetNotify(c,n)                                             \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_NOTIFY, ((c),(n)))               

#define vclipboardSetQueryNotify(c,n)                                        \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_QUERY_NOTIFY, ((c),(n)))

#define vclipboardSetEngine(c,e)                                             \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_ENGINE, ((c),(e)))

#define vclipboardSetRequestScrap(c,s)                                       \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_REQUEST_SCRAP, ((c),(s)))

#define vclipboardSetContents(c,s)                                           \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_CONTENTS, ((c),(s)))

#define vclipboardSetData(c,d)                                               \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardSET_DATA, ((c),(d)))

#define vclipboardClearContents(c)                                           \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardCLEAR_CONTENTS, ((c)))

#define vclipboardRequestContents(c)                                         \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardREQUEST_CONTENTS, ((c)))

#define vclipboardHasContents(c)                                             \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardHAS_CONTENTS, ((c)))

#define vclipboardQueryContentEncodings(c)                                   \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardQUERY_CONTENT_ENCODINGS, ((c)))

#define vclipboardNotify(c,s)                                                \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardNOTIFY, ((c),(s)))

#define vclipboardNotifyQuery(c,d)                                           \
    vclassSend(vclipboardGetClass((c)),                                      \
	       vclipboardNOTIFY_QUERY, ((c),(d)))

#define vclipboardDestroyEngine(e)                                           \
    vinstanceDestroy(vclipboardGetEngineInstance(e))

#define vclipboardSetEngineRegistry(e,r)                                     \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardSET_ENGINE_REGISTRY, ((e),(r)))

#define vclipboardClearEngineContents(e)                                     \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardCLEAR_ENGINE_CONTENTS, ((e)))

#define vclipboardDestroyEngineLocalContents(e)                              \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardDESTROY_ENGINE_LOCAL_CONTENTS, ((e)))

#define vclipboardSetEngineContents(e,s)                                     \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardSET_ENGINE_CONTENTS, ((e),(s)))

#define vclipboardConvertEngineContents(e,s)                                 \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardCONVERT_ENGINE_CONTENTS, ((e),(s)))

#define vclipboardGetEngineContentEncodings(e)                               \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardGET_ENGINE_CONTENT_ENCODINGS, ((e)))

#define vclipboardEngineHasContents(e)                                       \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardENGINE_HAS_CONTENTS, ((e)))

#define vclipboardRequestEngineContents(e,c)                                 \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardREQUEST_ENGINE_CONTENTS, ((e),(c)))

#define vclipboardQueryEngineContentEncodings(e,c)                           \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardQUERY_ENGINE_CONTENT_ENCODINGS, ((e),(c)))

#define vclipboardCreateEngineScrap(e,d)                                     \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardCREATE_ENGINE_SCRAP, ((e),(d)))

#define vclipboardCreateEngineStringTransferScrap(e)                         \
    vclassSend(vclipboardGetEngineClass((e)),                                \
	       vclipboardCREATE_ENGINE_STRING_TRANSFER_SCRAP, ((e)))

#define vclipboardDestroyFormatRegistry(r)                                   \
    vinstanceDestroy(vclipboardGetFormatRegistryInstance(r))

#define vclipboardRegisterFormat(r,f,e)                                      \
    vclassSend(vclipboardGetFormatRegistryClass((r)),                        \
	       vclipboardREGISTER_FORMAT, ((r),(f),(e)))
   
#define vclipboardGetEncodingFormat(r,e)                                     \
    vclassSend(vclipboardGetFormatRegistryClass((r)),                        \
	       vclipboardGET_ENCODING_FORMAT, ((r),(e)))
   
#define vclipboardGetFormatEncoding(r,f)                                     \
    vclassSend(vclipboardGetFormatRegistryClass((r)),                        \
	       vclipboardGET_FORMAT_ENCODING, ((r),(f)))
   
#define vclipboardMatchEncodings(r,s)                                        \
    vclassSend(vclipboardGetFormatRegistryClass((r)),                        \
	       vclipboardMATCH_ENCODINGS, ((r),(s)))
   

vportEND_CPLUSPLUS_EXTERN_C


#endif

