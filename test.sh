echo "TEST FORK EXECVE============================="
echo
echo foo
/bin/ls
echo
/bin/ls -laF
echo
/bin/ls -l -a -F
echo
echo "TEST BUILTINS==============================="
echo
echo It works
echo
cd /bin
/bin/pwd
cd -
pwd
cd
/bin/pwd
cd -
pwd
cd ~
/bin/pwd
cd -
pwd
cd ..
/bin/pwd
cd -
echo
echo "TEST ENVIRONMENT==============================="
echo
env
echo
export FOO=bar
env
echo
/usr/bin/env
echo
unset FOO
env
echo
unset FOO
env
echo
/usr/bin/env
echo
echo "TEST PATH RIGHTS==============================="
echo
mkdir /tmp/bin
export PATH=$PATH:/tmp/bin
touch /tmp/bin/test_exec_rights
chmod 644 /tmp/bin/test_exec_rights
test_exec_rights
echo
echo "TEST SEMICOLON==============================="
echo
;
echo TOP;ls;echo MIDDLE;ls;echo BOTTOM
echo
echo "TEST PATH==============================="
echo
unset PATH
export "PATH=/bin:/usr/bin"
ls
unset PATH
ls
/bin/ls
echo
exit
