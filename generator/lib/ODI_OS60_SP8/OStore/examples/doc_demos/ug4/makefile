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

#
# Schema flags
#

SCHEMA_SRC= schema.cpp
APP_SCHEMA_SRC= osschema.cpp
APP_SCHEMA_OBJ= osschema.obj

SET_APP= set_part
GET_APP= get_part
PART_APP= part
PART_HDR= $(PART_APP).hh
APP_SCHEMA_DB= $(OS_SCHEMA_DB_DIR)osschema.adb

#
# Other flags and macros
#

OBJECTS= $(SET_APP).obj $(PART_APP).obj $(GET_APP).obj $(APP_SCHEMA_OBJ)
EXECUTABLES= $(SET_APP).exe $(GET_APP).exe

#
# Rules
#

all:  $(EXECUTABLES)

$(SET_APP).exe: $(SET_APP).obj $(PART_APP).obj $(APP_SCHEMA_OBJ) $(PART_HDR)
	$(CCC) $(TFLAGS) /Fe$(SET_APP).exe $(SET_APP).obj $(PART_APP).obj $(APP_SCHEMA_OBJ)  $(LDLIBS)

$(GET_APP).exe: $(GET_APP).obj $(PART_APP).obj $(APP_SCHEMA_OBJ) $(PART_HDR)
	$(CCC) $(TFLAGS) /Fe$(GET_APP).exe $(GET_APP).obj $(PART_APP).obj $(APP_SCHEMA_OBJ)  $(LDLIBS)

debug:
	$(MAKE) "DEBUG_LIB_D=d" all

#
# Schema rules
# Generate $(APP_SCHEMA_SRC) and $(APP_SCHEMA_DB) from
# $(SCHEMA_SRC) and $(LIB_SCHEMA_DBS)
#

$(APP_SCHEMA_OBJ): $(SCHEMA_SRC) $(APP_SCHEMA_HDRS)
	ossg -asof $(APP_SCHEMA_OBJ) -asdb $(APP_SCHEMA_DB) $(CPPFLAGS) $(SCHEMA_SRC) $(LIB_SCHEMA_DBS)

clean:
	-del parts
	-osrm $(APP_SCHEMA_DB)
	-del $(SET_APP).exe
    -del $(GET_APP).exe
	-del $(SET_APP).obj
	-del $(PART_APP).obj
	-del $(GET_APP).obj
	-del $(APP_SCHEMA_SRC)
	-del $(APP_SCHEMA_OBJ)

