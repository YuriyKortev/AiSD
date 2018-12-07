#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "func_rbt.h"




void free_rbt(Rbt* tree){
	if(tree->right)free_rbt(tree->right);
	if(tree->left)free_rbt(tree->left);
	free(tree);
}

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

