/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _PATH_TEMPLATES
#define _PATH_TEMPLATES
#include <ostore/hdrstart.hh>

/* Templates for Index Paths. */

#ifdef __os_cplusplus
static const char __path_template_version[] = "$Revision: 10.7.1.1 $";
#endif

/* result of this is a path step */

template <> __expression path_star :
 new _Path_step(new _Deref())
;

/* result of this is a path */

template <> __expression path_noop :
 os_index_path(new _Path_step(new _Noop()))
;

/* result of this is a path */

template <
  __expression OFFSET,
  __expression MEMBER_NAME,
  __expression BACKPTR_OFFSET
>
__expression path_dot :
concatenate(new _Path_step(new _Offset($OFFSET, $BACKPTR_OFFSET),
		       $MEMBER_NAME, _Path_step::use_name ),
	    new _Path_step(new _Deref(), _Path_step::use_name) )
;

/* result of this is a path */

template <
  __expression LEFT,
  __expression OFFSET,
  __expression MEMBER_NAME,
  __expression BACKPTR_OFFSET
>
__expression path_dot_1 :
concatenate(
concatenate($LEFT,
	    new _Path_step(new _Offset($OFFSET, $BACKPTR_OFFSET),
		       $MEMBER_NAME, _Path_step::use_name ) ),
	    new _Path_step(new _Deref(), _Path_step::use_name) )
;

/* result of this is a path */

template <
  __expression OFFSET,
  __expression MEMBER_NAME,
  __expression BACKPTR_OFFSET
>
__expression path_arrow :
  concatenate(new _Path_step(new _Deref()),
	      new _Path_step(new _Offset($OFFSET, $BACKPTR_OFFSET), 
			 $MEMBER_NAME, _Path_step::use_name ) )
  .concatenate(new _Path_step(new _Deref(), _Path_step::use_name))
;

template <
  __expression LEFT,
  __expression OFFSET,
  __expression MEMBER_NAME,
  __expression BACKPTR_OFFSET
>
__expression path_arrow_1 :
  concatenate($LEFT, new _Path_step(new _Deref())).
  concatenate(new _Path_step(new _Offset($OFFSET, $BACKPTR_OFFSET),
			 $MEMBER_NAME, _Path_step::use_name ))
  .concatenate(new _Path_step(new _Deref(), _Path_step::use_name))
;


/* result of this is a path step */

template <__expression LEFT>
 __expression path_element :
concatenate(concatenate($LEFT, new _Path_step(new _Deset(), _Path_step::use_name)),
	    new _Path_step(new _Noop(), _Path_step::use_name))
;

/* result of this is a path step */

template < >
 __expression path_id :
new _Path_step(new _Id_value(), _Path_step::use_name)
;

/* result of this is a path step */

template < __expression TYPE_NAME, __expression ARRAY_SIZE, __expression ELEMENT_SIZE >
__expression path_ob :
new _Path_step(new _Ob_value((const char*)$TYPE_NAME, (os_int32)$ARRAY_SIZE,
	                 (os_int32)$ELEMENT_SIZE), _Path_step::use_name)
;

/* add a path step to a path step */
/* value is a path */

template <
 __expression STEP1,
 __expression STEP2
>
__expression path_concat :
concatenate ($STEP1, $STEP2)
;

template <
  __expression PATH,
  __expression ELEMENT_TYPE_NAME
>
__expression finish_path :
$PATH._set_element_type_name($ELEMENT_TYPE_NAME)
;

#include <ostore/hdrend.hh>
#endif
