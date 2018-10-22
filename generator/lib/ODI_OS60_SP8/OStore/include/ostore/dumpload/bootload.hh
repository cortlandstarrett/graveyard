/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef BOOTLOAD_HH
#define BOOTLOAD_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work           *
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

#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/dumpload/loader.hh>
#include <ostore/dumpload/obj_loader.hh>


//-- Forward Declarations ----------------------------------------------

class _OST_hash__unsignedint__void___info;
struct _OST_hash__unsignedint__void___data;

class _Pvts;
class _Pvts_info;
struct _Pvts_data;

struct _Per_segment_data_data;
class _Per_segment_data 
{ public: 
    char _os_pad_0;
    _Per_segment_data(struct _Per_segment_data_data&); 
};
class _Per_segment_data_info;

struct _Per_segment_reference_db_data;
class _Per_segment_reference_db
{ public: 
    char _os_pad_0;
    _Per_segment_reference_db(struct _Per_segment_reference_db_data&); 
};
class _Per_segment_reference_db_info;

class _Hash_table_entry__unsignedint__void___info;
struct _Hash_table_entry__unsignedint__void___data;

/*********************/
/* Class: _OST_hash<unsigned int,void*> */
/*********************/
struct _OST_hash__unsignedint__void___data: public os_Type_data
   {
   _OST_hash__unsignedint__void___data();
   /* Pointer member: tab */
   os_Fixup_reference tab;
   int size;
   int regrow_threshold;
   int entry_count;
   };

/*********************/
/* Class: _Pvts */
/*********************/
struct _Pvts_data: public os_Type_data
   {
   _Pvts_data();
   /* Pointer member: typespec */
   os_Fixup_reference typespec;
   unsigned int type_number;
   };

/*********************/
/* Class: _Per_segment_data */
/*********************/
struct _Per_segment_data_data: public os_Type_data
   {
   _Per_segment_data_data();
   unsigned int version;
   /* Pointer member: cursor_table */
   os_Fixup_reference cursor_table;
   /* Pointer member: pool */
   os_Fixup_reference pool;
   /* Pointer member: psrd */
   os_Fixup_reference psrd;
   /* Pointer member: reserved_1 */
   os_Fixup_reference reserved_1;
   /* Pointer member: reserved_2 */
   os_Fixup_reference reserved_2;
   /* Pointer member: reserved_3 */
   os_Fixup_reference reserved_3;
   /* Pointer member: reserved_4 */
   os_Fixup_reference reserved_4;
   };

/*********************/
/* Class: _Per_segment_reference_db */
/*********************/
struct _Per_segment_reference_db_data: public os_Type_data
   {
   _Per_segment_reference_db_data();
   unsigned int obj_counter;
   /* Class member: hash_table, Class: _OST_hash<unsigned int,void*> */
   _OST_hash__unsignedint__void___data hash_table;
   };

/*********************/
/* Class: _Hash_table_entry<unsigned int,void*> */
/*********************/
struct _Hash_table_entry__unsignedint__void___data: public os_Type_data
   {
   _Hash_table_entry__unsignedint__void___data();
   unsigned int key;
   /* Pointer member: value */
   os_Fixup_reference value;
   char status;
   /* Array member: _os_pad_ */
   char _os_pad_[3];
   };



/***********************************************************
class _OST_hash__unsignedint__void___info
***********************************************************/

class _OST_hash__unsignedint__void___loader;

class _OST_hash__unsignedint__void___info : public os_Type_info
   {
public: // Construction
   _OST_hash__unsignedint__void___info(_OST_hash__unsignedint__void___loader&, os_Loader_stream&, os_Object_info&, _OST_hash__unsignedint__void___data&);
   ~_OST_hash__unsignedint__void___info();
public: // Accessors
   virtual os_Loader_action::Kind get_kind () const;
protected: // Embedded data
   _OST_hash__unsignedint__void___data* data;
private: // Friends
   friend class _OST_hash__unsignedint__void___loader;
   };

/***********************************************************
   class _OST_hash__unsignedint__void___loader
***********************************************************/

class _OST_hash__unsignedint__void___loader: public os_Type_loader
   {
public: // Construction
   _OST_hash__unsignedint__void___loader();
   virtual ~_OST_hash__unsignedint__void___loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static _OST_hash__unsignedint__void___loader& get ();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

/***********************************************************
class _Pvts_info
***********************************************************/

class _Pvts_loader;

class _Pvts_info : public os_Type_info
   {
public: // Construction
   _Pvts_info(_Pvts_loader&, os_Loader_stream&, os_Object_info&, _Pvts_data&);
   ~_Pvts_info();
public: // Accessors
   virtual os_Loader_action::Kind get_kind () const;
protected: // Embedded data
   _Pvts_data* data;
private: // Friends
   friend class _Pvts_loader;
   };

/***********************************************************
   class _Pvts_loader
***********************************************************/

class _Pvts_loader: public os_Type_loader
   {
public: // Construction
   _Pvts_loader();
   virtual ~_Pvts_loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static _Pvts_loader& get ();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

/***********************************************************
class _Per_segment_data_info
***********************************************************/

class _Per_segment_data_loader;

class _Per_segment_data_info : public os_Type_info
   {
public: // Construction
   _Per_segment_data_info(_Per_segment_data_loader&, os_Loader_stream&, os_Object_info&, _Per_segment_data_data&);
   ~_Per_segment_data_info();
public: // Accessors
   virtual os_Loader_action::Kind get_kind () const;
protected: // Embedded data
   _Per_segment_data_data* data;
private: // Friends
   friend class _Per_segment_data_loader;
   };

/***********************************************************
   class _Per_segment_data_loader
***********************************************************/

class _Per_segment_data_loader: public os_Type_loader
   {
public: // Construction
   _Per_segment_data_loader();
   virtual ~_Per_segment_data_loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Object_info& info,unsigned number_elements);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static _Per_segment_data_loader& get ();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

/***********************************************************
class _Per_segment_reference_db_info
***********************************************************/

class _Per_segment_reference_db_loader;

class _Per_segment_reference_db_info : public os_Type_info
   {
public: // Construction
   _Per_segment_reference_db_info(_Per_segment_reference_db_loader&, os_Loader_stream&, os_Object_info&, _Per_segment_reference_db_data&);
   ~_Per_segment_reference_db_info();
public: // Accessors
   virtual os_Loader_action::Kind get_kind () const;
protected: // Embedded data
   _Per_segment_reference_db_data* data;
private: // Friends
   friend class _Per_segment_reference_db_loader;
   };

/***********************************************************
   class _Per_segment_reference_db_loader
***********************************************************/

class _Per_segment_reference_db_loader: public os_Type_loader
   {
public: // Construction
   _Per_segment_reference_db_loader();
   virtual ~_Per_segment_reference_db_loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Object_info& info,unsigned number_elements);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static _Per_segment_reference_db_loader& get ();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

/***********************************************************
class _Hash_table_entry__unsignedint__void___info
***********************************************************/

class _Hash_table_entry__unsignedint__void___loader;

class _Hash_table_entry__unsignedint__void___info : public os_Type_info
   {
public: // Construction
   _Hash_table_entry__unsignedint__void___info(_Hash_table_entry__unsignedint__void___loader&, os_Loader_stream&, os_Object_info&, _Hash_table_entry__unsignedint__void___data&);
   ~_Hash_table_entry__unsignedint__void___info();
public: // Accessors
   virtual os_Loader_action::Kind get_kind () const;
protected: // Embedded data
   _Hash_table_entry__unsignedint__void___data* data;
private: // Friends
   friend class _Hash_table_entry__unsignedint__void___loader;
   };

/***********************************************************
   class _Hash_table_entry__unsignedint__void___loader
***********************************************************/

class _Hash_table_entry__unsignedint__void___loader: public os_Type_loader
   {
public: // Construction
   _Hash_table_entry__unsignedint__void___loader();
   virtual ~_Hash_table_entry__unsignedint__void___loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Object_info& info,unsigned number_elements);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static _Hash_table_entry__unsignedint__void___loader& get ();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };


#endif /* BOOTLOAD_HH */
