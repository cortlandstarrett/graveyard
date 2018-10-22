#==========================================================================
#
# File:      $RCSfile: build_vars_project.inc,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:42:21 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
# Top level include for customizing a BridgePoint build
#
# ====
# NOTE: This file is used both as an imbed for a script and
# ====  is included as a makefile.  Don't put anything in that
#       is incompatiable for this condition.
#
# Input variables
#   ARCH1        - mount point for pttucson's /arch1
#   PLATFORM     - platform for which this build is intended
#   VERSION      - version for this this build in intended

# User environment

# Root of public source tree
BP_PUB=${ARCH1}/bp_source/${PLATFORM}/${VERSION}_extract

BP_PUB_SRC=${ARCH1}/bp_source/${PLATFORM}/${VERSION}
BP_PUB_BLD=${ARCH1}/bp_build/${PLATFORM}/${VERSION}
BP_PUB_PRD=${ARCH1}/bp_prod/${PLATFORM}/${VERSION}

BUILD_DIR=${BP_PUB_BLD}/build
LOG_DIR=${BP_PUB_BLD}/build_log
SCHEMA_DIR=${BP_PUB_BLD}/schema
