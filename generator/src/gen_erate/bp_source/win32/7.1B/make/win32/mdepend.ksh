#!/bin/sh
#==========================================================================
#
# File:      $RCSfile: mdepend.ksh,v $
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
#	Do the equivalent of the 'makedepend' program, but do it right.
#
#	Usage:
#
#	makedepend [cpp-flags] [-w width] [-s magic-string] [-f makefile]
#	  [-o object-suffix]
#
#	Notes:
#
#	The C compiler used can be overridden with the environment
#	variable "CC".
#
#	The "-v" switch of the "makedepend" program is not supported.
#
#
#	This script should
#	work on both USG and BSD systems.  However, when System V.4 comes out,
#	USG users will probably have to change "silent" to "-s" instead of
#	"-" (at least, that's what the documentation implies).
#
CC=${CC:-cl}


silent='-'

MC_DBMS_ROOTDIR=`echo "${MC_DBMS_ROOTDIR}" |
sed 's!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!\\\\/!/!g'`

GALAXYHOME=`echo "${GALAXYHOME}" |
sed 's!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!\\\\!/!g'`

# echo "MC_DBMS_ROOTDIR: '${MC_DBMS_ROOTDIR}'"
# echo "GALAXYHOME: '${GALAXYHOME}'"

TMP=${TMPDIR:-/tmp}/mdep$$
CPPCMD=${TMP}a.ksh
DEPENDLINES=${TMP}b
TMPMAKEFILE=${TMP}c
MAGICLINE=${TMP}d


trap "rm -f ${TMP}*; exit 1" 1 2 15
trap "rm -f ${TMP}*; exit 0" 1 2 13

echo " \c" > $CPPCMD
if [ `wc -c < $CPPCMD` -eq 1 ]
then
    c="\c"
    n=
else
    c=
    n="-n"
fi

echo $n "exec $CC -nologo -DWIN32 -MD -E$c " > $CPPCMD
chmod +x $CPPCMD

files=
makefile=
magic_string='# DO NOT DELETE'
objsuffix='obj'
width=78

while [ $# != 0 ]
do
    case "$1" in
	-D*)
	    echo $n " '$1'$c" >> $CPPCMD
	    ;;
    -I*)
        ifile="$1"
        # Remove /xxx/../ from directory names
        ifile=`echo "$ifile" |
sed 's!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!/[^/\.][^/]*/\.\./!/!g
s!\\\\!/!g'`
        # echo "ifile: '$ifile'"
	    echo $n " '$ifile'$c" >> $CPPCMD
	    ;;
	-w)
	    width="$2"
	    shift
	    ;;
	-s)
	    magic_string="$2"
	    shift
	    ;;
	-f)
	    makefile="$2"
	    shift
	    ;;
	-o)
	    objsuffix="$2"
	    shift
	    ;;
	-*)
	    echo "Unknown option '$1' ignored" 1>&2
	    ;;
	*)
	    files="$files $1"
	    ;;
    esac
    shift
done

echo ' $*' >> $CPPCMD

case "$makefile" in
    '')
	if [ -r makefile ]
	then
	    makefile=makefile
	elif [ -r Makefile ]
	then
	    makefile=Makefile
	else
	    echo 'no makefile or Makefile found' 1>&2
	    exit 1
	fi
	;;
    -)
	makefile=$TMPMAKEFILE
	;;
esac

echo '' > $DEPENDLINES
for i in $files
do
    f=`echo $i | awk -F\. '{ print $1 }'`
    lines=`$CPPCMD $i |
           grep "#line" |
           awk -F\" '{print $2}' |
           sed 's!\\\\\\\\!/!g' |
           sort -u |
           grep -iv 'program files' |
           grep -v "${MC_DBMS_ROOTDIR}" |
           grep -v "${GALAXYHOME}"`
    for line in $lines
    do
      # For DEBUG: echo "$f.obj: \"$line\"" | tee -a $DEPENDLINES
      echo "$f.obj: \"$line\"" >> $DEPENDLINES
    done
done 

printf "Writing dependency file ${makefile}\n"

trap "" 1 2 13 15	# Now we are committed
case "$makefile" in
    $TMPMAKEFILE)
	;;
    *)
	rm -f ${makefile}.bak
	cp ${makefile} ${makefile}.bak
	;;
esac

#
#	Before we go edit the Makefile, we must make sure that magic_string
#	exists, and that it's not the last line.  Otherwise, dear old ed
#	will exit prematurely.  What a pain.
#
cat >> $makefile <<- END_OF_APPEND
	$magic_string

END_OF_APPEND
ed $silent $makefile <<- END_OF_ED_SCRIPT
	/^$magic_string/w $MAGICLINE
	/^$magic_string/,\$d
	\$r $MAGICLINE
	\$r $DEPENDLINES
	w
	q
END_OF_ED_SCRIPT

case "$makefile" in
    $TMPMAKEFILE)
	cat $TMPMAKEFILE
	;;
esac

rm -f ${TMP}*
rm -f ${makefile}.bak
