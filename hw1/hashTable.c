#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

struct Node *hashTable[10000];
int collision = 0;
int searchSuccess = 0;

int hashFunc(int value) {
    value = value % 10000;
    if (value < 0) {
        value += 10000;
    }
    return value;
}

void insert(int key, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (hashTable[key] == NULL) {
        hashTable[key] = newNode;
        return;
    }
    else {
        collision++;
        struct Node *ptr = hashTable[key];
        while (ptr->next != NULL) {
            if (ptr->data == value) {
                free(newNode);
                return;
            }
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
   
}

void search(int key, int value) {
    struct Node *ptr = hashTable[key];
    if (ptr == NULL) {
        return;
    }
    while (ptr != NULL) {
        if (ptr->data == value) {
            searchSuccess++;
            return;
        }
        ptr = ptr->next;
    }
}

int main(int argc, char* argv[])
{
  
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 0;
    }
    char action;
    int num;
    int key;
        
    while (1) {
        int n = fscanf(fp, "%c\t%d\n", &action, &num);
        key = hashFunc(num);
        if (n != 2){
            break;
        }
        if (action == 'i') {
            insert(key, num);
        }
        if (action == 's') {
            search(key, num);
        }
    }


    printf("%d\n", collision);
    printf("%d\n", searchSuccess);
        

    for (int i = 0; i < 10000; i ++) {
        if (hashTable[i] != NULL) {
            struct Node *ptr = hashTable[i];
            while (ptr != NULL) {
                struct Node* temp = ptr;
                ptr = ptr->next;
                free(temp);
            }
        }
    }
    
    fclose(fp);
}
