#==========================================================================
#
# File:      $RCSfile: makefile,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:42:02 $
#
# (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
#Cygwin g++ makefile
GALAXY_INC = c:/lib/GalaxyGC30/INCLUDE
GENERATOR_INC = c:/workspace/model_compilers/generator/gen_erate/bp_build/win32/7.1B/build
BP6GENERATOR_INC = c:/workspace/model_compilers/generator/bp6_generator/bp_build/win32/7.1B/build
MCDBMS_INC = c:/workspace/model_compilers/generator/mc_dbms/include
CFLAGS = -c -GX -Iinclude -MD -DNOMINMAX -D_CONSOLE -DWIN32  -I ${GALAXY_INC} -I ${MCDBMS_INC} -I ${GENERATOR_INC} 
BP6CFLAGS = -c -GX -Iinclude -MD -DNOMINMAX -D_CONSOLE -DWIN32 -DBP6 -I ${GALAXY_INC} -I ${MCDBMS_INC} -I ${BP6GENERATOR_INC} 
SRC = .
DBGFLAG = -D_DEBUG -ZI
LFLAGS = /DEBUG
OBJ =	dbdump.obj

all: dbdump.exe

# a small test executable
dbdump.exe: dbdump.lib dbdump_main.obj
	link.exe ${LFLAGS} msvcrtd.lib msvcprtd.lib /OUT:dbdump.exe $^

# Compile test source file (main())
dbdump_main.obj: dbdump_main.cpp 
	cl.exe ${DBGFLAG} ${CFLAGS} $<

# Build a library that replaces objectstore
dbdump.lib: 	${OBJ}
	lib.exe ${DBGLIBFLAG} /OUT:dbdump.lib $< 
	cp dbdump.lib ../../lib/dbdump.lib

bp6_dbdump.lib: ${SRC}/dbdump.cpp	
	cl.exe ${DBGFLAG} ${BP6CFLAGS} $< 
	lib.exe ${DBGLIBFLAG} /OUT:bp6_dbdump.lib ${OBJ} 
	cp bp6_dbdump.lib ../../lib/bp6_dbdump.lib

dbdump.obj: ${SRC}/dbdump.cpp
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

clean:
	rm -f *.lib
	rm -f *.obj

