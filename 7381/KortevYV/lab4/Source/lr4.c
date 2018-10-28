#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char tree[200];
}BinTree;

int ind(char* str, char ch){  //возвращает индекс ch в str
  int n=0;
  while(ch!=str[n])n++;
  return n;
}

BinTree* postinfix(BinTree* tpr,char* lkp, char* lpk,int index, int n,int k){ //построение дерева по ЛКП И ЛПК перечислениям узлов
  if(tpr->tree[k]=='/')
    return NULL;
  printf("index:%d\n",index);
  printf("n:%d\n",n);
  printf("root(tpr):%c\n",tpr->tree[k]);
  int left_val=ind(lkp,lpk[index])-n;
  if(lpk[left_val]!='/'){
    tpr->tree[2*k+1]=lpk[left_val];
    printf("root(left(tpr)):%c\n",tpr->tree[2*k+1]);
  }
  else
    tpr->tree[2*k+1]='/';
    
  if(lpk[index-1]!='/'){
    tpr->tree[2*(k+1)]=lpk[index-1];
    printf("root(right(tpr)):%c\n",tpr->tree[2*(k+1)]);
  }
  else
    tpr->tree[2*(k+1)]='/';

  postinfix(tpr,lkp,lpk,left_val,n,2*k+1);
  postinfix(tpr,lkp,lpk,index-1,n+1,2*(k+1));
  return tpr;
}

void printKLP(BinTree* b,int k){
	if (b->tree[k]!='/') {
			printf("%c",b->tree[k]);
			printKLP(b,2*k+1);
			printKLP(b,2*(k+1));
	}
        else printf("/");
}

void PrintTree (BinTree* btree, int n,int k) 
{ 
  if(btree->tree[k]!='/'){
    if (btree->tree[2*k+1]!='/') PrintTree(btree, n+1,2*k+1); 
 
    for (int i = 0; i < n; i++) printf(" "); 
      printf("%c\n", btree->tree[k]); 
 
    if (btree->tree[2*(k+1)]!='/') PrintTree(btree, n+1,2*(k+1)); 
  }
}

int main() {
  printf("Введите перечисления узлов в ЛКП И ЛПК порядках\n");
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
  BinTree* btree=(BinTree*)malloc(sizeof(BinTree));
  btree->tree[0]=lpk[strlen(lpk)-1];
  postinfix(btree,lkp,lpk,strlen(lpk)-1,1,0);
  printKLP(btree,0);
  printf("\n");
  PrintTree(btree,0,0);
  free(btree);
  return 0;
}
