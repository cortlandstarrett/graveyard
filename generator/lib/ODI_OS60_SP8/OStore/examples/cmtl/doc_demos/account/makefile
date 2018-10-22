# makefile for microsoft C++ command-line compiler (cl)

MAIN_APP= account
IMPL_SRC= account
APP_HDR= $(IMPL_SRC).h
MAIN_SRC= main
INIT_SRC= init_db
MAIN_OBJS= $(IMPL_SRC).obj $(MAIN_SRC).obj
INIT_OBJS= $(IMPL_SRC).obj $(INIT_SRC).obj

SCHEMA_SRC= schema_src.cpp 
SCHEMA_NAME= schema
SCHEMA_OBJ= $(SCHEMA_NAME).obj
ASDB= $(SCHEMA_NAME).adb

ALL_OBJS= $(MAIN_OBJS) $(INIT_OBJS) $(SCHEMA_OBJ)
EXECUTABLES= $(MAIN_APP).exe $(INIT_SRC).exe

!ifdef DEBUG
CPPFLAGS= /nologo /EHa /W3 /MDd /DWIN32 /Zi -I$(OS_ROOTDIR)\include
!else
CPPFLAGS= /nologo /EHa /W3 /MD /DWIN32 -I$(OS_ROOTDIR)\include
!endif

!ifdef DEBUG
LDLIBS= $(OS_ROOTDIR)\lib\oscmtld.lib $(OS_ROOTDIR)\lib\ostored.lib
!else
LDLIBS= $(OS_ROOTDIR)\lib\oscmtl.lib $(OS_ROOTDIR)\lib\ostore.lib 
!endif

all: $(EXECUTABLES)

$(MAIN_APP).exe: $(MAIN_OBJS) $(SCHEMA_OBJ)
	cl /nologo /Fe$@ $(MAIN_OBJS) $(SCHEMA_OBJ) $(LDLIBS)

$(MAIN_SRC).obj: $(MAIN_SRC).cpp $(APP_HDR)

$(INIT_SRC).exe: $(INIT_OBJS) $(SCHEMA_OBJ)
	cl /nologo /Fe$@ $(INIT_OBJS) $(SCHEMA_OBJ) $(LDLIBS)

$(INIT_SRC).obj: $(INIT_SRC).cpp $(APP_HDR)

$(IMPL_SRC).obj: $(IMPL_SRC).cpp $(APP_HDR)

$(SCHEMA_OBJ): $(SCHEMA_SRC) $(APP_HDR)
	ossg -asof $(SCHEMA_OBJ) -asdb $(ASDB) $(CPPFLAGS) $(SCHEMA_SRC) 2> nul

debug:
	$(MAKE) DEBUG=1

.cpp.obj:
	cl $(CPPFLAGS) /c /Fo$@ $<

clean:
	-osrm *.db 2>nul
	-osrm $(ASDB) 2>nul
	-del/q $(EXECUTABLES) $(ALL_OBJS) 2>nul
	-del *.pdb
	-del *.log
        -del input
	-del tplog.odi

