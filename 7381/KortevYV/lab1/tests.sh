#!/bin/bash

gcc ./Source/prog.c -o pr
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
echo 'test4: '
cat ./Tests/t4.txt;
./pr < ./Tests/t4.txt;
echo -e '\n'
echo 'test5: '
cat ./Tests/t5.txt;
./pr < ./Tests/t5.txt;
echo -e '\n'
echo 'test6: '
cat ./Tests/t6.txt;
./pr < ./Tests/t6.txt;
echo -e '\n'
echo 'test7: '
cat ./Tests/t7.txt;
./pr < ./Tests/t7.txt;
echo -e '\n'
echo 'test8: '
cat ./Tests/t8.txt;
./pr < ./Tests/t8.txt;
echo -e '\n'
echo 'test9: '
cat ./Tests/t9.txt;
./pr < ./Tests/t9.txt;
echo -e '\n'
