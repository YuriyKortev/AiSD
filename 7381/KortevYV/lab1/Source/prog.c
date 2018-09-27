#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check (char *token)                                             //проверка удовлетворяет ли токен
{                                                                   //определению простого логического

  if (strcmp (token, "TRUE") == 0 || strcmp (token, "FALSE") == 0)
    return 1;
  else if (strlen (token) == 1 && isalpha (*token))
    return 1;
  return 0;

}

void print (int tabs)
{

  for (int i = 0; i < tabs; i++)
    printf ("! ");

}

int is_log (char *token, int tabs)
{

  print (tabs);

  if (check (token))
    {
      printf ("TRUE | FALSE | A-Z\n");
      return 1;
    }
  else if (strcmp (token, "NOT") == 0)                     //если NOT
    {                                                      //то следующий токен-простое логическое
      printf ("NOT ----\n");
      if (is_log (token = strtok (NULL, " "), tabs + 1))
	return 1;
      else
	return 0;
    }
  else if (*token == '(' && strlen (token) == 1)                      //если скобка, то
    {                                                                 
      printf ("(---- OR | AND ----)\n");
      token = strtok (NULL, " ");
      int fp = is_log (token, tabs + 1);                              //токены - простое логическое
      token = strtok (NULL, " ");
      if (strcmp (token, "AND") != 0 && strcmp (token, "OR") != 0)    //+ между AND || OR
	return 0;
      token = strtok (NULL, " ");
      int sp = is_log (token, tabs + 1);
      token = strtok (NULL, " ");
      if (fp == 1 && sp == 1 && *token == ')' && strlen (token) == 1)
	return 1;
      else
	return 0;
    }
  return 0;
}

int main ()
{

  char str[200];

  fgets (str, 200, stdin);
  str[strlen (str) - 1] = '\0';

  char *token = strtok (str, " ");


  if (is_log (token, 1))
    printf ("Yes\n");
  else
    printf ("No\n");
}

