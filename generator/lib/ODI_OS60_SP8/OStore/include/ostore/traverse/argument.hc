/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ARGUMENTS_HC
#define ARGUMENTS_HC

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

#include <assert.h>
#include <iostream.h>
#include <ostore/traverse/argument.hh>
#include <ostore/tix.hh>
#include <ostore/except.hh>

/*
 Pulled from libmisc to allow emitted loader to be compiled.
 Is there some way to throw a tix from client code?
*/

#define _LI_libmisc_err_0001_0239 117387517

/***********************************************************************
  class os_Argument_pt<Type>
***********************************************************************/

template<class Type>
os_Argument_pt<Type>::os_Argument_pt (os_Arguments& given_arguments, 
				      const char* given_value_name, 
				      const char* given_description, 
				      Type& given_value_storage)
    : os_Argument(given_arguments, given_value_name, given_description, this->_FALSE)
{
  this->value_storage = &given_value_storage;
}


template<class Type>
os_Argument_pt<Type>::os_Argument_pt (os_Arguments& given_arguments, 
				      const char* given_value_name, 
				      const char* given_description, 
				      Type& given_value_storage,
				      Boolean given_is_hidden)
    : os_Argument(given_arguments, given_value_name, given_description,
		  given_is_hidden)
{
  value_storage = &given_value_storage;
}


template<class Type>
os_Argument_pt<Type>::os_Argument_pt ()
{
  value_storage = 0;
}


template<class Type>
os_Argument_pt<Type>::~os_Argument_pt ()
{
  value_storage = 0;
}


template<class Type>
Type& os_Argument_pt<Type>::get_value_storage () const
{
  return *value_storage;
}


template<class Type>
void os_Argument_pt<Type>::bind (const char* actual_argument,
				 os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  bind(actual_argument, *value_storage, has_error);
  if ( ! has_error)
      set_is_bound(this->_TRUE);
}


template<class Type>
void os_Argument_pt<Type>::bind (const char* actual_argument,
				 Type& given_value_storage,
				 os_Argument::Boolean& has_error)
{
  set(given_value_storage, actual_argument, has_error);
}


template<class Type>
void os_Argument_pt<Type>::display () const
{
  os_Argument::display();
  cout << "    value_storage = " << (void*)value_storage;
}


template<class Type>
void os_Argument_pt<Type>::display_values () const
{
  if (value_storage)
      cout << get_string(*value_storage);
}


template<class Type>
void os_Argument_pt<Type>::set (Type& storage, const char* value_string,
				Boolean& has_error)
{
  os_Argument::set(storage, value_string, has_error);
}


template<class Type>
const char* os_Argument_pt<Type>::get_string (Type value) const
{
  return os_Argument::get_string(value);
}


/***********************************************************************
  class os_Argument_positional<Type>
***********************************************************************/

template<class Type>
os_Argument_positional<Type>::os_Argument_positional
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage)
{
  position = 0;
}


template<class Type>
os_Argument_positional<Type>::os_Argument_positional
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     os_Argument::Boolean given_is_hidden)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage, given_is_hidden)
{
  position = 0;
}


template<class Type>
os_Argument_positional<Type>::os_Argument_positional ()
{
  position = 0;
}


template<class Type>
os_Argument_positional<Type>::~os_Argument_positional ()
{
  position = 0;
}


template<class Type>
os_Argument::Kind os_Argument_positional<Type>::get_kind () const
{
  return this->positional;
}


template<class Type>
os_Argument::Boolean os_Argument_positional<Type>::has_position () const
{
  return this->_TRUE;
}


template<class Type>
os_Argument::Boolean os_Argument_positional<Type>::is_match 
    (unsigned given_position, const char* /*actual_argument*/,
     os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  if (this->is_bound())
      return this->_FALSE;
  else if (position != given_position)
      this->matched = this->_FALSE;
  else
      this->matched = this->_TRUE;
  return this->matched;
}


template<class Type>
os_Argument::Boolean os_Argument_positional<Type>::is_valid () const
{
  return os_Argument::Boolean(this->is_matched() && this->is_bound());
}


template<class Type>
os_Argument::Boolean os_Argument_positional<Type>::is_required () const
{
  return os_Argument::Boolean( ! this->is_hidden());
}


template<class Type>
void os_Argument_positional<Type>::set_position (unsigned given_position)
{
  position = given_position;
}


template<class Type>
void os_Argument_positional<Type>::display () const
{
  os_Argument_pt<Type>::display();
  if (this->value_storage) {
      cout << " (";
      this->display_values();
      cout << ')';
    }
  cout << endl;
  cout << "    position = " << position << endl;
}


/***********************************************************************
  class os_Argument_keyword<Type>
***********************************************************************/

template<class Type>
os_Argument_keyword<Type>::os_Argument_keyword
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword, Type given_initial_value,
     Type given_applied_value)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage)
{
  keyword_1 = given_keyword;
  keyword_2 = 0;
  initial_value = given_initial_value;
  applied_value = given_applied_value;
  *(this->value_storage) = initial_value;
  required = this->_FALSE;
}


template<class Type>
os_Argument_keyword<Type>::os_Argument_keyword
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword_1, const char* given_keyword_2, 
     Type given_initial_value, Type given_applied_value,
     os_Argument::Boolean given_is_hidden, 
     os_Argument::Boolean given_is_required)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage, given_is_hidden)
{
  keyword_1 = given_keyword_1;
  keyword_2 = given_keyword_2;
  initial_value = given_initial_value;
  applied_value = given_applied_value;
  *(this->value_storage) = initial_value;
  required = given_is_required;
}


template<class Type>
os_Argument_keyword<Type>::os_Argument_keyword ()
{
  keyword_1 = 0;
  keyword_2 = 0;
  initial_value = Type(0);
  applied_value = Type(0);
  required = this->_FALSE;
}


template<class Type>
os_Argument_keyword<Type>::~os_Argument_keyword ()
{
  keyword_1 = 0;
  keyword_2 = 0;
  initial_value = Type(0);
  applied_value = Type(0);
  required = this->_FALSE;
}


template<class Type>
os_Argument::Kind os_Argument_keyword<Type>::get_kind () const
{
  return os_Argument::keyword;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword<Type>::has_position () const
{
  return this->_FALSE;
}


template<class Type>
const char* os_Argument_keyword<Type>::usage () const
{
  static char buffer[64];
  if (keyword_1 && keyword_2)
      sprintf(buffer, "(%s|%s)", keyword_1, keyword_2);
  else if (keyword_1)
      sprintf(buffer, "%s", keyword_1);
  else if (keyword_2)
      sprintf(buffer, "%s", keyword_2);
  else
      /* TBD: better error report (though this should never happen). --rick@odi.com */
      assert(0);
  return buffer;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword<Type>::is_match 
    (unsigned /*given_position*/, const char* actual_argument,
     os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  if (this->is_bound())
      this->matched = this->_FALSE;
  else if (keyword_1 && keyword_2 
	   && (strcmp(keyword_1, actual_argument) == 0
	       || strcmp(keyword_2, actual_argument) == 0))
      this->matched = this->_TRUE;
  else if (keyword_1 && strcmp(keyword_1, actual_argument) == 0)
      this->matched = this->_TRUE;
  else if (keyword_2 && strcmp(keyword_2, actual_argument) == 0)
      this->matched = this->_TRUE;
  else
      this->matched = this->_FALSE;
  return this->matched;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword<Type>::is_valid () const
{
  if (is_required()) {
      if (this->is_matched() && this->is_bound())
	  return this->_TRUE;
      else
	  return this->_FALSE;
    }
  else {
      if ( ! this->is_matched())
	  return this->_TRUE;
      else if (this->is_bound())
	  return this->_TRUE;
      else
	  return this->_FALSE;
    }
}


template<class Type>
os_Argument::Boolean os_Argument_keyword<Type>::is_required () const
{
  return required;
}


template<class Type>
void os_Argument_keyword<Type>::bind (const char* /*actual_argument*/,
				      os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  *(this->value_storage) = applied_value;
  set_is_bound(this->_TRUE);
}


template<class Type>
void os_Argument_keyword<Type>::bind (const char* actual_argument,
				      Type& given_value_storage,
				      os_Argument::Boolean& has_error)
{
  os_Argument_pt<Type>::bind(actual_argument, given_value_storage, has_error);
}


template<class Type>
void os_Argument_keyword<Type>::display () const
{
  os_Argument_pt<Type>::display();
  if (this->value_storage) {
      cout << " (";
      this->display_values();
      cout << ')';
    }
  cout << endl;
  cout << "    keyword_1 = " << (keyword_1 ? keyword_1 : "NULL") << endl
       << "    keyword_2 = " << (keyword_2 ? keyword_2 : "NULL") << endl
       << "    initial_value = " << get_string(initial_value) << endl
       << "    applied_value = " << get_string(applied_value) << endl
       << "    required = " << os_Argument::get_string(required) << endl;
}


/***********************************************************************
  class os_Argument_keyword_with_values<Type>
***********************************************************************/

template<class Type>
os_Argument_keyword_with_values<Type>::os_Argument_keyword_with_values
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword, Type given_initial_value, 
     unsigned& given_value_count, unsigned given_maximum_values, 
     unsigned given_expected_values)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage)
{
  keyword_1 = given_keyword;
  keyword_2 = 0;
  initial_value = given_initial_value;
  maximum_values = given_maximum_values;
  expected_values = given_expected_values;
  value_count = &given_value_count;
  *value_count = 0;
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = initial_value;
  value_count_for_one = 0;
  required = this->_FALSE;
}


template<class Type>
os_Argument_keyword_with_values<Type>::os_Argument_keyword_with_values
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword_1, const char* given_keyword_2, 
     Type given_initial_value, unsigned& given_value_count, 
     unsigned given_maximum_values, os_Argument::Boolean given_is_hidden,
     os_Argument::Boolean given_is_required, unsigned given_expected_values)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage, given_is_hidden)
{
  keyword_1 = given_keyword_1;
  keyword_2 = given_keyword_2;
  initial_value = given_initial_value;
  maximum_values = given_maximum_values;
  expected_values = given_expected_values;
  value_count = &given_value_count;
  *value_count = 0;
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = initial_value;
  value_count_for_one = 0;
  required = given_is_required;
}


template<class Type>
os_Argument_keyword_with_values<Type>::os_Argument_keyword_with_values
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword, Type given_initial_value)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage)
{
  keyword_1 = given_keyword;
  keyword_2 = 0;
  initial_value = given_initial_value;
  maximum_values = 1;
  expected_values = 1;
  value_count = &value_count_for_one;
  *value_count = 0;
  *(this->value_storage) = initial_value;
  required = this->_FALSE;
}


template<class Type>
os_Argument_keyword_with_values<Type>::os_Argument_keyword_with_values
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     const char* given_keyword_1, const char* given_keyword_2, 
     Type given_initial_value, os_Argument::Boolean given_is_hidden,
      os_Argument::Boolean given_is_required)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage, given_is_hidden)
{
  keyword_1 = given_keyword_1;
  keyword_2 = given_keyword_2;
  initial_value = given_initial_value;
  maximum_values = 1;
  expected_values = 1;
  value_count = &value_count_for_one;
  *value_count = 0;
  *(this->value_storage) = initial_value;
  required = given_is_required;
}


template<class Type>
os_Argument_keyword_with_values<Type>::os_Argument_keyword_with_values ()
{
  keyword_1 = 0;
  keyword_2 = 0;
  initial_value = Type(0);
  maximum_values = 0;
  expected_values = 0;
  value_count = 0;
  value_count_for_one = 0;
  required = this->_FALSE;
}


template<class Type>
os_Argument_keyword_with_values<Type>::~os_Argument_keyword_with_values ()
{
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = Type(0);
  keyword_1 = 0;
  keyword_2 = 0;
  initial_value = Type(0);
  maximum_values = 0;
  expected_values = 0;
  if (value_count)
      *value_count = 0;
  value_count = 0;
  value_count_for_one = 0;
  required = this->_FALSE;
}


template<class Type>
os_Argument::Kind os_Argument_keyword_with_values<Type>::get_kind () const
{
  return this->keyword_with_values;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword_with_values<Type>::has_position
  () const
{
  return this->_FALSE;
}


template<class Type>
const char* os_Argument_keyword_with_values<Type>::usage () const
{
  /* TBD: make sure string isn't too long */
  static char buffer[128];
  if (keyword_1 && keyword_2)
      sprintf(buffer, "(%s|%s) %s", keyword_1, keyword_2, this->value_name);
  else if (keyword_1)
      sprintf(buffer, "%s %s", keyword_1, this->value_name);
  else if (keyword_2)
      sprintf(buffer, "%s %s", keyword_2, this->value_name);
  else
      /* TBD: better error report (though this should never happen). --rick@odi.com */
      assert(0);
  return buffer;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword_with_values<Type>::is_match 
    (unsigned /*given_position*/, const char* actual_argument,
     os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  if (this->is_bound())
      this->matched = this->_FALSE;
  else if (keyword_1 && keyword_2 
	   && (strcmp(keyword_1, actual_argument) == 0
	       || strcmp(keyword_2, actual_argument) == 0))
      this->matched = this->_TRUE;
  else if (keyword_1 && strcmp(keyword_1, actual_argument) == 0)
      this->matched = this->_TRUE;
  else if (keyword_2 && strcmp(keyword_2, actual_argument) == 0)
      this->matched = this->_TRUE;
  else
      this->matched = this->_FALSE;
  return this->matched;
}


template<class Type>
os_Argument::Boolean os_Argument_keyword_with_values<Type>::is_valid () const
{
  if (is_required()) {
      if (this->is_matched() && this->is_bound()
	  && value_count && *value_count >= expected_values)
	  return this->_TRUE;
      else
	  return this->_FALSE;
    }
  else {
      if ( ! this->is_matched())
	  return this->_TRUE;
      else if (expected_values > 1
	       && ( ! value_count || *value_count < expected_values))
	  return this->_FALSE;
      else if (this->is_bound())
	  return this->_TRUE;
      else
	  return this->_FALSE;
    }
}


template<class Type>
os_Argument::Boolean os_Argument_keyword_with_values<Type>::is_required () const
{
  return required;
}


template<class Type>
void os_Argument_keyword_with_values<Type>::bind 
    (const char* /*actual_argument*/, Type& given_value_storage,
     os_Argument::Boolean& has_error)
{
  unsigned limit = maximum_values;
  if (expected_values) {
    if (expected_values > maximum_values) {	
      err_objectstore.signal(_ODI_arg2(_LI_libmisc_err_0001_0239, "Argument value is out of range")); 
    }
  }
  Type* storage;
  os_Arguments& args = this->get_arguments();
  for (*value_count = 0, storage = &given_value_storage; 
       args.more() && *value_count < limit;
       ++(*value_count), ++storage) {
      const char* given = args.get_next_given();
      if (args.is_keyword(given)) {
	  args.push_back_given();
	  break;
	}
      set(*storage, given, has_error);
    }
  if (*value_count > maximum_values) {
      err_objectstore.signal(_ODI_arg2(_LI_libmisc_err_0001_0239, "Argument value is out of range")); 
    }
}


template<class Type>
void os_Argument_keyword_with_values<Type>::bind 
    (const char* actual_argument, os_Argument::Boolean& has_error)
{
  os_Argument_pt<Type>::bind(actual_argument, has_error);
}


template<class Type>
void os_Argument_keyword_with_values<Type>::display () const
{
  os_Argument_pt<Type>::display();
  if (this->value_storage)
      display_values();
  cout << endl;
  cout << "    keyword_1 = " << (keyword_1 ? keyword_1 : "NULL") << endl
       << "    keyword_2 = " << (keyword_2 ? keyword_2 : "NULL") << endl
       << "    initial_value = " << get_string(initial_value) << endl
       << "    maximum_values = " << maximum_values << endl
       << "    expected_values = " << expected_values << endl
       << "    required = " << required << endl
       << "    value_count = " << value_count;
  if (value_count)
      cout << " (" << *value_count << ')';
  cout << endl;
}


template<class Type>
void os_Argument_keyword_with_values<Type>::display_values () const
{
  if (this->value_storage) {
      unsigned limit = (value_count && *value_count ? *value_count : 0);
      if (limit > maximum_values)
	  limit = maximum_values;
      if (limit < expected_values)
	  limit = expected_values;
      cout << " ( ";
      Type* storage = this->value_storage;
      for (unsigned index = 0; index < limit; ++index)
	  cout << get_string(storage[index]) << ' ';
      cout << ')';
    }
}


/***********************************************************************
  class os_Argument_optional<Type>
***********************************************************************/

template<class Type>
os_Argument_optional<Type>::os_Argument_optional
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage)
    : os_Argument_positional<Type>(given_arguments, given_value_name, 
				   given_description, given_value_storage)
{}


template<class Type>
os_Argument_optional<Type>::os_Argument_optional
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     os_Argument::Boolean given_is_hidden)
    : os_Argument_positional<Type>(given_arguments, given_value_name, 
				   given_description, given_value_storage,
				   given_is_hidden)
{}


template<class Type>
os_Argument_optional<Type>::os_Argument_optional ()
{}


template<class Type>
os_Argument_optional<Type>::~os_Argument_optional ()
{}


template<class Type>
os_Argument::Kind os_Argument_optional<Type>::get_kind () const
{
  return this->optional;
}


template<class Type>
os_Argument::Boolean os_Argument_optional<Type>::is_valid () const
{
  if ( ! this->is_matched())
      return this->_TRUE;
  else if (this->is_bound())
      return this->_TRUE;
  else
      return this->_FALSE;
}


template<class Type>
os_Argument::Boolean os_Argument_optional<Type>::is_required () const
{
  return os_Argument::_FALSE;
}


/***********************************************************************
  class os_Argument_always<Type>
***********************************************************************/

template<class Type>
os_Argument_always<Type>::os_Argument_always
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     Type given_initial_value, unsigned& given_value_count,
     unsigned given_maximum_values, unsigned given_expected_values)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage)
{
  initial_value = given_initial_value;
  maximum_values = given_maximum_values;
  expected_values = given_expected_values;
  value_count = &given_value_count;
  *value_count = 0;
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = initial_value;
  value_count_for_one = 0;
}


template<class Type>
os_Argument_always<Type>::os_Argument_always
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     Type given_initial_value, unsigned& given_value_count,
     unsigned given_maximum_values, os_Argument::Boolean given_is_hidden,
     unsigned given_expected_values)
    : os_Argument_pt<Type>(given_arguments, given_value_name, 
			   given_description, given_value_storage, given_is_hidden)
{
  initial_value = given_initial_value;
  maximum_values = given_maximum_values;
  expected_values = given_expected_values;
  value_count = &given_value_count;
  *value_count = 0;
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = initial_value;
  value_count_for_one = 0;
}


template<class Type>
os_Argument_always<Type>::os_Argument_always
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     Type given_initial_value)
    : os_Argument_pt<Type>(given_arguments, given_value_name,
			   given_description, given_value_storage)
{
  initial_value = given_initial_value;
  maximum_values = 1;
  expected_values = 1;
  value_count = &value_count_for_one;
  *value_count = 0;
  *(this->value_storage) = initial_value;
}


template<class Type>
os_Argument_always<Type>::os_Argument_always
    (os_Arguments& given_arguments, const char* given_value_name, 
     const char* given_description, Type& given_value_storage,
     Type given_initial_value, os_Argument::Boolean given_is_hidden)
    : os_Argument_pt<Type>(given_arguments, given_value_name,
			   given_description, given_value_storage, given_is_hidden)
{
  initial_value = given_initial_value;
  maximum_values = 1;
  expected_values = 1;
  value_count = &value_count_for_one;
  *value_count = 0;
  *(this->value_storage) = initial_value;
}


template<class Type>
os_Argument_always<Type>::os_Argument_always ()
{
  initial_value = Type(0);
  maximum_values = 0;
  expected_values = 0;
  value_count = 0;
  value_count_for_one = 0;
}


template<class Type>
os_Argument_always<Type>::~os_Argument_always ()
{
  for (unsigned index = 0; index < maximum_values; ++index)
      this->value_storage[index] = Type(0);
  initial_value = Type(0);
  maximum_values = 0;
  expected_values = 0;
  if (value_count)
      *value_count = 0;
  value_count = 0;
  value_count_for_one = 0;
}


template<class Type>
os_Argument::Kind os_Argument_always<Type>::get_kind () const
{
  return this->always;
}


template<class Type>
os_Argument::Boolean os_Argument_always<Type>::has_position () const
{
  return this->_FALSE;
}


template<class Type>
os_Argument::Boolean os_Argument_always<Type>::is_match 
    (unsigned /*given_position*/, const char* /*actual_argument*/,
     os_Argument::Boolean& has_error)
{
  has_error = this->_FALSE;
  this->matched = this->_TRUE;
  return this->matched;
}


template<class Type>
os_Argument::Boolean os_Argument_always<Type>::is_valid () const
{
  if (expected_values > 1
      && ( ! value_count || *value_count < expected_values))
      return this->_FALSE;
  else
      return this->is_bound();
}


template<class Type>
os_Argument::Boolean os_Argument_always<Type>::is_required () const
{
  return os_Argument::Boolean( ! this->is_hidden());
}


template<class Type>
void os_Argument_always<Type>::bind 
    (const char* actual_argument, Type& given_value_storage,
     os_Argument::Boolean& has_error)
{
  unsigned limit = maximum_values;
  if (expected_values) {
      if (expected_values > maximum_values) {
        err_objectstore.signal(_ODI_arg2(_LI_libmisc_err_0001_0239, "Argument value is out of range")); 
      }
    }
  if (*value_count == limit) {
        err_objectstore.signal(_ODI_arg2(_LI_libmisc_err_0001_0239, "Too many arguments given")); 
  }
  Type* storage = &(&given_value_storage)[*value_count];
  const char* given = actual_argument;
  set(*storage, given, has_error);
  ++(*value_count);
}


template<class Type>
void os_Argument_always<Type>::bind 
    (const char* actual_argument, os_Argument::Boolean& has_error)
{
  os_Argument_pt<Type>::bind(actual_argument, has_error);
}


template<class Type>
void os_Argument_always<Type>::display () const
{
  os_Argument_pt<Type>::display();
  if (this->value_storage)
      display_values();
  cout << endl;
  cout << "    initial_value = " << get_string(initial_value) << endl
       << "    maximum_values = " << maximum_values << endl
       << "    expected_values = " << expected_values << endl
       << "    value_count = " << value_count;
  if (value_count)
      cout << " (" << *value_count << ')';
  cout << endl;
}


template<class Type>
void os_Argument_always<Type>::display_values () const
{
  if (this->value_storage) {
      unsigned limit = (value_count && *value_count ? *value_count : 0);
      if (limit > maximum_values)
	  limit = maximum_values;
      if (limit < expected_values)
	  limit = expected_values;
      cout << " ( ";
      Type* storage = this->value_storage;
      for (unsigned index = 0; index < limit; ++index)
	  cout << get_string(storage[index]) << ' ';
      cout << ')';
    }
}


#endif /* ARGUMENTS_HC */

