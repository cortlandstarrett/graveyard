/* $Id: vdebug.h,v 1.100 1997/09/18 21:36:24 jim Exp $ */

#ifndef vdebugINCLUDED
#define vdebugINCLUDED 1


/*
 * Include any files this header depends upon
 */

#ifndef  vportINCLUDED          /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdargINCLUDED        /* for va_list */
#include vstdargHEADER
#endif

#ifndef  vstdioINCLUDED         /* for FILE, stderr, etc. */
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED           /* for vbool */
#include vstdHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * * Public MACROs * * * * * * * * * * * * * * * * *
 */

/*
 * Note:  Most of the following macros can be redefined by defining them
 * BEFORE this header is included.  This ability is indicated and implemented
 * by an #ifndef wrapper
 */

/*
 * vdebugDEBUG
 *
 * the master switch for enabling the entire debug module.
 * This boolean flag indicates whether all debugging code is to be
 * compiled in or out.  There is no middle ground.  Compiling in
 * debugging code does not mean that it is turned on, it just means that it
 * is compiled in.
 */

#ifndef vdebugDEBUG
#define vdebugDEBUG vportDEBUG
#endif

/*
 * vdebugTEST_UI
 *
 * Switch to control inclusion of UI specific test hooks.
 */

#ifndef vdebugTEST_UI
#define vdebugTEST_UI vTRUE
#endif

/*
 * Debugging pieces that are defined or used on a per module basis can
 * have "tag"s associated with them for tracking purposes.  The tag must be
 * a string literal.  To override the default value, #define vdebugTAG to
 * whatever you like.  For example:
 *
 * #if (vdebugDEBUG)
 * static const char _mymoduleTag[] = "mymodule";
 * #define vdebugTAG _mymoduleTag
 * #endif
 */

#ifndef vdebugTAG
#ifndef vdebugNO_DEFAULT_TAG
extern vportLINK const char           vdebugTAG[];
#endif
#endif

/*
 * All debugging levels are stored in a global int.  Some of the more common
 * levels are named for ease of use and consistency.
 */

#define vdebugLEVEL_OFF         0
#define vdebugLEVEL_MIN         10
#define vdebugLEVEL_LOW         250
#define vdebugLEVEL_NORMAL      500
#define vdebugLEVEL_HIGH        750
#define vdebugLEVEL_MAX         1000

#define vdebugDEFAULT_ADVICE_LEVEL      vdebugLEVEL_NORMAL
#define vdebugDEFAULT_INFO_LEVEL        vdebugLEVEL_HIGH
#define vdebugDEFAULT_TRACING_LEVEL     (vdebugLEVEL_HIGH+100)
#define vdebugDEFAULT_WARNING_LEVEL     vdebugLEVEL_LOW

#define vdebugDEFAULT_ADVICE_STREAM     stderr
#define vdebugDEFAULT_INFO_STREAM       stderr
#define vdebugDEFAULT_TRACING_STREAM    stderr
#define vdebugDEFAULT_WARNING_STREAM    stderr

#define vdebugDEFAULT_MODULE_ENVIRONMENT_VARIABLE       "vdebugMODULE"
#define vdebugDEFAULT_LEVEL_ENVIRONMENT_VARIABLE        "vdebugLEVEL"


/*
 * * * * * * * * * * * Public Types * * * * * * * * * * * * * *
 */

typedef struct _vdebugProcStackFrame _vdebugProcStackFrame;

struct _vdebugProcStackFrame {
    const _vdebugProcStackFrame         *caller;
    const char                          *procname;
    const char                          *tag;
    void                                *priv;
    int                                  reentered;
    const char                          *parentTag;
    const char                          *parentFile;
    int                                  parentLine;
};

typedef void (*vdebugAssertionHandler)(void             *data,
                                       const char       *message,
                                       const char       *file,
                                       const char       *tag,
                                       int               line);

/*
 * * * * * * * * * * * * Public Prototypes * * * * * * * * * * * *
 */

#if (0) /* hide Prototypes the compiler doesn't understand */
void     vdebugBE( text );
void     vdebugEVAL( stmts );
void     vdebugIF( int /*vbool*/, stmts );
void     vdebugAT( int level, action );

void     vdebugMAdvise(( const char *, ... ));
void     vdebugMAdviseAt(( int, const char *, ... ));
void     vdebugMInform(( const char *, ... ));
void     vdebugMInformAt(( int, const char *, ... ));
void     vdebugMTrace(( const char *, ... ));
void     vdebugMTraceAt(( int, const char *, ... ));
void     vdebugMWarn(( const char *, ... ));
void     vdebugMWarnAt(( int, const char *, ... ));
#endif

void     vdebugStartup( void );

vbool    vdebugActive( const char *module );
vbool    vdebugActiveAt( const char *module, int level );
void     vdebugPerror( const char *str );
void     vdebugAssert( int /*vbool*/ condition );
void     vdebugMessagedAssert( int /*vbool*/ condition, const char *msg );
void     vdebugHandledAssert( int /*vbool*/ condition,
                              vdebugAssertionHandler handler, void *data );
void     vdebugHandledMessagedAssert(int /*vbool*/ condition, const char *msg,
                                     vdebugAssertionHandler proc, void *data);
void     vdebugSetAssertionHandler(vdebugAssertionHandler handler);
void     vdebugAbort( void *data,  const char *message,
                      const char *file, const char *tag, int line );
void     vdebugSetFalse( void *data,  const char *message,
                         const char *file, const char *tag, int line );

void     vdebugTraceEnter( void *proc );
void     vdebugTraceEnterAt( int level, void *proc );
void     vdebugTraceEnterFrom( void *proc,
                               const char *tag, const char *file, int line );
void     vdebugTraceEnterAtFrom( int level, void *proc,
                                 const char *tag, const char *file, int line );
void     vdebugTraceReenter( void );
void     vdebugTraceEnterSubroutine( void );
void     vdebugTraceLeave( void );
void     vdebugTracePop( void );
void     vdebugTraceClear( void );
void     vdebugTraceSetCaller( const char *tag, const char *file, int line );

void     vdebugTraceEnterRaw( void *proc );
void     vdebugTraceLeaveRaw( void );
void     vdebugTracePopRaw( void );
void     vdebugTraceClearRaw( void );

void     vdebugUpdateStack( void );

void     vdebugDumpProcStack( FILE *fp );

FILE    *vdebugGetAdviceStream( void );
void     vdebugSetAdviceStream( FILE *fp );
FILE    *vdebugGetInfoStream( void );
void     vdebugSetInfoStream( FILE *fp );
FILE    *vdebugGetTracingStream( void );
void     vdebugSetTracingStream( FILE *fp );
FILE    *vdebugGetWarningStream( void );
void     vdebugSetWarningStream( FILE *fp );

int      vdebugParseLevel( const char *value );
void     vdebugSetVariables( const char *specs );
void     vdebugSetLevel( int level );

int      vdebugGetModuleLevel( const char *module );
void     vdebugSetModuleLevel( const char *module, int level );

/*
 * Debugger Prototypes
 * call as vdebugAssertFrame(_vdebugProc) from inside a frame
 */

void     vdebugAssertFrame( const _vdebugProcStackFrame *pFrame );

/*
 * Public Deprecated Prototypes
 */

void             vdebugAdvise( const char *formatString, ... );
void             vdebugAdviseAt( int level, const char *formatString, ... );
void             vdebugInform( const char *formatString, ... );
void             vdebugInformAt( int level, const char *formatString, ... );
void             vdebugTrace( const char *formatString, ... );
void             vdebugTraceAt( int level, const char *formatString, ... );
void             vdebugWarn( const char *formatString, ... );
void             vdebugWarnAt( int level, const char *formatString, ... );

const char      *vdebugGetCurrentProcName( void );
const char      *vdebugGetCurrentModule( void );
void             vdebugSetCurrentModule( const char *module );

const char      *vdebugGetLastProcName( void );

int              vdebugGetAdviceLevel( void );
void             vdebugSetAdviceLevel( int level );
int              vdebugGetInfoLevel( void );
void             vdebugSetInfoLevel( int level );
int              vdebugGetTracingLevel( void );
void             vdebugSetTracingLevel( int level );
int              vdebugGetWarningLevel( void );
void             vdebugSetWarningLevel( int level );


/*
 * ==========================================================================
 *                             PRIVATE
 * Do not touch, use, examine, or otherwise think about the rest of this file
 * ==========================================================================
 */

/*
 * * * * * * * * * * * * * Private Variables * * * * * * * * * * * * * *
 */

extern vportLINK FILE                         *_vdebugAdviceStream;
extern vportLINK FILE                         *_vdebugInfoStream;
extern vportLINK FILE                         *_vdebugTracingStream;
extern vportLINK FILE                         *_vdebugWarningStream;

extern vportLINK vdebugAssertionHandler        _vdebugAssertionHandler;

#if (vdebugDEBUG)

extern vportLINK vbool                         _vdebugManagerInitialized;

extern vportLINK int                           _vdebugAdviceThreshold;
extern vportLINK int                           _vdebugInfoThreshold;
extern vportLINK int                           _vdebugTracingThreshold;
extern vportLINK int                           _vdebugWarningThreshold;

/*
 * _vdebugProc
 *
 * Usually masked by a local proc frame of the same name,
 * this exists only to allow vdebug code to tell if it's being invoked
 * from within a local proc frame.  If they see this frame, they know they
 * aren't.  This identifier must exactly match the local variable identifier
 * used in a vdebugTrace block.
 */
#undef _vdebugProc
extern vportLINK const _vdebugProcStackFrame   _vdebugProc;

#endif


/*
 * * * * * * * * * * * * * Private Prototypes * * * * * * * * * * * * * * *
 */

vportLINK int   _vdebugInitManager(void);
vportLINK int   _vdebugGetModuleLevel(const char *module,
                                        const _vdebugProcStackFrame *);
vportLINK vbool _vdebugActiveAt(const char *module, int level,
                                  const _vdebugProcStackFrame *);
vportLINK void  _vdebugAdvise(const char *formatString, ...);
vportLINK void  _vdebugAdviseAt(int level, const char *formatString, ...);
vportLINK void  _vdebugInform(const char *formatString, ...);
vportLINK void  _vdebugInformAt(int level, const char *formatString, ...);
vportLINK void  _vdebugTrace(const char *formatString, ...);
vportLINK void  _vdebugTraceAt(int level, const char *formatString, ...);
vportLINK void  _vdebugWarn(const char *formatString, ...);
vportLINK void  _vdebugWarnAt(int level, const char *formatString, ...);
vportLINK void  _vdebugTraceEnterAtFrom(_vdebugProcStackFrame *frame,
                                          int level, const char *procname,
                                          const char *parentTag,
                                          const char *parentFile,
                                          int parentLine, const char *tag);
vportLINK void  _vdebugTraceReenter(_vdebugProcStackFrame *frame);
vportLINK void  _vdebugTraceLeave(const _vdebugProcStackFrame *frame);
vportLINK void  _vdebugSetProcStackTop(const _vdebugProcStackFrame *frame);


/*
 * * * * * * * * * * * * * Private Definitions * * * * * * * * * * * * * *
 */

vportBEGIN_MUST_BE_MACRO

#define vdebugSetAssertionHandler(h)    (_vdebugAssertionHandler = (h))
#define vdebugHandledAssert(c, h, d)\
    vdebugHandledMessagedAssert(c, vportQUOTE(c) " was not true", h, d)
#define vdebugHandledMessagedAssert(c, m, h, d)\
    ((void)((c) || (((h)?(vdebugAssertionHandler)(h):_vdebugAssertionHandler)(d, m, __FILE__, vdebugTAG, __LINE__), 0)))

#if (vdebugDEBUG)

#define vdebugStartup()                 ((void) ((_vdebugManagerInitialized) \
                                                 || _vdebugInitManager()))
#define vdebugActive(module)            _vdebugGetModuleLevel(module, \
                                                              &_vdebugProc)
#define vdebugActiveAt(modul,lvl)       _vdebugActiveAt(modul,lvl,&_vdebugProc)

#define vdebugBE(text)                  text
#define vdebugEVAL(stmts)               if (!vdebugActive(vdebugTAG)) \
                                           {/*EMPTY*/} else {stmts;}
#define vdebugIF(bool, stmts)           if (!vdebugActive(vdebugTAG) || \
                                            !(bool)) {/*EMPTY*/} else {stmts;}
#define vdebugAT(level, action)         \
    if (!vdebugActiveAt(vdebugTAG, level)) {/*EMPTY*/} else {action;}
#define vdebugPerror(str)               \
    if (!vdebugActive(vdebugTAG)) {/*EMPTY*/} else perror((str))

#define vdebugAssert(_cond)             \
    vdebugHandledAssert(_cond, NULL, NULL)
#define vdebugMessagedAssert(_cond, msg)\
    vdebugHandledMessagedAssert(_cond, msg, NULL, NULL)

#define vdebugMAdvise(a)                (vdebugActive( vdebugTAG ) \
                                         && (_vdebugAdvise a, 0))
#define vdebugMAdviseAt(a)              (vdebugActive( vdebugTAG ) \
                                         && (_vdebugAdviseAt a, 0))
#define vdebugMInform(a)                (vdebugActive( vdebugTAG ) \
                                         && (_vdebugInform a, 0))
#define vdebugMInformAt(a)              (vdebugActive( vdebugTAG ) \
                                         && (_vdebugInformAt a, 0))
#define vdebugMTrace(a)                 (vdebugActive( vdebugTAG ) \
                                         && (_vdebugTrace a, 0))
#define vdebugMTraceAt(a)               (vdebugActive( vdebugTAG ) \
                                         && (_vdebugTraceAt a, 0))
#define vdebugMWarn(a)                  (vdebugActive( vdebugTAG ) \
                                         && (_vdebugWarn a, 0))
#define vdebugMWarnAt(a)                (vdebugActive( vdebugTAG ) \
                                         && (_vdebugWarnAt a, 0))

#define vdebugAdvise                    if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugAdvise
#define vdebugAdviseAt                  if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugAdviseAt
#define vdebugInform                    if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugInform
#define vdebugInformAt                  if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugInformAt
#define vdebugTrace                     if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugTrace
#define vdebugTraceAt                   if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugTraceAt
#define vdebugWarn                      if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugWarn
#define vdebugWarnAt                    if (!vdebugActive( vdebugTAG )) \
                                           {/*EMPTY*/} else _vdebugWarnAt

#ifndef _vdebugValidateFunction
# ifdef __cplusplus
#  if (vportAMPERSAND_MEMBER_REFERENCE)
#   define _vdebugValidateFunction(f) (&f)
#  elif (vportBROKEN_MEMBER_REFERENCE)
#   define _vdebugValidateFunction(f) 
#  else
#   define _vdebugValidateFunction(f) (f)
#  endif
# else
#  define _vdebugValidateFunction(f) ((void)(f))
# endif
#endif

#define vdebugGetAdviceLevel()          (vdebugStartup(),        \
                                         _vdebugAdviceThreshold)
#define vdebugSetAdviceLevel( level )   (vdebugStartup(),        \
                                         _vdebugAdviceThreshold = (level))
#define vdebugGetInfoLevel()            (vdebugStartup(),        \
                                         _vdebugInfoThreshold)
#define vdebugSetInfoLevel( level )     (vdebugStartup(),        \
                                         _vdebugInfoThreshold = (level))
#define vdebugGetTracingLevel()         (vdebugStartup(),        \
                                         _vdebugTracingThreshold)
#define vdebugSetTracingLevel( level )  (vdebugStartup(),        \
                                         _vdebugTracingThreshold = (level))
#define vdebugGetWarningLevel()         (vdebugStartup(),        \
                                         _vdebugWarningThreshold)
#define vdebugSetWarningLevel( level )  (vdebugStartup(),        \
                                         _vdebugWarningThreshold = (level))

#define vdebugGetAdviceStream()         (vdebugStartup(),        \
                                         _vdebugAdviceStream)
#define vdebugSetAdviceStream(s)        (vdebugStartup(),        \
                                         vdebugAssert((s)!=NULL),       \
                                         _vdebugAdviceStream = (s))
#define vdebugGetInfoStream()           (vdebugStartup(),        \
                                         _vdebugInfoStream)
#define vdebugSetInfoStream(s)          (vdebugStartup(),        \
                                         vdebugAssert((s)!=NULL),       \
                                         _vdebugInfoStream = (s))
#define vdebugGetTracingStream()        (vdebugStartup(),        \
                                         _vdebugTracingStream)
#define vdebugSetTracingStream(s)       (vdebugStartup(),        \
                                         vdebugAssert((s)!=NULL),       \
                                         _vdebugTracingStream = (s))
#define vdebugGetWarningStream()        (vdebugStartup(),        \
                                         _vdebugWarningStream)
#define vdebugSetWarningStream(s)       (vdebugStartup(),        \
                                         vdebugAssert((s)!=NULL),       \
                                         _vdebugWarningStream = (s))

#define vdebugGetModuleLevel( module )  _vdebugGetModuleLevel(module,   \
                                                              &_vdebugProc)

#else /* if (vdebugDEBUG) */

#define vdebugStartup()                 ((void)0)

#define vdebugActive( str )             FALSE
#define vdebugActiveAt( str, level )    FALSE
#define vdebugBE( text )
#define vdebugEVAL( expr )              ((void)0)
#define vdebugAT( level, action )       ((void)0)
#define vdebugIF( bool, expr )          ((void)0)
#define vdebugPerror( str )             ((void)0)
#define vdebugAssert( condition )       ((void)0)
#define vdebugMessagedAssert( cond, msg ) ((void)0)

#define vdebugMAdvise(a)                ((void)0)
#define vdebugMAdviseAt(a)              ((void)0)
#define vdebugMInform(a)                ((void)0)
#define vdebugMInformAt(a)              ((void)0)
#define vdebugMTrace(a)                 ((void)0)
#define vdebugMTraceAt(a)               ((void)0)
#define vdebugMWarn(a)                  ((void)0)
#define vdebugMWarnAt(a)                ((void)0)

#define vdebugAdvise                    if (1) {/*EMPTY*/} else (void)
#define vdebugAdviseAt                  if (1) {/*EMPTY*/} else (void)
#define vdebugInform                    if (1) {/*EMPTY*/} else (void)
#define vdebugInformAt                  if (1) {/*EMPTY*/} else (void)
#define vdebugTrace                     if (1) {/*EMPTY*/} else (void)
#define vdebugTraceAt                   if (1) {/*EMPTY*/} else (void)
#define vdebugWarn                      if (1) {/*EMPTY*/} else (void)
#define vdebugWarnAt                    if (1) {/*EMPTY*/} else (void)

#define vdebugGetAdviceLevel()          vdebugDEFAULT_ADVICE_LEVEL
#define vdebugSetAdviceLevel( level )   ((void)0)
#define vdebugGetInfoLevel()            vdebugDEFAULT_INFO_LEVEL
#define vdebugSetInfoLevel( level )     ((void)0)
#define vdebugGetTracingLevel()         vdebugDEFAULT_TRACING_LEVEL
#define vdebugSetTracingLevel( level )  ((void)0)
#define vdebugGetWarningLevel()         vdebugDEFAULT_WARNING_LEVEL
#define vdebugSetWarningLevel( level )  ((void)0)

#define vdebugSetAdviceStream( s )      ((void)(_vdebugAdviceStream = (s)))
#define vdebugSetInfoStream( s )        ((void)(_vdebugInfoStream = (s)))
#define vdebugSetTracingStream( s )     ((void)(_vdebugTracingStream = (s)))
#define vdebugSetWarningStream( s )     ((void)(_vdebugWarningStream = (s)))

#define vdebugGetAdviceStream()  (_vdebugAdviceStream ? _vdebugAdviceStream \
                                  : vdebugDEFAULT_ADVICE_STREAM)
#define vdebugGetInfoStream()    (_vdebugInfoStream ? _vdebugInfoStream \
                                  : vdebugDEFAULT_INFO_STREAM)
#define vdebugGetTracingStream() (_vdebugTracingStream ? _vdebugTracingStream \
                                  : vdebugDEFAULT_TRACING_STREAM)
#define vdebugGetWarningStream() (_vdebugWarningStream ? _vdebugWarningStream \
                                  : vdebugDEFAULT_WARNING_STREAM)

#define vdebugParseLevel(v)                     0
#define vdebugSetVariables(specs)               ((void)0)
#define vdebugSetLevel(level)                   ((void)0)

#define vdebugGetModuleLevel( module )          0
#define vdebugSetModuleLevel( module, level )   ((void)0)

#endif /* #if (vdebugDEBUG) #else */


#ifndef  vdebugMAKE_STACK
#define  vdebugMAKE_STACK       vdebugDEBUG
#endif


#if (vdebugMAKE_STACK)

#ifdef __cplusplus

class _vdebugUnwindingProcStackFrame : public _vdebugProcStackFrame {
  public:
    _vdebugUnwindingProcStackFrame(int _level, const char *_procname,
                                   const char *_tag)
        {_vdebugTraceEnterAtFrom(this, _level, _procname, NULL, NULL, 0, _tag);};
    ~_vdebugUnwindingProcStackFrame() {_vdebugTraceLeave(this);};
};

#define vdebugProcStackFrameAt(level, _proc)                            \
    _vdebugValidateFunction(_proc);                                     \
    _vdebugUnwindingProcStackFrame _vdebugProc(level,                   \
                                               vportQUOTE(_proc), vdebugTAG)

#endif

#define vdebugTraceEnterAt(level, _proc)                                \
    vdebugTraceEnterAtFrom(level, _proc, NULL, NULL, 0)
#define vdebugTraceEnterAtFrom(level, _proc, t, f, l)                   \
{ _vdebugProcStackFrame _vdebugProc;                                    \
    _vdebugValidateFunction(_proc);                                     \
    vexPushDestructor((void (*)(void*))_vdebugTraceLeave, &_vdebugProc);\
    _vdebugTraceEnterAtFrom(&_vdebugProc, level, vportQUOTE(_proc),     \
                            t, f, l, vdebugTAG);

#define vdebugTraceEnter(_proc) vdebugTraceEnterAt(_vdebugTracingThreshold, \
                                                   _proc)
#define vdebugTraceEnterFrom(p, t, f, l) \
    vdebugTraceEnterAtFrom(_vdebugTracingThreshold, p, t, f, l)

#define vdebugTraceReenter()                                            \
{ _vdebugProcStackFrame _vdebugProc;                                    \
      vexPushDestructor((void (*)(void*))_vdebugTraceLeave, &_vdebugProc); \
      _vdebugTraceReenter(&_vdebugProc);

#define vdebugTraceEnterSubroutine()    vdebugTraceReenter();           \
                                        _vdebugProc.procname=NULL

#define vdebugTraceLeave() vexPopDestructor((void(*)(void*))_vdebugTraceLeave,\
                                            &_vdebugProc); }

#define vdebugTracePop()                                                \
           vexClearDestructor((void (*)(void*))_vdebugTraceLeave, &_vdebugProc)

#define vdebugTraceClear()                                              \
           vexClearDestructor((void (*)(void*))_vdebugTraceLeave, &_vdebugProc)

#define vdebugTraceEnterRawAt(level, _proc)     { _vdebugProcStackFrame _vdebugProc; _vdebugValidateFunction(_proc); _vdebugTraceEnterAtFrom(&_vdebugProc, level, vportQUOTE(_proc), NULL, NULL, 0, vdebugTAG);

#define vdebugTraceEnterRaw(_proc)                                      \
                          vdebugTraceEnterRawAt(_vdebugTracingThreshold, _proc)

#define vdebugTraceLeaveRaw()           _vdebugTraceLeave(&_vdebugProc); }

#define vdebugTracePopRaw()             _vdebugTracePop()

#define vdebugTraceClearRaw()   _vdebugSetProcStackTop(_vdebugProc.caller)

#define vdebugUpdateStack()             _vdebugSetProcStackTop(&_vdebugProc)

#define vdebugGetCurrentProcName()      (_vdebugProc.procname)


#else

#define vdebugTraceEnter( proc )        ((void)0)
#define vdebugTraceEnterAt( lvl, proc ) ((void)0)
#define vdebugTraceEnterFrom(p, t, f, l) ((void)0)
#define vdebugTraceEnterAtFrom(lvl, p, t, f, l) ((void)0)
#define vdebugTraceReenter()            ((void)0)
#define vdebugTraceEnterSubroutine()    ((void)0)
#define vdebugTraceLeave()              ((void)0)
#define vdebugTracePop()                ((void)0)
#define vdebugTraceClear()              ((void)0)

#define vdebugTraceEnterRaw( proc )     ((void)0)
#define vdebugTraceLeaveRaw()           ((void)0)
#define vdebugTracePopRaw()             ((void)0)
#define vdebugTraceClearRaw()           ((void)0)

#define vdebugUpdateStack()             ((void)0)

#define vdebugDumpProcStack( fp )       ((void)0)

#define vdebugGetCurrentProcName()      NULL
#define vdebugGetCurrentModule()        NULL
#define vdebugSetCurrentModule( m )     ((void)0)

#define vdebugGetLastProcName()         NULL


#endif

vportEND_MUST_BE_MACRO

vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vdebugHEADER
#define vdebugHEADER vportNULL_HEADER
#endif

#ifndef  vexINCLUDED    /* !!! incest HACK */
#include vexHEADER
#endif

#endif /* #ifndef vdebugINCLUDED */


/*
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * indent-tabs-mode:nil
 * tab-width:4
 * End:
 */

