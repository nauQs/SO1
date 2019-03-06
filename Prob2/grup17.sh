#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi
if [ ! -d $1 ] 
   then
      echo "No heu entrat un directori"
      exit 2
fi

echo -en $(find $1 -type d -exec echo "\ndirectori: {} nFiles: " \; -exec sh -c 'find {} -type f -maxdepth 1 | wc -l' \;)
echo -en "\n"

exit 0

