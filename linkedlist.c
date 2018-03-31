#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define namesize 50
#define emailsize 20
#define phonesize 10
#define size 100

typedef struct elements{
  char name[namesize];
  char email[emailsize];
  char number[phonesize];
}phonebook;

typedef struct list{
  phonebook data;
  struct list *next;
}node;


node * root = NULL;
node * cur = NULL;

int countnode();
node * newnode();

void insertatpos(int i);
void insertbefore();
void insertafter();

node * deletenode(int i);
void deletelist();

node * search(char key[size]);

void showdata();

node * traverse(int i);

FILE * f;

int main(){
  
  node * temp3;
  int position;
  
  node * temp4;
  int positiondel;
  
  node * temp6;
  phonebook tmp;

  int count;
  
  f = fopen("phonebook.txt","r");
  
  int choice;
  char key[size];
  
  do{
    printf("\n\nMenu\n");
    printf("1.Add data before current node\n");
    printf("2.Add data after current node\n");
    printf("3.Add data at specific position\n");
    printf("4.Delete data at specific position\n");
    printf("5.Delete list\n");
    printf("6.Search data\n");
    printf("7.Show data\n");
    printf("8.Quit\n");
    printf("\nYour choice:");
    scanf("%d%*c",&choice);
    switch(choice){
    case 1:
      insertbefore();
      printf("\nAdd data successfully\n");
      break;
      
    case 2:
      insertafter();
      printf("\nAdd data successfully\n");
      break;
      
    case 3:
      printf("Enter the position: ");
      scanf("%d%*c",&position);
      if(position < 0 || position > countnode(root)){
	printf("Position is not valid\n");
	break;
	
      }
      else{
	insertatpos(position);
      }
      break;
      
    case 4:
      printf("Enter the position: ");
      scanf("%d%*c",&positiondel);
      if(positiondel < 0 || positiondel > countnode(root)){
	printf("Position is not valid\n");
	break;
	
      }
      else{
	temp4=deletenode(positiondel);
	if(temp4 == NULL) printf("\nError Occurs\n");
	else printf("\nDelete data successfully\n");
      }
      break;
      
    case 5:
      if(root == NULL) printf("The list is already empty\n");
      else{
	deletelist();
	printf("\nDelete list successfully\n");
      }
      break;
      
    case 6:
      if(root == NULL){
	printf("The list is empty\n");
	break;
      }
      else{
	printf("Enter the name you want to search: ");
	scanf("%s%*c",key);
	temp6 = search(key);
	if(temp6 == NULL){
	  printf("Cant find that person\n");
	  break;
	  }
	else{
	  tmp = temp6->data;
	  printf("\n%s    %s    %s\n\n",tmp.name,tmp.email,tmp.number);
	}
      }
      break;
      
    case 7:
      if(root == NULL) printf("The list is empty\n");
      else{
	count = countnode();
	printf("Number of elements: %d\n",count);
	showdata();
      }
      break;
      
    case 8:
      printf("\nQuit\n");
      break;
      
    default:  
      printf("Please choose from 1 to 8 only\n");
      break;
    }
  }while(choice != 8);
  
  fclose(f);
}

int countnode(){
  node * temp;
  int count = 0;
  temp = root;
  if(temp == NULL) return 0;
  else{
    while(temp != NULL){
      temp = temp->next;
      count++;
    }
  }
  free(temp);
  return count;
}

node * newnode(){
  node * new;
  new = (node*)malloc(sizeof(node));
  phonebook data;
  char s[size];
  fscanf(f,"%s",s);
  strcpy(data.name,s);
  fscanf(f,"%s",s);
  strcpy(data.email,s);
  fscanf(f,"%s",s);
  strcpy(data.number,s);
  new->data = data;
  new->next = NULL;
  return new;
}

node * traverse(int i){
  node * link;
  link = root;
  int pos=1;
  while(link != NULL){
    if(pos == i) return link;
    link = link->next;
    pos++;
  }
  return link;
}
    
void insertatpos(int i){
  node * link;
  node * temp;
  node * prev;
  node * pos;
  link = newnode();
  if(i == 1){
    temp = root;
    link->next = temp;
    root = link;
    cur = link;
  } 
  else if(i > 1 && i <= countnode(root)){
    prev = traverse(i-1);
    pos = traverse(i);
    link->next = pos;
    prev->next = link;
    
    printf("lol\n");
    cur = link;
    printf("lol\n");
  }
}

void insertafter(){
  node * link;
  link = newnode();
  if(root == NULL){
    root = link;
    cur = root;
  }
  else{
    link->next = cur->next;
    cur->next = link;
    cur = cur->next;
  }
}

void insertbefore(){
  node * link;
  node * prev;
  link = newnode();
  if(root == NULL){
    root = link;
    cur = root;
  }
  else{
    prev = root;
    if(prev == cur){
      link->next = prev;
      root = link;
      cur = link;
    }
    else{
      while(prev != NULL){
	printf("\n%s    %s    %s\n\n",(prev->data).name,(prev->data).email,(prev->data).number);
	if(prev->next == cur){
	  prev->next = link;
	  link->next = cur;
	  cur = link;
	}
	prev= prev->next;
      }
    }
  }
}

node * deletenode(int i){
  node * link;
  node * prev;
  if(i == 1){
    link = root;
    root = root->next;
    return link;
  }
  else if (i > 1 && i <= countnode(root)){
    link = traverse(i);
    prev = traverse(i-1);
    prev->next = link->next;
    return link;
  }
  else{
    return NULL;
  }
}

void deletelist(){
  while(root != NULL){
    node * link;
    link = root;
    free(link);
    root = root->next;
  }
}

node *search(char key[size]){
  node * link;
  link = (node*)malloc(sizeof(node));
  link = root;
  while(link != NULL){
    if(strcmp(link->data.name,key) == 0) return link;
    link = link->next;
  }
  return NULL;
}
    
void showdata(){
  node * link;
  link = root;
  while(link != NULL){
    printf("\n%s    %s    %s\n",(link->data).name,(link->data).email,(link->data).number);
    link = link->next;
  }
} 
