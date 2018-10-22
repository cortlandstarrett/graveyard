/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DB_TAB_I_HH
#define DB_TAB_I_HH

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
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>

#include <ostore/traverse/btreept.hh>
#include <ostore/traverse/chainlst.hh>

#include "dmp_ref.hh"
#include "fixup.hh"
#include "db_table.hh"


#define MAX_DB_TABLE_SIZE 1024

/***********************************************************************
  class os_Database_table_persist
***********************************************************************/

class os_Database_table_persist {

  public: // Construction

    /* Construct a os_Database_table_persist of the given number of entries. 
       Entry 0 in the database table refers to the null database */
    os_Database_table_persist (unsigned number_entries,
			       unsigned growth_size = 5);

    /* Destruct this os_Database_table_persist. */
    ~os_Database_table_persist ();

  public: // Accessors

    /* Returns the number of database entries in this table. */
    unsigned get_number_entries () const;

    /* Returns os_Database_entry at number. If this is invalid
       index an exception is raised. */
    os_Database_entry& operator[] (os_unsigned_int32 number) const;

    /* Returns os_Database_entry with the corresponding path. If no
       such path exists, 0 is returned. */
    os_Database_entry* find_entry (const char* path) const;

    /* Returns number of path in db_entry, If this path is not found,
       0 is returned. Number 0 in the database table refers to the
       null database */
    os_unsigned_int32 find_number (const char* path) const; 	
	
    /* Returns the os_Dumper_reference within the target databases
       corresponding to the given os_Dumper_reference. */
    os_Dumper_reference find_reference
        (const os_Dumper_reference& reference) const;

    /* Test whether the given object should be ignored. */
    os_boolean is_ignored (const os_Dumper_reference& object) const;

    /* Returns any cross-database reference fixups associated
       with this os_Database_table_persist. */
    os_Cross_database_reference_fixups* get_reference_fixups () const;

    /* Returns any root reference fixups associated
       with this os_Database_table_persist. */
    os_Database_root_reference_fixups* get_root_fixups () const;
    /* Returns any class key reference fixups associated
       with this os_Database_table_persist. */
    os_Database_class_key_reference_fixups* get_class_key_fixups () const;

    /* Returns any in-database fixups associated with this 
       os_Database_table_persist. */
    os_Fixups* get_fixups () const;

  public: // Modifiers

    /* Insert a os_Database_entry corresponding to the given database
       into this os_Database_table_persist. */
    void insert (os_database& database);

    /* Insert an os_Segment_entry corresponding to the given
       segment into this os_Database_table. */
    void insert (os_segment& segment);
   
   /* Insert an os_Cluster_entry corresponding to the given
       segment into this os_Database_table. */
    void insert (os_cluster& cluster);
    

    /* Insert a os_Database_entry corresponding to the given path
       into this os_Database_table_persist. */
    void insert (const char* path, 
		 os_unsigned_int32 database_size,
		 os_unsigned_int32 number_segments,
		 const char* release_name, 
		 os_Time_value last_modification_time);

    /* Insert a mapping from a source os_Dumper_reference to a
       target os_Dumper_reference into this os_Database_table_persist. */
    void insert (const os_Dumper_reference& source,
		 const os_Dumper_reference& target,
		 const os_type& referent_type);

    /* Insert a reference fixup into this os_Database_table_persist. */
    void insert (os_Reference_fixup_kind::Kind, 
		 const os_Dumper_reference& reference,
		 const os_Dumper_reference& referent_original_location);

    /* Insert a root reference fixup into this os_Database_table_persist. */
    void insert (const os_Dumper_reference& referent_original_location,
                 char* type_name,
                 char* root_name);

    /* Insert a class key reference fixup into this os_Database_table_persist. */
    void insert (const os_Dumper_reference& dictionary,
                  const os_Dumper_reference& key,
                  const os_Dumper_reference& value);

    /* Insert an object to ignore into the os_Database_table_persist. */
    void insert (const os_Dumper_reference& ignored_object);
    
    /* Insert an intra-segment generic os_Fixup into this 
       os_Database_table_persist. */
    void insert (os_segment&, const os_Fixup& fixup);

    /* Insert an intra-database generic os_Fixup into this 
       os_Database_table_persist. */
    void insert (os_database&, const os_Fixup& fixup);

    /* Insert an inter-database generic os_Fixup into this 
       os_Database_table_persist. */
    void insert (const os_Fixup& fixup);

    /* called when loader enters finalization so that
       all reference fixups are treated as cross database
       fixups. */
    void in_finalization() {flags |= 1;}

    /* os_Fixup the given segment's intra-segment objects. */
    void fixup (os_segment& segment);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Database_entry* entries;
    os_unsigned_int32 total_entries; /* Number of entries allocated. */
    os_unsigned_int32 used_entries; /* Number of entries used. */
    os_unsigned_int32 flags;
    os_Array<const char*>* work_database_paths;
    os_Cross_database_reference_fixups* reference_fixups;
    os_Database_root_reference_fixups* root_fixups;
    os_Database_class_key_reference_fixups* class_key_fixups;
    os_Fixups* fixups;

  protected: // Accessors
    os_boolean check_selection (os_unsigned_int32 number) const;
    os_Segment_table* get_segment_table (os_database& database) const;

  protected: // Modifiers
    void accommodate_insert (os_unsigned_int32 number);

    /* Inform this os_Database_table_persist that work on the given 
       database is beginning. */
    void enter (const os_database&);

    /* Inform this os_Database_table_persist that work on the given 
       database is ending. */
    void exit (const os_database&);

    /* Inform this os_Database_table_persist that work on the given 
       segment is beginning. */
    void enter (const os_segment&);

    /* Inform this os_Database_table_persist that work on the given 
       segment is ending. */
    void exit (const os_segment&);

  private: // Embedded data
    const unsigned growth_size;

  private: // Construction

    /* Make it impossible to copy a os_Database_table_persist. */
    os_Database_table_persist (const os_Database_table_persist&)
	: growth_size(0) {};

    /* Make it impossible to copy a os_Database_table_persist. */
    os_Database_table_persist& operator = (const os_Database_table_persist&)
    { return *this; }

  private: // Friends
    friend class os_Database_table;
    friend class os_Database_entry;

  };


/***********************************************************************
  class os_Database_entry
***********************************************************************/

class os_Database_entry {

  protected: // Construction

    os_Database_entry (os_Database_table_persist&, os_database& database, 
		       os_unsigned_int32 number);

    /* This constructor opens the database denoted by path. */
    os_Database_entry (os_Database_table_persist&, const char* path, 
		       os_unsigned_int32 database_size,
		       os_unsigned_int32 number_segments,
		       const char* release_name, 
		       os_Time_value last_modification_time,
		       os_unsigned_int32 number);

    os_Database_entry ();

    ~os_Database_entry ();
		    
  public: // Accessors
    os_boolean is_null () const;
    os_database& get_database () const;
    const char* get_path () const;
    os_Database_table_persist& get_database_table () const;
    /* TBD: other useful accessors */

  protected: // Modifiers
    void set_segment_table (os_Segment_table&);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Database_table_persist* database_table;
    const char* path;
    os_unsigned_int64 database_size;
    os_unsigned_int32 number_segments;
    const char* release_name;
    /* TBD: need a way to represent architecture set. */
    /* Architecture? architecture_set; */
    os_Time_value last_modification_time;
    os_Segment_table* segment_table;
    os_unsigned_int32 number;
    char _os_pad_0[4]; /* for neutralization */

  private: // Friends
    friend class os_Database_table_persist;

  };


/***********************************************************************
  typedef os_In_database_reference_fixups
***********************************************************************/

typedef os_Chained_list_block<os_In_database_reference_fixup> 
    os_In_database_reference_fixup_block;
typedef os_Chained_list<os_In_database_reference_fixup> 
    os_In_database_reference_fixups;
typedef os_Chained_list_cursor<os_In_database_reference_fixup> 
    os_In_database_reference_fixup_cursor;


/***********************************************************************
  class os_Segment_table
***********************************************************************/

class os_Segment_table {

  public: // Construction

    /* Construct a os_Segment_table of the given number of entries. */
    os_Segment_table (os_Database_entry&,
		      os_unsigned_int32 number_entries,
		      os_unsigned_int32 growth_size);

    /* Destruct this os_Segment_table */
    ~os_Segment_table ();

  public: // Accessors

    /* Returns os_Segment_entry at number. If this is an invalid
       number an exception is raised. The given number corresponds
       to the segment number. */
    os_Segment_entry& operator[] (os_unsigned_int32 number) const;

    /* Returns the os_Dumper_reference corresponding to the 
       given os_Dumper_reference's segment number and offset.
       If the returned os_Dumper_reference is incomplete, then the 
       os_Database_table_persist is expected to fill in the missing
       database information */
    os_Dumper_reference find_reference
        (const os_Dumper_reference& reference) const;

    /* Returns the os_Database_entry associated with this 
       os_Segment_table. */
    os_Database_entry& get_database_entry () const;

    /* Test whether the given object should be ignored. */
    os_boolean is_ignored (const os_Dumper_reference& object) const;

    /* Returns any in-database reference fixups associated
       with this os_Segment_table. */
    os_In_database_reference_fixups* get_reference_fixups () const;

    /* Returns any in-database fixups associated with this 
       os_Segment_table. */
    os_Fixups* get_fixups () const;

  public: // Modifiers

    /* Insert a os_Segment_entry corresponding to the given segment
       into this os_Segment_table. */
    void insert (os_segment& segment);

    /* Insert a os_Cluster_entry corresponding to the given segment
       into this os_Segment_table. */
    void insert (os_cluster& cluster);

    /* Insert a os_Segment_entry corresponding to the given number
       into this os_Segment_table. */
    void insert (os_unsigned_int32 segment_number,
#ifdef TBD_HOUDINI_SEG_SIZE
		 os_unsigned_int64 segment_size);
#else
		 os_unsigned_int32 segment_size);
#endif
    /* Insert a mapping from a source os_Dumper_reference to a
       target os_Dumper_reference into this os_Segment_table. Only
       the segment portion of the references are considered. */
    void insert (const os_Dumper_reference& source,
		 const os_Dumper_reference& target,
		 const os_type& referent_type);

    /* Insert a reference fixup into this os_Segment_table. */
    void insert (os_Reference_fixup_kind::Kind,
		 const os_Dumper_reference& reference,
		 const os_Dumper_reference& referent_original_location);

    /* Insert an object to ignore into the os_Segment_table. */
    void insert (const os_Dumper_reference& ignored_object);
    
    /* Insert an intra-segment generic os_Fixup into this os_Segment_table. */
    void insert (os_segment&, const os_Fixup& fixup);

    /* Insert an intra-database generic os_Fixup into this os_Segment_table. */
    void insert (const os_Fixup& fixup);

#if 0
    /* os_Fixup the given database's intra-database objects. */
    void fixup (os_database& database, os_unsigned_int32 database_number);
#endif

    /* os_Fixup the given segment's intra-segment objects. */
    void fixup (os_segment& segment, os_unsigned_int32 database_number);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Database_entry* database_entry;
    os_Segment_entry* entries;
    os_unsigned_int32 total_entries; /* Number of entries allocated. */
    os_unsigned_int32 growth_size;
    os_In_database_reference_fixups* reference_fixups;
    os_Fixups* fixups;

  protected: // Accessors
    os_unsigned_int32 get_selection_number (os_unsigned_int32 number) const;
    void check_selection (os_unsigned_int32 number) const;

  protected: // Modifiers
    void accommodate_insert (os_unsigned_int32 number);

  };


/***********************************************************************
  class os_Segment_entry
***********************************************************************/

class os_Segment_entry {

  protected: // Construction
    os_Segment_entry (os_Segment_table&, os_segment& segment);
    os_Segment_entry (os_Segment_table&, os_unsigned_int32 segment_number,
		      os_unsigned_int32 number_clusters);
    os_Segment_entry ();
    ~os_Segment_entry ();

  public: // Accessors
    os_boolean is_null () const;
    os_segment& get_segment () const;
    os_unsigned_int32 get_segment_number () const;
    os_Segment_table& get_segment_table () const;
    /* TBD: any other useful accessors. */

  protected: // Modifiers
#if 0
    void set_segment_size (os_unsigned_int32 size);
#endif
    void set_cluster_table (os_Cluster_table&);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Segment_table* segment_table;
    os_unsigned_int32 segment_number;
    //os_unsigned_int32 segment_size;
    os_unsigned_int32 number_clusters;
    os_Cluster_table* cluster_table;

  private: // Friends
    friend class os_Segment_table;

  };

/*+++*/
/***********************************************************************
  class os_Cluster_table
***********************************************************************/


class os_Cluster_table {

  public: // Construction

    /* Construct a os_Cluster_table of the given number of entries. */
    os_Cluster_table (os_Segment_entry&,
		      os_unsigned_int32 number_entries,
		      os_unsigned_int32 growth_size);

    /* Destruct this os_Cluster_table */
    ~os_Cluster_table ();

  public: // Accessors

    /* Returns os_Cluster_entry at number. If this is an invalid
       number an exception is raised. The given number corresponds
       to the segment number. */
    os_Cluster_entry& operator[] (os_unsigned_int32 number) const;

    /* Returns the os_Dumper_reference corresponding to the 
       given os_Dumper_reference's Cluster number and offset.
       If the returned os_Dumper_reference is incomplete, then the 
       os_Database_table_persist is expected to fill in the missing
       database information */
    os_Dumper_reference find_reference
        (const os_Dumper_reference& reference) const;

    /* Returns the os_Segment_entry associated with this 
       os_Cluster_table. */
    os_Segment_entry& get_segment_entry () const;

    /* Test whether the given object should be ignored. */
    os_boolean is_ignored (const os_Dumper_reference& object) const;

    /* Returns any in-database reference fixups associated
       with this os_Cluster_table. */
    os_In_database_reference_fixups* get_reference_fixups () const;

    /* Returns any in-database fixups associated with this 
       os_Cluster_table. */
    os_Fixups* get_fixups () const;

  public: // Modifiers

    /* Insert a os_Cluster_entry corresponding to the given Cluster
       into this os_Cluster_table. */
    void insert (os_cluster& cluster);

    /* Insert a os_Cluster_entry corresponding to the given number
       into this os_Cluster_table. */
    void insert (os_unsigned_int32 cluster_number,
#ifdef TBD_HOUDINI_SEG_SIZE
		 os_unsigned_int64 cluster_size);
#else
		 os_unsigned_int32 cluster_size);
#endif
    /* Insert a mapping from a source os_Dumper_reference to a
       target os_Dumper_reference into this os_Cluster_table. Only
       the Cluster portion of the references are considered. */
    void insert (const os_Dumper_reference& source,
		 const os_Dumper_reference& target,
		 const os_type& referent_type);

    /* Insert a reference fixup into this os_Cluster_table. */
    void insert (os_Reference_fixup_kind::Kind,
		 const os_Dumper_reference& reference,
		 const os_Dumper_reference& referent_original_location);

    /* Insert an object to ignore into the os_Cluster_table. */
    void insert (const os_Dumper_reference& ignored_object);
    
    /* Insert an intra-Cluster generic os_Fixup into this os_Cluster_table. */
    void insert (os_cluster&, const os_Fixup& fixup);

    /* Insert an intra-database generic os_Fixup into this os_Cluster_table. */
    void insert (const os_Fixup& fixup);

    /* os_Fixup the given Cluster's intra-Cluster objects. */
    void fixup (os_segment& segment, os_unsigned_int32 database_number);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Segment_entry* segment_entry;
    os_Cluster_entry* entries;
    os_unsigned_int32 total_entries; /* Number of entries allocated. */
    os_unsigned_int32 growth_size;
    os_In_database_reference_fixups* reference_fixups;
    os_Fixups* fixups;

  protected: // Accessors
    void check_selection (os_unsigned_int32 number) const;

  protected: // Modifiers
    void accommodate_insert (os_unsigned_int32 number);

  };


/***********************************************************************
  class os_Cluster_entry
***********************************************************************/

class os_Cluster_entry {

  protected: // Construction
    os_Cluster_entry (os_Cluster_table&, os_cluster& cluster);
    os_Cluster_entry (os_Cluster_table&, os_unsigned_int32 cluster_number,
		      os_unsigned_int32 cluster_size);
    os_Cluster_entry ();
    ~os_Cluster_entry ();

  public: // Accessors
    os_boolean is_null () const;
    os_cluster& get_cluster () const;
    os_unsigned_int32 get_cluster_number () const;
    os_Cluster_table& get_cluster_table () const;
    /* TBD: any other useful accessors. */

  protected: // Modifiers
    void set_cluster_size (os_unsigned_int32 size);
    void set_offset_table (os_Offset_table&);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Cluster_table* cluster_table;
    os_unsigned_int32 cluster_number;
    os_unsigned_int32 cluster_size;
    os_Offset_table* offset_table;

  private: // Friends
    friend class os_Cluster_table;

  };
/*---*/

/***********************************************************************
  class os_Offset_table_value
***********************************************************************/

class os_Offset_table_value {

  public: // Construction
    os_Offset_table_value (const os_Dumper_reference& source,
			   const os_Dumper_reference& target,
			   const os_type& referent_type);
    os_Offset_table_value (const os_Dumper_reference& ignored_object);
    os_Offset_table_value ();
    ~os_Offset_table_value ();

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_unsigned_int32 target_database;
    os_unsigned_int32 target_segment;
    os_unsigned_int32 target_cluster;
    os_unsigned_int32 target_offset;
    os_unsigned_int32 object_size;

  private: // Friends
    friend class os_Offset_table;

  };


/***********************************************************************
  typedef os_Offset_table_values
***********************************************************************/

typedef os_Chained_list_block<os_Offset_table_value>
    os_Offset_table_value_block;
typedef os_Chained_list<os_Offset_table_value> os_Offset_table_values;
typedef os_Chained_list_cursor<os_Offset_table_value>
    os_Offset_table_value_cursor;


/***********************************************************************
  typedef os_In_segment_reference_fixups
***********************************************************************/

typedef os_Chained_list_block<os_In_segment_reference_fixup> 
    os_In_segment_reference_fixup_block;
typedef os_Chained_list<os_In_segment_reference_fixup> 
    os_In_segment_reference_fixups;
typedef os_Chained_list_cursor<os_In_segment_reference_fixup> 
    os_In_segment_reference_fixup_cursor;


/***********************************************************************
  typedef os_Offset_table_tree
***********************************************************************/

typedef _B_tree_node_pt<os_unsigned_int32, os_Offset_table_value, 64, 256> 
    os_Offset_table_nodes;
typedef _B_tree_pt<os_unsigned_int32, os_Offset_table_value, 64, 256> 
    os_Offset_table_entries;
typedef _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 
                               64, 256> os_Offset_table_cursor;


/***********************************************************************
  class os_Offset_table
***********************************************************************/

class os_Offset_table {

  public: // Construction

    /* Construct an os_Offset_table. */
    os_Offset_table (os_Cluster_entry&);

    /* Destruct this os_Offset_table. */
    ~os_Offset_table ();

  public: // Accessors

    /* Returns the os_Segment_entry associated with this os_Offset_table. */
    os_Cluster_entry& get_cluster_entry () const;

    /* Returns the os_Dumper_reference corresponding to the 
       given os_Dumper_reference's offset. If the returned
       os_Dumper_reference is incomplete, then the os_Segment_table
       is expected to fill in the missing segment information
       while the os_Database_table_persist is expected to fill in the
       missing database information */
    os_Dumper_reference find_reference
        (const os_Dumper_reference& reference) const;

    /* Test whether the given object should be ignored. */
    os_boolean is_ignored (const os_Dumper_reference& object) const;

  public: // Modifiers

    /* Insert a mapping from a source os_Dumper_reference to a
       target os_Dumper_reference into this os_Offset_table. Only
       the offset portion of the references are considered. */
    void insert (const os_Dumper_reference& source,
		 const os_Dumper_reference& target,
		 const os_type& referent_type);

    /* Insert a reference fixup into this os_Offset_table. */
    void insert (os_Reference_fixup_kind::Kind,
		 const os_Dumper_reference& reference,
		 const os_Dumper_reference& referent_original_location);

    /* Insert an object to ignore into the os_Offset_table. */
    void insert (const os_Dumper_reference& ignored_object);
    
    /* Insert an intra-segment generic os_Fixup into this os_Offset_table. */
    void insert (const os_Fixup& fixup);

    /* os_Fixup the given cluster's intra-cluster objects. */
    void fixup (os_segment& segment,
       os_cluster& cluster, os_unsigned_int32 database_number);

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Cluster_entry* cluster_entry;
    os_Offset_table_entries* mapping_entries;
    os_Offset_table_values mapping_values;
    os_Offset_table_entries* ignore_entries;
    os_Offset_table_values ignore_values;
    os_In_segment_reference_fixups* reference_fixups;
    os_Fixups* fixups;

  };


#endif /* DB_TAB_I_HH */
