# Microsoft Developer Studio Project File - Name="o6pmfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=o6pmfc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "o6pmfc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "o6pmfc.mak" CFG="o6pmfc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "o6pmfc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "o6pmfc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "o6pmfc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "o6pmfc__"
# PROP BASE Intermediate_Dir "o6pmfc__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /EHa /c
# ADD CPP /nologo /MD /W3 /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS /I$(OS_ROOTDIR)\include" /D "_WINDLL" /D "_AFXDLL" /D "_OSMFCDLL" /FD /EHa /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x810 /d "NDEBUG"
# ADD RSC /l 0x810 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 $(OS_ROOTDIR)\lib\ostore.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "o6pmfc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "o6pmfc_0"
# PROP BASE Intermediate_Dir "o6pmfc_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /EHa /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS /I$(OS_ROOTDIR)\include" /D "_WINDLL" /D "_AFXDLL" /D "_OSMFCDLL" /FD /EHa /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x810 /d "_DEBUG"
# ADD RSC /l 0x810 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(OS_ROOTDIR)\lib\ostored.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"o6pmfcd.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "o6pmfc - Win32 Release"
# Name "o6pmfc - Win32 Debug"
# Begin Source File

SOURCE=.\oscstring.cpp
# End Source File
# End Target
# End Project
