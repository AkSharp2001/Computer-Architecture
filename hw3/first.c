#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 0;
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 0;
    }
    unsigned short x, n, v;
    char op[5];
    fscanf(fp, "%hu", &x);

    while (fscanf(fp, "%s\t%hu\t%hu\n", op, &n, &v) == 3) {
        if (strcmp(op, "set") == 0) {
            if (v == 0) {
                x = ~(1 << n) & x;
            }
            else if (v == 1) {
                x = (1 << n) | x;
            }
            printf("%hu\n", x);
        }
        else if (strcmp(op, "comp") == 0) {
            x = x ^ (1 << n);
            printf("%hu\n", x);
        }
        else if (strcmp(op, "get") == 0) {
            unsigned short getBit;
            getBit = (x >> n) & 1;
            printf("%hu\n", getBit);
        }
    }

    fclose(fp);
}
