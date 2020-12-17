#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct block {
    int tag;
    struct block* next;
} block;


bool powerOfTwo(int n);
void decToBin(unsigned int x);
int binToDec(int x[], int length);
int binaryAddress[48];
int cacheHit = 0;
int cacheMiss = 0;
int memoryRead = 0;
int memoryWrite = 0;

int main(int argc, char* argv[]) {

    if (argc != 6) {
        printf("error\n");
        return 0;
    }
    int cacheSize = atoi(argv[1]);
    char* associativity = argv[2];
    char* replacePolicy = argv[3];
    int blockSize = atoi(argv[4]);

    if (!powerOfTwo(cacheSize)) {
        printf("error\n");
        return 0;
    }
    if (!powerOfTwo(blockSize)) {
        printf("error\n");
        return 0;
    }
    if (blockSize > cacheSize) {
        printf("error\n");
        return 0;
    }
    if (strcmp(associativity, "direct") != 0) {
        if (strcmp(associativity, "assoc") != 0) {
            if (associativity[5] != ':') {
                printf("error\n");
                return 0;
            }
        }
    }
    int n;
    if (associativity[5] == ':') {
        char temp[5];
        int j = 0;
        for (int i = 6; i < strlen(associativity); i++) {
            temp[j] = associativity[i];
            j++;
        }
        n = atoi(temp);
        if (!(powerOfTwo(n))) {
            printf("error\n");
            return 0;
        }
    }
    if (strcmp(replacePolicy, "lru") != 0) {
        if (strcmp(replacePolicy, "fifo") != 0) {
            printf("error\n");
            return 0;
        }
    }
    FILE* fp = fopen(argv[5], "r"); 
    if (fp == NULL) {
        printf("error\n");
        return 0;
    }
    
    int tagBits = 0;
    int setBits = 0;
    int blockBits = 0;
    int numLines = 0;
    if (strcmp(associativity, "direct") == 0) {
        blockBits = log(blockSize)/log(2);
        numLines = cacheSize/blockSize;
        setBits = log(numLines)/log(2);
        tagBits = 48 - (blockBits + setBits);
        // printf("%d\n", setBits);

        int cache[numLines];
        char pc[20];
        char op;
        unsigned long int address;
        while (fscanf(fp, "%s %c %lx", pc, &op, &address) == 3) {
            // printf("%s %c %lx", pc, op, address);
            unsigned int x = address;
            // printf("%u\n", x);
            decToBin(x);
            
            int tagArray[tagBits];
            for (int i = 0; i < tagBits; i++) {
                tagArray[i] = binaryAddress[i];
                // printf("%d", tagArray[i]);
            }
            // printf("\n");
            int tag = binToDec(tagArray, tagBits);
            // printf("%d\n", tag);
            int set[setBits];
            int i = tagBits;
            int j = 0;
            while (j < setBits) {
                set[j] = binaryAddress[i];
                // printf("%d", set[j]);
                j++;
                i++;
            }
            // printf("\n");
            int setIndex = binToDec(set, setBits);
            // printf("%d\n", setIndex);

            if (op == 'R') {
                if (cache[setIndex] != tag) {
                    cacheMiss++;
                    cache[setIndex] = tag;
                    memoryRead++;
                }
                else {
                    cacheHit++;
                }
            }
            else if (op == 'W') {
                if (cache[setIndex] != tag) {
                    cacheMiss++;
                    cache[setIndex] = tag;
                    memoryRead++;
                    memoryWrite++;
                }
                else {
                    cacheHit++;
                    memoryWrite++;
                }
            }
        }
    }
    else if (strcmp(associativity, "assoc") == 0) {
        blockBits = log(blockSize)/log(2);
        numLines = cacheSize/blockSize;
        tagBits = 48 - blockBits;
        // printf("%d\n", tagBits);

        char pc[20];
        char op;
        unsigned long int address;
        
        if (strcmp(replacePolicy, "fifo") == 0) {
            int assocSet[numLines];
            int firstIn = 0;
            while (fscanf(fp, "%s %c %lx", pc, &op, &address) == 3) {
                // printf("%s %c %lx", pc, op, address);
                unsigned int x = address;
                // printf("%u\n", x);
                decToBin(x);
                
                int tagArray[tagBits];
                for (int i = 0; i < tagBits; i++) {
                    tagArray[i] = binaryAddress[i];
                    // printf("%d", tagArray[i]);
                }
                // printf("\n");
                int tag = binToDec(tagArray, tagBits);
                // printf("%d\n", tag);

                bool notInSet = true;
                for (int i = 0; i < numLines; i++) {
                    if (assocSet[i] == tag) {
                        notInSet = false;
                    } 
                }
                if (op == 'R') {    
                    if (notInSet == true) {
                        cacheMiss++;
                        assocSet[firstIn] = tag;
                        firstIn++;
                        if (firstIn == numLines) {
                            firstIn = 0;
                        }
                        memoryRead++;
                    }
                    else {
                        cacheHit++;
                    }
                }
                else if (op == 'W') {
                    if (notInSet == true) {
                        cacheMiss++;
                        assocSet[firstIn] = tag;
                        firstIn++;
                        if (firstIn == numLines) {
                            firstIn = 0;
                        }
                        memoryRead++;
                        memoryWrite++;
                    }
                    else {
                        cacheHit++;
                        memoryWrite++;
                    }
                }
            }     
        }    
        else if (strcmp(replacePolicy, "lru") == 0) {
            int blockCount = 0;
            block* head = NULL;
            block* ptr = NULL;
            block* prev = NULL;
            block* mru = NULL;
            if (blockCount != numLines) {
                head = malloc(sizeof(block));
                head->next = NULL;                
                blockCount++;
                ptr = head;
                while (blockCount != numLines) {
                    ptr->next = malloc(sizeof(block));
                    ptr->tag = 0;
                    blockCount++;
                    ptr = ptr->next;
                    ptr->next = NULL;
                }
                ptr->tag = 0;
            }
            while (fscanf(fp, "%s %c %lx", pc, &op, &address) == 3) {
                unsigned int x = address;
                // printf("%u\n", x);
                decToBin(x);
                
                int tagArray[tagBits];
                for (int i = 0; i < tagBits; i++) {
                    tagArray[i] = binaryAddress[i];
                    // printf("%d", tagArray[i]);
                }
                // printf("\n");
                int tag = binToDec(tagArray, tagBits);
                // printf("%d\n", tag);

                bool breakOut = false;
                ptr = head;
                prev = NULL;
                if (op == 'R') {
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            block* ptr1 = ptr;
                            block* prev1 = NULL;
                            while (ptr1 != NULL) {
                                if (ptr1->tag == tag) {
                                    cacheHit++;
                                    if (ptr1->next == NULL) {
                                        breakOut = true;
                                        break;
                                    }
                                    else {
                                        mru = ptr1;
                                        prev1->next = ptr1->next;
                                        while (ptr1->next != NULL) {
                                            prev1 = ptr1;
                                            ptr1 = ptr1->next;
                                        }
                                        ptr1->next = mru;
                                        mru->next = NULL;
                                        breakOut = true;
                                        break;
                                    }
                                }
                                prev1 = ptr1;
                                ptr1 = ptr1->next;
                            }
                            if (breakOut == false) {
                                cacheMiss++;
                                memoryRead++;
                                if (numLines == 1) {
                                    ptr->tag = tag;
                                    break;
                                }
                                head = head->next;
                                ptr->tag = tag;
                                block* temp = ptr;
                                while (ptr->next != NULL) {
                                    ptr = ptr->next;
                                }
                                ptr->next = temp;
                                temp->next = NULL;
                                break;
                            }
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            if (numLines == 1) break;
                            if (prev == NULL) {
                                head = head->next;
                                mru = ptr;
                                while (ptr->next != NULL) {
                                    prev = ptr;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                            else if (ptr->next == NULL) {
                                break;
                            }
                            else {
                                mru = ptr;
                                prev->next = ptr->next;
                                while (ptr->next != NULL) {
                                    prev = prev->next;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            if (numLines == 1) {
                                ptr->tag = tag;
                                break;
                            }
                            block* temp = head;
                            head = head->next;
                            free(temp);
                            block* new = malloc(sizeof(block));
                            new->tag = tag;
                            new->next = NULL;
                            ptr->next = new;
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }
                }
                else if (op == 'W') {
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            block* ptr1 = ptr;
                            block* prev1 = NULL;
                            while (ptr1 != NULL) {
                                if (ptr1->tag == tag) {
                                    cacheHit++;
                                    memoryWrite++;
                                    if (ptr1->next == NULL) {
                                        breakOut = true;
                                        break;
                                    }
                                    else {
                                        mru = ptr1;
                                        prev1->next = ptr1->next;
                                        while (ptr1->next != NULL) {
                                            prev1 = ptr1;
                                            ptr1 = ptr1->next;
                                        }
                                        ptr1->next = mru;
                                        mru->next = NULL;
                                        breakOut = true;
                                        break;
                                    }
                                }
                                prev1 = ptr1;
                                ptr1 = ptr1->next;
                            }
                            if (breakOut == false) {
                                cacheMiss++;
                                memoryRead++;
                                memoryWrite++;
                                if (numLines == 1) {
                                    ptr->tag = tag;
                                    break;
                                }
                                head = head->next;
                                ptr->tag = tag;
                                block* temp = ptr;
                                while (ptr->next != NULL) {
                                    ptr = ptr->next;
                                }
                                ptr->next = temp;
                                temp->next = NULL;
                                break;
                            }
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            memoryWrite++;
                            if (numLines == 1) break;
                            if (prev == NULL) {
                                head = head->next;
                                mru = ptr;
                                while (ptr->next != NULL) {
                                    prev = ptr;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                            else if (ptr->next == NULL) {
                                break;
                            }
                            else {
                                mru = ptr;
                                prev->next = ptr->next;
                                while (ptr->next != NULL) {
                                    prev = prev->next;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            memoryWrite++;
                            if (numLines == 1) {
                                ptr->tag = tag;
                                break;
                            }
                            block* temp = head;
                            head = head->next;
                            free(temp);
                            block* new = malloc(sizeof(block));
                            new->tag = tag;
                            new->next = NULL;
                            ptr->next = new;
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }
                }
            }
            //freeing the set
            ptr = head;
            while (ptr != NULL) {
                // printf("%d\n", ptr->tag);
                block* temp = ptr;
                ptr = ptr->next;
                free(temp);
            }
        }
    }
    else if (associativity[5] == ':') {
        if (cacheSize == blockSize) {
            printf("error\n");
            return 0;
        }
        blockBits = log(blockSize)/log(2);
        numLines = cacheSize/blockSize;
        int numSets = numLines/n;
        setBits = log(numSets)/log(2);
        tagBits = 48 - (blockBits + setBits);
        // printf("%d\n", tagBits);

        char pc[20];
        char op;
        unsigned long int address;

        if (strcmp(replacePolicy, "fifo") == 0) {
            int blockCount = 0;
            block* cache[numSets];
            block* ptr = NULL;
            for (int i = 0; i < numSets; i++) {
                blockCount = 0;
                block* newBlock = malloc(sizeof(block));
                blockCount++;
                newBlock->tag = 0;
                newBlock->next = NULL;
                cache[i] = newBlock;
                ptr = newBlock;
                while (blockCount != n) {
                    block* newBlock = malloc(sizeof(block));
                    blockCount++;
                    newBlock->tag = 0;
                    ptr->next = newBlock;
                    ptr = ptr->next;
                    ptr->next = NULL;
                }
            }

            while (fscanf(fp, "%s %c %lx", pc, &op, &address) == 3) {
                // printf("%s %c %lx", pc, op, address);
                unsigned int x = address;
                // printf("%u\n", x);
                decToBin(x);
                
                int tagArray[tagBits];
                for (int i = 0; i < tagBits; i++) {
                    tagArray[i] = binaryAddress[i];
                    // printf("%d", tagArray[i]);
                }
                // printf("\n");
                int tag = binToDec(tagArray, tagBits);
                // printf("%d\n", tag);
                int set[setBits];
                int i = tagBits;
                int j = 0;
                while (j < setBits) {
                    set[j] = binaryAddress[i];
                    // printf("%d", set[j]);
                    j++;
                    i++;
                }
                // printf("\n");
                int setIndex = binToDec(set, setBits);
                // printf("%d\n", setIndex);

                if (op == 'R') {
                    ptr = cache[setIndex];
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            cacheMiss++;
                            memoryRead++;
                            ptr->tag = tag;
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            break;
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            block* cachePtr = cache[setIndex];
                            cachePtr->tag = tag;
                            ptr->next = cachePtr;
                            cache[setIndex] = cachePtr->next;
                            cachePtr->next = NULL;
                            break;
                        }
                        ptr = ptr->next;
                    }
                }
                else if (op == 'W') {
                    ptr = cache[setIndex];
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            cacheMiss++;
                            memoryRead++;
                            memoryWrite++;
                            ptr->tag = tag;
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            memoryWrite++;
                            break;
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            memoryWrite++;
                            block* cachePtr = cache[setIndex];
                            cachePtr->tag = tag;
                            ptr->next = cachePtr;
                            cache[setIndex] = cachePtr->next;
                            cachePtr->next = NULL;
                            break;
                        }
                        ptr = ptr->next;
                    }
                }

            }

            //prints the cache
            // for (int i = 0; i < numSets; i++) {
            //     ptr = cache[i];
            //     while (ptr != NULL) {
            //         printf("%d ", ptr->tag);
            //         ptr = ptr->next;
            //     }
            //     printf("\n");
            // }


            //freeing cache
            for (int i = 0; i < numSets; i++) {
                block* ptr = cache[i];
                while (ptr != NULL) {
                    block* temp = ptr;
                    ptr = ptr->next;
                    free(temp);
                }
            }

        }
        else if (strcmp(replacePolicy, "lru") == 0) {
            int blockCount = 0;
            block* cache[numSets];
            block* ptr = NULL;
            block* prev = NULL;
            block* mru = NULL;
            for (int i = 0; i < numSets; i++) {
                blockCount = 0;
                block* newBlock = malloc(sizeof(block));
                blockCount++;
                newBlock->tag = 0;
                newBlock->next = NULL;
                cache[i] = newBlock;
                ptr = newBlock;
                while (blockCount != n) {
                    block* newBlock = malloc(sizeof(block));
                    blockCount++;
                    newBlock->tag = 0;
                    ptr->next = newBlock;
                    ptr = ptr->next;
                    ptr->next = NULL;
                }
            }

            while (fscanf(fp, "%s %c %lx", pc, &op, &address) == 3) {
                // printf("%s %c %lx", pc, op, address);
                unsigned int x = address;
                // printf("%u\n", x);
                decToBin(x);
                
                int tagArray[tagBits];
                for (int i = 0; i < tagBits; i++) {
                    tagArray[i] = binaryAddress[i];
                    // printf("%d", tagArray[i]);
                }
                // printf("\n");
                int tag = binToDec(tagArray, tagBits);
                // printf("%d\n", tag);
                int set[setBits];
                int i = tagBits;
                int j = 0;
                while (j < setBits) {
                    set[j] = binaryAddress[i];
                    // printf("%d", set[j]);
                    j++;
                    i++;
                }
                // printf("\n");
                int setIndex = binToDec(set, setBits);
                // printf("%d\n", setIndex);

                bool breakOut = false;

                if (op == 'R') {
                    ptr = cache[setIndex];
                    prev = NULL;
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            if (n == 1) {
                                cacheMiss++;
                                memoryRead++;
                                ptr->tag = tag;
                                break;
                            }
                            block* ptr1 = ptr;
                            block* prev1 = NULL;
                            while (ptr1 != NULL) {
                                if (ptr1->tag == tag) {
                                    cacheHit++;
                                    if (ptr1->next == NULL) {
                                        breakOut = true;
                                        break;
                                    }
                                    else {
                                        mru = ptr1;
                                        prev1->next = ptr1->next;
                                        while (ptr1->next != NULL) {
                                            prev1 = ptr1;
                                            ptr1 = ptr1->next;
                                        }
                                        ptr1->next = mru;
                                        mru->next = NULL;
                                        breakOut = true;
                                        break;
                                    }
                                }
                                prev1 = ptr1;
                                ptr1 = ptr1->next;
                            }
                            if (breakOut == false) {
                                cacheMiss++;
                                memoryRead++;
                                block* cachePtr = cache[setIndex];
                                cachePtr->tag = tag;
                                while (ptr->next != NULL) {
                                    ptr = ptr->next;
                                }
                                ptr->next = cachePtr;
                                cache[setIndex] = cachePtr->next;
                                cachePtr->next = NULL;
                                break;                       
                            }
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            if (n == 1) break;
                            if (prev == NULL) {
                                cache[setIndex] = ptr->next;
                                mru = ptr;
                                while (ptr->next != NULL) {
                                    prev = ptr;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                            else if (ptr->next == NULL) {
                                break;
                            }
                            else {
                                mru = ptr;
                                prev->next = ptr->next;
                                while (ptr->next != NULL) {
                                    prev = prev->next;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            if (n == 1) {
                                ptr->tag = tag;
                                break;
                            }
                            block* cachePtr = cache[setIndex];
                            cachePtr->tag = tag;
                            ptr->next = cachePtr;
                            cache[setIndex] = cachePtr->next;
                            cachePtr->next = NULL;
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }
                }
                else if (op == 'W') {
                    ptr = cache[setIndex];
                    prev = NULL;
                    while (ptr != NULL) {
                        if (ptr->tag == 0) {
                            if (n == 1) {
                                cacheMiss++;
                                memoryRead++;
                                memoryWrite++;
                                ptr->tag = tag;
                                break;
                            }
                            block* ptr1 = ptr;
                            block* prev1 = NULL;
                            while (ptr1 != NULL) {
                                if (ptr1->tag == tag) {
                                    cacheHit++;
                                    memoryWrite++;
                                    if (ptr1->next == NULL) {
                                        breakOut = true;
                                        break;
                                    }
                                    else {
                                        mru = ptr1;
                                        prev1->next = ptr1->next;
                                        while (ptr1->next != NULL) {
                                            prev1 = ptr1;
                                            ptr1 = ptr1->next;
                                        }
                                        ptr1->next = mru;
                                        mru->next = NULL;
                                        breakOut = true;
                                        break;
                                    }
                                }
                                prev1 = ptr1;
                                ptr1 = ptr1->next;
                            }
                            if (breakOut == false) {
                                cacheMiss++;
                                memoryRead++;
                                memoryWrite++;
                                block* cachePtr = cache[setIndex];
                                cachePtr->tag = tag;
                                while (ptr->next != NULL) {
                                    ptr = ptr->next;
                                }
                                ptr->next = cachePtr;
                                cache[setIndex] = cachePtr->next;
                                cachePtr->next = NULL;
                                break;
                            }
                            break;
                        }
                        else if (ptr->tag == tag) {
                            cacheHit++;
                            memoryWrite++;
                            if (n == 1) break;
                            if (prev == NULL) {
                                cache[setIndex] = ptr->next;
                                mru = ptr;
                                while (ptr->next != NULL) {
                                    prev = ptr;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                            else if (ptr->next == NULL) {
                                break;
                            }
                            else {
                                mru = ptr;
                                prev->next = ptr->next;
                                while (ptr->next != NULL) {
                                    prev = prev->next;
                                    ptr = ptr->next;
                                }
                                ptr->next = mru;
                                mru->next = NULL;
                                break;
                            }
                        }
                        else if (ptr->next == NULL) {
                            cacheMiss++;
                            memoryRead++;
                            memoryWrite++;
                            if (n == 1) {
                                ptr->tag = tag;
                                break;
                            }
                            block* cachePtr = cache[setIndex];
                            cachePtr->tag = tag;
                            ptr->next = cachePtr;
                            cache[setIndex] = cachePtr->next;
                            cachePtr->next = NULL;
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }
                }
            }

            //prints the cache
            // for (int i = 0; i < numSets; i++) {
            //     ptr = cache[i];
            //     while (ptr != NULL) {
            //         printf("%d ", ptr->tag);
            //         ptr = ptr->next;
            //     }
            //     printf("\n");
            // }


            //freeing cache
            for (int i = 0; i < numSets; i++) {
                block* ptr = cache[i];
                while (ptr != NULL) {
                    block* temp = ptr;
                    ptr = ptr->next;
                    free(temp);
                }
            }

        }


    }

    printf("Memory reads: %d\n", memoryRead);
    printf("Memory writes: %d\n", memoryWrite);
    printf("Cache hits: %d\n", cacheHit);
    printf("Cache misses: %d\n", cacheMiss);
}


bool powerOfTwo(int n) {
    if (n == 0) {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

void decToBin(unsigned int x) { 
    for (int i = 0; i < 48; i++) {
        binaryAddress[i] = 0;
    } 
  
    int i = 0; 
    while (x > 0) { 
        binaryAddress[i] = x % 2; 
        x = x / 2; 
        i++; 
    } 
  
    int temp;
    int start = 0;
    int end = 47;
    while (start < end)
    {
        temp = binaryAddress[start];   
        binaryAddress[start] = binaryAddress[end];
        binaryAddress[end] = temp;
        start++;
        end--;
    }
    // for (int i = 0; i < 48; i++) {
    //     printf("%d", binaryAddress[i]);
    // }
    // printf("\n");
}

int binToDec(int x[], int length) {
    int dec = 0;
    int j = 0;
    for (int i = length - 1; i >= 0; i--) {
        dec += x[i]*pow(2, j);
        j++;
    }
    return dec;
}
