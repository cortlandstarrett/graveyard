/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DB_TABLE_HH
#define DB_TABLE_HH

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
#include <ostore/traverse/cacheref.hh>

#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/dumpload/fixup.hh>

#define DB_TABLE_FILENAME "db_table.dmp"

//-- Forward Definition ------------------------------------------------

class os_Database_table;
class os_Database_table_persist;
class os_Database_entry;
class os_Segment_table;
class os_Segment_entry;
class os_Cluster_table;
class os_Cluster_entry;
class os_Offset_table;
class os_Offset_pool;
class os_Reference_pool;


/* TBD: make sure this is the right type for time. */
typedef os_unixtime_t os_Time_value;


/***********************************************************************
  typedef os_Cross_database_reference_fixups
***********************************************************************/

typedef os_Chained_list_block<os_Cross_database_reference_fixup> 
    os_Cross_database_reference_fixup_block;
typedef os_Chained_list<os_Cross_database_reference_fixup> 
    os_Cross_database_reference_fixups;
typedef os_Chained_list_cursor<os_Cross_database_reference_fixup> 
    os_Cross_database_reference_fixup_cursor;


/***********************************************************************
  typedef os_Database_root_reference_fixups
***********************************************************************/

typedef os_Chained_list_block<os_Database_root_reference_fixup> 
    os_Database_root_reference_fixup_block;
typedef os_Chained_list<os_Database_root_reference_fixup> 
    os_Database_root_reference_fixups;
typedef os_Chained_list_cursor<os_Database_root_reference_fixup> 
    os_Database_root_reference_fixup_cursor;


/***********************************************************************
  typedef os_Database_class_key_reference_fixups
***********************************************************************/

typedef os_Chained_list_block<os_Database_class_key_reference_fixup> 
    os_Database_class_key_reference_fixup_block;
typedef os_Chained_list<os_Database_class_key_reference_fixup> 
    os_Database_class_key_reference_fixups;
typedef os_Chained_list_cursor<os_Database_class_key_reference_fixup> 
    os_Database_class_key_reference_fixup_cursor;


/***********************************************************************
  typedef os_Fixups
***********************************************************************/

typedef os_Chained_list_block<os_Fixup*> os_Fixup_block;
typedef os_Chained_list<os_Fixup*> os_Fixups;
typedef os_Chained_list_cursor<os_Fixup*> os_Fixup_cursor;


/***********************************************************************
  class os_Database_table
***********************************************************************/

class os_Database_table {

  public: // Construction

    /* Construct an os_Database_table of the given number of entries in
       the given work database. Entry 0 in the database table refers
       to the null database. */
    static os_Database_table& create (os_database& work_database,
				      unsigned number_entries,
				      unsigned growth_size = 5);

    /* Setup an os_Database_table from the given work_database. */
    static os_Database_table& setup (os_database& work_database);

    /* Destruct this os_Database_table. */
    void destroy ();

  public: // Static Accessors
    static os_Database_table& get ();

  public: // Accessors

    /* Returns the number of database entries in this table. */
    os_unsigned_int32 get_number_entries () const;

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

  public: // Modifiers

    /* Insert a os_Database_entry corresponding to the given database
       into this os_Database_table. */
    void insert (os_database& database);

    /* Insert an os_Segment_entry corresponding to the given
       segment into this os_Database_table. */
    void insert (os_segment& segment);

    /* Insert an os_Cluster_entry corresponding to the given
       segment into this os_Database_table. */
    void insert (os_cluster& cluster);

    /* Insert a os_Database_entry corresponding to the given path
       into this os_Database_table. */
    void insert (const char* path, 
		 os_unsigned_int32 database_size,
		 os_unsigned_int32 number_segments,
		 const char* release_name, 
		 os_Time_value last_modification_time);

    /* Insert a mapping from a source os_Dumper_reference to a
       target os_Dumper_reference into this os_Database_table. */
    void insert (const os_Dumper_reference& source,
                 const void* target,
		 const os_type& referent_type);

    /* Insert a reference fixup into this os_Database_table. */
    void insert (os_Reference_fixup_kind::Kind, 
		 const os_Dumper_reference& reference,
		 const os_Dumper_reference& referent_original_location);

    /* Insert a root fixup into this os_Database_table. */
    void insert (const os_Dumper_reference& referent_original_location,
                 char* type_name,
                 char* root_name);

    /* Insert a class key fixup into this os_Database_table. */
    void insert (const os_Dumper_reference& dictionary,
                 const os_Dumper_reference& key,
                 const os_Dumper_reference& value);

    /* Insert an object to ignore into the os_Database_table. */
    void insert (const os_Dumper_reference& ignored_object);
    
    /* Insert an intra-segment generic os_Fixup into this 
       os_Database_table. */
    void insert (os_segment&, const os_Fixup& fixup);

    /* Insert an intra-database generic os_Fixup into this 
       os_Database_table. */
    void insert (os_database&, const os_Fixup& fixup);

    /* Insert an inter-database generic os_Fixup into this 
       os_Database_table. */
    void insert (const os_Fixup& fixup);

    /* os_Fixup this table's inter-database objects. */
    void fixup ();

    /* os_Fixup the given database's intra-database objects. */
    void fixup (os_database& database);

    /* os_Fixup the given segment's intra-segment objects. */
    void fixup (os_segment& segment);

    /* Signal in finalization */
    void in_finalization();

  protected: // Embedded data
    os_Cached_reference<os_Database_table_persist> persistent_db_table;

  protected: // Construction

    /* Construct an os_Database_table of the given number of entries in
       the given work database. Entry 0 in the database table refers
       to the null database. */
    os_Database_table (os_database& work_database,
		       unsigned number_entries,
		       unsigned growth_size = 5);

    /* Construct an os_Database_table setting up from the given
       work_database. */
    os_Database_table (os_database& work_database);

    /* Destruct this os_Database_table. */
    ~os_Database_table ();
  public:
     /* warning.  This is a highly transient data item
        which has been added because the object loader
        does not return the object loaded. */
     static const void* last_object_inserted;

  };


#endif /* DB_TABLE_HH */
