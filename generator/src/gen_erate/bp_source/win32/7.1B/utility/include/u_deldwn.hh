/*========================================================================
 *
 * File:      $RCSfile: u_deldwn.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_DELETE_DOWN_HH
#define U_DELETE_DOWN_HH

#include <u_cursor.hh>
#include <u_typdef.hh>


#define delete_mc_dbms_relationship_1_1_body( this_class, inst_ptr1, that_class, inst_ptr2 )  \
                                                                          \
  inst_ptr1->delete_down( nesting_level );



#define delete_mc_dbms_relationship_m_1_body( this_class, coll_ptr, that_class, inst_ptr )  \
{                                                                           \
  that_class *inst_ptr;                                                     \
  FOR_ALL_ELEMENTS_SAFE(inst_ptr,that_class,&(coll_ptr.getvalue()),cursor ) \
  {                                                                         \
    inst_ptr->delete_down( nesting_level );                                 \
  }                                                                         \
}

#define delete_mc_dbms_relationship_1_m_body( this_class, inst_ptr1, that_class, coll_ptr )  \
                                                                          \
  inst_ptr1->delete_down( nesting_level );



#define delete_mc_dbms_relationship_m_m_body( this_class, coll_ptr, that_class, coll_ptr2 )  \
{                                                                           \
  that_class *that_ptr;                                                     \
  FOR_ALL_ELEMENTS_SAFE(that_ptr,that_class,&(coll_ptr.getvalue()),cursor)  \
  {                                                                         \
    that_ptr->delete_down( nesting_level );                                 \
  }                                                                         \
}


#define delete_mc_dbms_relationship_supertype_body( supertypeName )            \
                                                                          \
  supertypeName::delete_down( nesting_level );


//*************************************************************************
//
//  Macro: DELETE_DOWN_START_SUBTYPE( class_name )
//
//  Purpose: This macro forms the top part of a delete_down() function for
//           the class specified by class_name.  It should be used by 
//           classes which inherit from another class.
//
//  Example: DELETE_DOWN_START_SUBTYPE( D_data_type )
//
//*************************************************************************
#define DELETE_DOWN_START_SUBTYPE( class_name )                           \
                                                                          \
void                                                                      \
class_name::delete_down( int nesting_level )                              \
{                                                                         \
  LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,                   \
             "Entered %s::delete_down ()...nesting_level = %d",           \
             #class_name, nesting_level));                                \
                                                                          \
  if ( ! delete_in_progress )                                             \
    {                                                                     \
      ++nesting_level;                                                    \
      delete_in_progress = TRUE;


//*************************************************************************
//
//  Macro: DELETE_DOWN_END_SUBTYPE( class_name )
//
//  Purpose: This macro forms the footer for the delete_down() function of
//           the class specified by class_name.  It should be used for
//           classes that are not supertypes, because it will delete the
//           this pointer.
//
//  Example: DELETE_DOWN_END_SUBTYPE( D_data_type )
//
//*************************************************************************
#define DELETE_DOWN_END_SUBTYPE( class_name )                             \
                                                                          \
      delete this;                                                        \
    }                                                                     \
                                                                          \
  LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,                     \
	          "Exitted %s::delete_down ().", #class_name));                 \
}


//*************************************************************************
//
//  Macro: DELETE_DOWN_START_SUPERTYPE( class_name )
//
//  Purpose: This macro forms the top part of a delete_down() function for
//           the class specified by class_name.  It should be used for
//           classes that are inherited from.  It is assumed that no
//           instances of this supertype class are created.
//
//  Example: DELETE_DOWN_START_SUPERTYPE( D_data_type )
//
//*************************************************************************
#define DELETE_DOWN_START_SUPERTYPE( class_name )                         \
                                                                          \
void                                                                      \
class_name::delete_down( int nesting_level )                              \
{                                                                         \
  LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,                   \
             "Entered %s::delete_down ()...nesting_level = %d",           \
             #class_name, nesting_level));                                \
                                                                          \
  ++nesting_level;


//*************************************************************************
//
//  Macro: DELETE_DOWN_END_SUPERTYPE( class_name )
//
//  Purpose: This macro forms the footer for the delete_down() function of
//           the class specified by class_name.  It should be used for
//           classes that are supertypes, because it will not delete the
//           this pointer.
//
//  Example: DELETE_DOWN_END_SUPERTYPE( D_data_type )
//
//*************************************************************************
#define DELETE_DOWN_END_SUPERTYPE( class_name )                           \
                                                                          \
  LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,                     \
	          "Exitted %s::delete_down ().", #class_name));                 \
}


//*************************************************************************
//
//  Macro: DELETE_DOWN_DECL_SUPERTYPE()
//
//  Purpose: This macro declares the delete_down() function within a
//           class declaration.
//
//  Example: DELETE_DOWN_DECL_SUPERTYPE()
//
//*************************************************************************
#define DELETE_DOWN_DECL_SUPERTYPE()                                      \
  virtual void delete_down( int nesting_level );


//*************************************************************************
//
//  Macro: DELETE_DOWN_DECL_SUBTYPE()
//
//  Purpose: This macro declares the delete_down() function within a
//           class declaration.
//
//  Example: DELETE_DOWN_DECL_SUBTYPE()
//
//*************************************************************************
#define DELETE_DOWN_DECL_SUBTYPE()                                        \
  virtual void delete_down( int nesting_level );                          \
  t_boolean delete_in_progress;


//*************************************************************************
//
//  Macro: DELETE_IN_PROGRESS_INIT()
//
//  Purpose: This macro initializes the delete_in_progress variable in the
//           constructor of a class that uses DELETE_DOWN_DECL_SUBTYPE()
//
//  Example: DELETE_IN_PROGRESS_INIT()
//
//*************************************************************************
#define DELETE_IN_PROGRESS_INIT()                                         \
  delete_in_progress = FALSE;



#endif
