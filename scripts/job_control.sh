BLUE='\033[0;34m'
RED='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m'

DEFAULT_DIR=$PWD

printf "\n\033[0;32m# Job control. \033[0m"
printf "\n\033[0;34m# Message indicating that the "ls" command is being executed \033[0m \n"
cd /tmp
mkfifo fifo
ls -lR /usr >fifo 2>&1 &
kill -18 %
sleep 1
rm fifo
jobs
sleep 1

printf "\n\033[0;34m# Message indicating that 5 instances of emacs are stopped in the background \033[0m \n"
emacs -nw &
sleep 1
emacs -nw &
sleep 1
emacs -nw &
sleep 1
emacs -nw &
sleep 1
emacs -nw &
sleep 1
jobs
sleep 1

printf "\n\033[0;34m# The "ls" command launched above must be the only one left \033[0m \n"
kill -9 %
sleep 1
kill -9 %
sleep 1
kill -9 %
sleep 1
kill -9 %
sleep 1
kill -9 %
sleep 1
jobs
sleep 1
kill -9 %
sleep 1

printf "\n\033[0;34m# Output of the "ls | cat -e" command \033[0m \n"
ls | cat -e &
sleep 1
jobs
sleep 1

printf "\n\033[0;34m# Message indicating that the order is suspended \033[0m \n"
ls -Rl / 2>&1 &
sleep 1
kill -s SIGTSTP %
sleep 1
jobs
sleep 1

printf "\n\033[0;34m# PID of the command "ls" from the previous test \033[0m \n"
ps a | grep "ls -Rl /" | grep -v 'grep' | cut -d ' ' -f 2
sleep 1

printf "\n\033[0;34m# Message indicating that the order has ended \033[0m \n"
kill -9 %
sleep 1
jobs
sleep 1

printf "\n\033[0;34m# Output should display nothing for (ps a | grep \"ls -Rl /\" | grep -v 'grep') \033[0m \n"
ps a | grep "ls -Rl /" | grep -v 'grep'
sleep 1

cd $DEFAULT_DIR
