#==========================================================================
#
# File:      $RCSfile: compopts.mk,v $
# Version:   $Revision: 1.10 $
# Modified:  $Date: 2013/01/10 23:43:07 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
# COMPILER FLAGS
TFLAGS=
OTHER_FLAGS = -GX -Zm800 -nologo -D_CONSOLE -DNOMINMAX -DWIN32
CC_GALAXY_FLAGS = -DvdebugDEBUG=0

ifeq (0,$(DEBUG_BUILD))
  CCDEBUG  = -MD -O2 
  CCFLAGS  = $(CCDEBUG) $(TFLAGS)
  CPPFLAGS = $(INCLUDE_LIST) $(OTHER_FLAGS) $(CC_GALAXY_FLAGS)
  CXXFLAGS = $(CCFLAGS) $(CPPFLAGS)
  CFLAGS = $(CCFLAGS) $(CPPFLAGS)
else
  CCDEBUG  = -MDd -D_DEBUG -Zi -Od -GZ
  CCFLAGS  = $(CCDEBUG) $(TFLAGS)
  CPPFLAGS = $(INCLUDE_LIST) $(OTHER_FLAGS) $(CC_GALAXY_FLAGS)
  CXXFLAGS = $(CCFLAGS) $(CPPFLAGS)
  CFLAGS = $(CCFLAGS) $(CPPFLAGS)
endif

# this galaxhome include resolves an ostore bug.  It must be first
CCSCHEMAFLAGS = -I$(GALAXYHOME)/ostore/include $(CPPFLAGS)

MC_DBMS_SCHEMA_FLAGS =

# Various executables
CC=$(CC_DIR)/CL.EXE
cc=$(CC_DIR)/CL.EXE
AR=$(CC_DIR)/LIB.EXE

