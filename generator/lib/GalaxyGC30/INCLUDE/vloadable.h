/* $Id: vloadable.h,v 1.68 1997/09/19 22:02:54 robert Exp $ */

/************************************************************

    vloadable.h

    C Interface file for the Class Manager loadable objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vloadableINCLUDED
#define vloadableINCLUDED

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

#ifndef  vfsINCLUDED
#include vfsHEADER
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


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

enum 
{
  vloadableMAX_ALIAS_CHAIN = 8
};

#if (vportCPLUSPLUS_SOURCE)

#define vloadableDONT_INIT	vsuppressDONT_INIT
#define vloadableDONT_LOAD	(vresourceNULL)

#define vloadableINLINE_LOAD_CONSTRUCTOR(type, base)		\
  type(vresource resource) : base(vsuppressDONT_INIT)		\
    { this->MaybeLoad(resource); }

#define vloadableINLINE_COPY_CONSTRUCTOR(type, base)		\
  type(const type &original) : base(vsuppressDONT_INIT)		\
    { this->MaybeCopy(&original); }

#define vloadableINLINE_CONSTRUCTORS(type, base)		\
    vkindTYPED_INLINE_DEFAULT_CONSTRUCTOR(type, base)		\
    vkindTYPED_INLINE_SUPPRESS_CONSTRUCTOR(type, base)		\
    vloadableINLINE_LOAD_CONSTRUCTOR(type, base)		\
    vloadableINLINE_COPY_CONSTRUCTOR(type, base)		\
    vkindTYPED_INLINE_DESTRUCTOR(type, base)


/* deprecated */

#define vloadableDECLARATION(type)				\
    _vkindTYPED_NEW_UNINITED_DECL();				\
    _vloadableREQUEST_SUB_LOAD_DECL(type)

#define vloadableDEFINITION(type)				\
    _vkindTYPED_NEW_UNINITED_DEF(type)				\
    _vloadableREQUEST_SUB_LOAD_DEF(type)


#endif /* (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vloadableClass		vloadableClass;

typedef vresource (*vloadableResolveResourceFunc)(vscribe *path,
						  vloadableClass *clas);
typedef vloadableClass *(*vloadableDetermineResourceClassFunc)(
							vresource resource);

#if (!vportCPLUSPLUS_SOURCE)

#ifdef	__cplusplus
struct vloadable {
    vinstance                       instance;
    const vname                    *tag;
    vstr		   	   *alias;
};
#else
typedef struct vloadable		vloadable;
#endif

#else /* if (vportCPLUSPLUS_SOURCE) */


class _vloadableCLASS_LINK vloadable;

typedef void (*vloadableStartupProc)(void);
typedef vloadable *(*vloadableNewProc)();

typedef struct _vloadableSubLoadInfo	_vloadableSubLoadInfo;
typedef struct _vloadableSubLoadElement	_vloadableSubLoadElement;

class _vloadableCLASS_LINK vloadable : public vkindTyped
  {
  public:

    vkindTYPED_DECLARATION(vloadable);

			vloadable();
			vloadable(vresource resource);
			vloadable(const vloadable &original);
			vloadable(vsuppress *);
		       ~vloadable();

    static const vkind	*LoadKind(vresource resource);
    static vloadable	*NewUninitedByResource(vresource resource);
    static vloadable	*NewUninitedByResource(vresource resource,
					       vkind *base, vbool force);
    static void		RegisterLoad(char *kind,
				     vloadableStartupProc startupProc,
				     vkindNewTypedProc newProc);
    static void		Startup();

    virtual vbool	CanLoad(vresource resource) const;
    virtual vloadable	*Clone() const;
    virtual void	Copy(vloadable *original);
    virtual void	Dump(FILE *stream);
	    const vchar *GetAlias() const;
	    const vname	*GetTag() const;
	    void	Load(vresource resource);
    virtual void	RegisterSubLoad(const vname *tag, vkindTyped *sub);
	    void	SetAlias(const vchar *alias);
    virtual void	SetAliasScribed(vscribe *alias);
    virtual void	SetTag(const vname *tag);
    virtual void	Store(vresource resource);
	    vloadable	*SubLoad(vresource resource);

//protected:
    int			WillLoad() const;
    int			HasSubLoads() const;
    void		VerifySubLoads() const;

    virtual void	Init();
    virtual void	LoadInit(vresource resource);
    virtual void	CopyInit(vloadable *original);
    virtual void	Destroy();

    void		MaybeInit();
    void		MaybeLoad(vresource resource);
    void		MaybeCopy(const vloadable *original);

  private:
    const vname			*tag;
    vstr		   	*alias;
    _vloadableSubLoadInfo	*subLoadInfo;

    friend vportDECL void vportLINK _vloadableDumpException( void *ex, FILE *fp );
    friend vportDECL void vportLINK _vloadableDumpUnloadedSubsException( void *ex, FILE *fp );
  };

typedef struct vloadableException
  {
    vexException		parent;
    vloadable			*instance;
    const vname			*kindName;

  }				   vloadableException;

typedef vloadableException	   vloadableNoResourceKindException;
typedef vloadableException	   vloadableUnknownKindException;
typedef vloadableException	   vloadableWrongKindException;
typedef vloadableException	   vloadableImproperSubLoadException;
typedef vloadableException	   vloadableUnloadedSubsException;

#endif /* if (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vloadableStartup(void);


/*
 * loadable objects
 */

vloadableClass *vloadableGetDefaultClass(
    void
    );

vinstance *vloadableGetInstance(
    vloadable			        *object
    );

vloadableClass *vloadableGetClass(
    vloadable			        *object
    );

vloadable *vloadableCreateOfClass(
    vloadableClass			*clas
    );

void vloadableInitOfClass(
    vloadable				*object,
    vloadableClass			*clas
    );

void vloadableDestroy(
    vloadable				*object
    );

vloadable *vloadableCloneOfClass(
    vloadable				*object,
    vloadableClass			*clas
    );

vloadable *vloadableCloneOfSubclass(
    vloadable				*object,
    vloadableClass			*base
    );

vloadable *vloadableClone(
    vloadable				*object
    );

void vloadableCopyInitOfClass(
    vloadable				*object,
    vloadable				*target,
    vloadableClass			*clas
    );

void vloadableCopyInitOfSubclass(
    vloadable				*object,
    vloadable				*target,
    vloadableClass			*base
    );

void vloadableCopyInit(
    vloadable				*object,
    vloadable				*target
    );

vloadable *vloadableLoadOfClass(
    vresource				 resource,
    vloadableClass			*clas
    );

vloadable *vloadableLoadOfSubclass(
    vresource				 resource,
    vloadableClass			*base
    );

vloadable *vloadableLoad(
    vresource				 resource
    );

void vloadableLoadInitOfClass(
    vloadable				*object,
    vresource				 resource,
    vloadableClass			*clas
    );

void vloadableLoadInitOfSubclass(
    vloadable				*object,
    vresource				 resource,
    vloadableClass			*base
    );

void vloadableLoadInit(
    vloadable				*object,
    vresource				 resource
    );

void vloadableCopy(
    vloadable				*object,
    vloadable				*target
    );

void vloadableCopyCommon(
    vloadable				*object,
    vloadable				*target
    );

void vloadableStore(
    vloadable				*object,
    vresource				 resource
    );

void vloadableDump(
    vloadable				*object,
    FILE				*stream
    );

vloadable *vloadableResolve(
    const vchar				*path
    );

vloadable *vloadableResolveScribed(
    vscribe				*path
    );

vloadable *vloadableResolveLiteral(
    const char				*path
    );

const vname *vloadableGetTag(
    vloadable			        *object
    );

void vloadableSetTag(
    vloadable				*object,
    const vname				*tag
    );

const vchar *vloadableGetAlias(
    vloadable			        *object
    );

void vloadableSetAlias(
    vloadable				*object,
    const vchar				*alias
    );

void vloadableSetAliasScribed(
    vloadable				*object,
    vscribe				*alias
    );

/*
 * utility routines
 */

void vclassStoreInheritance(
    void				*clas,
    vresource				 resource
    );

vloadableClass *vloadableTestGetResourceClass(
    vresource				 resource
    );

vloadableClass *vloadableGetResourceClass(
    vresource				 resource
    );

vloadableClass *vloadableGetResourceSubclass(
    vresource				 resource,
    vloadableClass			*base
    );

int vloadableIsResourceKindOf(
    vresource				 resource,
    vclass				 *clas
    );

vloadableClass *vloadableGetSourceSubclass(
    vloadable				*source,
    vloadableClass			*base
    );

int vloadableIsKindOf(
    const vloadable			*object,
    const vclass			*clas
    );

vloadableDetermineResourceClassFunc vloadableGetDetermineResourceClassFunc(
    void
    );

void vloadableSetDetermineResourceClassFunc(
    vloadableDetermineResourceClassFunc         func
    );
/*
 * Alias resource routines.
 */

vscribe *vloadableGetResourceAlias(
    vresource				resource
    );

vloadableClass *vloadableGetResourceAliasClass(
    vresource				resource
    );

void vloadableStoreResourceAlias(
    vresource				resource,
    const vchar				*alias,
    vloadableClass			*clas
    );

void vloadableStoreResourceAliasScribed(
    vresource				resource,
    vscribe				*alias,
    vloadableClass			*clas
    );

vresource vloadableTraverseResourceAlias(
    vresource				resource
    );

vresource vloadableTraverseResourceAliasOnce(
    vresource				resource
    );

/*
 * Resource resolving
 */

vresource vloadableResolveResource(
    const vchar				*path
    );

vresource vloadableResolveResourceScribed(
    vscribe				*path
    );

vresource vloadableResolveResourceLiteral(
    const char				*path
    );

vresource vloadableResolveResourceOfClass(
    const vchar				*path,
    vloadableClass			*clas
    );

vresource vloadableResolveResourceOfClassScribed(
    vscribe				*path,
    vloadableClass			*clas
    );

vresource vloadableResolveResourceOfClassLiteral(
    const vchar				*path,
    vloadableClass			*clas
    );

/*
 * Resource resolver hooks
 */

vloadableResolveResourceFunc vloadableGetResolveResourceFunc(
    void
    );

void vloadableSetResolveResourceFunc(
    vloadableResolveResourceFunc         func
    );


#if (vportCPLUSPLUS_SOURCE)

vloadableException		*vloadableGetException();

vloadableNoResourceKindException   *vloadableGetNoResourceKindException();
vloadableUnknownKindException	   *vloadableGetUnknownKindException();
vloadableWrongKindException	   *vloadableGetWrongKindException();
vloadableImproperSubLoadException   *vloadableGetImproperSubLoadException();
vloadableUnloadedSubsException	   *vloadableGetUnloadedSubsException();

const vexClass			*vloadableGetExceptionClass();

const vexClass			  *vloadableGetNoResourceKindExceptionClass();
const vexClass			  *vloadableGetUnknownKindExceptionClass();
const vexClass			  *vloadableGetWrongKindExceptionClass();
const vexClass			  *vloadableGetImproperSubLoadExceptionClass();
const vexClass			  *vloadableGetUnloadedSubsExceptionClass();

/* /Loadable Exception Argument Eater */
vportDECL void vportLINK vloadableINSTANCE(void *exception, va_list *argList);
vportDECL void vportLINK vloadableKIND(void *exception, va_list *argList);
vportDECL void vportLINK vloadableKIND_NAME(void *exception, va_list *argList);

vloadable      *vloadableGetExceptionInstance( vloadableException *exception );
const vname    *vloadableGetExceptionKindName( vloadableException *exception );

#endif /* (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#ifndef	__cplusplus
struct vloadable {
    vinstance                       instance;
    const vname                    *tag;
    vstr		   	   *alias;
};
#endif

#endif /* (!vportCPLUSPLUS_SOURCE) */

#define vloadableCLASS(SUPER, OBJECT)                                       \
    vinstanceCLASS(SUPER, OBJECT);                                          \
    vclassMETHOD(vloadableCOPY, (OBJECT *object, OBJECT *target));          \
    vclassMETHOD(vloadableCOPY_INIT, (OBJECT *object, OBJECT *target));     \
    vclassMETHOD(vloadableLOAD_INIT, (OBJECT *object, vresource resource)); \
    vclassMETHOD(vloadableSTORE, (OBJECT *object, vresource resource));     \
    vclassMETHOD(vloadableDUMP, (OBJECT *object, FILE *stream));            \
    vclassMETHOD(vloadableSET_TAG, (OBJECT *object, const vname *tag));     \
    vclassMETHOD(vloadableSET_ALIAS_SCRIBED,                     	    \
		 (OBJECT *object, vscribe *alias))

struct vloadableClass {
    vloadableCLASS(vloadableClass, vloadable);
};


/*
 * * * * * * * * * * PRIVATE DECLARATIONS * * * * * * * * * *
 */

#if (vportCPLUSPLUS_SOURCE)

/* type *type::RequestSubLoad(vkindTyped *parent, const char *tag); */

#define _vloadableREQUEST_SUB_LOAD_DECL(type)			\
    static type *RequestSubLoad(vloadable *parent,		\
				const char *tag)

#define _vloadableREQUEST_SUB_LOAD_DEF(type)			\
  type *type::RequestSubLoad(vloadable *parent,			\
			     const char *tag)			\
    {								\
      vkindTyped *sub = type::NewUninited();			\
      parent->RegisterSubLoad(vnameInternGlobalLiteral(tag), sub); \
      return((type *) sub);					\
    }

vportIMPORT_CONST const vexClass vportLINK _vloadableExceptionClass;

vportIMPORT_CONST const vexClass vportLINK _vloadableNoResourceKindExceptionClass;
vportIMPORT_CONST const vexClass vportLINK  _vloadableUnknownKindExceptionClass;
vportIMPORT_CONST const vexClass vportLINK  _vloadableWrongKindExceptionClass;
vportIMPORT_CONST const vexClass vportLINK  _vloadableImproperSubLoadExceptionClass;
vportIMPORT_CONST const vexClass vportLINK  _vloadableUnloadedSubsExceptionClass;

struct _vloadableSubLoadElement
  {
    const vname 		*tag;
    vloadable			*loadable;
  };

struct _vloadableSubLoadInfo
  {
    int				count;
    int				alloc;
    _vloadableSubLoadElement	*elements;
  };

#endif /* (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

vloadable *_vloadableCloneOfClassDebug(
    vloadable                      *object,
    vloadableClass		   *base,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vloadable *_vloadableCloneOfSubclassDebug(
    vloadable                      *object,
    vloadableClass		   *base,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vloadable *_vloadableLoadOfClassDebug(
    vresource                       resource,
    vloadableClass		   *base,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vloadable *_vloadableLoadOfSubclassDebug(
    vresource                       resource,
    vloadableClass		   *base,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

extern vportLINK vloadableResolveResourceFunc _vloadableResolveResourceFunc;
extern vportLINK vloadableDetermineResourceClassFunc
					_vloadableDetermineResourceClassFunc;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * loadable objects
 */

#define vloadableGetInstance(o)       vportBASE_OBJECT(o, instance)
#define vloadableGetClass(o) \
    ((vloadableClass*)vinstanceGetClass(vloadableGetInstance(o)))

#define vloadableCreateOfClass(c) \
    ((vloadable *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vloadableInitOfClass(o,c) \
    vinstanceInitOfClass(vloadableGetInstance(o), (vinstanceClass *)(c))
#define vloadableClone(o) \
    vloadableCloneOfSubclass((o), vloadableGetDefaultClass())
#define vloadableCopyInit(o, i) \
    vloadableCopyInitOfSubclass((o), (i), vloadableGetDefaultClass())
#define vloadableLoad(r) \
    vloadableLoadOfSubclass((r), vloadableGetDefaultClass())
#define vloadableLoadInit(i, r) \
    vloadableLoadInitOfSubclass((i), (r), vloadableGetDefaultClass())

#define vloadableResolve(p) \
    ((vloadable *) vinstanceResolveOfClass(p, vloadableGetDefaultClass()))
#define vloadableResolveScribed(p) \
    ((vloadable *) vinstanceResolveOfClassScribed(p, \
						  vloadableGetDefaultClass()))
#define vloadableResolveLiteral(p) \
    ((vloadable *) vinstanceResolveOfClassLiteral(p, \
						  vloadableGetDefaultClass()))

#define vloadableDestroy(o) \
    vinstanceDestroy(vloadableGetInstance(o))

#if (vdebugDEBUG)
#define vloadableCloneOfClass(o, c) \
    _vloadableCloneOfClassDebug(o, c, vmemTAG, __FILE__, __LINE__)
#define vloadableCloneOfSubclass(o, c) \
    _vloadableCloneOfSubclassDebug(o, c, vmemTAG, __FILE__, __LINE__)
#define vloadableLoadOfClass(o, c) \
    _vloadableLoadOfClassDebug(o, c, vmemTAG, __FILE__, __LINE__)
#define vloadableLoadOfSubclass(o, c) \
    _vloadableLoadOfSubclassDebug(o, c, vmemTAG, __FILE__, __LINE__)
#endif

#if (!vportCPLUSPLUS_SOURCE)

#define vloadableGetTag(o)          ((o)->tag)
#define vloadableGetAlias(o)        ((o)->alias)

#else /* (vportCPLUSPLUS_SOURCE) */

#define _vloadableGetTag_C(o)          ((o)->GetTag())
#define _vloadableGetAlias_C(o)        ((o)->GetAlias())

#endif /* (vportCPLUSPLUS_SOURCE) */

#define vloadableIsKindOf(o,c) \
    vinstanceIsKindOf(vloadableGetInstance(o), c)

#define vloadableGetDetermineResourceClassFunc() \
    (_vloadableDetermineResourceClassFunc)
#define vloadableSetDetermineResourceClassFunc(f) \
    (_vloadableDetermineResourceClassFunc = (f))

#define vloadableGetResolveResourceFunc() \
    (_vloadableResolveResourceFunc)
#define vloadableSetResolveResourceFunc(f) \
    (_vloadableResolveResourceFunc = (f))

#define vloadableResolveResource(p) \
	(*_vloadableResolveResourceFunc)(vcharScribe(p), \
					 vloadableGetDefaultClass())
#define vloadableResolveResourceScribed(p) \
	(*_vloadableResolveResourceFunc)(p, vloadableGetDefaultClass())
#define vloadableResolveResourceLiteral(p) \
	(*_vloadableResolveResourceFunc)(vcharScribeLiteral(p),\
					 vloadableGetDefaultClass())
#define vloadableResolveResourceOfClass(p,c) \
	(*_vloadableResolveResourceFunc)(vcharScribe(p), c)
#define vloadableResolveResourceOfClassScribed(p,c) \
	(*_vloadableResolveResourceFunc)(p, c)
#define vloadableResolveResourceOfClassLiteral(p,c) \
	(*_vloadableResolveResourceFunc)(vcharScribeLiteral(p), c)

#if (vportCPLUSPLUS_SOURCE)

#define vloadableGetException()	\
  ((vloadableException *) \
      vexGetExceptionOfClass(&_vloadableExceptionClass))

#define vloadableGetNoResourceKindException()	\
  ((vloadableNoResourceKindException *) \
      vexGetExceptionOfClass(&_vloadableNoResourceKindExceptionClass))

#define vloadableGetUnknownKindException()	\
  ((vloadableUnknownKindException *) \
      vexGetExceptionOfClass(&_vloadableUnknownKindExceptionClass))

#define vloadableGetWrongKindException()	\
  ((vloadableWrongKindException *) \
      vexGetExceptionOfClass(&_vloadableWrongKindExceptionClass))

#define vloadableGetImproperSubLoadException()	\
  ((vloadableImproperSubLoadException *) \
      vexGetExceptionOfClass(&_vloadableImproperSubLoadExceptionClass))

#define vloadableGetUnloadedSubsException()	\
  ((vloadableUnloadedSubsException *) \
      vexGetExceptionOfClass(&_vloadableUnloadedSubsExceptionClass))

#define vloadableGetExceptionClass() \
  (&_vloadableExceptionClass)

#define vloadableGetNoResourceKindExceptionClass() \
  (&_vloadableNoResourceKindExceptionClass)

#define vloadableGetUnknownKindExceptionClass() \
  (&_vloadableUnknownKindExceptionClass)

#define vloadableGetWrongKindExceptionClass() \
  (&_vloadableWrongKindExceptionClass)

#define vloadableGetImproperSubLoadExceptionClass() \
  (&_vloadableImproperSubLoadExceptionClass)

#define vloadableGetUnloadedSubsExceptionClass() \
  (&_vloadableUnloadedSubsExceptionClass)

#define vloadableGetExceptionInstance(exception) \
  ((exception)->instance)

#define vloadableGetExceptionKindName(exception) \
  ((exception)->kindName)

#endif /* (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * loadable objects
 */

#define vloadableCopy(o, t) \
    vclassSend(vloadableGetClass(o), vloadableCOPY, (o, t))
#define vloadableDump(o, s) \
    vclassSend(vloadableGetClass(o), vloadableDUMP, (o, s))
#define vloadableSetTag(o, t) \
    vclassSend(vloadableGetClass(o), vloadableSET_TAG, (o, t))
#define vloadableSetAliasScribed(o, a) \
    vclassSend(vloadableGetClass(o), vloadableSET_ALIAS_SCRIBED, (o, a))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vloadableHEADER
#define vloadableHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vloadableINCLUDED */

