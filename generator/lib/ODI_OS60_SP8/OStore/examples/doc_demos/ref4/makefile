# ObjectStore Documentation Example Makefile

#
# Compiler, token flags and schema flags
#

# Using Microsoft Visual C++ compiler

CCC=cl
TFLAGS=

COMPILE_RUNTIME=/MD$(DEBUG_LIB_D)
CPP_FLAGS= /nologo /EHa $(COMPILE_RUNTIME) /DWIN32
OSTORE_LIBS=$(OS_ROOTDIR)\lib\ostore$(DEBUG_LIB_D).lib
RUNTIME_LIBS=msvcrt$(DEBUG_LIB_D).lib msvcprt$(DEBUG_LIB_D).lib msvcirt$(DEBUG_LIB_D).lib

DEBUG_OPTS=/Zi /Od
OS_LINK_FLAGS=/link /debug:both
SHARED_LIB_SUFFIX= .dll

CC_OUT_OPTION=/Fo
FORCE_CPP= /Tp

CPU=I386

LINKER=link
LINKER_OPTS=-machine:$(CPU)
LINKER_O_OPTION=/OUT:$@
CL_LINK_OPTIONS=/nod /subsystem:console
DLL_LINK_OPTIONS=/nologo /subsystem:windows  /dll /incremental:no /pdb:$*.pdb /debug /machine:$(CPU) /nodefaultlib
OTHER_LIBS=kernel32.lib user32.lib advapi32.lib $(RUNTIME_LIBS)
DLL_LIBS=$(RUNTIME_LIBS) kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
CL_LINK=$(LINKER) $(LINKER_OPTS) $(CL_LINK_OPTIONS) $(LINKER_O_OPTION) $** $(OTHER_LIBS)
DLL_LINK=$(LINKER) $(OSTORE_LIBS) $(DLL_LIBS) $(DLL_LINK_OPTIONS) $(LINKER_O_OPTION) /implib:$*.lib /pdbtype:sept

# If you want your schema databases or example databases placed in
# directories other than the current directory, or in a rawfs directory,
# you should either:
#     - uncomment the last two lines of this comment and set
#       OS_SCHEMA_DB_DIR to the schema database directory path and
#       set OS_EXAMPLE_DB_DIR to the database directory path you want
# or
#     - set your environment variables OS_SCHEMA_DB_DIR and
#       OS_EXAMPLE_DB_DIR to the paths you want
#
# ** NOTE that both OS_SCHEMA_DB_DIR and OS_EXAMPLE_DB_DIR must end
# ** with a forward slash - '/'.  This means a value of './' is
# ** equivalent to the current directory.
#
# To set these, uncomment the next two lines.
# OS_SCHEMA_DB_DIR=./
# OS_EXAMPLE_DB_DIR=./

#
# C++ flags must include ObjectStore include directory
#

CPPFLAGS= $(CPP_FLAGS) -I$(OS_ROOTDIR)\include

#
# Link flags and libraries
#

LDFLAGS=	$(OS_LINK_FLAGS) -L$(OS_ROOTDIR)\lib

LDLIBS=$(OSTORE_LIBS)

TIX_APP= tix_example
DEF_APP= def_exc
TXN_APP= txn_example

#
# Other flags and macros
#

OBJECTS= $(TIX_APP).obj $(TXN_APP).obj $(DEF_APP).obj
EXECUTABLES= $(TIX_APP).exe $(TXN_APP).exe $(DEF_APP).exe

#
# Rules
#

all:  $(EXECUTABLES)

$(TIX_APP).exe: $(TIX_APP).obj
	$(CCC) $(CPPFLAGS) /Fe$(TIX_APP).exe $(TIX_APP).obj  $(LDLIBS)

$(TXN_APP).exe: $(TXN_APP).obj
	$(CCC) $(CPPFLAGS) /Fe$(TXN_APP).exe $(TXN_APP).obj  $(LDLIBS)

$(DEF_APP).exe: $(DEF_APP).obj
	$(CCC) $(CPPFLAGS) /Fe$(DEF_APP).exe $(DEF_APP).obj  $(LDLIBS)

debug:
	$(MAKE) "DEBUG_LIB_D=d" all

clean:
	-osrm nonsense.db
	-osrm stanza.db
	-del $(TIX_APP).exe
	-del $(TXN_APP).exe
	-del $(DEF_APP).exe
	-del $(TIX_APP).obj
	-del $(TXN_APP).obj
	-del $(DEF_APP).obj

