#==========================================================================
#
# File:      $RCSfile: leaf.mk,v $
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

include ${BUILD_INCLUDE}

SOURCE_DIR=`pwd`




all:	compile




scour:
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "Begin making  scour  in `pwd`"
	@echo
	@if [ ! -f .depend_${PLATFORM} ]; then  touch .depend_${PLATFORM}; fi
	@TARGET="scour" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		PLATFORM="${PLATFORM}" \
		VERSION="${VERSION}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		SOURCES="${SOURCES}" \
		CPP_SOURCES="${CPP_SOURCES}" \
		C_SOURCES="${C_SOURCES}" \
		COMPONENT="${COMPONENT}" \
		LIBNAME="${LIBNAME}" \
		APPL_SCHEMAS="${APPL_SCHEMAS}" \
		ANTLR_COMPILE="${ANTLR_COMPILE}" \
		ANTLR_LINKS="${ANTLR_LINKS}" \
		ANTLR_MAKEFILE="${ANTLR_MAKEFILE}" \
		VRE_VR="${VRE_VR}" \
		VRE_SOURCE="${VRE_SOURCE}" \
		${SOURCE_HOME}/make/${PLATFORM}/leaf.sh
	@echo
	@echo "End making  scour  in `pwd`"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"


links:
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "Begin making  links  in `pwd`"
	@echo
	@TARGET="links" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		PLATFORM="${PLATFORM}" \
		VERSION="${VERSION}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		SOURCES="${SOURCES}" \
		CPP_SOURCES="${CPP_SOURCES}" \
		C_SOURCES="${C_SOURCES}" \
		COMPONENT="${COMPONENT}" \
		LIBNAME="${LIBNAME}" \
		APPL_SCHEMAS="${APPL_SCHEMAS}" \
		ANTLR_COMPILE="${ANTLR_COMPILE}" \
		ANTLR_LINKS="${ANTLR_LINKS}" \
		ANTLR_MAKEFILE="${ANTLR_MAKEFILE}" \
		VRE_VR="${VRE_VR}" \
		VRE_SOURCE="${VRE_SOURCE}" \
		${SOURCE_HOME}/make/${PLATFORM}/leaf.sh
	@echo
	@echo "End making  links  in `pwd`"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"




depend:
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "Begin making  depend  in `pwd`"
	@echo
	@if [ ! -f .depend_${PLATFORM} ]; then \
	   touch .depend_${PLATFORM}; \
	 fi
	@ ssrcs= ; \
	  a_s="${APPL_SCHEMAS}" ; \
	  for s in $${a_s}; \
      do \
	    ssrcs="$${ssrcs} schem$${s}.cc"; \
	  done; \
	  TARGET="depend" \
	  MAKE="${MAKE}" \
	  MAKEFLAGS="${MAKEFLAGS}" \
	  PLATFORM="${PLATFORM}" \
	  VERSION="${VERSION}" \
	  SOURCE_HOME="${SOURCE_HOME}" \
	  BUILD_DIR="${BUILD_DIR}" \
	  SOURCES="${SOURCES}" \
	  CPP_SOURCES="${CPP_SOURCES}" \
	  C_SOURCES="${C_SOURCES}" \
	  COMPONENT="${COMPONENT}" \
	  LIBNAME="${LIBNAME}" \
	  APPL_SCHEMAS="${APPL_SCHEMAS}" \
	  ANTLR_COMPILE="${ANTLR_COMPILE}" \
	  ANTLR_LINKS="${ANTLR_LINKS}" \
	  ANTLR_MAKEFILE="${ANTLR_MAKEFILE}" \
	  VRE_VR="${VRE_VR}" \
	  VRE_SOURCE="${VRE_SOURCE}" \
	  DEPEND_SOURCES="${SOURCES} ${VRE_SOURCE} ${CPP_SOURCES} ${C_SOURCES} $${ssrcs}" \
	  ${SOURCE_HOME}/make/${PLATFORM}/leaf.sh
	@-chmod 666 .depend_${PLATFORM};
	@echo
	@echo "End making  depend  in `pwd`"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"




compile:
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "Inside leaf.mk"
	@echo "Begin making  compile  in `pwd`"
	@echo
	@if [ ! -f .depend_${PLATFORM} ]; then  touch .depend_${PLATFORM}; fi
	@TARGET="compile" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		PLATFORM="${PLATFORM}" \
		VERSION="${VERSION}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		SOURCES="${SOURCES}" \
		CPP_SOURCES="${CPP_SOURCES}" \
		C_SOURCES="${C_SOURCES}" \
		COMPONENT="${COMPONENT}" \
		LIBNAME="${LIBNAME}" \
		APPL_SCHEMAS="${APPL_SCHEMAS}" \
		ANTLR_COMPILE="${ANTLR_COMPILE}" \
		ANTLR_LINKS="${ANTLR_LINKS}" \
		ANTLR_MAKEFILE="${ANTLR_MAKEFILE}" \
		VRE_VR="${VRE_VR}" \
		VRE_SOURCE="${VRE_SOURCE}" \
		${SOURCE_HOME}/make/${PLATFORM}/leaf.sh
	@echo
	@echo "End making  compile  in `pwd`"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"

schema:
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "Begin making  schema  in `pwd`"
	@echo
	@if [ ! -f .depend_${PLATFORM} ]; then touch .depend_${PLATFORM}; fi
	@TARGET="schema" \
		MAKE="${MAKE}" \
		MAKEFLAGS="${MAKEFLAGS}" \
		PLATFORM="${PLATFORM}" \
		VERSION="${VERSION}" \
		SOURCE_HOME="${SOURCE_HOME}" \
		SOURCES="${SOURCES}" \
		CPP_SOURCES="${CPP_SOURCES}" \
		C_SOURCES="${C_SOURCES}" \
		COMPONENT="${COMPONENT}" \
		LIBNAME="${LIBNAME}" \
		APPL_SCHEMAS="${APPL_SCHEMAS}" \
		ANTLR_COMPILE="${ANTLR_COMPILE}" \
		ANTLR_MAKEFILE="${ANTLR_MAKEFILE}" \
		ANTLR_LINKS="${ANTLR_LINKS}" \
		VRE_VR="${VRE_VR}" \
		VRE_SOURCE="${VRE_SOURCE}" \
		${SOURCE_HOME}/make/${PLATFORM}/leaf.sh
	@echo
	@echo "End making  schema  in `pwd`"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	@echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
