/*========================================================================
 *
 * File:      $RCSfile: r_cursor.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:07 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef		RLCURSOR_HH
#define		RLCURSOR_HH


#include <vcursor.h>
#include <vdomview.h>

#include <u_typdef.hh>

//
// FILE: rlcursor.hh	AUTHOR: Donald R. Cornwell	CREATION DATE: 10/19/94
//
// CONTENTS:
//
//	This file contains the specification of the RL_Cursor class.
//
// REMARKS:
//	This class is very static in nature.  There are a finite
//	number of cursors that must be defined for the graphical
//	editor, such as a move cursor, resize cursor, etc.  
//


//
// DOMAIN: 	Render - used for Galaxy Render only
// CLASS: 	RL_Cursor
//
// DESCRIPTION:
//
//	This class defines a MCursor for use in the Graphical 
//	Editor domain.  The following public functions are defined:
//		init()
//		SetDrawMCursor()
//		SetCrosshairMCursor()
//		SetDefaultMCursor()
//		SetBusyMCursor()
//		SetUnBusyMCursor()
//		SetZoomInMCursor()
//		SetZoomOutMCursor()
//      GetResizeMCursor()
//

class RL_Cursor
{
	public:
		// MANAGER FUNCTIONS
		RL_Cursor()  { }
		~RL_Cursor()   { }
				
		// IMPLEMENTOR FUNCTIONS
		static  void init ();
		static  void SetDrawMCursor ( vdomainview* );
		static  void SetCrosshairMCursor ( vdomainview* );
		static  void SetZoomInMCursor ( vdomainview* );
		static  void SetZoomOutMCursor ( vdomainview* );
		static  void SetBusyMCursor ( );
		static  void SetUnBusyMCursor ( );
		static  vcursor *GetResizeMCursor ( );
		static  void SetDefaultMCursor (vdomainview*);

		static 	t_boolean is_cursor_busy ();
		
		// ACCESSOR FUNCTIONS
		
	private:
		// HELPING FUNCTIONS
		
		// PRIVATE VARIABLES
	 	static vcursor	*DrawCursor;
	 	static vcursor	*CrosshairCursor;
	 	static vcursor	*BusyCursor;
	 	static vcursor	*ResizeCursor;
	 	static vcursor	*ZoomInCursor;
	 	static vcursor	*ZoomOutCursor;

		static t_boolean	busy_cursor;
};



#endif	
