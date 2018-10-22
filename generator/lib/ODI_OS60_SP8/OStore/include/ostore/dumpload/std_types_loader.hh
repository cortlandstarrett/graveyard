/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef STD_TYPES_LOADER_HH
#define STD_TYPES_LOADER_HH

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
#include <ostore/dumpload/loader.hh>
#include <ostore/dumpload/obj_loader.hh>


//-- Forward Declarations ----------------------------------------------

class os_Char_loader;
class os_Char_info;
class os_Signed_char_loader;
class os_Signed_char_info;
class os_Unsigned_char_loader;
class os_Unsigned_char_info;
class os_Short_loader;
class os_Short_info;
class os_Unsigned_short_loader;
class os_Unsigned_short_info;
class os_Int_loader;
class os_Int_info;
class os_Unsigned_int_loader;
class os_Unsigned_int_info;
class os_Long_loader;
class os_Long_info;
class os_Unsigned_long_loader;
class os_Unsigned_long_info;
class os_Float_loader;
class os_Float_info;
class os_Double_loader;
class os_Double_info;
class os_Long_double_loader;
class os_Long_double_info;
class os_Void_pointer_loader;
class os_Void_pointer_info;


/***********************************************************************
  class os_Char_data
***********************************************************************/

class os_Char_data : public os_Type_data {

  public: // Construction
    os_Char_data ();
    ~os_Char_data ();

  protected: // Embedded data
    char value;

  private: // Friends
    friend class os_Char_loader;
    friend class os_Char_info;

  };


/***********************************************************************
  class os_Char_info
***********************************************************************/

class os_Char_info : public os_Type_info {

  public: // Construction
    os_Char_info (os_Char_loader&, os_Loader_stream&, os_Object_info&,
		  os_Char_data&);
    ~os_Char_info ();

  protected: // Embedded data
    os_Char_data* data;

  private: // Friends
    friend class os_Char_loader;

  };


/***********************************************************************
  class os_Char_loader
***********************************************************************/

class os_Char_loader : public os_Type_loader {

  public: // Construction
    os_Char_loader ();
    virtual ~os_Char_loader ();

  public: // Static Accessor
    static os_Char_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Object_info& object_info,
					   unsigned number_elements);

    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_unsigned_int32 data_size,
				    os_unsigned_int32 number_elements);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_unsigned_int32 data_size,
			os_unsigned_int32 object_size,
			os_unsigned_int32 number_elements);

  protected: // Actions
    virtual void create (os_Loader_info& info);

  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
  virtual os_Loader_action* load(os_Loader_stream& stream,
     os_Loader_info& info)
     {return (os_Loader_action*)0;}
  virtual void fixup(os_Type_data& data, void* object,
     os_boolean is_most_derived_class)
     {os_Type_loader::fixup(data,object,is_most_derived_class);}
 };


/***********************************************************************
  class os_Signed_char_data
***********************************************************************/

class os_Signed_char_data : public os_Type_data {

  public: // Construction
    os_Signed_char_data ();
    ~os_Signed_char_data ();

  protected: // Embedded data
    signed char value;

  private: // Friends
    friend class os_Signed_char_loader;
    friend class os_Signed_char_info;

  };


/***********************************************************************
  class os_Signed_char_info
***********************************************************************/

class os_Signed_char_info : public os_Type_info {

  public: // Construction
    os_Signed_char_info (os_Signed_char_loader&, os_Loader_stream&, 
			 os_Object_info&, os_Signed_char_data&);
    ~os_Signed_char_info ();

  protected: // Embedded data
    os_Signed_char_data* data;

  private: // Friends
    friend class os_Signed_char_loader;

  };


/***********************************************************************
  class os_Signed_char_loader
***********************************************************************/

class os_Signed_char_loader : public os_Type_loader {

  public: // Construction
    os_Signed_char_loader ();
    virtual ~os_Signed_char_loader ();

  public: // Static Accessor
    static os_Signed_char_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
   };


/***********************************************************************
  class os_Unsigned_char_data
***********************************************************************/

class os_Unsigned_char_data : public os_Type_data {

  public: // Construction
    os_Unsigned_char_data ();
    ~os_Unsigned_char_data ();

  protected: // Embedded data
    unsigned char value;

  private: // Friends
    friend class os_Unsigned_char_loader;
    friend class os_Unsigned_char_info;

  };


/***********************************************************************
  class os_Unsigned_char_info
***********************************************************************/

class os_Unsigned_char_info : public os_Type_info {

  public: // Construction
    os_Unsigned_char_info (os_Unsigned_char_loader&, os_Loader_stream&, 
			   os_Object_info&, os_Unsigned_char_data&);
    ~os_Unsigned_char_info ();

  protected: // Embedded data
    os_Unsigned_char_data* data;

  private: // Friends
    friend class os_Unsigned_char_loader;

  };


/***********************************************************************
  class os_Unsigned_char_loader
***********************************************************************/

class os_Unsigned_char_loader : public os_Type_loader {

  public: // Construction
    os_Unsigned_char_loader ();
    virtual ~os_Unsigned_char_loader ();

  public: // Static Accessor
    static os_Unsigned_char_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Short_data
***********************************************************************/

class os_Short_data : public os_Type_data {

  public: // Construction
    os_Short_data ();
    ~os_Short_data ();

  protected: // Embedded data
    short value;

  private: // Friends
    friend class os_Short_loader;
    friend class os_Short_info;

  };


/***********************************************************************
  class os_Short_info
***********************************************************************/

class os_Short_info : public os_Type_info {

  public: // Construction
    os_Short_info (os_Short_loader&, os_Loader_stream&, os_Object_info&,
		   os_Short_data&);
    ~os_Short_info ();

  protected: // Embedded data
    os_Short_data* data;

  private: // Friends
    friend class os_Short_loader;

  };


/***********************************************************************
  class os_Short_loader
***********************************************************************/

class os_Short_loader : public os_Type_loader {

  public: // Construction
    os_Short_loader ();
    virtual ~os_Short_loader ();

  public: // Static Accessor
    static os_Short_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Unsigned_short_data
***********************************************************************/

class os_Unsigned_short_data : public os_Type_data {

  public: // Construction
    os_Unsigned_short_data ();
    ~os_Unsigned_short_data ();

  protected: // Embedded data
    unsigned short value;

  private: // Friends
    friend class os_Unsigned_short_loader;
    friend class os_Unsigned_short_info;

  };


/***********************************************************************
  class os_Unsigned_short_info
***********************************************************************/

class os_Unsigned_short_info : public os_Type_info {

  public: // Construction
    os_Unsigned_short_info (os_Unsigned_short_loader&, os_Loader_stream&, 
			    os_Object_info&, os_Unsigned_short_data&);
    ~os_Unsigned_short_info ();

  protected: // Embedded data
    os_Unsigned_short_data* data;

  private: // Friends
    friend class os_Unsigned_short_loader;

  };


/***********************************************************************
  class os_Unsigned_short_loader
***********************************************************************/

class os_Unsigned_short_loader : public os_Type_loader {

  public: // Construction
    os_Unsigned_short_loader ();
    virtual ~os_Unsigned_short_loader ();

  public: // Static Accessor
    static os_Unsigned_short_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Int_data
***********************************************************************/

class os_Int_data : public os_Type_data {

  public: // Construction
    os_Int_data ();
    ~os_Int_data ();

  protected: // Embedded data
    int value;

  private: // Friends
    friend class os_Int_loader;
    friend class os_Int_info;

  };


/***********************************************************************
  class os_Int_info
***********************************************************************/

class os_Int_info : public os_Type_info {

  public: // Construction
    os_Int_info (os_Int_loader&, os_Loader_stream&, os_Object_info&,
		 os_Int_data&);
    ~os_Int_info ();

  protected: // Embedded data
    os_Int_data* data;

  private: // Friends
    friend class os_Int_loader;

  };


/***********************************************************************
  class os_Int_loader
***********************************************************************/

class os_Int_loader : public os_Type_loader {

  public: // Construction
    os_Int_loader ();
    virtual ~os_Int_loader ();

  public: // Static Accessor
    static os_Int_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Unsigned_int_data
***********************************************************************/

class os_Unsigned_int_data : public os_Type_data {

  public: // Construction
    os_Unsigned_int_data ();
    ~os_Unsigned_int_data ();

  protected: // Embedded data
    unsigned int value;

  private: // Friends
    friend class os_Unsigned_int_loader;
    friend class os_Unsigned_int_info;

  };


/***********************************************************************
  class os_Unsigned_int_info
***********************************************************************/

class os_Unsigned_int_info : public os_Type_info {

  public: // Construction
    os_Unsigned_int_info (os_Unsigned_int_loader&, os_Loader_stream&, 
			  os_Object_info&, os_Unsigned_int_data&);
    ~os_Unsigned_int_info ();

  protected: // Embedded data
    os_Unsigned_int_data* data;

  private: // Friends
    friend class os_Unsigned_int_loader;

  };


/***********************************************************************
  class os_Unsigned_int_loader
***********************************************************************/

class os_Unsigned_int_loader : public os_Type_loader {

  public: // Construction
    os_Unsigned_int_loader ();
    virtual ~os_Unsigned_int_loader ();

  public: // Static Accessor
    static os_Unsigned_int_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Long_data
***********************************************************************/

class os_Long_data : public os_Type_data {

  public: // Construction
    os_Long_data ();
    ~os_Long_data ();

  protected: // Embedded data
    long value;

  private: // Friends
    friend class os_Long_loader;
    friend class os_Long_info;

  };


/***********************************************************************
  class os_Long_info
***********************************************************************/

class os_Long_info : public os_Type_info {

  public: // Construction
    os_Long_info (os_Long_loader&, os_Loader_stream&, os_Object_info&,
		  os_Long_data&);
    ~os_Long_info ();

  protected: // Embedded data
    os_Long_data* data;

  private: // Friends
    friend class os_Long_loader;

  };


/***********************************************************************
  class os_Long_loader
***********************************************************************/

class os_Long_loader : public os_Type_loader {

  public: // Construction
    os_Long_loader ();
    virtual ~os_Long_loader ();

  public: // Static Accessor
    static os_Long_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Unsigned_long_data
***********************************************************************/

class os_Unsigned_long_data : public os_Type_data {

  public: // Construction
    os_Unsigned_long_data ();
    ~os_Unsigned_long_data ();

  protected: // Embedded data
    unsigned long value;

  private: // Friends
    friend class os_Unsigned_long_loader;
    friend class os_Unsigned_long_info;

  };


/***********************************************************************
  class os_Unsigned_long_info
***********************************************************************/

class os_Unsigned_long_info : public os_Type_info {

  public: // Construction
    os_Unsigned_long_info (os_Unsigned_long_loader&, os_Loader_stream&, 
			   os_Object_info&, os_Unsigned_long_data&);
    ~os_Unsigned_long_info ();

  protected: // Embedded data
    os_Unsigned_long_data* data;

  private: // Friends
    friend class os_Unsigned_long_loader;

  };


/***********************************************************************
  class os_Unsigned_long_loader
***********************************************************************/

class os_Unsigned_long_loader : public os_Type_loader {

  public: // Construction
    os_Unsigned_long_loader ();
    virtual ~os_Unsigned_long_loader ();

  public: // Static Accessor
    static os_Unsigned_long_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Float_data
***********************************************************************/

class os_Float_data : public os_Type_data {

  public: // Construction
    os_Float_data ();
    ~os_Float_data ();

  protected: // Embedded data
    float value;
    unsigned char buffer[2*sizeof(float)+1];

  private: // Friends
    friend class os_Float_loader;
    friend class os_Float_info;

  };


/***********************************************************************
  class os_Float_info
***********************************************************************/

class os_Float_info : public os_Type_info {

  public: // Construction
    os_Float_info (os_Float_loader&, os_Loader_stream&, os_Object_info&,
		   os_Float_data&);
    ~os_Float_info ();

  protected: // Embedded data
    os_Float_data* data;

  private: // Friends
    friend class os_Float_loader;

  };


/***********************************************************************
  class os_Float_loader
***********************************************************************/

class os_Float_loader : public os_Type_loader {

  public: // Construction
    os_Float_loader ();
    virtual ~os_Float_loader ();

  public: // Static Accessor
    static os_Float_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Double_data
***********************************************************************/

class os_Double_data : public os_Type_data {

  public: // Construction
    os_Double_data ();
    ~os_Double_data ();

  protected: // Embedded data
    double value;
    unsigned char buffer[2*sizeof(double)+1];

  private: // Friends
    friend class os_Double_loader;
    friend class os_Double_info;

  };


/***********************************************************************
  class os_Double_info
***********************************************************************/

class os_Double_info : public os_Type_info {

  public: // Construction
    os_Double_info (os_Double_loader&, os_Loader_stream&, os_Object_info&, 
		    os_Double_data&);
    ~os_Double_info ();

  protected: // Embedded data
    os_Double_data* data;

  private: // Friends
    friend class os_Double_loader;

  };


/***********************************************************************
  class os_Double_loader
***********************************************************************/

class os_Double_loader : public os_Type_loader {

  public: // Construction
    os_Double_loader ();
    virtual ~os_Double_loader ();

  public: // Static Accessor
    static os_Double_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Long_double_data
***********************************************************************/

class os_Long_double_data : public os_Type_data {

  public: // Construction
    os_Long_double_data ();
    ~os_Long_double_data ();

  protected: // Embedded data
    long double value;
    unsigned char buffer[2*sizeof(long double)+1];

  private: // Friends
    friend class os_Long_double_loader;
    friend class os_Long_double_info;

  };


/***********************************************************************
  class os_Long_double_info
***********************************************************************/

class os_Long_double_info : public os_Type_info {

  public: // Construction
    os_Long_double_info (os_Long_double_loader&, os_Loader_stream&, 
			 os_Object_info&, os_Long_double_data&);
    ~os_Long_double_info ();

  protected: // Embedded data
    os_Long_double_data* data;

  private: // Friends
    friend class os_Long_double_loader;

  };


/***********************************************************************
  class os_Long_double_loader
***********************************************************************/

class os_Long_double_loader : public os_Type_loader {

  public: // Construction
    os_Long_double_loader ();
    virtual ~os_Long_double_loader ();

  public: // Static Accessor
    static os_Long_double_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


/***********************************************************************
  class os_Void_pointer_data
***********************************************************************/

class os_Void_pointer_data : public os_Type_data {

  public: // Construction
    os_Void_pointer_data ();
    ~os_Void_pointer_data ();

  protected: // Embedded data
    os_Fixup_reference value;

  private: // Friends
    friend class os_Void_pointer_loader;
    friend class os_Void_pointer_info;

  };


/***********************************************************************
  class os_Void_pointer_info
***********************************************************************/

class os_Void_pointer_info : public os_Type_info {

  public: // Construction
    os_Void_pointer_info (os_Void_pointer_loader&, os_Loader_stream&,
			  os_Object_info&, os_Void_pointer_data&);
    ~os_Void_pointer_info ();

  protected: // Embedded data
    os_Void_pointer_data* data;

  private: // Friends
    friend class os_Void_pointer_loader;

  };


/***********************************************************************
  class os_Void_pointer_loader
***********************************************************************/

class os_Void_pointer_loader : public os_Type_loader {

  public: // Construction
    os_Void_pointer_loader ();
    virtual ~os_Void_pointer_loader ();

  public: // Static Accessor
    static os_Void_pointer_loader& get ();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& previous_info);
    virtual os_Loader_action* load (os_Loader_stream& stream, 
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

  protected: // Actions
    virtual void create (os_Loader_info& info);


  public: // Debugging
    virtual const char* get_name () const;

// shut Solaris up
private:
   virtual os_Loader_action* operator ()(os_Loader_stream& stream,
      os_Object_info& info, unsigned number_elements)
      {return os_Type_loader::operator ()(stream,info,number_elements);}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Loader_info& info)
      {return (os_Loader_action*)0;}
   virtual os_Loader_action* load (os_Loader_stream& stream,
      os_Type_data& data,os_unsigned_int32 data_size,
      os_unsigned_int32 number_elements)
      {return os_Type_loader::load(stream,data,data_size,number_elements);}
 };


#endif // STD_TYPES_LOADER_HH

