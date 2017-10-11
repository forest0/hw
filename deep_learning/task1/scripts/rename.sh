#! /usr/bin/env bash

sourceDir='../pictures/putin'
destinationDir='../pictures/origin'
prefix='putin'
suffix='.jpg'

cnt=0

toString() {
    if [ $1 -lt 10 ]; then
        echo "000$1"
    else
        echo "00$1"
    fi
}

for item in `ls $sourceDir`
do
    numString=`toString $cnt`
    mv $sourceDir/$item $destinationDir/$prefix$numString$suffix
    ((cnt++))
done

