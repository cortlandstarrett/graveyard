# ObjectStore Schema Evolution Example Makefile

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

SCHEMA_SRC_Apre= schm1pre.cpp
APP_SCHEMA_SRC_Apre= sch1apre.cpp
APP_SCHEMA_OBJ_Apre= sch1apre.obj
APP_SCHEMA_HDRS_Apre= part1pre.hh
APP_SCHEMA_DB_Apre= $(OS_SCHEMA_DB_DIR)sch1apre.adb

SCHEMA_SRC_Anew= schm1new.cpp
APP_SCHEMA_SRC_Anew= sch1anew.cpp
APP_SCHEMA_OBJ_Anew= sch1anew.obj
APP_SCHEMA_HDRS_Anew= part1new.hh
APP_SCHEMA_DB_Anew= $(OS_SCHEMA_DB_DIR)sch1anew.adb

SCHEMA_SRC_Bpre= schm2pre.cpp
APP_SCHEMA_SRC_Bpre= sch2apre.cpp
APP_SCHEMA_OBJ_Bpre= sch2apre.obj
APP_SCHEMA_HDRS_Bpre= part2pre.hh
APP_SCHEMA_DB_Bpre= $(OS_SCHEMA_DB_DIR)sch2apre.adb

SCHEMA_SRC_Bnew= schm2new.cpp
APP_SCHEMA_SRC_Bnew= sch2anew.cpp
APP_SCHEMA_OBJ_Bnew= sch2anew.obj
APP_SCHEMA_HDRS_Bnew= part2new.hh
APP_SCHEMA_DB_Bnew= $(OS_SCHEMA_DB_DIR)sch2anew.adb

SCHEMA_SRC_Cpre= schm3pre.cpp
APP_SCHEMA_SRC_Cpre= sch3apre.cpp
APP_SCHEMA_OBJ_Cpre= sch3apre.obj
APP_SCHEMA_HDRS_Cpre= part3pre.hh
APP_SCHEMA_DB_Cpre= $(OS_SCHEMA_DB_DIR)sch3apre.adb

SCHEMA_SRC_Cnew= schm3new.cpp
APP_SCHEMA_SRC_Cnew= sch3anew.cpp
APP_SCHEMA_OBJ_Cnew= sch3anew.obj
APP_SCHEMA_HDRS_Cnew= part3new.hh
APP_SCHEMA_DB_Cnew= $(OS_SCHEMA_DB_DIR)sch3anew.adb

SCHEMA_SRC_Dpre= schm4pre.cpp
APP_SCHEMA_SRC_Dpre= sch4apre.cpp
APP_SCHEMA_OBJ_Dpre= sch4apre.obj
APP_SCHEMA_HDRS_Dpre= part4pre.hh
APP_SCHEMA_DB_Dpre= $(OS_SCHEMA_DB_DIR)sch4apre.adb

SCHEMA_SRC_Dnew= schm4new.cpp
APP_SCHEMA_SRC_Dnew= sch4anew.cpp
APP_SCHEMA_OBJ_Dnew= sch4anew.obj
APP_SCHEMA_HDRS_Dnew= part4new.hh
APP_SCHEMA_DB_Dnew= $(OS_SCHEMA_DB_DIR)sch4anew.adb

SCHEMA_SRC_Epre= schm5pre.cpp
APP_SCHEMA_SRC_Epre= sch5apre.cpp
APP_SCHEMA_OBJ_Epre= sch5apre.obj
APP_SCHEMA_HDRS_Epre= part5pre.hh
APP_SCHEMA_DB_Epre= $(OS_SCHEMA_DB_DIR)sch5apre.adb

SCHEMA_SRC_Enew= schm5new.cpp
APP_SCHEMA_SRC_Enew= sch5anew.cpp
APP_SCHEMA_OBJ_Enew= sch5anew.obj
APP_SCHEMA_HDRS_Enew= part5new.hh
APP_SCHEMA_DB_Enew= $(OS_SCHEMA_DB_DIR)sch5anew.adb

LIB_SCHEMA_DBS=

#
# Other flags and macros
#

EXECUTABLES=db_pop1.exe db_read1.exe evolve2.exe db_pop2.exe db_read2.exe evolve3.exe db_pop3.exe db_read3.exe evolve4.exe db_pop4.exe db_read4.exe evolve5.exe db_pop5.exe db_read5.exe
OBJECTS=db_pop1.obj db_read1.obj evolve2.obj db_pop2.obj db_read2.obj evolve3.obj db_pop3.obj db_read3.obj evolve4.obj db_pop4.obj db_read4.obj part4pre.obj part4new.obj evolve5.obj db_pop5.obj db_read5.obj
EXAMPLE_DB1= $(OS_EXAMPLE_DB_DIR)db1.db
EXAMPLE_DB2= $(OS_EXAMPLE_DB_DIR)db2.db
EXAMPLE_WDB2= $(OS_EXAMPLE_DB_DIR)wdb2.db
EXAMPLE_DB3= $(OS_EXAMPLE_DB_DIR)db3.db
EXAMPLE_WDB3= $(OS_EXAMPLE_DB_DIR)wdb3.db
EXAMPLE_DB4= $(OS_EXAMPLE_DB_DIR)db4.db
EXAMPLE_WDB4= $(OS_EXAMPLE_DB_DIR)wdb4.db
EXAMPLE_DB5= $(OS_EXAMPLE_DB_DIR)db5.db
EXAMPLE_WDB5= $(OS_EXAMPLE_DB_DIR)wdb5.db

#
# Rules
#

all: db_pop1.exe db_read1.exe evolve2.exe db_pop2.exe db_read2.exe evolve3.exe db_pop3.exe db_read3.exe evolve4.exe db_pop4.exe db_read4.exe evolve5.exe db_pop5.exe db_read5.exe

dbname1.h: makefile
	echo static char *example_db1_name= "$(EXAMPLE_DB1)"; > dbname1.h

dbname2.h: makefile
	echo static char *example_db2_name= "$(EXAMPLE_DB2)"; > dbname2.h
	echo static char *example_wdb2_name= "$(EXAMPLE_WDB2)"; >> dbname2.h

dbname3.h: makefile
	echo static char *example_db3_name= "$(EXAMPLE_DB3)"; > dbname3.h
	echo static char *example_wdb3_name= "$(EXAMPLE_WDB3)"; >> dbname3.h

dbname4.h: makefile
	echo static char *example_db4_name= "$(EXAMPLE_DB4)"; > dbname4.h
	echo static char *example_wdb4_name= "$(EXAMPLE_WDB4)"; >> dbname4.h

dbname5.h: makefile
	echo static char *example_db5_name= "$(EXAMPLE_DB5)"; > dbname5.h
	echo static char *example_wdb5_name= "$(EXAMPLE_WDB5)"; >> dbname5.h

db_pop1.exe: db_pop1.obj $(APP_SCHEMA_OBJ_Apre)
	$(CCC) $(TFLAGS) /Fedb_pop1.exe db_pop1.obj $(APP_SCHEMA_OBJ_Apre)  $(LDLIBS)

db_pop1.obj: dbname1.h db_pop1.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_pop1.cpp

db_read1.exe: db_read1.obj $(APP_SCHEMA_OBJ_Anew)
	$(CCC) $(TFLAGS) /Fedb_read1.exe db_read1.obj $(APP_SCHEMA_OBJ_Anew)  $(LDLIBS)

db_read1.obj: dbname1.h db_read1.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_read1.cpp

db_pop2.exe: db_pop2.obj $(APP_SCHEMA_OBJ_Bpre)
	$(CCC) $(TFLAGS) /Fedb_pop2.exe db_pop2.obj $(APP_SCHEMA_OBJ_Bpre)  $(LDLIBS)

db_pop2.obj: dbname2.h db_pop2.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_pop2.cpp

db_read2.exe: db_read2.obj $(APP_SCHEMA_OBJ_Bnew)
	$(CCC) $(TFLAGS) /Fedb_read2.exe db_read2.obj $(APP_SCHEMA_OBJ_Bnew)  $(LDLIBS)

db_read2.obj: dbname2.h db_read2.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_read2.cpp

evolve2.exe: evolve2.obj $(APP_SCHEMA_OBJ_Bnew)
	$(CCC) $(TFLAGS) /Feevolve2.exe evolve2.obj $(APP_SCHEMA_OBJ_Bnew)  $(LDLIBS)

evolve2.obj: dbname2.h evolve2.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c evolve2.cpp

db_pop3.exe: db_pop3.obj $(APP_SCHEMA_OBJ_Cpre)
	$(CCC) $(TFLAGS) /Fedb_pop3.exe db_pop3.obj $(APP_SCHEMA_OBJ_Cpre)  $(LDLIBS)

db_pop3.obj: dbname3.h db_pop3.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_pop3.cpp

db_read3.exe: db_read3.obj $(APP_SCHEMA_OBJ_Cnew)
	$(CCC) $(TFLAGS) /Fedb_read3.exe db_read3.obj $(APP_SCHEMA_OBJ_Cnew)  $(LDLIBS)

db_read3.obj: dbname3.h db_read3.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_read3.cpp

evolve3.exe: evolve3.obj $(APP_SCHEMA_OBJ_Cnew)
	$(CCC) $(TFLAGS) /Feevolve3.exe evolve3.obj $(APP_SCHEMA_OBJ_Cnew)  $(LDLIBS)

evolve3.obj: dbname3.h evolve3.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c evolve3.cpp

part4pre.obj: dbname4.h part4pre.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c part4pre.cpp

part4new.obj: dbname4.h part4new.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c part4new.cpp

db_pop4.exe: db_pop4.obj part4pre.obj $(APP_SCHEMA_OBJ_Dpre)
	$(CCC) $(TFLAGS) /Fedb_pop4.exe db_pop4.obj part4pre.obj $(APP_SCHEMA_OBJ_Dpre)  $(LDLIBS)

db_pop4.obj: dbname4.h db_pop4.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_pop4.cpp

db_read4.exe: db_read4.obj part4new.obj $(APP_SCHEMA_OBJ_Dnew)
	$(CCC) $(TFLAGS) /Fedb_read4.exe db_read4.obj part4new.obj $(APP_SCHEMA_OBJ_Dnew)  $(LDLIBS)

db_read4.obj: dbname4.h db_read4.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_read4.cpp

evolve4.exe: evolve4.obj part4new.obj $(APP_SCHEMA_OBJ_Dnew)
	$(CCC) $(TFLAGS) /Feevolve4.exe evolve4.obj part4new.obj $(APP_SCHEMA_OBJ_Dnew)  $(LDLIBS)

evolve4.obj: dbname4.h evolve4.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c evolve4.cpp

db_pop5.exe: db_pop5.obj $(APP_SCHEMA_OBJ_Epre)
	$(CCC) $(TFLAGS) /Fedb_pop5.exe db_pop5.obj $(APP_SCHEMA_OBJ_Epre)  $(LDLIBS)

db_pop5.obj: dbname5.h db_pop5.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_pop5.cpp

db_read5.exe: db_read5.obj $(APP_SCHEMA_OBJ_Enew)
	$(CCC) $(TFLAGS) /Fedb_read5.exe db_read5.obj $(APP_SCHEMA_OBJ_Enew)  $(LDLIBS)

db_read5.obj: dbname5.h db_read5.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c db_read5.cpp

evolve5.exe: evolve5.obj $(APP_SCHEMA_OBJ_Enew)
	$(CCC) $(TFLAGS) /Feevolve5.exe evolve5.obj $(APP_SCHEMA_OBJ_Enew)  $(LDLIBS)

evolve5.obj: dbname5.h evolve5.cpp
	$(CCC) $(CPPFLAGS) $(TFLAGS) /c evolve5.cpp

debug:
	$(MAKE) "DEBUG_LIB_D=d" all

#
# Schema rules
# Generate $(APP_SCHEMA_SRC) and $(APP_SCHEMA_DB) from
# $(SCHEMA_SRC) and $(LIB_SCHEMA_DBS)
#

$(APP_SCHEMA_OBJ_Apre): $(SCHEMA_SRC_Apre) $(APP_SCHEMA_HDRS_Apre)
        ossg -asof $(APP_SCHEMA_OBJ_Apre) -asdb $(APP_SCHEMA_DB_Apre) $(CPPFLAGS) $(SCHEMA_SRC_Apre) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Anew): $(SCHEMA_SRC_Anew) $(APP_SCHEMA_HDRS_Anew)
        ossg -asof $(APP_SCHEMA_OBJ_Anew) -asdb $(APP_SCHEMA_DB_Anew) $(CPPFLAGS) $(SCHEMA_SRC_Anew) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Bpre): $(SCHEMA_SRC_Bpre) $(APP_SCHEMA_HDRS_Bpre)
        ossg -asof $(APP_SCHEMA_OBJ_Bpre) -asdb $(APP_SCHEMA_DB_Bpre) $(CPPFLAGS) $(SCHEMA_SRC_Bpre) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Bnew): $(SCHEMA_SRC_Bnew) $(APP_SCHEMA_HDRS_Bnew)
        ossg -asof $(APP_SCHEMA_OBJ_Bnew) -asdb $(APP_SCHEMA_DB_Bnew) $(CPPFLAGS) $(SCHEMA_SRC_Bnew) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Cpre): $(SCHEMA_SRC_Cpre) $(APP_SCHEMA_HDRS_Cpre)
        ossg -asof $(APP_SCHEMA_OBJ_Cpre) -asdb $(APP_SCHEMA_DB_Cpre) $(CPPFLAGS) $(SCHEMA_SRC_Cpre) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Cnew): $(SCHEMA_SRC_Cnew) $(APP_SCHEMA_HDRS_Cnew)
        ossg -asof $(APP_SCHEMA_OBJ_Cnew) -asdb $(APP_SCHEMA_DB_Cnew) $(CPPFLAGS) $(SCHEMA_SRC_Cnew) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Dpre): $(SCHEMA_SRC_Dpre) $(APP_SCHEMA_HDRS_Dpre)
        ossg -asof $(APP_SCHEMA_OBJ_Dpre) -asdb $(APP_SCHEMA_DB_Dpre) $(CPPFLAGS) $(SCHEMA_SRC_Dpre) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Dnew): $(SCHEMA_SRC_Dnew) $(APP_SCHEMA_HDRS_Dnew)
        ossg -asof $(APP_SCHEMA_OBJ_Dnew) -asdb $(APP_SCHEMA_DB_Dnew) $(CPPFLAGS) $(SCHEMA_SRC_Dnew) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Epre): $(SCHEMA_SRC_Epre) $(APP_SCHEMA_HDRS_Epre)
        ossg -asof $(APP_SCHEMA_OBJ_Epre) -asdb $(APP_SCHEMA_DB_Epre) $(CPPFLAGS) $(SCHEMA_SRC_Epre) $(LIB_SCHEMA_DBS)

$(APP_SCHEMA_OBJ_Enew): $(SCHEMA_SRC_Enew) $(APP_SCHEMA_HDRS_Enew)
        ossg -asof $(APP_SCHEMA_OBJ_Enew) -asdb $(APP_SCHEMA_DB_Enew) $(CPPFLAGS) $(SCHEMA_SRC_Enew) $(LIB_SCHEMA_DBS)

clean:
	-osrm $(APP_SCHEMA_DB_Apre)
	-osrm $(APP_SCHEMA_DB_Anew)
	-osrm $(APP_SCHEMA_DB_Bpre)
	-osrm $(APP_SCHEMA_DB_Bnew)
	-osrm $(APP_SCHEMA_DB_Cpre)
	-osrm $(APP_SCHEMA_DB_Cnew)
	-osrm $(APP_SCHEMA_DB_Dpre)
	-osrm $(APP_SCHEMA_DB_Dnew)
	-osrm $(APP_SCHEMA_DB_Epre)
	-osrm $(APP_SCHEMA_DB_Enew)
	-osrm $(EXAMPLE_DB1)
	-osrm $(EXAMPLE_DB2)
	-osrm $(EXAMPLE_DB3)
	-osrm $(EXAMPLE_DB4)
	-osrm $(EXAMPLE_DB5)
	-osrm $(EXAMPLE_WDB2)
	-osrm $(EXAMPLE_WDB3)
	-osrm $(EXAMPLE_WDB4)
	-osrm $(EXAMPLE_WDB5)
	-del dbname1.h
	-del dbname2.h
	-del dbname3.h
	-del dbname4.h
	-del dbname5.h
	-del db_pop1.exe
	-del db_read1.exe
	-del evolve2.exe
	-del db_pop2.exe
	-del db_read2.exe
	-del evolve3.exe
	-del db_pop3.exe
	-del db_read3.exe
	-del evolve4.exe
	-del db_pop4.exe
	-del db_read4.exe
	-del evolve5.exe
	-del db_pop5.exe
	-del db_read5.exe
	-del db_pop1.obj
	-del db_read1.obj
	-del evolve2.obj
	-del db_pop2.obj
	-del db_read2.obj
	-del evolve3.obj
	-del db_pop3.obj
	-del db_read3.obj
	-del evolve4.obj
	-del db_pop4.obj
	-del db_read4.obj
	-del part4pre.obj
	-del part4new.obj
	-del evolve5.obj
	-del db_pop5.obj
	-del db_read5.obj
	-del $(APP_SCHEMA_SRC_Apre)
	-del $(APP_SCHEMA_OBJ_Apre)
	-del $(APP_SCHEMA_SRC_Anew)
	-del $(APP_SCHEMA_OBJ_Anew)
	-del $(APP_SCHEMA_SRC_Bpre)
	-del $(APP_SCHEMA_OBJ_Bpre)
	-del $(APP_SCHEMA_SRC_Bnew)
	-del $(APP_SCHEMA_OBJ_Bnew)
	-del $(APP_SCHEMA_SRC_Cpre)
	-del $(APP_SCHEMA_OBJ_Cpre)
	-del $(APP_SCHEMA_SRC_Cnew)
	-del $(APP_SCHEMA_OBJ_Cnew)
	-del $(APP_SCHEMA_SRC_Dpre)
	-del $(APP_SCHEMA_OBJ_Dpre)
	-del $(APP_SCHEMA_SRC_Dnew)
	-del $(APP_SCHEMA_OBJ_Dnew)
	-del $(APP_SCHEMA_SRC_Epre)
	-del $(APP_SCHEMA_OBJ_Epre)
	-del $(APP_SCHEMA_SRC_Enew)
	-del $(APP_SCHEMA_OBJ_Enew)

