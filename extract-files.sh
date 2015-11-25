#!/bin/bash

#set -e
export DEVICE=bacon
export VENDOR=oneplus

if [ $# -eq 0 ]; then
  SRC=adb
else
  if [ $# -eq 1 ]; then
    SRC=$1
  else
    echo "$0: bad number of arguments"
    echo ""
    echo "usage: $0 [PATH_TO_EXPANDED_ROM]"
    echo ""
    echo "If PATH_TO_EXPANDED_ROM is not specified, blobs will be extracted from"
    echo "the device using adb pull."
    exit 1
  fi
fi

function extract() {
    for FILE in `egrep -v '(^#|^$)' $1`; do
      OLDIFS=$IFS IFS=":" PARSING_ARRAY=($FILE) IFS=$OLDIFS
      FILE=`echo ${PARSING_ARRAY[0]} | sed -e "s/^-//g"`
      DEST=${PARSING_ARRAY[1]}
      if [ -z $DEST ]
      then
        DEST=$FILE
      fi
      DIR=`dirname $DEST`
      if [ ! -d $BASE/$DIR ]; then
        mkdir -p $BASE/$DIR
      fi
      # Try CM target first
      if [ "$SRC" = "adb" ]; then
        adb pull /system/$DEST $BASE/$DEST
        # if file does not exist try OEM target
        if [ "$?" != "0" ]; then
            adb pull /system/$FILE $BASE/$DEST
        fi
      else
        if [ -z $SRC/system/$DEST ]; then
            echo ":: $DEST"
            cp $SRC/system/$DEST $BASE/$DEST
        else
            echo ":: $FILE"
            cp $SRC/system/$FILE $BASE/$DEST
        fi
      fi
    done
}

BASE=../../../vendor/$VENDOR/$DEVICE/proprietary
rm -rf $BASE/*

extract ../../$VENDOR/$DEVICE/proprietary-files-qc.txt $BASE
extract ../../$VENDOR/$DEVICE/proprietary-files.txt $BASE

./setup-makefiles.sh
