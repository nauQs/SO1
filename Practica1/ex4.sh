#!/bin/bash

if [ $# -ne 2 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

ls -l $directoriactual/$1 > "temp.txt"
col5=($(awk '{print $5}' "temp.txt"))
col9=($(awk '{print $9}' "temp.txt"))
len=${#col5[*]}
i=0
while [ $i -lt $len ]
do
  if [ -f $1/${col9[$i]} ]
  then
 	 if [ ${col5[$i]} -gt $2 ]
 	 then
		echo ${col9[$i]}: ${col5[$i]} Bytes
  	 fi
  fi
  (( i++ ))
done
exit 0
	


exit 0

