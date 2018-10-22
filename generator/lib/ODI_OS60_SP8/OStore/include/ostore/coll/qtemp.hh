/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _QUERY_TEMPLATES
#define _QUERY_TEMPLATES
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* Template Functions for the Query Facility */
/* names here must neither bump into compiler temporaries
   nor names defined by eXcelon Corp. personel. */

#define FUNCTION_NAME (__current_function_name_demangled)

/* -- it would be handy to be able to dump this, but
   it would require the introduction of a temp to capture the scan. */

template <
class ELEMENT_TYPE,
__expression ID,
__expression RES,
__expression VAL
>
__expression
compute_query_compute_inline_result :
  (
#ifdef DEBUGGING_QUERIES
   ( _Query_runtime::trace_level == _Query_runtime::os_qrtl_detail ?
    (
     _Query_runtime::trace (_Query_runtime::os_qrtl_detail, 
			    "%s: coll %p node %d index %s\n",
			    __current_template_name,
			    (void *)&__coll,
			    $ID,
			    __query_node[$ID]._index),
     0 ) : 0), 
#endif
   _Scan_K<ELEMENT_TYPE>(__coll, __query_node[$ID]._index, $RES, $VAL));


template <
__expression COMPUTE,
__expression ID   /* ID is that of the query. */
>
__statement
compute_query_materialize_inline_result :
{
  __result = $COMPUTE.breakpoint(__query_node[$ID]._index, _Scan::SCAN).materialize();
}

template <
__expression CALL_COMPUTE,
__expression ID /* ID is that of the query. */
>
__statement
compute_query_materialize_outline_result :
{
    _Scan * __temp_scan = $CALL_COMPUTE;
    __result = __temp_scan->breakpoint(__query_node[$ID]._index,
				       _Scan::SCAN).materialize ();
    delete __temp_scan;
}

template <
__expression COMPUTE,
__expression ID   /* ID is that of the query. */
>
__statement
compute_pick_query_materialize_inline_result :
{
  __result = $COMPUTE.breakpoint(__query_node[$ID]._index,
				 _Scan::PICK).materialize_pick();
}
	
	
template <
__expression CALL_COMPUTE,
__expression ID /* ID is that of the query. */
>
__statement
compute_pick_query_materialize_outline_result :
{
    _Scan * __temp_scan = $CALL_COMPUTE;
    __result = __temp_scan->breakpoint(__query_node[$ID]._index,
				       _Scan::PICK).materialize_pick();
    delete __temp_scan;
}


template <
class ELEMENT_TYPE,
class AGG_TYPE,
__expression N_NODES,
__statement STRATEGIZE,
__statement COMPUTE_RESULT,
__expression CHECK_ELEMENT,
__expression ID
>
__statement
compute_query :
{
  _Query_node_info __query_node($N_NODES);
  os_int32 __pick_or_existential_query = 0;
  
#ifdef DEBUGGING_QUERIES
  _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			"%s: coll %p\n", 
			FUNCTION_NAME,
			(void *)&__coll);
#endif
  
  __query_node[$ID]._index = 0;
  
  $STRATEGIZE;
  
#ifdef DEBUGGING_QUERIES
  _Query_runtime::check_strategy(__coll, $ID, 
				 __query_node[$ID]._index,
				 0
				 );
#endif
  
  if(__query_node[$ID]._index) {
#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			  "%s: coll %p compute_result\n",
			  FUNCTION_NAME,
			  (void *)&__coll);
#endif
    
    
    _Pset* __result;
    
    $COMPUTE_RESULT;
    
    os_collection& __cresult = __result->turn_into_collection(__coll, 1);
    /* __query_node.clear_strategy(); */
    return (AGG_TYPE) __cresult;
    
  } else {
#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			  "%s: coll %p scan\n",
			  FUNCTION_NAME,
			  (void *)&__coll);
#endif
    os_collection& __result = os_collection::create(os_collection::TEMPORARY,
						    __coll.get_behavior());
    void* __elem;
    os_cursor __curs(__coll, __coll._presort_if_appropriate());
    while (__curs.more()) {
      __elem = __curs.retrieve();
      __curs.next();
      ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __elem;
      /* to make things simpler, don't obviate the
	 local variable in favor of this asignment here,
	 which makes aliases work */
      __query_node[$ID].query_this = (void *)&__query_this;
      if($CHECK_ELEMENT)
	__result.insert(__query_this);
    }
    /* __query_node.clear_strategy(); */
    return (AGG_TYPE)__result;
  }
}



template <
__expression ID,
__expression PATH_STRING,
__expression RES,
__statement INHIBIT,
__expression ZVEC_FUNC_NAME
>
__statement
compute_query_strategize_1 :
{
  if (!__query_node[$ID].inhibited &&
      (__pick_or_existential_query || __coll._fast_count()) &&
      (__query_node[$ID]._index =
	 __coll._index($PATH_STRING, $RES, $ZVEC_FUNC_NAME) ) != 0 )
  /* os_collection::EQ for now, until compiler passes restriction */
    $INHIBIT;
}

template <
__expression NULLCHECK_ID
>
__statement
compute_query_strategize_inhibit :
{
  __query_node[$NULLCHECK_ID].inhibited = 1;
}


template <
__expression THIS_ID,
__expression RIGHT_ID,
__expression NESTING
>
__statement 
compute_query_strategize_query :
{
    if (__query_node[$RIGHT_ID]._index)
    {
      char* __name = __query_node.strip_suffix(__query_node[$RIGHT_ID]._index->LI_name,
					     $NESTING);
      __query_node[$THIS_ID]._index =
	__coll._index(__name, os_collection::EQ, 0 /* zvec_func_name */);
#ifdef DEBUGGING_QUERIES
      _Query_runtime::trace(_Query_runtime::os_qrtl_detail, 
		            "%s: [%d] -- index %d\n",
			    __current_template_name,
			    $RIGHT_ID,
			    __query_node[$THIS_ID]._index);
#endif
    }
    else
    {
      __query_node[$THIS_ID]._index = 0;
#ifdef DEBUGGING_QUERIES
        _Query_runtime::trace (_Query_runtime::os_qrtl_detail, "no index\n");
#endif
    }
}

template <
__expression THIS_ID,
__expression L_ID,
__expression R_ID,
__expression NESTING
>
__statement 
compute_query_strategize_andand :
{
#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace
	(_Query_runtime::os_qrtl_detail, 
	 "%s: L[%d] index %d, R[%d] index %d",
	 __current_template_name,
	 $L_ID, 
	 __query_node[$L_ID]._index,
	 $R_ID,
	 __query_node[$R_ID]._index);
#endif

    __query_node[$THIS_ID]._index = 0;
    char* __name = 0;
    if(__query_node[$L_ID]._index)
      {
	__name = __query_node.strip_suffix(__query_node[$L_ID]._index->LI_name, $NESTING);
	__query_node[$THIS_ID]._index =
	  __coll._index(__name, os_collection::EQ, 0 /* zvec_func_name */);
      }
    else if(__query_node[$R_ID]._index && !__name)
      {
	__name = __query_node.strip_suffix(__query_node[$R_ID]._index->LI_name, $NESTING);
	__query_node[$THIS_ID]._index =
	  __coll._index(__name, os_collection::EQ, 0 /* zvec_func_name */);
      }

    if(__query_node[$THIS_ID]._index)
      {
#ifdef DEBUGGING_QUERIES
	_Query_runtime::trace(
			      _Query_runtime::os_qrtl_detail, 
			      "index %s\n",
			      __query_node[$THIS_ID]._index);
#endif
      }
#ifdef DEBUGGING_QUERIES
    else _Query_runtime::trace (_Query_runtime::os_qrtl_detail, "no index\n");
#endif
}

template <
__expression THIS_ID,
__expression L_ID,
__expression R_ID,
__expression NESTING
>
__statement 
compute_query_strategize_oror :
{
#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace
	(_Query_runtime::os_qrtl_detail, 
	 "%s: L[%d] index %d, R[%d] index %d",
	 __current_template_name,
	 $L_ID, 
	 __query_node[$L_ID]._index,
	 $R_ID,
	 __query_node[$R_ID]._index);
#endif

    if(__query_node[$L_ID]._index &&
       __query_node[$R_ID]._index)
      {
	char* __name = __query_node.strip_suffix(__query_node[$R_ID]._index->LI_name, $NESTING);
	__query_node[$THIS_ID]._index =
	  __coll._index(__name, os_collection::EQ, 0 /* zvec_func_name */);
#ifdef DEBUGGING_QUERIES
	   _Query_runtime::trace
	       (_Query_runtime::os_qrtl_detail, 
		"index %s\n",
		__query_node[$THIS_ID]._index);
#endif
       }
#ifdef DEBUGGING_QUERIES
    else _Query_runtime::trace (_Query_runtime::os_qrtl_detail, "no index\n");
#endif
}

template <
__expression L,
__expression R
>
__statement
check_and :
{ 
#ifdef DEBUGGING_QUERIES
    if(_Query_runtime::do_trace(_Query_runtime::os_qrtl_function)) {
	os_int32 __trace_L, __trace_LR;
	__trace_L = (os_int32)$L;
	__trace_LR = __trace_L && (os_int32)$R;
	_Query_runtime::trace (_Query_runtime::os_qrtl_function,
			       "%s: left %d result %d\n", 
			       FUNCTION_NAME,
			       __trace_L, __trace_LR);
	return __trace_LR;
	
    } else
#endif
	return ($L) && ($R);
}


template <
  class ELEMENT_TYPE,
  __expression THIS_ID,
  __expression L_ID,
  __expression R_ID,
  __statement L_SCAN_INIT,
  __statement R_SCAN_INIT,
  __expression L_CHECK,
  __expression R_CHECK,
  __expression QUERY_ID
>
__statement
compute_and :
{
  _Scan * __left;
  _Scan * __right;

  os_unsigned_int32 __L_lookup = (os_unsigned_int32) __query_node[$L_ID]._index;
  os_unsigned_int32 __R_lookup = (os_unsigned_int32) __query_node[$R_ID]._index;

  _Index_name* __i = __query_node[$THIS_ID]._index;

  if (__L_lookup && __R_lookup)
  {
    $L_SCAN_INIT;
    $R_SCAN_INIT;
    if (__left->convert_to_range_query(__right))
	__left->breakpoint(__i, _Scan::SCAN);
    else
      {
	__left->breakpoint(__i, _Scan::SCAN);
	__right->breakpoint(__i, _Scan::SCAN);
	*__left &= *__right;
      }
    delete __right;
    return __left;
  }

  else if (__L_lookup)
  {
    $L_SCAN_INIT;
    __left->breakpoint(__i, _Scan::SCAN);
    _Pset* __result = new _Pset;
    for (__left->iteration_start(); 
	 __left->more(); __left->next())
    {
      ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __left->retrieve();
      __query_node[$QUERY_ID].query_this = (void *)&__query_this;
      if ($R_CHECK)
	{
	  void* __p = (void*) &__query_this;
	    __p = *(void**)__p;
	  __result->insert(__p);
	}
    }
    *__left = __result;
    return __left;
  }
	
  else if (__R_lookup)
  {
    $R_SCAN_INIT;
    __right->breakpoint(__i, _Scan::SCAN);
    _Pset* __result = new _Pset;
    for (__right->iteration_start();
	 __right->more(); __right->next())
    {
      ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __right->retrieve();
      __query_node[$THIS_ID].query_this = (void *)&__query_this;
      if ($L_CHECK)
	{
	  void* __p = (void*) &__query_this;
	    __p = *(void**)__p;
	  __result->insert(__p);
	}
    }
    *__right = __result;
    return __right;
  }

  else _Query_runtime::error("at least one index should be available");
}



template <
  class ELEMENT_TYPE,
  __expression THIS_ID,
  __expression L_ID,
  __expression R_ID,
  __statement L_SCAN_INIT,
  __statement R_SCAN_INIT,
  __expression R_CHECK,
  __expression QUERY_ID
>
__statement
compute_pick_and :
{
  _Scan * __left;
  _Scan * __right;

  os_unsigned_int32 __L_lookup = (os_unsigned_int32) __query_node[$L_ID]._index;
  os_unsigned_int32 __R_lookup = (os_unsigned_int32) __query_node[$R_ID]._index;

  _Index_name* __i = __query_node[$THIS_ID]._index;

  if (__R_lookup && !__L_lookup)
  {
    $R_SCAN_INIT;
    __right->breakpoint(__i, _Scan::PICK);
    return __right;
  }

  else if (__L_lookup)
  {
    $L_SCAN_INIT;
    __left->breakpoint(__i, _Scan::SCAN);
    _Pset* __result = new _Pset;
    for (__left->iteration_start(); 
	 __left->more(); __left->next())
    {
      ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __left->retrieve();
      __query_node[$QUERY_ID].query_this = (void *)&__query_this;
      if ($R_CHECK)
	{
	  void* __p = (void*) &__query_this;
	    __p = *(void**)__p;
	  __result->insert(__p);
	}
    }
    *__left = __result;
    return __left;
  }
	
  else _Query_runtime::error("at least one index should be available");
}




template <
__expression ELEMENT,
__expression FCN_NAME
>
__expression call_lex_qt_qn :
$FCN_NAME (__lex, $ELEMENT, __query_node);

template <
__expression CALL_COMPUTE,
__expression ID, /* query ID */
__expression NOT_FLAG
>
__statement check_query_compute_outline :
{
  _Scan * __temp_scan = $CALL_COMPUTE;
  __found = !__temp_scan->breakpoint(__query_node[$ID]._index,
				     _Scan::PICK).empty();
  if ($NOT_FLAG) __found = !__found;
  delete __temp_scan;
}

template <
__expression CALL_COMPUTE,
__expression ID,
__expression NOT_FLAG
>
__statement check_query_compute_inline :
{
    __found = !$CALL_COMPUTE.breakpoint(__query_node[$ID]._index,
					_Scan::PICK).empty();
    if ($NOT_FLAG) __found = !__found;
}

template <
class KEY_TYPE,
__expression KEY_NAME,
__expression KEY_INIT,
__expression SCAN_AGG,
__expression LR,
__expression ID,
__expression RES
>
__statement
dcl_scan :
{
/* The cast here is to remove const if it is present in key_init
   but absent in key_type. It might be safer to keep the const,
   but the query code generator is not in an easy position to
   detect the const on the type of KEY_INIT and then add it to
   KEY_TYPE. */

    KEY_TYPE $KEY_NAME = (KEY_TYPE) $KEY_INIT;
#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace (_Query_runtime::os_qrtl_detail, 
			   "%s: node %d\n",
			   __current_template_name,
			   $ID);
#endif
    $LR = new _Scan_K<KEY_TYPE>($SCAN_AGG, __query_node[$ID]._index, 
			      $RES,
			      $KEY_NAME);
#ifdef DEBUGGING_QUERIES
    if(_Query_runtime::do_trace(_Query_runtime::os_qrtl_dump)) {
	_Query_runtime::trace(_Query_runtime::os_qrtl_dump,
			      "%s: scanner follows:\n",
			      __current_template_name);

#if 0
	$LR->aggregate->dump();
#endif
    }
#endif
}

template <
__expression SCAN_AGG,
__expression LR,
__expression COMPUTE_OUTER_NAME
>
__statement
dcl_outer_scan :
{
    $LR = $COMPUTE_OUTER_NAME (__lex, $SCAN_AGG, __query_node);
}

template <
__expression L,
__expression R
>
__statement
check_or :
{ 
#ifdef DEBUGGING_QUERIES
    if(_Query_runtime::do_trace(_Query_runtime::os_qrtl_function)) {
	os_int32 __trace_L, __trace_LR;
	__trace_L = (os_int32)$L;
	__trace_LR = __trace_L || (os_int32)$R;
	_Query_runtime::trace (_Query_runtime::os_qrtl_function,
			       "%s: left %d result %d\n", 
			       FUNCTION_NAME,
			       __trace_L, __trace_LR);
	return __trace_LR;
	
    } else 
#endif
	return ($L) || ($R);
}


	
template <
  __expression QUERY_ID,
  __expression L_ID,
  __expression R_ID,
  __statement L_SCAN_INIT,
  __statement R_SCAN_INIT
>
__statement
compute_or :
{
  _Scan * __left;
  _Scan * __right;

  os_unsigned_int32 __L_lookup = (os_unsigned_int32) __query_node[$L_ID]._index;
  os_unsigned_int32 __R_lookup = (os_unsigned_int32) __query_node[$R_ID]._index;

  _Index_name* __i = __query_node[$QUERY_ID]._index;

  if (__L_lookup && __R_lookup)
  {
    $L_SCAN_INIT;
    __left->breakpoint(__i, _Scan::SCAN);

    $R_SCAN_INIT;
    __right->breakpoint(__i, _Scan::SCAN);

    *__left |= *__right;
    delete __right;
    return __left;
  }

  else _Query_runtime::error("both indices should be available");
}



	
template <
  __expression QUERY_ID,
  __expression L_ID,
  __expression R_ID,
  __statement L_SCAN_INIT,
  __statement R_SCAN_INIT
>
__statement
compute_pick_or :
{
  _Scan * __left;
  _Scan * __right;

  os_unsigned_int32 __L_lookup = (os_unsigned_int32) __query_node[$L_ID]._index;
  os_unsigned_int32 __R_lookup = (os_unsigned_int32) __query_node[$R_ID]._index;


  _Index_name* __i = __query_node[$QUERY_ID]._index;

  if (__L_lookup && __R_lookup)
    {
      $L_SCAN_INIT;
      __left->breakpoint(__i, _Scan::PICK);
      if (!__left->empty())
	return __left;

      delete __left;
      $R_SCAN_INIT;
      __right->breakpoint(__i, _Scan::PICK);
      return __right;
    }
  else _Query_runtime::error("both indices should be available");
}



template <
  class AGG_ELEMENT_TYPE,
  class ELEMENT_TYPE,
  __statement STRATEGIZE,
  __expression AGGREGATE,
  __expression ID,
  __statement COMPUTE_RESULT,	
  __expression CHECK_ELEMENT,
  __expression NOT_FLAG /* 1 for not case */
>
__statement
check_query_existential :
{
  _Scan * __right;
  os_int32 __pick_or_existential_query = 1;

  AGG_ELEMENT_TYPE& __coll = $AGGREGATE;

#ifdef DEBUGGING_QUERIES
  _Query_runtime::trace(_Query_runtime::os_qrtl_function, 
			"%s: coll %p\n",
			FUNCTION_NAME,
			(void *)&__coll);
#endif

  __query_node[$ID]._index = 0;

  $STRATEGIZE;

  os_unsigned_int32 __found = 0;
  if (__query_node[$ID]._index) {

/* COMPUTE_RESULT is always an assignment to __found of empty() applied
   to a scanner. In the inline case, the scanner is a temp object.
   In the non-inline case, it is a pointer to a scanner, and COMPUTE_RESULT
   declares a temp to hold it and then deletes it. */

    $COMPUTE_RESULT;

#ifdef DEBUGGING_QUERIES
  _Query_runtime::trace(_Query_runtime::os_qrtl_function, 
			FUNCTION_NAME,
			"%s: compute_result returned %d\n",
			__found);
#endif
  } else {
    void* __elem;
    os_cursor __curs(__coll, __coll._presort_if_appropriate());

#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace(_Query_runtime::os_qrtl_function, 
			  "%s: scanning\n",
			  FUNCTION_NAME
			  );
#if 0
    if(_Query_runtime::do_trace(_Query_runtime::os_qrtl_dump)) 
	__s.aggregate->dump();
#endif 
#endif
    while (!__found && __curs.more())
    {
      __elem = __curs.retrieve();
      __curs.next();
      ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __elem;
      __query_node[$ID].query_this = (void *)&__query_this;
      __found = (os_unsigned_int32) $CHECK_ELEMENT;
    }
  }

#ifdef DEBUGGING_QUERIES
  _Query_runtime::trace(_Query_runtime::os_qrtl_function, 
			"%s: exit %d\n",
			FUNCTION_NAME,
			__found);
#endif
  
  /* __query_node.clear_strategy(); */
  if ($NOT_FLAG) __found = !__found;
  return __found;
}

template <
 class KEY_TYPE,
 __expression KEY_VALUE,
 __expression ID,
 __expression RESTRICTION
>
__statement
compute_outer_query :
{
    _Scan_K<KEY_TYPE> * __s;
    __s = new _Scan_K<KEY_TYPE>(__coll,
			    __query_node[$ID]._index,
			    $RESTRICTION,  /* as in dcl_scan, this cast */
			                   /* removes a const marking that */
			                   /* may be missing from key_type */
			    $KEY_VALUE);

#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			  "%s: scanner %p\n",
			  FUNCTION_NAME,
			  (void *)&__s);
#if 0
    if(_Query_runtime::do_trace (_Query_runtime::os_qrtl_dump))
	__s->aggregate->dump();
#endif
    _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			  "%s: exit\n",
			  FUNCTION_NAME);
#endif
    return __s;
}

/* This template is used when the RHS of an existential query 
   itself generates a compute_outer function. We really
   could obviate this function, or at least inline it,
   but that would require some new virtual functions
   in labeling to allow the child compute_outer to stand
   in for the query. --benson */

template <
    __expression FUNCTION
>
__statement
compute_outer_query_outline :
{
    _Scan * __result;

#ifdef DEBUGGING_QUERIES
    _Query_runtime::trace(_Query_runtime::os_qrtl_function, "%s: enter\n",
			  FUNCTION_NAME);
#endif

    __result = $FUNCTION (__lex, __coll, __query_node);

#ifdef DEBUGGING_QUERIES
#if 0
    if(_Query_runtime::do_trace (_Query_runtime::os_qrtl_dump))
	__result->aggregate->dump();
#endif
    _Query_runtime::trace(_Query_runtime::os_qrtl_function,
			  "%s: scanner %s %p exit\n",
			  FUNCTION_NAME,
			  __result->type_name(), __result);
#endif
    return __result;
}



template <
  class ELEMENT_TYPE,
  __statement STRATEGIZE,
  __expression ID,
  __statement COMPUTE_RESULT,	
  __expression CHECK_ELEMENT,
  __expression N_NODES,
  __expression NOT_FLAG
>
__statement
check_query_top_existential :
{
    _Query_node_info __query_node($N_NODES);
    os_int32 __pick_or_existential_query = 1;

  $STRATEGIZE;
	
  os_unsigned_int32 __found = 0;
	
  TIX_HANDLE (err_coll_empty)
  {
    if (__query_node[$ID]._index)
    {
        $COMPUTE_RESULT;
    }
    else
    {
      void* __elem;
      os_cursor __curs(__coll, __coll._presort_if_appropriate());
      while (!__found && __curs.more())
      {
	__elem = (ELEMENT_TYPE*) __curs.retrieve();
	__curs.next();	
        ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __elem;
        __query_node[$ID].query_this = (void *)&__query_this;
        __found = (os_unsigned_int32) $CHECK_ELEMENT;
      }
    }
  }
  TIX_EXCEPTION
    __found = 0;
  TIX_END_HANDLE

  /* __query_node.clear_strategy(); */
	
  if ($NOT_FLAG)
    __found = !__found;

  return __found;
}


template <
class ELEMENT_TYPE,
__expression N_NODES,
__statement STRATEGIZE,
__statement COMPUTE_RESULT,
__expression CHECK_ELEMENT,
__expression ID,
__expression NOT_FLAG
>
__statement
compute_pick_query :
{
    _Query_node_info __query_node($N_NODES);
    os_int32 __pick_or_existential_query = 1;
    void* __result = 0;
	
    __query_node[$ID]._index = 0;

    $STRATEGIZE;

    if (__query_node[$ID]._index)
    {
        $COMPUTE_RESULT;
    }
    else
    {
      void* __elem;
      os_cursor __curs(__coll, __coll._presort_if_appropriate());
      while (!__result && __curs.more())
	{
	  __elem = __curs.retrieve();
	  __curs.next();
	  ELEMENT_TYPE& __query_this = (ELEMENT_TYPE) __elem;

	  /* to make things simpler, don't obviate the
	     local variable in favor of this assignment here,
	     which makes aliases work */
	  __query_node[$ID].query_this = (void *)&__query_this;

	  if ($CHECK_ELEMENT)
	    __result = __query_this;
	}
    }

    /* __query_node.clear_strategy(); */

    if (!$NOT_FLAG)
      {
	return (ELEMENT_TYPE) __result;
      }
    else
      {
	if (__result)
	  return (ELEMENT_TYPE) 0;
	return 1;
      }
}



template <
__expression ID,
class CET
>
__expression query_alias_reference :
*(CET *)__query_node[$ID].query_this
;

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
