/*========================================================================
 *
 * File:      $RCSfile: sw_creat.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:10 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SW_CREATE_HH
#define SW_CREATE_HH

#include <vdialog.h>
#include <vevent.h>
#include <u_string.hh>

struct vfilechsr;
struct vtextitem;
struct vbutton;
class W_index_gui_drivers;

class W_create_new_simfile_dialog {
        public:
                static void show(W_index_gui_drivers * parent_);        

        private:   //Galaxy is C like and does not hand "this" pointers
                   //Therefore, One class=one window (only one instance).....
                   //"and in the beginning there was "C"...."
                   //If I were smart and had time (I am and have niether)
                   //I would make a base class and have these statics 
                   //lookup which object made the 
                   //the call back and use that object to derefference
                   //to the correct function....(I think Galaxy is 
                   //giving me enough info to do that on the call back...
                   //maybe)  //see vdialogGetData() and vdialogSetData(...)
                   //But for now One Class=One Instance
                W_create_new_simfile_dialog(); 
                //call backs -- for buttons and window functions                
                static int cb_OOA_FileChooser(vcommandFunction*, vdict*);
                static int cb_SIM_FileChooser(vcommandFunction*, vdict*);
                static int cb_OK(vcommandFunction*, vdict*);
                static int cb_close(vcommandFunction*, vdict*);
                static int cb_close_hook(vdialog*, vevent*);
                //call backs -- for filechooser
                static int cb_OOA_fileApply(vfilechsr* database_window_ptr, vfsPath* path_ptr);
                static int cb_SIM_fileApply(vfilechsr* database_window_ptr, vfsPath* path_ptr);

                static W_create_new_simfile_dialog *gui;
                //Galaxy's pointer to this dialog box
                static vdialog * gui_dialog;
                //Galaxy's pointer to the error dialog box
                static vdialog * gui_error_dialog;
                static W_index_gui_drivers * index_gui_drivers_ptr;

        private:                
                static vcommandFunctionTemplate cmds [];
                static char *SIM_filepath;
                static char *OOA_filepath;
                static vfilechsr * filechsr; 
                static vtextitem * OOAtextitem;
                static vbutton *  OOA_FileChooserButton; //I don't really need this except for fixing the NT-Galaxy focus problem
                static vtextitem * SIMtextitem;
                static vdialogLabelItem * ErrorLabel;
 
                static void getTextBoxPathnames();
                static int ensureOrAppendExtension(char *name,char* ext);
                static int do_fileChooser(vdict* dict_ptr,
                                int (cb_fileApply)(vfilechsr* database_window_ptr, vfsPath* path_ptr),
                                char * title,char *filePath,const vname *filter, int options
                                );
                  
                static void SIMtextitem_notify(vtextitem *,vevent * event_ptr, int message);
                static void OOAtextitem_notify(vtextitem *,vevent * event_ptr, int message);
                //display error messages modal to this dialog box only
                static void errorMessage(GS_string &error_string);
                static void errorMessage(char *errorMsg);
                static void errorMessage(vscribe * errorMsg);

                //set the statuse bar at the bottom of the index window
                static void setStatusBarToCopyright();
                static void setStatusBar(GS_string &str);
                static void setStatusBar(char *str);

                // set the modailty of the parent
                static void setHourGlass(int boolean);


                //these are modified copies of sv_index.cc, razor 1.15,
                //   W_ooa_db_load_file_selected_notify and
                //   W_sim_db_create_file_selected_notify 
                static int openOOAFile(char *);
                static int createSimFile(char *);
};


#endif
