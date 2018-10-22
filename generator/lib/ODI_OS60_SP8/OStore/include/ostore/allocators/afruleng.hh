/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef ___ODI_AF_RULE_ENGINE__
#define ___ODI_AF_RULE_ENGINE__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afmap.hh>
#include <ostore/allocators/afitratr.hh>

/******************************************************************************
Class Name       : os_rule_engine
Description      : This is rule engine class that maintains all the rules and
                   evaluates rules to find the proper allocator name with the
                   help of allocation contexts pushed on context stack.
Remarks          :
******************************************************************************/

typedef _ODI_AF_Map< os_string > os_rule_map ;
typedef os_List< os_string* > os_rule_list ;

class _OS_DLLIMPORT(_OS_ALLOC)  os_rule_engine
{
    public : /* general */

        /*  constructor */
        os_rule_engine() ;
        /* destructor */
        ~os_rule_engine() ;
         /* return the singleton instance */
        static os_rule_engine* instance() ;

        static os_typespec* get_os_typespec() ;

        /* set the rule db path and the rule root name */
        static void rule_db( os_string database_path, os_string root_name ) ;


    public : /* create, modify, inquire rules */

        /* create new rule */
        os_boolean create_rule( const os_string& rule_name,
                                const os_string& rule_str ) ;
        /* find rule by name and return */
        os_string* get_rule( const os_string& rule_name ) ;
        /*  find rule string by name, delete rule string by name */
        os_boolean delete_rule( const os_string& rule_name ) ;
        /* make it effective */
        os_boolean register_rule( const os_string& rule_name ) ;
         /* return all the rules, if no rule return null */
        os_rule_iterator* get_rules() ;
        /* only sorted effective rules. if no rule effective, return null */
        os_rule_iterator* get_effective_rules() ;
        /* remove all the names from rule list. */
        os_boolean clear_effective_rules() ;
		/* remove the rules from the rule engine */
		os_boolean clear_rules() ;

    public : /* for allocator registry */

        /* return allocator name, find the name with the help of contexts */
        os_string get_allocator() ; 
    

    private :
        

        /* if necessay, read the state from database and initialize itself */
        os_boolean initialize() ;

        /* not implemented */
        os_rule_engine( const os_rule_engine& ) ;
        os_rule_engine& operator=( const os_rule_engine& );

    private :

        static os_rule_engine* m_p_self ;
        os_rule_map*         m_p_rules ;
        os_rule_list*        m_p_effective_rules ;

} ;

#endif
