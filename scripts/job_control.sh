BLUE='\033[0;34m'
RED='\033[0;34m'
GREEN='$GREENm'
NC='$NC'

DEFAULT_DIR=$PWD

printf "\n$GREENm# Job control. $NC"
printf "\n$BLUEm# Message indicating that the "ls" command is being executed $NC \n"
cd /tmp
mkfifo fifo
ls -lR /usr >fifo 2>&1 &
kill -18 %
sleep 1
rm fifo
jobs
sleep 1

printf "\n$BLUEm# Message indicating that 5 instances of emacs are stopped in the background $NC \n"
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

printf "\n$BLUEm# The "ls" command launched above must be the only one left $NC \n"
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

printf "\n$BLUEm# Output of the "ls | cat -e" command $NC \n"
ls | cat -e &
sleep 1
jobs
sleep 1

printf "\n$BLUEm# Message indicating that the order is suspended $NC \n"
ls -Rl / 2>&1 &
sleep 1
kill -s SIGTSTP %
sleep 1
jobs
sleep 1

printf "\n$BLUEm# PID of the command "ls" from the previous test $NC \n"
ps a | grep "ls -Rl /" | grep -v 'grep' | cut -d ' ' -f 2
sleep 1

printf "\n$BLUEm# Message indicating that the order has ended $NC \n"
kill -9 %
sleep 1
jobs
sleep 1

printf "\n$BLUEm# Output should display nothing for (ps a | grep \"ls -Rl /\" | grep -v 'grep') $NC \n"
ps a | grep "ls -Rl /" | grep -v 'grep'
sleep 1

cd $DEFAULT_DIR
