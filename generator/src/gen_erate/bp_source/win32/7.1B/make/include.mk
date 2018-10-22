#==========================================================================
#
# File:      $RCSfile: include.mk,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:41:55 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#

INCLUDE_LIST  = -I${SOURCE_DIR}/${SOURCE_HOME}/action/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/canvased/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/data/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/gen_sim/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/imp_exp/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/parser/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/render/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/repbin/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/swindow/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/translate/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/utility/include \
		-I${SOURCE_DIR}/${SOURCE_HOME}/window/include \
		-I$(GALAXYHOME)/include \
		-I$(MC_DBMS_ROOTDIR)/include \
		-I$(BUILD_DIR) \
                -I.
