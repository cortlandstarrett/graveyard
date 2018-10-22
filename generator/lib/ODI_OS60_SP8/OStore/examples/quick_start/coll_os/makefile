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

SCHEMA_SRC= schema_src.cpp
APP_SCHEMA_SRC= osschema.cpp
APP_SCHEMA_OBJ= osschema.obj

APP_SCHEMA_HDRS= restaurant.hh
APP_SCHEMA_DB= $(OS_SCHEMA_DB_DIR)schema.adb
LIB_SCHEMA_DBS=

#
# Other flags and macros
#

OBJECTS= main.obj restaurant.obj add_restaurant.obj init_db.obj schema.obj rlist.obj
EXECUTABLES= reserve.exe init_db.exe rlist.exe add_restaurant.exe
EXAMPLE_DB= $(OS_EXAMPLE_DB_DIR)restaurants.db

#
# Rules
#

all: reserve.exe init_db.exe rlist.exe add_restaurant.exe

dbname.h: makefile
	echo static char *DB_NAME= "$(EXAMPLE_DB)"; > dbname.h

reserve.exe: main.obj restaurant.obj $(APP_SCHEMA_OBJ)
	$(CCC) $(TFLAGS) /Fereserve.exe main.obj restaurant.obj $(APP_SCHEMA_OBJ)  $(LDLIBS)
main.obj: dbname.h main.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c main.cpp
restaurant.obj: dbname.h restaurant.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c restaurant.cpp
init_db.exe: init_db.obj restaurant.obj $(APP_SCHEMA_OBJ)
	$(CCC) $(TFLAGS) /Feinit_db.exe init_db.obj restaurant.obj $(APP_SCHEMA_OBJ)  $(LDLIBS)
init_db.obj: dbname.h init_db.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c init_db.cpp
rlist.exe: rlist.obj restaurant.obj $(APP_SCHEMA_OBJ)
	$(CCC) $(TFLAGS) /Ferlist.exe rlist.obj restaurant.obj $(APP_SCHEMA_OBJ)  $(LDLIBS)
rlist.obj: dbname.h rlist.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c rlist.cpp
add_restaurant.exe: add_restaurant.obj restaurant.obj $(APP_SCHEMA_OBJ)
	$(CCC) $(TFLAGS) /Feadd_restaurant.exe add_restaurant.obj restaurant.obj $(APP_SCHEMA_OBJ)  $(LDLIBS)
add_restaurant.obj: dbname.h add_restaurant.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c add_restaurant.cpp

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
	-osrm $(APP_SCHEMA_DB)
	-osrm $(EXAMPLE_DB)
   -del main.obj
   -del restaurant.obj
   -del add_restaurant.obj
   -del rlist.obj
   -del init_db.obj
   -del schema.obj
   -del reserve.exe
   -del init_db.exe
   -del rlist.exe
   -del add_restaurant.exe
	-del $(APP_SCHEMA_SRC)
	-del $(APP_SCHEMA_OBJ)
	-del dbname.h
	-del *.exp
	-del *.lib

