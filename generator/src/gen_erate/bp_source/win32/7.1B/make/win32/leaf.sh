#!/bin/sh
#==========================================================================
#
# File:      $RCSfile: leaf.sh,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:43:06 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#
echo "leaf.sh: Starting $0 $*"
set -e

export MAKE
. $BUILD_INCLUDE

# Assure variables are set
DEPEND_SOURCES=${DEPEND_SOURCES:=}
SPEC_FILE=${SPEC_FILE:=}

set -u

SOURCE_DIR=`pwd`
export SOURCE_DIR

if [ "${TARGET}" = "scour" ]; then
	rm -f .depend_${PLATFORM}
	rm -rf ${BUILD_DIR}
	rm -rf ${SCHEMA_DIR}

elif [ "${TARGET}" = "links" ]; then
	if [ ! -d "${BUILD_DIR}" ]; then
		mkdir -p ${BUILD_DIR}
		chmod 777 ${BUILD_DIR}
	fi

	if [ ! -f "${BUILD_DIR}/platform.str" ]; then
		echo "\"${PLATFORM}\"" > ${BUILD_DIR}/platform.str
		chmod 666 ${BUILD_DIR}/platform.str
	fi

	if [ ! -f "${BUILD_DIR}/version.str" ]; then
		echo "\"${VERSION}\"" > ${BUILD_DIR}/version.str
		chmod 666 ${BUILD_DIR}/version.str
	fi

	if [ ! -d "${SCHEMA_DIR}" ]; then
		mkdir -p ${SCHEMA_DIR}
		chmod 777 ${SCHEMA_DIR}
	fi

	if [ "${ANTLR_LINKS}" ]; then
	    cd ${SOURCE_DIR}
	    $MAKE -f ${ANTLR_MAKEFILE} ${ANTLR_LINKS}
	fi

	if [ "${SOURCES}" ]; then
		cd ${BUILD_DIR}
		if [ "${?}" = "0" ]; then
			rm -f ${SOURCES}
			SOURCE_DIR="${SOURCE_DIR}" \
				DESTINATION_DIR="${BUILD_DIR}" \
				LINK_FILES="${SOURCES}" \
				${SOURCE_DIR}/${SOURCE_HOME}/make/ln.sh
		else
			echo ERROR:  cd to ${BUILD_DIR} failed.
      exit 1
		fi
	fi

	if [ "${CPP_SOURCES}" ]
	then
		cd ${BUILD_DIR}
		if [ "${?}" = "0" ]
		then
			rm -f ${CPP_SOURCES}
			SOURCE_DIR="${SOURCE_DIR}" \
				DESTINATION_DIR="${BUILD_DIR}" \
				LINK_FILES="${CPP_SOURCES}" \
				${SOURCE_DIR}/${SOURCE_HOME}/make/ln.sh
		else
			echo ERROR:  cd to ${BUILD_DIR} failed.
		fi
	fi

	if [ "${C_SOURCES}" ]
	then
		cd ${BUILD_DIR}
		if [ "${?}" = "0" ]
		then
			rm -f ${C_SOURCES}
			SOURCE_DIR="${SOURCE_DIR}" \
				DESTINATION_DIR="${BUILD_DIR}" \
				LINK_FILES="${C_SOURCES}" \
				${SOURCE_DIR}/${SOURCE_HOME}/make/ln.sh
		else
			echo ERROR:  cd to ${BUILD_DIR} failed.
      exit 1
		fi
	fi

	if [ "${APPL_SCHEMAS}" ];then
     for schema_source in ${APPL_SCHEMAS}
       do
         schema_srcfile=schem${schema_source}.cc
         schema_objfile=schem${schema_source}.obj
         schema_libfile=lib${schema_source}.ldb
         rm -f ${SCHEMA_DIR}/${schema_srcfile}
         ln -f -s ${SOURCE_DIR}/${schema_srcfile} ${SCHEMA_DIR}
         rm -f ${SCHEMA_DIR}/${schema_objfile}
         ln -f -s ${SCHEMA_DIR}/${schema_libfile} ${SCHEMA_DIR}/${schema_objfile}
       done
	fi

elif [ "${TARGET}" = "depend" ]
then
  $MAKE \
    -f ${SOURCE_DIR}/${SOURCE_HOME}/make/${PLATFORM}/lib.mk \
	MAKEFLAGS=${MAKEFLAGS} \
	SOURCE_DIR=${SOURCE_DIR} \
	SOURCE_HOME=${SOURCE_HOME} \
	SOURCES="${SOURCES}" \
	CPP_SOURCES="${CPP_SOURCES}" \
	C_SOURCES="${C_SOURCES}" \
	DEPEND_SOURCES="${DEPEND_SOURCES}" \
	SPEC_FILE="${SPEC_FILE}" \
	LIBNAME="${LIBNAME}" \
	APPL_SCHEMAS="${APPL_SCHEMAS}" \
    ${TARGET}
else
  # [ "${TARGET}" = "compile" ]
	if [ ! -d "${BUILD_DIR}" ]; then
		mkdir -p ${BUILD_DIR}
		chmod 777 ${BUILD_DIR}
		chmod 666 ${BUILD_DIR}/platform.str
		chmod 666 ${BUILD_DIR}/version.str
	fi


	if [ ! -d "${SCHEMA_DIR}" ]; then
		mkdir -p ${SCHEMA_DIR}
		chmod 777 ${SCHEMA_DIR}
	fi


	APPL_SCHEMAS=${APPL_SCHEMAS:-null_schema}
  if [ "${APPL_SCHEMAS}" = "null_schema" ]
  then
    APPL_SCHEMAS=
  fi

	cd ${BUILD_DIR}
	#echo "$MAKE -f ${SOURCE_DIR}/${SOURCE_HOME}/make/${PLATFORM}/lib.mk MAKEFLAGS=${MAKEFLAGS} SOURCE_DIR=${SOURCE_DIR} SOURCE_HOME=${SOURCE_HOME} SOURCES="${SOURCES}" CPP_SOURCES="${CPP_SOURCES}" C_SOURCES="${C_SOURCES}" DEPEND_SOURCES="${DEPEND_SOURCES}" SPEC_FILE="${SPEC_FILE}" LIBNAME="${LIBNAME}" APPL_SCHEMAS="${APPL_SCHEMAS}" ${TARGET}"
	$MAKE -f ${SOURCE_DIR}/${SOURCE_HOME}/make/${PLATFORM}/lib.mk MAKEFLAGS=${MAKEFLAGS} SOURCE_DIR=${SOURCE_DIR} SOURCE_HOME=${SOURCE_HOME} SOURCES="${SOURCES}" CPP_SOURCES="${CPP_SOURCES}" C_SOURCES="${C_SOURCES}" DEPEND_SOURCES="${DEPEND_SOURCES}" SPEC_FILE="${SPEC_FILE}" LIBNAME="${LIBNAME}" APPL_SCHEMAS="${APPL_SCHEMAS}" ${TARGET}

	if [ "${APPL_SCHEMAS}" ]
	then

		cd ${SCHEMA_DIR};
    for schema_source in ${APPL_SCHEMAS}
      do
      schema_srcfile=schem${schema_source}.cc
      schema_objfile=schema_${schema_source}.obj
      schema_libfile=lib${schema_source}.ldb
      schema_outfile=${schema_source}.app_schema
      #echo "$MAKE -f ${SOURCE_DIR}/${SOURCE_HOME}/make/${PLATFORM}/lib.mk MAKEFLAGS=${MAKEFLAGS} SOURCE_DIR=${SOURCE_DIR} SOURCE_HOME=${SOURCE_HOME} SOURCES="${SOURCES}" CPP_SOURCES="${CPP_SOURCES}" C_SOURCES="${C_SOURCES}" DEPEND_SOURCES="${DEPEND_SOURCES}" SPEC_FILE="${SPEC_FILE}" LIBNAME="${LIBNAME}" SCHEMA_SOURCE="${schema_source}" SCHEMA_SRCFILE="${schema_srcfile}" SCHEMA_OBJFILE="${schema_objfile}" SCHEMA_LIBFILE="${schema_libfile}" ${schema_outfile}"
      $MAKE -f ${SOURCE_DIR}/${SOURCE_HOME}/make/${PLATFORM}/lib.mk MAKEFLAGS=${MAKEFLAGS} SOURCE_DIR=${SOURCE_DIR} SOURCE_HOME=${SOURCE_HOME} SOURCES="${SOURCES}" CPP_SOURCES="${CPP_SOURCES}" C_SOURCES="${C_SOURCES}" DEPEND_SOURCES="${DEPEND_SOURCES}" SPEC_FILE="${SPEC_FILE}" LIBNAME="${LIBNAME}" SCHEMA_SOURCE="${schema_source}" SCHEMA_SRCFILE="${schema_srcfile}" SCHEMA_OBJFILE="${schema_objfile}" SCHEMA_LIBFILE="${schema_libfile}" ${schema_outfile}
      done
	fi
fi
echo "leaf.sh: Ending $0"
