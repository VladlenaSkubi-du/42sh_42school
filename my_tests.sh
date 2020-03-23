#!/bin/bash --posix

echo -e "---test permission---"
mkdir test1
chmod 000 test1
err=$(./42sh -c "cd test1" 2>&1)
suc="e-bash: cd: test1: permission denied"
if [ "$err" = "$suc" ]
then
    echo -en "\033[32;1m SUCCESS \033[0m"
    echo -e "\n"
else
    echo -en "\033[31;1m FAULT \033[0m"
    echo -e "\n"
fi
rm -rf test1

echo -en "---test 'no such file or directory'---\n"
err=$(./42sh -c "cd ololo" 2>&1)
suc="e-bash: cd: ololo: no such file or directory"
if [ "$err" = "$suc" ]
then
    echo -en "\033[32;1m SUCCESS \033[0m"
    echo -e "\n"
else
    echo -en "\033[31;1m FAULT \033[0m"
    echo -e "\n"
fi
