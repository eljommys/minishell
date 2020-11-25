#! /bin/sh
echo hola
echo -n hola
echo "hola"
echo 'hola'
echo -n "hola"
echo -n 'hola'
echo "hola que tal   " me llamo 'jaime  '
echo -n "hola que tal      " yo me llamo '   paris'
echo "$HOME" '$HOME' $HOME me llamo paris $HOME
echo "<-  final"
pwd
cd ../..
ls
env
export PRUEBA=hola
env
export HOLA=prueba
env
unset PRUEBA
env
unset HOLA
env
exit
