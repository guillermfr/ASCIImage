#!bin/bash

clear

txtImgDir=data/textFiles
frameDelay=0.045

for img in $txtImgDir/*.txt; do
    tput cup 0 0
    cat $img
    sleep $frameDelay
done

clear