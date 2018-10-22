
/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/

//-- Include files -----------------------------------------------------
#include <ostore/ostore.hh>
#include <ostore/portypes.hh>

/* The following only wants to be included on systems
   with a completely global link time namespace. --rick@odi.com */
/* TBD: figure out the right macro name to ensure the above
        constraint. --rick@odi.com */
#ifndef _OS_Win32
#include <ostore/traverse/instanti.hc>
#include "jaccessor.hh"
#include "jaccessor.hc"
#include "d_instanti.hc"
#include <ostore/dumpload/dumpinst.hc>
#endif

#if defined(_OS_DECCXX) || defined(__os_sgi_mips)
/* Putting these here since they mess up load if I put them in instanti.hc  */ 


os_typespec* _Dict_pt_slot<void*>::get_os_typespec()
{
  return os_typespec::get_pointer();
}

os_typespec* _Rhash_pt<void*>::get_os_typespec()
{
  return os_typespec::get_pointer();
}


#endif
