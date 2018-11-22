#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
    char key;
    struct node* left;
    struct node* right;
}Rbt;


Rbt* add(Rbt* tpr,char k){
    if(tpr==NULL){
        tpr=(Rbt*)malloc(sizeof(Rbt));
        tpr->key=k;
        tpr->right=NULL;
        tpr->left=NULL;
    }
    else{
        if(tpr->key>k)
          tpr->left=add(tpr->left,k);
        else
          tpr->right=add(tpr->right,k);
    }
 
    return tpr;
}

void PrintTree (Rbt* btree, int n) 
{ 
  if(btree!=NULL){
    if (btree->right) PrintTree(btree->right, n+1); 
 
    for (int i = 0; i < n; i++) printf(" "); 
      printf("%c\n", btree->key); 
 
    if (btree->left) PrintTree(btree->left, n+1); 
  }
}

Rbt* find(Rbt* tpr, char k){
    if(tpr==NULL)return NULL;
    if(tpr->key==k)return tpr;
    if(k<tpr->key)return find(tpr->left,k);
    else return find(tpr->right,k);
}

void delete(Rbt* p,char data){
	Rbt** tpr=&p;
	while((*tpr)->key!=data){
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
	q->left=NULL;
	q->right=NULL;
	free(q);

}

int main()
{
    char fname[100];
    fgets(fname,100,stdin);
    fname[strlen(fname)-1]='\0';
    FILE* ptr=fopen(fname,"r");
    if(ptr==NULL){
       printf("нет файла\n");
       return 0;
    }
    Rbt* tree=NULL;
    int n=0;
    char rbt[100];
    fgets(rbt,100,ptr);
    rbt[strlen(rbt)-1]='\0';
    while(rbt[n]!='\0'){
       tree=add(tree,rbt[n]);
       n++;
    }
    PrintTree(tree,0);

    char d;
    fscanf(ptr,"%c",&d);
    
    if(find(tree,d))
	    delete(tree,d);
	    
    printf("\n\n");
    PrintTree(tree,0);
    return 0;
}
