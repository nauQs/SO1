#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

a=$1
echo $1

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
  adr=$a$i
  echo $adr
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

