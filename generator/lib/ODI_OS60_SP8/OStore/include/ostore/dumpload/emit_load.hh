/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef EMIT_LOADER_HH
#define EMIT_LOADER_HH

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

#include <fstream.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/mop.hh>

/***********************************************************************
  class os_Emit_loader_code
***********************************************************************/
class os_Emitter_state;

class os_Emit_loader_code
   {
public:
   os_Emit_loader_code(os_Traverser&, os_boolean);
   virtual ~os_Emit_loader_code();
   virtual void view(const os_schema& schema);
protected:
   enum filename
      {
      main,
      data_def,
      data_data,
      template_def,
      class_def,
      user_def,
      class_implementation,
      loader_header,
      loader_implementation,
      unix_makefile,
      nt_makefile,
      nt_project,
      class_schema
      };
   virtual char* filename(os_Emit_loader_code::filename file);
   virtual void output_ldrhdr();
   virtual void emit_loader_initialize();
   virtual void emit_loader_finalize();
   virtual void emit_class_info(const os_class_type &class_type,
      os_Emitter_state& given_state);
   virtual void emit_nt_makefile_info();
   virtual void emit_unix_makefile_info();
   virtual void initialize_nt_build_environment();
   virtual void set_nt_build_rules();
   virtual void initialize_unix_build_environment();
   virtual void set_unix_build_rules();
   virtual void create_unix_cleanup_rules();
// data
   ofstream *ldrdef00_h;
   ofstream *ldrdat00_h;
   ofstream *ldrtpl00_h;
   ofstream *ldrcls00_h;
   ofstream *ldrldr00_h;
   ofstream *ldrmai00_cpp;
   ofstream *ldrcls00_cpp;
   ofstream *ldrldr00_cpp;
   ofstream *ldrsch00_cpp;
   ofstream *makefile_w32;
   ofstream *makefile_unx;
private:
   int entry_size;
   int max_loaders;
   int member_offset;
   int base_offset;
   os_Traverser* traverser;
   os_boolean pseudo;
   };
#endif //EMIT_LOADER_HH





