#==========================================================================
#
# File:      $RCSfile: dep_prod.mk,v $
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

OOA_LIBS = \
		${BUILD_DIR}/libAL.a \
		${BUILD_DIR}/libCE.a \
		${BUILD_DIR}/libDATA_BK.a \
		${BUILD_DIR}/libDATA_COM.a \
		${BUILD_DIR}/libDATA_DD.a \
		${BUILD_DIR}/libDATA_MDL.a \
		${BUILD_DIR}/libDATA_SM.a \
		${BUILD_DIR}/libIE.a \
		${BUILD_DIR}/libPARS.a \
		${BUILD_DIR}/libRL.a \
		${BUILD_DIR}/libUTIL.a \
		${BUILD_DIR}/libWIN_DE.a \
		${BUILD_DIR}/libWIN_DS.a \
		${BUILD_DIR}/libWIN_MD.a \
		${BUILD_DIR}/libWIN_MI.a \
		${BUILD_DIR}/libWIN_PR.a \
		${BUILD_DIR}/libWIN_RE.a

DBIO_LIBS =	${BUILD_DIR}/libGS_DBIO.a \
		${BUILD_DIR}/libGS_IDB.a \
		${BUILD_DIR}/libGS_UI.a \
		${BUILD_DIR}/libUTIL.a

GEN_LIBS =	${BUILD_DIR}/libGS_GEN.a \
		${BUILD_DIR}/libPARS.a \
		${BUILD_DIR}/libGS_INTP.a \
		${BUILD_DIR}/libGS_IDB.a \
		${BUILD_DIR}/libGS_UI.a \
		${BUILD_DIR}/libUTIL.a

SIM_LIBS =	${BUILD_DIR}/libAL.a \
		${BUILD_DIR}/libPARS.a \
		${BUILD_DIR}/libDATA_BK.a \
		${BUILD_DIR}/libDATA_COM.a \
		${BUILD_DIR}/libDATA_DD.a \
		${BUILD_DIR}/libDATA_MDL.a \
		${BUILD_DIR}/libDATA_SM.a \
		${BUILD_DIR}/libGS_IDB.a \
		${BUILD_DIR}/libGS_SIM.a \
		${BUILD_DIR}/libGS_INTP.a \
		${BUILD_DIR}/libSW_COM.a \
		${BUILD_DIR}/libSW_RE.a \
		${BUILD_DIR}/libUTIL.a


OOA_SCHEMAS =	${SCHEMA_DIR}/libooa.ldb

GEN_SCHEMAS =	${SCHEMA_DIR}/libgen.ldb

SIM_SCHEMAS =	${SCHEMA_DIR}/libsim.ldb


OOA_APPLICATION_SCHEMA_DB_PATH = ${SCHEMA_DIR}/ooa.app_schema
GEN_APPLICATION_SCHEMA_DB_PATH = ${SCHEMA_DIR}/gen.app_schema
SIM_APPLICATION_SCHEMA_DB_PATH = ${SCHEMA_DIR}/sim.app_schema

