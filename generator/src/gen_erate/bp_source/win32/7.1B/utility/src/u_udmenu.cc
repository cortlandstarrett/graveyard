/*========================================================================
 *
 * File:      $RCSfile: u_udmenu.cc,v $
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

#include <u_desc.hh>
#include <u_error.hh>
#include <u_file.hh>

#include <vfs.h>
#include <vmenu.h>
#include <vmenubar.h>

#include <stdlib.h>

mc_dbms_List<U_user_defined_menu*> *U_user_defined_menu::menu_list = 0;

void U_user_defined_menu::init(const char *app_name)
{
    // For each file menu_file_dir
    //    create menu
    //    for each line in file 
    //       create menu item

    if ( menu_list == 0 )
    {
        menu_list = new (
            mc_dbms_database::get_transient_database(), 
            mc_dbms_List<U_user_defined_menu*>::get_mc_dbms_typespec()) 
            mc_dbms_List<U_user_defined_menu*>;
    }

    Description menu_file_dir ( "../menus/" );
    menu_file_dir += app_name;
    vfsPath *path = vfsPathFromStr(menu_file_dir.char_ptr());

    vfsDir *openDir  = 0;
	vexWITH_HANDLING {

        openDir  = vfsOpenDir(path);

	} vexON_EXCEPTION {
    } vexEND_HANDLING;

    if ( openDir == 0 )
    {
       	LOG_ERROR( ( L_log_string,
       	    "U_user_defined_menu::init()...could not open menu file directory %s", menu_file_dir.char_ptr() ));

        vfsDestroyPath(path);
        return;
    }

    vstr *dirEntry = 0;
	vexWITH_HANDLING
      {
      dirEntry = vfsReadDir(openDir);
      }
    vexON_EXCEPTION
      {
      dirEntry = 0;
      }
    vexEND_HANDLING;

    while (dirEntry) 
    {
        if ( vcharCompare( dirEntry, vfsGetCurrentPathElementString() ) != 0 &&
             vcharCompare( dirEntry, vfsGetParentPathElementString() ) != 0 )
        {
            vfsPath *file_path = vfsBuildPath( vfsPATH_TYPE_RELATIVE, menu_file_dir.char_ptr(), dirEntry, NULL );
            vstr *file_path_str = vfsPathToStr ( file_path );
    	    char *name_str_System = (char *) vcharExportAlloc( 
	    	    vcharScribeSystemExport(file_path_str));

            RM_file * file_ptr = new RM_file ();
            if (file_ptr->RM_open_media (name_str_System) != RM_render_media::MEDIA_OPENED)
            {
        	    LOG_ERROR( ( L_log_string,
        	        "U_user_defined_menu::init()...could not open menu file %s", dirEntry ));
            }
            else
            {
                vchar *dot_pos = vcharSearchChar( dirEntry, '.' );
                vchar *menu_name = vstrClone ( dirEntry );
                if ( dot_pos != 0 )
                {
                    int len = dot_pos - dirEntry;
                    menu_name[len] = 0;
                }


                U_user_defined_menu *udm = new U_user_defined_menu;
                udm->m_menu = vmenuCreate ();
                vmenuSetTitle( udm->m_menu, menu_name );
                vmenuSetMnemonic( udm->m_menu, menu_name[0] );
                vmenuSetData ( udm->m_menu, udm );
                menu_list->insert( udm );

	            vchar *line_str;
		        while ((line_str = file_ptr->RM_read_vchar ()) != 0)
		        {
                    // parse the line in the file
                    int pos = 0;
                    while ( vcharIsWhiteSpace( line_str[pos] ) ) ++ pos;

                    if ( line_str[pos] != vcharFromLiteral( '#' ) )
                    {
                        if ( line_str[pos] != vcharFromLiteral( '"' ) )
                        {
                    	    LOG_ERROR( ( L_log_string,
        	                    "U_user_defined_menu::init()...format error in file %s, line %s: missing initial \"", dirEntry, line_str ));
                        }
                        else
                        {
                            int menu_item_start_pos = ++ pos;
                            while ( pos < vcharLength( line_str ) && line_str[pos] != vcharFromLiteral('"') ) ++ pos;
                            if ( pos >= vcharLength( line_str ) )
                            {
                        	    LOG_ERROR( ( L_log_string,
            	                    "U_user_defined_menu::init()...format error in file %s, line %s: missing closing \" for first entry", dirEntry, line_str ));
                            }
                            else
                            {
                                int menu_item_end_pos = pos;
                                pos += 1;
                                while ( pos < vcharLength( line_str ) && line_str[pos] != vcharFromLiteral('"') ) ++ pos;
                                if ( pos >= vcharLength( line_str ) )
                                {
                        	        LOG_ERROR( ( L_log_string,
            	                        "U_user_defined_menu::init()...format error in file %s, line %s: missing initial \" for second entry", dirEntry, line_str ));
                                }
                                else
                                {
                                    int command_start_pos = ++ pos;
                                    while ( pos < vcharLength( line_str ) && line_str[pos] != vcharFromLiteral('"') ) ++ pos;
                                    if ( pos >= vcharLength( line_str ) )
                                    {
                        	            LOG_ERROR( ( L_log_string,
            	                            "U_user_defined_menu::init()...format error in file %s, line %s: missing closing \" for second entry", dirEntry, line_str ));
                                    }
                                    else
                                    {
                                        int command_end_pos = pos;
                                        vchar* menu_item_name = &line_str[menu_item_start_pos];
                                        vchar* command_str = &line_str[command_start_pos];
                                        line_str[menu_item_end_pos] = 0;
                                        line_str[command_end_pos] = 0;

                                        vmenuItem* mitem = vmenuCreateItem();
                                        vmenuSetItemTitle( mitem, menu_item_name );
                                        vmenuSetItemMnemonic( mitem, menu_item_name[0] );
                                        vmenuAppendItem( udm->m_menu, mitem );
                                        vmenuSetItemData( mitem, vstrClone( command_str ) );
                                        vmenuSetItemNotify( mitem, U_user_defined_menu::execute_menu_item);
                                    }
                                }
                            }
                        }
                    }
		        }

                vstrDestroy (menu_name);
            }

            delete file_ptr;
        	vcharExportFree( name_str_System );
            vstrDestroy( file_path_str );
            vfsDestroyPath(file_path);
        }

        vstrDestroy( dirEntry );
        dirEntry = 0;
        vexWITH_HANDLING
          {
            dirEntry = vfsReadDir(openDir);
          }
        vexON_EXCEPTION
          {
            dirEntry = 0;
          }
        vexEND_HANDLING;
    }
        
    vfsCloseDir(openDir);

    vfsDestroyPath(path);

}

void U_user_defined_menu::remove_from_menubar ( vmenubar* p_menubar_ptr )
{

    int num_menus = vmenubarGetMenuCount( p_menubar_ptr );

    mc_dbms_Cursor<U_user_defined_menu *> menu_cursor (*menu_list);
    U_user_defined_menu *udm = menu_cursor.last ();
    while (udm != 0)
    {
        num_menus -= 1;
        vmenu* menu_ptr = vmenubarGetMenuAt( p_menubar_ptr, num_menus );
        vmenubarRemoveMenu( p_menubar_ptr, menu_ptr );
        vmenuDestroy( menu_ptr );

        udm = menu_cursor.previous();
    }
}

void U_user_defined_menu::execute_menu_item ( vmenuItem * p_menuitem, vevent * p_event)
{
    vstr* command_str = (vstr*) vmenuGetItemData( p_menuitem );

    char *command_str_System = (char *) vcharExportAlloc( 
	    vcharScribeSystemExport(command_str));

    system( command_str_System );

    vcharExportFree( command_str_System );
}

