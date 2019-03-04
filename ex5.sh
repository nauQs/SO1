#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

directoriactual=$(pwd)
dir=$directoriactual/$1


echo $dir
if [ ! -d $dir ]
then
	echo sortim
	exit 2
fi

for subdir in $(ls $dir)
do
   adr=$dir/$subdir
   if [ -f $adr ]
   then
	echo $adr
   else	
	echo crida recursiva $adr
	./$0 $adr
   fi
done
exit 0

