#!/bin/bash

gcc ./Source/lr4.c -o pr
echo 'test1: '
cat ./Tests/t1.txt;
./pr < ./Tests/t1.txt;
echo -e '\n'
echo 'test2: '
cat ./Tests/t2.txt;
./pr < ./Tests/t2.txt;
echo -e '\n'
cat ./Tests/t3.txt;
./pr < ./Tests/t3.txt;
echo -e '\n'


