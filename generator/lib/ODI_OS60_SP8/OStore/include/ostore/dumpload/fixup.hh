/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef FIXUP_HH
#define FIXUP_HH

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
#include <ostore/mop.hh>
#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/coll/lw.hh>


/***********************************************************************
  class os_Reference_fixup_kind
***********************************************************************/

class os_Reference_fixup_kind {
  public: // Subtypes
    enum Kind { 
	none, pointer, reference_local, reference_this_db,
	reference, reference_protected_local, reference_protected,
	soft_pointer32, soft_pointer64, root, class_key
      };
  };


/***********************************************************************
  class os_Reference_fixup
***********************************************************************/

template <class Details> class os_Reference_fixup {

  public: // Construction
    os_Reference_fixup (os_Reference_fixup_kind::Kind, 
			const os_Dumper_reference reference_to_fix,
			const os_Dumper_reference original_referent);
    os_Reference_fixup (const os_Dumper_reference original_referent,
                        char* type_name,char* root_name);
    os_Reference_fixup (const os_Dumper_reference dictionary,
                        const os_Dumper_reference key,
                        const os_Dumper_reference value);
    os_Reference_fixup (const os_Reference_fixup<Details>&);
    os_Reference_fixup ();

  public: // Accessors
    os_Dumper_reference get_reference_to_fix 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_reference_to_fix 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_reference_to_fix () const;

  public: // Modifiers
    os_Reference_fixup<Details>& operator = (const os_Reference_fixup<Details>&);

  public: // Actions
    void fix (os_unsigned_int32 database_number,
	      os_unsigned_int32 segment_number) const;
    void fix (os_unsigned_int32 database_number) const;
    void fix () const;

  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    /* TBD: figure out a means to encode these as a bit field. 
            --rick@odi.com */
    /*os_Reference_fixup_kind::Kind*/ os_unsigned_int32 kind;
    Details details;

  protected: // Actions
    void fix_reference (const os_Dumper_reference reference_to_fix,
			const os_Dumper_reference original_referent) const;

  };


/***********************************************************************
  class os_Fixup_details
***********************************************************************/

template <class Location> class os_Fixup_details {

  public: // Construction
    os_Fixup_details (const os_Dumper_reference reference_to_fix,
		      const os_Dumper_reference original_referent);
    os_Fixup_details (const os_Dumper_reference original_referent,
                      char* type_name,char* root_name);
    os_Fixup_details (const os_Dumper_reference dictionary,
		      const os_Dumper_reference key,
                      const os_Dumper_reference value);
    os_Fixup_details (const os_Fixup_details<Location>&);
    os_Fixup_details ();

  public: // Accessors
    os_Dumper_reference get_reference_to_fix 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_reference_to_fix 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_reference_to_fix () const;

    os_Dumper_reference get_original_referent 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_original_referent 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_original_referent () const;
    Location const* get_source() const {return &original_referent;}
  public: // Modifiers
    os_Fixup_details<Location>& operator = (const os_Fixup_details<Location>&);

  protected: // Embedded data
    Location reference_to_fix;
    Location original_referent;

  };


/***********************************************************************
  class os_In_segment_location
***********************************************************************/

class os_In_segment_location {

  public: // Construction
    os_In_segment_location (const os_Dumper_reference location);
    os_In_segment_location (const os_In_segment_location&);
    os_In_segment_location ();
    ~os_In_segment_location ();

  public: // Accessors
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_location () const;

  public: // Modifiers
    os_In_segment_location& operator = (const os_In_segment_location&);

  protected: // Embedded data
    os_unsigned_int32 cluster_number;
    os_unsigned_int32 offset;
    os_unsigned_int32 export_id;
  };


/***********************************************************************
  class os_In_database_location
***********************************************************************/

class os_In_database_location {

  public: // Construction
    os_In_database_location (const os_Dumper_reference location);
    os_In_database_location (const os_In_database_location&);
    os_In_database_location ();
    ~os_In_database_location ();

  public: // Accessors
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_location () const;

  public: // Modifiers
    os_In_database_location& operator = (const os_In_database_location&);

  protected: // Embedded data
    os_unsigned_int32 segment_number;
    os_unsigned_int32 cluster_number;
    os_unsigned_int32 offset;
    os_unsigned_int32 export_id;
  };


/***********************************************************************
  class os_Cross_database_location
***********************************************************************/

class os_Cross_database_location {

  public: // Construction
    os_Cross_database_location (const os_Dumper_reference location);
    os_Cross_database_location (const os_Cross_database_location&);
    os_Cross_database_location ();
    ~os_Cross_database_location ();

  public: // Accessors
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_location () const;

  public: // Modifiers
    os_Cross_database_location& operator = (const os_Cross_database_location&);

  protected: // Embedded data
    os_Dumper_reference reference;

  };


/***********************************************************************
  class os_Database_root_location
***********************************************************************/

class os_Database_root_location {

  public: // Construction
    os_Database_root_location (const os_Dumper_reference location,
       char* type_name,char* root_name);
    os_Database_root_location (const os_Dumper_reference location);
    os_Database_root_location (const os_Database_root_location&);
    os_Database_root_location ();
    ~os_Database_root_location ();

  public: // Accessors
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number,
	 os_unsigned_int32 segment_number) const;
    os_Dumper_reference get_location 
        (os_unsigned_int32 database_number) const;
    os_Dumper_reference get_location () const;
    char* get_root() const {return root_name_string;}
    char* get_type() const {return root_type_string;}

  public: // Modifiers
    os_Database_root_location& operator = (const os_Database_root_location&);

  protected: // Embedded data
    os_Dumper_reference reference;
    char* root_type_string;
    char* root_name_string;
  };


/***********************************************************************
  class os_Database_root_location
***********************************************************************/

class os_Database_class_key_location
   {
public: // Construction
   os_Database_class_key_location (const os_Dumper_reference dictionary,
       const os_Dumper_reference key,const os_Dumper_reference value);
   os_Database_class_key_location (const os_Dumper_reference location);
   os_Database_class_key_location (const os_Database_class_key_location&);
   os_Database_class_key_location ();
  ~os_Database_class_key_location ();

public: // Accessors
   os_Dumper_reference get_location 
       (os_unsigned_int32 database_number,
        os_unsigned_int32 segment_number) const;
   os_Dumper_reference get_location 
       (os_unsigned_int32 database_number) const;
   os_Dumper_reference get_location () const;
   os_dictionary* get_dictionary() const;
   void* get_key() const;
   void* get_value() const;

public: // Modifiers
   os_Database_class_key_location& operator = (const os_Database_class_key_location&);

protected: // Embedded data
   os_Dumper_reference dictionary;
   os_Dumper_reference key;
   os_Dumper_reference value;
   };


/***********************************************************************
  typdefs
***********************************************************************/

typedef os_Fixup_details<os_In_segment_location> os_In_segment_fixup_details;
typedef os_Fixup_details<os_In_database_location> os_In_database_fixup_details;
typedef os_Fixup_details<os_Cross_database_location>
    os_Cross_database_fixup_details;

typedef os_Fixup_details<os_Database_root_location>
    os_Database_root_fixup_details;
typedef os_Fixup_details<os_Database_class_key_location>
    os_Database_class_key_fixup_details;

typedef os_Reference_fixup<os_In_segment_fixup_details> 
    os_In_segment_reference_fixup;
typedef os_Reference_fixup<os_In_database_fixup_details> 
    os_In_database_reference_fixup;
typedef os_Reference_fixup<os_Cross_database_fixup_details> 
    os_Cross_database_reference_fixup;

typedef os_Reference_fixup<os_Database_root_fixup_details> 
    os_Database_root_reference_fixup;
typedef os_Reference_fixup<os_Database_class_key_fixup_details> 
    os_Database_class_key_reference_fixup;


/***********************************************************************
  class os_Fixup
***********************************************************************/

class os_Fixup : public os_virtual_behavior {

  public: // Construction
    os_Fixup (const os_class_type&, const os_Dumper_reference object_to_fix,
	      unsigned number_elements = 0);
    os_Fixup (const os_Fixup&);
    virtual ~os_Fixup ();
    virtual os_Fixup& duplicate (os_segment&) const = 0;
    virtual os_Fixup& duplicate (os_cluster&) const = 0;

  public: // Predicates
    virtual os_boolean is_handling_transactions () const;

  public: // Accessors
    const os_class_type& get_class_type () const;
    os_Dumper_reference get_object_to_fix () const;
    unsigned get_number_elements () const;

  public: // Actions
    virtual void fix () = 0;

  protected: // Embedded data
    os_Reference<const os_class_type> class_type;
    os_Dumper_reference object_to_fix;
    unsigned number_elements;

  };


#endif /* FIXUP_HH */
