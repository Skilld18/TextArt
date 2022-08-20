#!/bin/bash
page=`pdfinfo $1 | grep -- ^Pages | grep -oE [0-9]+`
for ((i=1; i<=$page; i++))
do
    pdftoppm "$@" -f $i -l $i .prefix
    draw .prefix*$i* 
    read -p ""
done
