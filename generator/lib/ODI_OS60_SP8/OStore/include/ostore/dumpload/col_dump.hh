/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef COL_DUMP_HH
#define COL_DUMP_HH

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
#include <ostore/dumpload/fix_dump.hh>
#include <ostore/dumpload/col_spc.hh>

/* -- forward declarations ---------------------------------------------*/
class os_Fixup;

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Description: Registration of ObjectStore collection os_Dumpers
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class os_coll_dumper : public os_coll_specialization {

     public: // Actions
        virtual void operator () (const os_class_type& actual_type, void* object);
    
};

class os_query_dumper : public os_query_specialization {

   public: // Actions
      virtual void operator () (const os_class_type& actual_type, void* object);
};

class os_cursor_dumper : public os_cursor_specialization {
     
   public: // Actions
      virtual void operator () (const os_class_type& actual_type,void* object);
};

//extern class os_coll_dumper os_coll_dumper;
//extern class os_cursor_dumper os_cursor_dumper;
//extern class os_query_dumper os_query_dumper;

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Description: Registration of ObjectStore collection Planners
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class os_coll_planner : public os_Planning_action {
   public: 
      virtual void operator () (const os_type& actual_type, void* object);

   public: // Accessors 
      virtual os_boolean should_emit_loader (const os_class_type&) const;
};
                                
class os_coll_rep_planner : public os_Planning_action {
   public: 
      virtual void operator () (const os_type& actual_type, void* object);
      virtual void operator () (const os_type& actual_type, void* object,
                                os_int32 count);
   public: // Accessors 
      virtual os_boolean should_emit_loader (const os_class_type&) const;
      os_boolean should_walk(char * obj_name) const;
};
              
class os_coll_cursor_planner : public os_Planning_action {
   public: 
      virtual void operator () (const os_type& actual_type,void* object);
   public: // Accessors 
      virtual os_boolean should_emit_loader (const os_class_type&) const;
};

class os_coll_query_planner : public os_Planning_action {
   public: 
      virtual void operator () (const os_type& actual_type,void* object);
   public: // Accessors 
      virtual os_boolean should_emit_loader (const os_class_type&) const;
};


extern class os_coll_planner os_coll_planner;
extern class os_coll_rep_planner os_coll_rep_planner;
extern class os_coll_cursor_planner os_coll_cursor_planner;
extern class os_coll_query_planner os_coll_query_planner;

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Description: Registration of ObjectStore collection fixups
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

class os_cursor_fixup : public os_Fixup_dumper {

      public: // Construction
       os_cursor_fixup (os_Dumper_stream& stream,
                        const os_class_type& given_actual_class, 
			os_Dumper_reference& given_reference)
       : os_Fixup_dumper(stream, given_actual_class, given_reference)
       {}

       os_cursor_fixup (const os_cursor_fixup& given_fixup)
       : os_Fixup_dumper(given_fixup.get_stream(),
			 given_fixup.get_class_type(), 
			 given_fixup.get_object_to_fix(),
			 given_fixup.get_number_elements()) 
       {}

    public: // Actions
       virtual void dump_info () const;
       virtual os_Fixup& duplicate (os_cluster& cluster) const 
          { return *new(&cluster, os_cursor_fixup::get_os_typespec()) 
                        os_cursor_fixup(*this);
          }
       virtual os_Fixup& duplicate (os_segment& segment) const 
          { return *new(&segment, os_cursor_fixup::get_os_typespec()) 
                        os_cursor_fixup(*this);
          }
       virtual const char* get_name () const;

    public: // ObjectStore

       static os_typespec* get_os_typespec ();

};


class os_coll_element_fixup : public os_Fixup_dumper {
      public: // Construction
      os_coll_element_fixup (os_Dumper_stream& stream,
			     const os_class_type& given_actual_class, 
                             os_Dumper_reference& given_reference)
       : os_Fixup_dumper(stream, given_actual_class, given_reference)
       {}
      os_coll_element_fixup (const os_coll_element_fixup& given_fixup)
       : os_Fixup_dumper(given_fixup.get_stream(),
			 given_fixup.get_class_type(), 
			 given_fixup.get_object_to_fix(),
			 given_fixup.get_number_elements())
       {}

    public: // Actions
       virtual void dump_info () const;
       virtual os_Fixup& duplicate (os_cluster& cluster) const 
          { return *new(&cluster, os_coll_element_fixup::get_os_typespec()) 
                       os_coll_element_fixup(*this);
          }
       virtual os_Fixup& duplicate (os_segment& segment) const 
          { return *new(&segment, os_coll_element_fixup::get_os_typespec()) 
                       os_coll_element_fixup(*this);
          }
       virtual const char* get_name () const;
       virtual os_boolean is_handling_transactions () const;
    public: // ObjectStore
       static os_typespec* get_os_typespec ();

};

class os_coll_index_fixup : public os_Fixup_dumper {
   public: // Construction
      os_coll_index_fixup (os_Dumper_stream& stream,
			   const os_class_type& given_actual_class, 
                           os_Dumper_reference given_reference)
       : os_Fixup_dumper(stream, given_actual_class, given_reference)
       {}
        os_coll_index_fixup (const os_coll_index_fixup& given_fixup)
       : os_Fixup_dumper(given_fixup.get_stream(),
			 given_fixup.get_class_type(), 
			 given_fixup.get_object_to_fix(),
			 given_fixup.get_number_elements())
       {} 

    public: // Actions
       virtual void dump_info () const;
       virtual os_Fixup& duplicate (os_cluster& cluster) const 
          { return *new(&cluster, os_coll_index_fixup::get_os_typespec())
                        os_coll_index_fixup(*this);
          }
       virtual os_Fixup& duplicate (os_segment& segment) const 
          { return *new(&segment, os_coll_index_fixup::get_os_typespec())
                        os_coll_index_fixup(*this);
          }
       virtual const char* get_name () const;

    public: // ObjectStore
       static os_typespec* get_os_typespec ();

}; 

class os_coll_embed_fixup : public os_Fixup_dumper {
   public: // Construction
      os_coll_embed_fixup (os_Dumper_stream& stream,
			   const os_class_type& given_actual_class, 
                           os_Dumper_reference given_reference)
       : os_Fixup_dumper(stream, given_actual_class, given_reference)
       {}
        os_coll_embed_fixup (const os_coll_embed_fixup& given_fixup)
       : os_Fixup_dumper(given_fixup.get_stream(),
			 given_fixup.get_class_type(), 
			 given_fixup.get_object_to_fix(),
			 given_fixup.get_number_elements())
       {} 

    public: // Actions
       virtual void dump_info () const;
        virtual os_Fixup& duplicate (os_cluster& cluster) const 
          { return *new(&cluster, os_coll_embed_fixup::get_os_typespec()) 
                        os_coll_embed_fixup(*this);
          }
       virtual os_Fixup& duplicate (os_segment& segment) const 
          { return *new(&segment, os_coll_embed_fixup::get_os_typespec())
                        os_coll_embed_fixup(*this);
          }
       virtual const char* get_name () const;

    public: // ObjectStore
       static os_typespec* get_os_typespec ();

}; 

#endif /* COL_DUMP_HH */
