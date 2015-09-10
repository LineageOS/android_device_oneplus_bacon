#!/bin/bash

# Use Traditional sorting
export LC_ALL=C

FP=$(cd ${0%/*} && pwd -P)
export VENDOR=$(basename $(dirname $FP))
export DEVICE=$(basename $FP)

function extract() {
    for FILE in `egrep -v '(^#|^$)' $1`; do
        OLDIFS=$IFS IFS=":" PARSING_ARRAY=($FILE) IFS=$OLDIFS
        FILE=`echo ${PARSING_ARRAY[0]} | sed -e "s/^-//g"`
        DEST=${PARSING_ARRAY[1]}
        if [ -z $DEST ]; then
            DEST=$FILE
        fi
        DIR=`dirname $FILE`
        if [ ! -d $2/$DIR ]; then
            mkdir -p $2/$DIR
        fi
        # Try CM target first
        adb pull /system/$DEST $2/$DEST
        # if file does not exist try OEM target
        if [ "$?" != "0" ]; then
            adb pull /system/$FILE $2/$DEST
        fi
    done
}


DEVBASE=../../../vendor/$VENDOR/$DEVICE/proprietary
rm -rf $DEVBASE/*

extract proprietary-files-qc.txt $DEVBASE
extract proprietary-files.txt $DEVBASE

../../../device/$VENDOR/$DEVICE/setup-makefiles.sh
