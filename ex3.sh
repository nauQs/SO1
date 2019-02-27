#!/bin/bash

if [ $# -ne 2 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

dir=$1

fitxers=$(ls $dir)

for fitxer in $fitxers
do
   adr=$dir/$fitxer
   if [ -f $adr ]
   then 
      count=0
      paraules=$(cat $adr)
      for paraula in $paraules
      do
	string=$2
	longitud=${#string}
	subparaula=${paraula:0:$longitud}
	if [ $subparaula = $string ]
	then
		count=$(($count+1))
		echo $fitxer: $paraula
	fi
      done
      echo Total $fitxer: $count
   fi
done
exit 0

