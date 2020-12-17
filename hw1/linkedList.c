#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

struct Node* front = NULL;
int numNodes = 0;

void insert(struct Node* newNode, int data) {
 
  if(front == NULL){
    front = newNode;
    numNodes++;
    return;
  }
  
  struct Node* ptr = front;
  struct Node* prev = NULL;
  
  while(ptr != NULL){
    if(data <= ptr->data) { 
      if(prev == NULL) {
        newNode->next = ptr;
        front = newNode;
        numNodes++;
        return;
      }
      else {
        prev->next = newNode;
        newNode->next = ptr;
        numNodes++;
	      return;
      }
    }
    else if(data > ptr->data) {
      if(ptr->next == NULL) {
        ptr->next = newNode;
        numNodes++;
        return;
      }
      else{
        prev = ptr;
        ptr = ptr->next;
      }
    }
  }
  
}

void delete(int val) {
  if (front == NULL) {
    return;
  }
  if (front->data == val) {
    struct Node *temp = front;
    front = front->next;
    free(temp);
    numNodes--;
    return;
  }
  struct Node* ptr = front;
  struct Node* prev = NULL;
  
  while (ptr != NULL) {
    if (ptr->data == val) {
      prev->next = ptr->next;
      free(ptr);
      numNodes--;
      return;
    }
    else {
      prev = ptr;
      ptr = ptr->next;
    }
  }
 
}

void printNoDuplicates() {
  if (front == NULL) {
    return;
  }
  struct Node *ptr = front;
  struct Node *next;

  while (ptr->next != NULL) {
    if (ptr->data == ptr->next->data) {
      next = ptr->next->next; 
      free(ptr->next); 
      ptr->next = next;   
    } 
    else { 
      ptr = ptr->next;  
    } 
  }

  ptr = front;
  while (ptr != NULL) {
    printf("%d\t", ptr->data);
    ptr = ptr->next;
  }
  printf("\n\n");
}


int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("error\n");
    return 0;
  }
  
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("error\n");
    return 0;
  }
  char action;
  int num;
  

  while (1) {
    int n = fscanf(fp, "%c\t%d\n", &action, &num);
    if (n != 2) {
      break;
    }
    if (action == 'i') {
      struct Node* new = malloc(sizeof(struct Node));
      new->data = num;
      new->next = NULL;
      insert(new, num);
    }
    else if (action == 'd') {
      delete(num);
    }
  
  }
    
  
  printf("%d\n", numNodes);
  printNoDuplicates();

  //clean-up
  struct Node* curr = front;
  while (curr != NULL) {
    struct Node* temp = curr;
    curr = curr->next;
    free(temp);
  }


  fclose(fp);
  
}
