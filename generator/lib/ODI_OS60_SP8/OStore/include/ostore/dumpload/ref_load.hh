/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REF_LOAD_HH
#define REF_LOAD_HH

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


// AS<

/***********************************************************************
  class os_soft_pointer32_data
***********************************************************************/

class os_soft_pointer32_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_soft_pointer32_loader;
    friend class os_soft_pointer32_info;
    friend class os_soft_pointer32_initializer;

  };

/***********************************************************************
  class os_soft_pointer64_data
***********************************************************************/

class os_soft_pointer64_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_soft_pointer64_loader;
    friend class os_soft_pointer64_info;
    friend class os_soft_pointer64_initializer;

  };

/***********************************************************************
  class os_reference_data
***********************************************************************/

class os_reference_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_reference_loader;
    friend class os_reference_info;
    friend class os_reference_initializer;

  };

/***********************************************************************
  class os_reference_this_DB_data
***********************************************************************/

class os_reference_this_DB_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_reference_this_DB_loader;
    friend class os_reference_this_DB_info;
    friend class os_reference_this_DB_initializer;

  };

/***********************************************************************
  class os_reference_protected_data
***********************************************************************/

class os_reference_protected_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_reference_protected_loader;
    friend class os_reference_protected_info;
    friend class os_reference_protected_initializer;

  };

/***********************************************************************
  class os_Reference_data
***********************************************************************/

class os_Reference_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_Reference_loader;
    friend class os_Reference_info;
    friend class os_reference_init;

  };

/***********************************************************************
  class os_Reference_this_DB_data
***********************************************************************/

class os_Reference_this_DB_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_Reference_this_DB_loader;
    friend class os_Reference_this_DB_info;
    friend class os_reference_this_DB_initializer;

  };

/***********************************************************************
  class os_Reference_protected_data
***********************************************************************/

class os_Reference_protected_data : public os_Type_data {

  protected: // Embedded data
    os_Dumper_reference reference;

  private: // Friends
    friend class os_Reference_protected_loader;
    friend class os_Reference_protected_info;
    friend class os_reference_protected_initializer;

  };



/***********************************************************************
  class os_soft_pointer32_info
***********************************************************************/

class os_soft_pointer32_info : public os_Type_info {

  public: // Construction
    os_soft_pointer32_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_soft_pointer32_data&);
    ~os_soft_pointer32_info ();

  protected: // Embedded data
    os_soft_pointer32_data * data;

  private: // Friends
    friend class os_soft_pointer32_loader;

  };

/***********************************************************************
  class os_soft_pointer64_info
***********************************************************************/

class os_soft_pointer64_info : public os_Type_info {

  public: // Construction
    os_soft_pointer64_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_soft_pointer64_data&);
    ~os_soft_pointer64_info ();

  protected: // Embedded data
    os_soft_pointer64_data * data;

  private: // Friends
    friend class os_soft_pointer64_loader;

  };

/***********************************************************************
  class os_reference_info
***********************************************************************/

class os_reference_info : public os_Type_info {

  public: // Construction
    os_reference_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_reference_data&);
    ~os_reference_info ();

  protected: // Embedded data
    os_reference_data * data;

  private: // Friends
    friend class os_reference_loader;

  };

/***********************************************************************
  class os_reference_this_DB_info
***********************************************************************/

class os_reference_this_DB_info : public os_Type_info {

  public: // Construction
    os_reference_this_DB_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_reference_this_DB_data&);
    ~os_reference_this_DB_info ();

  protected: // Embedded data
    os_reference_this_DB_data * data;

  private: // Friends
    friend class os_reference_this_DB_loader;

  };

/***********************************************************************
  class os_reference_protected_info
***********************************************************************/

class os_reference_protected_info : public os_Type_info {

  public: // Construction
    os_reference_protected_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_reference_protected_data&);
    ~os_reference_protected_info ();

  protected: // Embedded data
    os_reference_protected_data * data;

  private: // Friends
    friend class os_reference_protected_loader;

  };

/***********************************************************************
  class os_Reference_info
***********************************************************************/

class os_Reference_info : public os_Type_info {

  public: // Construction
    os_Reference_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_Reference_data&);
    ~os_Reference_info ();

  protected: // Embedded data
    os_Reference_data * data;

  private: // Friends
    friend class os_Reference_loader;

  };

/***********************************************************************
  class os_Reference_this_DB_info
***********************************************************************/

class os_Reference_this_DB_info : public os_Type_info {

  public: // Construction
    os_Reference_this_DB_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_Reference_this_DB_data&);
    ~os_Reference_this_DB_info ();

  protected: // Embedded data
    os_Reference_this_DB_data * data;

  private: // Friends
    friend class os_Reference_this_DB_loader;

  };

/***********************************************************************
  class os_Reference_protected_info
***********************************************************************/

class os_Reference_protected_info : public os_Type_info {

  public: // Construction
    os_Reference_protected_info (os_Type_loader&, os_Loader_stream&, os_Object_info&,
		       os_Reference_protected_data&);
    ~os_Reference_protected_info ();

  protected: // Embedded data
    os_Reference_protected_data * data;

  private: // Friends
    friend class os_Reference_protected_loader;

  };

// >AS

/***********************************************************************
  class os_soft_pointer32_loader
***********************************************************************/

class os_soft_pointer32_loader : public os_Type_loader {

   public:
      os_soft_pointer32_loader();
     ~os_soft_pointer32_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_soft_pointer32_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };

/***********************************************************************
  class os_soft_pointer64_loader
***********************************************************************/

class os_soft_pointer64_loader : public os_Type_loader {


   public:
      os_soft_pointer64_loader();
     ~os_soft_pointer64_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_soft_pointer64_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };

/***********************************************************************
  class os_reference_local_loader
***********************************************************************/

class os_reference_local_loader : public os_Type_loader {

   public:
      os_reference_local_loader();
     ~os_reference_local_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_reference_this_DB_loader
***********************************************************************/

class os_reference_this_DB_loader : public os_Type_loader {

   public:
      os_reference_this_DB_loader();
     ~os_reference_this_DB_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_reference_this_DB_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_reference_loader
***********************************************************************/

class os_reference_loader : public os_Type_loader {

   public:
      os_reference_loader();
     ~os_reference_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_reference_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };



/***********************************************************************
  class os_reference_protected_loader
***********************************************************************/

class os_reference_protected_loader : public os_Type_loader {

   public:
      os_reference_protected_loader();
     ~os_reference_protected_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_reference_protected_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_reference_protected_local_loader
***********************************************************************/

class os_reference_protected_local_loader : public os_Type_loader {

   public:
      os_reference_protected_local_loader();
     ~os_reference_protected_local_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Reference_local_loader
***********************************************************************/

class os_Reference_local_loader : public os_Type_loader {

   public:
      os_Reference_local_loader();
     ~os_Reference_local_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Reference_this_DB_loader
***********************************************************************/

class os_Reference_this_DB_loader : public os_Type_loader {

   public:
      os_Reference_this_DB_loader();
     ~os_Reference_this_DB_loader();

   public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_Reference_this_DB_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Reference_loader
***********************************************************************/

class os_Reference_loader : public os_Type_loader {

   public:
      os_Reference_loader();
     ~os_Reference_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);
    static os_Reference_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };



/***********************************************************************
  class os_Reference_protected_loader
***********************************************************************/

class os_Reference_protected_loader : public os_Type_loader {

   public:
      os_Reference_protected_loader();
     ~os_Reference_protected_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);
    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
    virtual void fixup (os_Type_data& data, void* object,
			os_boolean is_most_derived_class);

    static os_Reference_protected_loader& get ();
    virtual const char* get_name () const;

  public: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Reference_protected_local_loader
***********************************************************************/

class os_Reference_protected_local_loader : public os_Type_loader {

   public:
      os_Reference_protected_local_loader();
     ~os_Reference_protected_local_loader();

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					os_Loader_info& info);

    virtual void construct (os_Type_data& data, void* object,
                        os_boolean is_most_derived_class);
  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Type_data& data,
				    os_boolean is_most_derived_class);
    virtual void create (os_Loader_info& info);

  };
 

#endif /* REF_LOAD_HH */
