/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MSGDMPLOD_HH_
#define _MSGDMPLOD_HH_

#include <ostore/msgsys/msgsys.hh>
#include <ostore/msgsys/msgtrvrs.hh>


class os_Dumpload_messages : public os_Message
   {
public:
   enum messageid
      {
      bad_initialization = os_Traverser_messages::next_available_message,
      bad_initialization_get,
      null_segment_table,
      null_database_entry,
      insert_null_segment_table,
      database_table_check_selection,
      get_database_null_database_entry,
      find_reference_null_offset_table,
      insert_null_offset_table,
      segment_table_check_selection,
      null_segment,
      offset_table_offset,
      setup_application_schema_path,
      OS_DECLARE_SUBSYSTEM_CHAINING(os_Traverser_messages)
      };
   OS_DECLARE_SUBSYSTEM_MESSAGES(os_Dumpload_messages);
   };

#endif /* _MSGDMPLOD_HH_ */
