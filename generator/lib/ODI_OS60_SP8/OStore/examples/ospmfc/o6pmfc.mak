# Microsoft Developer Studio Generated NMAKE File, Based on o6pmfc.dsp
!IF "$(CFG)" == ""
CFG=o6pmfc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to o6pmfc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "o6pmfc - Win32 Release" && "$(CFG)" != "o6pmfc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "o6pmfc - Win32 Release"

OUTDIR=.
INTDIR=.\Release
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\o6pmfc.dll"


CLEAN :
	-@erase "$(INTDIR)\oscstring.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\o6pmfc.dll"
	-@erase "$(OUTDIR)\o6pmfc.exp"
	-@erase "$(OUTDIR)\o6pmfc.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /I$(OS_ROOTDIR)\include /D "_WINDLL" /D "_AFXDLL" /D "_OSMFCDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\o6pmfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(OS_ROOTDIR)\lib\ostore.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\o6pmfc.pdb" /machine:I386 /out:"$(OUTDIR)\o6pmfc.dll" /implib:"$(OUTDIR)\o6pmfc.lib" 
LINK32_OBJS= \
	"$(INTDIR)\oscstring.obj"

"$(OUTDIR)\o6pmfc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "o6pmfc - Win32 Debug"

OUTDIR=.
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\o6pmfcd.dll"


CLEAN :
	-@erase "$(INTDIR)\oscstring.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\o6pmfcd.dll"
	-@erase "$(OUTDIR)\o6pmfcd.exp"
	-@erase "$(OUTDIR)\o6pmfcd.ilk"
	-@erase "$(OUTDIR)\o6pmfcd.lib"
	-@erase "$(OUTDIR)\o6pmfcd.pdb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /I$(OS_ROOTDIR)\include /D "_WINDLL" /D "_AFXDLL" /D "_OSMFCDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\o6pmfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(OS_ROOTDIR)\lib\ostored.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\o6pmfcd.pdb" /debug /machine:I386 /out:"$(OUTDIR)\o6pmfcd.dll" /implib:"$(OUTDIR)\o6pmfcd.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\oscstring.obj"

"$(OUTDIR)\o6pmfcd.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("o6pmfc.dep")
!INCLUDE "o6pmfc.dep"
!ELSE 
!MESSAGE Warning: cannot find "o6pmfc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "o6pmfc - Win32 Release" || "$(CFG)" == "o6pmfc - Win32 Debug"
SOURCE=.\oscstring.cpp

"$(INTDIR)\oscstring.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

