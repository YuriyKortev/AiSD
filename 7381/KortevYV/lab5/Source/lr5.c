#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
    char key;
    struct node* left;
    struct node* right;
    int size;
}Rbt;

Rbt* search(Rbt* tpr,char k){
    if(tpr==NULL)return NULL;
    if(tpr->key==k)return tpr;
    if(k<tpr->key)
      search(tpr->left,k);
    else
      search(tpr->right,k);
}

int gsize(Rbt* tpr){
    if(tpr==NULL)
      return 0;
    return tpr->size;
}

void fsize(Rbt* tpr){
    tpr->size=gsize(tpr->right)+gsize(tpr->left)+1;
}

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
    fsize(tpr);
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

Rbt* join(Rbt* p, Rbt* q) // объединение двух деревьев
{
	if( !p ) return q;
	if( !q ) return p;
	if( rand()%(p->size+q->size) < p->size ) 
	{
		p->right = join(p->right,q); 
		fsize(p); 
		return p; 
	}
	else 
	{
		q->left = join(p,q->left); 
		fsize(q); 
		return q; 
	}
}

Rbt* delete(Rbt* p, char k) // удаление из дерева p первого найденного узла с ключом k 
{
	if( !p ) return p; 
	if( p->key==k ) 
	{
		Rbt* q = join(p->left,p->right); 
		free(p); 
		return q; 
	}
	else if( k<p->key ) 
		p->left = delete(p->left,k); 
	else 
		p->right = delete(p->right,k); 
	return p; 
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
    char in,rbt[100];
    fgets(rbt,100,ptr);
    rbt[strlen(rbt)-1]='\0';
    while(rbt[n]!='\0'){
       tree=add(tree,rbt[n]);
       n++;
    }
    PrintTree(tree,0);
    printf("\nPrint key\n");
    char d;
    fscanf(ptr,"%c",&d);
    if(find(tree,d)!=NULL)
      delete(tree,d);
    printf("\n\n");
    PrintTree(tree,0);
    return 0;
}
