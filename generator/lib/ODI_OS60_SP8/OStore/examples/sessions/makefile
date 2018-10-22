# ObjectStore Sessions Example Makefile

#
# Compiler, token flags and schema flags
#

# Using Microsoft Visual C++ compiler

CCC=cl
TFLAGS= /Zi /Od
COMPILE_RUNTIME=/MD$(DEBUG_LIB_D)
CPP_FLAGS= /nologo /EHa $(COMPILE_RUNTIME) /DWIN32
DEBUG_OPTS=/Zi /Od
OSTORE_LIBS=$(OS_ROOTDIR)/lib/ostore$(DEBUG_LIB_D).lib

#
# C++ flags must include ObjectStore include directory
#

CPPFLAGS= $(CPP_FLAGS) -I$(OS_ROOTDIR)\include


#
# Schema flags
#

SCHEMA_SRC= schema.cpp
APP_SCHEMA_SRC= osschema.cpp
APP_SCHEMA_OBJ= osschema.obj

APP_SCHEMA_HDRS= part.hh employee.hh
APP_SCHEMA_DB= $(OS_SCHEMA_DB_DIR)sessions.adb

#
# Other flags and macros
#

OBJECTS= app_server.obj osint.obj queue.obj
EXECUTABLES= app_server.exe 

#
# Rules
#

all: app_server.exe

debug:
	$(MAKE) "DEBUG_LIB_D=d" all

app_server.exe: $(OBJECTS)
	$(CCC) $(TFLAGS) /Feapp_server.exe $(OBJECTS) $(OSTORE_LIBS)

app_server.obj: app_server.cpp app_server.hh
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c app_server.cpp

osint.obj: osint.cpp osint.hh
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c osint.cpp

queue.obj: queue.cpp queue.hh
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c queue.cpp

clean:
	-osrm $(EXAMPLE_DB) 
	-del $(EXECUTABLES) 
	-del app_server.obj 
	-del osint.obj 
	-del queue.obj 
	-del dbname.h 
	-del *.opt 
	-del *.pdb 
	-del *.ilk 





