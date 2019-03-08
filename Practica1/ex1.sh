#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

directori=$1

if [ ! -d $directori ] 
   then
      echo "No heu entrat un directori"
      exit 2
fi

fit=0
dir=0
paraules=$(ls $directori)
for i in $paraules 
do
  adr=$1/$i
  if [ -d $adr ] 
  then
        dir=$(($dir+1))
  else
        fit=$(($fit+1))
  fi
done

echo "Fitxers: $fit"
echo "Directoris $dir"
exit 0

