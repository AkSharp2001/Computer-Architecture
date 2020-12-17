#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        return 0;
    }
    FILE* fp = fopen(argv[1], "r"); 
    if (fp == NULL) {
        return 0;
    }

    char array[100][50];
    int i = 0;
    while(fgets(array[i], 100, fp) != NULL) 
	{
        array[i][strlen(array[i]) - 1] = '\0';
        i++;
    }
    int totalLines = i;
    // printf("%d\n", totalLines);

    // for (int i = 0; i < totalLines; i++) {
    //     printf("%s\n", array[i]);
    // }
    
    char* arr[100][100];
    int j = 0;
    for (int i = 0; i < totalLines; i++) {
        char *ptr = strtok(array[i], " ");
        j = 0;
        while (ptr != NULL) {
            arr[i][j++] = ptr;
            ptr = strtok(NULL, " ");
        }
    }

    // for (int i = 0; i < totalLines; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         printf("%s ", arr[i][j]);
    //     }
    //     printf("\n");
    // }

    int numInputs = atoi(arr[0][1]);
    int numOutputs = atoi(arr[1][1]);
    int numLines = (int) pow(2, numInputs);
    int output[numLines][numOutputs];
    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < numOutputs; j++) {
            output[i][j] = 0;
        }
    }
    int input[numInputs];
    // for (i = 0; i < numInputs; i++) {
    //     input[i] = 0;
    // }

    char* inputVar[numInputs];
    i = 0;
    j = 2;
    while (arr[0][j] != NULL) {
        inputVar[i++] = arr[0][j++];
    }
    
    char* outputVar[numOutputs];
    i = 0;
    j = 2;
    while (arr[1][j] != NULL) {
        outputVar[i++] = arr[1][j++];
    }

    int numTemp = 0;
    char* tempVar[16];
    int count = 0;
    i = 2;
    while (i < totalLines) {
        j = 0;
        while (arr[i][j] != NULL) {
            if (arr[i][j+1] == NULL) {
                if (arr[i][j][0] >= 'a' && arr[i][j][0] <= 'z') {
                    // printf("%s ", arr[i][j]);
                    tempVar[count++] = arr[i][j];
                    numTemp = count;
                }
            }
            j++;
        }
        i++;
    }
    
    int temp[numTemp];
    for (int i = 0; i < numTemp; i++) {
        temp[i] = 0;
    }

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < numInputs; j++) {
            int v = i & 1 << (numInputs - 1 - j);
            if (v == 0) {
                input[j] = 0;
                // printf("%d ", input[j]);
            }
            else {
                input[j] = 1;
                // printf("%d ", input[j]);
            }
        }

        for (int k = 2; k < totalLines; k++) {
            if (strcmp(arr[k][0], "NOT") == 0) {
                bool isTemp = false;
                int varIndex1 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    isTemp = true;
                    for (int m = 0; m < numTemp; m++) {
                        if (strcmp(arr[k][1], tempVar[m]) == 0) {
                            varIndex1 = m;
                        }
                    }
                }
                else {
                    for (int m = 0; m < numInputs; m++) {
                        if (strcmp(arr[k][1], inputVar[m]) == 0) {
                            varIndex1 = m;
                        }
                    }
                }
                if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][2], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (isTemp == false) {
                        if (input[varIndex1] == 0) {
                            temp[outIndex] = 1;
                        }
                        else {
                            temp[outIndex] = 0;
                        }
                    }
                    else {
                        if (temp[varIndex1] == 0) {
                            temp[outIndex] = 1;
                        }
                        else {
                            temp[outIndex] = 0;
                        }
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][2], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (isTemp == false) {
                        if (input[varIndex1] == 0) {
                            output[i][outIndex] = 1;
                        }
                        else {
                            output[i][outIndex] = 0;
                        }
                    }
                    else {
                        if (temp[varIndex1] == 0) {
                            output[i][outIndex] = 1;
                        }
                        else {
                            output[i][outIndex] = 0;
                        }
                    }
                }
            }
            else if (strcmp(arr[k][0], "AND") == 0) {
                bool firstIsTemp = false;
                bool secIsTemp = false;
                int varIndex1 = 0;
                int varIndex2 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    firstIsTemp = true;
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                else {
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                if (arr[k][3][0] >= 'a' && arr[k][3][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][3], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        temp[outIndex] = input[varIndex1] & input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        temp[outIndex] = temp[varIndex1] & temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        temp[outIndex] = temp[varIndex1] & input[varIndex2];
                    }
                    else {
                        temp[outIndex] = input[varIndex1] & temp[varIndex2];
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][3], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        output[i][outIndex] = input[varIndex1] & input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        output[i][outIndex] = temp[varIndex1] & temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        output[i][outIndex] = temp[varIndex1] & input[varIndex2];
                    }
                    else {
                        output[i][outIndex] = input[varIndex1] & temp[varIndex2];
                    }
                }
            }
            else if (strcmp(arr[k][0], "OR") == 0) {
                bool firstIsTemp = false;
                bool secIsTemp = false;
                int varIndex1 = 0;
                int varIndex2 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    firstIsTemp = true;
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                else {
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                if (arr[k][3][0] >= 'a' && arr[k][3][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][3], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        temp[outIndex] = input[varIndex1] | input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        temp[outIndex] = temp[varIndex1] | temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        temp[outIndex] = temp[varIndex1] | input[varIndex2];
                    }
                    else {
                        temp[outIndex] = input[varIndex1] | temp[varIndex2];
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][3], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        output[i][outIndex] = input[varIndex1] | input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        output[i][outIndex] = temp[varIndex1] | temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        output[i][outIndex] = temp[varIndex1] | input[varIndex2];
                    }
                    else {
                        output[i][outIndex] = input[varIndex1] | temp[varIndex2];
                    }
                }
            }
            else if (strcmp(arr[k][0], "NAND") == 0) {
                bool firstIsTemp = false;
                bool secIsTemp = false;
                int varIndex1 = 0;
                int varIndex2 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    firstIsTemp = true;
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                else {
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                if (arr[k][3][0] >= 'a' && arr[k][3][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][3], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        temp[outIndex] = input[varIndex1] & input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        temp[outIndex] = temp[varIndex1] & temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        temp[outIndex] = temp[varIndex1] & input[varIndex2];
                    }
                    else {
                        temp[outIndex] = input[varIndex1] & temp[varIndex2];
                    }
                    if (temp[outIndex] == 0) {
                        temp[outIndex] = 1;
                    }
                    else {
                        temp[outIndex] = 0;
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][3], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        output[i][outIndex] = input[varIndex1] & input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        output[i][outIndex] = temp[varIndex1] & temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        output[i][outIndex] = temp[varIndex1] & input[varIndex2];
                    }
                    else {
                        output[i][outIndex] = input[varIndex1] & temp[varIndex2];
                    }
                    if (output[i][outIndex] == 0) {
                        output[i][outIndex] = 1;
                    }
                    else {
                        output[i][outIndex] = 0;
                    }
                }
            }
            else if (strcmp(arr[k][0], "NOR") == 0) {
                bool firstIsTemp = false;
                bool secIsTemp = false;
                int varIndex1 = 0;
                int varIndex2 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    firstIsTemp = true;
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                else {
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                if (arr[k][3][0] >= 'a' && arr[k][3][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][3], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        temp[outIndex] = input[varIndex1] | input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        temp[outIndex] = temp[varIndex1] | temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        temp[outIndex] = temp[varIndex1] | input[varIndex2];
                    }
                    else {
                        temp[outIndex] = input[varIndex1] | temp[varIndex2];
                    }
                    if (temp[outIndex] == 0) {
                        temp[outIndex] = 1;
                    }
                    else {
                        temp[outIndex] = 0;
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][3], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        output[i][outIndex] = input[varIndex1] | input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        output[i][outIndex] = temp[varIndex1] | temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        output[i][outIndex] = temp[varIndex1] | input[varIndex2];
                    }
                    else {
                        output[i][outIndex] = input[varIndex1] | temp[varIndex2];
                    }
                    if (output[i][outIndex] == 0) {
                        output[i][outIndex] = 1;
                    }
                    else {
                        output[i][outIndex] = 0;
                    }
                }
            }
            else if (strcmp(arr[k][0], "XOR") == 0) {
                bool firstIsTemp = false;
                bool secIsTemp = false;
                int varIndex1 = 0;
                int varIndex2 = 0;
                int outIndex = 0;
                if (arr[k][1][0] >= 'a' && arr[k][1][0] <= 'z') {
                    firstIsTemp = true;
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][1], tempVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                else {
                    if (arr[k][2][0] >= 'a' && arr[k][2][0] <= 'z') {
                        secIsTemp = true;
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                        }
                        for (int m = 0; m < numTemp; m++) {
                            if (strcmp(arr[k][2], tempVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                    else {
                        for (int m = 0; m < numInputs; m++) {
                            if (strcmp(arr[k][1], inputVar[m]) == 0) {
                                varIndex1 = m;
                            }
                            if (strcmp(arr[k][2], inputVar[m]) == 0) {
                                varIndex2 = m;
                            }
                        }
                    }
                }
                if (arr[k][3][0] >= 'a' && arr[k][3][0] <= 'z') {
                    for (int n = 0; n < numTemp; n++) {
                        if (strcmp(arr[k][3], tempVar[n]) == 0) {
                            outIndex = n;
                        }
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        temp[outIndex] = input[varIndex1] ^ input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        temp[outIndex] = temp[varIndex1] ^ temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        temp[outIndex] = temp[varIndex1] ^ input[varIndex2];
                    }
                    else {
                        temp[outIndex] = input[varIndex1] ^ temp[varIndex2];
                    }
                }
                else {
                    for (int n = 0; n < numOutputs; n++) {
                        if (strcmp(arr[k][3], outputVar[n]) == 0) {
                            outIndex = n;
                        } 
                    }
                    if (firstIsTemp == false && secIsTemp == false) {
                        output[i][outIndex] = input[varIndex1] ^ input[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == true) {
                        output[i][outIndex] = temp[varIndex1] ^ temp[varIndex2];
                    }
                    else if (firstIsTemp == true && secIsTemp == false) {
                        output[i][outIndex] = temp[varIndex1] ^ input[varIndex2];
                    }
                    else {
                        output[i][outIndex] = input[varIndex1] ^ temp[varIndex2];
                    }
                }
            }   
        }
    }


    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < numInputs; j++) {
            int v = i & 1 << (numInputs - 1 - j);
            printf(v == 0 ? "0 " : "1 ");
        }
        for (int k = 0; k < numOutputs; k++) {
            printf("%d ", output[i][k]);
        }
        printf("\n");
    }

    fclose(fp);
}