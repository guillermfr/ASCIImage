#!bin/bash

clear

txtImgDir=data/textFiles
frameDelay=0.05

for img in $txtImgDir/*.txt; do
    clear
    cat $img
    sleep $frameDelay
done

clear