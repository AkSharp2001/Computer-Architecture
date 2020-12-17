#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short ax, bx, cx, dx;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return 0;
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 0;
    }

    char array[100][15];
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

    fclose(fp);
    
    char* arr[100][300];
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
    //     for (int j = 0; j < 5; j++) {
    //         printf("%s ", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    
    i = 0, j = 0;
    while (i < totalLines) {
        if (arr[i][j] == NULL) {
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "read") == 0) {
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                scanf("%hi", &ax);
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                scanf("%hi", &bx);
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                scanf("%hi", &cx);
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                scanf("%hi", &dx);
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "print") == 0) {
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                printf("%hi", ax);
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                printf("%hi", bx);
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                printf("%hi", cx);
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                printf("%hi", dx);
            }
            else {
                printf("%hi", atoi(arr[i][j]));
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "mov") == 0) {
            j++;
            short num;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                ax = num;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                bx = num;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                cx = num;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                dx = num;
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "add") == 0) {
            j++;
            short num;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                ax += num;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                bx += num;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                cx += num;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                dx += num;
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "sub") == 0) {
            j++;
            short num;  
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                ax -= num;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                bx -= num;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                cx -= num;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                dx -= num;
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "mul") == 0) {
            j++;
            short num;  
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                ax *= num;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                bx *= num;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                cx *= num;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                dx *= num;
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "div") == 0) {
            j++;
            short num;  
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                ax = num/ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                bx = num/bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                cx = num/cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                dx = num/dx;
            }
            i++;
            j = 0;
        }
        else if (strcmp(arr[i][j], "jmp") == 0) {
            j++;
            int line = atoi(arr[i][j]);
            i = line;
            j = 0;
        }
        else if (strcmp(arr[i][j], "je") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num == num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
        else if (strcmp(arr[i][j], "jne") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num != num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
        else if (strcmp(arr[i][j], "jg") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num > num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
        else if (strcmp(arr[i][j], "jge") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num >= num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
        else if (strcmp(arr[i][j], "jl") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num < num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
        else if (strcmp(arr[i][j], "jle") == 0) {
            j++;
            short num, num1;
            int line = atoi(arr[i][j]);
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num = dx;
            }
            else {
                num = atoi(arr[i][j]);
            }
            j++;
            if (strcmp(arr[i][j], "ax") == 0) {
                num1 = ax;
            }
            else if (strcmp(arr[i][j], "bx") == 0) {
                num1 = bx;
            }
            else if (strcmp(arr[i][j], "cx") == 0) {
                num1 = cx;
            }
            else if (strcmp(arr[i][j], "dx") == 0) {
                num1 = dx;
            }
            else {
                num1 = atoi(arr[i][j]);
            }
            if (num <= num1) {
                i = line;
                j = 0;
            }
            else {
                i++;
                j = 0;
            }
        }
    
    }
}