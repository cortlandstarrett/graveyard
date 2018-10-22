/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_ERRORS
#define CLIENT_INTERFACE_ERRORS
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/except.hh>

/* Exceptions */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_hardware);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_alignment);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_trans_not_abortable);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_not_allowed_in_abort_only);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_transient);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_directory_exists);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_wrong_version);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_wrong_version_db_needs_upgrade);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_wrong_version_db_needs_multiple_upgrade);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_wrong_version_app_needs_upgrade);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_wrong_version_incompatible);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_validation_failed);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_validation_error);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_database);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_trans_wrong_type);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_not_assigned);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_no_such_object);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_unknown_pointer);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cross_db_pointer);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_transient_pointer);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_address_space_full);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_operator_new_args);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_null_pointer);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_typespec_mismatch);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_write_permission_denied);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_uninitialized);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_architecture_mismatch);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_root_exists);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_deref_transient_pointer);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_too_many_retries);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_network_failure);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_deletion);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_export_id);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_export_schema_segment);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_reference_assignment);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_abort_committed);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_commit_with_children);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_explicit_commit_stack_txn);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_commit_aborted);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_commit_abort_only);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_checkpoint_committed);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_checkpoint_aborted);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_checkpoint_not_inner);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_checkpoint_not_top_level);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_checkpoint_prepared);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cluster_mismatch);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_reference_not_found);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_reference_to_transient);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_allocation_too_big);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cannot_open_application_schema);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_absorption_not_allowed);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_insufficient_virtual_memory);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_root_value);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_reference_syntax);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_broken);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_type_not_found);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_evict_wired_segment);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_delete);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_string_too_long);

_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_network);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_cant_connect);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_no_server);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_host_down);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_connection_refused);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_connect_timeout);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_server_address_in_use);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_no_such_host);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_connection_closed);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_datagram_error);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_no_service_on_net);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_net_indigestable_pna);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_user_aborted_simple_authentication);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_authentication_failure);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cursor_invalid);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cursor_at_end);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cursor_not_at_object);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_segment_transient);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cluster_transient);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_default_segment);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_default_cluster);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_event_info);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_generic_event);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_key);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_illegal_acquire_lock);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mvcc_nested);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_object_init);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_unimplemented_feature);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cannot_affiliate);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_explicit_abort);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_database_open);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_xa);
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_allocator_framework);

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_metadata);

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_ERRORS */
