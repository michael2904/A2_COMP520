#!/bin/bash


echo
echo "*****************************"
echo "  Compiling programs"
echo "*****************************"

if [ -f compiling.log ]
then
	rm compiling.log
fi

COMPILED_DIR=./generated/valid/*.c

COMPILED=0
COMPILED_CORRECT=0
for PROG in $COMPILED_DIR
do
	((COMPILED++))
	
	echo -n "$PROG: " | tee -a compiling.log
	out=$(gcc $PROG -o ${PROG%.c}.out 2>&1) | tee -a compiling.log
	if [ $? -ne 0 ]
	then
		echo -e -n "$PROG Errors: \033[0;31m[fail]"
	else
		if grep "warning:" <<<"${out}" >/dev/null
		then
			echo $PROG Warnings
		else
			echo -e -n " \033[0;32m[pass]"
			((COMPILED_CORRECT++))
		fi
	fi
	echo -e "\033[0m"
done 
echo
echo ">>>>> # compiling programs handled: ${COMPILED_CORRECT}/${COMPILED}"

