#==========================================================================
#
# File:      $RCSfile: rep_scripts.mk,v $
# Version:   $Revision: 1.9 $
# Modified:  $Date: 2013/01/10 23:43:07 $
#
# (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
#
#==========================================================================
# This document contains information proprietary and confidential to
# Mentor Graphics Corp., and is not for external distribution.
#==========================================================================
#

include $(BUILD_INCLUDE)
include ${SOURCE_HOME}/make/${PLATFORM}/compopts.mk

REP_SOURCE_PATH=$(NT_ARCH1)${SOURCE_HOME}/repbin/src
REP_INCLUDE_PATH=-I$(NT_ARCH1)${SOURCE_HOME}/repbin/include
REP_LIB_PATH=${SH_REPB_IMPLIB}

rep_scripts: \
	pt_ver_data_get.exe \
	pt_ver_info_get.exe \
	pt_ver_num_highest_get.exe \
	pt_get_ver_data.exe \
	pt_get_ver_info.exe \
	pt_get_latest.exe \
	pt_get_branches.exe \
	pt_get_versions.exe

pt_get_env_compat.obj: $(REP_SOURCE_PATH)/pt_get_env_compat.c
	$(CC) $(REP_INCLUDE_PATH) -c $(REP_SOURCE_PATH)/pt_get_env_compat.c

pt_ver_data_get.obj: $(REP_SOURCE_PATH)/pt_ver_data_get.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_ver_data_get.c

pt_ver_info_get.obj: $(REP_SOURCE_PATH)/pt_ver_info_get.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_ver_info_get.c

pt_ver_num_highest_get.obj: $(REP_SOURCE_PATH)/pt_ver_num_highest_get.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_ver_num_highest_get.c


pt_ver_data_get.exe: pt_ver_data_get.obj pt_get_env_compat.obj $(SH_REPB_DLL)
	link pt_ver_data_get.obj pt_get_env_compat.obj $(REP_LIB_PATH)

pt_ver_info_get.exe: pt_ver_info_get.obj pt_get_env_compat.obj $(SH_REPB_DLL)
	link pt_ver_info_get.obj pt_get_env_compat.obj $(REP_LIB_PATH)

pt_ver_num_highest_get.exe: pt_ver_num_highest_get.obj pt_get_env_compat.obj $(SH_REPB_DLL)
	link pt_ver_num_highest_get.obj pt_get_env_compat.obj $(REP_LIB_PATH)


pt_get_env.obj: $(REP_SOURCE_PATH)/pt_get_env.c
	$(CC) $(REP_INCLUDE_PATH) -c $(REP_SOURCE_PATH)/pt_get_env.c

pt_get_ver_data.obj: $(REP_SOURCE_PATH)/pt_get_ver_data.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_get_ver_data.c

pt_get_ver_info.obj: $(REP_SOURCE_PATH)/pt_get_ver_info.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_get_ver_info.c

pt_get_latest.obj: $(REP_SOURCE_PATH)/pt_get_latest.c
	$(CC) $(REP_INCLUDE_PATH) /c $(REP_SOURCE_PATH)/pt_get_latest.c


pt_get_ver_data.exe: pt_get_ver_data.obj pt_get_env.obj $(SH_REPB_DLL)
	link pt_get_ver_data.obj pt_get_env.obj $(REP_LIB_PATH)

pt_get_ver_info.exe: pt_get_ver_info.obj pt_get_env.obj $(SH_REPB_DLL)
	link pt_get_ver_info.obj pt_get_env.obj $(REP_LIB_PATH)

pt_get_latest.exe: pt_get_latest.obj pt_get_env.obj $(SH_REPB_DLL)
	link pt_get_latest.obj pt_get_env.obj $(REP_LIB_PATH)


pt_get_branches.exe: pt_get_branches.obj pt_get_env.obj $(SH_REPB_DLL)
	link pt_get_branches.obj pt_get_env.obj $(REP_LIB_PATH)

pt_get_versions.exe: pt_get_versions.obj pt_get_env.obj $(SH_REPB_DLL)
	link pt_get_versions.obj pt_get_env.obj $(REP_LIB_PATH)


#
# Formatting information for emacs
#
# Local Variables:
# tab-width:2
# End:
#
