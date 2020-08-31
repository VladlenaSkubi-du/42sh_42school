# BLUE='\033[0;34m'
# RED='\033[0;34m'
# GREEN='\033[0;32m'
# NC='\033[0m'

DEFAULT_DIR=$PWD

printf "\n\033[0;32m# MANDATORY PART. \033[0m\n"

printf "\n\033[0;32m# Prerequisites from minishell. \033[0m"
printf "\n\033[0;34m# Test a command (and/or built-in) with non-existent options; return code (must not be 0) \033[0m \n"
pwd -abs
echo ${?}

printf "\n\033[0;34m# Non-existent command ; return code (must not be 0) \033[0m \n"
doesnotexist
echo ${?}

printf "\n\033[0;34m# Launch file with insufficient permission ; return code (must not be 0) \033[0m \n"
./author
echo ${?}

printf "\n\033[0;34m# Launch existent binary file; return code (must be 0) \033[0m \n"
/bin/ls
echo ${?}

printf "\n\033[0;34m# Launch command; return code (must be 0) \033[0m \n"
ls
echo ${?}

printf "\n\033[0;34m# Launch existent binary file with flags; return code (must be 0) \033[0m \n"
/bin/ls -alF
echo ${?}

printf "\n\033[0;34m# Launch existent binary file with spaces between flags; return code (must be 0) \033[0m \n"
/bin/ls -l -a -F
echo ${?}

printf "\n\033[0;32m# Prerequisites from 21sh. \033[0m"
printf "\n\033[0;34m# Output of the \"ls\" command on the system root \033[0m \n"
ls > /tmp/ftsh_ls_out /
cat /tmp/ftsh_ls_out

printf "\n\033[0;34m# 2 listings of the root must appear and the second must have a $ at the end of each line \033[0m \n"
< /tmp/ftsh_ls_out cat -e >> /tmp/ftsh_ls_out
cat /tmp/ftsh_ls_out

printf "\n\033[0;34m# Output should display only \"1\" \033[0m \n"
echo 1 >out >&2 2>err

printf "\n\033[0;34m# Output should display only \"2\" \033[0m \n"
cd /tmp
echo 2 >out 2>err
cat err
cat out
rm -f err out
cd ${OLDPWD}
rm -f err out

printf "\n\033[0;34m# Error message indicating that the file descriptor is invalid \033[0m \n"
cat <&40

printf "\n\033[0;34m# Output should display \"ls: doesnotexist: No such file or directory\" \033[0m \n"
ls doesnotexist . 2>&1 >/dev/null
ls doesnotexist . >/dev/null 2>&1

printf "\n\033[0;34m# Output should display Content of the current folder, sorted, with a '$' at the end of each line \033[0m \n"
ls | sort -rn | cat -e

printf "\n\033[0;34m# Output should display \"Yes\" or \"No\" randomly \033[0m \n"
base64 < /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e s/1/Yes/g -e s/0/No/g

printf "\n\033[0;34m# Output should display nothing for (ps a | grep 'base64') \033[0m \n"
ps a | grep 'base64' | grep -v 'grep'

printf "\n\033[0;34m# Output should display of 2 'ls'. An additional file, \"test_file\", must appear in the second output \033[0m \n"
rm -f ${PWD}/test_file
ls -1; touch ${PWD}/test_file; ls -1
rm -f ${PWD}/test_file

printf "\n\033[0;34m# Output should display \"stayin' alive\" \033[0m \n"
exit 1 | exit 2 | exit 3; echo "stayin' alive"

printf "\n\033[0;34m# Optional error message indicating that it is impossible to write to stdout; \"out2\" \033[0m \n"
echo out >&-; echo out2
sleep 0.1

printf "\n\033[0;34m# Optional error message indicating that it is impossible to write to stdout; \"out2\" \033[0m \n"
echo out >&- | echo out2
sleep 0.1

printf "\n\033[0;34m# Optional error message indicating that it is impossible to write to stdout \033[0m \n"
echo out >&- && echo out2
sleep 0.1

printf "\n\033[0;34m# Optional error message indicating that it is impossible to write to stdout; \"out2\" \033[0m \n"
echo out >&- || echo out2
sleep 0.1

printf "\n\033[0;34m# Output should display sentense \033[0m \n"
cat << END
hello world
and good
morning!
END
sleep 0.1

printf "\n\033[0;34m# Output should display \"hi\" \033[0m \n"
cat << EO\
F
hi
EOF
sleep 0.1

printf "\n\033[0;34m# Output should display \"abc\" \"def$\" \"ghi$\" \033[0m \n"
cat > /tmp/heredoc-append << FIN
abc
FIN
sleep 0.1
cat -e >> /tmp/heredoc-append << FIN
def
ghi
FIN
cat /tmp/heredoc-append
sleep 1

printf "\n\033[0;34m# Output should display three strings in alphabetical order \033[0m \n"
cat << EOF | sort
abd
abc
abb
EOF
sleep 0.1

printf "\n\033[0;32m# Built-ins (without checking exit). \033[0m"
printf "\n\033[0;34m# Check \"cd /Users; pwd\" \033[0m \n"
cd /Users
pwd

printf "\n\033[0;34m# Check \"cd ..; pwd\" \033[0m \n"
cd ..
pwd

printf "\n\033[0;34m# Check \"cd /tmp; /bin/pwd\" \033[0m \n"
cd /tmp
/bin/pwd

printf "\n\033[0;34m# Check \"cd; /bin/pwd\" \033[0m \n"
cd
/bin/pwd

printf "\n\033[0;34m# Check \"cd /tmp; pwd\" \033[0m \n"
cd /tmp
pwd

printf "\n\033[0;34m# Check \"cd /bin; pwd\" \033[0m \n"
cd /bin
pwd

printf "\n\033[0;34m# Check \"cd -; pwd\" \033[0m \n"
cd -
pwd

printf "\n\033[0;34m# Check \"cd -L /tmp; cd -P ..; pwd\" \033[0m \n"
cd -L /tmp; cd -P ..
pwd

printf "\n\033[0;34m# Message indicating that "type" is a builtin and "ls" a command with its path \033[0m \n"
type type ls

printf "\n\033[0;32m# Logical operators. \033[0m"
printf "\n\033[0;34m# Display of the "ls" command twice with different parameters \033[0m \n"
ls -l && ls

printf "\n\033[0;34m# \"ls: doesnotexist: No such file or directory\nNotice me senpai\"; return code (must be 0) \033[0m \n"
ls doesnotexist || echo "Notice me senpai"
echo ${?}

printf "\n\033[0;34m# Output should display \"No error\"; return code (must be 0) \033[0m \n"
echo 'No error' || echo 'You cant see me'
echo ${?}

printf "\n\033[0;34m# Output should display \"bar\"\033[0m \n"
false && echo foo || echo bar

printf "\n\033[0;34m# Output should display \"bar\"\033[0m \n"
true || echo foo && echo bar

printf "\n\033[0;32m# Environment management. \033[0m"
printf "\n\033[0;34m# Output should display \"hello_world\" and \"world\"\033[0m \n"
a=hello b=world; b=42 echo ${a}_${b} && echo ${b}

printf "\n\033[0;34m# Output of the \"ls -atr\" command on the system root \033[0m \n"
directory=/ ls_opt=-atr
ls ${ls_opt} ${directory}

printf "\n\033[0;34m# Output should display empty string for (echo ${empty}|cat -e) \033[0m \n"
echo ${empty}|cat -e

printf "\n\033[0;34m# Output should display all internal shell and environment variables \033[0m \n"
set

printf "\n\033[0;34m# Output should display \"a=hello\" and \"b=world\"\033[0m \n"
set | grep -E '(a|b)=' | grep -v _=

printf "\n\033[0;34m# Output should display all environment variables only \033[0m \n"
env

printf "\n\033[0;34m# Output should display nothing for (env | grep -E '(a|b)=') \033[0m \n"
env | grep -E '(a|b)=' | grep -v _=

printf "\n\033[0;34m# Output should display \"world\" \033[0m \n"
export b
printenv b

printf "\n\033[0;34m# Output should display \"ONESHOT=\" \033[0m \n"
ONESHOT= env | grep ONESHOT | grep -v _=

printf "\n\033[0;34m# Output should display nothing for (env | grep ONESHOT) \033[0m \n"
env | grep ONESHOT | grep -v _=

printf "\n\033[0;34m# Output should display nothing for (env | grep -E '(a|b)=') \033[0m \n"
unset a b
env | grep -E '(a|b)=' | grep -v _=
printf "\n\033[0;34m# Output should display nothing for (set | grep -E '(a|b)=') \033[0m \n"
set | grep -E '(a|b)=' | grep -v _=

printf "\n\033[0;34m# Output should display return code (must be 0) \033[0m \n"
cd /tmp
rm -rf testdir
unset PATH
PATH=/bin:/usr/bin
mkdir -p testdir
echo ${?}

printf "\n\033[0;34m# Output should display \"testdir\" \033[0m \n"
ls -1 | grep testdir

printf "\n\033[0;34m# Output should display \"0\", then \"1\" \033[0m \n"
true; echo ${?}; false; echo ${?}

cd $DEFAULT_DIR
