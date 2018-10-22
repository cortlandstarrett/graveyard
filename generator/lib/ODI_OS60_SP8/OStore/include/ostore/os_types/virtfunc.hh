/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef __OS_VIRTUAL_BEHAVIOR__
#define __OS_VIRTUAL_BEHAVIOR__ 1
#include <ostore/hdrstart.hh>

#include <ostore/os_types/paddef.hh>

/* what's this all about, you may ask?
   if os_virtual_behavior or the 64 bit version is the first
   base class of a marked type, the virtual function table for
   that class may mangle the same way as that for the base class.  
   if we declare it in the generated schema source file, we'll
   end up with duplicate symbols or redefined symbols.  so
   if we're in the schema source file, we specifically don't
   include these definitions. */
#if defined(__os_linux) && defined(__os_linux_in_schema_file)
#define __include_virtual_behavior_defs 0
#else
#define __include_virtual_behavior_defs 1
#endif

#if __include_virtual_behavior_defs
class _OS_DLLIMPORT(_OS_LOW) os_virtual_behavior {
public:
  os_virtual_behavior () {}
  virtual void dummy_virtual_function() const;
};

class _OS_DLLIMPORT(_OS_LOW) os_virtual_behavior64 {
public:
  os_virtual_behavior64() {}
  virtual void dummy_virtual_function() const;

  /* needs to be 8 bytes to potentially allow for 64 bit vtbls */
  os_pad_vftbl_only8
};
#endif

template <class T>
class os_virtual_behavior_t {
public:
  os_virtual_behavior_t () {}
#ifdef __os_xlc
  virtual void dummy_virtual_function() const;
#else
  virtual void dummy_virtual_function() const {}
#endif
};

#ifdef __os_xlc
template <class T>
void os_virtual_behavior_t <T> :: dummy_virtual_function() const {}
#endif
template <class T> class _os_pad_cons_disp {
#ifndef _OS_MicrosoftCC
  os_int32 ival;
#endif
};

template <class T> class _os_pad_cons_disp_filler {
  os_int32 ival;
};

/*
  Note: compilers with cfront heritage may be unable to deal with
  template classes where a template class formal is used as a base
  class.  We will only support the ObjectStore version of cfront.
  As a result, the __os_cplusplus macro is used to conditionalize
  the cfront templates instead of _OS_cfrontC.
  */
  


/*
  os_vb_fbsc

  - introduces vftbl, virtual base simultaneously, allowing for cset
    self pointers and construction displacement members
  - this is the most general form for virtual base introduction.
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.  This number includes
    construction displacement compensating virtual base classes.
  - non-virtual class layout is:
    vftbl
    vbtbl
    [ inherited vbptrs ]
    vbptr(cons_disp(T))
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

/* Note: cfront loses here because we need 2 virtual base classes */

template <int C, class T> class os_vb_fbsc_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  /* Account for vbtbl + C inherited vbptrs */
  void* _os_pad_vbtbl_and_vbptrs[C+1];
};

template <int C, class T> class os_vb_fbsc :
			  public os_vb_fbsc_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_fbsc_1 : 
			  public os_virtual_behavior_t<T>
{
  /* inherits vbptrs automatically */
  void* _os_pad_vbtbl;
};

template <int C, class T> class os_vb_fbsc :
			  public os_vb_fbsc_1<C,T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_fbsc :
	public os_virtual_behavior_t<T>,
	public virtual _os_pad_cons_disp<T>,
	public virtual T
{
  virtual void dummy_function() {}
  /* account for C inherited vbptrs + 2 new vbptrs */
  void* _os_pad_vbptr[C+2];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_cafe)

#if defined(__os_sol2c5)
/* cafe 6.1 */
template<int C, class T>
class os_vb_fbsc : public os_virtual_behavior_t<T>,
		   public virtual _os_pad_cons_disp<T>,
		   public virtual T
{
  /* pad: vbtbl (1), vbptrs(C), cons_disp(1), vbptr(T)(1), selfptr(1) */
  void* _os_pad_vbtbl_vbptrs_cons_disp_vbptr_selfptr[1 + C + 1 + 1 + 1];
};

#else
/* cafe 4.2 */

template <int C, class T> class os_vb_fbsc_1 : 
			  public os_virtual_behavior_t<T>
{
  /* account for C inherited vbptrs + vbtbl */
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_fbsc :
			  public os_vb_fbsc_1 <C,T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_fbsc_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  /* account for C inherited vbptrs + vbtbl */
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_fbsc :
			  public os_vb_fbsc_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_fbsc_1 :
	public virtual _os_pad_cons_disp<T>,
	public virtual T
{
  /* this gets vftbl + vbtbl */
  virtual void dummy_function() {}
};

template <int C, class T> class os_vb_fbsc :
	public os_vb_fbsc_1<C,T>
{
  void* _os_pad_vbptr[C+2];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_fbsc :
	public virtual _os_pad_cons_disp<T>,
	public virtual T
{
  /* this gets vftbl */
  virtual void dummy_function() {}
  void* _os_pad_vtbl;
  void* _os_pad_vbptr[C+2];
  void* _os_pad_selfptr;
};

#endif


#if defined(__os_linux)

template<int C, class T>
class os_vb_fbsc_1 
{
  void* _os_pad_vbptrs[C+1];
};

template<int C, class T>
class os_vb_fbsc_2 : public virtual _os_pad_cons_disp<T> { };

template<int C, class T>
class os_vb_fbsc_3 : public virtual T { };

template<int C, class T>
class os_vb_fbsc :
  /* vftbl */
  public os_virtual_behavior_t<T>,
  /* vbtbl, inherited vbptrs */
  public os_vb_fbsc_1<C, T>,
  /* vbptr(cons_disp(T)) */
  public os_vb_fbsc_2<C, T>,
  /* vb ptr(T) */
  public os_vb_fbsc_3<C, T>
{
  /* selfptr */
  void* _os_pad_selfptr;
};

#endif


/*
  os_vb_fbs

  - introduces vtbl, virtual base simultaneously, allowing for cset
    self pointers but not construction displacement members
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.
  - non-virtual class layout is:
    vftbl
    vbtbl
    [ inherited vbptrs ]
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_fbs_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
  void* _os_pad_vbtbl_vbpts[C+1];
};

template <int C, class T> class os_vb_fbs :
			  public os_vb_fbs_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_fbs_1 : 
			  public os_virtual_behavior_t<T>
{
  void* _os_pad_vbtbl;
};

template <int C, class T> class os_vb_fbs :
			  public os_vb_fbs_1<C,T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_fbs :
	public os_virtual_behavior_t<T>,
	public virtual T
{
  virtual void dummy_function() {}
  void* _os_pad_vbptr [C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_cafe)

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_fbs : public os_virtual_behavior_t<T>,
		  public virtual T
{
  /* vbtbl(1), vbptrs(C), vbptr(T)(1), selfptr(1) */
  void* _os_pad_vbtbl_vbptrs_vbptr_selfptr[1 + C + 1 + 1];
};

#else
template <int C, class T> class os_vb_fbs_1 : 
			  public os_virtual_behavior_t<T>
{
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_fbs :
			  public os_vb_fbs_1 <C,T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_fbs_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_fbs :
			  public os_vb_fbs_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_fbs_1 :
	public virtual T
{
  // introduce a vtbl, make it external so we can see it.
  virtual void dummy_function();
};

template <int C, class T> class os_vb_fbs :
	public os_vb_fbs_1<C,T>
{
  // really make sure the compiler makes the vtbl external.
  virtual void dummy_function();
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(_OS_DECCXX)
#define define_os_vb_fbs_vf(C,T) \
void os_vb_fbs_1< C , T >::dummy_function() {} \
void os_vb_fbs< C , T >::dummy_function() {}
#else
#define define_os_vb_fbs_vf(C,T)
#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_fbs :
	public virtual T
{
  virtual void dummy_function() {}
  void* _os_pad_vbtbl;
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_linux)

template<int C, class T>
class os_vb_fbs_1 
{
  /* vbtbl, inherited vbptrs */
  void* _os_pad_vbptrs[C+1];
};

template<int C, class T>
class os_vb_fbs :
  /* vftbl */
  public os_virtual_behavior_t<T>,
  /* vbtbl, inherited vbptrs */
  public os_vb_fbs_1<C, T>,
  /* vb ptr(T) */
  public virtual T
{
  /* selfptr */
  void* _os_pad_selfptr;
};

#endif


/*
  os_vb_fs

  - introduces vtbl, virtual base simultaneously, allowing for cset
    self pointers but ignoring construction displacement members
    and vbtbl
  - this is suitable when neither Dec C++ or Visual C++ are in use.
  - non-virtual class layout is:
    vftbl
    [ inherited vbptrs ]
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_fs_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
  /* don't bother with promoted vbptr pads because it won't work anyway */
};

template <int C, class T> class os_vb_fs :
			  public os_vb_fs_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_fs :
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

/* This template doesn't apply to Visual C++, but provide a dummy */
/* definition just so that the neutralizer can be applied */

template <os_int32 C, class T> class os_vb_fs :
	public virtual T
{
  virtual void dummy_function() {}
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_fs : public os_virtual_behavior_t<T>,
		 public virtual T
{
  /* vbptrs(C), vbptr(T)(1), selfptr(1) */
  void* _os_pad_vbptrs_vbptr_selfptr[C + 1 + 1];
};

#else
template <int C> class os_vb_fs_1 : 
			  public os_virtual_behavior
{
  void* _os_pad_vbptr[C];
};

class os_vb_fs_1<0> : 
			  public os_virtual_behavior
{
};

template <int C, class T> class os_vb_fs : 
			  public os_vb_fs_1<C> ,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C> class os_vb_fs_1 : 
			  public os_virtual_behavior
{
  void* _os_pad_vbptr[C];
};

class os_vb_fs_1<0> : 
			  public os_virtual_behavior
{
};

template <int C, class T> class os_vb_fs_2 : 
			  public os_vb_fs_1<C>,
			  public virtual T
{
};

template <int C, class T> class os_vb_fs : 
			  public os_vb_fs_2<C>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

/* This template doesn't apply to DEC C++, but provide a dummy */
/* definition just so that the neutralizer can be applied */

template <os_int32 C, class T> class os_vb_fs :
	public virtual T
{
  virtual void dummy_function() {}
};

#endif

#if defined(__os_hpansi)

template <os_int32 C, class T> class os_vb_fs :
	public virtual T
{
  virtual void dummy_function() {}
  void* _os_pad_vbptrs[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_linux)

template<int C, class T>
class os_vb_fs_1 
{
  /* inherited vbptrs */
  void* _os_pad_vbptrs[C];
};

template<int C, class T>
class os_vb_fs :
  /* vftbl */
  public os_virtual_behavior_t<T>,
  /* inherited vbptrs */
  public os_vb_fs_1<C, T>,
  /* vb ptr(T) */
  public virtual T
{
  /* selfptr */
  void* _os_pad_selfptr;
};

#endif

/*
  os_vb_f

  - introduces vtbl, virtual base simultaneously, allowing only for 
    virtual base pointers.  
  - this is suitable when none of Dec C++, Visual C++, or Xlc are in use.
  - non-virtual class layout is:
    vftbl
    vbptr(T)
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_f :
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
};

#endif


#ifdef __os_xlc

/* This template doesn't apply to CSet++, but provide a dummy */
/* definition just so that the neutralizer can be applied */

template <int C, class T> class os_vb_f :
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

/* This template doesn't apply to Visual C++, but provide a dummy */
/* definition just so that the neutralizer can be applied */

template <int C, class T> class os_vb_f :
	public virtual T
{
  virtual void dummy_function() {}
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_f : public os_virtual_behavior_t<T>,
		public virtual T
{
  void* _os_pad_vbptr;
};

#else

template <int C> class os_vb_f_1 : public os_virtual_behavior
{
  void* _os_pad_vbptr[C];
};

/* specialization for 0 promoted bases */
class os_vb_f_1<0> :  public os_virtual_behavior
{
};

template <int C, class T> class os_vb_f : 
			  public os_vb_f_1<C>,
			  public virtual T
{
};
#endif

#endif

#ifdef _OS_EPC

template <int C> class os_vb_f_1 : public os_virtual_behavior
{
  void* _os_pad_vbptr[C];
};

/* specialization for 0 promoted bases */
class os_vb_f_1<0> :  public os_virtual_behavior
{
};

template <int C, class T> class os_vb_f : 
			  public os_vb_f_1<C>,
			  public virtual T
{
};

#endif

#if defined(_OS_DECCXX) || defined(__os_hpansi)

/* This template doesn't apply to DEC C++, but provide a dummy */
/* definition just so that the neutralizer can be applied */

template <int C, class T> class os_vb_f :
	public virtual T
{
  virtual void dummy_function() {}
};

#endif

#if defined(__os_linux)

template<int C, class T> 
class os_vb_f :
  public os_virtual_behavior_t<T>,
  public virtual T
{
};

#endif

/*
  os_vb_fbscd

  - introduces vftbl, virtual base simultaneously, allowing for cset
    self pointers and construction displacement members
  - this differs from os_vb_fbsc in that it anticipatest that the virtual
    base class may require 8 byte alignment.
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.  This number includes
    construction displacement compensating virtual base classes.
  - non-virtual class layout is:
    vftbl
    vbtbl
    [ 4 byte pad for odd numbers of inherited vbptrs ]
    [ inherited vbptrs ]
    vbptr(cons_disp_filler(T))
    vbptr(cons_disp(T))
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

/* cfront can't be done right because it requires 3 virtual bases */

template <int C, class T> class os_vb_fbscd_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual _os_pad_cons_disp_filler<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  void* _os_pad_vbtbl_and_vbptrs[1+C+C%2];
};

template <int C, class T> class os_vb_fbscd :
			  public os_vb_fbscd_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_fbscd_1 : 
			  public os_virtual_behavior_t<T>
{
  /* inherits vbptrs automatically */
  void* _os_pad_vbtbl_and_pad[1+C%2];
};

template <int C, class T> class os_vb_fbscd :
			  public os_vb_fbscd_1<C,T>,
			  public virtual _os_pad_cons_disp_filler<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_fbscd :
	public os_virtual_behavior_t<T>,
	public virtual _os_pad_cons_disp_filler<T>,
	public virtual T
{
  virtual void dummy_function() {}
  /* account for C inherited vbptrs + 3 new vbptrs */
  void* _os_pad_vbptr[C+3+C%2];
  void* _os_pad_selfptr;
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_fbscd : public os_virtual_behavior_t<T>,
		    public virtual _os_pad_cons_disp_filler<T>,
		    public virtual _os_pad_cons_disp<T>,
		    public virtual T
{
  /* vbtbl(1), vbptrs(C), cons_disp(1), cons_disp_filler(1), vbptr(T)(1),
     selfptr(1), + 4 bytes if C is odd. */
  void* _os_pad_vbtbl_vbptrs_cons_disp_and_filler_vbptr_selfptr
    [1 + C%2 + C + 1 + 1 + 1 + 1];
};

#else
template <int C, class T> class os_vb_fbscd_1 : 
			  public os_virtual_behavior_t<T>
{
  /* account for C inherited vbptrs + vbtbl */
  void* _os_pad_vbtbl_and_vbptrs[1+C+C%2];
};

template <int C, class T> class os_vb_fbscd :
			  public os_vb_fbscd_1 <C,T>,
			  public virtual _os_pad_cons_disp_filler<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_fbscd_1 :
			  public os_virtual_behavior_t<T>,
			  public virtual _os_pad_cons_disp_filler<T>,
			  public virtual _os_pad_cons_disp<T>,
			  public virtual T
{
  /* account for C inherited vbptrs + vbtbl */
  void* _os_pad_vbtbl_and_vbptrs[1+C+C%2];
};

template <int C, class T> class os_vb_fbscd :
			  public os_vb_fbscd_1 <C,T>
{
  /* For MIPS platforms, the base class may already be rounded up */
  /* if EPC does non_virtual_base_round_ignores_virtual then the */
  /* conditional can be removed */

#ifdef _OS_I386
  /* EPC on Intel */
  void* _os_pad_selfptr;
#endif
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_fbscd_1 :
	public virtual _os_pad_cons_disp_filler<T>,
	public virtual _os_pad_cons_disp<T>
{
  /* this gets vftbl + vbtbl */
  virtual void dummy_function() {}
};

template <int C, class T> class os_vb_fbscd :
	public os_vb_fbscd_1<C,T>,
	public virtual T
{
  void* _os_pad_vbptr[3+C+C%2];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_fbscd :
	public virtual _os_pad_cons_disp_filler<T>,
	public virtual _os_pad_cons_disp<T>,
	public virtual T
{
  virtual void dummy_function() {}
  void* _os_pad_vbtbl;
  void* _os_pad_vbptr[3+C+C%2];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_linux)


template<int C, class T>
class os_vb_fbscd_1 
{
  void* _os_pad_vbptrs[1+C+C%2];
};

template<int C, class T>
class os_vb_fbscd_2 : public virtual _os_pad_cons_disp_filler<T> { };

template<int C, class T>
class os_vb_fbscd_3 : public virtual _os_pad_cons_disp<T> { };

template<int C, class T>
class os_vb_fbscd_4 : public virtual T { };

template<int C, class T>
class os_vb_fbscd :
  /* vftbl */
  public os_virtual_behavior_t<T>,
  /* vbtbl, inherited vbptrs */
  public os_vb_fbscd_1<C, T>,
  /* vbptr(cons_disp_filler(T)) */
  public os_vb_fbscd_2<C, T>,
  /* vbptr(cons_disp(T)) */
  public os_vb_fbscd_3<C, T>,
  /* vb ptr(T) */
  public os_vb_fbscd_4<C, T>
{
  /* selfptr */
  void* _os_pad_selfptr;
};

#endif

/*
  os_vb_fbsd - Not yet implemented

  - introduces vtbl, virtual base simultaneously, allowing for cset
    self pointers but not construction displacement members
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.
  - This is a special case that assumes the virtual base is 8 byte aligned
  - non-virtual class layout is:
    vftbl
    vbtbl
    [ 4 byte pad for odd number of inherited vb ptrs ]
    [ inherited vbptrs ]
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_fbsd_1 : 
			  public os_virtual_behavior_t<T>,
			  public virtual T
{
  void* _os_pad_vbtbl_and_pad[1+C+C%2] ;
};

template <int C, class T> class os_vb_fbsd :
			  public os_vb_fbsd_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_fbsd_1 : 
			  public os_virtual_behavior_t<T>
{
  void* _os_pad_vbtbl_and_pad [ 1 + (1+C)%2];
};

template <int C, class T> class os_vb_fbsd :
			  public os_vb_fbsd_1<C,T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_fbsd :
	public virtual T
{
  virtual void dummy_function(os_vb_fbsd<C,T>*) {}
  void* _os_pad_vbptr [C+1+C%2];
  void* _os_pad_selfptr;
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_fbsd : public os_virtual_behavior_t<T>,
		   public virtual T
{
  /* vbtbl(1), vbptrs(C), 1 extra if C is odd, 
     vbptr(T)(1), selfptr(1) */
  void* _os_pad_vbtbl_vbptrs_vbptr_selfptr[1 + C + C%2 + 1 + 1];
};

#else

template <int C, class T> class os_vb_fbsd_1 : 
			  public os_virtual_behavior_t<T>
{
  void* _os_pad_vbtbl_pad_vbptrs[2+C];
};

template <int C, class T> class os_vb_fbsd :
			  public os_vb_fbsd_1 <C,T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_fbsd_1 : 
			  public os_virtual_behavior_t<T>
{
  void* _os_pad_vbtbl_pad_vbptrs_but_one[1+C];
};

template <int C, class T> class os_vb_fbsd_2 : 
			  public os_vb_fbsd_1<T>,
			  public virtual T
{
  void* _os_pad_vbptr_extra;
};

template <int C, class T> class os_vb_fbsd :
			  public os_vb_fbsd_2 <C,T>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_fbsd_1 :
	public virtual T
{
  virtual void dummy_function() {}
};

template <int C, class T> class os_vb_fbsd :
	public os_vb_fbsd_1<C,T>
{
  void* _os_pad_1;
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_fbsd :
	public virtual T
{
  virtual void dummy_function() {}
  void* _os_pad_vbtbl;
  void* _os_pad_vbptr[C+1+C%2];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_linux)

template<int C, class T>
class os_vb_fbsd_1 
{
  void* _os_pad_vbptrs[1+C+C%2];
};

template<int C, class T>
class os_vb_fbsd :
  /* vftbl */
  public os_virtual_behavior_t<T>,
  /* vbtbl, inherited vbptrs */
  public os_vb_fbsd_1<C, T>,
  /* vb ptr(T) */
  public virtual T
{
  /* selfptr */
  void* _os_pad_selfptr;
};

#endif

/*
  os_vb_bs

  - introduces virtual base but no vftbl allowing for cset self pointers
    and virtual base table.
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.
  - non-virtual class layout is:
    vbtbl
    [ inherited vbptrs ]
    vbptr(T)
    selfptr
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_bs_1 : 
			  public virtual T
{
  void* _os_pad_vbtbl_vbpts[C+1];
};

template <int C, class T> class os_vb_bs :
			  public os_vb_bs_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_bs_1
{
  void* _os_pad_vbtbl;
};

template <int C, class T> class os_vb_bs :
			  public os_vb_bs_1<C,T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_bs :
	public virtual T
{
  void* _os_pad_vbptr [C+1];
  void* _os_pad_selfptr;
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_bs : public os_virtual_behavior_t<T>,
		 public virtual T
{
  /* vbptrs(C), vbptr(T)(1), selfptr(1) */
  void* _os_pad_vbptrs_vbptr_selfptr[C + 1 + 1];
};

#else

template <int C, class T> class os_vb_bs_1
{
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_bs :
			  public os_vb_bs_1 <C,T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};

#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_bs_1 :
			  public virtual T
{
  /* account for C inherited vbptrs + vbtbl */
  void* _os_pad_vbtbl_and_vbptrs[1+C];
};

template <int C, class T> class os_vb_bs :
			  public os_vb_bs_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_bs_1 :
	public virtual T
{
};

template <int C, class T> class os_vb_bs :
	public os_vb_bs_1<C,T>
{
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_bs :
	public virtual T
{
  void* _os_pad_vbtbl;
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_linux)

template<int C, class T>
class os_vb_bs_1 
{
  void* _os_pad_vbtbl_and_vbptrs[C + 1];
};


template<int C, class T>
class os_vb_bs : public os_vb_bs_1<C, T>,
		 public virtual T
{
  void* _os_pad_selfptr;
};

#endif


/*
  os_vb_bsd

  - introduces virtual base but no vftbl allowing for cset self pointers
    and virtual base table, expecting that the virtual base is 8 byte aligned.
  - The numeric template instantiation parameter is the number of inherited
    vbptrs when the virtual base has virtual bases.
  - non-virtual class layout is:
    vbtbl
    [ inherited vbptrs ]
    vbptr(T)
    selfptr
    4 byte pad
    */

#if defined(__os_cfront) || defined(__os_hpcfront) || (defined(_OS_cfrontC) && defined(_ODI_OSSG_))

template <int C, class T> class os_vb_bsd_1 : 
			  public virtual T
{
  void* _os_pad_vbtbl_pad_vbpts[C+2];
};

template <int C, class T> class os_vb_bsd :
			  public os_vb_bsd_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif


#ifdef __os_xlc

template <int C, class T> class os_vb_bsd_1
{
  void* _os_pad_vbtbl;
  char  _os_pad_0[4];
};

template <int C, class T> class os_vb_bsd :
			  public os_vb_bsd_1<C,T>,
			  public virtual T
{
};

#endif


#ifdef _OS_MicrosoftCC

template <int C, class T> class os_vb_bsd :
	public virtual T
{
  char  _os_pad_0[4];
  void* _os_pad_vbptr [C+1];
  void* _os_pad_selfptr;
};

#endif

#ifdef __os_cafe

#if defined(__os_sol2c5)

template<int C, class T>
class os_vb_bsd : public os_virtual_behavior_t<T>,
		  public virtual T
{
  void* _os_pad_vbptrs_vbptr_selfptr[C + 1 + 1];
  char* _os_pad_1[4];
};

#else

template <int C, class T> class os_vb_bsd_1
{
  void* _os_pad_vbtbl_and_pad_and_vbptrs[2+C];
};

template <int C, class T> class os_vb_bsd :
			  public os_vb_bsd_1 <C,T>,
			  public virtual T
{
  void* _os_pad_selfptr;
};
#endif

#endif

#ifdef _OS_EPC

template <int C, class T> class os_vb_bsd_1 :
			  public virtual T
{
  /* account for C inherited vbptrs + vbtbl + pad */
  void* _os_pad_vbtbl_and_pad_and_vbptrs[2+C];
};

template <int C, class T> class os_vb_bsd :
			  public os_vb_bsd_1 <C,T>
{
  void* _os_pad_selfptr;
};

#endif

#ifdef _OS_DECCXX

template <int C, class T> class os_vb_bsd_1 :
	public virtual T
{
};

template <int C, class T> class os_vb_bsd :
	public os_vb_bsd_1<C,T>
{
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
};

#endif

#if defined(__os_hpansi)

template <int C, class T> class os_vb_bsd :
	public virtual T
{
  void* _os_pad_vbptr[C+1];
  void* _os_pad_selfptr;
  char  _os_pad_1[4];
};

#endif

#if defined(__os_linux)

template<int C, class T>
class os_vb_bsd_1
{
  void* _os_pad_vbtbl_and_vbptrs[C+1];
};

template<int C, class T>
class os_vb_bsd :
  public os_vb_bsd_1<C, T>,
  public virtual T
{
  /* pad up the vb ptr to 8 bytes,
     add self ptr */
  void* _os_pad_vb_ptr_and_self_ptr[2];
  /* add additional 4 byte pad. */
  char _os_pad_1[4];
};
  
#endif


#include <ostore/hdrend.hh>
#endif






