/* $Id: vmem.h,v 1.54 1996/08/30 15:31:02 eric Exp $ */
/************************************************************

    vmem.h

    C Interface file for the Memory Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmemINCLUDED		/*-------------  vmemINCLUDED  -------------*/
#define vmemINCLUDED		1


#ifndef  vportINCLUDED			/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED		/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdargINCLUDED		/* for va_list */
#include vstdargHEADER
#endif

#ifndef  vstringINCLUDED		/* for mem*() */
#include vstringHEADER
#endif

#ifndef  vstdioINCLUDED			/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED			/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*===========================================================================*\
				C O N S T A N T S
\*===========================================================================*/


/**  vmemDEBUG
 ** 
 **	Defined if vmem calls are to be checked for using valid memory blocks
 **	in correct ways and not overwriting allocated area boundaries.  Also
 **	used for finding memory leaks.
 **
 **	Debugging memory can be done on a per-file basis.
 **/
#ifndef  vmemDEBUG			/*----------  vmemDEBUG  ----------*/
#define  vmemDEBUG	vdebugDEBUG
#endif					/*----------  vmemDEBUG  ----------*/


/**  vmemTAG
 **
 **	This is a string naming the tag of the client module for purposes of
 **	memory tracking.
 **/
#ifndef  vmemTAG			/*------------  vmemTAG  ------------*/
#define  vmemTAG	vdebugTAG
#endif					/*------------  vmemTAG  ------------*/


/**  vmemBALANCE
 **
 **	A compile-time flag to indicate whether client code is
 **	required to balance all allocations with appropriate frees
 **	This is used to detect memory leaks, and verifies the integrity
 **	of allocated memory as a side effect.
 **/
#ifndef vmemBALANCE
#define vmemBALANCE	(vmemDEBUG || vportCPLUSPLUS_BALANCE)
#endif


/**  vmemALL_TAG
 ** 
 **	Tag that summarizes total usage of all the different name spaces
 **	it begins with a space so it will sort to the top
 **/
#define vmemALL_TAG	"ALL"


/**  vmemDEFAULT_DEBUGGING_FLAGS_ENVIRONMENT_VARIABLE
 **
 **	Environment variable used to store default flag value
 **	(equivalent to calling vmemSetDefaultDebuggingFlags() on startup)
 **/
#define  vmemDEFAULT_DEBUGGING_FLAGS_ENVIRONMENT_VARIABLE	"vmemFLAGS"



/**  Notification Types
 **/
enum {
   vmemMONITOR_EVENT_ALLOC,
   vmemMONITOR_EVENT_FREE,
   vmemMONITOR_EVENT_NEW_GROUP,
   vmemMONITOR_EVENT_REALLOC,
   vmemMONITOR_EVENT_START,
   vmemMONITOR_EVENT_STOP
};


/**  Debugging flags
 **/
enum {
   vmemFLAG_RANDOMIZE_ALLOC	= 0x1,
   vmemFLAG_RANDOMIZE_FREE	= 0x2,
   vmemFLAG_MOVE_REALLOC	= 0x4,
   vmemFLAG_USE_OVERWRITE	= 0x8,
   vmemFLAG_MONITOR_LEAKS	= 0x10,
   vmemFLAG_USE_HEADER		= 0x80
};


/**  These are private
 **/
enum {
    vmemHeaderMASK_SIZE		= 0x3fffffff,
    vmemHeaderFLAG_POOL		= 0x40000000
};



/**  leave low bits unset for priority modifier  (low, normal, high)
 **/
enum
{
    vmemPRIORITY_GARBAGE		=  (1 << 2),
    vmemPRIORITY_PERFORMANCE		=  (4 << 2),
    vmemPRIORITY_MINOR_USER_VISIBLE	=  (7 << 2),
    vmemPRIORITY_MAJOR_USER_VISIBLE	= (10 << 2),
    vmemPRIORITY_EMERGENCY		= (13 << 2),

    vmemPRIORITY_MODIFIER_LOW		= 0x1,
    vmemPRIORITY_MODIFIER_HIGH		= 0x2
};


/*===========================================================================*\
	    			T Y P E S
\*===========================================================================*/

/**  Free Function
 **
 **	Called when memory is no longer available
 **/
typedef vbool (*vmemFreeFunction)(void);


/**  Pre-declare some structs to a global scope for picky compilers
 **/
typedef struct vmemGroup	vmemGroup;
typedef struct vmemHeader	vmemHeader;	/**  PRIVATE dispite name  **/



/**  Overwrite Buffer
 **
 **	Each memory block has on overwrite buffer prepended to the front and
 **	another one appended to the rear.  These buffers are initialized to a
 **	unique value and checked periodically to see if they have been mangled.
 **/
typedef vbyte _vmemOverwriteBuffer[8];



/**  Monitor Event
 **/
typedef struct vmemMonitorEvent
{
    vmemGroup		*group;
    int			 code;
    const char 		*file;
    int			 line;
    size_t		 size;
    size_t		 sizeOld;
    void		*block;
    void		*blockOld;
}  vmemMonitorEvent;



/**  Memory Block Header
 **
 **	A block header is prepended to each memory block allocated from the
 **	system.
 **/
struct vmemHeader
{
    unsigned int	 flags;
    vmemGroup		*groupCreated;
    
    const char		*sFileCreated;
    int			 nLineCreated;
    
    vmemHeader		*headerPrev;	/* in linked list of blocks */
    vmemHeader		*headerNext;	/* in linked list of blocks */

    _vmemOverwriteBuffer bufferOverwrite;
};



/**  Tagged Group
 **
 **	Each named memory space grouping being tracked has a vmemGroup
 **	block allocated for its use.  The vmemGroup block is used to
 **	track usage of all memory blocks in the named grouping.
 **/
struct vmemGroup
{
    vmemHeader		*headerHead;
    
    const char		*sTag;			/* label of memory 	     */
    int			 nTag;
    unsigned int	 flags;

    unsigned long	 nTotalBytesAllocated;	/* cumulative bytes malloced */
    unsigned long	 nTotalBytesReallocated;/* cumulative bytes realloced*/
    unsigned long	 nTotalBytesFreed;	/* cumulative bytes freed    */
    unsigned long	 nMaxBytesUsed;		/* alloced+realloced - freed */

    int			 nAllocs;		/* calls to malloc	     */
    int			 nReallocs;		/* calls to realloc	     */
    int			 nFrees;		/* calls to free	     */
    
    vmemGroup		*groupNext;
    vmemGroup		*groupPrev;	  
};



/**  Monitor Proc
 **
 **	This prototypes all callback functions used by the Memory Manager.
 **	Callbacks are used to inform interested clients of calls to the Memory
 **	Manager that modify global state.
 **/
typedef void (*vmemMonitorProc)(
	vmemMonitorEvent	*event			
	);



/*===========================================================================*\
		E X C E P T I O N      H A N D L I N G
\*===========================================================================*/
/*********************
 **  Exception Types
 *********************/
typedef vexException vmemException;


typedef struct vmemAllocException {
    vmemException		 parent;
    size_t			 size;
} vmemAllocException;


typedef struct vmemMoveException {
    vmemException		 parent; /* ancestor: /Memory */
    void			*from;
    void			*to;
    size_t			 size;
} vmemMoveException;


typedef struct vmemReallocException {
    vmemException		 parent; /* ancestor: /Memory */
    void			*block;
    size_t			 size;
} vmemReallocException;


typedef struct vmemInvalidException {
    vmemException		 parent; /* ancestor: /Memory */
    void			*block;
} vmemInvalidException;

typedef struct vmemBoundsException {
    vmemException		 parent;
    void			*block;
    int				 bounds;
} vmemBoundsException;

typedef vmemInvalidException vmemInvalidAlreadyFreedException;

typedef struct vmemValueException {
    vmemException		 parent;
    void			*address;
    size_t                       size;
} vmemValueException;






/*******************
 **  Get Exceptions
 *******************/
vmemException		*vmemGetException(void);
vmemAllocException	*vmemGetAllocException(void);
vmemMoveException	*vmemGetMoveException(void);
vmemReallocException	*vmemGetReallocException(void);
vmemBoundsException	*vmemGetBoundsException( void );
vmemInvalidException	*vmemGetInvalidException( void );
vmemInvalidAlreadyFreedException *vmemGetInvalidAlreadyFreedException( void );
vmemValueException	*vmemGetValueException( void );



/**************************
 **  Get Exception Classes
 **************************/
const vexClass	*vmemGetExceptionClass(void);
const vexClass	*vmemGetAllocExceptionClass(void);
const vexClass	*vmemGetMoveExceptionClass(void);
const vexClass	*vmemGetReallocExceptionClass(void);
const vexClass  *vmemGetBoundsExceptionClass( void );
const vexClass  *vmemGetInvalidExceptionClass( void );
const vexClass  *vmemGetInvalidAlreadyFreedExceptionClass( void );
const vexClass  *vmemGetValueExceptionClass( void );



/**********************
 **  Exception Values
 **********************/
size_t  vmemGetAllocSize(
	const vmemAllocException	*exception
	);

void  *vmemGetMoveFrom(
	const vmemMoveException		*exception
	);

void  *vmemGetMoveTo(
	const vmemMoveException		*exception
	);

size_t  vmemGetMoveSize(
	const vmemMoveException		*exception
	);

size_t	 vmemGetReallocSize(
	const vmemReallocException 	*exception
	);

void	*vmemGetReallocBlock(
	const vmemReallocException 	*exception
	);

void  *vmemGetBoundsBlock(
	const vmemBoundsException	*exception
	);

int  vmemGetBoundsBounds(
	const vmemBoundsException	*exception
	);

void  *vmemGetInvalidBlock(
	const vmemInvalidException	*exception
	);

void  *vmemGetValueAddress(
	const vmemValueException	*exception
	);

size_t vmemGetValueSize(
	const vmemValueException	*exception
	);


/****************************************
 **  Exception Argument Eaters
 **  (these are documented as constants)
 ****************************************/
void  vmemAllocSIZE(
	void	*exception,
	va_list *ap
	);

void  vmemMoveFROM(
	void	*exception,
	va_list *ap
	);

void  vmemMoveTO(
	void	*exception,
	va_list *ap
	);

void  vmemMoveSIZE(
	void	*exception,
	va_list *ap
	);

void  vmemReallocBLOCK(
	void	*exception,
	va_list *ap
	);

void  vmemReallocSIZE(
	void	*exception,
	va_list *ap
	);

void  vmemBoundsBLOCK(
	void	*exception,
	va_list *ap
	);

void  vmemBoundsBOUNDS(
	void	*exception,
	va_list *ap
	);

void  vmemInvalidBLOCK(
	void	*exception,
	va_list *ap
	);

void  vmemValueADDRESS(
	void	*exception,
	va_list *ap
	);

void  vmemValueSIZE(
	void	*exception,
	va_list *ap
	);


/************************
 **  Exception  Classes
 ************************/
extern vportLINK const vexClass		_vmemExceptionClass;
extern vportLINK const vexClass		_vmemAllocExceptionClass;
extern vportLINK const vexClass		_vmemMoveExceptionClass;
extern vportLINK const vexClass		_vmemReallocExceptionClass;
extern vportLINK const vexClass		_vmemBoundsExceptionClass;
extern vportLINK const vexClass		_vmemInvalidExceptionClass;
extern vportLINK const vexClass		_vmemInvalidAlreadyFreedExceptionClass;
extern vportLINK const vexClass		_vmemValueExceptionClass;



/*===========================================================================*\
		  F U N C T I O N       P R O T O T Y P E S
\*===========================================================================*/

/********************
 **  create/destroy
 *******************/
void  *vmemAlloc(
	size_t	 nBytes
	);

void  *vmemAllocAndClear(
	size_t	 nBytes
	);

void  vmemFree(
	void	*address
	);

void  *vmemRealloc(
	void	*address,
	size_t	 nBytes
	);

void  vmemReallocPtr(
	void	**paddress,
	size_t	 nBytes
	);

void  *vmemAllocDebug(
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);

void  *vmemAllocAndClearDebug(
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);

void  vmemFreeDebug(
	void		*address,
	const char	*tag,
	const char	*file,
	int		 line
	);

void  *vmemReallocDebug(
	void		*address,
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);

void  vmemReallocPtrDebug(
	void		**address,
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);


void  *vmemTryAlloc(
	size_t	 nBytes
	);

void  *vmemTryAllocDebug(
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);

void  *vmemTryRealloc(
	void	*address,
	size_t	 nBytes
	);

void  *vmemTryReallocDebug(
	void		*address,
	size_t		 nBytes,
	const char	*tag,
	const char	*file,
	int		 line
	);


/*********************
 **  access / modify
 *********************/
int  vmemCompare(
	const void	*address1,
	const void	*address2,
	size_t		 nBytes
	);

void  *vmemCopy(
	const void	*addressSource,
	void		*addressTarget,
	size_t		 nBytes
	);

void  *vmemMove(
	const void	*addressSource,
	void		*addressTarget,
	size_t		 nBytes
	);

void  *vmemSet(
	void		*address,
	int		 value,	/*vbyte*/
	size_t		 nBytes
	);

/****************
 **  low memory
 ****************/
void  vmemRegisterFreeFunction(
	vmemFreeFunction	fn,
	int			priority
	);

void  vmemUnregisterFreeFunction(
	vmemFreeFunction	fn,
	int			priority
	);
			 

/****************
 **  validation
 ****************/
void  vmemValidateBlock(
	const void	*address
	);

void  vmemValidateBlockDebug(
	const void	*address,
	const char	*tag,
	const char	*file,
	int		 line
	);

int  vmemIsValidBlock(
	const void	*address
	);


/*===========================================================================*\
    		D E B U G G I N G     P R O T O T Y P E  S
\*===========================================================================*/
/******************************
 **  routines on tagged memory
 ******************************/
unsigned int  vmemGetDefaultDebuggingFlags(void);

void  vmemSetDefaultDebuggingFlags(
	unsigned int	flags
	);


/************
 **  Groups
 ************/
vmemGroup  *vmemGetGroupWithTag(
	const char	*tag
	);

const char *vmemGetGroupTag(
	vmemGroup	*group
	);




/************
 **  Dumping
 ************/
void  vmemDumpStatisticsWithTag(
	const char	*tag,
	FILE		*fp
	);

void  vmemDumpBlocksWithTag(
	const char	*tag,
	FILE		*fp
	);

int  vmemDumpInvalidBlocksWithTag(
	const char	*tag,
	FILE		*fp
	);

int  vmemDumpInvalidBlocks(
	FILE		*fp
	);



/*******************
 **  Event Monitors
 *******************/
void  vmemRegisterMonitorProc(
	vmemMonitorProc	 monitorProc
	);

void  vmemUnregisterMonitorProc(
	vmemMonitorProc	 monitorProc
	);

void  vmemDefaultMonitorProc(
	vmemMonitorEvent	*event		 
	);

int  vmemGetMonitorEventCode(
	vmemMonitorEvent	*event
	);

void  *vmemGetMonitorEventBlock(
	vmemMonitorEvent	*event
	);

const char  *vmemGetMonitorEventFile(
	vmemMonitorEvent	*event
	);

vmemGroup *vmemGetMonitorEventGroup(
	vmemMonitorEvent	*event
	);

int  vmemGetMonitorEventLine(
	vmemMonitorEvent	*event
	);

void *vmemGetMonitorEventOldBlock(
	vmemMonitorEvent	*event
	);

size_t  vmemGetMonitorEventOldSize(
	vmemMonitorEvent	*event
	);

size_t  vmemGetMonitorEventSize(
	vmemMonitorEvent	*event
	);



#if (vportCPLUSPLUS_SOURCE)

#define vmemNEW_DECLARATION(type)					\
    void *operator new(size_t size);					\
    void  operator delete(void *dead)

#define vmemNEW_DEFINITION(type)					\
  void *type::operator new(size_t size)					\
  {									\
    _vclientSetInNew(TRUE);						\
    return vmemAlloc(size);						\
  }									\
  void  type::operator delete(void *dead)				\
  {									\
    if (dead != NULL)							\
        vmemFree(dead);							\
  }

#endif /* (vportCPLUSPLUS_SOURCE) */


/*===========================================================================*\
		P R I V A T E     E X P O R T E D     P R O T O T Y P E S
\*===========================================================================*/
void  *_vmemAlloc(
	size_t		nBytes
	);

void  *_vmemAllocAndClear(
	size_t		nBytes
	);

void  *_vmemRealloc(
	void		*address,
	size_t		 nBytes
	);

void  _vmemFree(
	void		*address
	);

void  *_vmemTryAlloc(
	size_t		nBytes
	);

void  *_vmemTryRealloc(
	void		*address,
	size_t		 nBytes
	);

void *_vmem_malloc(
        size_t           size
        );

void *_vmem_calloc(
        size_t           count,
        size_t           size
        );

void *_vmem_realloc(
        void            *p,
        size_t           size
        );

void _vmem_free(
        void            *p
        );

#if (vdebugDEBUG)		/*--------------  vdebugDEBUG  --------------*/
void  *_vmemSet(
	void		*mem,
	int		 value,
	size_t		 size
	);

void  *_vmemCopy(
	const void	*src,
	void		*dest,
	size_t		 size
	);

void  *_vmemMove(
	const void	*src,
	void		*dest,
	size_t		 size
	);

int   _vmemCompare(
	const void	*mem,
	const void	*mem2,
	size_t		 length
	);

#endif				/*--------------  vdebugDEBUG  --------------*/

#if (vmemDEBUG)			/*--------------  vmemDEBUG  --------------*/

int  _vmemDumpInvalidBlocksWithTagDebug(
	const char	*tag,
	FILE		*fp,
	const char	*file,
	int		 line
	);

int  _vmemDumpInvalidBlocksDebug(
	FILE		*fp,
	const char	*file,
	int		 line
	);


#endif				/*--------------  vmemDEBUG  --------------*/


/*===========================================================================*\
	F U N C T I O N S     D E F I N E D     A S     M A C R O S
\*===========================================================================*/

/***************
 **  debugging
 ***************/
#if (vmemDEBUG)			/*---------------  vmemDEBUG  ---------------*/
#define  vmemSetBlockFlag(_block, _flag)				\
    {if (vmemGetGroupWithTag(vmemTAG)->flags & vmemFLAG_USE_HEADER)	\
    	((vmemHeader *)(_block))[-1].flags |= (_flag);}

#define  vmemGetGroupTag(_group)		(_group)->sTag

#define  vmemValidateBlock(_p)						\
  vmemValidateBlockDebug(_p, vmemTAG, __FILE__, __LINE__)

#define  vmemDumpInvalidBlocks(_fp)					\
    _vmemDumpInvalidBlocksDebug(_fp, __FILE__, __LINE__)
#define  vmemDumpInvalidBlocksWithTag(_tag, _fp)			\
    _vmemDumpInvalidBlocksWithTagDebug(_tag, _fp, __FILE__, __LINE__)
#else				/*---------------  vmemDEBUG  ---------------*/
#define  vmemRegisterMonitorProc(_fn)		/* EMPTY */
#define  vmemUnregisterMonitorProc(_fn)		/* EMPTY */
#define  vmemGetGroupTag(_group)		vmemALL_TAG
#define  vmemSetBlockFlag(_block, _flag)	/* EMPTY */
#define  vmemGetDefaultDebuggingFlags()		0
#define  vmemSetDefaultDebuggingFlags(_n)	/* EMPTY */
#define  vmemValidateBlock(_p)			/* EMPTY */
#define  vmemValidateBlockDebug(_p, _t, _f, _l)	/* EMPTY */
#define  vmemDumpInvalidBlocks(_fp)		0
#define  vmemDumpInvalidBlocksWithTag(_tag, _fp) 0

#define  vmemAllocDebug(_n, _t, _f, _l)		_vmemAlloc(_n)
#define  vmemAllocAndClearDebug(_n, _t, _f, _l)	_vmemAllocAndClear(_n)
#define  vmemFreeDebug(_p, _t, _f, _l)		_vmemFree(_p)
#define  vmemReallocDebug(_p, _n, _t, _f, _l)	_vmemRealloc((_p), (_n))
#define  vmemTryAllocDebug(_n, _t, _f, _l)	_vmemTryAlloc(_n)
#define  vmemTryReallocDebug(_p, _n, _t, _f, _l) _vmemTryRealloc((_p), (_n))
#endif				/*---------------  vmemDEBUG  ---------------*/


/********************
 **  create/destroy
 ********************/
#define  vmemAlloc(_n)							\
   vmemAllocDebug(_n, vmemTAG, __FILE__, __LINE__)

#define  vmemAllocAndClear(_n)						\
   vmemAllocAndClearDebug(_n, vmemTAG, __FILE__, __LINE__)

#define  vmemFree(_p)							\
   vmemFreeDebug(_p, vmemTAG, __FILE__, __LINE__)

#define  vmemRealloc(_p, _n)						\
   vmemReallocDebug(_p, _n, vmemTAG, __FILE__, __LINE__)

#define  vmemReallocPtrDebug(_pp, _n, _tag, _file, _line)		\
   (*(_pp) = vmemReallocDebug(*(_pp), _n, _tag, _file, _line))

#define  vmemReallocPtr(_pp, _n)					\
   vmemReallocPtrDebug(_pp, _n, vmemTAG, __FILE__, __LINE__)

#define  vmemTryAlloc(_n)						\
   vmemTryAllocDebug(_n, vmemTAG, __FILE__, __LINE__)

#define  vmemTryRealloc(_p, _n)						\
   vmemTryReallocDebug(_p, _n, vmemTAG, __FILE__, __LINE__)


/*******************************************
 **  Convenience macros to ease C++ work
 *******************************************/
#define _vmemAllocType(t)						\
   ((t *)vmemAlloc(sizeof(t)))

#define _vmemAllocAndClearType(t)					\
   ((t *)vmemAllocAndClear(sizeof(t)))

#define _vmemAllocArrayOfType(t, s)					\
   ((t *)vmemAlloc((s) * sizeof(t)))

#define _vmemAllocAndClearArrayOfType(t, s)				\
   ((t *)vmemAllocAndClear((s) * sizeof(t)))

#define _vmemReallocArrayOfType(m, t, s)				\
   ((t *)vmemRealloc((m), (s) * sizeof(t)))

/* for completeness */
#define _vmemFreeType(t, m)						\
   vmemFree(m)

#define _vmemFreeArrayOfType(t, m)					\
   vmemFree(m)

/*******************************
 **  access / modify
 **  (defined by  vdebugDEBUG,
 **   not by vmemDEBUG
 *******************************/
#if (vdebugDEBUG)		/*--------------  vdebugDEBUG  --------------*/
#define vmemCompare(_p1, _p2, _n)	_vmemCompare(_p1, _p2, _n)
#define vmemCopy(_src, _dst, _n)	_vmemCopy(_src, _dst, _n)
#define vmemMove(_src, _dst, _n)	_vmemMove(_src, _dst, _n)
#define vmemSet(_p, _val, _n)		_vmemSet(_p, _val, _n)
#else				/*--------------  vdebugDEBUG  --------------*/
#define vmemCompare(_p1, _p2, _n)	memcmp((void *)(_p1),		\
					       (void *)(_p2), (_n))
#define vmemCopy(_src, _dst, _n)	((void *)memcpy((void *)(_dst),	\
							(void *)(_src), (_n)))
#define vmemMove(_src, _dst, _n)	((void *)memmove((void *)(_dst),\
							 (void *)(_src), (_n)))
#define vmemSet(_p, _val, _n)		((void *)memset((void *)(_p),	\
							(_val), (_n)))
#endif				/*--------------  vdebugDEBUG  --------------*/


/*******************
 **  Event Monitors
 *******************/
#define  vmemGetMonitorEventCode(_event)	(_event)->code
#define  vmemGetMonitorEventBlock(_event)	(_event)->block
#define  vmemGetMonitorEventFile(_event)	(_event)->file
#define  vmemGetMonitorEventGroup(_event)	(_event)->group
#define  vmemGetMonitorEventLine(_event)	(_event)->line
#define  vmemGetMonitorEventOldBlock(_event)	(_event)->blockOld
#define  vmemGetMonitorEventOldSize(_event)	(_event)->sizeOld
#define  vmemGetMonitorEventSize(_event)	(_event)->size



/*********************************
 **  Get Exception Class Macros
 *********************************/
#define vmemGetAllocExceptionClass()			\
   (&_vmemAllocExceptionClass)

#define vmemGetExceptionClass()				\
   (&_vmemExceptionClass)

#define vmemGetMoveExceptionClass()			\
   (&_vmemMoveExceptionClass)

#define vmemGetReallocExceptionClass()			\
   (&_vmemReallocExceptionClass)

#define vmemGetBoundsExceptionClass()			\
   (&_vmemBoundsExceptionClass)

#define vmemGetInvalidAlreadyFreedExceptionClass()	\
  (&_vmemInvalidAlreadyFreedExceptionClass)

#define vmemGetInvalidExceptionClass()			\
   (&_vmemInvalidExceptionClass)

#define vmemGetValueExceptionClass()		        \
   (&_vmemValueExceptionClass)



/*********************************
 **  Get Exception Macros
 *********************************/
#define vmemGetAllocException()				\
   ((vmemAllocException *)vexGetExceptionOfClass(&_vmemAllocExceptionClass))

#define vmemGetException()				\
  ((vmemException *) vexGetExceptionOfClass(&_vmemExceptionClass))

#define vmemGetMoveException()				\
  ((vmemMoveException *) vexGetExceptionOfClass(&_vmemMoveExceptionClass))

#define vmemGetReallocException()			\
  ((vmemReallocException *)vexGetExceptionOfClass(&_vmemReallocExceptionClass))

#define vmemGetBoundsException()			\
 ((vmemBoundsException *)vexGetExceptionOfClass(&_vmemBoundsExceptionClass))

#define vmemGetInvalidAlreadyFreedException()		\
  ((vmemInvalidAlreadyFreedException *)			\
   vexGetExceptionOfClass(&_vmemInvalidAlreadyFreedExceptionClass))

#define vmemGetInvalidException()			\
  ((vmemInvalidException *)vexGetExceptionOfClass(&_vmemInvalidExceptionClass))

#define vmemGetValueException()				\
 ((vmemValueException *)vexGetExceptionOfClass(&_vmemValueExceptionClass))



/****************************
 **  Other Exception Macros
 ****************************/
#define vmemGetAllocSize( _pMAEx )			\
  (((vmemAllocException *) (_pMAEx))->size)

#define vmemGetMoveFrom( exception )			\
  (((vmemMoveException *)(exception))->from)

#define vmemGetMoveTo( _pMREx )				\
  (((vmemMoveException *)(_pMREx))->to)

#define vmemGetMoveSize( _pMREx )			\
  (((vmemMoveException *)(_pMREx))->size)

#define vmemGetReallocBlock( _pMREx )			\
  (((vmemReallocException *)(_pMREx))->block)

#define vmemGetReallocSize( _pMREx )			\
  (((vmemReallocException *)(_pMREx))->size)

#define vmemGetBoundsBlock( _pMBEx )			\
   (((vmemBoundsException *) (_pMBEx))->block)

#define vmemGetBoundsBounds( _pMBEx )			\
   (((vmemBoundsException *) (_pMBEx))->bounds)

#define vmemGetInvalidBlock( _pMIEx )			\
   (((vmemInvalidException *)(_pMIEx))->block)

#define vmemGetValueAddress( _pMCEx )		\
   (((vmemValueException *) (_pMCEx))->address)

#define vmemGetValueSize( _pMCEx )		        \
   (((vmemValueException *) (_pMCEx))->size)


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vmemHEADER
#define vmemHEADER vportNULL_HEADER
#endif


#endif				/*-------------  vmemINCLUDED  -------------*/
