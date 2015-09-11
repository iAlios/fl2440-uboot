#!/bin/sh
# 使用说明 
usage()
{
	echo "usage: `basename $0` file"
	echo "        download the file into nand flash"
}

if [ $# -ne 1 ]
then
	usage
	exit 1
fi

# 使用 oflash 进行下载程序
oflash 0 1 0 0 0 $1
