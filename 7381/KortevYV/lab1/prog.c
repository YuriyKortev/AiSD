#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check(char* w){					//проверка удовлетворяет ли токен
							//определению простого логического
if(strcmp(w,"TRUE")==0 || strcmp(w,"FALSE")==0)
    return 1;
else
    if(strlen(w)==1 && isalpha(*w))
      return 1;
return 0;

}

void print(int tabs){

for(int i=0; i<tabs;i++)
	printf("! ");

}

int is_log(char* w,int tabs){

print(tabs);

if(check(w)){
    printf("\e[1;96mTRUE | FALSE | A-Z\e[0m\n");
    return 1;
}
else
  if(strcmp(w,"NOT")==0){
      printf("\e[1;96mNOT ----\e[0m\n");	 //если NOT
      if(is_log(w=strtok(NULL," "),tabs+1))	 //то следующий токен-простое логическое
	 return 1;
      else
        return 0;
  }
  else
        if(*w=='('){
	    printf("\e[1;96m(---- OR | AND ----)\e[0m\n");			//если скобка, то
            w=strtok(NULL," ");							//токены - простое логическое
            int fp=is_log(w,tabs+1);						//+ между AND || OR
            w=strtok(NULL," ");
            if(strcmp(w,"AND")!=0 && strcmp(w,"OR")!=0)
                return 0;
            w=strtok(NULL," ");
            int sp=is_log(w,tabs+1);
            w=strtok(NULL," ");
            if(fp==1 && sp==1 && *w==')' && strlen(w)==1)
                return 1;
            else
                return 0;
        }
return 0;
}

int main(){

char str[200];

fgets(str,200,stdin);
str[strlen(str)-1]='\0';

char* w=strtok(str," ");


if(is_log(w,1))
    printf("Yes\n");
else
    printf("No\n");
}
