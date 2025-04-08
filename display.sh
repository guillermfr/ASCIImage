#!bin/bash

clear

txtImgDir=data/textFiles
frameDelay=0.0333

for img in $txtImgDir/*.txt; do
    tput cup 0 0
    cat $img
    sleep $frameDelay
done

clear