#!/bin/bash

echo hola
echo -n hola
echo "hola"
echo 'hola'
echo -n "hola"
echo -n 'hola'
echo "hola que tal   " me llamo 'jaime  '
echo -n "hola que tal      " yo me llamo '   paris'
echo "<-  final
"

pwd

cd ../..

ls

echo "

"

env
export PRUEBA=hola
echo "
"
env
export HOLA=prueba
echo "

"
env
unset PRUEBA
echo "

"
env
unset HOLA
echo "

"
env

exit
