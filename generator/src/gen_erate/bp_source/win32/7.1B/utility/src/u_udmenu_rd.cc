/*========================================================================
 *
 * File:      $RCSfile: u_udmenu_rd.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:58 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_udmenu.hh>

#include <w_ctrl.hh>

#include <vmenu.h>
#include <vmenubar.h>

// These two functions are in a separate file to allow the gen_import
// and gen_file programs to link correctly.

void U_user_defined_menu::add_to_menubar ( vmenubar* p_menubar_ptr, t_boolean p_add_about )
{
    Description help_str ( "Help" );
    Description about_str ( "About ..." );

    mc_dbms_Cursor<U_user_defined_menu *> menu_cursor (*menu_list);
    U_user_defined_menu *udm = menu_cursor.first ();
    while (udm != 0)
    {
        vmenu *menu_ptr = vmenuClone(udm->m_menu);

        // if p_add_about and this is the Help menu, 
        //    add a separator and About menu item to the end.
        if ( p_add_about &&
             vcharCompare ( vmenuGetTitle(menu_ptr), help_str.char_ptr() ) == 0 )
        {
            vmenuSeparatorItem *sep_item = vmenuCreateSeparatorItem();
            vmenuAppendItem( menu_ptr, sep_item );

            vmenuItem* mitem = vmenuCreateItem();
            vmenuSetItemTitle( mitem, about_str.char_ptr() );
            vmenuAppendItem( menu_ptr, mitem );
            vmenuSetItemMnemonic( mitem, (about_str.char_ptr())[0] );
            vmenuSetItemNotify( mitem, U_user_defined_menu::execute_about_item);
        }

        vmenubarAppendMenu( p_menubar_ptr, menu_ptr );
        
        udm = menu_cursor.next();
    }

}


void U_user_defined_menu::execute_about_item ( vmenuItem * p_menuitem, vevent * p_event)
{
    W_control::show_control_window (ABOUT_WINDOW);
}
