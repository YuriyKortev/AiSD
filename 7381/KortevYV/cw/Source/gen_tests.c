#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gen_tests.h"

void swap(int* a,int* b){int c=*a; *a=*b; *b=c;}

int* TestGenAdd(int count){
	srand(clock());
	int* arr=(int*)malloc(count*sizeof(int));
	int n=0,i=0,j=0; 

	int dup_flag;
	int rand_val;
	char fname[100];

	FILE* ptr=fopen("test_rbt.txt","w");
	if(ptr==NULL){printf("не удалось открыть файл\n"); return NULL;}
	
	fputs("add:\n",ptr);
	for ( i= 0; i<count; i++ ) {
	    for ( ; ; ) {
	        rand_val= 1+rand()%count;
	        dup_flag= 0;
	        for ( j= 0; j<i; j++ ) {
	            if ( rand_val == arr[j] ) { dup_flag= 1; break; }
	        }
	        if ( !dup_flag ) { break; }
	    }
	    arr[i]= rand_val;
	    fprintf(ptr,"%d ",rand_val);
	}
	fputs("\n",ptr);
	fclose(ptr);
	return arr;
}

int* GenWorstAdd(int count){
	int* arr=(int*)malloc(sizeof(int)*count);
	int i=0;
	for(i;i<count;i++)
		arr[i]=i+1;
	return arr;
}
	

void TestGenDel(int* arr,int size){
	int i;
	FILE* ptr=fopen("test_rbt.txt","a+");
	if(ptr==NULL){printf("не удалось открыть файл\n"); return;}
	
	fputs("\ndel:\n",ptr);
	
	srand(clock());

	for(i=0;i<size;i++)
		swap(&arr[i],&arr[rand()%size]);
	
	for(i=0;i<size;i++)
		fprintf(ptr,"%d ",arr[i]);
		
	fputs("\n",ptr);
	fclose(ptr);
	return;
}

