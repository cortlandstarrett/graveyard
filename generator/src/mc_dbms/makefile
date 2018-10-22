#==========================================================================
#
# File:      $RCSfile: makefile,v $
# Version:   $Revision: 1.14 $
# Modified:  $Date: 2013/01/10 23:43:00 $
#
# (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
CFLAGS = -c -GX -Iinclude -MD -DNOMINMAX -D_CONSOLE -DWIN32
LIBD = lib
INC = include/mc_dbms
SRC = src
DEBUG_BUILD ?= 0

ifeq (0, $(DEBUG_BUILD))
  DBGFLAG =  -MD -O2 
  LFLAGS = 
  LIBS = msvcrt.lib msvcprt.lib
else
  DBGFLAG =  -MDd -D_DEBUG -Zi -Od -GZ
  LFLAGS = /DEBUG
  LIBS = msvcrtd.lib msvcprtd.lib
endif

OBJ =	collection.obj \
		database.obj \
		database_root.obj \
		list.obj \
		bag.obj \
		typespec.obj \
		segment.obj \
		cursor.obj \
		set.obj \
		InstanceTracker.obj \
		persistence.obj \
		SerializableObject.obj \
		SerializablePointer.obj

all: test_dbms.exe

debug:
	DBGFLAG = -D_DEBUG -ZI
	LIBS = msvcrtd.lib msvcprtd.lib

# a small test executable
test_dbms.exe: test_dbms.obj mc_dbms.lib
	link.exe ${LFLAGS} ${LIBS} /OUT:test_dbms.exe $^

# Compile test source file (main())
test_dbms.obj: test_dbms.cpp 
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

# Build a library that replaces objectstore
mc_dbms.lib: 	${OBJ}
	lib.exe ${DBGLIBFLAG} /OUT:mc_dbms.lib ${OBJ}
	
collection.obj: ${SRC}/collection.cpp ${INC}/collection.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

database.obj: ${SRC}/database.cpp ${INC}/database.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

database_root.obj: ${SRC}/database_root.cpp ${INC}/database_root.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

bag.obj: ${SRC}/bag.cpp ${INC}/bag.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

typespec.obj: ${SRC}/typespec.cpp ${INC}/typespec.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

segment.obj: ${SRC}/segment.cpp ${INC}/segment.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

cursor.obj: ${SRC}/cursor.cpp ${INC}/cursor.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

set.obj: ${SRC}/set.cpp ${INC}/set.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

list.obj: ${SRC}/list.cpp ${INC}/list.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

InstanceTracker.obj: ${SRC}/InstanceTracker.cpp ${INC}/InstanceTracker.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

persistence.obj: ${SRC}/persistence.cpp ${INC}/persistence.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

SerializableObject.obj: ${SRC}/SerializableObject.cpp ${INC}/SerializableObject.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

SerializablePointer.obj: ${SRC}/SerializablePointer.cpp ${INC}/SerializablePointer.h ${INC}/mc_dbms_types.h
	cl.exe ${DBGFLAG} ${CFLAGS} $< 

clean:
	rm -f *.obj
	rm -f vc60.*

