/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef COL_SPC_HH
#define COL_SPC_HH

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


/* -- include files ---------------------------------------------*/
#include <ostore/dumpload/dumper.hh>
#include <ostore/dumpload/planner.hh>
#include <ostore/dumpload/fix_dump.hh>
#include <ostore/dumpload/coll_dl.hh>

/* define loader names */
#define OS_COLL_LOADER       "os_coll"
#define OS_CURSOR_LOADER     "os_cursor"
#define OS_COLL_QUERY_LOADER "os_coll_query"

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Description: Registration of ObjectStore collection os_Dumpers
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class os_coll_specialization : public os_Dumper_specialization {

     public: // Accessors 
        virtual os_boolean should_use_default_constructor
	    (const os_class_type& class_type) const;
	virtual char* get_specialization_name
	    (const os_class_type& class_type) const;
        virtual char* get_marking_string
            (const os_class_type&) const;
        virtual char* get_instantiation_string
            (const os_class_type& actual_class) const;
    private: //odds and ends
	    char* create_marking_string(char * name, int type) const;
};

class os_query_specialization : public os_Dumper_specialization {

   public: // Accessors   
      virtual os_boolean should_use_default_constructor
          (const os_class_type& class_type) const;
      virtual char* get_specialization_name
          (const os_class_type& class_type) const;
};

class os_cursor_specialization : public os_Dumper_specialization {
     
   public: // Accessors
      virtual os_boolean should_use_default_constructor
          (const os_class_type& class_type) const;
      virtual char* get_specialization_name
          (const os_class_type& class_type) const; 
};

#endif /* COL_SPC_HH */
