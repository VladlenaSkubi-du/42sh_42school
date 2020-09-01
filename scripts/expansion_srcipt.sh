#! /bin/bash

TEST='|U hate this|'
printf "\033[0;32m*** Simple tests ***\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~1~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo ${TEST}
printf "\033[0;31m|U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~2~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo ${TEST}$TEST
printf "\033[0;31m|U hate this||U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~3~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo ${TES}$TEST
printf "\033[0;31m|U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~4~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo $TEST${TEST}
printf "\033[0;31m|U hate this||U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~5~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo ${TEST}AAAA
printf "\033[0;31m|U hate this|AAAA\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~6~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo AAAA${TEST}AAAA
printf "\033[0;31mAAAA|U hate this|AAAA\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~7~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo AAAA${TST}AAAA
printf "\033[0;31mAAAAAAAA\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~8~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo AAAA${TEST}AAAA$TEST
printf "\033[0;31mAAAA|U hate this|AAAA|U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~9~~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo $TESTasdf
printf "\033[0;31m\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~10~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo AAA$TEST
printf "\033[0;31mAAA|U hate this|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~11~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo AAA$TET
printf "\033[0;31mAAA\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~12~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo $$
printf "\033[1;34m~~~~~~~~~~~~13~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo $$$TEST
printf "\033[1;34m~~~~~~~~~~~~13~~~~~~~~~~~\033[0m\n"
TEST='|U hate this|' echo $$$$TEST
printf "\033[1;34m~~~~~~~~~~~~13~~~~~~~~~~~\033[0m\n"

printf "\033[0;32m*** Middle tests ***\033[0m\n"

TEST2='|JTERRY|'
TEST1='|GGWIN-GO|'
printf "\033[1;34m~~~~~~~~~~~~1~~~~~~~~~~~~\033[0m\n"
echo ${TEST2:-$TEST1}
printf "\033[0;31m|JTERRY|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~2~~~~~~~~~~~~\033[0m\n"
echo ${TES2:-$TEST1}
printf "\033[0;31m|GGWIN-GO|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~3~~~~~~~~~~~~\033[0m\n"
echo ${TES2:-$TES1}
printf "\033[0;31m\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~4~~~~~~~~~~~~\033[0m\n"
echo ${TEST2:+$TEST1}
printf "\033[0;31m|GGWIN-GO|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~5~~~~~~~~~~~~\033[0m\n"
echo ${TET2:+$TEST1}
printf "\033[0;31m\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~6~~~~~~~~~~~~\033[0m\n"
echo ${TEST2:=$TEST1}
printf "\033[0;31m|JTERRY|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~6~~~~~~~~~~~~\033[0m\n"
echo ${TET2:=$TEST1}
printf "\033[0;31m|GGWIN-GO|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~7~~~~~~~~~~~~\033[0m\n"
echo ${TET2}
printf "\033[0;31m|GGWIN-GO|\033[0m\n"
printf "\033[1;34m~~~~~~~~~~~~8~~~~~~~~~~~~\033[0m\n"
echo ${PWD:PWD}