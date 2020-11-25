#!/bin/bash

echo hola
echo -n hola
echo "hola"
echo 'hola'
echo -n "hola"
echo -n 'hola'
echo "hola que tal   " me llamo 'jaime  '
echo -n "hola que tal      " yo me llamo '   paris'
echo "<-  final "
echo " "

pwd

cd ../..

pwd

ls

echo " "
echo " "

env
export PRUEBA=hola
echo " "
echo " "
env
export HOLA=prueba
echo " "
echo " "
env
unset PRUEBA
echo " "
echo " "
env
unset HOLA
echo " "
echo " "
env

exit
