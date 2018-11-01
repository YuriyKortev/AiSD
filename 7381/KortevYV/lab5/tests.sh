#!/bin/bash

gcc ./Source/lr5.c -o pr
echo 'test1: '
cat ./Tests/ts1.txt;
./pr < ./Tests/ts1.txt;
echo -e '\n'
echo 'test2: '
cat ./Tests/ts2.txt;
./pr < ./Tests/ts2.txt;
echo -e '\n'
cat ./Tests/ts3.txt;
./pr < ./Tests/ts3.txt;
echo -e '\n'


