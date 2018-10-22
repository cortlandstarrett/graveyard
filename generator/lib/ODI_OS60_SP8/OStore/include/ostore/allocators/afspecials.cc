/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#include <ostore/allocators/afalloc.hh>
#include <ostore/allocators/afxalloc.hh>


/******************************************************************************
  This module contains specializations for get_allocated_type_typespec()
  for the fundamental types.

Member Function: get_allocated_type_typespec()
Class Name     : os_Allocator<T>
Purpose        : get the typespec for the fundamental types
               :
Parameters     : None
Return Value   : os_typespec *
Remarks        :
******************************************************************************/

#if defined (__os_aix43)
template <char *>
#endif
os_typespec * Get_Typespec(char * pt)  
{
  return os_typespec::get_char();
}

#if defined (__os_aix43)
template <double *>
#endif
os_typespec * Get_Typespec(double *pt)  
{
  return os_typespec::get_double();
}

#if defined (__os_aix43)
template <float *>
#endif
os_typespec * Get_Typespec(float *pt)  
{
  return os_typespec::get_float();
}
#if defined (__os_aix43)
template <int *>
#endif
os_typespec * Get_Typespec(int *pt)  
{
  return os_typespec::get_int();
}

#if defined (__os_aix43)
template <long *>
#endif
os_typespec * Get_Typespec(long *pt)  
{
  return os_typespec::get_long();
}

#if defined (__os_aix43)
template <long double *>
#endif
os_typespec * Get_Typespec(long double *pt)  
{
  return os_typespec::get_long_double();
}

#if defined (__os_aix43)
template <os_int16 *>
#endif
os_typespec * Get_Typespec(os_int16 *pt)  
{
  return os_typespec::get_os_int16();
}

#if defined (__os_aix43)
template <os_int64 *>
#endif
os_typespec * Get_Typespec(os_int64 *pt)  
{
  return os_typespec::get_os_int64();
}

#if !defined(__os_sgi_mips)
#if defined (__os_aix43)
template <os_signed_int8 *>
#endif
os_typespec * Get_Typespec(os_signed_int8 *pt)  
{
  return os_typespec::get_os_signed_int8();
}
#endif

#if defined (__os_aix43)
template <os_unsigned_int8 *>
#endif
os_typespec * Get_Typespec(os_unsigned_int8 *pt)  
{
  return os_typespec::get_os_unsigned_int8();
}

#if defined (__os_aix43)
template <os_unsigned_int16 *>
#endif
os_typespec * Get_Typespec(os_unsigned_int16 *pt)  
{
  return os_typespec::get_os_unsigned_int16();
}

#if defined (__os_aix43)
template <os_unsigned_int32 *>
#endif
os_typespec * Get_Typespec(os_unsigned_int32 *pt)  
{
  return os_typespec::get_os_unsigned_int32();
}

#if defined (__os_aix43)
template <os_unsigned_int64 *>
#endif
os_typespec * Get_Typespec(os_unsigned_int64 *pt)  
{
  return os_typespec::get_os_unsigned_int64();
}

#if defined (__os_aix43)
template <void**>
#endif
os_typespec * Get_Typespec(void**pt)  
{
  return os_typespec::get_pointer();
}

