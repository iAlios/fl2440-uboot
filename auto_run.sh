#!/bin/sh
usage()
{
	echo "usage: `basename $0` download|rnew"
	echo "           download <file>      download file with oflash tools"
	echo "           rnew <build_path>    clean all files, remake uboot, then download it"
}

if [ $# -lt 2 ]
then
	usage
	exit 1
fi

case $1 in
	rnew) echo "start clean files, remake uboot, then download it into nand flash....."
	rm -rf $2
	make O=$2 clean
	make O=$2 fl2440_config
	make O=$2
	if [ $? -eq 0 ]
	then
		./download.sh $2/u-boot.bin
	else
		echo "=============== build error =============="
		exit 1
	fi
	;;
	download) echo "download file into nand flash...."
	./download.sh $2
	;;
	*) usage
	;;
esac

