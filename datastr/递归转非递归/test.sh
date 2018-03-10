#!/bin/bash
g++ quick_non_recurisive.c
ZERO=0
for ((var=1;var<100;var++));do
    python indata.py 
    ./a.out < input > output1
    jug=`diff output1 output | wc -l`
    if [ $jug -gt  $ZERO ];then
        echo "WAi in "
        echo $var
        break
    fi
done
echo "AC"
