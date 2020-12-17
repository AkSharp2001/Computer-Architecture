#include <stdio.h>
#include <stdlib.h>

struct BSTnode {
    int data;
    struct BSTnode *left;
    struct BSTnode *right;
};

struct BSTnode *root = NULL;

struct BSTnode* insert(struct BSTnode *root, int data) {
    if (root == NULL) {
        struct BSTnode *newNode = malloc(sizeof(struct BSTnode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }   
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

void inorder(struct BSTnode *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d\t", root->data);
    inorder(root->right);
}

void cleanUp(struct BSTnode *root) {
    if (root == NULL) {
        return;
    }
    cleanUp(root->left);
    cleanUp(root->right);
    free(root);
}

int main(int argc, char* argv[])
{
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
            root = insert(root, num);
        }
    }
    
    inorder(root);
    printf("\n");
    cleanUp(root);
    fclose(fp);

}