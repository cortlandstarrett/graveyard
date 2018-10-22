/*========================================================================
 *
 * File:      $RCSfile: u_fopen.cc,v $
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
#include <u_fopen.hh>

#include <vwindow.h>
#include <u_env.hh>


#ifdef WIN32

#include <commdlg.h>

extern "C" HWND vwindowGetMSWWindow(vwindow *window);

t_boolean
U_file_open::load_ooa_file_win32 (vdialog* index_dialog, char*& p_filepath, char*& p_filename)
{

    HWND hWnd  = vwindowGetMSWWindow(vdialogGetWindow(index_dialog)); // undocumented call !

	OPENFILENAME ofn;       // common dialog box structure  
	char szDirName[4096];   // directory string  staticchar 
	static char szFile[4096];      // filename string  
	static char szFileTitle[256];
	char *szFilterName = "OOA Database Files (*.ooa)";     // filter string  
	char *szFilterPattern = "*.ooa";
	char szFilter[256];
	char szSelectFile[256] = "Open OOA DB File";// title of select file dialog   

	strcpy( szDirName, U_environment::get_ooa_dir ().char_ptr () );
	szFile[0] = 0;
	szFileTitle[0] = 0;

	// setup the filter
	strcpy ( szFilter, szFilterName );
	int name_len = strlen( szFilterName );
	strcpy ( szFilter+name_len+1, szFilterPattern );
	int patt_len = strlen( szFilterPattern );
	szFilter[name_len+patt_len+2] = 0;

	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hwndOwner = hWnd; 
	ofn.lpstrFilter = szFilter; 
	ofn.lpstrCustomFilter = NULL; 
	ofn.nFilterIndex = 1; 
	ofn.lpstrFile = szFile; 
	ofn.nMaxFile = sizeof(szFile); 
	ofn.lpstrFileTitle = szFileTitle; 
	ofn.nMaxFileTitle = sizeof(szFileTitle); 
	ofn.lpstrInitialDir = szDirName; 
	ofn.lpstrTitle = szSelectFile; 
	ofn.lpstrDefExt = NULL; 
	ofn.Flags = OFN_SHAREAWARE | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  
	//Put up Open File dialog to get filename   
	if (GetOpenFileName(&ofn))  
	{ 
		p_filepath = szFile;
		p_filename = szFileTitle;
		return TRUE;
	}    
	else
	{
		return FALSE;
	}
}

t_boolean
U_file_open::load_sim_file_win32 (vdialog* index_dialog, char*& p_filepath, char*& p_filename)
{

    HWND hWnd  = vwindowGetMSWWindow(vdialogGetWindow(index_dialog)); // undocumented call !

	OPENFILENAME ofn;       // common dialog box structure  
	char szDirName[4096];   // directory string  staticchar 
	static char szFile[4096];      // filename string  
	static char szFileTitle[256];
	char *szFilterName = "Simulation Database Files (*.sim)";     // filter string  
	char *szFilterPattern = "*.sim";
	char szFilter[256];
	char szSelectFile[256] = "Open Simulation Workspace";// title of select file dialog   

	strcpy( szDirName, U_environment::get_ooa_dir ().char_ptr () );
	szFile[0] = 0;
	szFileTitle[0] = 0;

	// setup the filter
	strcpy ( szFilter, szFilterName );
	int name_len = strlen( szFilterName );
	strcpy ( szFilter+name_len+1, szFilterPattern );
	int patt_len = strlen( szFilterPattern );
	szFilter[name_len+patt_len+2] = 0;

	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hwndOwner = hWnd; 
	ofn.lpstrFilter = szFilter; 
	ofn.lpstrCustomFilter = NULL; 
	ofn.nFilterIndex = 1; 
	ofn.lpstrFile = szFile; 
	ofn.nMaxFile = sizeof(szFile); 
	ofn.lpstrFileTitle = szFileTitle; 
	ofn.nMaxFileTitle = sizeof(szFileTitle); 
	ofn.lpstrInitialDir = szDirName; 
	ofn.lpstrTitle = szSelectFile; 
	ofn.lpstrDefExt = NULL; 
	ofn.Flags = OFN_SHAREAWARE | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  
	//Put up Open File dialog to get filename   
	if (GetOpenFileName(&ofn))  
	{ 
		p_filepath = szFile;
		p_filename = szFileTitle;
		return TRUE;
	}    
	else
	{
		return FALSE;
	}
}


t_boolean
U_file_open::load_bak_file_win32 (vdialog* index_dialog, char*& p_filepath, char*& p_filename)
{

    HWND hWnd  = vwindowGetMSWWindow(vdialogGetWindow(index_dialog)); // undocumented call !

	OPENFILENAME ofn;       // common dialog box structure  
	char szDirName[4096];   // directory string  staticchar 
	static char szFile[4096];      // filename string  
	static char szFileTitle[256];
	char *szFilterName = "Backup File (*.bak)";     // filter string  
	char *szFilterPattern = "*.bak";
	char szFilter[256];
	char szSelectFile[256] = "Select Bak File For Default Template";// title of select file dialog   

	strcpy( szDirName, U_environment::get_ooa_dir ().char_ptr () );
	szFile[0] = 0;
	szFileTitle[0] = 0;

	// setup the filter
	strcpy ( szFilter, szFilterName );
	int name_len = strlen( szFilterName );
	strcpy ( szFilter+name_len+1, szFilterPattern );
	int patt_len = strlen( szFilterPattern );
	szFilter[name_len+patt_len+2] = 0;

	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hwndOwner = hWnd; 
	ofn.lpstrFilter = szFilter; 
	ofn.lpstrCustomFilter = NULL; 
	ofn.nFilterIndex = 1; 
	ofn.lpstrFile = szFile; 
	ofn.nMaxFile = sizeof(szFile); 
	ofn.lpstrFileTitle = szFileTitle; 
	ofn.nMaxFileTitle = sizeof(szFileTitle); 
	ofn.lpstrInitialDir = szDirName; 
	ofn.lpstrTitle = szSelectFile; 
	ofn.lpstrDefExt = NULL; 
	ofn.Flags = OFN_SHAREAWARE | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  
	//Put up Open File dialog to get filename   
	if (GetOpenFileName(&ofn))  
	{ 
		p_filepath = szFile;
		p_filename = szFileTitle;
		return TRUE;
	}    
	else
	{
		return FALSE;
	}
}

#endif
