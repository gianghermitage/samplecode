#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define namesize 20
#define emailsize 40
#define phonesize 10
#define queuesize 5


typedef struct address
{
  char name[namesize];
  char email[emailsize];
  char phone[phonesize];
}phonebook;

phonebook list[100];

typedef struct queues{
  phonebook elements[queuesize];
  int front;
  int rear;
}queue;

int count = 0;
FILE * f1;
//FILE * f2;

void printdata(queue q,int n);

void adddata(){
  int i;
  char s[100];
  for(i = 0;i<100;i++){
    fscanf(f1,"%s",s);
    strcpy(list[i].name,s);
    fscanf(f1,"%s",s);
    strcpy(list[i].email,s);
    fscanf(f1,"%s",s);
    strcpy(list[i].phone,s);
  }
}

void makenull_q(queue * q);
int check_empty_q(queue q);
int check_full_q(queue q);
void enqueue(phonebook e,queue *q);
void dequeue(queue * q);

int search(queue *q, int count, char key[namesize]);

  int main(int argc, char const *argv[])
{
  f1 = fopen("phonebook.txt","r");
  if(f1 == NULL){
    printf("\nError open phonebook file\n");
    exit(1);
  }

  adddata();

  queue q;
  makenull_q(&q);
	
  int i= 0;
  int choice;
  char namesearch[namesize];
	
  do{
    printf("Menu\n");
    printf("1.Enqueue\n");
    printf("2.Dequeue\n");
    printf("3.Show queue\n");
    printf("4.Search by name\n");
    printf("5.Quit\n");
    scanf("%d%*c",&choice);
	
    switch(choice){

    case 1:
      enqueue(list[i],&q);
      printf("front = %d\n",q.front);
      printf("rear = %d\n",q.rear);
      i++;
      break;
	
    case 2:
      // f2 = fopen("queue.txt","w");
      dequeue(&q);
      printf("front = %d\n",q.front);
      printf("rear = %d\n",q.rear);
      break;
	
    case 3:
      if(q.front == -1){
	printf("\nQueue is empty\n\n");
      }
      else{
	printf("\n\nPhonebook\n\n");
	for(int j = q.front;j <= q.rear;j++){
	  printf("%s   ",q.elements[j].name);
	  printf("%s   ",q.elements[j].email);
	  printf("%s\n",q.elements[j].phone);
	}
	printf("\n\n");
      }
      break;
	
    case 4:
      
      printf("Enter the name:");
      scanf("%[^\n]%*c",namesearch);
      int k = search(&q,10,namesearch);
      if(k == -1){
	printf("\nThe item you are searching for is not exist\n");
	  }
      else{
	printf("%s",q.elements[k].name);
	printf("%s",q.elements[k].email);
	printf("%s",q.elements[k].phone);
      }
      break;

    case 5:
      printf("\nQuit\n");
      break;

    }
  }while(choice != 5);
  fclose(f1);
}

/*void printdata(queue q,int n){
  fprintf(f2,"%s",q.elements[n].name);
  fprintf(f2,"%s",q.elements[n].email);
  fprintf(f2,"%s",q.elements[n].phone);
  }*/

void makenull_q(queue * q){
  q->front = -1;
  q->rear = -1;
}

int check_empty_q(queue q){
  if (q.front == -1) return 1;
  else return 0;
}

int check_full_q(queue q){
  if((q.rear - q.front + 1)% queuesize == 0) return 1;
  else return 0;
}

void enqueue(phonebook e, queue *q){
  int i;
  if(check_full_q(*q) == 1){
    printf("\nQueue is full\n\n");
  }
  else{
    if(check_empty_q(*q) == 1){ 
      q->front = 0;
    }
    q->rear = q->rear + 1;

    strcpy(q->elements[q->rear].name,e.name);
    strcpy(q->elements[q->rear].email,e.email);
    strcpy(q->elements[q->rear].phone,e.phone);
  }
}

void dequeue(queue *q){
  if(check_empty_q(*q) == 1){
    printf("\nQueue is empty\n\n");
  }
  else{
    printf("%s   ",q->elements[q->front].name);
    printf("%s   ",q->elements[q->front].email);
    printf("%s\n",q->elements[q->front].phone);
    q->front = q->front + 1;
		
    if(q->front > q->rear)
      makenull_q(q);
  }
}

int search(queue *q, int count, char key[namesize]){
  int k;
  for(k=0;k<5;k++){
    if(strcmp(key,q->elements[k].name) == 0)
    return k;
  }
  return -1;
}
