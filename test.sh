#!/bin/bash

echo hola
echo -n hola
echo "hola"
echo 'hola'
echo -n "hola"
echo -n 'hola'
echo "hola que tal   " me llamo 'jaime  '
echo -n "hola que tal      " yo me llamo '   paris'
echo "<-  final"

pwd

cd ../..

ls

env
export PRUEBA=hola
echo "\n\n"
env
export HOLA=prueba
echo "\n\n"
env
unset PRUEBA
echo "\n\n"
env
unset HOLA
echo "\n\n"
env

exit
