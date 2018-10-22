/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DATA_GEN_HH
#define DATA_GEN_HH

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
#include <ostore/coll.hh>

#include <ostore/dumpload/intrpgen.hh>
#include <ostore/dumpload/intrplod.hh>


/***********************************************************************
  class os_Data_generator
***********************************************************************/

class os_Data_generator : public os_Interpretive_loader_generator {

  public: // Construction
    os_Data_generator (os_Interpretive_loader&, os_Traverser&);
    os_Data_generator (os_Traverser&);
    ~os_Data_generator ();

  public: // Accessors
    os_base_classes& get_data_bases ();
    os_members& get_data_members ();

  public: // Modifiers

  public: // Base Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_base_class& base_class);

  public: // Member Variable Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_member_variable& member_variable);

  protected: // Member Type Actions
    os_boolean pre_action(const os_member_type& member_type);

  protected: // Embedded data
    os_base_classes data_bases;
    os_members data_members;
    os_unsigned_int32 data_size;
    os_unsigned_int32 data_alignment;
    os_unsigned_int32 data_offset;

  protected: // Accessors
    os_unsigned_int32 get_data_size () const;
    os_unsigned_int32 get_data_alignment () const;
    os_unsigned_int32 get_data_offset () const;

  protected: // Modifiers
    void set_data_size (os_unsigned_int32);
    void set_data_alignment (os_unsigned_int32);
    void set_data_offset (os_unsigned_int32);
    os_unsigned_int32 get_corrected_offset (const os_type&);
    void increment_data_size (const os_member_variable&);

  protected: // Modifiers
    os_class_type& generate_minimal_data_type (const os_type& member_type,
                                               os_unsigned_int32 data_size, 
                                               os_unsigned_int32 data_alignment);
    os_class_type& generate_expected_data_type (const os_type& member_type);

  protected: // Friends
    friend class os_Interpretive_loader;

  };


/***********************************************************************
  class os_Data_debugger
***********************************************************************/

class os_Data_debugger : public os_Wrapper_actions {

  public: // Construction
    os_Data_debugger (os_Traverser&, ostream&);
    ~os_Data_debugger ();

  public: // Base Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_base_class& base_class);

  public: // Member Variable Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_member_variable& member_variable);

  protected: // Embedded data
    os_Traverser* traverser;
    os_Wrapper_actions* previous_actions;
    ostream* stream;

  protected: // Friends
    friend class os_Interpretive_loader;

  };


#endif /* DATA_GEN_HH */
