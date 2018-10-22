/*========================================================================
 *
 * File:      $RCSfile: u_udmenu.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef USER_DEFINED_MENU_HH
#define USER_DEFINED_MENU_HH


#include <u_typdef.hh>

struct vevent;
struct vmenubar;
struct vmenu;
struct vmenuItem;

class U_user_defined_menu
{
public:
    static void init(const char *);
    static void add_to_menubar ( vmenubar*, t_boolean add_about );
    static void remove_from_menubar ( vmenubar* );

private:
    static void execute_about_item ( vmenuItem *, vevent * );
    static void execute_menu_item ( vmenuItem *, vevent * );

    static mc_dbms_List<U_user_defined_menu*> *menu_list;
    vmenu* m_menu;
};

#endif
