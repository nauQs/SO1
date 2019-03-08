#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi



echo $1
if [ ! -d $1 ]
then
	echo sortim
	exit 2
fi

for subdir in $(ls $1)
do
   adr=$1/$subdir
   if [ -f $adr ]
   then
	echo $adr
   else	
	./$0 $adr
   fi
done
exit 0

