/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef FIXUP_HC
#define FIXUP_HC
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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>

#include <ostore/ostore.hh>
#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/dumpload/fixup.hh>
#include <ostore/dumpload/ref_help.hh>
#include <ostore/msgsys/msgdmp.hh>
#include <ostore/dumpload/db_table.hh>

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Reference_fixup
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Method:      os_Reference_fixup<Details>::os_Reference_fixup
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>::os_Reference_fixup 
    (os_Reference_fixup_kind::Kind given_kind, 
     const os_Dumper_reference reference_to_fix,
     const os_Dumper_reference original_referent)
  : details(reference_to_fix, original_referent)
{
  kind = given_kind;
}




/***********************************************************************
  Method:      os_Reference_fixup<Details>::os_Reference_fixup
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>::os_Reference_fixup 
    (const os_Dumper_reference original_referent,
    char* type_name,char* root_name)
  : details(original_referent,type_name,root_name)
{
  kind = os_Reference_fixup_kind::root;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::os_Reference_fixup
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>::os_Reference_fixup 
    (const os_Dumper_reference dictionary,
    const os_Dumper_reference key,const os_Dumper_reference value)
  : details(dictionary,key,value)
{
  kind = os_Reference_fixup_kind::class_key;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::os_Reference_fixup
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>::os_Reference_fixup 
    (const os_Reference_fixup<Details>& given_fixup)
  : details(given_fixup.details)
{
  kind = given_fixup.kind;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::os_Reference_fixup
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>::os_Reference_fixup ()
  : details()
{
  kind = os_Reference_fixup_kind::none;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Dumper_reference os_Reference_fixup<Details>::get_reference_to_fix
  (os_unsigned_int32 database_number, os_unsigned_int32 segment_number) const
{
  os_Dumper_reference reference_to_fix
    = details.get_reference_to_fix(database_number, segment_number);
  return reference_to_fix;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Dumper_reference os_Reference_fixup<Details>::get_reference_to_fix
  (os_unsigned_int32 database_number) const
{
  os_Dumper_reference reference_to_fix
    = details.get_reference_to_fix(database_number);
  return reference_to_fix;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Dumper_reference os_Reference_fixup<Details>::get_reference_to_fix
  () const
{
  os_Dumper_reference reference_to_fix = details.get_reference_to_fix();
  return reference_to_fix;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
void os_Reference_fixup<Details>::fix
  (os_unsigned_int32 database_number, os_unsigned_int32 segment_number) const
{
  os_Dumper_reference reference_to_fix
    = details.get_reference_to_fix(database_number, segment_number);
  os_Dumper_reference original_referent
    = details.get_original_referent(database_number, segment_number);
  fix_reference(reference_to_fix, original_referent);
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
void os_Reference_fixup<Details>::fix
  (os_unsigned_int32 database_number) const
{
  os_Dumper_reference reference_to_fix
    = details.get_reference_to_fix(database_number);
  os_Dumper_reference original_referent
    = details.get_original_referent(database_number);
  fix_reference(reference_to_fix, original_referent);
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/
void os_Reference_fixup<os_Fixup_details<os_Database_root_location> >::fix
   () const
   {
   os_Database_table& database_table = os_Database_table::get();
   os_Dumper_reference new_referent_location
      = database_table.find_reference(details.get_original_referent());
   os_database& database =
      *os_database::of(new_referent_location.resolve());
   char* root_name = details.get_source()->get_root();
   os_database_root* root =
      database.create_root(root_name);
   delete root_name;
   char* type_name = details.get_source()->get_type();
   int len = strlen(type_name);
   /* Remove trailing * dumper put there in error */
   *(type_name + len - 1) = '\0';
   os_typespec atypespec(type_name);
   delete type_name;
   os_typespec* typespec = &atypespec;
   if (!strcmp(type_name,"void*"))
      typespec = 0;
   root->set_value(new_referent_location.resolve(),typespec);
   }

/***********************************************************************
  Method:      os_Reference_fixup<Details>::fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

void os_Reference_fixup<os_Fixup_details<os_Database_class_key_location> >::fix
   () const
   {
   os_dictionary* dictionary = details.get_source()->get_dictionary();
   void* const key = details.get_source()->get_key();
   void* const value = details.get_source()->get_value();
   dictionary -> insert(key,value);
   delete key;
   }

template <class Details>
void os_Reference_fixup<Details>::fix () const
{
  os_Dumper_reference reference_to_fix = details.get_reference_to_fix();
  os_Dumper_reference original_referent = details.get_original_referent();
  fix_reference(reference_to_fix, original_referent);
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::operator =
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
os_Reference_fixup<Details>& os_Reference_fixup<Details>::operator = 
    (const os_Reference_fixup<Details>& given_fixup)
{
  os_Reference_fixup<Details>& fixup
      = *::new(this) os_Reference_fixup<Details>(given_fixup);
  return fixup;
}


/***********************************************************************
  Method:      os_Reference_fixup<Details>::fix_reference
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Details>
void os_Reference_fixup<Details>::fix_reference 
    (const os_Dumper_reference reference_to_fix,
     const os_Dumper_reference original_referent_location) const
   {
   switch (kind)
      {
   case os_Reference_fixup_kind::pointer:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "Pointer at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }
      void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
      *pointer_to_fix_address = new_referent_location;
      }
      break;
   case os_Reference_fixup_kind::soft_pointer32:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "Soft_pointer32 at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }   
      /* TBD: Consider whether or not to test reference_to_fix is persistent? */
      os_soft_pointer32_initializer* reference_to_fix_address
         = (os_soft_pointer32_initializer*)reference_to_fix.resolve();
      reference_to_fix_address->initialize(new_referent_location);
      }
      break;
   case os_Reference_fixup_kind::soft_pointer64:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "soft_pointer64 at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }   
      /* TBD: Consider whether or not to test reference_to_fix is persistent? */
      os_soft_pointer64_initializer* reference_to_fix_address
         = (os_soft_pointer64_initializer*)reference_to_fix.resolve();
      reference_to_fix_address->initialize(new_referent_location);
      }
      break;
   case os_Reference_fixup_kind::root:
      {
      assert(0);
      }
      break;
   case os_Reference_fixup_kind::reference_local:
      break;
   case os_Reference_fixup_kind::reference_this_db:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "Reference at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }
      os_reference_this_DB_initializer* reference_to_fix_address
         = (os_reference_this_DB_initializer*)reference_to_fix.resolve();
      reference_to_fix_address->initialize(new_referent_location);
      }
      break;
    case os_Reference_fixup_kind::reference:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "Reference at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }
      os_reference_initializer* reference_to_fix_address
         = (os_reference_initializer*)reference_to_fix.resolve();
      reference_to_fix_address->initialize(new_referent_location);
      }
      break;
   case os_Reference_fixup_kind::reference_protected_local:
      break;
   case os_Reference_fixup_kind::reference_protected:
      {
      os_Database_table& database_table = os_Database_table::get();
      os_Dumper_reference new_referent_location
         = database_table.find_reference(original_referent_location);
      if ( ! new_referent_location.is_valid())
         {
         void** pointer_to_fix_address = (void**)reference_to_fix.resolve();
         *pointer_to_fix_address = 0;
         os_Dumper_messages::OS_WARN(os_Dumper_messages::reference_fixup_fix);
         char buffer[128];
         strcpy(buffer,reference_to_fix.get_string());
         cout  << "Reference at " << *pointer_to_fix_address << " (" << buffer
               << ") points to a non-existent object.";
         break;
         }
      /* TBD this will not work in over address space cases because of resolve */
      os_reference_initializer* reference_address
         = new os_reference_initializer();
      reference_address->initialize(new_referent_location);
      os_reference_protected* reference_to_fix_address
         = (os_reference_protected*)reference_to_fix.resolve();
      *reference_to_fix_address
         = ((os_reference)(*reference_address)).resolve();
      delete reference_address;
      }
      break;
   default:
      os_Dumper_messages::OS_FATAL(os_Dumper_messages::reference_fixup_fix_unknown,kind);
      break;
      }
   }


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Fixup_details
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Method:      os_Fixup_details<Location>::os_Fixup_details
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Fixup_details<Location>::os_Fixup_details 
    (const os_Dumper_reference given_reference_to_fix,
     const os_Dumper_reference given_original_referent)
  : reference_to_fix(given_reference_to_fix),
    original_referent(given_original_referent)
{
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::os_Fixup_details
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

os_Fixup_details<os_Database_root_location>::os_Fixup_details 
    (const os_Dumper_reference given_original_referent,
     char* type_name,char* root_name)
  : original_referent(given_original_referent,type_name,root_name)
{
}

template <class Location>
os_Fixup_details<Location>::os_Fixup_details 
    (const os_Dumper_reference given_original_referent,
     char* type_name,char* root_name)
  : original_referent(given_original_referent)
{
}



/***********************************************************************
  Method:      os_Fixup_details<Location>::os_Fixup_details
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

os_Fixup_details<os_Database_class_key_location>::os_Fixup_details 
    (const os_Dumper_reference dictionary,
     const os_Dumper_reference key,
     const os_Dumper_reference value)
  : original_referent(dictionary,key,value)
{
}

template <class Location>
os_Fixup_details<Location>::os_Fixup_details 
    (const os_Dumper_reference dictionary,
     const os_Dumper_reference key,
     const os_Dumper_reference value)
  : original_referent(dictionary)
{
}



/***********************************************************************
  Method:      os_Fixup_details<Location>::os_Fixup_details
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Fixup_details<Location>::os_Fixup_details 
    (const os_Fixup_details<Location>& given_details)
  : reference_to_fix(given_details.reference_to_fix),
    original_referent(given_details.original_referent)
{
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::os_Fixup_details
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Fixup_details<Location>::os_Fixup_details ()
  : reference_to_fix(), original_referent()
{
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_reference_to_fix 
    (os_unsigned_int32 database_number,
     os_unsigned_int32 segment_number) const
{
  return reference_to_fix.get_location(database_number, segment_number);
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_reference_to_fix 
    (os_unsigned_int32 database_number) const
{
  return reference_to_fix.get_location(database_number);
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_reference_to_fix
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_reference_to_fix () const
{
  return reference_to_fix.get_location();
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_original_referent
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_original_referent 
    (os_unsigned_int32 database_number,
     os_unsigned_int32 segment_number) const
{
  return original_referent.get_location(database_number, segment_number);
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_original_referent
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_original_referent 
    (os_unsigned_int32 database_number) const
{
  return original_referent.get_location(database_number);
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::get_original_referent
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Dumper_reference os_Fixup_details<Location>::get_original_referent () const
{
  return original_referent.get_location();
}


/***********************************************************************
  Method:      os_Fixup_details<Location>::operator =
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Location>
os_Fixup_details<Location>& os_Fixup_details<Location>::operator =
    (const os_Fixup_details<Location>& given_details)
{
  os_Fixup_details<Location>& details 
      = *::new(this) os_Fixup_details<Location>(given_details);
  return details;
}


#endif
