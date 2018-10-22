/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef SCHEMA_LOADER_HH
#define SCHEMA_LOADER_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1999-2000 by eXcelon Corporation. All Rights Reserved.                          *
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
  class os_Schema_loader
***********************************************************************/

class os_Schema_loader : public os_Loader_action {

  public: // Construction
    os_Schema_loader ();
    ~os_Schema_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Schema_info
***********************************************************************/

class os_Schema_info : public os_Loader_info {

  public: // Construction
    os_Schema_info (os_Schema_loader&, os_Loader_stream&,
                    os_Loader_translated_info& previous_info);
    ~os_Schema_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  protected: // Embedded data
    os_database* database;
    unsigned database_index;
    char* pathname;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;
    os_database& get_database () const;

  protected: // Modifiers
    void set_database (os_database&);

  private: // Friends
    friend class os_Schema_loader;
    friend class os_Schema_file_loader;

  };


/***********************************************************************
  class os_Schema_file_loader
***********************************************************************/

class os_Schema_file_loader : public os_Loader_action {

  public: // Construction
    os_Schema_file_loader ();
    ~os_Schema_file_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info&);
    virtual void create (os_Loader_info&);

  };


/***********************************************************************
  class os_Schema_file_info
***********************************************************************/

class os_Schema_file_info : public os_Loader_info {

  public: // Construction
    os_Schema_file_info (os_Schema_file_loader&, os_Loader_stream&,
                         os_Loader_translated_info& previous_info);
    ~os_Schema_file_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  protected: // Embedded data
    char* schema_database_path;
    os_database* schema_database;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;
    os_database& get_schema_database () const;

  protected: // Modifiers
    void set_schema_database (os_database&);

  private: // Friends
    friend class os_Schema_file_loader;

  };


#endif /* SCHEMA_LOADER_HH */
