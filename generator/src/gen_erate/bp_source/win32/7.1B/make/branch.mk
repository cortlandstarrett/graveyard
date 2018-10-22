#==========================================================================
#
# File:      $RCSfile: branch.mk,v $
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

all:	compile


clean:
	@echo "##########################################################################"
	@echo "##########################################################################"
	@echo BEGIN MAKING clean FOR ${SOURCE_DIRS} FROM `pwd`
	@echo
	@TARGET="clean" \
		SOURCE_DIRS="${SOURCE_DIRS}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		${SOURCE_HOME}/make/branch.sh
	@echo
	@echo END MAKING clean FOR ${SOURCE_DIRS} FROM `pwd`
	@echo "##########################################################################"
	@echo "##########################################################################"


scour:
	@echo "##########################################################################"
	@echo "##########################################################################"
	@echo BEGIN MAKING scour FOR ${SOURCE_DIRS} FROM `pwd`
	@echo
	@TARGET="scour" \
		SOURCE_DIRS="${SOURCE_DIRS}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		${SOURCE_HOME}/make/branch.sh
	@echo
	@echo END MAKING scour FOR ${SOURCE_DIRS} FROM `pwd`
	@echo "##########################################################################"
	@echo "##########################################################################"


links:
	@echo "##########################################################################"
	@echo "##########################################################################"
	@echo BEGIN MAKING links FOR ${SOURCE_DIRS} FROM `pwd`
	@echo
	@TARGET="links" \
		SOURCE_DIRS="${SOURCE_DIRS}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		${SOURCE_HOME}/make/branch.sh
	@echo
	@echo END MAKING links FOR ${SOURCE_DIRS} FROM `pwd`
	@echo "##########################################################################"
	@echo "##########################################################################"


depend:
	@echo "##########################################################################"
	@echo "##########################################################################"
	@echo BEGIN MAKING depend FOR ${SOURCE_DIRS} FROM `pwd`
	@echo
	@TARGET="depend" \
		SOURCE_DIRS="${SOURCE_DIRS}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		${SOURCE_HOME}/make/branch.sh
	@echo
	@echo END MAKING depend FOR ${SOURCE_DIRS} FROM `pwd`
	@echo "##########################################################################"
	@echo "##########################################################################"


compile:
	@echo "##########################################################################"
	@echo "##########################################################################"
	@echo "Inside branch.mk"
	@echo BEGIN MAKING compile FOR ${SOURCE_DIRS} FROM `pwd`
	@echo
	@TARGET="compile" \
		SOURCE_DIRS="${SOURCE_DIRS}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		${SOURCE_HOME}/make/branch.sh
	@echo
	@echo END MAKING compile FOR ${SOURCE_DIRS} FROM `pwd`
	@echo "##########################################################################"
	@echo "##########################################################################"
