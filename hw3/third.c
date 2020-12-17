#include <stdio.h>
#include <stdlib.h>

unsigned short get(unsigned short x, unsigned short n);

int main(int argc, char* argv[])
{
    if (argc < 2) return 0;
    unsigned short number = atoi(argv[1]);
    unsigned short reverse = 0;
    unsigned short num = number;

    unsigned short i;
    for (i = 0; i < 16; i++) {
        reverse <<= 1;
        if ((num & 1) == 1) {
            reverse ^= 1;
        }
        num >>= 1;
    }

    if(number == reverse) {
        printf("Is-Palindrome\n");
    }  
    else {
        printf("Not-Palindrome\n");
    }
}

unsigned short get(unsigned short x, unsigned short n) {
    return (x >> n) & 1;
}
