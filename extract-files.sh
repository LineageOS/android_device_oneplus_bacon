#!/bin/sh

#Use Traditional sorting
export LC_ALL=C

FP=$(cd ${0%/*} && pwd -P)
export VENDOR=$(basename $(dirname $FP))
export DEVICE=$(basename $FP)
./../../oppo/msm8974-common/extract-files.sh $@
