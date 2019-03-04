#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

str=$1
len=${#str}
i=0
while [ $i -lt $len ]
do
  if [ ${str:i:1} != ${str:len-i-1:1} ]
  then
	echo "No és un palíndrom"
	exit 0
  fi
  (( i++ ))
done
echo "És un palíndrom"
exit 0
	


exit 0

