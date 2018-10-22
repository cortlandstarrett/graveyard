# 		quick_start/iostreams example
# makefile for microsoft C++ command-line compiler (cl)

MAIN_APP = reserve
IMPL_SRC = restaurant
APP_HDR= $(IMPL_SRC).hh dbname.h
MAIN_SRC= main
INIT_SRC= init_db
MAIN_OBJS= $(IMPL_SRC).obj $(MAIN_SRC).obj
INIT_OBJS= $(IMPL_SRC).obj $(INIT_SRC).obj

ALL_OBJS= $(MAIN_OBJS) $(INIT_OBJS)
EXECUTABLES= $(MAIN_APP).exe $(INIT_SRC).exe

!ifdef DEBUG
CPPFLAGS= /nologo /W3 /Zi
!else
CPPFLAGS= /nologo /W3
!endif

all: $(EXECUTABLES)

$(MAIN_APP).exe: $(MAIN_OBJS)
	cl /nologo /Fe$@ $(MAIN_OBJS) $(LDLIBS)

$(INIT_SRC).exe: $(INIT_OBJS)
	cl /nologo /Fe$@ $(INIT_OBJS) $(LDLIBS)

$(MAIN_SRC).obj: $(MAIN_SRC).cpp $(APP_HDR)

$(INIT_SRC).obj: $(INIT_SRC).cpp $(APP_HDR)

$(IMPL_SRC).obj: $(IMPL_SRC).cpp $(APP_HDR)

dbname.h: makefile
	echo static char *DB_NAME = "restaurants.db"; > dbname.h


debug:
	$(MAKE) DEBUG=1

.cpp.obj:
	cl $(CPPFLAGS) /c /Fo$@ $<

clean:
	-del *.db 
   -del dbname.h 
   -del main.obj 
   -del restaurant.obj 
   -del init_db.obj 
   -del init_db.exe
   -del reserve.exe
	-del *.pdb
