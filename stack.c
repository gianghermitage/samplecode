#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define namesize 20
#define emailsize 40
#define phonesize 10
#define stacksize 5
#define size 100


typedef struct address
{
  char name[namesize];
  char email[emailsize];
  char phone[phonesize];
}phonebook;

phonebook list[size];

typedef struct stack{
  phonebook storage[stacksize];
  int top;
}stk;

FILE * f1;
FILE * f2;

void printdata(stk s,int n);

void Initialize(stk * s)
{
  s->top = 0;
}
int empty(stk s);
int full(stk s);
void push(phonebook e,stk *s);
phonebook pop(stk *s);

void adddata(){
  int i;
  char s[100];
  for(i = 0;i<100;i++){
    fscanf(f1,"%s",s);
    strcpy(list[i].name,s);
    fscanf(f1,"%s",s);
    strcpy(list[i].email,s);
    fscanf(f1,"%s",s);;
    strcpy(list[i].phone,s);
  }
}


int main(int argc, char const *argv[])
{
  phonebook temp;
  f1 = fopen("phonebook.txt","r");
  if(f1 == NULL){
    printf("\nError open phonebook file\n");
    exit(1);
  }
  //f2 = fopen("pop.txt","w+");
  adddata();

  stk sta;
  Initialize(&sta);
	
  int i= 0;
  int choice;
	
  do{
    printf("Menu\n");
    printf("1.Push data to stack\n");
    printf("2.Pop data to file\n");
    printf("3.Show stack\n");
    printf("4.Quit\n");
    scanf("%d%*c",&choice);
	
    switch(choice){

    case 1:
      push(list[i],&sta);
      i++;
      break;
	
    case 2:
      temp = pop(&sta);
      printf("%s   ",temp.name);
      printf("%s   ",temp.email);
      printf("%s   \n",temp.phone);
      
      break;
	
    case 3:
      if(sta.top == 0){
	printf("\nStack is empty\n");
      }
      else{
	printf("\n\nPhonebook\n\n");
	for(int j = sta.top;j > 0;j--){
	  printf("%s   ",sta.storage[j-1].name);
	  printf("%s   ",sta.storage[j-1].email);
	  printf("%s   \n",sta.storage[j-1].phone);
	}
      }
      break;
	
    case 4:
      printf("\nQuit\n");
      break;

    }
  }while(choice != 4);
}

/*void printdata(stk s,int n){
  printf("%s",s.storage[n-1].name);
  printf("%s",s.storage[n-1].email);
  printf("%s\n",s.storage[n-1].phone);
  }*/
 
int empty(stk s){
  if(s.top==0) return 1;
  else return 0;
}

int full(stk  s){
  if(s.top==stacksize) return 1;
  else return 0;
}

void push(phonebook e,stk *s){
  if(full(*s)==1){
    printf("\nStack overflow\n\n");
  }
  else{
    strcpy(s->storage[s->top].name,e.name);
    strcpy(s->storage[s->top].email,e.email);
    strcpy(s->storage[s->top].phone,e.phone);
    s->top++;
    printf("\nPush data to stack successfully\n\n");

  }
}

phonebook pop(stk *s){
  if(empty(*s)==1){
    printf("\nStack undeflow\n\n");
    
  }
  else{
    s->top--;
    printf("\nPop data to file successfully\n\n");
    return s->storage[s->top];
  }
}
