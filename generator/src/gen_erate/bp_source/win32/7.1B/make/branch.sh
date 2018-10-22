#!/bin/sh
#==========================================================================
#
# File:      $RCSfile: branch.sh,v $
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
set -e
set -u

export MAKE
# echo "branch.sh: In `basename $0`:
#   MAKE=$MAKE
#   MAKEFLAGS='$MAKEFLAGS'"

for source_dir in ${SOURCE_DIRS}
do
  cd ${source_dir}
  pwd
  #echo "branch.sh: $MAKE -$MAKEFLAGS ${TARGET}"
  $MAKE -$MAKEFLAGS ${TARGET}
  cd ..
done





