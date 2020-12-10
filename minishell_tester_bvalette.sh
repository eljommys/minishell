#! /bin/bash --posix

print_separator(){
	i=1
	max=$(tput cols)
	while [ $i -le $max ]
	do
		echo -n $1
		((i+=1))
	done
	echo
}

print_diff_full () {
	colordiff $EXTRA_FLAGS -y /tmp/ba.log /tmp/minishell.log
}

print_diff_fail () {
	echo -e "\e[31m \e[1m[$TEST_NB][  ] \e[0m\t\t["$TEST"]"
	echo -e "🟨 [Diff]\n"
	diff $EXTRA_FLAGS /tmp/ba.log /tmp/minishell.log | cat -e
	echo -e "\n🟡 [Color Diff]\n"
	print_diff_full
}

print_diff_simple (){
	# SORT_RESULT allow to sort lines in order to avoid race conditions false positive
	# not set by default
	if [[ ! -z $SORT_RESULT ]]
	then
		echo -e "\n \e[36m  ℹ️  This test sort the output in order to avoid race condition :\e[0m"
		cat /tmp/ba.log | sort > /tmp/ba_sorted.log ; cat /tmp/ba_sorted.log > /tmp/ba.log
		cat /tmp/minishell.log | sort > /tmp/ms_sorted.log ; cat /tmp/ms_sorted.log > /tmp/minishell.log
	fi
	diff $EXTRA_FLAGS -s /tmp/ba.log /tmp/minishell.log &>/dev/null
	if [[ $? -ne 0 ]]
	then
		print_separator '▁'
		print_diff_fail
		((TEST_FAILED_NB+=1))
		echo "🔴 [$TEST_NB] $TEST" >> /tmp/test_ko
		echo -e "\e[34m $(diff $EXTRA_FLAGS -s /tmp/ba.log /tmp/minishell.log)\e[0m" >> /tmp/test_ko
		echo -e "\t ⏫  ❌ [$TEST_NB][$TEST]" >> /tmp/bash_sumup
		echo -e "\t ⏫  ❌ [$TEST_NB][$TEST]" >> /tmp/minishell_sumup
		print_separator '▔'
	else
		echo -e "\e[32m \e[1m✅  [$TEST_NB][OK] \e[0m\t\t["$TEST"]"
	fi
}

clean_log () {
## bricolage destiné a retirer les faux negatifs du testeur
	sed -i 's/NO_LINE_ED~$>//g' /tmp/minishell.log
	sed -i 's/Minishell: /bash: /g' /tmp/minishell.log
	sed -i 's/minishell: /bash: /g' /tmp/minishell.log
	# sed -i 's/bash-4.4$ exit//' /tmp/ba.log

	#to remove once fixed
	cat /tmp/ba.log | grep -v "\_\=\|bash-4.4\\$ " > /tmp/ba_tmp.log ; cat /tmp/ba_tmp.log > /tmp/ba.log

	#to remove once fixed
	# cat /tmp/minishell.log | grep -v "exit$" > /tmp/minishell_tmp.log ; cat /tmp/minishell_tmp.log > /tmp/minishell.log
}

test () {
	((TEST_NB+=1))
	export TEST=$1

	echo "$TEST" | env -i $EXTRA_ENV $(which bash) --posix -i &>/tmp/ba.log
	echo "EXITED WITH : $?" >> /tmp/ba.log

	REDIRECTION='>\|<\|>>'
	if grep -q "$REDIRECTION" <<< "$TEST"; then
		sleep 0.1 ;
	fi

	echo "$TEST" | env -i $EXTRA_ENV ./minishell &>/tmp/minishell.log
	echo "EXITED WITH : $?" >> /tmp/minishell.log

	# pour ENV
	# echo "$TEST" | $EXTRA_ENV bash --posix -i &>/tmp/ba.log
	# echo "$TEST" | $EXTRA_ENV ./Minishell &>/tmp/minishell.log
	#

	echo -e "\n\n\t 🟡 [$TEST_NB][$TEST] 🟡 " >> /tmp/minishell_sumup
	cat /tmp/minishell.log >> /tmp/minishell_sumup

	echo -e "\n\n\t 🟡 [$TEST_NB][$TEST] 🟡 " >> /tmp/bash_sumup
	cat /tmp/ba.log >> /tmp/bash_sumup
	# echo "$TEST" | env -i $EXTRA_ENV ./Minishell &>/tmp/minishell.log
	# echo "RETURNED : $?" >> /tmp/minishell.log
	# echo "$TEST" | env -i $EXTRA_ENV bash --posix -i &>/tmp/ba.log
	# echo "RETURNED : $?" >> /tmp/ba.log


	clean_log
	print_diff_simple
}

test_random() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"


	test "hfdjskhdfkjhfsd"
	test "ls fdsfsdfhfsd"
	test "echo aaaaa bbbb cccccc dddddd > /tmp/a ; cat -e /tmp/a"
	test "echo terminal is [\$TERM]"
	test "echo terminal is [\$TERM4"
	test " toto+=42; echo \$toto ; toto+=.; echo \$toto ; toto+=-; echo \$toto ; toto+='' ; echo \$toto ; toto+=42; echo \$toto ; toto+=42; echo \$toto ; toto+=42; echo \$toto ; toto+=42; echo \$toto"
	test "echo > /tmp/test"
	test "cat -e /tmp/test"
	test "echo -n > /tmp/test"
	test "cat -e /tmp/test"
	test "echo \$?"
	test "ls hdfjkdsf ; echo \$?"
	test "ls hdfjkdsf ; echo \$?"
	test "export TEST; export | grep TEST"
	test "export TEST=1; export | grep TEST"
	test "export VAR_VALID=1"
	test "export BROK;EN_VAR=1; export | grep EN_VAR"
	test "export TEST+=23; export | grep TEST"
	test "export TEST1 TEST2=456 TEST4 TEST5 TEST3=78"
	test " export TEST1=123; export TEST1 TEST2=456 TEST4 TEST5 TEST3=789; echo \$TEST\$TEST2\$TEST3 > /tmp/test1 > /tmp/test2 > /tmp/test3; cat /tmp/test1; cat /tmp/test2; cat /tmp/test3 "
	test "cd .././../.././../bin/ls"
	test "unset \$HOME; cd"
	test "touch /tmp/file ; /tmp/file"
	test "4ABC=toto"
}

test_failed() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "	\"e\"'c'ho 'b'\"o\"nj\"o\"'u'r\";\"	"
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo '\$CHARS' ; echo \$CHARS ; echo \$PWD\$HOMe\"\$VAR_NONEXISTANT01\$PWD\" \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT02\"'\$EMPTY\$\"PWD' \$CHARS\"\$CHARS\"'\$PWD\"\$PWD\"'\$EMPTY\$NOTEMPTY |wc"
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo '\$CHARS' ; echo \$CHARS ; echo \$PWD\$HOMe\"\$VAR_NONEXISTANT01\$PWD\" \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT02\"'\$EMPTY\$\"PWD' \$CHARS\"\$CHARS\"'\$PWD\"\$PWD\"'\$EMPTY\$NOTEMPTY "
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo '\$CHARS' ; echo \$CHARS ; echo \$PWD\$VAR_NONEXISTANT01\"\$VAR_NONEXISTANT02\$PWD\" \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\"'\$EMPTY\$\"PWD' \$CHARS\"\$CHARS\"'\$PWD\"\$PWD\"'\$EMPTY\$NOTEMPTY | wc"
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo '\$CHARS' ; echo \$CHARS ; echo \$PWD\$VAR_NONEXISTANT01\"\$VAR_NONEXISTANT02\$PWD\" \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\"'\$EMPTY\$\"PWD' \$CHARS\"\$CHARS\"'\$PWD\"\$PWD\"'\$EMPTY\$NOTEMPTY ;"
	test " echo \"\$HOME\" ; echo \$HOME ; echo \"\$\"HOME ; echo \$\"\"HOME ; echo \"\"\$HOME ; echo \$\"HOME\" ; echo \$\"HO\"\"ME\" ; echo \"\$HO\"\"ME\" ; echo \"\$HO\"ME ; echo \$\"HOME\" "
	# test " mkdir -p test1/test2/test3 ; cd test1/test2/test3 ; rm -rf ../../../test1 ; cd .. ; pwd ; cd .. ; pwd ; cd .. ; pwd "
	##aucune importance
	test "export 4ABC=toto"
	#test "toto/tata=1"
	##pb Brian
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo \"\$VAR_NONEXISTANT02\$PWD\" \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\""
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo \$PWD \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\""
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo \$PWD \$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\""
	test " export EMPTY ; export NOTEMPTY= ; export CHARS=AAA ; echo \$PWD\$NOTEMPTY\$EMPTY'' \$\"VAR_NONEXISTANT03\""
}

test_bonus () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "\"\""
	test "\'\'"
	test "echo a && echo b ; echo \$?"
	test "echo a || echo b ; echo \$?"
	test "false || echo b ; echo \$?"
	test "false && echo b ; echo \$?"
	test "echo a || false ; echo \$?"
	test "echo a && false ; echo \$?"
}

test_correction_exec () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "/bin/ls"
	test "/bin/ip"
	test "/bin/aaaaaaaaaaaa"
	test "./non_existing_file______pouette"
	test "./fail_bin/segfault"
	test "non_existing_command______pouette"
	test "./Makefile ; echo \$?"
	test "/dev ; echo \$?"
	test "../../../ls ; echo \$?"
	test "\"\" ; echo \$?"
	test ""
	test " "
	test ">/tmp/000 | >/tmp/0001 ; echo \$?"
	test "ls aaaaaa >/tmp/000 | >/tmp/0001 ; echo \$?"
	test ">/tmp/000 | ls aaaaaaaa >/tmp/0001 ; echo \$?"
	test ">/tmp/000 | >/tmp/0001 | >/tmp/000 | >/tmp/0001 | >/tmp/000 | >/tmp/0001; echo \$?"

	tmp_extra_env=$EXTRA_ENV
	EXTRA_ENV='PATH=":"'
	test "echo \$PATH ; ls"
	EXTRA_ENV='PATH=": "'
	test "echo \$PATH ; ls"
	EXTRA_ENV='PATH=" :"'
	test "echo \$PATH ; ls"
	EXTRA_ENV='PATH=" : "'
	test "echo \$PATH ; ls"
	EXTRA_ENV='PATH="::::"'
	test "echo \$PATH ; ls"
	EXTRA_ENV='PATH=": : : : : : : :"'
	test "echo \$PATH ; ls"
	unset EXTRA_ENV
	EXTRA_ENV=$tmp_extra_env

 }

test_correction_arg () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "/bin/ls -l"
	test "/bin/ls aaaaaaaaaaa"
	test "/bin/ls -x Makefile"
	test "/bin/ls - Makefile"
	test "/bin/ls -- Makefile"
}


test_correction_echo () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "echo echo echo echo"
	test "echo ; echo ; echo ; echo"
	test "echo coucou a b c d e f g"
	test "echo - test"
	test "echo -nnnnnnx hello"
	test "echo -----nnnnnnn hello"
	test "echo - hello"
	test "echo - nnnnnnn hello"
	test "echo - n hello"
	test "echo -n"
	test "echo -n -n -n -n"
	test "echo -nnnn"

	#test "echo \$1cat=42"
	test "echo a \$NOVAR b| wc"
	test "echo a \\n b| wc"
	test "echo -n a \\n b| wc"
	test "echo aaaaaaaaa > /tmp/a ; cat -e /tmp/a ; echo "
	test "echo -n aaaaaaaaa > /tmp/a ; cat -e /tmp/a ; echo "
	test "echo -n -n -n  aaaaaaaaa > /tmp/a ; cat -e /tmp/a ; echo"
	test "echo -nnn  aaaaaaaaa > /tmp/a | cat -e /tmp/a ; echo"
	test "echo \$ ; echo \"\$\" ; echo '\$'"
    test "echo \$\"\" ; echo \"\$\"\"\" ; echo '\$'''"
    test "echo \$toto ; echo \"\$toto\" ; echo '\$toto'"
    test "echo \$toto\"\" ; echo \"\$toto\"\"\" ; echo '\$toto'''"
    test "toto= 42 ; echo \$toto ; echo \"\$toto\" ; echo '\$toto'"
    test "toto=42 ; echo \$toto\"\" ; echo \"\$toto\"\"\" ; echo '\$toto'''"

# Cannot be tested with this
	# extra flags to void tests to fail because of files redirection and new lines
	# EXTRA_FLAGS="--ignore-trailing-space"
	# EXTRA_FLAGS="--ignore-all-space"
		# test "echo -n test aaa"
		# test "echo -n -n -n -n -n -n test aaa"
		# test "echo -n -n -N -n -n -n test aaa"
		# test "echo n -n -n -n -n -x test aaa"
	# EXTRA_FLAGS=""
}


test_correction_exit () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "exit 5"
	test "exit abcdef"
	test "exit 2 2 2 2 2 2"
	test "exit dqdsqd 2 dsqdqs"
	test "exit 9223372036854775807"
	test "exit 9223372036854775808"
	test "exit 500"
	test "exit -500"
	test "ls ; exit"
	test "ls | exit"
}


test_correction_return () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "/bin/ip ; echo \$?"
	test "/bin/ipaaaaaaaaaa ; echo \$?"
	test "/bin/ls aaaaaaabbbbbbbb ; echo \$?"
	test "/bin/ls aaaaaaaaaaa ; echo \$?"
	test "/bin/ls -x Makefile ; echo \$?"
	test "/bin/ls - Makefile ; echo \$?"
	test "/bin/ls -- Makefile ; echo \$?"
}


test_correction_semicolons () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "echo a ; echo b"
	test "echo a; echo b"
	test "echo a ;echo b"
	test "echo a;echo b"
	test "echo a' ; 'echo b"
	test "echo a'; 'echo b"
	test "echo a' ;'echo b"
	test "echo a';'echo b"
	test "echo a ';' echo b"
}


test_correction_baskslashs () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "ls \\Makefile"
	test "ls \\\"Makefile\\\""
	test "ls \\\'Makefile\\\'"
}


test_correction_env () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "env | sort "
	test "export cat ; env | grep cat"
	test "cat=meow ; env  | sort ; export"
	test "export cat ; env  | sort ; export"
	test "export cat=42 ; env  | sort ; export"
	test "unset PWD ; cat=meow env; echo ; env | sort  ; export"
	test "unset PWD ; cat=meow env; echo ; env | sort ; export"
	test "cat env | sort; env | sort ; export"
	test "cat=meow env | sort; env | sort  ; export"
	test "cat=meow env | sort; env | sort ; export"
	test "cat env | sort; env | sort ; export"
	test "toto=4242424242 echo \$toto"
	test "toto=4242424242 ; echo \$toto"
	test "toto=4242424242 echo \$toto | ls"
	test "toto=4242424242 ; ls \$toto"
	test "toto=42424242 ls \$toto"
	test "toto=42 | titi=21 ; env | sort ; echo \$toto \$titi"
	test "toto=42 | totot=21 ; env | sort ; echo \$toto"
	test "toto=42 echo \$toto | totot=21 echo \$toto ; env | sort ; echo \$toto"
	test "toto=42 echo \$toto ; env | sort ; echo \$toto"
	#test "export hello=hey ; echo \$? ; export -hola=touto ; echo \$? ; env -l ; echo \$? ; unset hola ; echo \$? ; unset hello ; echo \$? ; export toto+=hello ; echo \$? ; export _titi=tutu ; echo \$?"

}

test_correction_export_identifier () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "export  _cat  ; echo \$? ; export"
	test "export  %cat  ; echo \$? ; export"
	test "export  4cat  ; echo \$? ; export"
	test "export  ca_t  ; echo \$? ; export"
	test "export  ca%t  ; echo \$? ; export"
	test "export  ca4t  ; echo \$? ; export"

	test "export abcd.  ; echo \$? ; export"
	test "export abcd/  ; echo \$? ; export"
	test "export abcd]  ; echo \$? ; export"
	test "export abcd[  ; echo \$? ; export"
	test "export abcd;  ; echo \$? ; export"
	test "export abcd:  ; echo \$? ; export"
	test "export abcd,  ; echo \$? ; export"
	test "export abcd@  ; echo \$? ; export"
	test "export abcd%  ; echo \$? ; export"
	test "export abcd^  ; echo \$? ; export"
	test "export abcd!  ; echo \$? ; export"
	test "export abcd?  ; echo \$? ; export"
	test "export abcd+  ; echo \$? ; export"

	test "export .  ; echo \$? ; export"
	test "export /  ; echo \$? ; export"
	test "export ]  ; echo \$? ; export"
	test "export [  ; echo \$? ; export"
	test "export ;  ; echo \$? ; export"
	test "export :  ; echo \$? ; export"
	test "export ,  ; echo \$? ; export"
	test "export @  ; echo \$? ; export"
	test "export %  ; echo \$? ; export"
	test "export ^  ; echo \$? ; export"
	test "export !  ; echo \$? ; export"
	test "export ?  ; echo \$? ; export"
	test "export +  ; echo \$? ; export"

	test "export  _cat=42  ; echo \$? ; export"
	test "export  %cat=42  ; echo \$? ; export"
	test "export  4cat=42  ; echo \$? ; export"
	test "export  ca_t=42  ; echo \$? ; export"
	test "export  ca%t=42  ; echo \$? ; export"
	test "export  ca4t=42  ; echo \$? ; export"

	test "export abcd.=42  ; echo \$? ; export"
	test "export abcd/=42  ; echo \$? ; export"
	test "export abcd]=42  ; echo \$? ; export"
	test "export abcd[=42  ; echo \$? ; export"
	test "export abcd;=42  ; echo \$? ; export"
	test "export abcd:=42  ; echo \$? ; export"
	test "export abcd,=42  ; echo \$? ; export"
	test "export abcd@=42  ; echo \$? ; export"
	test "export abcd%=42  ; echo \$? ; export"
	test "export abcd^=42  ; echo \$? ; export"
	test "export abcd!=42  ; echo \$? ; export"
	test "export abcd?=42  ; echo \$? ; export"
	test "export abcd+=42  ; echo \$? ; export"
	test "export abcd+efg=42  ; echo \$? ; export"

	test "export .=42  ; echo \$? ; export"
	test "export /=42  ; echo \$? ; export"
	test "export ]=42  ; echo \$? ; export"
	test "export [=42  ; echo \$? ; export"
	test "export ;=42  ; echo \$? ; export"
	test "export :=42  ; echo \$? ; export"
	test "export ,=42  ; echo \$? ; export"
	test "export @=42  ; echo \$? ; export"
	test "export %=42  ; echo \$? ; export"
	test "export ^=42  ; echo \$? ; export"
	test "export !=42  ; echo \$? ; export"
	test "export ?=42  ; echo \$? ; export"
	test "export +=42  ; echo \$? ; export"
	test "export +a=42  ; echo \$? ; export"

	test "export a=====42  ; echo \$ ; export"
	test "export a====+42  ; echo \$ ; export"
	test "export a+====42  ; echo \$ ; export"
	test "export a+b====42  ; echo \$ ; export"
	test "export a+b+====42  ; echo \$ ; export"
	test "export 42 ; echo \$ ; export"
	test "export a=4+2 ; echo \$ ; export"
	test "export a=42+= ; echo \$ ; export"
	test "export a+=42= ; echo \$ ; export"
	test "export a+=42+= ; echo \$ ; export"

}

test_correction_export_identifier_mix_valid () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "export food=pizza  _cat  ; echo \$? ; export"
	test "export food=pizza  %cat  ; echo \$? ; export"
	test "export food=pizza  4cat  ; echo \$? ; export"
	test "export food=pizza  ca_t  ; echo \$? ; export"
	test "export food=pizza  ca%t  ; echo \$? ; export"
	test "export food=pizza  ca4t  ; echo \$? ; export"

	test "export food=pizza abcd.  ; echo \$? ; export"
	test "export food=pizza abcd/  ; echo \$? ; export"
	test "export food=pizza abcd]  ; echo \$? ; export"
	test "export food=pizza abcd[  ; echo \$? ; export"
	test "export food=pizza abcd;  ; echo \$? ; export"
	test "export food=pizza abcd:  ; echo \$? ; export"
	test "export food=pizza abcd,  ; echo \$? ; export"
	test "export food=pizza abcd@  ; echo \$? ; export"
	test "export food=pizza abcd%  ; echo \$? ; export"
	test "export food=pizza abcd^  ; echo \$? ; export"
	test "export food=pizza abcd!  ; echo \$? ; export"
	test "export food=pizza abcd?  ; echo \$? ; export"

	test "export food=pizza .  ; echo \$? ; export"
	test "export food=pizza /  ; echo \$? ; export"
	test "export food=pizza ]  ; echo \$? ; export"
	test "export food=pizza [  ; echo \$? ; export"
	test "export food=pizza ;  ; echo \$? ; export"
	test "export food=pizza :  ; echo \$? ; export"
	test "export food=pizza ,  ; echo \$? ; export"
	test "export food=pizza @  ; echo \$? ; export"
	test "export food=pizza %  ; echo \$? ; export"
	test "export food=pizza ^  ; echo \$? ; export"
	test "export food=pizza !  ; echo \$? ; export"
	test "export food=pizza ?  ; echo \$? ; export"

	test "export food=pizza  _cat=42  ; echo \$? ; export"
	test "export food=pizza  %cat=42  ; echo \$? ; export"
	test "export food=pizza  4cat=42  ; echo \$? ; export"
	test "export food=pizza  ca_t=42  ; echo \$? ; export"
	test "export food=pizza  ca%t=42  ; echo \$? ; export"
	test "export food=pizza  ca4t=42  ; echo \$? ; export"

	test "export food=pizza abcd.=42  ; echo \$? ; export"
	test "export food=pizza abcd/=42  ; echo \$? ; export"
	test "export food=pizza abcd]=42  ; echo \$? ; export"
	test "export food=pizza abcd[=42  ; echo \$? ; export"
	test "export food=pizza abcd;=42  ; echo \$? ; export"
	test "export food=pizza abcd:=42  ; echo \$? ; export"
	test "export food=pizza abcd,=42  ; echo \$? ; export"
	test "export food=pizza abcd@=42  ; echo \$? ; export"
	test "export food=pizza abcd%=42  ; echo \$? ; export"
	test "export food=pizza abcd^=42  ; echo \$? ; export"
	test "export food=pizza abcd!=42  ; echo \$? ; export"
	test "export food=pizza abcd?=42  ; echo \$? ; export"

	test "export food=pizza .=42  ; echo \$? ; export"
	test "export food=pizza /=42  ; echo \$? ; export"
	test "export food=pizza ]=42  ; echo \$? ; export"
	test "export food=pizza [=42  ; echo \$? ; export"
	test "export food=pizza ;=42  ; echo \$? ; export"
	test "export food=pizza :=42  ; echo \$? ; export"
	test "export food=pizza ,=42  ; echo \$? ; export"
	test "export food=pizza @=42  ; echo \$? ; export"
	test "export food=pizza %=42  ; echo \$? ; export"
	test "export food=pizza ^=42  ; echo \$? ; export"
	test "export food=pizza !=42  ; echo \$? ; export"
	test "export food=pizza ?=42  ; echo \$? ; export"

	test "export  _cat  food=pizza ; echo \$? ; export"
	test "export  %cat  food=pizza ; echo \$? ; export"
	test "export  4cat  food=pizza ; echo \$? ; export"
	test "export  ca_t  food=pizza ; echo \$? ; export"
	test "export  ca%t  food=pizza ; echo \$? ; export"
	test "export  ca4t  food=pizza ; echo \$? ; export"
	test "export abcd.  food=pizza ; echo \$? ; export"
	test "export abcd/  food=pizza ; echo \$? ; export"
	test "export abcd]  food=pizza ; echo \$? ; export"
	test "export abcd[  food=pizza ; echo \$? ; export"
	test "export abcd;  food=pizza ; echo \$? ; export"
	test "export abcd:  food=pizza ; echo \$? ; export"
	test "export abcd,  food=pizza ; echo \$? ; export"
	test "export abcd@  food=pizza ; echo \$? ; export"
	test "export abcd%  food=pizza ; echo \$? ; export"
	test "export abcd^  food=pizza ; echo \$? ; export"
	test "export abcd!  food=pizza ; echo \$? ; export"
	test "export abcd?  food=pizza ; echo \$? ; export"
	test "export .  food=pizza ; echo \$? ; export"
	test "export /  food=pizza ; echo \$? ; export"
	test "export ]  food=pizza ; echo \$? ; export"
	test "export [  food=pizza ; echo \$? ; export"
	test "export ;  food=pizza ; echo \$? ; export"
	test "export :  food=pizza ; echo \$? ; export"
	test "export ,  food=pizza ; echo \$? ; export"
	test "export @  food=pizza ; echo \$? ; export"
	test "export %  food=pizza ; echo \$? ; export"
	test "export ^  food=pizza ; echo \$? ; export"
	test "export !  food=pizza ; echo \$? ; export"
	test "export ?  food=pizza ; echo \$? ; export"
	test "export  _cat=42  food=pizza ; echo \$? ; export"
	test "export  %cat=42  food=pizza ; echo \$? ; export"
	test "export  4cat=42  food=pizza ; echo \$? ; export"
	test "export  ca_t=42  food=pizza ; echo \$? ; export"
	test "export  ca%t=42  food=pizza ; echo \$? ; export"
	test "export  ca4t=42  food=pizza ; echo \$? ; export"
	test "export abcd.=42  food=pizza ; echo \$? ; export"
	test "export abcd/=42  food=pizza ; echo \$? ; export"
	test "export abcd]=42  food=pizza ; echo \$? ; export"
	test "export abcd[=42  food=pizza ; echo \$? ; export"
	test "export abcd;=42  food=pizza ; echo \$? ; export"
	test "export abcd:=42  food=pizza ; echo \$? ; export"
	test "export abcd,=42  food=pizza ; echo \$? ; export"
	test "export abcd@=42  food=pizza ; echo \$? ; export"
	test "export abcd%=42  food=pizza ; echo \$? ; export"
	test "export abcd^=42  food=pizza ; echo \$? ; export"
	test "export abcd!=42  food=pizza ; echo \$? ; export"
	test "export abcd?=42  food=pizza ; echo \$? ; export"
	test "export .=42  food=pizza ; echo \$? ; export"
	test "export /=42  food=pizza ; echo \$? ; export"
	test "export ]=42  food=pizza ; echo \$? ; export"
	test "export [=42  food=pizza ; echo \$? ; export"
	test "export ;=42  food=pizza ; echo \$? ; export"
	test "export :=42  food=pizza ; echo \$? ; export"
	test "export ,=42  food=pizza ; echo \$? ; export"
	test "export @=42  food=pizza ; echo \$? ; export"
	test "export %=42  food=pizza ; echo \$? ; export"
	test "export ^=42  food=pizza ; echo \$? ; export"
	test "export !=42  food=pizza ; echo \$? ; export"
	test "export ?=42  food=pizza ; echo \$? ; export"

}

test_correction_export () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"


	test "export ; env | grep cat"
	test "cat=MEOOW ; export cat; export | grep cat ; env | grep cat"
	test "cat='' ; export cat ; export | grep cat ; env | grep cat"
	test "cat=\"\" ; export cat ; export | grep cat ; env | grep cat"
	test "cat='\"\"' ; export cat ; export | grep cat ; env | grep cat"
	test "cat=\"''\" ; export cat ; export | grep cat ; env | grep cat"
	test "cat='\"''\"' ; export cat ; export | grep cat ; env | grep cat"
	test "export toto='\\\"dd\\\"' ; env | grep toto"
	test "export toto=\"\"'\"dd\"'\"\" ; env | grep toto ; export | grep toto ; echo \$toto"
	test "export cat ; export | grep cat ; env | grep cat"
	test "export cat=''; export | grep cat ; env | grep cat"
	test "export cat='0'; export | grep cat ; env | grep cat"
	test "export cat=\"\" ; export | grep cat ; env | grep cat"
	test "export cat= export | grep cat ; env | grep cat"
	test "export cat= ; export | grep cat ; env | grep cat"

	test "cat=meow export food=pizza ; export ; export"
	#test "export -toto=1"
	test "export cat=woof -toto=1"
	#test "export -xxxxx cat=woof"
	#test "export -xxxxx cat=woof -yyyyyy"
	test "export cat=meow ; echo \$cat"
	test "food=pizza export; export"
	test "export cat=meow ; export cat=woof ; export"
	test "export cat=meow ; cat=woof ; export"
	test "cat=meow ; export cat=woof ; export"
	test "cat=meow ; export cat=woof export ; export"
	test "cat+=woof ; cat+=woof ; cat+=piaou ; export cat; export"
	test "export cat=woof ; cat+=woof ; cat+=piaou ; export"
	test "export cat+=woof ; cat+=woof ; cat+=piaou ; export"

	test "export ERR+EUR=1 ; export"
	test "export VAR-INVALID=1 ; export"
	test "export PATH=42 ; export"
	test "export ; export"
	test "cat=moew export | export"
	test "export cat=moew | export"
	test "cat=moew export"
	test "export cat=moew ; export"
	test "unset PATH ; export PATH ; export ; ls"
	test "toto=42 ; echo \$? ; export to%to; echo \$? ; export"
	test "toto=42 export to%to; echo \$? ; export"
	test "toto= 42 export toto+=hello ; echo \$toto ; echo \$? ; unset toto ; echo \$toto"

}

test_correction_unset_identifier () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "unset . ; echo \$?"
	test "unset / ; echo \$?"
	test "unset ] ; echo \$?"
	test "unset [ ; echo \$?"
	test "unset ; ; echo \$?"
	test "unset : ; echo \$?"
	test "unset , ; echo \$?"
	test "unset @ ; echo \$?"
	test "unset + ; echo \$?"
	test "unset % ; echo \$?"
	test "unset ^ ; echo \$?"
	test "unset ! ; echo \$?"
	test "unset ? ; echo \$?"

	test "unset cat=. ; echo \$?"
	test "unset cat=/ ; echo \$?"
	test "unset cat=] ; echo \$?"
	test "unset cat=[ ; echo \$?"
	test "unset cat=; ; echo \$?"
	test "unset cat=: ; echo \$?"
	test "unset cat=, ; echo \$?"
	test "unset cat=@ ; echo \$?"
	test "unset cat=+ ; echo \$?"
	test "unset cat=% ; echo \$?"
	test "unset cat=^ ; echo \$?"
	test "unset cat=! ; echo \$?"
	test "unset cat=? ; echo \$?"

	test "unset cat=\"\" ; echo \$?"
	test "unset cat='' ; echo \$?"
	test "unset cat=\"''\" ; echo \$?"
	test "unset cat='\"\"' ; echo \$?"

	test "unset abcd. ; echo \$?"
	test "unset abcd/ ; echo \$?"
	test "unset abcd] ; echo \$?"
	test "unset abcd[ ; echo \$?"
	test "unset abcd; ; echo \$?"
	test "unset abcd: ; echo \$?"
	test "unset abcd, ; echo \$?"
	test "unset abcd@ ; echo \$?"
	test "unset abcd+ ; echo \$?"
	test "unset abcd% ; echo \$?"
	test "unset abcd^ ; echo \$?"
	test "unset abcd! ; echo \$?"
	test "unset abcd? ; echo \$?"

	test "unset _cat ; echo \$?"
	test "unset %cat ; echo \$?"
	test "unset 4cat ; echo \$?"
	test "unset ca_t ; echo \$?"
	test "unset ca%t ; echo \$?"
	test "unset ca4t ; echo \$?"

	test "unset _cat=wwooff ; echo \$?"
	test "unset cat=_wwooff ; echo \$?"
	test "unset %cat=wwooff ; echo \$?"
	test "unset cat=%wwooff ; echo \$?"
	test "unset cat=wwooff ; echo \$?"
	test "unset cat=%wwooff ; echo \$?"
	test "unset 4cat=wwooff ; echo \$?"
	test "unset cat=4wwooff ; echo \$?"

	test "unset c+at=wwooff ; echo \$?"
	test "unset cat=w+wooff ; echo \$?"
	test "unset ca%t=wwooff ; echo \$?"
	test "unset cat=wwoo%ff ; echo \$?"
	test "unset ca_t=wwooff ; echo \$?"
	test "unset cat=wwo_off ; echo \$?"
	test "unset ca4t=wwooff ; echo \$?"
	test "unset cat=wwo4off ; echo \$?"
}

test_correction_unset_identifier_mix_valid () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "export food=pizza ; unset . food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset / food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ] food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset [ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ; food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset : food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset , food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset @ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset + food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset % food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ^ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ! food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ? food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=. food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=/ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=] food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=[ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=; food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=: food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=, food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=@ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=+ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=% food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=^ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=! food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=? food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd. food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd/ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd] food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd[ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd; food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd: food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd, food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd@ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd+ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd% food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd^ food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd! food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset abcd? food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset _cat food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset %cat food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset 4cat food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca_t food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca%t food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca4t food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset _cat=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=_wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset %cat=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=%wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=%wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset 4cat=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=4wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset c+at=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=w+wooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca%t=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=wwoo%ff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca_t=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=wwo_off food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset ca4t=wwooff food  ; echo \$? ; export| grep food"
	test "export food=pizza ; unset cat=wwo4off food  ; echo \$? ; export| grep food"
}

test_correction_unset () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "unset"
	test "unset hfdjskhdfkjhfsd ; env | sort"
	test "export cat ; unset cat ; echo \$? ; export"
	test "export cat=meow ; unset cat ; echo \$? ; export"
	test "export food=pizza cat=MEOOWW; export | grep 'food\|cat' ; unset food -xxxxxxx cat ; echo \$? ; export"
	test "export food=pizza cat=MEOOWW; export | grep 'food\|cat' ; unset food -xxxxxxx cat -yyyyyy ; echo \$? ; export"
	test "export food=pizza; export | grep food ; cat=MEOOOWWW unset food ; export"
	test "export food=pizza; export | grep food ; cat=MEOOOWWW unset food cat ; export"
	test "export food=pizza; export | grep food ; cat=MEOOOWWW unset cat ; export"
	test "export food=pizza; export | grep food ; cat=MEOOOWWW unset food | ls ; export"

	test "food=pizza; env | sort | grep food ; cat=MEOOOWWW unset food | ls ; env | sort"
	test "food=pizza; env | sort | grep food ; food=MEOOOWWW unset food | ls ; env | sort"
	test "food=pizza; env | sort | grep food ; cat=MEOOOWWW unset food ; env | sort"
	test "food=pizza; env | sort | grep food ; food=MEOOOWWW unset food ; env | sort"

	test "dog=MEOWWW unset a b c d e ; export ; env | sort"
	test "dog=MEOWWW unset dog ; export ; env | sort"
}

test_correction_exp () {
	print_separator '█'

	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"
	test "echo \$TERM"
	test "echo \$\"TERM\""
	test "echo \$\'TERM\'"
	test "export TOTO=42 ; echo \$TERM\$TOTO"
	test "echo \$TERMaaaaaaa"
	test "echo aaaaaaa\$TERM"
	test "echo -\$TERM"
	test "cmd=\"ls\" ; \$cmd"
}

test_correction_cd() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	tmp_extra_env=$EXTRA_ENV
	EXTRA_ENV+="HOME=$HOME OLDPWD=$OLDPWD PWD=$PWD"
	test "cd"

	test "cd"
	test "cd ../ ; /bin/ls"
	test "cd ../././../// ; /bin/ls"
	test "cd / ; /bin/ls"
	test "cd ./ ; /bin/ls"
	test "cd ./.. ; /bin/ls"
	test "cd ./sources ; /bin/ls"
	test "cd ./aaaaaaaaaa ; /bin/ls"
	test "cd /aaaaaaaaaa ; /bin/ls"
	test "cd aaaaaaa ; /bin/ls"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa ; cd /tmp/aaa ; /bin/ls"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa ; chmod 000 /tmp/aaa ; cd /tmp/aaa ; /bin/ls"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa ; cd /tmp/aaa ; rm -rf /tmp/aaa ; cd .. ; /bin/ls"
	test "cd /tmp ; cd - ; /bin/ls"
	test "cd Makefile"
	test "cd -x"
	test "cd /tmp ; cd - >file; ls -l /tmp/file ; rm -rf /tmp/file"
	unset EXTRA_ENV
	EXTRA_ENV=$tmp_extra_env
	test "cd"

}

test_correction_pwd() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	tmp_extra_env=$EXTRA_ENV
	EXTRA_ENV+="HOME=$HOME OLDPWD=$OLDPWD PWD=$PWD"
	test "pwd"

	test "pwd"
	test "pwd -X"
	test "pwd aaaaaaaaa"
	test "pwd ./aaaaaaaaa"
	test "cd ../ ; pwd"
	test "cd ../././../// ; pwd"
	test "cd / ; pwd"
	test "cd ./ ; pwd"
	test "cd ./ ; pwd"
	test "cd ./sources ; pwd"
	test "cd ./aaaaaaaaaa ; pwd"
	test "cd aaaaaaa ; pwd"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa ; cd /tmp/aaa ; pwd"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa ; cd /tmp/aaa ; chmod 000 /tmp/aaa ; pwd"
	test "rm -rf /tmp/aaa ; mkdir -p /tmp/aaa/bbb ; cd /tmp/aaa/bbb ; rm -rf /tmp/aaa ; pwd"
	test "cd /tmp ; cd - ; pwd"
	unset EXTRA_ENV
	EXTRA_ENV=$tmp_extra_env
	test "pwd"
}

test_correction_PATH() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "unset PATH; \"\""
	test "unset PATH; hjsdfkhfds"
	test "unset PATH; ls"
	test "unset PATH; Makefile"
	test "unset PATH; /bin/ls"
	test "export PATH=\"\"; ls"
	test "export PATH= ; ls"
	test "export PATH=pizza ; ls"
	test "export PATH=pizza ; pwd"
	test "export PATH=pizza ; echo"
	test "PATH=/tmp:./ ; ls"
}

test_correction_simple_quotes(){
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "ls ''"
	test "ls ''''"
	test "echo ''"
	test "echo $''"
	test "export toto='' ; export"
	test "''"
	test "cat ''"
}

test_correction_redirect(){
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "ls /tmp > /tmp/file ; cat /tmp/file ; echo \$?"
	test "ls >../../../../../../../../../../../../tmp/file2 ; cat /tmp/file2 ; echo \$?"
	test "ls-l /tmp > /tmp/ls ; cat </tmp/ls ; echo \$?"
	test "ls > /tmp/ls ; pwd >> /tmp/ls ; cat </tmp/ls ; echo \$?"
	test "echo ls > /tmp/ls ; cat < /tmp/ls ; cat /tmp/ls ; echo \$?"
	test "cat </tmp ; echo \$?"
	test "cat >/tmp ; echo \$?"
	test "touch /tmp/aaaaaaaa >/tmp ; ls -l /tmp/aaaaaaaaa ; echo \$?"
	test "touch /tmp/aaaaaaaa </tmp ; ls -l /tmp/aaaaaaaaa ; echo \$?"
	test "rm -rf /tmp/b ; ls >> /tmp/b ; ls >> /tmp/b ; ls >> /tmp/b ; ls >> /tmp/b ; cat /tmp/b ; echo \$?"
	test "rm -rf /tmp/b ; ls >> /tmp/b ; ls >> /tmp/b ; ls >> /tmp/b ; ls > /tmp/b ; cat /tmp/b ; echo \$?"
	test "cp Makefile /tmp/b ; true > /tmp/b ; cat </tmp/b ; echo \$?"
	test "cat > coucou > test_cat < coucou ; cat < coucou"
	test "cat > coucou > test_cat < coucou | cat < coucou"
	test "cat > coucou > test_cat < coucou | cat < coucou ; rm -rf coucou test_cat ; echo \$?"
	test "rm -rf /tmp/a ; ls >/tmp/a </tmp ; ls /tmp/a ; echo \$?"
	test "rm -rf /tmp/a ; touch /tmp/a >>/tmp ; ls -l /tmp/a ; echo \$?"
	test "rm -rf /tmp/a ; touch /tmp/a >/tmp ; ls -l /tmp/a ; echo \$?"
	test "rm -rf /tmp/a /tmp/b /tmp/c ; echo aaa >        /tmp/a>     /tmp/b >                   /tmp/c ; ls -l /tmp/a /tmp/b /tmp/c ;  cat /tmp/a /tmp/b /tmp/c ; echo \$?"
	test "rm -rf /tmp/a /tmp/b /tmp/c ; echo aaa >/tmp/a >/tmp/b >/tmp/c ; ls -l /tmp/a /tmp/b /tmp/c ;  cat /tmp/a /tmp/b /tmp/c ; echo \$?"
	test "rm -rf /tmp/a ; touch /tmp/a >/tmp >/tmp >/ ; ls -l /tmp/a ; rm -rf /tmp/a ; echo \$?"
	test "cal >/tmp ; echo \$?"
	test "ls >/tmp >/tmp >/ ; echo \$?"
	test "ls /tmp >/tmp >/ | cut -b 1-2 ; echo \$?"
	test "echo aaaaaaaaa >/tmp >/tmp >/ ; echo \$?"
	test "echo aaaaaaaaa >/tmp >/tmp >/ | cut -b 1-2 ; echo \$?"
	test "rm -rf /tmp/a ; echo aaa >/tmp >/tmp >/tmp/a ; ls -l /tmp/a ; echo \$?"
	test "rm -rf /tmp/a ; echo aaa >/tmp/a /tmp >/tmp ; ls -l /tmp/a ; echo \$?"
	test "rm -rf /tmp/a /tmp/b /tmp/c ; touch /tmp/a /tmp/b /tmp/c ; chmod 000 /tmp/a /tmp/b /tmp/c ; echo aaa > /tmp/a > /tmp/b > /tmp/c ; ls -l /tmp/a /tmp/b /tmp/c ;  cat /tmp/a /tmp/b /tmp/c ; echo \$?"
	test "echo >/dev ; echo \$?"
	test "file='/tmp/file_red' ; echo aaa >\$file ; cat /tmp/file_red ; ls -l /tmp/file_red"
	test "file='/tmp/file_red' ; >\$file echo aaa ; cat /tmp/file_red ; ls -l /tmp/file_red"
	test "rm -rf /tmp/a ; >/dev touch /tmp/a ; ls -l /tmp/a ; rm /tmp/a"
	test "rm -rf /tmp/a ; >/tmp/a echo xxxxxxxx ; ls -l /tmp/a ; rm /tmp/a"
	test "<Makefile cat >/tmp/make_file ; ls -l /tmp/make_file"
 }

test_correction_pipes() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "ls | sort | cut -b 1-6"
	test "echo aaa | cat"
	test "true | false | true"
	test "false | false | true"
	test "cat | cat | cat | grep 42"
	test "cat | cat | cat"
	test "| ls | sort"
	test "rm -rf /tmp/a /tmp/b ; touch /tmp/a | ls >/dev | touch /tmp/b ; ls -l /tmp/a /tmp/b"
	test "rm -rf /tmp/a /tmp/b /tmp/c ; echo aaa > /tmp/a | echo bbb >/tmp/b | cal > /tmp/c ; ls -l /tmp/a /tmp/b /tmp/c ; cat /tmp/a /tmp/b /tmp/c"
	test "ls | grep XXXXXXX | sort -r | cut -b 1-1 | cat"
	test "ls | grep | sort -r | cut -b 1-1 | cat"
	test "ls | grep e | sort -r | aaaaaaa | cat"

	SORT_RESULT=TRUE
	test "ls >/tmp >/tmp/a | fake2"
	test "fake1 ; ls >/tmp >/tmp/a | fake2"
	test "ls >/tmp >/tmp/a | fake2 ; echo \$?"
	test "ls >/tmp >/tmp/a | fake2 ; echo \$?"
	test "ls >/tmp >/tmp/a | fakecommande ; echo \$?"
	test "ls >/tmp/a >/tmp | fakecommande ; echo \$?"
	test "ls <./aaaaaaaaa >/tmp/a | fakecommande ; echo \$?"
	test "ls >/tmp <./aaaaaaaaa | fakecommande ; echo \$?"
	test "touch /tmp/xxx ; chmod 000 /tmp/xxx ; ls </tmp/xxx >/tmp/a | fakecommande ; echo \$? ; rm -rf /tmp/xxx"
	test "touch /tmp/xxx ; chmod 000 /tmp/xxx ; ls >/tmp/xxx | fakecommande ; echo \$? ; rm -rf /tmp/xxx"

	test "echo 000001 ; sleep 0.4 ; fake3"
	test "echo 00001 | sleep 0.4 | fake1 | sleep 0.4 | echo 00002"
	unset SORT_RESULT
}

test_correction_AND_OR () {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "true && echo aaa"
	test "false && echo aaa"
	test "true || echo aaa"
	test "false || echo aaa"
	test "aaaaaaaa && echo aaa"
	test "aaaaaaaa || echo aaa"
	test "cd /xxxxxxxxxx && echo aaa"
	test "cd /xxxxxxxxxx || echo aaa"
	test "true || true && true && echo aaa"
	test "true && true && true || echo aaa"
	test "false && false || true && echo aaa"
	test "false && false || false && echo aaa"

}

test_signal() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "fail_bin/buserror;"
	test "fail_bin/abort"
	test "fail_bin/segfault"
}

test_syntax() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test "ls >"
	test "1"
	test "1 2 3 4 5 6 7 8 9"
	test "-1 -2"
	test "\\\n"
	test ";"
	test "|"
	test ";|"
	test ">>"
	test "<"
	test ">"
	test ";>>|><"
}

test_with_extra_env ()
{
	EXTRA_ENV="$1"
	echo -e "\n \e[36m  ℹ️  This test is done with env -i $1 [./Minishell | bash --posix]\e[0m"
	test "$2"
	unset EXTRA_ENV

}

test_env_starter() {
	print_separator '█'
	echo -e "\n\n\e[34m \e[1m 🌈 [$FUNCNAME]\n \e[0m"

	test_with_extra_env "c\@t=42"				"env | sort; export | sort"
	test_with_extra_env "c.t=42"				"env | sort; export | sort ; echo ; echo \$c.t ; echo \$c.t=42"
	test_with_extra_env "cat+dog=42"			"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$cat+dog ; echo \$c.t=42 ; sh -c 'export ; env | sort'"
	test_with_extra_env "cat+=42"				"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$cat+ ; echo \$cat+=42 ; sh -c 'export ; env | sort'"
	test_with_extra_env "c+at+=42"				"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$c+at+ ; echo \$c+at+=42 ; sh -c 'export ; env | sort'"
	test_with_extra_env "c+at+=42"				"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$c+at+ ; echo \$c+at+=42 ; sh -c 'export ; env | sort'"
	test_with_extra_env "c;at=42"				"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$c;at ; echo \$c;at=42 ; sh -c 'export ; env | sort'"
	test_with_extra_env "cat=MEEEEEEEEEOWW"		"env | sort | grep -v '?' ; echo ; export | sort | grep -v '?' ; echo \$cat ; echo \$cat=MEEEEEEEEEOWW ; sh -c 'export ; env | sort'"
	test_with_extra_env "PWD=/tmp"				"ls ; pwd"
	test_with_extra_env "PATH=/tmp"				"ls ; export ; pwd ; cal ; ps ; echo ; /bin/ls"
	test_with_extra_env "PATH="					"ls ; export ; pwd ; cal ; ps ; echo ; /bin/ls"
	test_with_extra_env "PATH=''"				"ls ; export ; pwd ; cal ; ps ; echo ; /bin/ls"
}

main () {
	true > /tmp/test_ko
	true > /tmp/minishell_sumup
	true > /tmp/bash_sumup
	unset SORT_RESULT
	export EXTRA_FLAGS=
	export TEST_NB=0
	export TEST_FAILED_NB=0
	export EXTRA_ENV='TERM=xterm-256color'

	if [[ -n "$1" ]]
	then
		test "$1"
		echo -e "\n [RESULT]\n"
		print_diff_full
	else

	#   test_random
	#   test_bonus
	#   test_executor
	#   test_failed
	#   test_signal
	#   test_syntax

	test_correction_arg
	test_correction_echo
	test_correction_exit
	test_correction_exec
	test_correction_return
	test_correction_semicolons
	test_correction_baskslashs
	test_correction_env
	test_correction_export_identifier
	test_correction_export_identifier_mix_valid
	test_correction_export
	test_correction_unset_identifier
	test_correction_unset_identifier_mix_valid
	test_correction_unset
	test_correction_exp
	test_correction_cd
	test_correction_pwd
	test_correction_PATH
	test_correction_simple_quotes
	test_correction_redirect
	test_correction_pipes
	test_correction_AND_OR

	fi

	print_separator '█'
	if [[ $TEST_FAILED_NB -gt 0 ]]
	then
		echo -e "\n\n\e[31m \e[1m\t\t[ ❌  FAILED TEST : $TEST_FAILED_NB / $TEST_NB ] \n\e[0m"
		echo -e "$(date): [ FAILED TEST :   $TEST_FAILED_NB / $TEST_NB ] ❌ " >> /tmp/history.log
		cat /tmp/test_ko
	else
		echo -e "\n\n\e[32m \e[1m\t\t[ ✅  SUCCESS TEST : $TEST_NB / $TEST_NB ] \n\e[0m"
		echo -e "$(date): [ FAILED TEST :   $TEST_FAILED_NB / $TEST_NB ] ✅ " >> /tmp/history.log
	fi
	echo -e "\n\n		---- HISTORY 10 last run ---\n"
	cat /tmp/history.log | tail --lines=10

}

main "$1"
