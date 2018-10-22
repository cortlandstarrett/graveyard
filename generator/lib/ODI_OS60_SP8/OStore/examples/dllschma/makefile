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
# Link flags and libraries
#
FLIGHTS_SHARED_NAME= flight_cs
FLIGHTS_SHARED_NAME2= flight_cs2
FLIGHTS_SHARED_DLL= $(FLIGHTS_SHARED_NAME)$(SHARED_LIB_SUFFIX)
FLIGHTS_SHARED_DLL2= $(FLIGHTS_SHARED_NAME2)$(SHARED_LIB_SUFFIX)

FLIGHTS_SHARED_LIB= $(FLIGHTS_SHARED_NAME).lib
FLIGHTS_SHARED_LIB2= $(FLIGHTS_SHARED_NAME2).lib

LIB_SCHEMA_DBS=

#
# Application Schema flags
#
SCHEMA_SRC= schema.cpp
SCHEMA_MSRC= osschema.cc
SCHEMA_OBJ= osschema.obj
SCHEMA_HDRS= string.hh  flight.hh  plane.hh  person.hh
SCHEMA_DB= $(OS_SCHEMA_DB_DIR)schma.adb

#
# Shared library component schema flags.
#
COMP_SCHEMA_SRC= comp_schema.cpp
COMP_SCHEMA_MSRC= oscomp_schema.cc
COMP_SCHEMA_OBJ= oscomp_schema.obj
COMP_SCHEMA_HDRS= string.hh  flight.hh  plane.hh  person.hh
COMP_SCHEMA_DB= $(OS_SCHEMA_DB_DIR)comp_schma.adb

COMP_SCHEMA2_SRC= comp_schema2.cpp
COMP_SCHEMA2_MSRC= oscomp_schema2.cc
COMP_SCHEMA2_OBJ= oscomp_schema2.obj
COMP_SCHEMA2_HDRS= string.hh  flight.hh  plane.hh  person.hh
COMP_SCHEMA2_DB= $(OS_SCHEMA_DB_DIR)comp_schma2.adb

#
# Other flags and macros
#

MAIN_OBJECT= main.obj main2.obj main3.obj main4.obj
SHARED_OBJECTS= fmenu.obj flight.obj plane.obj string.obj person.obj force_vfts.obj
OBJECTS= $(MAIN_OBJECT) $(SHARED_OBJECTS)
EXECUTABLES= flights.exe flights2.exe flights3.exe flights4.exe
EXAMPLE_DB=

#
# Rules
#

.SUFFIXES: .cpp

.cpp.o:
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c $<

all: $(FLIGHTS_SHARED_DLL) $(FLIGHTS_SHARED_DLL2) $(EXECUTABLES)

main.obj: main.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) -DCS_STATIC_LINK $(CC_OUT_OPTION)main.obj -c main.cpp

main2.obj: main.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) -DCS_STATIC_LINK $(CC_OUT_OPTION)main2.obj -c main.cpp

main3.obj: main.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) -DCS_DYNAMIC_LOAD $(CC_OUT_OPTION)main3.obj -c main.cpp

main4.obj: main.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) -DCS_MANUAL_LOAD $(CC_OUT_OPTION)main4.obj -c main.cpp

flights.exe : main.obj $(SHARED_OBJECTS) $(SCHEMA_OBJ)
	$(CCC) $(TFLAGS) /Feflights.exe main.obj $(SHARED_OBJECTS) $(SCHEMA_OBJ)  $(LDLIBS)

flights2.exe : main2.obj $(FLIGHTS_SHARED_LIB)
	$(CCC) $(TFLAGS) /Feflights2.exe main2.obj  $(FLIGHTS_SHARED_LIB) $(LDLIBS)

flights3.exe : main3.obj
	$(CCC) $(TFLAGS) /Feflights3.exe main3.obj  $(LDLIBS)

flights4.exe : main4.obj
	$(CCC) $(TFLAGS) /Feflights4.exe main4.obj  $(LDLIBS)

#
# Shared library contains the component schema.
# 

$(FLIGHTS_SHARED_DLL): $(SHARED_OBJECTS) $(COMP_SCHEMA_OBJ) $(OSTORE_LIBS)
	$(DLL_LINK) $**

$(FLIGHTS_SHARED_DLL2): $(SHARED_OBJECTS) $(COMP_SCHEMA2_OBJ) $(OSTORE_LIBS)
	$(DLL_LINK) /def:$(FLIGHTS_SHARED_NAME2).def $**

#
# Application Schema rules
# Generate $(SCHEMA_MSRC) and $(SCHEMA_DB) from
# $(SCHEMA_SRC) and $(LIB_SCHEMA_DBS)
#

$(SCHEMA_OBJ): $(SCHEMA_SRC) $(SCHEMA_HDRS)
	ossg -asof $(SCHEMA_OBJ) -asdb $(SCHEMA_DB) \
		$(OSSCHEMA_FLAGS) $(CPPFLAGS) $(SCHEMA_SRC) \
	$(LIB_SCHEMA_DBS)

#
# Component (Shared Library) Schema rules
# Generate $(COMP_SCHEMA_MSRC) and $(COMP_SCHEMA_DB) from
# $(COMP_SCHEMA_SRC) and $(LIB_COMP_SCHEMA_DBS)
#

$(COMP_SCHEMA_OBJ): $(COMP_SCHEMA_SRC) $(COMP_SCHEMA_HDRS)
	ossg -asof $(COMP_SCHEMA_OBJ) -asdb $(COMP_SCHEMA_DB) \
		$(OSSCHEMA_FLAGS) $(CPPFLAGS) $(COMP_SCHEMA_SRC) \
	$(LIB_SCHEMA_DBS)

$(COMP_SCHEMA2_OBJ): $(COMP_SCHEMA2_SRC) $(COMP_SCHEMA2_HDRS)
	ossg -asof $(COMP_SCHEMA2_OBJ) -asdb $(COMP_SCHEMA2_DB) \
		$(OSSCHEMA_FLAGS) $(CPPFLAGS) $(COMP_SCHEMA2_SRC) \
	$(LIB_SCHEMA_DBS)

debug:
	$(MAKE) "DEBUG_LIB_D=d" all

clean:
	-osrm $(SCHEMA_DB) $(COMP_SCHEMA_DB) $(COMP_SCHEMA2_DB)
	-del flights.exe
	-del flights2.exe
	-del flights3.exe
	-del flights4.exe
	-del main.obj
	-del main2.obj
	-del main3.obj
	-del main4.obj
	-del fmenu.obj
	-del flight.obj
	-del plane.obj
	-del string.obj
	-del person.obj
	-del force_vfts.obj
        -del $(FLIGHTS_SHARED_DLL)
        -del $(FLIGHTS_SHARED_DLL2)
	-del $(COMP_SCHEMA_OBJ)
	-del $(COMP_SCHEMA2_OBJ)
	-del $(SCHEMA_DB)
	-del $(SCHEMA_OBJ)
        -osrm $(COMP_SCHEMA_DB)
        -osrm $(COMP_SCHEMA2_DB)

	-del $(FLIGHTS_SHARED_LIB)
	-del $(FLIGHTS_SHARED_LIB2)
	-del flight*.exp
	-del flight*.lib	
	-del flight*.pdb

