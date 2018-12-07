#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "gen_tests.h"
#include "func_rbt.h"
#include "func_graph.h"

void study_adding(char* fname,int count,void (*add)(Rbt**,int,int*)){
	Rbt* tree=NULL;
	int iter=0,time1,n=0,i;
	FILE* ptr=fopen(fname,"w");   
    if(ptr==NULL){printf("не удалось открыть файл\n"); return;}
    fputs("adding: \n",ptr);

	int compl[count];
  
    int time=clock();
    int* rbt=TestGenAdd(count);
    
    fopen(res_add,"w");
	remove(res_add);
    for(i=0;i<4;i++){
        fprintf(ptr,TABLE_HAT1); 
		rbt=TestGenAdd(count);
		n=0;
    	while(n<count){
       		time1=clock();
       		add(&tree,rbt[n],&iter);
       		fprintf(ptr,TABLE2,n,rbt[n],iter,(int)clock()-time1);
       		compl[n]=iter;
      		iter=0;
      		n++;
      		
    	}
	fprintf(ptr,TABLE1);
   	graph(compl,100,count,i,res_add);

	free_rbt(tree);

    	tree=NULL;
	}
}

void study_deleting(char* fname,int count,void(*delete)(Rbt**,int,int*),void (*add)(Rbt**,int,int*)){
	int i,n,iter=0,time1;
	int* rbt;
	int compl[count];
	FILE* ptr=fopen(fname,"a+");   
    if(ptr==NULL){printf("не удалось открыть файл\n"); return;}
    
	Rbt* tree=NULL;
	fopen(res_del,"w");
	remove(res_del);
	for(i=0;i<4;i++){
		n=0;
		rbt=TestGenAdd(count);
		while(n<count){
     	  		add(&tree,rbt[n],&iter);
    	   		iter=0;
    	  		n++;
      		
   	 	}
		TestGenDel(rbt,count);
	
		n=0,iter=0;
    	fprintf(ptr,TABLE_HAT2);

		while(n<count){
			time1=clock();
			delete(&tree,rbt[n],&iter);
			compl[n]=iter;
			fprintf(ptr,TABLE2,n,rbt[n],iter,(int)clock()-time1);
		
   			iter=0;
    		n++;
		}
		graph(compl,100,count,i,res_del);
		fprintf(ptr,TABLE1);
	}
}

void study_worst(char* fname,void(*delete)(Rbt**,int,int*),void (*add)(Rbt**,int,int*)){
	int count,n,time1,iter=0;
	Rbt* tree=NULL;
	FILE* ptr=fopen(fname,"w");
	if(ptr==NULL){printf("не удалось открыть файл\n"); return ;}
	
	printf("Введите кол-во узлов в худшем случае\n");
	scanf("%d",&count);
	int* rbt=GenWorstAdd(count);
	n=0;
	
	fprintf(ptr,TABLE_HAT1); 
	while(n<count){
		time1=clock();
		add(&tree,rbt[n],&iter);
        fprintf(ptr,TABLE2,n,rbt[n],iter,(int)clock()-time1);
    	iter=0;
    	n++;
	}
	fprintf(ptr,TABLE1);
	
	fprintf(ptr,TABLE_HAT2);
	n--;
	while(n>0){
		time1=clock();
		delete(&tree,rbt[n],&iter);
  	        fprintf(ptr,TABLE2,count-n-1,rbt[n],iter,(int)clock()-time1);
    		iter=0;
    		n--;
	}
	fprintf(ptr,TABLE1);
	fclose(ptr);
}
int main()
{
	void (*add) (Rbt**,int,int*);
	void (*delete) (Rbt**,int,int*);
	char* fname;
	char* fname_worst;
	printf("Исследовать итерационный тип реализации - 0\nРекурсивный - 1\n");
	int flag;
	scanf("%d",&flag);
	
	if(flag==0){add=add_iter; delete=delete_iter;fname=f_iter;fname_worst=fworst_iter;}
	if(flag==1){add=add_rec; delete=delete_rec;fname=f_rec;fname_worst=fworst_rec;}
	if(flag!=0 && flag!=1)return 0;
		
	
    int count;

	printf("Введите кол-во узлов\n");
	scanf("%d",&count);
    
    study_adding(fname,count,add);
    
    study_deleting(fname,count,*delete,add);
    
    study_worst(fname_worst,*delete,add);
	
	return 0;
}
