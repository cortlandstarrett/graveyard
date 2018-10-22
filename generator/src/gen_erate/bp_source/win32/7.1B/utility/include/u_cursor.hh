/*========================================================================
 *
 * File:      $RCSfile: u_cursor.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef U_CURSOR_HH
#define U_CURSOR_HH






//
//  Example call to FIRST_ELEMENT macro:
//
//	Object *object_ptr;
//	FIRST_ELEMENT (object_ptr, Object, get_object_coll_ptr (), cursor);
//

#define FIRST_ELEMENT(element_ptr,element_type,collection_ptr,cursor)	\
    mc_dbms_Cursor<element_type*> cursor (*collection_ptr);			\
    element_ptr = cursor.first ();
	
#define NEXT_ELEMENT(element_ptr,cursor)				\
    element_ptr = cursor.next ()
	
#define FOR_ALL_ELEMENTS(element_ptr,element_type,collection_ptr,cursor) \
    mc_dbms_Cursor<element_type*> cursor (*collection_ptr);			\
    for (element_ptr = cursor.first ();					\
	element_ptr != 0;						\
	element_ptr = cursor.next ())




//
// Macros for safe cursors, can ONLY be used in update transactions with
// the configuration checked out
//

#define FIRST_ELEMENT_SAFE(element_ptr,element_type,collection_ptr,cursor) \
    mc_dbms_Cursor<element_type*> cursor (*collection_ptr, mc_dbms_cursor::safe);	\
    element_ptr = cursor.first ();
	
#define NEXT_ELEMENT_SAFE(element_ptr,cursor)				\
    element_ptr = cursor.next ()
	
#define FOR_ALL_ELEMENTS_SAFE(element_ptr,element_type,collection_ptr,cursor) \
    mc_dbms_Cursor<element_type*> cursor(*collection_ptr, mc_dbms_cursor::safe);	\
    for (element_ptr = cursor.first ();					\
	element_ptr != 0;						\
	element_ptr = cursor.next ())
	



//
// Example call to FIRST_ELEMENT_BY_NAME macro:
//
//	Object *object_ptr;
//	FIRST_ELEMENT_BY_NAME( object_ptr, Object, "Object *", 
//		get_object_coll_ptr(), cursor, name_path );
//

#define FIRST_ELEMENT_BY_NAME(element_ptr,element_type,element_type_ptr_str,coll_ptr,cursor,name_path) \
									\
    mc_dbms_Cursor<element_type*> cursor (*coll_ptr, name_path);		\
    element_ptr = cursor.first ();
	
#define NEXT_ELEMENT_BY_NAME(element_ptr,cursor)			\
    element_ptr = cursor.next ()
	
#define FOR_ALL_ELEMENTS_BY_NAME(element_ptr,element_type,element_type_ptr_str,coll_ptr,cursor,name_path) \
									\
    mc_dbms_Cursor<element_type*> cursor (*coll_ptr, name_path);		\
									\
    for (element_ptr = cursor.first ();					\
	element_ptr != 0;						\
	element_ptr = cursor.next ())




#endif
