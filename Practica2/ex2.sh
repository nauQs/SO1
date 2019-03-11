#!/bin/bash

if [ $# -ne 3 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

for fitxer in $(find $1 -type f -name "*.$2" -exec ls {} \;)
do
	echo $fitxer
	echo  la cadena $3 apareix $(grep -o $3 $fitxer | wc -l) vegades
done

exit 0

