/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DMP_REF_HH
#define DMP_REF_HH

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
//#include <llpl_types.hh>


//-- Forward Declarations ----------------------------------------------

class os_Offset_table;
class os_Fixup_reference;


/***********************************************************************
  class os_Dumper_reference
***********************************************************************/

/* TBD: Determine which exceptions should be raised 
        from the following. --rick@odi.com */

class os_Dumper_reference {
   public:
      static const os_unsigned_int32 no_export;
   public: // Construction
    os_Dumper_reference (const void*);
    os_Dumper_reference (os_unsigned_int32 database_number,
         os_unsigned_int32 segment_number,
         os_unsigned_int32 cluster_number,
         os_unsigned_int32 offset,
         os_unsigned_int32 given_export_id);
    os_Dumper_reference (const os_Dumper_reference&);
    os_Dumper_reference ();
    ~os_Dumper_reference ();

  public: // Accessors

    /* Resolve this reference into an address and return the result. */
    void* resolve() const;

    /**/
    os_boolean operator == (const os_Dumper_reference&) const;

    /**/
    os_boolean operator < (const os_Dumper_reference&) const;

    /**/
    os_boolean operator > (const os_Dumper_reference&) const;

    /**/
    os_boolean operator != (const os_Dumper_reference&) const;

    /**/
    os_boolean operator >= (const os_Dumper_reference&) const;

    /**/
    os_boolean operator <= (const os_Dumper_reference&) const;

    /**/
    os_boolean operator ! () const;

    /**/
    operator void*() const { return resolve(); }

    /* Get the database containing the referent of this reference. */
    os_database* get_database () const;

    /* Get the database table number of the database containing the
       referent of this reference. */
    os_unsigned_int32 get_database_number () const;

    /* Get the segment containing the referent of this reference. */
    os_segment* get_segment () const;

    /* Get the cluster containing the referent of this reference. */
    os_cluster* get_cluster () const;

    /* Get the segment number of the segment containing the
       referent of this reference. */
    os_unsigned_int32 get_segment_number () const;

    /* Get the cluster number of the cluster containing the
       referent of this reference. */
    os_unsigned_int32 get_cluster_number () const;

    /* Get the offset of the referent of this reference within
       its segment. */
    os_unsigned_int32 get_offset () const;

    /* Get the flags for this reference. */
    os_unsigned_int32 get_export_id () const;

    /* Get the size of the containing cluster */
    os_unsigned_int32 get_cluster_size () const;

    /* Return the reference's value as an encoded string. */
    const char* get_string () const;

    /* Return the reference's value as an encoded string with
       the database number replaced with the database path. */
    // TBD: const char* get_string_with_path () const;

    /* Returns true if this os_Dumper_reference is completely
       valid; otherwise returns false. */
    os_boolean is_valid () const;

  public: // Modifiers
    
    /**/
    os_Dumper_reference& operator = (const os_Dumper_reference&);

    /**/
    os_Dumper_reference& operator = (void* object);

    /* Load the reference using the given encoded string. */
    void load (const char* encoded_string);
    static os_boolean parse(const char* string,
      os_unsigned_int32& db_id, os_unsigned_int32& seg_id,
      os_unsigned_int32& clus_id,os_unsigned_int32& offset,
      os_unsigned_int32& export_id);

    /* Set the flags of this reference to the given. */
    void set_export_id (os_unsigned_int32 export_id);


  public: // Static data
    static const os_unsigned_int32 invalid_number;

  private: // Embedded data
    os_unsigned_int32 database_number;
    os_unsigned_int32 segment_number;
    os_unsigned_int32 cluster_number;
    os_unsigned_int32 offset;
    os_unsigned_int32 export_id;

  protected: // Modifiers
    
    /* Set the database of this reference to the given. */
    void set_database (os_database&);

    /* Set the database table number of this reference to the given. */
    void set_database_number (os_unsigned_int32 number);

    /* Set the segment of this reference to the given. */
    void set_segment (os_segment&);

    /* Set the cluster of this reference to the given. */
    void set_cluster (os_cluster&);

    /* Set the segment number of this reference to the given. */
    void set_segment_number (os_unsigned_int32 number, os_database* = 0);

    /* Set the cluster of this reference to the given. */
    void set_cluster_number (os_unsigned_int32 cluster);

    /* Set the offset of this reference to the given. */
    void set_offset (os_unsigned_int32 offset);

  private: // ObjectStore
    static os_typespec* get_os_typespec ();

  private: // Friends
    friend class os_Database_table_persist;
    friend class os_Segment_table;
    friend class os_Cluster_table;
    friend class os_Offset_table;

  };


/***********************************************************************
  class os_Fixup_reference
***********************************************************************/

class os_Fixup_reference : public os_Dumper_reference {

  public: // Construction
    os_Fixup_reference (const void*);
    os_Fixup_reference (os_unsigned_int32 database_number,
			os_unsigned_int32 segment_number,
			os_unsigned_int32 cluster_number,
			os_unsigned_int32 offset,
			os_unsigned_int32 export_id);
    os_Fixup_reference (const os_Dumper_reference&);
    os_Fixup_reference (const os_Fixup_reference&);
    os_Fixup_reference ();
    ~os_Fixup_reference ();

  public: // Accessors

    /* Resolve this reference into an address and return the result. */
    void* resolve() const;

    /**/
    operator void*() const { return resolve(); }

    /* Returns true if this os_Dumper_reference is completely
       valid; otherwise returns false. */
    os_boolean is_valid () const;

  public: // Modifiers
    
    /**/
    os_Fixup_reference& operator = (const os_Fixup_reference&);

    /**/
    os_Fixup_reference& operator = (const os_Dumper_reference&);

    /**/
    os_Fixup_reference& operator = (void* object);

    /* Load the reference using the given encoded string. */
    void load (const char* encoded_string);

    /* If the os_Dumper_reference portion of this os_Fixup_reference
       is valid, then make the os_Fixup_reference valid. */
    void set_valid ();

  protected: // Embedded data
    os_boolean valid;

  private: // ObjectStore
    static os_typespec* get_os_typespec ();

  };


#endif /* DMP_REF_HH */

