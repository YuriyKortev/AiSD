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

BinKor* crtBinKor(char* str, int* i,BinKor* parent){  //инициализация
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
  if(str[*i=*i+2]=='(')
    tpr->child=crtBinKor(str,i,tpr);
  else
    if(isdigit(str[*i]))
      tpr->weight=str[*i];
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
  if(str[*i]=='(')
    tpr->child=crtBinKor(str,i,tpr);
  else
    if(isdigit(str[*i]))
      tpr->weight=str[*i];
    else
      return NULL;
  *i=*i+2;
  return head;
}

void numKor(BinKor* f,BinKor* sec,int* num)    //поиск вхождений
{
  if(f==NULL || sec==NULL){
    printf("not BinKor\n");
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
  
  BinKor* head=crtBinKor(str,&i,NULL);
  i=0;
  BinKor* sec=crtBinKor(str2,&i,NULL);
  int num=0;
  numKor(head,sec,&num);
  printf("%d\n",num);
  free(head);
  free(sec);
  return 0;

}
