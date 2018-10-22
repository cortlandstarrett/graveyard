#!/bin/sh         
#==========================================================================
#
# File:      $RCSfile: cslash.ksh,v $
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
# Parms:
#   $1 - name of the file to convert
#
# convert forward slashes (/) to backslashes (\)
# start each -xxx parm on a new line
# assure ^M's at the end of each line
# change aaa/xxx/.../bbb to aaa/bbb
#

fname=$1
cat $fname |
sed 's|//|/|g
     s|/|\\|g
     s|[ 	][ 	]*| |g
     s|[ 	][ 	]*$||
     s|\\[^\\][^\\]*\\\.\.\\|\\|g
     s|\\[^\\][^\\]*\\\.\.\\|\\|g
     s|\\[^\\][^\\]*\\\.\.\\|\\|g' |
sed 's| -|\
-|g' > $fname.tmp
mv $fname.tmp $fname
