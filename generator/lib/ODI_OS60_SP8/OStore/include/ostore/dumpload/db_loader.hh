/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DB_LOADER_HH
#define DB_LOADER_HH

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


//-- Forward Declarations ----------------------------------------------


/***********************************************************************
  class os_Database_entry_loader
***********************************************************************/

class os_Database_entry_loader : public os_Loader_action {

  public: // Construction
    os_Database_entry_loader (os_Databases_loader&, 
			      os_boolean should_use_current_directory);
    ~os_Database_entry_loader ();

  public: // Accessors
    virtual Kind get_kind () const;
    os_Databases_loader& get_databases_loader () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info,
					   unsigned number_elements);

  protected: // Embedded data
    os_Databases_loader* databases_loader;
    os_boolean use_current_directory;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Database_entry_info
***********************************************************************/

class os_Database_entry_info : public os_Loader_info {

  public: // Construction
    os_Database_entry_info (os_Database_entry_loader&, os_Loader_stream&,
			    os_Loader_info& previous_info);
    ~os_Database_entry_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data
    os_database* database;
    char* pathname;
    os_unsigned_int32 database_size; // TBD: make 64-bits
    os_unsigned_int32 number_segments;
    char* odi_release;
    char* architecture; // TBD: what is this really?
    os_Time_value date;
    objectstore::segment_reference_policy segment_reference_policy;

  private: // Friends
    friend class os_Database_entry_loader;
    friend class osji_Database_entry_loader;

  };


/***********************************************************************
  class os_Databases_loader
***********************************************************************/

class os_Databases_loader : public os_Loader_action {

  public: // Construction
    os_Databases_loader ();
    ~os_Databases_loader ();

  public: // Accessors
    virtual Kind get_kind () const;
    os_Database_table& get_database_table () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data
    /* TBD: Consider removing database_table and then using
            os_Loader_header::database_table directly. -rick@odi.com */
    os_Reference_transient<os_Database_table> database_table;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Databases_info
***********************************************************************/

class os_Databases_info : public os_Loader_info {

  public: // Construction
    os_Databases_info (os_Databases_loader&, os_Loader_stream&,
		       os_Loader_translated_info& previous_info);
    ~os_Databases_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data
    unsigned number_databases;

  private: // Friends
    friend class os_Databases_loader;

  };


/***********************************************************************
  class os_Database_loader
***********************************************************************/

class os_Database_loader : public os_Loader_action {

  public: // Construction
    os_Database_loader ();
    ~os_Database_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Database_info
***********************************************************************/

class os_Loader_architecture
   {
public:
   static void set(const char* name);
   static const char* get(void);
   };

class os_Database_info : public os_Loader_info {

  public: // Construction
    os_Database_info (os_Database_loader&, os_Loader_stream&,
		      os_Loader_translated_info& previous_info);
    os_Database_info (const os_Database_info&);
    ~os_Database_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Actions
    void pending_action ();

  protected: // Embedded data
    os_database* database;
    unsigned database_index;
    char* pathname;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;

  protected: // Modifiers
    void set_database (os_database&);

  private: // Friends
    friend class os_Database_loader;

  };


/***********************************************************************
  class os_Root_entry_loader
***********************************************************************/

class os_Root_entry_loader : public os_Loader_action {

  public: // Construction
    os_Root_entry_loader (os_Roots_loader&);
    ~os_Root_entry_loader ();

  public: // Accessors
    virtual Kind get_kind () const;
    os_Roots_loader& get_roots_loader () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info, 
					   unsigned number_elements);

  protected: // Embedded data
    os_Roots_loader* roots_loader;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Root_entry_info
***********************************************************************/

class os_Root_entry_info : public os_Loader_info {

  public: // Construction
    os_Root_entry_info (os_Root_entry_loader&, os_Loader_stream&,
			os_Loader_info& previous_info);
    ~os_Root_entry_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data
    char* root_name;
    char* type_string;
    os_Dumper_reference reference;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;

  private: // Friends
    friend class os_Root_entry_loader;

  };


/***********************************************************************
  class os_Roots_loader
***********************************************************************/

class os_Roots_loader : public os_Loader_action {

  public: // Construction
    os_Roots_loader ();
    ~os_Roots_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Roots_info
***********************************************************************/

class os_Roots_info : public os_Loader_info {

  public: // Construction
    os_Roots_info (os_Roots_loader&, os_Loader_stream&,
		   os_Loader_info& previous_info);
    ~os_Roots_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data
    unsigned number_roots;

  private: // Friends
    friend class os_Roots_loader;

  };


/***********************************************************************
  class os_Finalization_loader
***********************************************************************/

class os_Finalization_loader : public os_Loader_action {

  public: // Construction
    os_Finalization_loader ();
    ~os_Finalization_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info& info);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Finalization_info
***********************************************************************/

class os_Finalization_info : public os_Loader_info {

  public: // Construction
    os_Finalization_info (os_Finalization_loader&, os_Loader_stream&,
			  os_Loader_info& previous_info);
    ~os_Finalization_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data

  private: // Friends
    friend class os_Finalization_loader;

  };


#endif /* DB_LOADER_HH */
