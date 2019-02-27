#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

dir=$1

fitxers=$(ls $dir)

for directori in $fitxers
do
   adr=$dir/$fitxer
   if [ -d $adr ]
   then 
      
      
   fi
done
exit 0

