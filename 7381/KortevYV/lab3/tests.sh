#!/bin/bash

gcc ./Source/lab3.c -o pr
echo 'test1: '
cat ./Tests/t1.txt;
./pr < ./Tests/t1.txt;
echo -e '\n'
echo 'test2: '
cat ./Tests/t2.txt;
./pr < ./Tests/t2.txt;
echo -e '\n'
echo 'test3: '
cat ./Tests/t3.txt;
./pr < ./Tests/t3.txt;
echo -e '\n'

