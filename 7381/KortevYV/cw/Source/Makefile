all: main.o func_graph.o func_rbt.o gen_tests.o
	gcc main.o func_graph.o func_rbt.o gen_tests.o -lm

main.o: main.c func_graph.h gen_tests.h func_rbt.h
	gcc -c main.c

func_grapf.o: func_graph.c 
	gcc -c func_graph.c

func_rbt.o: func_rbt.c 
	gcc -c func_rbt.c

gen_tests.o: gen_tests.c 
	gcc -c gen_tests.c
clean:
	rm main.o func_rbt.o gen_tests.o func_graph.o
