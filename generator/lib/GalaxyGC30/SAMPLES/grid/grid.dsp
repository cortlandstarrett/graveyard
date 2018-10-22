# Microsoft Developer Studio Project File - Name="grid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601
CFG=grid - Win32 (x86) Release Galaxy DLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "grid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "grid.mak" CFG="grid - Win32 (x86) Debug Static"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "grid - Win32 (x86) Release Galaxy DLL" (based on "Win32 (x86) Application")
!MESSAGE "grid - Win32 (x86) Debug Galaxy DLL" (based on "Win32 (x86) Application")
!MESSAGE "grid - Win32 (x86) Release Static" (based on "Win32 (x86) Application")
!MESSAGE "grid - Win32 (x86) Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "grid - Win32 (ALPHA) Release Galaxy DLL" (based on "Win32 (ALPHA) Application")
!MESSAGE "grid - Win32 (ALPHA) Debug Galaxy DLL" (based on "Win32 (ALPHA) Application")
!MESSAGE "grid - Win32 (ALPHA) Release Static" (based on "Win32 (ALPHA) Application")
!MESSAGE "grid - Win32 (ALPHA) Debug Static" (based on "Win32 (ALPHA) Application")
!MESSAGE 
# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "grid - Win32 (x86) Release Galaxy DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\RelGDLL"
# PROP BASE Intermediate_Dir ".\RelGDLL"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\RelGDLL"
# PROP Intermediate_Dir ".\RelGDLL"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D vportGALAXY_DLL=1 /D "_WINDOWS" /D vdebugDEBUG=0 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "x86" /NDEBUG
# ADD MTL /nologo /D "x86" /mktyplib203 /NDEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /machine:IX86

!ELSEIF  "$(CFG)" == "grid - Win32 (x86) Debug Galaxy DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\DbgGDLL"
# PROP BASE Intermediate_Dir ".\DbgGDLL"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DbgGDLL"
# PROP Intermediate_Dir ".\DbgGDLL"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D vportGALAXY_DLL=1 /D "_WINDOWS" /D vdebugDEBUG=1 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "x86" /_DEBUG
# ADD MTL /nologo /D "x86" /mktyplib203 /_DEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /debug /machine:IX86

!ELSEIF  "$(CFG)" == "grid - Win32 (x86) Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\RelStatic"
# PROP BASE Intermediate_Dir ".\RelStatic"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\RelStatic"
# PROP Intermediate_Dir ".\RelStatic"
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D vdebugDEBUG=0 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "x86" /NDEBUG
# ADD MTL /nologo /D "x86" /mktyplib203 /NDEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /machine:IX86

!ELSEIF  "$(CFG)" == "grid - Win32 (x86) Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\DbgStatic"
# PROP BASE Intermediate_Dir ".\DbgStatic"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DbgStatic"
# PROP Intermediate_Dir ".\DbgStatic"
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D vdebugDEBUG=1 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "x86" /_DEBUG
# ADD MTL /nologo /D "x86" /mktyplib203 /_DEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /debug /machine:IX86

!ELSEIF  "$(CFG)" == "grid - Win32 (ALPHA) Release Galaxy DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\RelGDLL"
# PROP BASE Intermediate_Dir ".\RelGDLL"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\RelGDLL"
# PROP Intermediate_Dir ".\RelGDLL"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D vportGALAXY_DLL=1 /D "_WINDOWS" /D vdebugDEBUG=0 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "ALPHA" /NDEBUG
# ADD MTL /nologo /D "ALPHA" /mktyplib203 /NDEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "grid - Win32 (ALPHA) Debug Galaxy DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\DbgGDLL"
# PROP BASE Intermediate_Dir ".\DbgGDLL"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DbgGDLL"
# PROP Intermediate_Dir ".\DbgGDLL"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D vportGALAXY_DLL=1 /D "_WINDOWS" /D vdebugDEBUG=1 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "ALPHA" /_DEBUG
# ADD MTL /nologo /D "ALPHA" /mktyplib203 /_DEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /debug /machine:ALPHA

!ELSEIF  "$(CFG)" == "grid - Win32 (ALPHA) Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\RelStatic"
# PROP BASE Intermediate_Dir ".\RelStatic"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\RelStatic"
# PROP Intermediate_Dir ".\RelStatic"
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D vdebugDEBUG=0 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "ALPHA" /NDEBUG
# ADD MTL /nologo /D "ALPHA" /mktyplib203 /NDEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "grid - Win32 (ALPHA) Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\DbgStatic"
# PROP BASE Intermediate_Dir ".\DbgStatic"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DbgStatic"
# PROP Intermediate_Dir ".\DbgStatic"
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D vdebugDEBUG=1 /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "ALPHA" /_DEBUG
# ADD MTL /nologo /D "ALPHA" /mktyplib203 /_DEBUG
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /debug /machine:ALPHA

!ENDIF 

# Begin Target

# Name "grid - Win32 (x86) Release Galaxy DLL"
# Name "grid - Win32 (x86) Debug Galaxy DLL"
# Name "grid - Win32 (x86) Release Static"
# Name "grid - Win32 (x86) Debug Static"
# Name "grid - Win32 (ALPHA) Release Galaxy DLL"
# Name "grid - Win32 (ALPHA) Debug Galaxy DLL"
# Name "grid - Win32 (ALPHA) Release Static"
# Name "grid - Win32 (ALPHA) Debug Static"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\grid.c

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
