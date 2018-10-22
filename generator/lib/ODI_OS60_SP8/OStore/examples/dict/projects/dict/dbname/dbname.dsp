# Microsoft Developer Studio Project File - Name="dbname" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=dbname - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dbname.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbname.mak" CFG="dbname - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbname - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "dbname - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "dbname - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "dbname - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "dbname - Win32 Release"
# Name "dbname - Win32 Debug"
# Begin Source File

SOURCE=..\..\..\dbname.h

!IF  "$(CFG)" == "dbname - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dbname - Win32 Debug"

# Begin Custom Build
OutDir=.\Debug
WkspName=dict
InputPath=..\..\..\dbname.h

"dbname.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if     not     defined     OS_EXAMPLE_DB_DIR     set     OS_EXAMPLE_DB_DIR=$(OutDir)\  
	echo OS_EXAMPLE_DB_DIR=%OS_EXAMPLE_DB_DIR% 
	set EXAMPLE_DB=%OS_EXAMPLE_DB_DIR%$(WkspName).db 
	set CODE=static char *example_db_name= "%EXAMPLE_DB:\=/%"; 
	if not exist $(InputPath) ( 
	echo %CODE% > $(InputPath) 
	) else ( 
	for /f %%I in ($(InputPath)) do @set OLDCODE=%%I 
	if NOT "%OLDCODE%"=="%CODE%" ( 
	echo %CODE% > $(InputPath) 
	) 
	) 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
