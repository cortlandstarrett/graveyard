#==========================================================================
#
# File:      $RCSfile: prodopts.mk,v $
# Version:   $Revision: 1.12 $
# Modified:  $Date: 2013/01/10 23:43:06 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
# compile command
LNK=$(CC_DIR)/LINK.EXE

TFLAGS =         
PURIFY =         
         
ifeq (1,$(DEBUG_BUILD)) 
  LIBDEBUG = -debug -map
else
  LIBDEBUG = 
endif
         
SH_REPB_DLL=libREPB.dll
SH_REPB_IMPLIB=libREPB.lib
SH_REPB_DEF=libREPB.def
         
SH_TRANS_DLL=libTRANS.dll
SH_TRANS_IMPLIB=libTRANS.lib
SH_TRANS_DEF=libTRANS.def

# Changed from -machine:I386 to -machine:IX86
OOA_LIBOPTS = -subsystem:windows -machine:IX86 -nodefaultlib -stack:3072000
SIM_LIBOPTS = -subsystem:windows -machine:IX86 -nodefaultlib -stack:3072000
GEN_LIBOPTS = -subsystem:console -machine:IX86 -nodefaultlib -stack:3072000
PAS_LIBOPTS = -subsystem:console -machine:IX86 -nodefaultlib -stack:3072000
ENV_LIBOPTS = -subsystem:console -machine:IX86 -nodefaultlib -stack:3072000

SCHEMA_PATHS = \
-LIBPATH:$(SCHEMA_DIR) \
-LIBPATH:$(MC_DBMS_SCHEMA_DIR)         

LDPATHS = \
-LIBPATH:$(BUILD_DIR) \
-LIBPATH:$(GALAXYHOME)/lib \
-LIBPATH:$(MC_DBMS_ROOTDIR)/lib \

ifeq (1,$(DEBUG_BUILD)) 
  MSDEV_LIBS = msvcrtd.lib msvcirtd.lib msvcprtd.lib \
  oldnames.lib \
  kernel32.lib \
  user32.lib \
  gdi32.lib \
  winspool.lib \
  comdlg32.lib \
  advapi32.lib \
  mpr.lib \
  netapi32.lib
else
  MSDEV_LIBS = msvcrt.lib msvcirt.lib  msvcprt.lib \
  oldnames.lib \
  kernel32.lib \
  user32.lib \
  gdi32.lib \
  winspool.lib \
  comdlg32.lib \
  advapi32.lib \
  mpr.lib \
  netapi32.lib
endif

MC_DBMS_LIBS = mc_dbms.lib

GALAXY_LIBS = \
vgalc.lib \
vginitc.lib

OOA_LDLIBS = \
libWIN_DE.lib \
libWIN_DS.lib \
libWIN_MI.lib \
libWIN_MD.lib \
libWIN_PR.lib \
libWIN_RE.lib \
libDATA_BK.lib \
libDATA_COM.lib \
libDATA_DD.lib \
libDATA_MDL.lib \
libDATA_SM.lib \
libCE.lib \
libRL.lib \
libIE.lib \
libAL.lib \
libPARS.lib \
libUTIL.lib \
libREPB.lib 

SIM_LDLIBS = \
libSW_COM.lib \
libSW_RE.lib \
libDATA_BK.lib \
libDATA_COM.lib \
libDATA_DD.lib \
libDATA_MDL.lib \
libDATA_SM.lib \
libGS_SIM.lib \
libGS_INTP.lib \
libGS_IDB.lib \
libAL.lib \
libPARS.lib \
libUTIL.lib \
libCE.lib \
libRL.lib \
libTRANS.lib

DBIO_LDLIBS = \
libGS_IDB.lib \
libGS_DBIO.lib \
libGS_UI.lib \
libUTIL.lib

GEN_LDLIBS = \
libGS_GEN.lib \
libGS_IDB.lib \
libGS_INTP.lib \
libGS_UI.lib \
libPARS.lib \
libUTIL.lib \
libTRANS.lib

