/*========================================================================
 *
 * File:      $RCSfile: u_file.hh,v $
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
#ifndef		U_FILE_HH
#define		U_FILE_HH

#include <u_media.hh>
#include <u_string.hh>

#include <vchar.h>
#include <vfs.h>

#define READ_STRING_SIZE    32768

#include <vlimits.h>      // _POSIX_PATH_MAX

#ifdef WIN32
#define DELETE_CRITERIA(_PATH_PTR_,_PATH_DIR_) \
    vfsAccess (_PATH_PTR_, vfsCAN_WRITE)

#else
#define DELETE_CRITERIA(_PATH_PTR_,_PATH_DIR_)   \
    (vfsAccess (_PATH_PTR_, vfsCAN_WRITE)) &&   \
    (vfsAccess (_PATH_DIR_, vfsCAN_EXECUTE)) && \
    (vfsAccess (_PATH_DIR_, vfsCAN_WRITE))

#endif

class RM_file : public RM_render_media
{
public:
  // MANAGER FUNCTIONS

  RM_file();
  virtual ~RM_file();
			
  // IMPLEMENTOR FUNCTIONS
  // Rename only works when both old_file and new_file
  // are on the same file system 
  static t_boolean RM_static_rename_media
    (const char * old_file, const char * new_file);

  static t_boolean RM_static_move_media
    (const char * old_file, const char * new_file);

  virtual t_create_render_media RM_create_media
    ( const char *p_media_name, t_boolean overwrite_flag );
  virtual t_create_render_media RM_create_temp_media();
  virtual t_create_render_media RM_overwrite_media( const char *p_media_name );
  virtual t_create_render_media RM_open_media( const char *p_media_name );
  virtual t_create_render_media RM_append_media( const char *p_media_name );
  virtual void RM_remove_media( );
  static  void RM_static_remove_media( const char *p_media_name );
  virtual void RM_close_media( const char *p_media_name );
  virtual void RM_close ();
  virtual void RM_open (vfsType p_open_type);
  virtual void RM_flush_media_to_device( const char *p_device_name  );
  void RM_flush_media_to_printer( void* printer );
  virtual void RM_write( const char *p_string );
  virtual void RM_write( const vchar *p_string );
  virtual char * RM_read();
  virtual vchar * RM_read_vchar();
  virtual t_boolean RM_read_file(vbyte *buffer, int size);
  virtual void RM_rewind();

  String&	get_file_name_string ()
      {return file_name_string; }
	
  t_boolean good();
  t_boolean RM_from_stdin();

protected:

private:

  void *		file_ptr;

  String		file_name_string;
  vfsType open_type;
  vfsPath *path_ptr;

  char read_string [READ_STRING_SIZE];
  vchar vchar_read_string [READ_STRING_SIZE];

};

#endif	
