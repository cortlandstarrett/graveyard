/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _INDEXABLE_TEMPLATE
#define _INDEXABLE_TEMPLATE
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

template <
  __expression FIELD,
  __expression BACKPTR_OFFSET,
  __expression ASSIGNMENT,
  __expression F_TEMP
>
__expression index_update :
(   $F_TEMP = &$FIELD,
   ((os_backptr *)(((char *)((void *)$F_TEMP)) + $BACKPTR_OFFSET))->
      break_link((void *)$F_TEMP,
		 (void *)$F_TEMP,
		 (os_int32)$BACKPTR_OFFSET),
   $ASSIGNMENT, /* modified *F_TEMP */
   ((os_backptr *)(((char *)((void *)$F_TEMP)) + $BACKPTR_OFFSET))->
      make_link((void *)$F_TEMP,
		(void *)$F_TEMP,
		(os_int32)$BACKPTR_OFFSET),
   *$F_TEMP  
)
;

template <
  __expression FIELD,
  __expression BACKPTR_OFFSET,
  __expression F_TEMP
> 
__expression index_update_call_pre :
(   $F_TEMP = &$FIELD,
   ((os_backptr *)(((char *)((void *)$F_TEMP)) + $BACKPTR_OFFSET))->
      break_link((void *)$F_TEMP,
		 (void *)$F_TEMP,
		 (os_int32)$BACKPTR_OFFSET),
   0
)
;

template <
  __expression BACKPTR_OFFSET,
  __expression F_TEMP
> 
__expression index_update_call_post :
   ((os_backptr *)(((char *)((void *)$F_TEMP)) + $BACKPTR_OFFSET))->
      make_link((void *)$F_TEMP,
		(void *)$F_TEMP,
		(os_int32)$BACKPTR_OFFSET)
;

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
