echo -e "\e[1;31mTEST MINISHELL\e[0m"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell "echo 00\\\\\\'pp ; echo 00\\\\\\\\\\'pp"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo 00\\\\\\'pp ; echo 00\\\\\\\\\\'pp"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell "echo ';;'"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo ';;'"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo '";;;"'
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo ';;;'"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell "echo 00\\\\\\\\'pp' ; echo “./hello”. ; echo ./hello ; echo ello"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo 00\\\\\\\\'pp' ; echo “./hello”. ; echo ./hello ; echo ello"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell 'echo /$"123$USER"'
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo /$"123$USER"'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo | cd .. | pwd
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo | cd .. | pwd'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $1 234
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo $1 234'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $POEP hallo
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo $POEP hallo'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo "hallo$"
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo "hallo$"'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo "\poep"
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo "\poep"'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $/
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo $/"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $2$4
echo -e "\e[1;32mBASH\e[0m"
bash -c 'echo $2$4'
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo $"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo "123\\\"456"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo 123\\\"456"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $?
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo $?"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo \\\"test\\\"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo \\\"test\\\""
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $TEST
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo $TEST"
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell echo $PWD ; echo $HOME ; echo "$PWD" ; echo '$PWD' ; echo "$HOME"
echo -e "\e[1;32mBASH\e[0m"
bash -c "echo $PWD ; echo $HOME ; echo "$PWD" ; echo \$\PWD ; echo "$HOME""
echo -e "\e[1;34mMINISHELL\e[0m"
./minishell export | grep -e "PWD="
echo -e "\e[1;32mBASH\e[0m"
bash -c "export | grep -e "PWD=""
