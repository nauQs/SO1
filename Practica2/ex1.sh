#!/bin/bash

if [ $# -ne 2 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

find $1 -type f -name "*.$2" -exec ls -l {} \; | sort -nk5 | head -10


exit 0

