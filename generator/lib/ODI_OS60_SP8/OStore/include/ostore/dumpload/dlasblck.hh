/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DLASBLCK_HH
#define DLASBLCK_HH


/***********************************************************************
*                                                                      *
* Copyright (c) 1998-2000 by eXcelon Corporation. All Rights Reserved.                          *
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

#include <ostore/ostore.hh>


/***********************************************************************
  class os_DL_address_space_controller
***********************************************************************/

class os_DL_address_space_controller {

  public: // Static Initializer
    static void initialize ();

  public: // Static Accessors
    static os_boolean has_exceeded_address_space_threshold ();
    static os_ptr_val get_address_space_total ();
    static os_ptr_val get_address_space_available ();
    static float get_address_space_threshold (); // percentage [0.00,1.00]

  public: // Static Modifiers
    static void set_address_space_total (os_ptr_val total_bytes);
    static void set_address_space_threshold (float percentage /*[0.00,1.00]*/);

  private: // Construction
    os_DL_address_space_controller ();
    os_DL_address_space_controller (os_DL_address_space_controller&);
    ~os_DL_address_space_controller ();

  private: // Assignment
    os_DL_address_space_controller& operator = (os_DL_address_space_controller&);

  };


/***********************************************************************
  Macros: Dump/Load Address Space Control

  The following macros must be used together. In a given usage, the
  values of marker, txn_tag, excp_ptr, and txn_type must be the same
  for each macro in the set. 

  It is expected that the usage pattern for these macros will be like

    OS_DLAS_OUTER_BLOCK_BEGIN(marker0,txn0,0,os_transaction::update) {
        Item* item = 0;
        while (has_more_items()) {
            OS_DLAS_INNER_BLOCK_BEGIN(marker0,txn0,0,os_transaction::update) {
                while (item || has_more_items()) {
		    // Note that when dumping, the item can not denote persistent
                    // state. Any necessary persistent state or the details
                    // needed to retrieve some persistent state across a
                    // transaction must be copied into transient memory.
                    if ( ! item)
                        item = get_next_item();
                    OS_DLAS_INNER_BLOCK_BREAK(marker0);
                    process(item);
                    item = 0;
                  }
              } OS_DLAS_INNER_BLOCK_END(marker0,txn0);
          }
      } OS_DLAS_OUTER_BLOCK_END(marker0,txn0);

  Note that the transaction kind will likely be os_transaction::update in
  the loader, but os_transaction::read_only in the dumper. --rick@odi.com
***********************************************************************/

// #if release 5.0 or greater

#define OS_DLAS_OUTER_BLOCK_BEGIN(marker,txn_tag,excp_ptr,txn_type) {\
    OS_BEGIN_TXN(txn_tag,excp_ptr,txn_type) \
        os_address_space_marker marker;

#define OS_DLAS_INNER_BLOCK_BEGIN(marker,txn_tag,excp_ptr,txn_type) {

#define OS_DLAS_INNER_BLOCK_BREAK(marker) \
    if (os_DL_address_space_controller::has_exceeded_address_space_threshold()) \
        break

#define OS_DLAS_INNER_BLOCK_END(marker,txn_tag) \
    marker.release(); \
  }

#define OS_DLAS_OUTER_BLOCK_END(marker,txn_tag) \
    OS_END_TXN(txn_tag) \
  }

// #else before release 5.0

/*
#define OS_DLAS_OUTER_BLOCK_BEGIN(marker,txn_tag,excp_ptr,txn_type) {

#define OS_DLAS_INNER_BLOCK_BEGIN(marker,txn_tag,excp_ptr,txn_type) { \
    OS_BEGIN_TXN(txn_tag,excp_ptr,txn_type)

#define OS_DLAS_INNER_BLOCK_BREAK(marker) \
    if (os_DL_address_space_controller::has_exceeded_address_space_threshold()) \
        break

#define OS_DLAS_INNER_BLOCK_END(marker,txn_tag) \
    OS_END_TXN(txn_tag) \
  }

#define OS_DLAS_OUTER_BLOCK_END(marker,txn_tag) \
  }
*/

// #endif

#endif /* DLASBLCK_HH */
