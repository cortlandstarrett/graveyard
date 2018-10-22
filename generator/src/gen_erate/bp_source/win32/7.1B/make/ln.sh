#!/bin/sh
#==========================================================================
#
# File:      $RCSfile: ln.sh,v $
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
#echo "Starting $0 $*"
set -e
set -u
# set -x
for link_file in ${LINK_FILES}
do
	if [ "${PLATFORM}" = "sol1" ] ; then
		# echo "/usr/5bin/ln -f -s ${SOURCE_DIR}/${link_file} ${DESTINATION_DIR}"
		/usr/5bin/ln -f -s ${SOURCE_DIR}/${link_file} ${DESTINATION_DIR} ;
	else
		# echo "ln -f -s ${SOURCE_DIR}/${link_file} ${DESTINATION_DIR}"
		ln -f -s ${SOURCE_DIR}/${link_file} ${DESTINATION_DIR} ;
	fi ;
  echo `basename $link_file`
done

# echo "Ending $0"
exit 0 ;
