/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef MSGTRVRS_H_
#define MSGTRVRS_H_

#include <ostore/msgsys/msgexcpt.hh>
#include <ostore/msgsys/msgsys.hh>


class os_Traverser_messages : public os_Message
   {
public:
   enum messageid
      {
      bad_initialization = os_Message::next_available_message,
      unimplemented,
      bad_cast_const,
      bad_cast,
      bad_action_stack,
      bad_node_cast_const,
      bad_node_cast,
      array_action_error_const,
      array_action_error,
      class_action,
      indirect_action_const,
      member_action_unhandled,
      object_action_error,
      compute_schema_path,
      get_base_element_type,
      argument_keyword_with_values_expected,
      argument_keyword_with_values_maximum,
      argument_always_expected,
      argument_always_maximum,
      b_tree_node_pt_delete,
      b_tree_node_pt_change_key,
      b_tree_node_pt_verify_parent,
      b_tree_node_pt_verify_count,
      b_tree_node_pt_verify_root,
      b_tree_node_pt_verify_height,
      b_tree_node_pt_verify_min,
      b_tree_node_pt_verify_key,
      b_tree_node_pt_verify_left_sibling1,
      b_tree_node_pt_verify_left_sibling2,
      b_tree_node_pt_verify_left_sibling3,
      b_tree_node_pt_verify_left_sibling4,
      b_tree_node_pt_verify_right_sibling1,
      b_tree_node_pt_verify_right_sibling2,
      b_tree_node_pt_verify_right_sibling3,
      b_tree_node_pt_verify_right_sibling4,
      b_tree_node_pt_verify_sort,
      b_tree_node_pt_lshift,
      b_tree_node_pt_rshift,
      b_tree_node_pt_insert_here,
      b_tree_node_pt_split,
      b_tree_node_pt_remove_here1,
      b_tree_node_pt_remove_here2,
      b_tree_node_pt_change_key_here1,
      b_tree_node_pt_change_key_here2,
      b_tree_node_pt_change_key_here3,
      b_tree_node_pt_change_key_here4,
      b_tree_node_pt_balance_with_right_sibling,
      b_tree_node_pt_collapse_with_right_sibling1,
      b_tree_node_pt_collapse_with_right_sibling2,
      b_tree_node_pt_collapse_with_right_sibling3,
      b_tree_node_pt_collapse_with_right_sibling4,
      b_tree_pt_b_tree_pt1,
      b_tree_pt_b_tree_pt2,
      b_tree_pt_change_key,
      b_tree_pt_verify1,
      b_tree_pt_verify2,
      b_tree_safe_cursor_pt_at_an_entry1,
      b_tree_safe_cursor_pt_at_an_entry2,
      b_tree_safe_cursor_pt_remove_at,
      OS_DECLARE_SUBSYSTEM_CHAINING(os_Message)
      };
   OS_DECLARE_SUBSYSTEM_MESSAGES(os_Traverser_messages);
   };

OS_MSGS_EXCEPTION(tix_traverser_exception);

#endif
