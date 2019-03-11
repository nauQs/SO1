#!/bin/bash

if [ $# -ne 3 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

if [ $2 != "practiques" ]
then
    if [ $2 != "problemes" ]
    then
        echo "Entra practiques o problemes"
        exit 2
    fi
fi

awk -F ";" -v niub="$1" -v canvi="$2" -v grup="$3" '{if ($1 == niub) if(canvi == "problemes") sub(/F/,"CANVIGRUP",$3) ; if ($1 == niub) if(canvi == "practiques") print $2'} alumnes.csv

exit 0

