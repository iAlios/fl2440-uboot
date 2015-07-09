#!/bin/sh
#
# Patch mtd into kernel
#
# usage:patchkernel [-2 -3 -b] kernelpath
# 	kernelpath must be given
#	
# Works for Kernels >= 2.6.8 
#
# You can use it for pristine kernels and for already patches kernels too.
#
# tglx (tglx@linutronix.de)
#
# $Id: patchkernel.sh,v 1.2 2005/03/14 16:53:19 gleixner Exp $
#
# 13-03-2004 tglx simple wrapper for treewalk.py

#
# Display usage of this script
#
usage () {
	echo "usage:  $0 [-c] [-2] [-3] [-b] [-y] kernelpath"
	echo "   -c  -- copy files to kernel tree instead of building links"
	echo "   -2  -- include JFFS2 file system"
	echo "   -3  -- include JFFS3 file system (experimental, you probably don't want this)"
	echo "   -b  -- check files out for write from BK" 
	echo '   -y  -- assume "Yes" on any question'
	echo '   -v  -- verbosity level'
	exit 1
}

#
# Start of script
#
JFFS2_FS="no"
JFFS3_FS="no"
JFFS2=""
JFFS3=""
METHOD="ln"
BK=""
ASSUME_YES=no
VERBOSE=""

# Get commandline options
while getopts 23cbvy opt
do
    case "$opt" in
      2)  JFFS2="jffs2"; JFFS2_FS="jffs2";;
      3)  JFFS3="jffs3"; JFFS3_FS="jffs3";;
      c)  METHOD="cp";;
      b)  BK="bk";;
      y)  ASSUME_YES=yes;;
      v)  VERBOSE="-v 1";;
      \?)
	  usage;
    esac
done
shift `expr $OPTIND - 1`
LINUXDIR=$1

if [ -z $LINUXDIR ]; then
    usage;
fi

if [ ! -f $LINUXDIR/Makefile -a "$BK" = "yes" ]; then
    pushd $LINUXDIR
    bk co Makefile
    popd
fi

# Check if kerneldir contains a Makefile
if [ ! -f $LINUXDIR/Makefile ] 
then 
	echo "Directory $LINUXDIR does not exist or is not a kernel source directory";
	exit 1;
fi

if [ $ASSUME_YES != "yes" ]; then
	echo "Patching $LINUXDIR"
	echo "Include JFFS2 file system: $JFFS2_FS"
	echo "Include JFFS3 file system (experimental): $JFFS3_FS"
	echo "Method: $METHOD"
	read -p "Can we start now ? [y/N]" ANSWER
	echo ""
	if [ "$ANSWER" != "y" ]; then
		echo Patching Kernel cancelled
		exit 1;
	fi
fi

ACTIONS="-a $METHOD,$JFFS2,$JFFS3,$BK"

scripts/treewalk.py -f scripts/patchin.xml $ACTIONS $VERBOSE $LINUXDIR

