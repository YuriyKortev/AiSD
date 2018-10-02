#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinKor{         //плечо бинарного коромысла, если child==NULL
  char weight;                 //то держит гирьку
  char lenght;
  struct  BinKor* next;
  struct  BinKor* prev;
  struct  BinKor* parent;
  struct  BinKor* child;
}BinKor;

void print(int num){
  for(int i=0;i<num;i++)
    printf("! ");
}

BinKor* crtBinKor(char* str, int* i,BinKor* parent,int tab){  //инициализация
  tab++;

  BinKor* tpr=NULL;
  BinKor* head=NULL;
  
  if(str[*i]=='('){
    *i=*i+2;
    tpr=malloc(sizeof(BinKor));
    head=tpr;
    tpr->parent=parent;
    tpr->child=NULL;
    tpr->prev=NULL;
    tpr->lenght=str[*i];
  }
  else
    return NULL;
  
  *i=*i+2;

  print(tab);
  printf(" %d: ",tab);
  printf("(%c ",tpr->lenght);

  if(str[*i]=='('){
    printf("->%d)\n",tab+1);
    tpr->child=crtBinKor(str,i,tpr,tab);
  }
  else
    if(isdigit(str[*i])){
      tpr->weight=str[*i];
      printf("%c)\n",tpr->weight);
    }
    else
      return NULL;

  tpr->next=malloc(sizeof(BinKor));
  tpr->next->prev=tpr;
  *i=*i+4;
  tpr=tpr->next;
  tpr->next=NULL;
  tpr->child=NULL;
  tpr->parent=NULL;
  if(isdigit(str[*i]))
    tpr->lenght=str[*i];
  *i=*i+2;

  print(tab);
  printf(" %d: ",tab);
  printf("(%c ",tpr->lenght);

  if(str[*i]=='('){
    printf("->%d)\n",tab+1);
    tpr->child=crtBinKor(str,i,tpr,tab);
  }
  else
    if(isdigit(str[*i])){
      tpr->weight=str[*i];
      printf("%c)\n",tpr->weight);
    }
    else
      return NULL;

  *i=*i+2;
  return head;
}

void numKor(BinKor* f,BinKor* sec,int* num)    //поиск вхождений
{
  if(f==NULL || sec==NULL){
    printf("Введено не бинарное коромысло\n");
    return;
  }
  if(f->child==NULL && f->next->child==NULL && f->weight==sec->weight && f->lenght==sec->lenght && f->next->lenght==sec->next->lenght && f->next->weight==sec->next->weight)
  {
	*num=*num+1;
	return;
  }
  if(f->child!=NULL)
      numKor(f->child,sec,num);
  if(f->next->child!=NULL)
	  numKor(f->next->child,sec,num);
}

int main() {
  char str[200];
  char str2[200];
  printf("БинКор::=((lenght грузик) (lenght грузик))\nгрузик::=weight | БинКор\n");
  fgets(str,200,stdin);
  fgets(str2,200,stdin);
  str[strlen(str)-1]='\0';
  str2[strlen(str2)-1]='\0';
  int i=0;
  
  BinKor* head=crtBinKor(str,&i,NULL,0);
  i=0;
  printf("\n");
  BinKor* sec=crtBinKor(str2,&i,NULL,0);
  int num=0;
  numKor(head,sec,&num);
  printf("%d вхождений(я) 2го коромысла в 1е\n",num);
  free(head);
  free(sec);
  return 0;

}
