#! /usr/bin/env bash

sourceDir='../pictures/origin'
destinationDir='../pictures'
sizeArray=(28 32 224 227)


for item in `ls $sourceDir`
do
    for size in ${sizeArray[@]}
    do
        convert -resize ${size}x${size} $sourceDir/$item $destinationDir/$size/$item
    done
done
