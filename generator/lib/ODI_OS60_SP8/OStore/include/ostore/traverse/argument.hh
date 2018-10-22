/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ARGUMENTS_HH
#define ARGUMENTS_HH

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
  Defines
************************************************************************/

#if defined(_OS_HP_aCC)
#define _CLASS class
#else
#define _CLASS
#endif


/***********************************************************************
  Includes
***********************************************************************/
#include <ostore/traverse/boolean.hh>

/***********************************************************************
  Declarations
***********************************************************************/

class os_Arguments;

/***********************************************************************
  class os_Argument
***********************************************************************/


class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument {

  public: // Subtypes
    /* The Boolean type is necessary so that an overloading distinction
       can be made between Boolean types and integrals. */
    enum Boolean { _FALSE = os_Bool::_FALSE, _TRUE = os_Bool::_TRUE };
    enum Kind { no_argument, positional, keyword, keyword_with_values,
                optional, always };

  public: // Modifiers
    os_Argument& operator , (os_Argument&);
    os_Argument& operator += (os_Argument&);

  protected: // Embedded data
    os_Arguments* arguments;
    os_Argument* next;
    const char* value_name;
    const char* description;
    Boolean matched;
    Boolean bound;
    Boolean hidden;

  protected: // Construction
    os_Argument (os_Arguments&, const char* value_name, 
                 const char* description, Boolean is_hidden);
    os_Argument (); // Don't use this.
    virtual ~os_Argument ();

  protected: // Accessors
    os_Arguments& get_arguments () const;
    os_Argument* get_next_argument () const;
    const char* get_value_name () const;
    const char* get_description () const;
    Boolean is_matched () const;
    Boolean is_bound () const;
    Boolean is_optional () const;
    Boolean is_hidden () const;

  protected: // Virtual Accessors
    virtual const char* usage () const;
    virtual os_Argument::Kind get_kind () const = 0;
    virtual Boolean has_position () const = 0;
    virtual Boolean is_match (unsigned position, 
                              const char* actual_argument,
                              Boolean& has_error) = 0;
    virtual Boolean is_valid () const = 0;
    virtual Boolean is_required () const = 0;

  protected: // Value Modifiers
    static void set (Boolean& storage, const char* value_string,
                     Boolean& has_error);
    static void set (char& storage, const char* value_string,
                     Boolean& has_error);
    static void set (short& storage, const char* value_string,
                     Boolean& has_error);
    static void set (unsigned short& storage, const char* value_string,
                     Boolean& has_error);
    static void set (int& storage, const char* value_string,
                     Boolean& has_error);
    static void set (unsigned& storage, const char* value_string,
                     Boolean& has_error);
    static void set (long& storage, const char* value_string,
                     Boolean& has_error);
    static void set (unsigned long& storage, const char* value_string,
                     Boolean& has_error);
    static void set (const char*& storage, const char* value_string,
                     Boolean& has_error);
    static void set (char*& storage, const char* value_string,
                     Boolean& has_error);
    static void set (float& storage, const char* value_string,
                     Boolean& has_error);
    static void set (double& storage, const char* value_string,
                     Boolean& has_error);

  protected: // Modifiers
    void set_is_bound (Boolean);
    os_Argument& append (os_Argument&);

  protected: // Virtual Modifiers
    virtual void set_position (unsigned position);
    virtual void bind (const char* actual_argument,
                       Boolean& has_error) = 0;

  protected: // Debugging
    virtual void display () const;
    virtual void display_values () const = 0;
    static const char* get_string (os_Argument::Boolean);
    static const char* get_string (char);
    static const char* get_string (short);
    static const char* get_string (unsigned short);
    static const char* get_string (int);
    static const char* get_string (unsigned);
    static const char* get_string (long);
    static const char* get_string (unsigned long);
    static const char* get_string (const char*);
    static const char* get_string (char*);
    static const char* get_string (float);
    static const char* get_string (double);

  protected: // Friends
    friend class os_Arguments;

  };


/***********************************************************************
  class os_Argument_pt<Type>
***********************************************************************/

template<class Type> class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_pt : public os_Argument {

  protected: // Embedded data
    Type* value_storage;

  protected: // Construction
    os_Argument_pt (os_Arguments&, const char* value_name, 
                    const char* description, Type& value_storage);
    os_Argument_pt (os_Arguments&, const char* value_name, 
                    const char* description, Type& value_storage,
                    Boolean is_hidden);
    os_Argument_pt (); // Don't use this
    virtual ~os_Argument_pt ();

  protected: // Accessors
    Type& get_value_storage () const;

  protected: // Modifiers
    void set (Type& storage, const char* value_string, Boolean& has_error);

  protected: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       Boolean& has_error);
    virtual void bind (const char* actual_argument,
                       Type& value_storage,
                       Boolean& has_error);

  protected: // Debugging
    virtual void display () const;
    virtual void display_values () const;
    const char* get_string (Type) const;

  protected: // Friends
    friend class os_Arguments;

  };


/***********************************************************************
  class os_Argument_positional<Type>
***********************************************************************/

template<class Type> 
class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_positional : public os_Argument_pt<Type> {

  public: // Construction
    os_Argument_positional (os_Arguments&, const char* value_name, 
                            const char* description, Type& value_storage);
    os_Argument_positional (os_Arguments&, const char* value_name, 
                            const char* description, Type& value_storage,
                            os_Argument::Boolean is_hidden);
    os_Argument_positional (); // Don't use this
    virtual ~os_Argument_positional ();

  protected: // Embedded data
    unsigned position;

  protected: // Accessors
    virtual os_Argument::Kind get_kind () const;
    virtual os_Argument::Boolean has_position () const;
    virtual os_Argument::Boolean is_match (unsigned position, 
                              const char* actual_argument,
                              os_Argument::Boolean& has_error);
    virtual os_Argument::Boolean is_valid () const;
    virtual os_Argument::Boolean is_required () const;

  protected: // Modifier
    void set_position (unsigned position);

  protected: // Debugging
    virtual void display () const;

  protected: // Friends
    friend class os_Arguments;

  };



/***********************************************************************
  class os_Argument_keyword
***********************************************************************/

template<class Type>
class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_keyword : public os_Argument_pt<Type> {

  public: // Construction
    os_Argument_keyword (os_Arguments&, const char* value_name, 
                         const char* description, Type& value_storage, 
                         const char* keyword, Type initial_value, 
                         Type applied_value);
    os_Argument_keyword (os_Arguments&, const char* value_name, 
                         const char* description, Type& value_storage, 
                         const char* keyword_1, const char* keyword_2, 
                         Type initial_value, Type applied_value, 
			 os_Argument::Boolean is_hidden,
                         os_Argument::Boolean is_required);
    os_Argument_keyword (); // Don't use this
    virtual ~os_Argument_keyword ();

  protected: // Embedded data
    const char* keyword_1;
    const char* keyword_2;
    Type initial_value;
    Type applied_value;
    os_Argument::Boolean required;

  protected: // Virtual Accessors
    virtual os_Argument::Kind get_kind () const;
    virtual os_Argument::Boolean has_position () const;
    virtual const char* usage () const;
    virtual os_Argument::Boolean is_match (unsigned position, 
                              const char* actual_argument,
                              os_Argument::Boolean& has_error);
    virtual os_Argument::Boolean is_valid () const;
    virtual os_Argument::Boolean is_required () const;

  protected: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       os_Argument::Boolean& has_error);

  protected: // Debugging
    virtual void display () const;

  private: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       Type& value_storage,
                       os_Argument::Boolean& has_error);

  private: // Friends
    friend class os_Arguments;

  };

/***********************************************************************
  class os_Argument_keyword_with_values
***********************************************************************/

template<class Type> 
class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_keyword_with_values : public os_Argument_pt<Type> {

  public: // Construction
    os_Argument_keyword_with_values (os_Arguments&, 
                                     const char* value_name, 
                                     const char* description, 
                                     Type& value_storage,
                                     const char* keyword, 
                                     Type initial_value,
                                     unsigned& value_count,
                                     unsigned maximum_values,
                                     unsigned expected_values = 0);
    os_Argument_keyword_with_values (os_Arguments&, 
                                     const char* value_name, 
                                     const char* description, 
                                     Type& value_storage,
                                     const char* keyword_1, 
                                     const char* keyword_2, 
                                     Type initial_value,
                                     unsigned& value_count,
                                     unsigned maximum_values,
                                     os_Argument::Boolean is_hidden,
                                     os_Argument::Boolean is_required,
                                     unsigned expected_values = 0);
    os_Argument_keyword_with_values (os_Arguments&, 
                                     const char* value_name, 
                                     const char* description, 
                                     Type& value_storage,
                                     const char* keyword, 
                                     Type initial_value);
    os_Argument_keyword_with_values (os_Arguments&, 
                                     const char* value_name, 
                                     const char* description, 
                                     Type& value_storage,
                                     const char* keyword_1, 
                                     const char* keyword_2, 
                                     Type initial_value,
                                     os_Argument::Boolean is_hidden,
                                     os_Argument::Boolean is_required);
    os_Argument_keyword_with_values (); // Don't use this
    virtual ~os_Argument_keyword_with_values ();

  public: // Virtual Accessors
    virtual os_Argument::Kind get_kind () const;
    virtual os_Argument::Boolean has_position () const;
    virtual const char* usage () const;
    virtual os_Argument::Boolean is_match (unsigned position, 
                              const char* actual_argument,
                              os_Argument::Boolean& has_error);
    virtual os_Argument::Boolean is_valid () const;
    virtual os_Argument::Boolean is_required () const;

  public: // Virtual Modifiers
    virtual void bind (const char* actual_argument, 
                       Type& value_storage, os_Argument::Boolean& has_error);

  protected: // Embedded data
    const char* keyword_1;
    const char* keyword_2;
    Type initial_value;
    unsigned maximum_values;
    unsigned expected_values;
    unsigned* value_count;
    unsigned value_count_for_one;
    os_Argument::Boolean required;

  protected: // Debugging
    virtual void display () const;
    virtual void display_values () const;

  private: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       os_Argument::Boolean& has_error);

  private: // Friends
    friend class os_Arguments;

  };

/***********************************************************************
  class os_Argument_optional
***********************************************************************/

template<class Type> 
class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_optional : public os_Argument_positional<Type> {

  public: // Construction
    os_Argument_optional (os_Arguments&, const char* value_name, 
                          const char* description, Type& value_storage);
    os_Argument_optional (os_Arguments&, const char* value_name, 
                          const char* description, Type& value_storage,
                          os_Argument::Boolean is_hidden);
    os_Argument_optional (); // Don't use this
    virtual ~os_Argument_optional ();

  protected: // Virtual Accessors
    virtual os_Argument::Kind get_kind () const;
    virtual os_Argument::Boolean is_valid () const;
    virtual os_Argument::Boolean is_required () const;

  protected: // Friends
    friend class os_Arguments;

  };

/***********************************************************************
  class os_Argument_always
***********************************************************************/

template<class Type> class _OS_DLLIMPORT(_OS_TRAVERSE) os_Argument_always : public os_Argument_pt<Type> {

  public: // Construction
    os_Argument_always (os_Arguments&, 
                        const char* value_name, 
                        const char* description, 
                        Type& value_storage,
                        Type initial_value,
                        unsigned& value_count,
                        unsigned maximum_values,
                        unsigned expected_values = 0);
    os_Argument_always (os_Arguments&, 
                        const char* value_name, 
                        const char* description, 
                        Type& value_storage,
                        Type initial_value,
                        unsigned& value_count,
                        unsigned maximum_values,
                        os_Argument::Boolean is_hidden,
                        unsigned expected_values = 0);
    os_Argument_always (os_Arguments&, 
                        const char* value_name, 
                        const char* description, 
                        Type& value_storage,
                        Type initial_value);
    os_Argument_always (os_Arguments&, 
                        const char* value_name, 
                        const char* description, 
                        Type& value_storage,
                        Type initial_value,
                        os_Argument::Boolean is_hidden);
    os_Argument_always (); // Don't use this
    virtual ~os_Argument_always ();

  public: // Virtual Accessors
    virtual os_Argument::Kind get_kind () const;
    virtual os_Argument::Boolean has_position () const;
    virtual os_Argument::Boolean is_match (unsigned position, 
                              const char* actual_argument,
                              os_Argument::Boolean& has_error);
    virtual os_Argument::Boolean is_valid () const;
    virtual os_Argument::Boolean is_required () const;

  public: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       Type& value_storage, os_Argument::Boolean& has_error);

  protected: // Embedded data
    Type initial_value;
    unsigned maximum_values;
    unsigned expected_values;
    unsigned* value_count;
    unsigned value_count_for_one;

  protected: // Debugging
    virtual void display () const;
    virtual void display_values () const;

  private: // Virtual Modifiers
    virtual void bind (const char* actual_argument,
                       os_Argument::Boolean& has_error);

  protected: // Friends
    friend class os_Arguments;

  };


/***********************************************************************
  class os_Arguments
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Arguments {

  public: // Construction
    os_Arguments (int argc, char* argv[]);
    virtual ~os_Arguments ();

  public: // Accessors
    void usage ();
    os_Argument::Boolean more () const;
    os_Argument::Boolean is_keyword (const char* string) const;

  public: // Modifiers
    const char* get_next_given ();
    void push_back_given ();
    void bind ();

  public: // Embedded data
    int argc;
    char** argv;
    int index;
    os_Argument::Boolean verbose;
    int debugging;
    os_Argument::Boolean indirects;
    os_Argument* arguments;

  protected: // Accessors
    os_Argument::Boolean is_exposing () const;

  };


#endif /* ARGUMENTS_HH */



