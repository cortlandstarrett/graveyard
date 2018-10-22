/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef SEGMENT_LOADER_HH
#define SEGMENT_LOADER_HH

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

/***********************************************************************
  class os_Segment_loader
***********************************************************************/

class os_Segment_loader : public os_Loader_action {

  public: // Construction
    os_Segment_loader ();
    ~os_Segment_loader ();

  public: // Accessors
    virtual Kind get_kind () const;

  public: // Modifiers

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data

  protected: // Actions
    virtual os_Loader_action* segment_action (os_Loader_stream& stream,
					      os_Loader_info& info);
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info& info);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_Segment_info
***********************************************************************/

class os_Segment_info : public os_Loader_info {

  public: // Construction
    os_Segment_info (os_Segment_loader&, os_Loader_stream&,
		     os_Loader_translated_info& previous_info);
    ~os_Segment_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  protected: // Embedded data
    os_segment* segment;
    unsigned long segment_number;
    unsigned long segment_flags;
#ifdef TBD_HOUDINI_SEG_SIZE
    os_unsigned_int64 segment_size;
#else
    unsigned long segment_size;
#endif
    char* pathname;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;

  protected: // Modifiers
    void set_segment (os_segment&);

  private: // Friends
    friend class os_Segment_loader;
    friend class osji_Segment_loader;

  };


/***********************************************************************
  class os_Cluster_loader
***********************************************************************/

class os_Cluster_loader : public os_Loader_action {

  public: // Construction
    os_Cluster_loader ();
    ~os_Cluster_loader ();

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
  class os_Cluster_info
***********************************************************************/

class os_Cluster_info : public os_Loader_info {

  public: // Construction
    os_Cluster_info (os_Cluster_loader&, os_Loader_stream&,
		     os_Loader_translated_info& previous_info);
    ~os_Cluster_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  protected: // Embedded data
    os_cluster* cluster;
    unsigned long cluster_size;

  protected: // Accessors
    os_Loader_translated_info& get_translated_info () const;

  protected: // Modifiers
    void set_cluster (os_cluster&);

  private: // Friends
    friend class os_Cluster_loader;

  };


/***********************************************************************
  class os_End_block_loader
***********************************************************************/

class os_End_block_loader : public os_Loader_action {

  public: // Construction
    os_End_block_loader ();
    os_End_block_loader (os_Loader_action& pending_action,
			 os_Loader_info& pending_info);
    ~os_End_block_loader ();

  public: // Static Accessors
    static os_End_block_loader& get ();

  public: // Accessors
    virtual Kind get_kind () const;
    os_Loader_action* get_pending_action () const;
    os_Loader_info* get_pending_info () const;
    virtual os_boolean is_handling_transactions (os_Loader_info* = 0) const;

  public: // Modifiers
    void set_pending_info (os_Loader_info& info);

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
					   os_Loader_info& info);

  protected: // Embedded data
    os_Loader_action* pending_action;
    os_Loader_info* pending_info;

  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
				    os_Loader_info& info);
    virtual void create (os_Loader_info& info);

  };


/***********************************************************************
  class os_End_block_info
***********************************************************************/

class os_End_block_info : public os_Loader_info {

  public: // Construction
    os_End_block_info (os_End_block_loader&, os_Loader_stream&,
		       os_Loader_info& previous_info);
    ~os_End_block_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;

  public: // Modifiers

  protected: // Embedded data

  private: // Friends
    friend class os_End_block_loader;

  };


#endif /* SEGMENT_LOADER_HH */
