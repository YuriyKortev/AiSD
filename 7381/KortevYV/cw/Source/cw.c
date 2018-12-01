#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define TABLE_HAT1 "adding\n========================================\n||  i  || узел   ||   iter  ||  nsec  ||\n========================================\n"
#define TABLE_HAT2 "deleting\n========================================\n||  i  || узел   ||   iter  ||  nsec  ||\n========================================\n"
#define TABLE1 "========================================\n"
#define TABLE2 "||% 5d||% 5d   || % 5d   ||% 5d   ||\n"

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
}Rbt;

void swap(int* a,int* b){int c=*a; *a=*b; *b=c;};

int height(Rbt* tpr){
	if(tpr==NULL)return 0;
	int hl,hr;
	if(tpr->right)
		hl=height(tpr->right);
	else
		hr=-1;
	if(tpr->left)
		hr=height(tpr->left);
	else
		hl=-1;
	return (max(hl,hr)+1);
}

int* TestGenAdd(int count){
	srand(clock());
	int* arr=(int*)malloc(count*sizeof(int));
	int n=0,i=0,j=0; 

	int dup_flag;
	int rand_val;
	
	FILE* ptr=fopen("rbt.txt","w");
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
	FILE* ptr=fopen("rbt.txt","a+");
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
	

void add_iter(Rbt** tpr, int k,int* iter){
	while(*tpr!=NULL){
		*iter=*iter+1;
		if((*tpr)->key<k)
			tpr=&((*tpr)->right);
		else 
			if((*tpr)->key>k)
				tpr=&((*tpr)->left);
			else{printf("Ключ уже есть в дереве\n"); return;}
	}
	(*tpr)=(Rbt*)malloc(sizeof(Rbt));
	(*tpr)->key=k;
	(*tpr)->left=NULL;
	(*tpr)->right=NULL;
}

void add_rec(Rbt** tpr,int k,int* iter){
    *iter=*iter+1;
    if((*tpr)==NULL){
        (*tpr)=(Rbt*)malloc(sizeof(Rbt));
        (*tpr)->key=k;
        (*tpr)->right=NULL;
        (*tpr)->left=NULL;
    }
    else{
        if((*tpr)->key>k)
          add_rec(&((*tpr)->left),k,iter);
        else
          add_rec(&((*tpr)->right),k,iter);
    }
    return;
}

void delete_iter(Rbt** tpr,int data,int* iter){
	*iter=*iter+1;
	
	while((*tpr)->key!=data){
		*iter=*iter+1;
		if((*tpr)->key<data)
			tpr=&((*tpr)->right);
		else
			tpr=&((*tpr)->left);
	}
	
	Rbt* q=*tpr;
	if(q->left==NULL)
		*tpr=q->right;
	else
		if(q->right==NULL)
			*tpr=q->left;
		else
		{
			
			if(q->left->right!=NULL){
				Rbt* r=q->left;
				Rbt* s=q;
				while(r->right!=NULL){
					s=r;
					r=r->right;
				}
				s->right=r->left;
				r->left=q->left;
				r->right=q->right;
				(*tpr)=r;
			}
			else{
				q->left->right=q->right;
				(*tpr)=q->left;
			}
		}
	q->left=NULL;
	q->right=NULL;
	free(q);
	return;
}

void delete_rec(Rbt** tpr, int data,int* iter){
*iter=*iter+1;
    if((*tpr)->key==data){
        Rbt* q=*tpr;
	if(q->left==NULL)
		*tpr=q->right;
	else
		if(q->right==NULL)
			*tpr=q->left;
		else
		{
			
			if(q->left->right!=NULL){
				Rbt* r=q->left;
				Rbt* s=q;
				while(r->right!=NULL){
					s=r;
					r=r->right;
				}
				s->right=r->left;
				r->left=q->left;
				r->right=q->right;
				(*tpr)=r;
			}
			else{
				q->left->right=q->right;
				(*tpr)=q->left;
			}
		}
	q->left=NULL;
	q->right=NULL;
	free(q);
    }
    else{
        if((*tpr)->key>data)
          delete_rec(&((*tpr)->left),data,iter);
        else
          delete_rec(&((*tpr)->right),data,iter);
    }
    return;
}

int main()
{
	void (*add) (Rbt**,int,int*);
	void (*delete) (Rbt**,int,int*);
	
	printf("Исследовать итерационный тип реализации - 0\nРекурсивный - 1\n");
	int flag;
	scanf("%d",&flag);
	
	if(flag==0){add=add_iter; delete=delete_iter;}
	if(flag==1){add=add_rec; delete=delete_rec;}
	if(flag!=0 && flag!=1)return 0;
		
	
    int iter=0,count,time1;

	printf("Введите кол-во узлов\n");
	scanf("%d",&count);
	
	int* rbt=TestGenAdd(count);
	
    Rbt* tree=NULL;
    int n=0;
       
    FILE* ptr=fopen("rbt.txt","a+");   
    if(ptr==NULL){printf("не удалось открыть файл\n"); return 0;}
    fputs("\n",ptr);

    fprintf(ptr,TABLE_HAT1);   
    int time=clock();
    while(n<count){
       time1=clock();
       add(&tree,rbt[n],&iter);
       fprintf(ptr,TABLE2,n,rbt[n],iter,(int)clock()-time1);
       iter=0;
       n++;
    }
    printf("Время добавления: %d\n",(int)clock()-time);
    fprintf(ptr,TABLE1);
	printf("height: %d\ngood height: %d\n",height(tree)-1,(int)(log(count)/log(2))+1);
	
	TestGenDel(rbt,count);
	
	n=0,iter=0;
    fprintf(ptr,TABLE_HAT2);
    time=clock();
	while(n<count){
		time1=clock();
		delete(&tree,rbt[n],&iter);
        fprintf(ptr,TABLE2,n,rbt[n],iter,(int)clock()-time1);
    	iter=0;
    	n++;
	}
	printf("время удаления: %d\n",(int)clock()-time);
	fprintf(ptr,TABLE1);

	ptr=fopen("worstRbt.txt","w");
	if(ptr==NULL){printf("не удалось открыть файл\n"); return 0;}
	
	printf("Введите кол-во узлов в худшем случае\n");
	scanf("%d",&count);
	rbt=GenWorstAdd(count);
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
	return 0;
}
