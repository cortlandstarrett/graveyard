/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MSGLOD_HH_
#define _MSGLOD_HH_

#include <ostore/msgsys/msgsys.hh>
#include <ostore/msgsys/msgdmplod.hh>


class os_Loader_messages : public os_Message
   {
public:
   enum messageid
      {
      uninitialized = os_Dumpload_messages::next_available_message,
      unimplemented,
      loader_uninitialized,
      work_database_uninitialized,
      database_uninitialized,
      segment_uninitialized,
      no_current,
      no_header,
      translate_unexpected_input,
      unexpected_input,
      entry_uninitialized,
      table_uninitialized,
      cache_size,
      bad_cast,
      bad_action_stack,
      bad_info_cast,
      unexpected_eof,
      excessive_input,
      pop_string_buffer,
      unimplemented_type,
      get_loader_type,
      bad_parse,
      no_type,
      type_loader_invocation,
      create_segment,
      cluster_loader_input,
      bind_input,
      bind_input_format,
      bind_input_failed,
      bind_input_expecting,
      bind_unexpected_input,
      col_load_unexpected_input,
      cursor_load_unexpected_input,
      coll_index_fixup_data_unexpected_input,
      coll_query_data_unexpected_input,
      coll_element_fixup_data_unexpected_input,
      coll_embed_fixup_data_unexpected_input,
      cursor_load_new_ref,
      coll_element_fixup_load_new_ref,
      cursor_fixup_loader_fixup_original,
      cursor_fixup_loader_fixup_replaced,
      coll_index_fixup_loader_fixup_original,
      coll_index_fixup_loader_fixup_replaced,
      coll_element_fixup_loader_fixup_original,
      coll_element_fixup_loader_fixup_replaced,
      coll_embed_fixup_loader_fixup_embedded,
      coll_embed_fixup_loader_fixup_outofline,
      collection_load_assign,
      collection_load_get_key_value_original,
      collection_load_get_key_value_key,
      collection_load_get_key_value_unexpected,
      root_entry_loader_create,
      root_entry_info_get_translated,
      fixup_loader_original,
      fixup_loader_replacing,
      fixup_loader_create,
      type_fixup_loader_original_array,
      loader_translated_info,
      loader_translated_info_initial_database,
      loader_translated_info_initial_segment,
      loader_translated_info_initial_cluster,
      loader_translated_info_original_location,
      loader_translated_info_current_database,
      loader_translated_info_current_segment,
      loader_translated_info_current_cluster,
      loader_translated_info_set_orignal_location,
      loader_stream_get,
      object_loader_create,
      object_info_get_original_segment,
      object_info_get_replacing_segment,
      object_info_get_original_database,
      object_info_get_replacing_database,
      object_info_get_loader_translated_info,
      type_info_get_original_location,
      type_info_get_replacing_location,
      type_info_get_replacing_segment,
      type_info_get_replacing_database,
      type_info_set_replacing_location,
      type_info_get_type,
      type_info_get_type_type,
      type_info_get_object_info,
      reference_data_representation,
      segment_loader_create_database,
      segment_loader_create_segment,
      segment_info_get_translated_info,
      cluster_loader_create_segment,
      cluster_loader_create_cluster,
      cluster_info_get_translated_info,
      input_value_get_value_storage,
      input_value_bind,
      input_value_get_kind,
      input_value_get_kind_string,
      relationship,
      relationship_single,
      relationship_many,
      instantiate_abstract,
      input_file_missing,
      schema_dump_file_not_found,
      preferred_schema_uninitialized,
      preferred_schema_DB_not_found,      
      OS_DECLARE_SUBSYSTEM_CHAINING(os_Dumpload_messages)
      };
   OS_DECLARE_SUBSYSTEM_MESSAGES(os_Loader_messages);
   };

OS_MSGS_EXCEPTION(tix_values_unexpected_input);
extern os_Message_exception values_unexpected_input;


#endif /* _MSGLOD_HH_ */
