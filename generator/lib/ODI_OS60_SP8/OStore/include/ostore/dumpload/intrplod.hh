/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef INTRPLOD_HH
#define INTRPLOD_HH

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


/***********************************************************************
  class os_Embedded_loader
***********************************************************************/

class os_Embedded_loader {
  public: // Construction
    os_Embedded_loader (os_Type_loader& type_loader, os_unsigned_int32 data_offset);
    ~os_Embedded_loader ();
  public: // Actions
    virtual void operator () (os_Loader_stream& stream, os_Type_data& data,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_Type_loader* type_loader;
    os_unsigned_int32 data_offset;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_array_loader
***********************************************************************/

class os_Embedded_array_loader : public os_Embedded_loader {
  public: // Construction
    os_Embedded_array_loader (os_Type_loader& type_loader,
                              os_unsigned_int32 data_offset,
                              os_unsigned_int32 data_size,
                              os_unsigned_int32 number_elements);
    ~os_Embedded_array_loader ();
  public: // Actions
    virtual void operator () (os_Loader_stream& stream, os_Type_data& data,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_unsigned_int32 data_size;
    os_unsigned_int32 number_elements;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_constructor
***********************************************************************/

class os_Embedded_constructor {
  public: // Construction
    os_Embedded_constructor (os_Type_loader& type_loader, 
                             os_unsigned_int32 object_offset,
                             os_unsigned_int32 data_offset);
    ~os_Embedded_constructor ();
  public: // Actions
    virtual void operator () (os_Type_data&, void* object,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_Type_loader* type_loader;
    os_unsigned_int32 object_offset;
    os_unsigned_int32 data_offset;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_array_constructor
***********************************************************************/

class os_Embedded_array_constructor : public os_Embedded_constructor {
  public: // Construction
    os_Embedded_array_constructor (os_Type_loader& type_loader, 
                                   os_unsigned_int32 object_offset,
                                   os_unsigned_int32 data_offset,
                                   os_unsigned_int32 data_size,
                                   os_unsigned_int32 object_size,
                                   os_unsigned_int32 number_elements);
    ~os_Embedded_array_constructor ();
  public: // Actions
    virtual void operator () (os_Type_data&, void* object,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_unsigned_int32 data_size;
    os_unsigned_int32 object_size;
    os_unsigned_int32 number_elements;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_field_constructor
***********************************************************************/

class os_Embedded_field_constructor : public os_Embedded_constructor {
  public: // Construction
    os_Embedded_field_constructor (
       os_Type_loader&   given_type_loader,
       os_unsigned_int32 given_object_offset_bytes,
       os_unsigned_int8  given_object_offset_bits,
       os_unsigned_int32 given_data_offset,
       os_unsigned_int32 given_data_size,
       os_unsigned_int8  given_object_size);
    ~os_Embedded_field_constructor ();
  public: // Actions
    virtual void operator () (os_Type_data&, void* object,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_unsigned_int32 data_size;
    os_unsigned_int8  object_size;
    os_unsigned_int8  object_offset_bits;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_fixup
***********************************************************************/

class os_Embedded_fixup {
  public: // Construction
    os_Embedded_fixup (os_Type_loader& type_loader, 
                       os_unsigned_int32 object_offset, os_unsigned_int32 data_offset);
    ~os_Embedded_fixup ();
  public: // Actions
    virtual void operator () (os_Type_data&, void* object,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_Type_loader* type_loader;
    os_unsigned_int32 object_offset;
    os_unsigned_int32 data_offset;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  class os_Embedded_array_fixup
***********************************************************************/

class os_Embedded_array_fixup : public os_Embedded_fixup {
  public: // Construction
    os_Embedded_array_fixup (os_Type_loader& type_loader, 
                             os_unsigned_int32 object_offset,
                             os_unsigned_int32 data_offset,
                             os_unsigned_int32 data_size,
                             os_unsigned_int32 object_size,
                             os_unsigned_int32 number_elements);
    ~os_Embedded_array_fixup ();
  public: // Actions
    virtual void operator () (os_Type_data&, void* object,
                              os_boolean is_most_derived_class);
  protected: // Embedded data
    os_unsigned_int32 data_size;
    os_unsigned_int32 object_size;
    os_unsigned_int32 number_elements;
  public: // Debugging
    virtual void show () const;
    virtual void show (ostream&) const;
  };


/***********************************************************************
  Interpretive loader parts
***********************************************************************/

typedef os_List<os_Embedded_loader*> os_Embedded_loaders;
typedef os_List<os_Embedded_constructor*> os_Embedded_constructors;
typedef os_List<os_Embedded_fixup*> os_Embedded_fixups;


/***********************************************************************
  class os_Interpretive_data
***********************************************************************/

class os_Interpretive_data : public os_Type_data {
  public: // Construction
    os_Interpretive_data (const os_type& value_type, const os_class_type& data_type);
    ~os_Interpretive_data ();
  public: // Accessors
    os_Type_data& get_actual_data ();
  protected: // Embedded data
    const os_type* value_type;
    const os_class_type* data_type;
    os_Type_data* data;
  protected: // Helpers
    os_Type_data* allocate_data (os_unsigned_int32 size,
                                 os_unsigned_int32 alignment);
  };


/***********************************************************************
  class os_Interpretive_info
***********************************************************************/

class os_Interpretive_info : public os_Type_info {
  public: // Construction
    os_Interpretive_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
                          os_Interpretive_data&);
    ~os_Interpretive_info ();
  public: // Accessors
    os_Type_data& get_actual_data ();
  public: // Modifiers
  protected: // Embedded data
    os_Interpretive_data* data;
  private: // Friends
    friend class os_Interpretive_loader;
  };


/***********************************************************************
  class os_Interpretive_loader
***********************************************************************/

class os_Interpretive_loader : public os_Type_loader {

  public: // Static Construction
    static os_Interpretive_loader& create
       (const os_class_type& class_type,const char* type_string);

  public: // Construction
    os_Interpretive_loader
       (const os_class_type& class_type,const char* type_string);
    ~os_Interpretive_loader ();

  public: // Actions

    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& previous_info);

    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Type_data& given_data,
                                    os_boolean is_most_derived_class);

    virtual void construct (os_Type_data& given_data, void* given_object, 
                            os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& given_data, void* given_object, 
                        os_boolean is_most_derived_class);
      
  protected: // Embedded data

    /* TBD: if necessary, make a special schema reference using the class name.
            --rick@odi.com */
    os_Reference_transient<const os_class_type> class_type;
    os_typespec* typespec;
    os_Embedded_loaders* embedded_loaders;
    os_Embedded_constructors* embedded_constructors;
    os_Embedded_fixups* embedded_fixups;
    char* name;

  protected: // Static Data
    static os_Registration_block<os_Type_loader*, os_Loader>* registration_block;
    static os_unsigned_int32 maximum_registration_entries;
    static os_unsigned_int32 block_number;

  protected: // Static Accessors
    static os_class_type* find_data_type (const char* data_name);
    static char* generate_data_name (const os_class_type&);
    static char* generate_data_name (const os_type&);
    static os_unsigned_int32 get_maximum_registration_entries ();
    static os_unsigned_int32 get_block_number ();
    static os_Traverser& get_traverser ();

  protected: // Static Modifiers
    static void insert_data_type (const os_class_type& data_type);
    static void register_loader (os_Interpretive_loader&);
    static os_Registration_block<os_Type_loader*, os_Loader>&
        construct_registration_block ();
    static os_unsigned_int32 increment_block_number ();

  protected: // Accessors
    const os_class_type& get_class_type () const;
    os_Embedded_loaders& get_embedded_loaders () const;
    os_Embedded_constructors& get_embedded_constructors () const;
    os_Embedded_fixups& get_embedded_fixups () const;

  protected: // Modifiers
    void generate_data ();
    void generate_embedded_loaders ();
    void generate_embedded_constructors ();
    void generate_embedded_fixups ();

  protected: // Actions
    virtual void create (os_Loader_info& given_info);

  public: // Debugging
    static os_boolean is_debugging (int level = 1);
    virtual void show () const;
    virtual void show (ostream&) const;
    virtual const char* get_name () const;
    virtual void show_data (ostream&) const;
    virtual void show_embedded_loaders (ostream&) const;
    virtual void show_embedded_constructors (ostream&) const;
    virtual void show_embedded_fixups (ostream&) const;

  private: // Friends
    friend class os_Interpretive_loader_generator;
    friend class os_Data_generator;
    friend class os_Embedded_loader_generator;
    friend class os_Embedded_constructor_generator;
    friend class os_Embedded_fixup_generator;

  };


#endif /* INTRPLOD_HH */
