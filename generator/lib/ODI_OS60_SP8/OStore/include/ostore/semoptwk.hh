/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _OS_SCHMEVOL_MOP_PT_WK_HDR_
#define _OS_SCHMEVOL_MOP_PT_WK_HDR_
#include <ostore/hdrstart.hh>

#include <ostore/collptwk.hh>

/***
 ***	The following are the workaround declarations for schema evolution.
 ***/

template <class Ptype> class os_prim_typed_pointer;
template <class Ftype> class os_func_ass;

typedef os_prim_typed_pointer<void> os_typed_pointer_void;
typedef os_typed_pointer_void const& os_typed_pointer_void_const_r;
typedef os_char_p (*os_evolve_subtype_fun)(os_typed_pointer_void_const_r);
typedef os_func_ass<os_evolve_subtype_fun> os_evolve_subtype_fun_binding;
os_Collection_declare_no_class(os_evolve_subtype_fun_binding)

typedef const char _os_semoptwk_cchar;
os_Collection_declare_no_class(char)
os_Collection_declare_no_class(_os_semoptwk_cchar)

typedef void (*os_transformer)(os_void_p p);
typedef os_func_ass<os_transformer> os_transformer_binding;
os_Collection_declare_no_class(os_transformer_binding)

typedef void (*os_se_hook_function_void)(void) ;
os_Collection_declare_ptr_tdef(os_se_hook_function_void)

class os_se_version_group_version_entry;
typedef os_se_version_group_version_entry  os_vgroup_version_entry;

class os_se_version_vgroup;
typedef os_se_version_vgroup               os_version_vgroup;

class os_se_nonversion_vgroup;
typedef os_se_nonversion_vgroup            os_nonversion_vgroup;

os_Collection_declare_no_class(os_vgroup_version_entry)
os_Collection_declare_no_class(os_version_vgroup)
os_Collection_declare_no_class(os_nonversion_vgroup)

/***
 ***	The following are the workaround declarations for the meta object
 ***	protocol.
 ***/

os_Collection_declare(os_class_type)
os_Collection_declare(os_type)
os_Collection_declare(os_base_class)
os_Collection_declare(os_member)
os_Collection_declare(os_pragma)
os_Collection_declare(os_template_actual_arg)
os_Collection_declare(os_template_formal_arg)
os_Collection_declare(os_enumerator_literal)

#include <ostore/hdrend.hh>
#endif	/* _OS_SCHMEVOL_MOP_PT_WK_HDR_ */
