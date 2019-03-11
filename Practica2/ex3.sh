#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

find $1 -type f  -exec ls -l {} \; | awk '{sum+=$5; fit+=1} END {print fit " fitxers \n"  sum " bytes"}'


exit 0

