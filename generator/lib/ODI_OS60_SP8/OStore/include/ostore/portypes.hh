/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _PORTABLE_TYPES_HH_
#define _PORTABLE_TYPES_HH_
#include <ostore/hdrstart.hh>

/* */
#ifdef _OS_64BIT_PTR_ERRORS
#include <llpl_types.hh>
#endif

/* Definitions:
 *    Macro		Meaning
 * _OS_64BIT_NATIVE     defined for 64 bit platforms
 * _OS_ALPHA		DEC Alpha AXP processor
 * _OS_ANSI_TOKENS	Token pasting
 * _OS_DECLSPEC_DLLEXPORT  __declspec(dllexport) for VC++
 * _OS_DECLSPEC_DLLIMPORT  __declspec(dllimport) for VC++
 * _OS_DECCXX		DEC C++
 * _OS_DECCXX32		DEC C++ (VMS version)
 * _OS_DECCXX64		DEC C++ (AXP version)
 * _OS_DLLEXPORT	Always defined, __declspec(dllexport) on Win32, empty otherwise
 * _OS_DLLIMPORT(n)	Always defined
 * _OS_Desktop		For Windows, OS/2, or Novell
 * _OS_EPC		EPC compiler
 * _OS_I386		Intel i386/i486/Pentium
 * _OS_IBMC		IBM C/C++ Tools
 * _OS_INSTANTIATE	Instantiate a template.  Only defined if proposed ANSI instantiation is
 *			implemented by the compiler.
 * _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg_1,function_args)
 * _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg_1,template_arg_2,function_args)
 *			Same but for a template function rather than class.
 * _OS_INT64_NATIVE	Compiler provides a 64-bit integer (32 or 64 bit platform)
 * _OS_MicrosoftCC	Microsoft C/C++, value is version (also see _OS_VCPP_n)
 * _OS_OS2		For OS/2
 * _OS_PROTOTYPES	C requires function prototypes
 * _OS_StandardC	Compiler is at least ANSI C
 * _OS_VCPP_n	        Visual C++ compiler bug n work-around
 * _OS_TYPENAME         Always defined as typename for compilers that
 *                       support the keyword, empty otherwise
 * _OS_VECTOR_NEW	Defined if operator new[] is defined.
 * _OS_VOLATILE         Always defined, volatile for compilers that
 *                      support the keyword, empty otherwise.
 * _OS_VOLATILE_IS_volatile Defined if _OS_VOLATILE is defined to volatile
 * _OS_WATCOMC		WATCOM C++
 * _OS_Win		For 16 or 32 bit Windows
 * _OS_Win32		For 32 bit Windows (Windows NT or Windows 32s)
 * _OS_Win64		For 64 bit Windows (Windows 2000 Intel 64)
 * _OS_Win32c		For 32 bit Windows 32c (Chicago)
 * _OS_Win32s		For 32 bit Windows 32s (subset which runs on Win16)
 * _OS_WinNT		For 32 bit Windows NT, not Windows 32s or Windows 32c
 * _OS_WinOS2		For Windows (16 or 32 bit) or OS/2
 * _OSSYSCALL           Always defined, _System on OS/2, __stdcall on NT.
 *                      Should be defined to the universal calling convention
 * __os_unix		Unix(TM)
 * __os_xlc		IBM C/C++ Tools or AIX xlC
 *
 */

/* _OS_ANSI_CASTS       platform can do ansi casts */
/* _OS_REINTERPRET      reinterpret_cast on ansi platforms. Nuthin elsewhere. */

/* PLATFORM-SPECIFIC PACKAGING TOP TOKEN. DO NOT REMOVE. */

/* avoid using #elif */

/* We are always using templates */
#define __TEMPLATES__ 1

/* as compilers support the typename keyword, define _OS_TYPENAME
   to be 'typename' for that environment.  
*/
#ifndef _OS_TYPENAME
#define _OS_TYPENAME
#endif

/* Microsoft 16 and 32 bit Windows heuristications */
#if defined(_MSC_VER)
#define _OS_MicrosoftCC _MSC_VER
#define _OS_VCPP_19
#define _OS_VCPP_27
#define _OS_VCPP_201

#define _OS_INSTANTIATE template
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name function_args
#define _OS_VCPP_217r
#define _OS_VCPP_222

#ifdef _M_IX86
#define _OS_I386
#endif

#ifdef _ALPHA_
#define _OS_ALPHA
#endif

#define _OS_Win32 1

#if !defined(_OS_Win32s) && !defined(_OS_Win32c)
#define _OS_WinNT 1
#endif

/* New definition - two underscores */
#define _OSSYSCALL __stdcall
#if defined(_WIN64 )		/* 64 Bit native Windows */
#define _OS_Win64		/* IA64 Windows	*/
#define _OS_64BIT_NATIVE
#ifndef _OS_DLL_NAME
#define _OS_DLL_NAME _OS_PRIVATE
#endif
#endif
#endif /* _MSC_VER */

#if defined(__IBMC__)
#define _OS_IBMC __IBMC__
#endif

#if defined(__IBMCPP__)
#define _OS_IBMC __IBMCPP__
#endif

#if defined(_OS_IBMC)
#define __os_xlc

#if defined(__OS2__)
#define _OS_OS2
#define _OS_I386
#define _OSSYSCALL _System
#if (_OS_IBMC >= 300) 
#define _OS_VECTOR_NEW
#endif
#endif

#define _OS_VECTOR_NEW
#ifdef __DEBUG_ALLOC__
#define _OS_DBALLOC_PARMS , char const * _os_dballoc_file, size_t _os_dballoc_line
#define _OS_DBALLOC_ARGS , _os_dballoc_file, _os_dballoc_line
#define _OS_DBALLOC_NARGS , __FILE__, __LINE__
#endif
#endif

#ifdef __xlC__
#ifndef __os_xlc  /* avoid warnings in internal compilations */
#define __os_xlc
#endif
#ifndef __os_aix32 /* avoid warnings in internal compilations */
#define __os_aix32
#endif
#ifndef __os_aix41 /* avoid warnings in internal compilations */
#define __os_aix41
#endif
#ifndef __os_aix43
#define __os_aix43
#endif
#endif

#ifdef __WATCOMC__
#define _OS_WATCOMC __WATCOMC__
#define _OS_I386
#if defined(__OS2__)
#define _OS_OS2
#define _OSSYSCALL __syscall
#endif
#endif

#if (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x400) || (defined(i386) && defined(__SUNPRO_C) && __SUNPRO_C >= 0x301) || (defined(__SUNPRO_C) && __SUNPRO_C >= 0x400)
#ifndef __os_unix
#define __os_unix
#endif
#ifndef __os_cafe
#define __os_cafe
#endif /* cafe */
#ifdef __SVR4
#ifndef __os_sol2
#define __os_sol2
#endif /* sol2 */
#ifndef __os_sysv4
#define __os_sysv4
#endif /* sysv4 */
#endif /* SYSV4 */
/* now find out of this is the SPARKWorks 5.1 (Forte 6.0) compiler and
   set a couple of more flags accordingly. */
#if  (__SUNPRO_CC >= 0x510 && __SUNPRO_CC_COMPAT >= 5)
#ifdef _OS_TYPENAME
#undef _OS_TYPENAME
#define _OS_TYPENAME typename
#endif
#ifndef __os_sol2c5
#define __os_sol2c5
#endif /* __os_sol2c5 */
#ifdef __sparcv9
#ifndef  __os_sol64
#define __os_sol64
#endif /* __os_sol64 */
#endif /* Solaris 64 bits */
#endif /* FORTE compiler */
#endif /* CAFE COMPILER */

#ifdef __DECCXX_VER
#define _OS_DECCXX __DECCXX_VER
#else
#ifdef __DECCXX
#define _OS_DECCXX __DECCXX
#else
#if (!defined(__cplusplus)) && (defined(__osf__) || defined(__vaxc))
#define _OS_DECCXX 0	/* I can't figure out how to get the version of DEC C. --Hornig */
#endif /* !defined(__cplusplus) ... */
#endif /* __DECCXX */
#endif /* __DECCXX_VER */

#ifdef _OS_DECCXX
#if defined(__alpha) && !defined(__32BITS)
#define _OS_DECCXX64
#define _OS_64BIT_NATIVE
#else
#define _OS_DECCXX32
#endif
#if defined(__unix) || defined(__unix__)
#define __os_unix
#endif
#ifdef __alpha
#define _OS_ALPHA
#endif
#if defined(__alpha) && defined(__osf__)
#define __os_alpha_osf
#endif
#if (__DECCXX_VER >= 60390008) && defined(__alpha) && defined(__osf__)
#define __os_alpha_osf5
#endif

#define _OS_VECTOR_NEW
#endif /* _OS_DECCXX */

#if defined(__os_sol64)
#define _OS_64BIT_NATIVE
#endif

#if defined(__os_sol2c5) || defined(__os_sol64)
#ifndef _OS_VECTOR_NEW
#define _OS_VECTOR_NEW
#endif
#define _OS_INSTANTIATE template class
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
#endif

#if defined(sni)
#define _OS_INSTANTIATE template
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
#ifndef __os_sni
#define __os_sni
#endif
#ifndef _OS_EPC
#define _OS_EPC
#endif
#ifndef __os_sysv4
#define __os_sysv4
#endif
#ifndef __os_mips_eb
#define __os_mips_eb
#endif
#endif

#if defined(__ECPP__) && defined(__I386)
#define _OS_INSTANTIATE template
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
/* if we are using EPC and we are an an x86 box, assume we are lynx) */
#ifndef __os_lynx
#define __os_lynx
#endif
#ifndef _OS_EPC
#define _OS_EPC
#endif
#ifndef _OS_I386
#define _OS_I386
#endif
#endif

#if defined(_OS_EPC)
#define _OS_VECTOR_NEW
#endif

#if defined(_OS_Win32)
#define _OS_Win
#endif

#if defined(_OS_Win) || defined(_OS_OS2)
#define _OS_WinOS2
#endif

#if defined(_OS_WinOS2)
#define _OS_Desktop
#endif

#if defined(sgi) || defined(__sgi)
#ifndef __os_sgi_mips
#define __os_sgi_mips
#endif
#ifndef __os_sysv4
#define __os_sysv4
#endif
#ifndef __os_mips_eb
#define __os_mips_eb
#endif
#define _OS_VECTOR_NEW
#define OS_NO_DEPRECATED_INTERFACES
#endif /*__sgi*/

#if defined(__linux__)
#define _OS_INSTANTIATE template
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
  /* turns on alternate definitions of boot schema. */
#define GCC_ALTERNATE_LAYOUT 1
#ifndef __os_linux
#define __os_linux
#endif
#ifndef __os_unix 
#define __os_unix
#endif
#ifdef _OS_TYPENAME
#undef _OS_TYPENAME
#define _OS_TYPENAME typename
#endif
#define _OS_VECTOR_NEW
#endif /* __linux__ */

#if defined(__hpux)
#define _PORTABLE_TYPES_HH_ARCH_FOUND
#ifndef __os_unix /* all HP unix */
#define __os_unix
#endif
#ifndef __os_hppa /* all HP PA-RISC */
#define __os_hppa
#endif
#ifndef __os_hpux /* all HP hpux */
#define __os_hpux
#endif
#ifndef __os_hp11 /* HP11 hpux 32 & 64 bits */
#define __os_hp11
#endif

#if defined(__LP64__)
#ifndef __os_hp64
#define __os_hp64   /* HP11 64 bit */
#endif
#ifndef _OS_64BIT_NATIVE
#define _OS_64BIT_NATIVE
#endif
#else
#ifndef __os_hp32
#define __os_hp32  /* HP11 32 bit */
#endif
#endif
#ifdef __STDCPP__ /* some HP ansi */
#ifndef __os_hpansi /* old ifdef */
#define __os_hpansi
#endif
#ifndef _OS_HP_aCC
#define _OS_HP_aCC /* new ifdef */
#endif
// define macro for typename keyword
#ifdef _OS_TYPENAME
#undef _OS_TYPENAME
#define _OS_TYPENAME typename
#endif
#define _OS_VECTOR_NEW
#define _OS_ANSI_CASTS
#define _OS_COMPILER_SUPPORTS_BOOL
#define _OS_INSTANTIATE template class
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
#endif

#if ( !defined (_LINGUIST_) )
#define _OS_INSTANTIATE template class
#define _OS_INSTANTIATE_FUNCTION_1(return_type,name,template_arg1,function_args) \
  template return_type name <template_arg1> function_args
#define _OS_INSTANTIATE_FUNCTION_2(return_type,name,template_arg1,template_arg2,function_args) \
  template return_type name <template_arg1,template_arg2> function_args
#endif
#define OS_NO_DEPRECATED_INTERFACES
#ifndef _OS_HP_aCC
typedef unsigned char os_unsigned_int8;
typedef char os_signed_int8;
typedef short os_int16;
typedef unsigned short os_unsigned_int16;
typedef int os_int32;
typedef unsigned int os_unsigned_int32;
/* os_boolean must always be int for link compatibility
   and persistent storage compatibility.*/
typedef int os_boolean;
/* however ... there are cases involving the return values of 
   operators where we really have to use a boolean if the
   compiler has a boolean. Perhaps this should exempt MSVC,
   since this is link-incompatible there and wasn't needed
   for the initial port to MSVC 5.0. */
#ifdef _OS_COMPILER_SUPPORTS_BOOL
typedef bool os_boolean_operator_return;
#else
typedef int os_boolean_operator_return;
#endif
#ifdef _OS_Win64
typedef __int64 os_unixtime_t;
#else
typedef long os_unixtime_t;
#endif
typedef int os_compare_result;
typedef unsigned int osbitf;
typedef os_unsigned_int32 os_pid;
#define os_int32_typestring "int"
#define os_unsigned_int32_typestring "unsigned int"
#endif

#if defined(__STDC__) && !defined(_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS 1
#endif
#endif

#if defined(_OS_Desktop) || defined(__os_xlc) || defined(__os_cafe) || defined(_OS_DECCXX) || defined(_OS_EPC) || defined(_OS_HP_aCC) || defined(__os_linux)

#if defined(i386)
#define _OS_I386
#endif

/*102797:sean:aCC:This constant has been defined in the general case above*/
#if !defined (_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS
#endif
#define _OS_StandardC
#define _OS_PROTOTYPES
#define OS_NO_DEPRECATED_INTERFACES
#define _OS_VOLATILE volatile
#define _OS_VOLATILE_IS_volatile

typedef unsigned char os_unsigned_int8;
#define os_unsigned_int8_typestring "unsigned char"
typedef signed char os_signed_int8;
#define os_signed_int8_typestring "signed char"
typedef short os_int16;
#define os_int16_typestring "short"
typedef unsigned short os_unsigned_int16;
#define os_unsigned_int16_typestring "unsigned short"

#ifndef _OS_64BIT_PTR_ERRORS
typedef int os_int32;
#define os_int32_typestring "int"
typedef unsigned int os_unsigned_int32;
#define os_unsigned_int32_typestring "unsigned int"
#endif 

typedef int os_boolean;
#define os_boolean_typestring "int"

#if defined(_OS_DECCXX64)
typedef int os_unixtime_t;
#define os_unixtime_t_typestring "int"
#elif defined(_OS_Win64)
typedef __int64 os_unixtime_t;
#define os_unixtime_t_typestring "__int64"
#else
typedef long os_unixtime_t;
#define os_unixtime_t_typestring "long"
#endif

typedef int os_compare_result;
#define os_compare_result_typestring "int"
typedef unsigned int osbitf; 
#define osbitf_typestring "unsigned int"
typedef os_unsigned_int32 os_pid; 
#define os_pid_typestring os_unsigned_int32_typestring

#else  

//Missing architecture-specific information.
/*  This was brought over straight from sgi's 5.1 code.  I'm pretty sure that all *
 *  this is not still needed.  I will come back and clean this up when time       *
 *  permits.  bduong                                                              */
#define _OS_cfrontC

#if ( defined (__os_cplusplus) && !defined (_LINGUIST_) )
#define _OS_INSTANTIATE template
#endif

#if defined(i386) || defined(__i386) || defined(__386__) || defined(__os_ncr)
#define _OS_I386
#endif

#if defined (_AIX) && !defined(_PORTABLE_TYPES_HH_ARCH_FOUND)
#define _PORTABLE_TYPES_HH_ARCH_FOUND
#ifndef _OS_ANSI_TOKENS
#define _OS_ANSI_TOKENS
#endif
#define __os_unix
typedef unsigned char os_unsigned_int8;
typedef char os_signed_int8;
typedef short os_int16;
typedef unsigned short os_unsigned_int16;
typedef int os_int32;
typedef unsigned int os_unsigned_int32;
typedef int os_boolean;
#ifdef _OS_Win64
typedef __int64 os_unixtime_t;
#else
typedef long os_unixtime_t;
#endif
typedef int os_compare_result;
typedef unsigned int osbitf;
typedef os_unsigned_int32 os_pid;
#define os_int32_typestring "long"
#define os_unsigned_int32_typestring "unsigned long"
#endif /* block that turns on _OS_cfrontC or not */


#if (defined(unix)||defined(__unix) ||defined(_MIPS_ABI)) && !defined(_PORTABLE_TYPES_HH_ARCH_FOUND)
#define _PORTABLE_TYPES_HH_ARCH_FOUND
#define __os_unix
typedef unsigned char os_unsigned_int8;
typedef char os_signed_int8;
typedef short os_int16;
typedef unsigned short os_unsigned_int16;
typedef int os_int32;
typedef unsigned int os_unsigned_int32;
typedef int os_boolean;
#ifdef _OS_Win64
typedef __int64 os_unixtime_t;
#else
typedef long os_unixtime_t;
#endif
typedef int os_compare_result;
typedef unsigned int osbitf;
typedef os_unsigned_int32 os_pid;
#define os_int32_typestring "int"
#define os_unsigned_int8_typestring "unsigned char"
#define os_unsigned_int16_typestring "unsigned short"
#define os_unsigned_int32_typestring "unsigned int"
#define os_int8_typestring "char"
#define os_int16_typestring "short"
#define os_int32_typestring "int"
#define os_signed_int8_typestring "char"
#define os_signed_int16_typestring "short"
#define os_signed_int32_typestring "int"
#endif

#ifndef _PORTABLE_TYPES_HH_ARCH_FOUND

/* Shouldn't happen.  Try to make the C compiler issue an error. */
typedef Unrecognized_Architecture sorry;

#endif

#undef _PORTABLE_TYPES_HH_ARCH_FOUND

#if defined(__STDC__) && !defined(_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS
#endif

#if (defined(__os_sysv4) && !defined(__os_sgi_mips)) && !defined(_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS
#endif

#if defined(__STDC__)
#define _OS_StandardC
#endif

#if defined(stone) && !defined(__os_stone)
#define __os_stone
#endif
#if defined(__os_stone) && !defined(_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS
#endif


#if defined(__STDCPP__) && !defined(_OS_ANSI_TOKENS)
#define _OS_ANSI_TOKENS
#endif

#ifdef __NCR
#ifndef __cfront21
#define __cfront21
#endif
#endif

#if defined(_MIPS_ABI)
#define __os_sysv4
#ifndef _OS_ANSI_TOKENS
#define _OS_ANSI_TOKENS
#endif
#ifndef __os_mips_eb
#define __os_mips_eb
#endif
#endif 

#endif

#ifndef _OSSYSCALL
#define _OSSYSCALL
#endif

#if defined(__os_sol2) || defined (__os_ncr) || defined(__os_sgi_mips)
#define _OS_VOLATILE volatile
#define _OS_VOLATILE_IS_volatile
#endif

#ifndef _OS_VOLATILE
#define _OS_VOLATILE
#endif

#ifndef _OS_DBALLOC_PARMS
#define _OS_DBALLOC_PARMS
#define _OS_DBALLOC_ARGS
#define _OS_DBALLOC_NARGS
#endif

#ifdef _OS_VECTOR_NEW
#define _OS_VECTOR []
#else
#define _OS_VECTOR
#endif

/* DLL import/export definitions for Win32 */

#define _OS_PRIVATE	1	/* Use for modules which don't export data */
#define _OS_LOW		2
#define _OS_LOWNET	3
#define _OS_CLIENT	4
#define _OS_COLL	5
#define _OS_MOP		6
#define _OS_SEVOL	7
#define _OS_SATMGR	8
#define _OS_R4UPGRDB	9
#define _OS_QRY	        10
#define _OS_BACKREST	11
#define _OS_ST		12
#define _OS_OPE		13
#define _OS_STRCONV	14
#define _OS_DBUTIL	15
#define _OS_ALLOC	16
#define _OS_JTC         17
#define _OS_EXPAT       18
#define _OS_CMTL        19
#define _OS_TRAVERSE    20

#ifndef _OS_DLL_NAME
#ifdef _OS_NEED_DLL_NAME /* Defined while compiling ObjectStore on VC++ */
typedef _OS_DLL_NAME_needed sorry;
#else
#define _OS_DLL_NAME _OS_PRIVATE
#endif /* OS_NEED_DLL_NAME */
#endif /* _OS_DLL_NAME */

#if defined(_OS_MicrosoftCC)
#define _OS_DECLSPEC_DLLEXPORT __declspec(dllexport)
#define _OS_DECLSPEC_DLLIMPORT __declspec(dllimport)
#else
#define _OS_DECLSPEC_DLLEXPORT
#define _OS_DECLSPEC_DLLIMPORT
#endif

#if defined(_OS_MicrosoftCC)
#define _OS_DLLIMPORT(dll_name) dll_name##_IMPORT

#if (_OS_DLL_NAME==_OS_PRIVATE)
#define _OS_PRIVATE_IMPORT
#define _OS_DLLEXPORT
#else
#define _OS_DLLEXPORT _OS_DECLSPEC_DLLEXPORT
#endif /* _OS_PRIVATE */

#if (_OS_DLL_NAME==_OS_LOW)
#define _OS_LOW_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_LOW_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_LOW */

#if (_OS_DLL_NAME==_OS_LOWNET)
#define _OS_LOWNET_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_LOWNET_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_LOWNET */

#if (_OS_DLL_NAME==_OS_CLIENT)
#define _OS_CLIENT_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_CLIENT_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_CLIENT */

#if (_OS_DLL_NAME==_OS_COLL)
#define _OS_COLL_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_COLL_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_COLL */

#if (_OS_DLL_NAME==_OS_DBUTIL)
#define _OS_DBUTIL_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_DBUTIL_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_DBUTIL */

#if (_OS_DLL_NAME==_OS_QRY)
#define _OS_QRY_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_QRY_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_QRY */

#if (_OS_DLL_NAME==_OS_MOP)
#define _OS_MOP_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_MOP_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_MOP */

#if (_OS_DLL_NAME==_OS_SEVOL)
#define _OS_SEVOL_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_SEVOL_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_SEVOL */

#if (_OS_DLL_NAME==_OS_SATMGR)
#define _OS_SATMGR_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_SATMGR_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_SATMGR */

#if (_OS_DLL_NAME==_OS_R4UPGRDB)
#define _OS_R4UPGRDB_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_R4UPGRDB_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_R4UPGRDB */

#if (_OS_DLL_NAME==_OS_BACKREST)
#define _OS_BACKREST_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_BACKREST_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_R4UPGRDB */

#if (_OS_DLL_NAME==_OS_ST)
#define _OS_ST_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_ST_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_ST */

#if (_OS_DLL_NAME==_OS_OPE)
#define _OS_OPE_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_OPE_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_OPE */

#if (_OS_DLL_NAME==_OS_STRCONV)
#define _OS_STRCONV_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_STRCONV_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_STRCONV */

#if (_OS_DLL_NAME==_OS_ALLOC)
#define _OS_ALLOC_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_ALLOC_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_ALLOC */

#if (_OS_DLL_NAME==_OS_JTC)
#define _OS_JTC_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_JTC_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_JTC */

#if (_OS_DLL_NAME==_OS_EXPAT)
#define _OS_EXPAT_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_EXPAT_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_EXPAT */

#if (_OS_DLL_NAME==_OS_CMTL)
#define _OS_CMTL_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_CMTL_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_CMTL */

#if (_OS_DLL_NAME==_OS_TRAVERSE)
#define _OS_TRAVERSE_IMPORT _OS_DECLSPEC_DLLEXPORT
#else
#define _OS_TRAVERSE_IMPORT _OS_DECLSPEC_DLLIMPORT
#endif /* _OS_CMTL */


#else /* Not _OS_MicrosoftCC */
#define _OS_DLLIMPORT(dll_name)
#define _OS_PRIVATE_IMPORT
#define _OS_LOW_IMPORT
#define _OS_LOWNET_IMPORT
#define _OS_CLIENT_IMPORT
#define _OS_COLL_IMPORT
#define _OS_DBUTIL_IMPORT
#define _OS_MOP_IMPORT
#define _OS_SEVOL_IMPORT
#define _OS_SATMGR_IMPORT
#define _OS_R4UPGRDB_IMPORT
#define _OS_BACKREST_IMPORT
#define _OS_DLLEXPORT
#define _OS_QRY_IMPORT
#define _OS_ST_IMPORT
#define _OS_ALLOC_IMPORT
#define _OS_CMTL_IMPORT
#define _OS_TRAVERSE_IMPORT
#endif /* _OS_MicrosoftCC */

#if defined(__os_cafe) || defined(__os_sgi_mips)
#define ODI_INST_INTERNAL static int _instantiate ();
#define _ODI_NEED_ODI_INST
#else /* __os_cafe */
#define ODI_INST_INTERNAL 
#endif /* __os_cafe */
#define ODI_INST() ODI_INST_INTERNAL friend class dummy_friend

/* Definitions for DEC C++. */
typedef char* os_char_p;
typedef void* os_void_p;
#if defined(_OS_StandardC) || defined(__cplusplus)
typedef char const* os_char_const_p;
typedef const char* os_const_char_p;
typedef void const* os_void_const_p;
#else
typedef char* os_char_const_p;
typedef char* os_const_char_p;
typedef void* os_void_const_p;
#endif /* _OS_StandardC */

#ifdef _OS_ANSI_CASTS
#define _OS_REINTERPRET(type,val) reinterpret_cast<type>(val)
#else
#define _OS_REINTERPRET(type,val) (type)(val)
#endif

/* integral type which can hold a pointer */
#if defined(__os_aix43) || defined(__os_aix32) || (defined(_OS_DECCXX64) && (__INITIAL_POINTER_SIZE != 32)) || defined(__os_hp64) || defined(__os_sol64)
typedef unsigned long os_ptr_val;
#define os_ptr_val_typestring "unsigned long"
#elif defined(_OS_Win64)
typedef unsigned __int64 os_ptr_val;
#define os_ptr_val_typestring "unsigned __int64"
#else
typedef unsigned int os_ptr_val;
#define os_ptr_val_typestring "unsigned int"
#endif
#define OS_PTR_MASK (~(os_ptr_val)(sizeof(os_ptr_val)-1))

/* types for 64 bit signed and unsigned integers */
#if defined(_OS_64BIT_NATIVE) || defined(_OS_MicrosoftCC) || defined(__os_cafe) || defined(__os_sgi_mips) || defined(__os_hp11) || defined(__os_linux) || defined(__os_aix43)

#define _OS_INT64_NATIVE
#if defined(_OS_64BIT_NATIVE) && !defined(_OS_Win64) && !(defined(__os_hp11) && !defined(__os_hp64))
  typedef long os_platform_int64;
  #define os_platform_int64_typestring "long"
  typedef unsigned long os_platform_uint64;
  #define os_platform_uint64_typestring "unsigned long"
#else   
#if defined(_OS_MicrosoftCC)
  /* On Microsoft platform use __int64 */
  typedef __int64 os_platform_int64;
  #define os_platform_int64_typestring "__int64"
  typedef unsigned __int64 os_platform_uint64;
  #define os_platform_uint64_typestring "unsigned __int64"
#else 
#if defined(__cplusplus) || defined(__os_hp32) || (defined(__os_hp11) && !defined(__os_hp64)) 
  typedef long long os_platform_int64;
  #define os_platform_int64_typestring "long long"
  typedef unsigned long long os_platform_uint64;
  #define os_platform_uint64_typestring "unsigned long long"
#endif /* _OS_MicrosoftCC */ 
#endif /* __cplusplus */ 
#endif /* _OS_64BIT_NATIVE */
#else /* On platforms which do not have a native type... */
  /* TDB - develop non-native int64 class 
     This has to be commented out as long as lingossg\ccaudit.c
     is compiled without any platform or compiler defined.
  typedef not_yet_implemented os_platform_int64;
  typedef not_yet_implemented os_platform_uint64;
  */
#endif /* _OS_64BIT_NATIVE || _OS_MicrosoftCC || __os_cafe || __os_sgi_mips  */


/* An os_DLL_handle is a platform-specific handle to a loaded
 * instance of a DLL.  For example, an HMODULE on Windows NT
 * or a void* on Solaris.
 * os_null_DLL_handle is a null value for this type.  Do not
 * write code assuming that os_null_DLL_handle is zero (false).
 */
#if defined(_OS_WinOS2)
/* os_DLL_handle is really HMODULE, but there are too many problems
 * with including Windef.h here, so we use void* instead */
typedef void* os_DLL_handle;
#define os_null_DLL_handle ((os_DLL_handle)0)

#elif defined(_AIX)
typedef void* os_DLL_handle;
#define os_null_DLL_handle ((os_DLL_handle)0)

#elif defined(__hpux)
typedef void* os_DLL_handle;
#define os_null_DLL_handle ((os_DLL_handle)0)


/* Accepts __os_unix because when compiling with cc rather than CC on
 * Solaris, __os_sol2 does not get defined.  This matters when compiling
 * a user program, not when compiling ObjectStore itself.
 * I guess we just have to assume a generic Unix works like Solaris.
 */
#elif defined(__os_sol2) || defined(__osf__) || defined(__os_sgi_mips) || defined(__os_unix) || defined(__os_linux)
typedef void* os_DLL_handle;
#define os_null_DLL_handle ((os_DLL_handle)0)
#endif

/* Define concantenation macros which can be used with both token pasting and
 * non token pasting compilers.
 * NOTE: Do not put spaces between the arguments in a call to this macro. Some 
 * compilers will preserve the spaces with the result that the arguments will
 * not be concatenated.
 */

#if defined(_OS_ANSI_TOKENS)
#define _ODI_CONCAT(ARG1, ARG2)		ARG1##ARG2
#define _ODI_CONCAT3(ARG1, ARG2, ARG3)	ARG1##ARG2##ARG3
#define _ODI_STRINGIFY(ARG)			#ARG
#else
#define _ODI_CONCAT(ARG1, ARG2)		ARG1/**/ARG2
#define _ODI_CONCAT3(ARG1, ARG2, ARG3)	ARG1/**/ARG2/**/ARG3
#define _ODI_STRINGIFY(ARG)			"ARG"
#endif

/*
 * Pseudo decl-specifiers for global variables
 *
 * These expand into nothing, but act as structured comments to indicate
 * how a static or global variable is used with respect to multiple sessions.
 * Use these like you would use const.
 */

/* process_wide indicates a variable that can be used by any thread in the
 * process.  Put a comment before the variable's declaration that specifies
 * what locking strategy is used to protect against simultaneous writes and
 * against reads simultaneous with writes.
 */
#define process_wide

/* process_wide_unsafe indicates a variable that can be used by any thread
 * in the process, and is not protected against simultaneous access.
 * When using this variable you must be aware that its value could be
 * garbled by unpredictable timing hazards.  Use this feature sparingly!
 */
#define process_wide_unsafe

/* schmgen_only indicates a variable that could be used by any thread
 * in the process, and is not protected against simultaneous access,
 * but does not suffer from timing hazards because all code that writes
 * this variable is only executed in the schema generator (ossg), which
 * is not multi-threaded.
 */
#define schmgen_only

/* const_after_preinit indicates a variable that can be used by any thread
 * in the process, but is only written once, to initialize it.  There are
 * no timing hazards because the initialization happens in a function called
 * by _Preinitialize_objectstore the first time it is called in the process.
 * This happens before ObjectStore can possibly be called by multiple threads.
 */
#define const_after_preinit

/* const_after_once_only indicates a variable that can be used by any thread
 * in the process, but is only written once, to initialize it.  There are
 * no timing hazards because the initialization happens the first time the
 * variable is referenced, under the protection of the BEGIN_ONCE_ONLY and
 * END_ONCE_ONLY macros.
 */
#define const_after_once_only


/* PLATFORM-SPECIFIC PACKAGING BOTTOM TOKEN. DO NOT REMOVE. */

#include <ostore/hdrend.hh>
#endif /* _PORTABLE_TYPES_HH_ */
