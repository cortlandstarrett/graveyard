/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REF_SPC_HH
#define REF_SPC_HH

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
#include <ostore/dumpload/dumper.hh>

/***********************************************************************
  class os_reference_local_specialization
***********************************************************************/

class os_reference_local_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;

  };

/***********************************************************************
  class os_reference_this_DB_specialization
***********************************************************************/

class os_reference_this_DB_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string (const os_class_type&) const;

  };


/***********************************************************************
  class os_reference_specialization
***********************************************************************/

class os_reference_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string (const os_class_type&) const;
  };


/***********************************************************************
  class os_reference_protected_specialization
***********************************************************************/

class os_reference_protected_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string (const os_class_type&) const;
  };


/***********************************************************************
  class os_reference_protected_local_specialization
***********************************************************************/

class os_reference_protected_local_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };


/***********************************************************************
  class os_soft_pointer32_specialization
***********************************************************************/

class os_soft_pointer32_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string (const os_class_type&) const;
  };


/***********************************************************************
  class os_soft_pointer64_specialization
***********************************************************************/

class os_soft_pointer64_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string (const os_class_type&) const;
  };


/***********************************************************************
  class os_Reference_this_DB_specialization
***********************************************************************/

class os_Reference_this_DB_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };


/***********************************************************************
  class os_Reference_specialization
***********************************************************************/

class os_Reference_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };


/***********************************************************************
  class os_Reference_local_specialization
***********************************************************************/

class os_Reference_local_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };


/***********************************************************************
  class os_Reference_protected_specialization
***********************************************************************/

class os_Reference_protected_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };


/***********************************************************************
  class os_Reference_protected_local_specialization
***********************************************************************/

class os_Reference_protected_local_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
  };




#endif /* REF_SPC_HH */
