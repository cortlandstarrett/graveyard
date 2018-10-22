# Visual C++ version 2.0 include for makefiles for ObjectStore 
#
# Environment variables used
# OS_ROOTDIR=Location of ObjectStore files
#
# Note that if you have $(OS_ROOTDIR)\include in your include
# environment variable, then the -I$(OS_ROOTDIR)\include arguments
# below can be removed.  And if $(OS_ROOTDIR)\lib is in your lib environment
# variable, then the '$(OS_ROOTDIR)\lib\' prefix to ostore.lib can be removed.

OSSG= $(OS_ROOTDIR)\bin\ossg.exe

.SUFFIXES: .cc .cpp .c .asm .def

OSTORE_INCPATH=$(OS_ROOTDIR)\include

# Compilation options for command line programs
CL_OBJECTS=
CL_LINK_OPTIONS= -debug -debugtype:cv -map:$*.map -subsystem:console

OSTORE_LIBS=  \
	$(OS_ROOTDIR)\lib\ostore.lib	\

!ifndef OS_LIBDIR
OS_LIBDIR=$(OS_ROOTDIR)\lib
!endif

COLL_LIBSCHEMA=$(OS_LIBDIR)\os_coll.ldb

LIBPATH=$(OS_LIBDIR);$(LIB)

COMPILER=cl
COPTS=
CCOPTS=/vmg /vmv /EHa /DWIN32
CPP_OPT=
DEBUG_OPTS=/Zi /Od
WARNING_OPTS=
BASE_COMPILER_OPTS=/I$(OSTORE_INCPATH) /c /MD $(WARNING_OPTS)
COMPILER_OPTS=$(BASE_COMPILER_OPTS) $(DEBUG_OPTS)
SCHEMA_COMPILER_OPTS=$(BASE_COMPILER_OPTS)
CC_C_OPTION=-Fo
FORCE_CPP= /Tp
FORCE_C= /Tc

ASSEMBLER=
ASSEMBLER_OPTS=

LINKER=link
LINKER_DEBUG_OPTS=/DEBUG

LINKER_OPTS=
LINKER_LIB_PREFIX=$(LIBPATH:;=\ )\\

LIBMAN=lib /nologo /noignorecase
LIBMAN_BIG=lib /nologo /noignorecase /pagesize:256

IMPLIB=implib

RC=rc -p -x

# Rules used only for debugging.

.c.asm:
	$(COMPILER) $(COMPILER_OPTS) /Fo- /Fa$@ $(COPTS) $(FORCE_C) $<

.cc.asm:
	$(COMPILER) $(COMPILER_OPTS) /Fo- /Fa$@ $(CCOPTS) $(FORCE_CPP) $<

.c.i:
	$(COMPILER) $(COMPILER_OPTS) /Pc- /Pd $(COPTS) $(FORCE_C) $< > $@

.cc.ii:
	$(COMPILER) $(COMPILER_OPTS) /Pc- /Pd $(CCOPTS) $(FORCE_CPP) $< > $@

COMPILER_OPTS=$(COMPILER_OPTS) $(EXTRA_COMPILER_OPTS)

LINK=$(LINKER) $(LINKER_OPTS)
SO_LINK=$(LINKER) $(LINKER_OPTS) $(CL_LINK_OPTIONS) 
CL_LINK=$(LINKER) $(LINKER_OPTS) $(CL_LINK_OPTIONS) $(CL_OBJECTS) $(CL_LIBS) 
GUI_LINK=$(LINKER) $(LINKER_OPTS) $(GUI_LINK_OPTIONS) $(GUI_OBJECTS) $(GUI_LIBS) 
DLL_LINK=$(LINKER) $(LINKER_OPTS) $(DLL_LINK_OPTIONS) $(DLL_OBJECTS) $(DLL_LIBS) 

.c.obj:
	$(COMPILER) $(COMPILER_OPTS) $(CC_C_OPTION)$@ $(COPTS) $(FORCE_C) $<

.cc.obj:
	$(COMPILER) $(COMPILER_OPTS) $(CC_C_OPTION)$@ $(CCOPTS) $(FORCE_CPP) $<

.cpp.obj:
	$(COMPILER) $(COMPILER_OPTS) $(CC_C_OPTION)$@ $(CCOPTS) $(FORCE_CPP) $<

.asm.obj:
	$(ASSEMBLER) $(ASSEMBLER_OPTS) $<,$@;

.c.sob:
	$(COMPILER) $(COPTS) $(SCHEMA_COMPILER_OPTS) $(CC_C_OPTION)$@ $(FORCE_C) $<

.cc.sob:
	$(COMPILER) $(CCOPTS) $(SCHEMA_COMPILER_OPTS) $(CC_C_OPTION)$@ $(FORCE_CPP) $<

.cpp.sob:
	$(COMPILER) $(CCOPTS) $(SCHEMA_COMPILER_OPTS) $(CC_C_OPTION)$@ $(FORCE_CPP) $<

.def.lib:
	$(IMPLIB) $@ $?

.$(DEF).def:
	copy $? $@

