/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REGISTER_HH
#define REGISTER_HH

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

//-- Forward Declarations ----------------------------------------------

template <class Value, class Context> class os_Registrations;


/***********************************************************************
  class os_Registration_entry
***********************************************************************/

template <class Value, class Context> class  _OS_DLLIMPORT(_OS_TRAVERSE)  os_Registration_entry {

  public: // Construction
    os_Registration_entry (const char* key, Value value);
    os_Registration_entry ();
    ~os_Registration_entry ();

  public: // Accessors
    const char* get_key () const;
    const char* get_string() const; 

    Value get_value () const;

  public: // Modifiers
    void set_context (Context&);
    void register_entry (Context&);

  public: // Debugging
    void dump () const;

  protected: // Embedded Data
    const char* key;
    Value value;

  public: // Instantiation
    static int _instantiate ();

  };


/***********************************************************************
  class os_Registration_block
***********************************************************************/

template <class Value, class Context> class _OS_DLLIMPORT(_OS_TRAVERSE)  os_Registration_block {

  public: // Construction
    os_Registration_block (os_Registration_entry<Value, Context>* entries,
			   unsigned number_entries, const char* file_name, 
			   unsigned line_number);
    ~os_Registration_block ();

  public: // Accessors
    const char* get_file_name () const;
    unsigned get_line_number () const;
    unsigned get_number_entries () const;
    os_Registration_entry<Value, Context>* get_entry (unsigned int index);

  public: // Modifiers
    unsigned increment_number_entries ();

  public: // Debugging
    void dump () const;

  protected: // Embedded Data
    os_Registration_block<Value, Context>* next_block;
    os_Registration_entry<Value, Context>* entries;
    unsigned number_entries;
    const char* file_name;
    unsigned line_number;

  protected: // Modifiers
    void register_entries (Context&);
    void add_block (os_Registration_block<Value, Context>& next_block);

  private: // Friends
    friend class os_Registrations<Value, Context>;

  public: // Instantiation
    static int _instantiate ();

  };



#define OS_NUMBER_REGISTRATIONS(ARRAY, ELEMENT_TYPE) \
        sizeof(ARRAY) / sizeof(ELEMENT_TYPE)


#endif /* REGISTER_HH */
