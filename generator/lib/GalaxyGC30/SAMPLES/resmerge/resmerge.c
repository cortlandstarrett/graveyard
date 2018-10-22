/* $Id: resmerge.c,v 1.5 1994/08/12 20:17:40 hoyle Exp $ */

/*
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/****************************************************************************
 * Source File, merge.c
 *
 * Managers Illustrated:
 *     vresource
 *
 * Description Of Sample:
 *     This code illustrates how to merge multiple resource files into a 
 *     destination resource file.  The destination resource file is the last
 *     resource file in the command line.  If the destination resource file
 *     does not exist, it is created.  Use the option -replace if you want
 *     to replace existing resources in the destination resource file.
 *
 * NOTE:  If the destination resource file exists and an error occurs during
 *        the merge, the destination resource file can become corrupted.
 *
 * History:
 *     Written for 1.2 release, 7/14/93
 *
 *     Modified to handle resource arrays correctly, cleaned up unneeded
 *     special cases, general updating.
 *
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER		/* for exit */
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

/*
 *  Create mode for destination resource file if does not exist
 */
#define CREATE_MODE \
  ( vfsOWNER_WRITE | vfsOWNER_READ | vfsGROUP_READ | vfsOTHER_READ )

/*
 *  Forward Declations
 */
static void _resourceCopy( vresource from, vresource to );

/*
 *  Global Variables
 */
static const vname	*inheritTag;
static vbool		 replaceExisting = FALSE;

/*************************************************************
  _resourceCopyDict
**************************************************************/
static void _resourceCopyDict( vresource from, vresource to )
{
  int		 count, i;
  vresource	 currRes;
  vresource  	 newRes;
  const vchar	*currResTag;

  count = vresourceCountComponents( from );
  for ( i = 0; i < count; i++ )
    {
      currRes = vresourceGetNthComponent( from, i, &currResTag );
      if ( vresourceType( currRes ) == vresourceARRAY )
	newRes = vresourceCreateArray( to, currResTag, 
				       vresourceArrayType( currRes ),
				       vresourceCountComponents( currRes ) );
      else
	newRes = vresourceCreate( to, currResTag, vresourceType( currRes ) );
      _resourceCopy( currRes, newRes );
    }
}

/*************************************************************
  _resourceCopyArray
**************************************************************/
static void _resourceCopyArray( vresource from, vresource to )
{
  int		 count, restype, i;
  vchar		*str;

  count = vresourceCountComponents( from );
  restype = vresourceArrayType( from );
  for ( i = 0; i < count; i++ )
    {
      switch ( restype )
	{
	case vresourceUNTYPED 	:
	  break;
	case vresourceDICT   	:
	  _resourceCopy( vresourceGetAt( from, i ), 
			 vresourceCreateAt( to, i, vresourceDICT ) );
	  break;
	case vresourceBOOLEAN	:
	  vresourceSetBooleanAt( to, i, vresourceGetBooleanAt( from, i ) );
	  break;
	case vresourceINTEGER	:
	  vresourceSetIntegerAt( to, i, vresourceGetIntegerAt( from, i ) );
	  break;
	case vresourceSTRING	:
	  str = vresourceGetStringAt( from, i );
	  vresourceSetStringAt( to, i, str );
	  vstrDestroy( str );
	  break;
	case vresourceFIXED		:
	  vresourceSetFixedAt( to, i, vresourceGetFixedAt( from, i ) );
	  break;
	case vresourceCHAR		:
	  vresourceSetCharAt( to, i, vresourceGetCharAt( from, i ) );
	  break;
	case vresourceFLOAT		:
	  vresourceSetFloatAt( to, i, vresourceGetFloatAt( from, i ) );
	  break;
	case vresourceTAG		:
	  vresourceSetTagAt( to, i, vresourceGetTagAt( from, i ) );
	  break;
	case vresourceARRAY		:
	  _resourceCopy( vresourceGetAt( from, i ), vresourceGetAt( to, i ) );
	  break;
	case vresourceOPAQUE	:
	  _resourceCopy( vresourceGetAt( from, i ), vresourceGetAt( to, i ) );
	  break;
	}
    }
}

/*************************************************************
  _resourceCopy
**************************************************************/
static void _resourceCopy( vresource from, vresource to )
{
  vchar		*str;
  vbyte		*data;
  size_t       	 size;

  switch( vresourceType( from ) )
    {
    case vresourceUNTYPED 	:
      break;
    case vresourceDICT   	:
      _resourceCopyDict( from, to );
      break;
    case vresourceBOOLEAN	:
      vresourceSetBoolean( to, vresourceTAG_NULL, 
			   vresourceGetBoolean( from, vresourceTAG_NULL ) );
      break;
    case vresourceINTEGER	:
      vresourceSetInteger( to, vresourceTAG_NULL, 
			   vresourceGetInteger( from, vresourceTAG_NULL ) );
      break;
    case vresourceSTRING	:
      str = vresourceGetString( from, vresourceTAG_NULL );
      vresourceSetString( to, vresourceTAG_NULL, str );
      vstrDestroy( str );
      break;
    case vresourceFIXED		:
      vresourceSetFixed( to, vresourceTAG_NULL, 
			 vresourceGetFixed( from, vresourceTAG_NULL ) );
      break;
    case vresourceCHAR		:
      vresourceSetChar( to, vresourceTAG_NULL, 
		        vresourceGetChar( from, vresourceTAG_NULL ) );
      break;
    case vresourceFLOAT		:
      vresourceSetFloat( to, vresourceTAG_NULL, 
			 vresourceGetFloat( from, vresourceTAG_NULL ) );
      break;
    case vresourceTAG		:
      vresourceSetTag( to, vresourceTAG_NULL, 
		       vresourceGetTag( from, vresourceTAG_NULL ) );
      break;
    case vresourceARRAY		:
      _resourceCopyArray( from, to );
      break;
    case vresourceOPAQUE	:
      data = vresourceGetOpaque( from, vresourceTAG_NULL, &size );
      vresourceSetOpaque( to, vresourceTAG_NULL, data, size );
      vmemFree( data );
      break;
    }
}

/*************************************************************
  _mergeObjectInheritance

  merges the object inheritance dictionary from the resource
  file "from" to the resource file "to"
**************************************************************/
static void _mergeObjectInheritance( vresource from, vresource to )
{
  int            count, i;
  vresource      currRes;   
  const vname   *currResTag;
  vresource      res;
  
  count = vresourceCountComponents( from );
  for ( i = 0; i < count; i++ )
    {
      currRes = vresourceGetNthComponent( from, i, &currResTag );
      if ( !vresourceTestGet( to, currResTag, &res ) )
        vresourceSetTag( to, currResTag,   
                         vresourceGetTag( currRes, vresourceTAG_NULL ) );
    }
}
      
/*************************************************************
  _mergeFiles
                                                 
  merges the contents of the file "from" into the file "to"
**************************************************************/
static void _mergeFiles( vresource from, vresource to )
{
  int            count, i;
  vresource      currRes, newRes;
  const vname   *currResTag;
  vresource      fromInherit, toInherit;
  vresource      res;

  /*
   *  Merge contents of from into to
   */
  count = vresourceCountComponents( from );
  for ( i = 0; i < count; i++ )
    {
      currRes = vresourceGetNthComponent( from, i, &currResTag );
      if ( currResTag != inheritTag &&
           ( replaceExisting || !vresourceTestGet( to, currResTag, &res ) ) )
        {
	  if ( vresourceType( currRes ) == vresourceARRAY )
	    newRes = vresourceCreateArray( to, currResTag, 
					   vresourceArrayType( currRes ),
					   vresourceCountComponents( currRes ) );
	  else
	    newRes = vresourceCreate( to, currResTag, vresourceType( currRes ) );
	  _resourceCopy( currRes, newRes );
        }
    }
  
  /*
   *  Merge object inheritance dictionary
   */
  if ( vresourceTestGet( from, inheritTag, &fromInherit ) &&
       vresourceTestGet( to, inheritTag, &toInherit ) )
    _mergeObjectInheritance( fromInherit, toInherit );
}

/*************************************************************
 **********************     main     ************************
**************************************************************/
int main( short argc, char *argv[] )
{
  vfsPath		**paths;
  int			  numFiles;
  volatile vresource	  to;
  volatile vresource	  from;
  vfsPath * volatile	  path;
  volatile int		  i;
  vstr			 *str;
  vchar			  buffer[255];
  volatile vbool	  error = FALSE;
  const vname		 *name;

  /*
   *  Initialize preference for replacing existing resources
   */
  name = vnameInternGlobalLiteral( "replace" );
  vprefStore( name, vnameNULL );

  /*
   *  Initialize proper classes
   */
  vstartup( argc, argv );

  /*
   *  Check value of preference
   */
  replaceExisting = ( vprefLoad( name ) != NULL );

  /*
   *  Assume remaining arguments are vfsPaths the last path is the 
   *    destination resource file
   */
  vfsGetArgs( &numFiles, (const vfsPath ***) &paths);
  if ( numFiles > 2 )
    {
      path = paths[numFiles-1];

      vexWITH_HANDLING
	{
	  if ( vfsAccess( path, vfsFILE_EXISTS ) )
	    to = vresourceOpenFile( path, vfsOPEN_READ_WRITE );
	  else
	    to = vresourceCreateFile( path, CREATE_MODE );
	}
      vexON_EXCEPTION
	{
	  str = vfsPathToStr( path );
	  vcharExport( vcharScribe( str ), buffer );
	  vstrDestroy( str );
	  fprintf( stdout, "error opening or creating destination file %s\n",
		   buffer );
	  error = TRUE;
	}
      vexEND_HANDLING;

      if ( error )
	exit( EXIT_FAILURE );

      /*
       *  Create object inheritance dictionary in destination file if it
       *   does not exist
       */
      inheritTag = vnameInternGlobalLiteral( "vobjectInheritance" );
      (void) vresourceMake( to, inheritTag );
      
      /*
       *  Merge the rest of the files into the destination file
       */
      for ( i = 1; i < numFiles - 1; i++ )
	{
	  path = paths[i];
	  
	  vexWITH_HANDLING
	    {
	      from = vresourceOpenFile( path, vfsOPEN_READ_ONLY );
	    }
	  vexON_EXCEPTION
	    {
	      str = vfsPathToStr( path );
	      vcharExport( vcharScribe( str ), buffer );
	      vstrDestroy( str );
	      fprintf( stdout, "error opening resource file %s\n", buffer );
	      error = TRUE;
	    }
	  vexEND_HANDLING;

	  if ( error )
	    exit( EXIT_FAILURE );

	  _mergeFiles( from, to );
	  vresourceCloseFile( from );
	}

      vresourceCloseFile( to );
    }

  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}
