/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _COLL_PT_WK
#define _COLL_PT_WK
#include <ostore/hdrstart.hh>

/***
 ***	The following is a macro suitable for pre-declaring an ObjectStore
 ***	collection type to work around instantiation problems found in most
 ***	AT&T cfront 3.0.1 based compilers.
 ***
 ***	NOTE:  The forward declarations are repeated in all the macros in this
 ***	header file because you can not predict which will be used first in a
 ***	particular source file.
 ***/

/*  pzl 2-6-97 - I modified these for EPC so that the macros can be
    used to force instantiation for the entire family of os_Collection
    classes at the same time. */

#ifdef _OS_EPC

#define os_Collection_declare(x) class x; \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  template os_Collection< x * >; \
  template os_Set< x * > ; \
  template os_Bag< x * > ; \
  template os_List< x * > ; \
  template os_Array< x * > ; \
  template os_Cursor< x * > ; \
  template os_Collection< x const * > ; \
  template os_Set< x const * > ; \
  template os_Bag< x const * > ; \
  template os_List< x const * > ; \
  template os_Array< x const * > ; \
  template os_Cursor< x const * > ;

#else /* _OS_EPC */

#ifdef _OS_ANSI_TOKENS
#define os_Collection_declare(x) class x; \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x * > _os_coll_##x##_dummy1; \
  typedef os_Set< x * > _os_coll_##x##_dummy2; \
  typedef os_Bag< x * > _os_coll_##x##_dummy3; \
  typedef os_List< x * > _os_coll_##x##_dummy4; \
  typedef os_Array< x * > _os_coll_##x##_dummy5; \
  typedef os_Cursor< x * > _os_coll_##x##_dummy6; \
  typedef os_Collection< x const * > _os_coll_const_##x##_dummy1; \
  typedef os_Set< x const * > _os_coll_const_##x##_dummy2; \
  typedef os_Bag< x const * > _os_coll_const_##x##_dummy3; \
  typedef os_List< x const * > _os_coll_const_##x##_dummy4; \
  typedef os_Array< x const * > _os_coll_const_##x##_dummy5; \
  typedef os_Cursor< x const * > _os_coll_const_##x##_dummy6;
#else
#define os_Collection_declare(x) class x; \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x * > _os_coll_/**/x/**/_dummy1; \
  typedef os_Set< x * > _os_coll_/**/x/**/_dummy2; \
  typedef os_Bag< x * > _os_coll_/**/x/**/_dummy3; \
  typedef os_List< x * > _os_coll_/**/x/**/_dummy4; \
  typedef os_Array< x * > _os_coll_/**/x/**/_dummy5; \
  typedef os_Cursor< x * > _os_coll_/**/x/**/_dummy6; \
  typedef os_Collection< x const * > _os_coll_const_/**/x/**/_dummy1; \
  typedef os_Set< x const * > _os_coll_const_/**/x/**/_dummy2; \
  typedef os_Bag< x const * > _os_coll_const_/**/x/**/_dummy3; \
  typedef os_List< x const * > _os_coll_const_/**/x/**/_dummy4; \
  typedef os_Array< x const * > _os_coll_const_/**/x/**/_dummy5; \
  typedef os_Cursor< x const * > _os_coll_const_/**/x/**/_dummy6;
#endif
#endif /* _OS_EPC */

/***
 ***	The following is a version of the os_Collection_declare macro which
 ***	can be used for typedefs which are not themselves typedefs for pointer
 ***	types or fundamental types (char, int, ...).  There is no current need
 ***	for a const type parameter of the so the additional six typedefs are
 ***	omitted for the sake of brevity and saving of compilation cycles.
 ***/
#ifdef _OS_EPC

#define os_Collection_declare_no_class(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  template os_Collection< x * >; \
  template os_Set< x * > ; \
  template os_Bag< x * > ; \
  template os_List< x * > ; \
  template os_Array< x * > ; \
  template os_Cursor< x * > ;

#else /* _OS_EPC */
#ifdef _OS_ANSI_TOKENS
#define os_Collection_declare_no_class(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x * > _os_coll_noclass_##x##_dummy1; \
  typedef os_Set< x * > _os_coll_noclass_##x##_dummy2; \
  typedef os_Bag< x * > _os_coll_noclass_##x##_dummy3; \
  typedef os_List< x * > _os_coll_noclass_##x##_dummy4; \
  typedef os_Array< x * > _os_coll_noclass_##x##_dummy5; \
  typedef os_Cursor< x * > _os_coll_noclass_##x##_dummy6;
#else
#define os_Collection_declare_no_class(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x * > _os_coll_noclass_/**/x/**/_dummy1; \
  typedef os_Set< x * > _os_coll_noclass_/**/x/**/_dummy2; \
  typedef os_Bag< x * > _os_coll_noclass_/**/x/**/_dummy3; \
  typedef os_List< x * > _os_coll_noclass_/**/x/**/_dummy4; \
  typedef os_Array< x * > _os_coll_noclass_/**/x/**/_dummy5; \
  typedef os_Cursor< x * > _os_coll_noclass_/**/x/**/_dummy6;
#endif	/* _OS_ANSI_TOKENS */
#endif /* _OS_EPC */


/***
 ***	The following is a version of the os_Collection_declare macro which
 ***	can be used for typedefs which are themselves typedefs for pointer
 ***	types.  The const type parameter of this is problematic because it
 ***	will create a os_Set<foo * const> and not a os_Set<const foo *>.
 ***	The constness of the pointed to type should be preserved in the
 ***	typedef before it is used as an argument to this macro.
 ***/
#ifdef _OS_EPC
#define os_Collection_declare_ptr_tdef(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  template os_Collection< x > ; \
  template os_Set< x > ; \
  template os_Bag< x > ; \
  template os_List< x > ; \
  template os_Array< x > ; \
  template os_Cursor< x > ;
#else
#ifdef _OS_ANSI_TOKENS
#define os_Collection_declare_ptr_tdef(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x > _os_coll_noptr_##x##_dummy1; \
  typedef os_Set< x > _os_coll_noptr_##x##_dummy2; \
  typedef os_Bag< x > _os_coll_noptr_##x##_dummy3; \
  typedef os_List< x > _os_coll_noptr_##x##_dummy4; \
  typedef os_Array< x > _os_coll_noptr_##x##_dummy5; \
  typedef os_Cursor< x > _os_coll_noptr_##x##_dummy6;
#else
#define os_Collection_declare_ptr_tdef(x) \
  template <class E> class os_Collection; \
  template <class E> class os_Set; \
  template <class E> class os_Bag; \
  template <class E> class os_List; \
  template <class E> class os_Array; \
  template <class E> class os_Cursor; \
  typedef os_Collection< x > _os_coll_noptr_/**/x/**/_dummy1; \
  typedef os_Set< x > _os_coll_noptr_/**/x/**/_dummy2; \
  typedef os_Bag< x > _os_coll_noptr_/**/x/**/_dummy3; \
  typedef os_List< x > _os_coll_noptr_/**/x/**/_dummy4; \
  typedef os_Array< x > _os_coll_noptr_/**/x/**/_dummy5; \
  typedef os_Cursor< x > _os_coll_noptr_/**/x/**/_dummy6;
#endif
#endif /* _OS_EPC */

#include <ostore/hdrend.hh>
#endif	/* _COLL_PT_WK */
