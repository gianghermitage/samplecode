#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//declare node//

typedef struct address_t{
  char name[20];
  char tell[11];
  char email[25];

}address;

struct list_el{
  address addr;
  struct list_et *next;
};

typedef struct list_el node_addr;

//make new node//

node_addr *root=NULL;
node_addr *cur = NULL;
node_addr *prev = NULL;

node_addr* makeNewNode(address addr){
  node_addr *new = (node_addr*)malloc(sizeof(node_addr));
  new->addr = addr;
  new->next = NULL;

  return new;
}

//read node//

address readNode(){
  address tmp;
  printf("Name: ");
  gets(tmp.name);
  printf("Telephone number: ");
  gets(tmp.tell);
  printf("Email: ");
  gets(tmp.email);

  return tmp;
}

//display node//

void displayNode(node_addr* ptr){
  if(ptr==NULL){
    printf("Error pointer NULL\n");
    return;
  }
  address tmp = ptr->addr;
  printf("%-20s\t%-15s\t%-30s %p\n",tmp.name,tmp.tell,tmp.email,ptr->next);
}

//insert at the head of list//

void insertHead(address addr){
  node_addr *new = makeNewNode(addr);
  new->next = root;
  root = new;
  cur = root;

}

//insert at the given position//

void insertAfter(address addr){
  node_addr *new = makeNewNode(addr);

  if(root==NULL){
    //there is no element in the list//
    root = new;
    cur = root;
  }
  else{
    new->next = cur->next;
    cur->next = new;
    //prev=cur//
    cur = cur->next;
  }
}

void insertBefore(address addr){
  node_addr *new = makeNewNode(addr);

  if(root==NULL){
    root = new;
    cur = root;
  }
  else{
    prev->next = new;
    new->next = cur;
    cur = new;
  }
}

void traversing(){
  node_addr *new;
  new = root;
  address tmp;
  tmp = new->addr;
  
  while(new!=NULL){
    printf("%-20s\t%-15s\t%-30s %p\n",tmp.name,tmp.tell,tmp.email,new->next);
    new=new->next;
  }
}

void freeList(){
  node_addr* to_free;
  to_free = root;
  while(to_free != NULL){
    root = root->next;
    free(to_free);
    to_free = root;
  }
}

node_addr* insertAtPosition(node_addr *root,address addr, int n){
  node_addr *new,*link;
  link=root;
  int i=1;
  
  if(n<1 || n> strlen(root)+1) printf("Inavailable position\n");
  else{
    new=makeNewNode(addr);
    if(n==1) insertHead(addr);
    else{
      while(link!=NULL && i!= n-1){
	i++;
	link=link->next;
      }
      new->next = link->next;
      link->next = new;
    }
  }

  return new;
}
void deleteHead(){
  node_addr *del = root;
  root = del->next;
  free(del);
  cur = root;
};

node_addr* deleteAtPosition(int n){
  node_addr *link;
  link=root;
  int i=1;
  address addr;

  if(n<1 || n>strlen(root)) printf("Inavailable position\n");
  else{
    if(n==1) deleteHead(addr);
    else{
      while(link!=NULL && i!=n-1){
	link=link->next;
	i++;
      }
      link = link->next;
    }
  }

  return link;
}
node_addr *reverseList(node_addr *root){
  cur = prev;
  while(root!=NULL){
    cur = root;
    root=root->next;
    cur->next = prev;
    prev= cur;
  }

  return prev;
}


/*deleteele*/
//prev>next = cur->next; free(cur); cur = prev->next;//


  
    
