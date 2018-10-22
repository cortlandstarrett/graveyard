#==========================================================================
#
# File:      $RCSfile: lib.mk,v $
# Version:   $Revision: 1.10 $
# Modified:  $Date: 2013/01/10 23:43:06 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
# include paths
include $(SOURCE_DIR)/$(SOURCE_HOME)/make/include.mk

# custom build include
include $(BUILD_INCLUDE)

# platform dependent include file
include $(SOURCE_DIR)/$(SOURCE_HOME)/make/$(PLATFORM)/compopts.mk

.SUFFIXES =	.cc .c .cpp
.PHONY: depend compile print_info

O = .obj
A = .lib

# objects is a list of the .obj files
OBJECTS =	$(SOURCES:.cc=$O) \
		$(C_SOURCES:.c=$O) \
		$(CPP_SOURCES:.cpp=$O)

# meta-rule for .cc to .obj
%$O : %.cc
	@$(CC) -c $(CXXFLAGS) $(CCDEBUG) -Tp$< -Fo$*$O

# meta-rule for .c to .obj
%$O : %.c
	@$(CC) -c $(CFLAGS) $(CCDEBUG) -Tc$< -Fo$*$O

# meta-rule for .cpp to .obj
%$O : %.cpp
	@$(CC) -c $(CPPFLAGS) $(CCDEBUG) -Tp$< -Fo$*$O


# rule for making the library
B_LIBNAME = $(basename $(LIBNAME))$A
TOUCH_LIB_FILE = touch_lib_$(B_LIBNAME)

compile: $(TOUCH_LIB_FILE)

print_info:
	@echo "OBJECTS = $(OBJECTS)" | sed 's/[ 	][ 	]*/ /g'
	@echo "TOUCH_LIB_FILE = $(TOUCH_LIB_FILE)"
	@echo ""

# The following is actually run on the NT machine: 
$(TOUCH_LIB_FILE): $(OBJECTS)
	@if [ "$(LIBNAME)" != "" ]; then \
	  echo "$(AR) /LIBPATH:$(BUILD_DIR) /OUT:$(B_LIBNAME) /NOLOGO $(OBJECTS)" | sed 's/[ 	][ 	]*/ /g' ; \
	  $(AR) /LIBPATH:$(BUILD_DIR) /OUT:$(B_LIBNAME) /NOLOGO $(OBJECTS) ; \
	  touch -f $(B_LIBNAME) $(TOUCH_LIB_FILE) ; \
    ls -al $(B_LIBNAME) $(TOUCH_LIB_FILE) ; \
	fi
	@echo "Done with Touch lib file"

DEPEND_FILE = .depend_$(PLATFORM)
MAKEDEP = $(SOURCE_DIR)/$(SOURCE_HOME)/make/$(PLATFORM)/mdepend.ksh
MAKEDEPFLAGS = -f $(DEPEND_FILE)

# The following is actually run on the NT machine: 
depend:
	@$(MAKEDEP) $(INCLUDE_LIST) $(MAKEDEPFLAGS) $(DEPEND_SOURCES)

include $(SOURCE_DIR)/$(DEPEND_FILE)

