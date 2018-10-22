/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REL_LOAD_HH
#define REL_LOAD_HH
/* Declarations of loader classes */
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

//-- Include Files --------------------------------

#include <ostore/ostore.hh>

#include <ostore/dumpload/loader.hh>
#include <ostore/dumpload/obj_loader.hh>
#include <ostore/dumpload/ref_fixup.hh>
#include <ostore/relat.hh>

/*********************/
/* Class: os_rel_single */
/*********************/
struct os_rel_single_data: public os_Type_data
   {
   /* Pointer member: value */
   os_Fixup_reference value;
   };
/*********************/
/* Class: os_rel_many */
/*********************/
struct os_rel_many_data: public os_Type_data
   {
   os_Fixup_reference value;
   };

/***********************************************************
class os_rel_single_info
***********************************************************/

class os_rel_single_loader;

class os_rel_single_info : public os_Type_info
   {
public: // Construction
   os_rel_single_info(os_rel_single_loader&, os_Loader_stream&, os_Object_info&, os_rel_single_data&);
   ~os_rel_single_info();
protected: // Embedded data
   os_rel_single_data* data;
private: // Friends
   friend class os_rel_single_loader;
   };

/***********************************************************
   class os_rel_single_loader
***********************************************************/

class os_rel_single_loader: public os_Type_loader
   {
public: // Construction
   os_rel_single_loader();
   virtual ~os_rel_single_loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& data, void* object,
                           os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static os_rel_single_loader& get();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

/***********************************************************
class os_rel_many_info
***********************************************************/

class os_rel_many_loader;

class os_rel_many_info : public os_Type_info
   {
public: // Construction
   os_rel_many_info(os_rel_many_loader&, os_Loader_stream&,
      os_Object_info&, os_rel_many_data&);
   ~os_rel_many_info();
protected: // Embedded data
   os_rel_many_data* data;
private: // Friends
   friend class os_rel_many_loader;
   };

/***********************************************************
   class os_rel_many_loader
***********************************************************/

class os_rel_many_loader: public os_Type_loader
   {
public: // Construction
   os_rel_many_loader();
   virtual ~os_rel_many_loader ();
public: // Actions
   virtual os_Loader_action* operator () (os_Loader_stream& stream,
           os_Loader_info &obj_info);
   virtual os_Loader_action* load (os_Loader_stream& stream,
           os_Type_data& given_data,os_boolean is_most_derived_class);
   virtual void construct (os_Type_data& data, void* object,
                           os_boolean is_most_derived_class);
   virtual void fixup (os_Type_data& given_data,
           void* object,os_boolean is_most_derived_class); /* constructed class object */
public: // Static accessor
    static os_rel_many_loader& get();
protected: // Actions
   virtual void create (os_Loader_info& given_info);
protected: // Member variables
   };

#endif 
