/* $Id: vex.h,v 1.89 1997/10/16 20:40:01 robert Exp $ */

#ifndef vexINCLUDED
#define vexINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  verrnoINCLUDED		/* for errno */
#include verrnoHEADER
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdargINCLUDED	/* for va_list */
#include vstdargHEADER
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vsetjmpINCLUDED	/* for jmp_buf */
#include vsetjmpHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * Types
 */

typedef struct _vexHandler _vexHandler;
typedef struct vexClass vexClass;
typedef struct vexException vexException;

typedef void (*vexDestroyer)( void *exception );
typedef void (*vexDumper)( void *exception, FILE *fp );
typedef void (*vexCloner)( void *from, void *to );
typedef void (*vexArgEater)( void *exception, va_list *argList );

typedef vexArgEater vexTag;

typedef vexException vexAbandonException;

typedef vexException vexAppException;

typedef struct vexArgException vexArgException;

typedef vexArgException vexArgNullException;

typedef vexArgException vexArgRangeException;

typedef vexException vexMathException;

typedef vexMathException vexMathDivByZeroException;

typedef vexMathException vexMathDomainException;

typedef vexMathException vexMathRangeException;

typedef vexException vexModuleException;

typedef vexModuleException vexModuleLimitException;

typedef vexModuleException vexModuleStartupException;

typedef vexModuleException vexModuleStateException;

typedef vexModuleException vexModuleUnimplementedException;

typedef vexException vexReturnException;

typedef vexReturnException vexReturnNullException;

typedef vexReturnException vexReturnRangeException;

typedef vexException vexValueException;

typedef vexValueException vexValueNullException;

typedef vexValueException vexValueRangeException;


/*
 * Constants
 */

#if !(vportBAD_WEAK_EXTERNS)
extern vportLINK const vexTag	 vexNULL;
#endif

/* / Exception Argument Eaters */
void	 vexVA_LIST( void *exception, va_list *argList );
void	 vexMESSAGE( void *exception, va_list *argList );
void	 vexMODULE( void *exception, va_list *ap );
void	 vexFILE( void *exception, va_list *argList );
void	 vexPROC_NAME( void *exception, va_list *argList );
void	 vexLINE( void *exception, va_list *argList );
void	 vexERRNO( void *exception, va_list *argList );
void	 vexOS_ERROR( void *exception, va_list *argList );

/* /Arg Exception Argument Eaters */
void	 vexArgPOSITION( void *exception, va_list *argList );

/* /Module Exception Argument Eaters - deprecated: use vexMODULE instead */
void	 vexModuleNAME( void *exception, va_list *argList );


/*
 * Prototypes
 */

void			 vexStartup( void );

void			 vexGenerate( const vexClass *clas, vexTag tag, ... );
void			 vexPropagate( const vexClass *clas, vexTag tag, ... );
void			 vexClear( void );
void			 vexPopHandler( void );
void			 vexPushDestructor( void (*proc)(void *),
					   const void *arg );
void			 vexPopDestructor( void (*proc)(void *),
					  const void *arg );
void			 vexPopDestructorUncalled( void (*proc)(void *),
					  const void *arg );
void			 vexClearDestructor( void (*proc)(void *),
					    const void *arg );

void			 vexDumpChain( FILE *file );
void			 vexDumpHandlerStack( FILE *file );

void			*vexGetExceptionOfClass( const vexClass *clas );

/* 
 * new -- chris (moved vexInitClass, vexDestroyClass to vex.c)
 */
vexException		*vexGetException( void );
vexException		*vexCloneException( void );
void                     vexSetChainData( void *data );
void                    *vexGetChainData( void );
void			 vexRegenerateException( vexException *exception );
void			 vexRestoreException( vexException *exception );
void                     vexFreeClonedException( vexException *exception );

void			 vexInitClass( vexClass *clas, const vexClass *parent,
				      const char *name, int instanceSize,
				      vexDumper dumper );
void			 vexDestroyClass( vexClass *clas );
int 			 vexClassIsConstructed( vexClass *clas );
void                     vexSetClassExceptionDestroyer( vexClass *clas, 
						   vexDestroyer destroyer );
void                     vexSetClassExceptionCloner( vexClass *clas, 
						   vexCloner cloner );

/* 
 * new -- chris
 */
void                     	*vexGetClassData( vexClass *clas );
void                             vexSetClassData( vexClass *clas,
						  void *data );
const vexClass                  *vexGetClassParent( vexClass *clas );
int                              vexHasClassParent( const vexClass *clas, 
						    const vexClass *parent );
const char                      *vexGetClassName( vexClass *clas );
size_t                           vexGetClassSize( vexClass *clas );

/* / Exception calls */
vexException			*vexGetRootException( void );

/* 
 * new -- chris
 */
const vexClass                  *vexGetClass( vexException *exception );

const char			*vexGetMessage( vexException *exception );
const char			*vexGetModule( vexException *exception );
const char			*vexGetFile( vexException *exception );
const char			*vexGetProcName( vexException *exception );
int				 vexGetLine( vexException *exception );
int				 vexGetErrno( vexException *exception );
unsigned long 			 vexGetOsError( vexException *exception );
#if (vportNEED_VMS_ERROR_CODES)
int                              vexGetVMSError( vexException *exception );
#endif
const vexClass			*vexGetRootClass( void );

/* /Abandon Exception calls */
void				 vexGenerateAbandon( void );
void 			 vexGenerateMessagedAbandon( const char *message );
vexAbandonException		*vexGetAbandonException( void );
const vexClass			*vexGetAbandonClass( void );

/* /App Exception calls */
void				 vexGenerateApp( void );
void			 vexGenerateMessagedApp( const char *message );
vexAppException			*vexGetAppException( void );
const vexClass			*vexGetAppClass( void );

/* /Arg Exception calls */
void				 vexGenerateArg( void );
void			 vexGenerateMessagedArg( const char *message );
vexArgException			*vexGetArgException( void );
int				 vexGetArgPosition( vexArgException *exception );
const vexClass			*vexGetArgClass( void );

/* /Arg/Null Exception calls */
void				 vexGenerateArgNull( void );
void			 vexGenerateMessagedArgNull( const char *message );
vexArgNullException		*vexGetArgNullException( void );
const vexClass			*vexGetArgNullClass( void );

/* /Arg/Range Exception calls */
void				 vexGenerateArgRange( void );
void			 vexGenerateMessagedArgRange( const char *message );
vexArgRangeException		*vexGetArgRangeException( void );
const vexClass			*vexGetArgRangeClass( void );

/* /Math Exception calls */
vexMathException		*vexGetMathException( void );
const vexClass			*vexGetMathClass( void );

/* /Math/DivByZero Exception calls */
vexMathDivByZeroException	*vexGetMathDivByZeroException( void );
const vexClass			*vexGetMathDivByZeroClass( void );

/* /Math/Domain Exception calls */
vexMathDomainException		*vexGetMathDomainException( void );
const vexClass			*vexGetMathDomainClass( void );

/* /Math/Range Exception calls */
vexMathRangeException		*vexGetMathRangeException( void );
const vexClass			*vexGetMathRangeClass( void );

/* /Module Exception calls */
vexModuleException		*vexGetModuleException( void );
const vexClass			*vexGetModuleClass( void );

/* /Module/Limit Exception calls */
void				 vexGenerateModuleLimit( void );
void			 vexGenerateMessagedModuleLimit( const char *message );
vexModuleLimitException		*vexGetModuleLimitException( void );
const vexClass			*vexGetModuleLimitClass( void );

/* /Module/Startup Exception calls */
void				 vexGenerateModuleStartup( void );
void		 vexGenerateMessagedModuleStartup( const char *message );
vexModuleStartupException	*vexGetModuleStartupException( void );
const vexClass			*vexGetModuleStartupClass( void );

/* /Module/State Exception calls */
void				 vexGenerateModuleState( void );
void			 vexGenerateMessagedModuleState( const char *message );
vexModuleStateException		*vexGetModuleStateException( void );
const vexClass			*vexGetModuleStateClass( void );

/* /Module/Unimplemented Exception calls */
void				 vexGenerateModuleUnimplemented( void );
void		 vexGenerateMessagedModuleUnimplemented( const char *message );
vexModuleUnimplementedException	*vexGetModuleUnimplementedException( void );
const vexClass			*vexGetModuleUnimplementedClass( void );

/* /Return Exception calls */
void				 vexGenerateReturn( void );
void			 vexGenerateMessagedReturn( const char *message );
vexReturnException		*vexGetReturnException( void );
const vexClass			*vexGetReturnClass( void );

/* /Return/Null Exception calls */
void				 vexGenerateReturnNull( void );
void			 vexGenerateMessagedReturnNull( const char *message );
vexReturnNullException		*vexGetReturnNullException( void );
const vexClass			*vexGetReturnNullClass( void );

/* /Return/Range Exception calls */
void				 vexGenerateReturnRange( void );
void			 vexGenerateMessagedReturnRange( const char *message );
vexReturnRangeException		*vexGetReturnRangeException( void );
const vexClass			*vexGetReturnRangeClass( void );

/* /Value Exception calls */
void				 vexGenerateValue( void );
void			 vexGenerateMessagedValue( const char *message );
vexValueException		*vexGetValueException( void );
const vexClass			*vexGetValueClass( void );

/* /Value/Null Exception calls */
void				 vexGenerateValueNull( void );
void			 vexGenerateMessagedValueNull( const char *message );
vexValueNullException		*vexGetValueNullException( void );
const vexClass			*vexGetValueNullClass( void );

/* /Value/Range Exception calls */
void				 vexGenerateValueRange( void );
void			 vexGenerateMessagedValueRange( const char *message );
vexValueRangeException		*vexGetValueRangeException( void );
const vexClass			*vexGetValueRangeClass( void );


/*
 * * * * * * * * * * * * * * * P R I V A T E * * * * * * * * * * * * * * * * *
 */

typedef struct _vexDestructor _vexDestructor;

struct _vexHandler {

#if (!vportCPLUSPLUS_EXCEPTIONS)
    jmp_buf		 jb;
#endif /* (!vportCPLUSPLUS_EXCEPTIONS) */

    vexException	*entry;
    const _vexHandler	*next;
    void		*priv;
#if (vdebugDEBUG)
    const char		*module;
    const char		*file;
    int			 line;
    int			 depth;
#endif
    _vexDestructor	*destructor;
};

struct vexClass {
    void          	*data;   /* new -- chris */
    const vexClass	*parent;
    const char		*name;
    size_t		 size;
    vexDumper		 dumper;
    vexDestroyer         destroyer;
    vexCloner            cloner;
    unsigned short	 flags;
};

struct vexException {
    const vexClass	*clas;
    vexException	*prev;	/* previous exception in chain */
    const char		*message;
    const char		*module;
    const char		*file;
    const char		*proc;
    int			 line;
    int			 error;
    unsigned long	 oserror;
#if (vportNEED_VMS_ERROR_CODES)
    int                  vmserror;
#endif
    int			 flags;
};

struct vexArgException {
    vexException	 parent;
    int			 position;
};


/*
 * MACROs
 */

#if (!vdebugDEBUG)
#define _vexPushHandler(h,m,f,l)        _vexPushHandler(h)
#define _vexPushUnwinder(h,m,f,l)       _vexPushUnwinder(h)
#define _vexPopHandler(h,m,f,l)         _vexPopHandler(h)
#endif


/*
 * Privately Exported Prototypes
 */

void		 _vexGenerate(const vexClass *clas, vexTag tag, ...);
void		 _vexRegenerateException(vexException *exception, int flag);

#if (vdebugDEBUG)
void		 _vexSetGlobal(const char *modulename, const char *filename,
			       int line);

 /* new -- chris */
vexException    *_vexCreateOfClassDebug(const vexClass *, const char *tag,
					const char *file, int line);

#else

/* new -- chris */
vexException    *vexCreateOfClass(const vexClass *clas);

#endif

void		 _vexPushHandler(_vexHandler *handler, const char *module,
				 const char *file, int line);
void		 _vexPushUnwinder(_vexHandler *handler, const char *module,
				  const char *file, int line);
void		 _vexPopHandler(const _vexHandler *, const char *module,
				const char *file, int line);

vexException	*_vexGetCurrentChain(void);
void		 _vexSetCurrentChain(vexException *exception);

void		 _vexPushDestructor( void (*proc)(void *), const void *arg );
void		 _vexPopDestructor( void (*proc)(void *), const void *arg );
void		 _vexPopDestructorUncalled( void (*proc)(void *), 
					    const void *arg );


/*
 * Privately Exported Globals
 */

extern vportLINK vexClass	 _vexClass;
extern vportLINK vexClass	 _vexAbandonClass;
extern vportLINK vexClass	 _vexAppClass;
extern vportLINK vexClass	 _vexArgClass;
extern vportLINK vexClass	 _vexArgNullClass;
extern vportLINK vexClass	 _vexArgRangeClass;
extern vportLINK vexClass	 _vexMathClass;
extern vportLINK vexClass	 _vexMathDivByZeroClass;
extern vportLINK vexClass	 _vexMathDomainClass;
extern vportLINK vexClass	 _vexMathRangeClass;
extern vportLINK vexClass	 _vexModuleClass;
extern vportLINK vexClass	 _vexModuleLimitClass;
extern vportLINK vexClass	 _vexModuleStartupClass;
extern vportLINK vexClass	 _vexModuleStateClass;
extern vportLINK vexClass	 _vexModuleUnimplementedClass;
extern vportLINK vexClass	 _vexReturnClass;
extern vportLINK vexClass	 _vexReturnNullClass;
extern vportLINK vexClass	 _vexReturnRangeClass;
extern vportLINK vexClass	 _vexValueClass;
extern vportLINK vexClass	 _vexValueNullClass;
extern vportLINK vexClass	 _vexValueRangeClass;

/*
 * MACROs
 */

vportBEGIN_MUST_BE_MACRO

#if (vdebugDEBUG)
#define vexGenerate	if (_vexSetGlobal(vdebugTAG, __FILE__, __LINE__),0) \
                        {/*EMPTY*/} else _vexGenerate
#else
#define vexGenerate	_vexGenerate
#endif

#if (vdebugDEBUG)
#define vexRegenerateException(ex) \
	if (_vexSetGlobal(vdebugTAG, __FILE__, __LINE__),0) \
        {/*EMPTY*/} else _vexRegenerateException(ex, 1)
#else
#define vexRegenerateException(ex) \
	_vexRegenerateException(ex, 1)
#endif

#if (vdebugDEBUG)
#define vexRestoreException(ex) \
	if (_vexSetGlobal(vdebugTAG, __FILE__, __LINE__),0) \
        {/*EMPTY*/} else _vexRegenerateException(ex, 0)
#else
#define vexRestoreException(ex) \
	_vexRegenerateException(ex, 0)
#endif

#define vexPropagate	vexGenerate

#define vexClear()	(_vexSetCurrentChain(_vexLocalHandler.entry), errno=0)

/*
 * new -- chris
 */

enum {
 _vexCONSTRUCTED = 1
};

#if (vdebugDEBUG)

#define vexConstructClassLiteral( parent, name, type, dumper )	   \
    {NULL, \
     (parent), (name), sizeof (type), (dumper), NULL, NULL, _vexCONSTRUCTED}

#else

#define vexConstructClassLiteral( parent, name, type, dumper )	\
    {NULL,    \
     (parent), (name), sizeof (type), (dumper), NULL, NULL, _vexCONSTRUCTED}

#endif

#define vexClassIsConstructed( clas )   (((clas)->flags&_vexCONSTRUCTED)!=0)
#define vexDestroyClass(c)

vportEND_MUST_BE_MACRO

/*
 * new -- chris 
 */
#define vexGetClassData( clas )         ((clas)->data)
#define vexSetClassData( clas, d ) 	((clas)->data=(d))
#define vexGetClassParent( clas )       ((clas)->parent)
#define vexGetClassName( clas )         ((clas)->name)
#define vexGetClassSize( clas )         ((clas)->size)
#define vexSetClassExceptionDestroyer( clas, dest ) \
    ((clas)->destroyer = dest)
#define vexSetClassExceptionCloner( clas, clon ) \
    ((clas)->cloner = clon)


#define vexNULL				((vexTag)NULL)

#define vexGetRootException()		((vexException *) vexGetExceptionOfClass( &_vexClass ))

/*
 * new -- chris 
 */
#define vexGetClass( exception )        ((exception)->clas)

#define vexGetMessage( exception )	((exception)->message)

#define vexGetModule( exception )	((exception)->module)
#define vexGetFile( exception )		((exception)->file)
#define vexGetProcName( exception )	((exception)->proc)
#define vexGetLine( exception )		((exception)->line)

#define vexGetErrno( exception )	((exception)->error)
#define vexGetOsError( exception )	((exception)->oserror)

#if (vportNEED_VMS_ERROR_CODES)
#define vexGetVMSError( exception )     ((exception)->vmserror)
#endif

vportBEGIN_MUST_BE_MACRO
#define vexGetRootClass()			(&_vexClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateAbandon()	vexGenerate( vexGetAbandonClass(), vexNULL )
#define vexGenerateMessagedAbandon( msg ) vexGenerate( vexGetAbandonClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetAbandonException()	((vexAbandonException *) vexGetExceptionOfClass( &_vexAbandonClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetAbandonClass()		(&_vexAbandonClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateApp()	vexGenerate( vexGetAppClass(), vexNULL )
#define vexGenerateMessagedApp( msg ) vexGenerate( vexGetAppClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetAppException()		((vexAppException *) vexGetExceptionOfClass( &_vexAppClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetAppClass()		(&_vexAppClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateArg()		vexGenerate( vexGetArgClass(), vexNULL )
#define vexGenerateMessagedArg( msg )	vexGenerate( vexGetArgClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetArgException()		((vexArgException *) vexGetExceptionOfClass( &_vexArgClass ))
#define vexGetArgPosition( exception )	((exception)->position)

vportBEGIN_MUST_BE_MACRO
#define vexGetArgClass()		(&_vexArgClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateArgNull()		  vexGenerate( vexGetArgNullClass(), vexNULL )
#define vexGenerateMessagedArgNull( msg ) vexGenerate( vexGetArgNullClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetArgNullException()	((vexArgNullException *) vexGetExceptionOfClass( &_vexArgNullClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetArgNullClass()		(&_vexArgNullClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateArgRange()	           vexGenerate( vexGetArgRangeClass(), vexNULL )
#define vexGenerateMessagedArgRange( msg ) vexGenerate( vexGetArgRangeClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetArgRangeException()	((vexArgRangeException *) vexGetExceptionOfClass( &_vexArgRangeClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetArgRangeClass()		(&_vexArgRangeClass)
vportEND_MUST_BE_MACRO

#define vexGetMathException()		((vexMathException *) vexGetExceptionOfClass( &_vexMathClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetMathClass()		(&_vexMathClass)
vportEND_MUST_BE_MACRO

#define vexGetMathDivByZeroException()	((vexMathDivByZeroException *) vexGetExceptionOfClass( &_vexMathDivByZeroClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetMathDivByZeroClass()	(&_vexMathDivByZeroClass)
vportEND_MUST_BE_MACRO

#define vexGetMathDomainException()	((vexMathDomainException *) vexGetExceptionOfClass( &_vexMathDomainClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetMathDomainClass()		(&_vexMathDomainClass)
vportEND_MUST_BE_MACRO

#define vexGetMathRangeException()	((vexMathRangeException *) vexGetExceptionOfClass( &_vexMathRangeClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetMathRangeClass()		(&_vexMathRangeClass)
vportEND_MUST_BE_MACRO

#define vexGetModuleException()		((vexModuleException *) vexGetExceptionOfClass( &_vexModuleClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetModuleClass()		(&_vexModuleClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateModuleLimit()              vexGenerate( vexGetModuleLimitClass(), vexNULL )
#define vexGenerateMessagedModuleLimit( msg ) vexGenerate( vexGetModuleLimitClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetModuleLimitException()	((vexModuleLimitException *) vexGetExceptionOfClass( &_vexModuleLimitClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetModuleLimitClass()	(&_vexModuleLimitClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateModuleStartup() \
				vexGenerate( vexGetModuleStartupClass(), vexNULL )
#define vexGenerateMessagedModuleStartup( msg ) \
				vexGenerate( vexGetModuleStartupClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetModuleStartupException()	((vexModuleStartupException *) vexGetExceptionOfClass( &_vexModuleStartupClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetModuleStartupClass()	(&_vexModuleStartupClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateModuleState() \
				vexGenerate( vexGetModuleStateClass(), vexNULL )
#define vexGenerateMessagedModuleState( msg ) \
				vexGenerate( vexGetModuleStateClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetModuleStateException()	((vexModuleStateException *) vexGetExceptionOfClass( &_vexModuleStateClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetModuleStateClass()	(&_vexModuleStateClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateModuleUnimplemented() \
			vexGenerate( vexGetModuleUnimplementedClass(), vexNULL )
#define vexGenerateMessagedModuleUnimplemented( msg ) \
			vexGenerate( vexGetModuleUnimplementedClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetModuleUnimplementedException()	((vexModuleUnimplementedException *) vexGetExceptionOfClass( &_vexModuleUnimplementedClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetModuleUnimplementedClass()	(&_vexModuleUnimplementedClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateReturn()	         vexGenerate( vexGetReturnClass(), vexNULL )
#define vexGenerateMessagedReturn( msg ) vexGenerate( vexGetReturnClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetReturnException()		((vexReturnException *) vexGetExceptionOfClass( &_vexReturnClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetReturnClass()		(&_vexReturnClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateReturnNull()	             vexGenerate( vexGetReturnNullClass(), vexNULL )
#define vexGenerateMessagedReturnNull( msg ) vexGenerate( vexGetReturnNullClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetReturnNullException()	((vexReturnNullException *) vexGetExceptionOfClass( &_vexReturnNullClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetReturnNullClass()		(&_vexReturnNullClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateReturnRange()              vexGenerate( vexGetReturnRangeClass(), vexNULL )
#define vexGenerateMessagedReturnRange( msg ) vexGenerate( vexGetReturnRangeClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetReturnRangeException()	((vexReturnRangeException *) vexGetExceptionOfClass( &_vexReturnRangeClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetReturnRangeClass()	(&_vexReturnRangeClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateValue()		vexGenerate( vexGetValueClass(), vexNULL )
#define vexGenerateMessagedValue( msg )	vexGenerate( vexGetValueClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetValueException()		((vexValueException *) vexGetExceptionOfClass( &_vexValueClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetValueClass()		(&_vexValueClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateValueNull()		    vexGenerate( vexGetValueNullClass(), vexNULL )
#define vexGenerateMessagedValueNull( msg ) vexGenerate( vexGetValueNullClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetValueNullException()	((vexValueNullException *) vexGetExceptionOfClass( &_vexValueNullClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetValueNullClass()		(&_vexValueNullClass)
vportEND_MUST_BE_MACRO

vportBEGIN_MUST_BE_MACRO
#define vexGenerateValueRange()		     vexGenerate( vexGetValueRangeClass(), vexNULL )
#define vexGenerateMessagedValueRange( msg ) vexGenerate( vexGetValueRangeClass(), vexMESSAGE, msg, vexNULL )
vportEND_MUST_BE_MACRO

#define vexGetValueRangeException()	((vexValueRangeException *) vexGetExceptionOfClass( &_vexValueRangeClass ))

vportBEGIN_MUST_BE_MACRO
#define vexGetValueRangeClass()		(&_vexValueRangeClass)
vportEND_MUST_BE_MACRO

#define vexModuleNAME			vexMODULE


vportBEGIN_MUST_BE_MACRO

#if (vportCPLUSPLUS_EXCEPTIONS)

#define vexWITH_HANDLING						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  try { {
    
#define vexON_EXCEPTION							\
    } _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ ); } \
  catch(vexException * _vexLocalException) { {

#define vexEND_HANDLING		; (void)&_vexLocalException;} vexClear(); } }

#define vexUNWIND_PROTECT						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  try { {

#define _vexUNWIND_PROTECT						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushUnwinder( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
      try { {

#define vexON_UNWIND							\
  } _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ ); \
  } catch(...) {} {

#define vexEND_UNWIND							\
    ; } if (_vexGetCurrentChain() > _vexLocalHandler.entry)		\
    vexPropagate(NULL, vexNULL); }

#define vexWITH_MATCHING						\
{ vexException *_vexLocalThrown = NULL; _vexHandler _vexLocalHandler;	\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  try { {

#define vexMATCH( eclass )						\
    } _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ ); \
  } catch(vexException * _vexLocalException) {				\
    _vexLocalThrown = _vexLocalException;				\
    if (vexGetExceptionOfClass(eclass)) {

#define vexMATCH_NEXT( eclass )						\
   ; _vexLocalThrown = NULL; }					        \
    if (_vexLocalThrown == NULL) vexClear(); }				\
  if (_vexLocalThrown != NULL) {					\
    if (vexGetExceptionOfClass(eclass)) {

#define vexMATCH_REST							\
   ; _vexLocalThrown = NULL; }						\
    if (_vexLocalThrown == NULL) vexClear(); }				\
  if (_vexLocalThrown != NULL) { {

#define vexMATCH_ALL							\
    } _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ ); \
  } catch(vexException * _vexLocalException) {				\
    _vexLocalThrown = _vexLocalException; {

#define vexEND_MATCHING							\
   ; _vexLocalThrown = NULL; }						\
    if (_vexLocalThrown == NULL) vexClear(); }				\
  if (_vexLocalThrown != NULL) vexPropagate(NULL, vexNULL); }

#else

#define vexWITH_HANDLING						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  if (setjmp( _vexLocalHandler.jb ) == 0) { {
    
#define vexON_EXCEPTION							\
  } _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__); } \
  else { {

#define vexEND_HANDLING		; } vexClear(); } }

#define vexUNWIND_PROTECT						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  if (setjmp( _vexLocalHandler.jb ) == 0) { { {

#define _vexUNWIND_PROTECT						\
{ _vexHandler _vexLocalHandler;						\
  _vexPushUnwinder( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  if (setjmp( _vexLocalHandler.jb ) == 0) { { {

#define vexON_UNWIND							\
  } } _vexPopHandler(&_vexLocalHandler, vdebugTAG, __FILE__, __LINE__); } { { {

#define vexEND_UNWIND							\
  ; } } if (_vexGetCurrentChain() > _vexLocalHandler.entry)		\
  vexPropagate(NULL, vexNULL); } }

#define vexWITH_MATCHING						\
{ _vexHandler _vexLocalHandler; int _vexRetValue;			\
  _vexPushHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__ );	\
  if ( ( _vexRetValue = setjmp( _vexLocalHandler.jb )) == 0 ) { {

#define vexMATCH(eclass)						\
    } if (!_vexRetValue)						\
     _vexPopHandler( &_vexLocalHandler, vdebugTAG, __FILE__, __LINE__); \
      else vexClear();							\
  } else if ( vexGetExceptionOfClass( eclass ) ) { {

#define vexMATCH_NEXT(eclass)	vexMATCH(eclass)

#define vexMATCH_REST		vexMATCH(vexGetRootClass())

#define vexMATCH_ALL		vexMATCH(vexGetRootClass())

#define vexEND_MATCHING							\
    ; } if (_vexRetValue) vexClear();					\
  } else { vexPropagate( NULL, vexNULL ); } }

#endif

#undef  vexUNWIND_PROTECT
#define vexUNWIND_PROTECT _vexUNWIND_PROTECT

#define vexPushDestructor(h,a)		{_vexPushDestructor(h,a)
#define vexPopDestructor(h,a)		_vexPopDestructor(h,a);}
#define vexPopDestructorUncalled(h,a)	_vexPopDestructorUncalled(h,a);}
#define vexClearDestructor(h,a)		_vexPopDestructor(h,a)

vportEND_MUST_BE_MACRO


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vexHEADER
#define vexHEADER vportNULL_HEADER
#endif

#endif /* #ifndef vexINCLUDED */

