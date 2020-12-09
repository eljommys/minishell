#!/bin/bash
/bin/echo -e "\e[1;31m======================>Test PATH absoluto<======================\e[0m"
/bin/echo
echo -e "\e[1;33m/bin/ls\e[0m"
/bin/ls
/bin/echo
echo -e "\e[1;33m/bin/ls -la\e[0m"
/bin/ls -la
/bin/echo
echo -e "\e[1;33m/bin/ls -l -a\e[0m"
/bin/ls -l -a
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [echo]<======================|\e[0m"
/bin/echo
echo It works!
/bin/echo -e "\e[1;32mIt works!\e[0m"
echo -n "Bienvenidos a 42 Madrid "
echo sin salto de linea
/bin/echo -e "\e[1;32mBienvenidos a 42 Madrid sin salto de linea\e[0m"
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [exit]<======================|\e[0m"
/bin/echo
echo -e "\e[1;34m\"exit\" y \"exit abc\" deben probarase fuera del test\e[0m"
/bin/echo
echo -e "\e[1;33mexit 127 abc\e[0m"
exit 127 abc
/bin/echo -e "\e[1;32m./test.sh: line xx: exit: too many arguments\e[0m"
/bin/echo
echo -e "\e[1;31m|======================>Test Valor de retorno de un proceso[\$?]<======================|\e[0m"
/bin/echo
echo -e "\e[1;33m/bin/ls -la\e[0m"
/bin/ls -la
echo -e "\e[1;33m$?: command not found\e[0m"
/bin/echo -e "\e[1;32m0: command not found\e[0m"
/bin/echo
/bin/ls archivonulo
echo -e "\e[1;33m$?: command not found\e[0m"
/bin/echo "/bin/ls: cannot access 'archivonulo': No such file or directory"
/bin/echo -e "\e[1;32m2: command not found\e[0m"
/bin/echo
echo -e "\e[1;34mPunto y coma(;) debe probarase fuera del test con el siguiente resultado\e[0m"
echo -e "\e[1;33m;\e[0m"
/bin/echo -e "\e[1;32mbash: syntax error near unexpected token \`;'\e[0m"
echo -e "\e[1;33m\$?\e[0m"
/bin/echo -e "\e[1;32m2: command not found\e[0m"
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test Punto y coma [;]<======================|\e[0m"
/bin/echo
echo -e "\e[1;33mecho TOP;ls;echo MIDDLE;ls;echo BOTTOM\e[0m"
/bin/echo TOP;/bin/ls;/bin/echo MIDDLE;/bin/ls;/bin/echo BOTTOM
/bin/echo
echo -e "\e[1;33mecho -n TOP ; pwd ; echo -n MIDDLE; pwd ; echo BOTTOM\e[0m"
/bin/echo -n "TOP "; /bin/pwd ; /bin/echo -n "MIDDLE " ; /bin/pwd ; /bin/echo BOTTOM
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test Comillas<======================|\e[0m"
/bin/echo
echo -e "\e[1;33mecho -n \"Vamos a probar las comillas con ; y espacios en el interior\"\e[0m"
echo -n "Vamos a probar las comillas con ; y espacios en el interior"
echo -e "\e[1;33mSin salto de linea\e[0m"
/bin/echo -e "\e[1;32mVamos a probar las comillas con ; y espacios en el interior\e[0m"
/bin/echo
echo -e "\e[1;33mecho Tambien vamos a probar la barra invertida [\\\\\]\e[0m"
echo Tambien vamos a probar la barra invertida [\\]
/bin/echo -e "\e[1;32mTambien vamos a probar la barra invertida [\]\e[0m"
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [env]<======================|\e[0m"
/bin/echo
echo -e "\e[1;33menv\e[0m"
env
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [export]<======================|\e[0m"
/bin/echo
echo -e "\e[1;33mexport a b c ZETA=zeta @ USER=jserrano 123ABC=error\e[0m"
export a b c ZETA=zeta @ USER=jserrano 123ABC=error ZAFIRO=zafiro
/bin/echo -e "\e[1;32m./test.sh: line xx: export: \`@': not a valid identifier\e[0m"
/bin/echo -e "\e[1;32m./test.sh: line xx: export: \`123ABC=error': not a valid identifier\e[0m"
echo -e "\e[1;33menv\e[0m"
env
echo -e "\e[1;33mexport\e[0m"
export
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [unset]<======================|\e[0m"
/bin/echo
echo -e "\e[1;33mexport USER=parmarti\e[0m"
export USER=parmarti
echo -e "\e[1;33munset ZETA ZAFIRO\e[0m"
unset ZETA ZAFIRO
echo -e "\e[1;33menv\e[0m"
env
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test Variables de entorno<======================|\e[0m"
/bin/echo
echo -e "\e[1;33mecho \$HOME '\$HOME' \"\$HOME\" \\\$HOME \${HOME} \"\\\$HOME\"\e[0m"
echo $HOME '$HOME' "$HOME" \$HOME ${HOME} "\$HOME"
/bin/echo -e "\e[1;32m/home/parmarti \$HOME /home/parmarti \$HOME /home/parmarti \$HOME\e[0m"
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [cd]<======================|\e[0m"
/bin/echo
/bin/echo -e "\e[1;33mcd /bin\e[0m"
cd /bin
/bin/ls
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -
/bin/ls
/bin/echo -e "\e[1;33mcd --\e[0m"
cd --
/bin/ls
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -
/bin/ls
/bin/echo -e "\e[1;33mcd ~\e[0m"
cd ~
/bin/ls
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -
/bin/ls
/bin/echo -e "\e[1;33mcd\e[0m"
cd
/bin/ls
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -
/bin/ls
/bin/echo -e "\e[1;33mcd .\e[0m"
cd .
/bin/ls
/bin/echo -e "\e[1;33mcd ..\e[0m"
cd ..
/bin/ls
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -
/bin/echo
/bin/echo -e "\e[1;31m|======================>Test [pwd]<======================|\e[0m"
/bin/echo
/bin/echo -e "\e[1;33mpwd\e[0m"
pwd
/bin/echo -e "\e[1;33mpwd abc\e[0m"
pwd abc
/bin/echo -e "\e[1;33mcd /bin\e[0m"
cd /bin
/bin/echo -e "\e[1;33mpwd\e[0m"
pwd
/bin/echo -e "\e[1;33mcd -\e[0m"
cd -




