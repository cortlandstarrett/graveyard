/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MSGDMP_HH_
#define _MSGDMP_HH_

#include <ostore/msgsys/msgsys.hh>
#include <ostore/msgsys/msgdmplod.hh>


class os_Dumper_messages : public os_Message
   {
public:
   enum messageid
      {
      dumper_reference_transient = os_Dumpload_messages::next_available_message,
      unimplemented,
      dumper_reference_invalid,
      make_reference_extension_reference_invalid,
      make_reference_extension_database,
      make_reference_extension_segment,
      get_database_invalid,
      get_segment_invalid,
      set_database_number,
      pre_action_kind,
      get_location,
      get_location_database_only,
      get_location_none,
      dump_type_unknown,
      loader_name_unknown,
      cannot_find_load_main,
      cannot_find_makefile,
      no_base_element_type,
      unrecognized_filename_requested,
      dump_coll_elements_key,
      get_dict_key_type,
      dump_coll_range,
      dump_key_value,
      get_first_element,
      work_database_uninitialized,
      dumper_dump_type,
      dumper_dump_kind,
      dumper_actions_get_dumper,
      get_base_type,
      planning_action_get_dumper,
      get_traverser,
      reference_fixup_fix,
      reference_fixup_fix_unknown,
      relationship_unknown,
      OS_DECLARE_SUBSYSTEM_CHAINING(os_Dumpload_messages)
      };
   OS_DECLARE_SUBSYSTEM_MESSAGES(os_Dumper_messages);
   };

#endif /* _MSGDMP_HH_ */
