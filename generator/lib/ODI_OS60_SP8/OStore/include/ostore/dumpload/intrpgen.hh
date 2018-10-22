/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef INTRPGEN_HH
#define INTRPGEN_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1998-2000 by eXcelon Corporation. All Rights Reserved.                          *
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
/***********************************************************************
* Author:  Rick Tompkins                                               *
* Version: 0.0                                                         *
***********************************************************************/


//-- Include files -----------------------------------------------------

#include <ostore/ostore.hh>
#include <ostore/mop.hh>

#include <ostore/dumpload/obj_loader.hh>
#include <ostore/dumpload/intrplod.hh>


/***********************************************************************
  class os_Interpretive_loader_generator
***********************************************************************/

class os_Interpretive_loader_generator : public os_Wrapper_actions {

  protected: // Construction
    os_Interpretive_loader_generator (os_Interpretive_loader&, os_Traverser&);
    os_Interpretive_loader_generator (os_Traverser&);
    ~os_Interpretive_loader_generator ();

  protected: // Member Type Actions
    os_boolean pre_action(const os_member_type& member_type);

  protected: // Static Predicates
    static os_boolean has_array_type (const os_member_variable&);

  protected: // Static Accessors
    static const char* get_type_string
       (const os_type& type,const os_member_variable* member);
    static const os_type& get_base_type(const os_type& given_type);
    static os_Type_loader& get_type_loader
       (const os_type& given_type,const os_member_variable* member);

  protected: // Accessors
    os_Interpretive_loader* get_interpretive_loader () const;
    os_Traverser& get_traverser () const;
    os_Wrapper_actions* get_previous_actions () const;
    os_unsigned_int32 get_data_offset (const os_base_class&) const;
    os_unsigned_int32 get_data_offset (const os_member_variable&) const;
    os_unsigned_int32 get_data_size (const os_member_variable&) const;
    os_unsigned_int32 get_object_offset (const os_base_class&) const;
    os_unsigned_int32 get_object_offset (const os_member_variable&) const;
    os_unsigned_int32 get_object_size (const os_member_variable&) const;
    os_unsigned_int32 get_number_elements (const os_member_variable&) const;

  protected: // Embedded data
    os_Interpretive_loader* interpretive_loader;
    os_Traverser* traverser;
    os_Wrapper_actions* previous_actions;

  };


#endif /* INTRPGEN_HH */
