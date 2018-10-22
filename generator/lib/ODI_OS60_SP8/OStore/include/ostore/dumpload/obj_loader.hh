/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef OBJ_LOADER_HH
#define OBJ_LOADER_HH

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

#include "dmp_ref.hh"
#include "loader.hh"


//-- Forward Declarations ----------------------------------------------

class os_Type_data;


/***********************************************************************
  class os_Object_loader
***********************************************************************/

class os_Object_loader : public os_Loader_action {

  public: // Construction
    os_Object_loader ();
    ~os_Object_loader ();

  public: // Static Accessors
    static const os_type& get_loader_type (const os_type& type);

  public: // Accessors
    virtual Kind get_kind () const;
    const os_type* get_type (const char* type_string) const;
    const os_type* get_base_type (const char*& type_string) const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info);
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info,
                                           char*);

  protected: // Accessors
    virtual os_Type_loader* find_type_loader (os_Object_info& info) const;
    virtual os_Type_loader* find_type_loader
        (const char* type_string, const os_type*& type) const;
    virtual os_Type_loader& get_interpretive_loader
        (const os_type& type) const;
    const os_schema& get_schema () const;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Loader_info& info);
    virtual void create (os_Loader_info& info);

  private: // Friends
    friend class os_Loader;
    friend class os_Type_loader;

  };


/***********************************************************************
  class os_Object_info
***********************************************************************/

class os_Object_info : public os_Loader_info {

  public: // Construction
    os_Object_info (os_Object_loader&, os_Loader_stream&,
                    os_Loader_translated_info& previous_info);
    os_Object_info (const os_Object_info&);
    ~os_Object_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;
    const os_type* get_type () const;
    const char* get_type_string () const;
    os_Dumper_reference get_original_location () const;
    os_Dumper_reference get_replacing_location () const;
    os_segment& get_original_segment () const;
    os_segment& get_replacing_segment () const;
    os_database& get_original_database () const;
    os_database& get_replacing_database () const;
    void set_replacing_flags (os_unsigned_int32 flags);
    void set_original_location (os_Dumper_reference);

  protected: // Embedded data
    os_Type_loader* type_loader;
    char* type_string;
    const os_type* type;
    os_Dumper_reference original_location;
    os_Dumper_reference replacing_location;

  protected: // Accessors
    os_Loader_translated_info& get_loader_translated_info () const;

  protected: // Modifiers
    void set_replacing_location (os_Dumper_reference);

  private: // Friends
    friend class os_Object_loader;
    friend class os_Type_loader;
    friend class os_Type_info;
    friend class os_Fixup_loader;
    friend class os_Type_fixup_loader;

  private: // Data memebers
    int number_of_elements;   // negative number of elements indicates that it is not an array
    unsigned int type_name_length;

  };


/***********************************************************************
  class os_Type_loader
***********************************************************************/

class os_Type_loader : public os_Loader_action {

public: // Construction
  os_Type_loader ();
  ~os_Type_loader ();

public: // Accessors
  virtual Kind get_kind () const;
  virtual os_Type_loader* find_type_loader (const char* type_string) const;

public: // Actions
  virtual os_Loader_action* operator () (os_Loader_stream& stream,
					 os_Loader_info& info) = 0;
  virtual os_Loader_action* operator () (os_Loader_stream& stream,
					 os_Object_info& info,
					 unsigned number_elements);
  virtual os_Loader_action* load (os_Loader_stream& stream,
				  os_Type_data& data,
				  os_boolean is_most_derived_class) = 0;
  virtual void construct (os_Type_data& data, void* object,
			  os_boolean is_most_derived_class);
  virtual void fixup (os_Type_data& data, void* object,
		      os_boolean is_most_derived_class);

  virtual os_Loader_action* load (os_Loader_stream& stream,
				  os_Type_data& data,
				  os_unsigned_int32 data_size,
				  os_unsigned_int32 number_elements);
  virtual void construct (os_Type_data& data, void* object,
			  os_unsigned_int32 data_size,
			  os_unsigned_int32 object_size,
			  os_unsigned_int32 number_elements);
  virtual void fixup (os_Type_data& data, void* object,
		      os_unsigned_int32 data_size,
		      os_unsigned_int32 object_size,
		      os_unsigned_int32 number_elements);
  virtual void set_field (void* xbyte, int bit, int width, void* xdata);

protected: // Embedded data
  os_Object_loader object_loader;
  os_class_type* data_type;
  os_unsigned_int32 data_size;
  os_unsigned_int32 data_alignment;

protected: // Accessors
  virtual os_class_type* get_data_type () const;
  virtual os_unsigned_int32 get_data_size () const;
  virtual os_unsigned_int32 get_data_alignment () const;

public:
  void set_loader (os_Loader&);                               
protected: // Modifiers
  void set_data_type (os_class_type&);
  void set_data_size (os_unsigned_int32);
  void set_data_alignment (os_unsigned_int32);

protected: // Actions
  virtual void create (os_Loader_info& info) = 0;

private: // Actions
  virtual os_Loader_action* load (os_Loader_stream& stream,
				  os_Loader_info& info);

public: // Debugging
  virtual void show () const;
  virtual void show (ostream&) const;
  virtual const char* get_name () const;

private: // Friends
  //    friend void os_Loader_registration_entry::set_context (os_Loader& loader);
  friend class os_Embedded_constructor;
  friend class os_Data_generator;
  friend class os_Interpretive_data;
  friend class os_Interpretive_loader_generator;
  friend class os_Embedded_loader_generator;
  friend class os_Embedded_fixup_generator;

};


/***********************************************************************
  class os_Type_info
***********************************************************************/

class os_Type_info : public os_Loader_info {

  public: // Construction
    os_Type_info ();
    os_Type_info (os_Type_loader&, os_Loader_stream&, os_Object_info&);
    ~os_Type_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;
    os_Dumper_reference get_original_location () const;
    os_Dumper_reference get_replacing_location () const;
    os_segment& get_replacing_segment () const;
    os_database& get_replacing_database () const;
    const os_type& get_type () const;
    const os_type* get_type_pt () const;
    const char* get_type_string () const
       {return object_info->get_type_string();}
    const char* element_string () const;
    void set_replacing_flags (os_unsigned_int32 flags);

  protected: // Embedded data
    os_Object_info* object_info;

  protected: // Accessors
    os_Object_info& get_object_info () const;

  protected: // Modifiers
    void set_replacing_location (os_Dumper_reference location);

  private: // Friends
    friend class os_Type_loader;

  };


/***********************************************************************
  class os_Type_data
***********************************************************************/

class os_Type_data {
  };


/***********************************************************************
  class os_Nop_loader
***********************************************************************/

class os_Nop_loader : public os_Type_loader {

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info);
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Object_info& info,
                                        unsigned number_elements);

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Type_data& data);
    virtual void create (os_Loader_info& info);
// shut up Solaris
private: // Actions
   virtual os_Loader_action* load(os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data, os_boolean is_most_derived_class) = 0;
   virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Loader_info& info) = 0;
  };

#endif /* OBJ_LOADER_HH */
