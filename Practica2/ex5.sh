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

niub=$(grep $1 alumnes.csv | awk -F ";" '{print $1}')
prac=$(grep $1 alumnes.csv | awk -F ";" '{print $2}')
prob=$(grep $1 alumnes.csv | awk -F ";" '{print $3}')

line=($niub";"$prac";"$prob)

if [ $2 != "problemes" ]
then
newline=($niub";"$3";"$prob)
echo Grup de practiques modificat
else
newline=($niub";"$prac";"$3)
echo Grup de problemes modificat
fi
sed -i'' -e "s/$line/$newline/g" alumnes.csv


exit 0

