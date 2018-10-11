#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node  //узел очереди
{
  int value;
  struct node *next;
} node;

 
typedef struct queue //структура очереди
{
  node * head;
  node * tail;
}queue;

 
int isempty (queue * children)
{
  if (children->head == NULL && children->tail == NULL)
    return 1;
  else
    return 0;
}


 
void push (queue * children, int value)
{
  node * tpr = (node *) malloc (sizeof (node));
  tpr->next = NULL;
  
  tpr->value = value;
  
  if (!isempty (children)){      
    children->tail->next = tpr;  
    children->tail = children->tail->next;
  }
  else{
    children->head = tpr;  
    children->tail = tpr;
  }
  return;
}


 
int pop (queue * children){
  
  if (isempty (children)){
      printf ("Очередь пуста\n");
      return 0;
  }
  
  if (children->head == children->tail){
    int exit = children->head->value; 
    children->head = NULL;
    children->tail = NULL;
    return exit;
  }
  
  node * tpr = children->head;
  
  children->head = children->head->next;
  
return tpr->value;

}


 
void clean (queue * children){
  
  while (!isempty (children)){
    node * tpr = children->head;
    children->head = children->head->next;
    free (tpr);
  }
  
return;

}

void printqueue (queue* children){
  if(isempty(children)){
    printf("пуста\n");
    return;
  }

  node* tpr=children->head;
  while(tpr!=NULL){
    printf("-%d",tpr->value);
    tpr=tpr->next;
  }
  printf("\n");
  return;
}

 
queue * init (){
  
  queue * tpr = malloc (sizeof (queue));
  
  tpr->head = NULL;
  
  tpr->tail = NULL;
  
return tpr;

}
char** getfmly(FILE* ptr,int num){           //создает массив типа дети

  char** children=malloc(num*sizeof(char*));
  int i,j;
  for(i=0;i<num;i++){
    children[i]=malloc(sizeof(char)*(num+2));
    fgets(children[i],num+2,ptr);
    children[i][strlen(children[i])-1]='\0';
  }
  
  return children;
}

char** getnames(FILE* ptr,int num){      //создает массив с именами из файла

  char **name=malloc(num*sizeof(char*));
  int i;
  for(i=0;i<num;i++){
    name[i]=malloc(sizeof(char)*20);
    fgets(name[i],20,ptr);
    name[i][strlen(name[i])-1]='\0';
  }
  
  return name;
}


 
int main (){
  
  char fname[20];
  printf("choose fmly file\n");
  fgets(fname,20,stdin);
  fname[strlen(fname)-1]='\0';
  
  FILE * ptr = fopen (fname, "r");
  FILE * exit = fopen("generation.txt", "w");
  if(ptr==NULL){
    printf("error");
    return 0;
  }
  int num;
  fscanf(ptr,"%d\n",&num);

  char** name=getnames(ptr,num);
  printf("\n");
  char** list=getfmly(ptr,num);

  fclose(ptr);
  queue * children = init ();
  
  char start[20];
  
  printf ("Введите имя того, чье потомство вы хотите узнать\n");
  
  printf ("Варианты:\n");
  
  for (int p=0; p < num; p++)
    printf ("%s\n", name[p]);
  
  fgets (start, 20, stdin);
  
  start[strlen (start) - 1] = '\0';
  
  int next = 0;
  
  while (strcmp (name[next], start)!=0){   //поиск индекса имени в массиве
    next++;
    if(next==num){
      printf("введено некорректное имя\n");
      return 0;
    }
  }

  push (children, next);                   //добавляю в очередь индекс имени 
                                           //человка
  printf("\n");
 
  while (!isempty (children)){             //добавляю в очередь индексы потомков
      printqueue(children);                //человека и вывожу в файл
      next = pop (children);
      fprintf (exit, "%s\n", name[next]);

      for (int i = 0; i < num; i++)
	if (list[next][i]=='1')
	  push (children, i);
  }
  fclose(exit);
  return 0;
}
