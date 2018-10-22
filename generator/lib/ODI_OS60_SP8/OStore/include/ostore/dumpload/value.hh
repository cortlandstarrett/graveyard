/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef VALUE_HH
#define VALUE_HH

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


/***********************************************************************
  Includes
***********************************************************************/

#include <ostore/ostore.hh>
#include <ostore/traverse/boolean.hh>

/***********************************************************************
  Declarations
***********************************************************************/


/***********************************************************************
  class os_Input_value_t
***********************************************************************/

class os_Input_value_t {

  public: // Subtypes
    /* The Boolean type is necessary so that an overloading distinction
       can be made between Boolean types and integrals. */
    enum Boolean { _FALSE = os_Bool::_FALSE, _TRUE = os_Bool::_TRUE };
    enum Kind { Void, Bool_v, Char, Short, Unsigned_short,
		Int, Unsigned, Long, Unsigned_long,
		Float, Double, String };

  public: // Construction
    os_Input_value_t ();
    virtual ~os_Input_value_t ();

  public: // Modifiers
    os_Input_value_t& operator , (os_Input_value_t&);
    os_Input_value_t& operator += (os_Input_value_t&);

  protected: // Embedded data
    os_Input_value_t* next;
    os_boolean bound;

  protected: // Accessors
    os_Input_value_t* get_next_value () const;
    os_boolean is_bound () const;
    os_boolean is_match (const char* string) const;
#ifdef _OS_HP_aCC
    virtual Kind get_kind () const;
#else
    virtual Kind get_kind () const = 0;
#endif
    static Kind get_kind (Boolean);
    static Kind get_kind (char);
    static Kind get_kind (short);
    static Kind get_kind (unsigned short);
    static Kind get_kind (int);
    static Kind get_kind (unsigned);
    static Kind get_kind (long);
    static Kind get_kind (unsigned long);
    static Kind get_kind (float);
    static Kind get_kind (double);
    static Kind get_kind (char*);
#ifdef _OS_HP_aCC
    virtual const char* get_kind_string () const;
#else
    virtual const char* get_kind_string () const = 0;
#endif
    static const char* get_kind_string (Boolean);
    static const char* get_kind_string (char);
    static const char* get_kind_string (short);
    static const char* get_kind_string (unsigned short);
    static const char* get_kind_string (int);
    static const char* get_kind_string (unsigned);
    static const char* get_kind_string (long);
    static const char* get_kind_string (unsigned long);
    static const char* get_kind_string (float);
    static const char* get_kind_string (double);
    static const char* get_kind_string (char*);

  protected: // Value Modifiers
    static void set (Boolean& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (char& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (short& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (unsigned short& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (int& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (unsigned& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (long& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (unsigned long& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (float& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (double& storage, 
		     const char* value_string,
		     os_boolean& has_error);
    static void set (char*& storage, 
		     const char* value_string,
		     os_boolean& has_error);

  protected: // Modifiers
    os_Input_value_t& append (os_Input_value_t&);
    void set_is_bound (os_boolean state); 

  protected: // Virtual Modifiers

#ifdef _OS_HP_aCC
    virtual void bind (const char* actual_value,
		       os_boolean& has_error);
#else
    virtual void bind (const char* actual_value,
		       os_boolean& has_error) = 0;
#endif

  protected: // Debugging
#ifdef _OS_HP_aCC
    virtual void display () const;
#else
    virtual void display () const = 0;
#endif
    static const char* get_string (Boolean);
    static const char* get_string (char);
    static const char* get_string (short);
    static const char* get_string (unsigned short);
    static const char* get_string (int);
    static const char* get_string (unsigned);
    static const char* get_string (long);
    static const char* get_string (unsigned long);
    static const char* get_string (float);
    static const char* get_string (double);
    static const char* get_string (const char*);

  private: // Friends
    friend class os_Input_values;

  };


/***********************************************************************
  class os_Input_value<Type>
***********************************************************************/

template<class Type> class os_Input_value : public os_Input_value_t {

  public: // Construction
    os_Input_value (Type& value_storage);
    os_Input_value (); // Do not use explicitly
    virtual ~os_Input_value ();

  protected: // Embedded data
    Type* value_storage;

  protected: // Accessors
    Type& get_value_storage () const;
    Kind get_kind () const;
    const char* get_kind_string () const;

  protected: // Virtual Modifiers
    virtual void bind (const char* actual_value,
		       os_boolean& has_error);
    virtual void bind (const char* actual_value,
		       Type& value_storage,
		       os_boolean& has_error);

  protected: // Debugging
    virtual void display () const;

  private: // Friends
    friend class os_Input_values;

  };


/***********************************************************************
  class os_Input_values
***********************************************************************/

class os_Input_values {

  public: // Construction

    os_Input_values (const char* format, os_Input_value_t&);
    virtual ~os_Input_values ();

  public: // Modifiers
    virtual void bind (istream& stream);
    virtual void bind (const char* string);

  protected: // Embedded data
    const char* format;
    os_Input_value_t* values;

  protected: // Accessors
    const char* get_format () const;
    os_Input_value_t& get_values () const;
    os_boolean is_format_argument (const char* format_pattern,
				   const char* sub_format) const;

  protected: // Debugging
    virtual void display () const;

  };


#endif /* VALUE_HH */



