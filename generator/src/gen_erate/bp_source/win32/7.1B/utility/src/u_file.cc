/*========================================================================
 *
 * File:      $RCSfile: u_file.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:00 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <vex.h>
#include <vfs.h>
#include <vchar.h>
#include <vprint.h>

#include <stdio.h>
#include <stdlib.h>

#include <u_trace.hh>
#include <u_error.hh>
#include <u_string.hh>
#include <u_cmd.hh>
#include <u_env.hh>
#include <u_file.hh>






RM_file::RM_file ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_file ()."));


	file_ptr = 0;
	file_name_string = "";


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_file ()."));
}


RM_file::~RM_file ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::~RM_file ()...file_name = %S, file_ptr = 0x%x",
		vcharScribeASCII(file_name_string.char_ptr()), file_ptr ));


	if (file_ptr)
	{
		vexWITH_HANDLING {

            if (path_ptr)
              vfsDestroyPath (path_ptr);
            path_ptr = vfsPathFromFile((vfsFile *)file_ptr);
			vfsCloseFile ((vfsFile *)file_ptr);
            file_ptr = 0;

		} vexON_EXCEPTION {
		} vexEND_HANDLING;
	}


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::~RM_file ()."));
}

t_boolean RM_file::good()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::good ()...file_name = %S, file_ptr = 0x%x",
		vcharScribeASCII(file_name_string.char_ptr()), file_ptr ));


	t_boolean ret_val = FALSE;
	if (file_ptr)
	{
		FILE* the_file = vfsGetFilePtr((vfsFile *)file_ptr);
		ret_val = !feof(the_file) && !ferror(the_file);
	}


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::good()."));

	return ret_val;
}

t_boolean RM_file::RM_from_stdin()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_from_stdin ()."));

	t_boolean ret_val = FALSE;


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_from_stdin()."));

	return ret_val;
}


t_boolean
RM_file::RM_static_rename_media (const char * old_file, const char * new_file)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_static_rename_media (old_file='%S', new_file='%S').",
	vcharScribeASCII(old_file), vcharScribeASCII(new_file) ));


	t_boolean return_value = TRUE;


	vfsPath * old_path = vfsPathFromStrScribed
		(vcharScribeASCII (old_file));
	vfsPath * new_path = vfsPathFromStrScribed
		(vcharScribeASCII (new_file));

	vfsExpandVariablesInPath (old_path);
	vfsExpandVariablesInPath (new_path);

	vfsPath * old_path_dir = vfsClonePath (old_path);
	vfsDeletePathElementAt (old_path_dir,
		(vfsGetPathElementCount (old_path) - 1));

	vfsPath * new_path_dir = vfsClonePath (new_path);
	vfsDeletePathElementAt (new_path_dir,
		(vfsGetPathElementCount (new_path) - 1));

	if ((!vfsAccess (old_path_dir, vfsCAN_EXECUTE)) ||
		(!vfsAccess (old_path_dir, vfsCAN_WRITE)))
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"RM_file::RM_static_rename_media (); Could not write or execute directory for %S.",
		vcharScribeASCII(old_file) ));
		return_value = FALSE;
	}

	if ((!vfsAccess (new_path_dir, vfsCAN_EXECUTE)) ||
		(!vfsAccess (new_path_dir, vfsCAN_WRITE)))
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"RM_file::RM_static_rename_media (); Could not write or execute directory for %S.",
		vcharScribeASCII(new_file)));
		return_value = FALSE;
	}

	if (vfsAccess (new_path, vfsFILE_EXISTS))
	{
		if (!vfsAccess (new_path, vfsCAN_WRITE))
		{
			LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
			"RM_file::RM_static_rename_media (); Could not over write %S.",
			vcharScribeASCII(new_file)));
			return_value = FALSE;
		}
	}

	if (vfsAccess (new_path, vfsFILE_EXISTS))
	{
		if (!vfsAccess (new_path, vfsCAN_WRITE))
		{
			LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
			"RM_file::RM_static_move_media (); Could not over write %S.",
			vcharScribeASCII(new_file) ));
			return_value = FALSE;
		}
		else
		{
		   vfsRemove ( new_path );
		}
	}

	if (return_value && vfsAccess (old_path, vfsFILE_EXISTS))
	{
		vfsRename (old_path, new_path);
	}

	vfsDestroyPath (old_path_dir);
	vfsDestroyPath (new_path_dir);
	vfsDestroyPath (old_path);
	vfsDestroyPath (new_path);


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_static_rename_media (return_value=%d).",
	return_value));
	return return_value;
}

t_boolean
RM_file::RM_static_move_media (const char * old_file, const char * new_file)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_static_move_media (old_file='%S', new_file='%S').",
	vcharScribeASCII(old_file), vcharScribeASCII(new_file) ));


	t_boolean return_value = TRUE;


	vfsPath * old_path = vfsPathFromStrScribed
		(vcharScribeASCII (old_file));
	vfsPath * new_path = vfsPathFromStrScribed
		(vcharScribeASCII (new_file));

	vfsExpandVariablesInPath (old_path);
	vfsExpandVariablesInPath (new_path);

	vfsPath * old_path_dir = vfsClonePath (old_path);
	vfsDeletePathElementAt (old_path_dir,
		(vfsGetPathElementCount (old_path) - 1));

	vfsPath * new_path_dir = vfsClonePath (new_path);
	vfsDeletePathElementAt (new_path_dir,
		(vfsGetPathElementCount (new_path) - 1));

	if ((!vfsAccess (old_path_dir, vfsCAN_EXECUTE)) ||
		(!vfsAccess (old_path_dir, vfsCAN_WRITE)))
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"RM_file::RM_static_move_media (); Could not write or execute directory for %S.",
		vcharScribeASCII(old_file) ));
		return_value = FALSE;
	}

	if ((!vfsAccess (new_path_dir, vfsCAN_EXECUTE)) ||
		(!vfsAccess (new_path_dir, vfsCAN_WRITE)))
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"RM_file::RM_static_move_media (); Could not write or execute directory for %S.",
		vcharScribeASCII(new_file)));
		return_value = FALSE;
	}

	if (vfsAccess (new_path, vfsFILE_EXISTS))
	{
		if (!vfsAccess (new_path, vfsCAN_WRITE))
		{
			LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
			"RM_file::RM_static_move_media (); Could not over write %S.",
			vcharScribeASCII(new_file) ));
			return_value = FALSE;
		}
		else
		{
		   vfsRemove ( new_path );
		}
	}

	if (return_value && vfsAccess (old_path, vfsFILE_EXISTS))
	{
		// we do a copy and remove because vfsRename doesn't
		// work across file systems
		vfsCopy (old_path, new_path);
		vfsRemove ( old_path );
	}

	vfsDestroyPath (old_path_dir);
	vfsDestroyPath (new_path_dir);
	vfsDestroyPath (old_path);
	vfsDestroyPath (new_path);


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_static_move_media (return_value=%d).",
	return_value));
	return return_value;
}

RM_render_media::t_create_render_media
RM_file::RM_create_media (const char *p_media_name, t_boolean overwrite_flag)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_create_media (p_media_name='%S', overwrite_flag=%d).",
	vcharScribeASCII(p_media_name), overwrite_flag));


	t_boolean file_created = TRUE;

	if (strcmp (p_media_name, "") == 0)
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"End #1 RM_file::RM_create_media (UNABLE_TO_OPEN_MEDIA)."));
		return RM_render_media::UNABLE_TO_OPEN_MEDIA;
	}


	path_ptr = vfsPathFromStrScribed (vcharScribeASCII (p_media_name));
	vfsExpandVariablesInPath (path_ptr);


	// If overwrite_flag is FALSE, check for file exsitance.
	//
	if (overwrite_flag == FALSE)
	{
		if (vfsAccess (path_ptr, vfsFILE_EXISTS))
		{
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End #2 RM_file::RM_create_media (MEDIA_ALREADY_EXISTS)."));
			return RM_render_media::MEDIA_ALREADY_EXISTS;
		}
	}


	// Verify that that user can write and execute the directory
	// of the file.
	//
	vfsPath * path_dir = vfsClonePath (path_ptr);
	vfsDeletePathElementAt (path_dir,
		(vfsGetPathElementCount (path_ptr) - 1));

	if (vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		if ((!vfsAccess (path_ptr, vfsCAN_WRITE)) ||
			(!vfsAccess (path_dir, vfsCAN_EXECUTE)))
		{
			vfsDestroyPath (path_dir);
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End #3 RM_file::RM_create_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}
	else
	{
		if ((!vfsAccess (path_dir, vfsCAN_EXECUTE)) ||
			(!vfsAccess (path_dir, vfsCAN_WRITE)))
		{
			vfsDestroyPath (path_dir);
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End #4 RM_file::RM_create_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}

	// Verify that that user can write the file if it exists.
	//
	if (vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		if (!vfsAccess (path_ptr, vfsCAN_WRITE))
		{
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End #5 RM_file::RM_create_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}
	else
	{
		vexWITH_HANDLING {

			vfsCreateFile (path_ptr, vfsOWNER_READ | vfsOWNER_WRITE |
				vfsGROUP_READ | vfsOTHER_READ);
            file_name_string = p_media_name;
        
		} vexON_EXCEPTION {

			file_created = FALSE;

		} vexEND_HANDLING;
	}


	file_ptr = 0;
	if (file_created)
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End #6 RM_file::RM_create_media (MEDIA_CREATED)...file_name = %S",
		vcharScribeASCII(file_name_string.char_ptr()) ));
		return RM_render_media::MEDIA_CREATED;
	}
    else
    {
        vfsDestroyPath (path_ptr);
        path_ptr = 0;
    }
    

	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End #7 RM_file::RM_create_media (UNABLE_TO_OPEN_MEDIA)."));
	return RM_render_media::UNABLE_TO_OPEN_MEDIA;
}


RM_render_media::t_create_render_media
RM_file::RM_create_temp_media ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_create_temp_media ()."));


	String temp_name = U_environment::get_temp_dir() + "ptXXXXXX";
	vchar* generated_name
		= vstrCloneScribed (vcharScribeLiteral (temp_name.char_ptr()));
	path_ptr = vfsPathFromStr (vfsGenerateTempName (generated_name));


	while (vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		vfsDestroyPath (path_ptr);
		vstrDestroy (generated_name);

		generated_name
			= vstrCloneScribed (vcharScribeLiteral (temp_name.char_ptr()));
		path_ptr = vfsPathFromStr (vfsGenerateTempName (generated_name));
	}

	char temp_file_name [256];
	temp_file_name [0] = '\0';
	vcharExport (vcharScribeSystemExport (generated_name), temp_file_name);

	
	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"RM_file::RM_create_temp_media temp file name is '%S'.",
	vcharScribeASCII(temp_file_name) ));

    vstrDestroy (generated_name);

	if (strcmp (temp_file_name, "") == 0)
	{
		vfsDestroyPath (path_ptr);
        path_ptr = 0;

		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_create_temp_media (UNABLE_TO_OPEN_MEDIA)."));
		return RM_render_media::UNABLE_TO_OPEN_MEDIA;
	}

	t_boolean file_created = TRUE;

	vexWITH_HANDLING {

		vfsCreateFile (path_ptr, vfsOWNER_READ | vfsOWNER_WRITE |
			vfsGROUP_READ | vfsOTHER_READ);
		file_name_string = temp_file_name;

	} vexON_EXCEPTION {

		file_created = FALSE;

	} vexEND_HANDLING;


	file_ptr = 0;
	if (file_created)
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_create_temp_media (MEDIA_CREATED)."));
		return RM_render_media::MEDIA_CREATED;
	}
    else
    {
        vfsDestroyPath (path_ptr);
        path_ptr = 0;
    }

	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_create_temp_media (UNABLE_TO_OPEN_MEDIA)."));
	return RM_render_media::UNABLE_TO_OPEN_MEDIA;
}


void
RM_file::RM_close_media (const char *p_media_name)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_close_media (p_media_name='%S').",
	vcharScribeASCII(p_media_name) ));


	if (file_ptr == 0)
	{
		LOG_ERROR ((L_log_string,
		"RM_file::RM_close_media () RM_close_media called without a file open."));
	}
	else
	{
      vexWITH_HANDLING {
        
        if (path_ptr)
          vfsDestroyPath (path_ptr);
        path_ptr = vfsPathFromFile((vfsFile *)file_ptr);
        vfsCloseFile ((vfsFile *)file_ptr);

      } vexON_EXCEPTION {

        LOG_ERROR ((L_log_string,
                    "RM_file::RM_close_media ()\n\tCould not close unix file."));

      } vexEND_HANDLING;
	}

	file_ptr = 0;


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_file::RM_close_media ()."));
}


void
RM_file::RM_close ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_close ()."));


	if (file_ptr != 0)
	{
		vexWITH_HANDLING {

            if (path_ptr)
              vfsDestroyPath (path_ptr);
            path_ptr = vfsPathFromFile((vfsFile *)file_ptr);
			vfsCloseFile ((vfsFile *)file_ptr);

		} vexON_EXCEPTION {

			LOG_ERROR ((L_log_string,
			"RM_file::RM_close ()\n\tException raised closing file."));

		} vexEND_HANDLING;
	}

	file_ptr = 0;


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_file::RM_close ()."));
    
}


void
RM_file::RM_open (vfsType p_open_type)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_file::RM_open ()."));

    //  vfsType:
    //     vfsOPEN_READ_ONLY        Open for reading only. 
    //     vfsOPEN_READ_WRITE       Open for reading and writing. 
    //     vfsOPEN_WRITE_TRUNCATE   Open for reading and writing and
    //            the file was truncated to zero length when it was opened. 
    //     vfsOPEN_APPEND           Open for append

    t_boolean close_reqd = FALSE;
    vexWITH_HANDLING
      {
        if (file_ptr != 0)
          {
            switch (p_open_type)
              {
              case vfsOPEN_READ_ONLY:
                switch (open_type)
                  {
                  case vfsOPEN_READ_ONLY:
                    break;
                  case vfsOPEN_READ_WRITE:
                  case vfsOPEN_WRITE_TRUNCATE:
                  case vfsOPEN_APPEND:
                  default:
                    close_reqd = TRUE;
                    break;
                  }
                break;
              case vfsOPEN_READ_WRITE:
              case vfsOPEN_WRITE_TRUNCATE:
              case vfsOPEN_APPEND:
                switch (open_type)
                  {
                  case vfsOPEN_READ_ONLY:
                    close_reqd = TRUE;
                    break;
                  case vfsOPEN_READ_WRITE:
                  case vfsOPEN_WRITE_TRUNCATE:
                  case vfsOPEN_APPEND:
                  default:
                    break;
                  }
                break;
              }
            
            if (close_reqd)
              {
                if (path_ptr)
                  vfsDestroyPath (path_ptr);
                path_ptr = vfsPathFromFile((vfsFile *)file_ptr);
                vfsCloseFile ((vfsFile *)file_ptr);
                file_ptr = 0;
              }
          }
        if ( (file_ptr == 0) && (path_ptr) )
          {
            open_type = p_open_type;
            file_ptr = vfsOpenFile(path_ptr, open_type);
          }
      }
    vexON_EXCEPTION
      {
        file_ptr = 0;
        LOG_ERROR ((L_log_string,
                    "RM_file::RM_open ()\n\tCould not open file."));
        
      }
    vexEND_HANDLING;

	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_file::RM_open ()."));
}


RM_render_media::t_create_render_media
RM_file::RM_overwrite_media (const char *p_media_name)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin/End  RM_file::RM_overwrite_media (p_media_name='%S').",
	vcharScribeASCII(p_media_name) ));


	return RM_create_media (p_media_name, TRUE);
}


RM_render_media::t_create_render_media
RM_file::RM_open_media (const char *p_media_name)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_open_media (p_media_name='%S').",
	vcharScribeASCII(p_media_name) ));


	if (strcmp (p_media_name, "") == 0)
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End #1 RM_file::RM_open_media (UNABLE_TO_OPEN_MEDIA)."));
		return RM_render_media::UNABLE_TO_OPEN_MEDIA;
	}

	path_ptr = vfsPathFromStrScribed
		(vcharScribeASCII (p_media_name));
	vfsExpandVariablesInPath (path_ptr);

	if (!vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		vfsDestroyPath (path_ptr);
        path_ptr = 0;

		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End #2 RM_file::RM_open_media (UNABLE_TO_OPEN_MEDIA)."));
		return RM_render_media::UNABLE_TO_OPEN_MEDIA;
	}
	else
	{
		if (!vfsAccess (path_ptr, vfsCAN_READ))
		{
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End #3 RM_file::RM_open_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}


	vexWITH_HANDLING {

      open_type = vfsOPEN_READ_ONLY;
      file_ptr = (void *)vfsOpenFile (path_ptr, open_type);

	} vexON_EXCEPTION {

		file_ptr = 0;

	} vexEND_HANDLING;


	if (file_ptr != 0)
	{
		file_name_string = p_media_name;
		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End #4 RM_file::RM_open_media (MEDIA_OPENED)."));
		return RM_render_media::MEDIA_OPENED;
	}
    else
    {
        vfsDestroyPath (path_ptr);
        path_ptr = 0;
    }


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End #5 RM_file::RM_open_media (UNABLE_TO_OPEN_MEDIA)."));
	return RM_render_media::UNABLE_TO_OPEN_MEDIA;
}


RM_render_media::t_create_render_media
RM_file::RM_append_media (const char *p_media_name)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_append_media (p_media_name='%S').",
	vcharScribeASCII(p_media_name) ));


	t_boolean file_created = TRUE;

	if (strcmp (p_media_name, "") == 0)
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_append_media (UNABLE_TO_OPEN_MEDIA)."));
		return RM_render_media::UNABLE_TO_OPEN_MEDIA;
	}

	path_ptr = vfsPathFromStrScribed (vcharScribeASCII (p_media_name));
	vfsExpandVariablesInPath (path_ptr);

	// Verify that that user can write and execute the directory
	// of the file.
	//
	vfsPath * path_dir = vfsClonePath (path_ptr);
	vfsDeletePathElementAt (path_dir,
		(vfsGetPathElementCount (path_ptr) - 1));

	if (vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		if ((!vfsAccess (path_ptr, vfsCAN_WRITE)) ||
			(!vfsAccess (path_dir, vfsCAN_EXECUTE)))
		{
			vfsDestroyPath (path_dir);
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End  RM_file::RM_append_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}
	else
	{
		if ((!vfsAccess (path_dir, vfsCAN_EXECUTE)) ||
			(!vfsAccess (path_dir, vfsCAN_WRITE)))
		{
			vfsDestroyPath (path_dir);
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End  RM_file::RM_append_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}

	// Verify that that user can write the file if it exists.
	//
	if (vfsAccess (path_ptr, vfsFILE_EXISTS))
	{
		if (!vfsAccess (path_ptr, vfsCAN_WRITE))
		{
			vfsDestroyPath (path_ptr);
            path_ptr = 0;

			LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
			"End  RM_file::RM_append_media (UNABLE_TO_OPEN_MEDIA)."));
			return RM_render_media::UNABLE_TO_OPEN_MEDIA;
		}
	}
	else
	{
		vexWITH_HANDLING {

			vfsCreateFile (path_ptr, vfsOWNER_READ | vfsOWNER_WRITE |
				vfsGROUP_READ | vfsOTHER_READ);

		} vexON_EXCEPTION {

			file_created = FALSE;

		} vexEND_HANDLING;
	}


	file_ptr = 0;
	if (file_created)
	{
      file_name_string = p_media_name;
      RM_open(vfsOPEN_APPEND);

      LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_append_media (MEDIA_CREATED)."));
      return RM_render_media::MEDIA_CREATED;
	}


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_append_media (UNABLE_TO_OPEN_MEDIA)."));
	return RM_render_media::UNABLE_TO_OPEN_MEDIA;
}


void
RM_file::RM_flush_media_to_device (const char *p_device_str )
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_flush_media_to_printer\n\t()."));

	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_file::RM_flush_media_to_device ()."));

}



void
RM_file::RM_write (const char *p_string)
{
	LOG_TRACE (L_RENDER, L_HI_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_write (p_string=%S).",
	vcharScribeASCII(p_string) ));

    RM_open(vfsOPEN_WRITE_TRUNCATE);

	if (file_ptr != 0)
	{
		vfsWriteStringScribed (vcharScribeASCII (p_string),
			(vfsFile *)file_ptr);
	}

	LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_write ()."));
}

void
RM_file::RM_write (const vchar *p_string)
{
	LOG_TRACE (L_RENDER, L_HI_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_write (vchar p_string)."));


    RM_open(vfsOPEN_WRITE_TRUNCATE);

	if (file_ptr != 0)
	{
		vfsWriteString (p_string,	(vfsFile *)file_ptr);
	}


	LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_write ()."));
}



char *
RM_file::RM_read ()
{
  LOG_TRACE (L_RENDER, L_HI_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_read ()."));

  vchar temp_read_string [READ_STRING_SIZE];

  char * return_ptr = 0;

  RM_open(vfsOPEN_READ_ONLY);
  
  if (file_ptr != 0)
	{
      if (vfsReadString (temp_read_string, READ_STRING_SIZE,
                         (vfsFile *)file_ptr))
		{
          vchar nl = vcharFromASCII('\n');
          vchar cr = vcharFromASCII('\r');
          vchar nil = vcharFromASCII('\0');
          int slen = vcharLength(temp_read_string);
          if ( slen >= 2 && temp_read_string[slen-1] == nl &&
               temp_read_string[slen-2] == cr )
			{
              temp_read_string[slen-2] = nl;
              temp_read_string[slen-1] = nil;
			}
          vcharExport (vcharScribeSystemExport(temp_read_string), read_string);
          return_ptr = read_string;
		}
	}

  if (return_ptr != 0)
	{
      LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_read (read_string='%S').",
        vcharScribeASCII(read_string) ));
	}
  else
	{
      LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_read ()."));
	}
  return return_ptr;
}


vchar *
RM_file::RM_read_vchar ()
{
  LOG_TRACE (L_RENDER, L_HI_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_read_vchar ()."));

  vchar * return_ptr = 0;
  RM_open(vfsOPEN_READ_ONLY);

  if (file_ptr != 0)
	{
      if (vfsReadString (vchar_read_string, READ_STRING_SIZE,
                         (vfsFile *)file_ptr))
		{
          vchar nl = vcharFromASCII('\n');
          vchar cr = vcharFromASCII('\r');
          vchar nil = vcharFromASCII('\0');
          int slen = vcharLength(vchar_read_string);
          if ( slen >= 2 && vchar_read_string[slen-1] == nl &&
               vchar_read_string[slen-2] == cr )
			{
              vchar_read_string[slen-2] = nl;
              vchar_read_string[slen-1] = nil;
			}
      
          return_ptr = vchar_read_string;
		}
	}

  if (return_ptr != 0)
	{
      LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_read_vchar (read_string='%s').",
		vchar_read_string ));
	}
  else
	{
      LOG_TRACE (L_RENDER, L_HI_FUNCTION_END, (L_log_string,
		"End  RM_file::RM_read_vchar ()."));
	}
  return return_ptr;
}

t_boolean
RM_file::RM_read_file(vbyte *buffer, int size)
{
  t_boolean rc = FALSE;
  int numBytes;
  RM_open(vfsOPEN_READ_ONLY);
  if (file_ptr)
	{
      vexWITH_HANDLING {
        //  Read the file into the buffer using bytes as the reference size.
        numBytes = vfsReadFile(buffer, sizeof(vbyte), size, (vfsFile *)file_ptr);
        if (numBytes == size)
          {
            rc = TRUE;
          }
      } vexON_EXCEPTION {
      } vexEND_HANDLING;
    }
  
  return rc;
}



void
RM_file::RM_rewind ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_rewind ()."));


	if (file_ptr != 0)
	{
		vfsRewindFile ((vfsFile *)file_ptr);
	}


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_rewind ()."));
}


void
RM_file::RM_static_remove_media (const char* p_media_name)
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_static_remove_media (p_media_name=\"%S\").",
	vcharScribeASCII(p_media_name) ));


	vfsPath* l_path_ptr = vfsPathFromStrScribed
		(vcharScribeASCII (p_media_name));
	vfsExpandVariablesInPath (l_path_ptr);

	vfsPath * path_dir = vfsClonePath (l_path_ptr);
	vfsDeletePathElementAt (path_dir,
		(vfsGetPathElementCount (l_path_ptr) - 1));


	if (vfsAccess (l_path_ptr, vfsFILE_EXISTS))
	{
        if ( DELETE_CRITERIA(l_path_ptr, path_dir) )
		{
			vexWITH_HANDLING {

				vfsRemove (l_path_ptr);

			} vexON_EXCEPTION {
			} vexEND_HANDLING;
		}
		else
		{
			LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
			"RM_file::RM_static_remove_media (): User does not have file write access."));
		}
	}
	else
	{
		LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
		"RM_file::RM_static_remove_media (): File does not exists"));
	}

	vfsDestroyPath (l_path_ptr);
	vfsDestroyPath (path_dir);


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_static_remove_media ()."));
}


void
RM_file::RM_remove_media ()
{
	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_remove_media ()...file name = %S",
	vcharScribeASCII(file_name_string.char_ptr()) ));


	if (file_ptr != 0)
	{
		path_ptr = vfsPathFromStrScribed
			(vcharScribeASCII ((char*) file_name_string.char_ptr ()));
		vfsExpandVariablesInPath (path_ptr);

		vfsPath * path_dir = vfsClonePath (path_ptr);
		vfsDeletePathElementAt (path_dir,
			(vfsGetPathElementCount (path_ptr) - 1));

		if (vfsAccess (path_ptr, vfsFILE_EXISTS))
		{
		  if ( DELETE_CRITERIA(path_ptr, path_dir) )
			{
				vexWITH_HANDLING {

					LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
					"RM_file::RM_remove_media ()...removing file %S",
					vcharScribeASCII(file_name_string.char_ptr()) ));

					vfsCloseFile ((vfsFile *)file_ptr);
                    if (path_ptr)
                      vfsRemove (path_ptr);

				} vexON_EXCEPTION {
				} vexEND_HANDLING;

				file_ptr = 0;
			}
			else
			{
				LOG_TRACE (L_RENDER, L_FUNCTION_STEP_LO, (L_log_string,
				"RM_file::RM_remove_media (): User does not have file write access."));
			}
		}

		vfsDestroyPath (path_dir);
        path_ptr = 0;
	}


	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End  RM_file::RM_remove_media ()."));
}

