/* $Id: vpq.h,v 1.19 1996/03/23 00:40:06 chad Exp $ */

#ifndef vpqINCLUDED
#define vpqINCLUDED 1


/*
 * Include any other headers this file depends upon.
 */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * * Types * * * * * * * * * * * * * * *
 */
 
typedef vbool (*vpqLessThanProc)( const void *first, const void *second );

typedef /*const*/ void *vpqElement;

typedef struct vpq {
    vpqElement		*array;
    vpqLessThanProc	 lessThan;
    int			 dynamic;
} vpq;

typedef struct vpqException {
    vexException	  parent;
    const vpq		 *pq;
} vpqException;

typedef vpqElement *vpqIterator;


/*
 * * * * * * * * * * * * * * Prototypes * * * * * * * * * * * * * * * *
 */
 
vpq		*vpqCreate           ( void );
void		 vpqInit             ( vpq *pq );
vpq		*vpqClone            ( const vpq *pq );
void		 vpqDestroy          ( vpq *pq );
void		 vpqEnqueue          ( vpq *pq, const void *newElement );
void		*vpqDequeue          ( vpq *pq );
void		*vpqPeek             ( const vpq *pq );
vbool            vpqRemoveElement    ( vpq *pq, const void *oldElem );
void             vpqSetLessThanProc  ( vpq *pq, vpqLessThanProc proc );
vpqLessThanProc  vpqGetLessThanProc  ( const vpq *pq );
void             vpqDump             ( const vpq *pq, FILE *fp );
void		 vpqAssert           ( const vpq *pq );

vpqException    *vpqGetException     ( void );
const vpq       *vpqGetExceptionPQ   ( const vpqException *exception );
const vexClass  *vpqGetExceptionClass( void );

void		 vpqInitIterator     ( vpqIterator *iterator, const vpq *pq );
int		 vpqNextIterator     ( vpqIterator *iterator );
void		 vpqDestroyIterator  ( vpqIterator *iterator );
void		*vpqGetIteratorObject( const vpqIterator *iterator );

/*
 * * * * * * * * * * * * Privately Exported Constants * * * * * * * * * * * * *
 */

extern vportLINK const vexClass	 _vpqExceptionClass;


/*
 * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * *
 */

void             vpqPQ               ( void *exception, va_list *ap );


/*
 * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * *
 */

#define vpqPeek( pq )			( *(((pq)->array)+1) )

#define vpqSetLessThanProc( pq, proc )	\
	(vpqAssert(pq), vdebugAssert((proc)!=NULL), (pq)->lessThan = (proc))

#define vpqGetLessThanProc( pq )	((pq)->lessThan)

#define vpqGetExceptionClass()		(&_vpqExceptionClass)

#define vpqGetException()	\
	((vpqException *) vexGetExceptionOfClass( vpqGetExceptionClass() ))

#define vpqGetExceptionPQ( exception )	(((vpqException *) exception)->pq)

#define vpqNextIterator(i)		(*(--*(i)) ? 1 : 0)
#define vpqDestroyIterator(i)
#define vpqGetIteratorObject(i)		(**(i))


vportEND_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * * * Miscellaneous * * * * * * * * * * * * * *
 */

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:2
 * c-brace-offset:-2
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-2
 * End:
 */


#endif /* vpqINCLUDED */








































