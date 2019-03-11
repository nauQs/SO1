#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

ps aux | awk -v user="$1" '{if ($1 == user) vsz+=$5; rss+=$6} END {print "VSZ: " vsz " bytes \nRSS: " rss " bytes"}'

exit 0

