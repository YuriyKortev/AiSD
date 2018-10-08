#include  <stdio.h>
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


 
queue * init (){
  
  queue * tpr = malloc (sizeof (queue));
  
  tpr->head = NULL;
  
  tpr->tail = NULL;
  
return tpr;

}


 
int main (){
  
  FILE * ptr = fopen ("generations.txt", "w");
  
 
  char *name[] ={ "anna", "boris", "ekaterina", "igor", "marina", "olga", "yakov" };
  
 
  int list[7][7] ={ {0, 0, 0, 1, 0, 1, 0},  //заданный массив, содержащий информацию
                    {0, 0, 0, 0, 0, 0, 0},  // о детях человека
                    {0, 0, 0, 0, 1, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0}, 
                    {0, 0, 0, 0, 0, 0, 0}, 
                    {0, 0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0, 0}};
  
 
  queue * children = init ();
  
  char start[20];
  
  printf ("Введите имя того, чье потомство вы хотите узнать\n");
  
  printf ("Варианты:\n");
  
  for (int p; p < 7; p++)
    printf ("%s\n", name[p]);
  
  fgets (start, 20, stdin);
  
  start[strlen (start) - 1] = '\0';
  
  int next = 0;
  
  while (strcmp (name[next], start)!=0){
    next++;
    if(next==7){
      printf("введено некорректное имя\n");
      return 0;
    }
  }

  push (children, next);
  
  printf("\n");
 
  while (!isempty (children)){
      next = pop (children);
      fprintf (ptr, "%s\n", name[next]);
      printf("%s\n",name[next]);
      for (int i = 0; i < 7; i++){
	if (list[next][i])
	  push (children, i);
      }
  }
  
return 0;
}
