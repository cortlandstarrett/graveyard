/*========================================================================
 *
 * File:      $RCSfile: u_media.hh,v $
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
#ifndef		U_MEDIA_HH
#define		U_MEDIA_HH


#include <u_typdef.hh>


//
// CONTENTS:
//
//	This file contains the class definition of the RM_render_media class.
//	This class is a base class that contains all the virtual functions
//	necessary for any rendering media instance (eg - UNIX file) to
//	perform a rendering.
//

class RM_render_media
	{
    public:

		enum t_create_render_media { MEDIA_CREATED, MEDIA_ALREADY_EXISTS,
			UNABLE_TO_OPEN_MEDIA, MEDIA_OPENED };

		enum t_seek_start_position { TOP_OF_FILE, CURRENT_POSITION,
			END_OF_FILE };

		// MANAGER FUNCTIONS

		RM_render_media() {}
		virtual ~RM_render_media() {}
			
		// IMPLEMENTOR FUNCTIONS

		virtual t_create_render_media RM_create_media
			( const char *p_media_name, t_boolean overwrite_flag ) = 0;
		virtual t_create_render_media RM_create_temp_media() = 0;
		virtual t_create_render_media RM_overwrite_media( const char *p_media_name ) = 0;
		virtual t_create_render_media RM_open_media( const char *p_media_name ) = 0;
		virtual t_create_render_media RM_append_media( const char *p_media_name ) = 0;
		virtual void RM_remove_media( ) = 0;
		virtual void RM_close_media( const char *p_media_name ) = 0;
		virtual void RM_flush_media_to_device( const char *p_device_name ) = 0;
		virtual void RM_write( const char *p_string ) = 0;
		virtual char * RM_read() = 0;
		virtual void RM_rewind() = 0;
	
    protected:

    private:

	};

#endif
