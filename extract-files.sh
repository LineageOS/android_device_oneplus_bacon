#!/bin/bash

# Use Traditional sorting
export LC_ALL=C

FP=$(cd ${0%/*} && pwd -P)
export VENDOR=$(basename $(dirname $FP))
export DEVICE=$(basename $FP)

while getopts ":hd:" options
do
    case $options in
        d ) LDIR=$OPTARG ;;
        h ) echo "Usage: `basename $0` [OPTIONS] "
            echo "  -d  Fetch blobs from local directory"
            echo "  -h  Show this help"
            exit ;;
        * ) ;;
    esac
done

function extract() {
    for FILE in `egrep -v '(^#|^$)' $1`; do
        OLDIFS=$IFS IFS=":" PARSING_ARRAY=($FILE) IFS=$OLDIFS
        FILE=`echo ${PARSING_ARRAY[0]} | sed -e "s/^-//g"`
        DEST=${PARSING_ARRAY[1]}
        if [ -z $DEST ]; then
            DEST=$FILE
        fi
        DIR=`dirname $DEST`
        if [ ! -d $2/$DIR ]; then
            mkdir -p $2/$DIR
        fi
        if [ -z $LDIR ]; then
            # Try CM target first
            adb pull /system/$DEST $2/$DEST
            # if file does not exist try OEM target
            if [ "$?" != "0" ]; then
                adb pull /system/$FILE $2/$DEST
            fi
        else
            # Try CM target first
            cp $LDIR/system/$DEST $2/$DEST
            # if file does not exist try OEM target
            if [ "$?" != "0" ]; then
                cp $LDIR/system/$FILE $2/$DEST
            fi
        fi
    done
}


DEVBASE=../../../vendor/$VENDOR/$DEVICE/proprietary
rm -rf $DEVBASE/*

extract proprietary-files-qc.txt $DEVBASE
extract proprietary-files.txt $DEVBASE

../../../device/$VENDOR/$DEVICE/setup-makefiles.sh
