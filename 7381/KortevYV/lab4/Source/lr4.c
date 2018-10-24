#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char val;
  struct node* left;
  struct node* right;
}BinTree;

int ind(char* str1, char ch){
  int n=0;
  while(ch!=str1[n])n++;
  return n;
}

BinTree* postinfix(BinTree* tpr,char* lkp, char* lpk,int index, int n){
  if(tpr==NULL)
    return NULL;
  int left_val=ind(lkp,lpk[index])-n;
  if(lpk[left_val]!='/'){
    tpr->left=(BinTree*)malloc(sizeof(BinTree));
    tpr->left->val=lpk[left_val];
  }
  else
    tpr->left=NULL;
    
  if(lpk[index-1]!='/'){
    tpr->right=(BinTree*)malloc(sizeof(BinTree));
    tpr->right->val=lpk[index-1];
  }
  else
    tpr->right=NULL;

  postinfix(tpr->left,lkp,lpk,left_val,n);
  postinfix(tpr->right,lkp,lpk,index-1,n+1);
  return tpr;
}

void printKLP(BinTree* b){
	if (b!=NULL) {
			printf("%c",b->val);
			printKLP(b->left);
			printKLP(b->right);
	}
        else printf("/");
}

void destroy(BinTree* b){
  if(b!=NULL){
    destroy(b->left);
    destroy(b->right);
    free(b);
  }
}

int main() {
  
  char lkp[500];
  char lpk[500];
  fgets(lkp,500,stdin);
  fgets(lpk,500,stdin);

  if(strlen(lkp)!=strlen(lpk)){
    printf("Неверно перечислены узлы\n");
    return 0;
  }

  lkp[strlen(lkp)-1]='\0';
  lpk[strlen(lpk)-1]='\0';
  BinTree* tree=(BinTree*)malloc(sizeof(BinTree));
  tree->val=lpk[strlen(lpk)-1];
  postinfix(tree,lkp,lpk,strlen(lpk)-1,1);
  printKLP(tree);
  printf("\n");
 // destroy(&tree);
  return 0;
}
