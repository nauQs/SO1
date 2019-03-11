#!/bin/bash

if [ $# -ne 3 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

find $1 -type f -name "*.$2" -exec ls {} \; -exec sh -c 'echo cadena $2: grep -c $3 {} vegades' \; 


exit 0

