#!/bin/sh
#install Netpbm first
# image2bmp.sh <jpeg> <out>
    jpegtopnm $1 | ppmquant 31 | ppmtobmp -bpp 8 > $2
