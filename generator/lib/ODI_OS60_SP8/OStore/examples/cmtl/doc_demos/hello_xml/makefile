# makefile for microsoft C++ command-line compiler (cl)

MAIN_APP= hello
IMPL_SRC= hello
APP_HDR= $(IMPL_SRC).h
MAIN_SRC= main
MAIN_OBJS= $(IMPL_SRC).obj $(MAIN_SRC).obj

ALL_OBJS= $(MAIN_OBJS) $(INIT_OBJS)
EXECUTABLES= $(MAIN_APP).exe

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

$(MAIN_APP).exe: $(MAIN_OBJS)
	cl /nologo /Fe$@ $(MAIN_OBJS) $(LDLIBS)

$(MAIN_SRC).obj: $(MAIN_SRC).cpp $(APP_HDR)

$(IMPL_SRC).obj: $(IMPL_SRC).cpp $(APP_HDR)

debug:
	$(MAKE) DEBUG=1

.cpp.obj:
	cl $(CPPFLAGS) /c /Fo$@ $<

clean:
	-osrm *.db 2>nul
	-del/q $(EXECUTABLES) $(ALL_OBJS) 2>nul
	-del *.pdb
	-del *.log
	-del tplog.odi


