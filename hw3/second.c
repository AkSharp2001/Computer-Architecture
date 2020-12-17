#include <stdio.h>
#include <stdlib.h>

unsigned short count(unsigned short number);

int main(int argc, char* argv[])
{
    if (argc < 2) return 0;
    unsigned short number = atoi(argv[1]);  
    if (count(number) % 2 == 0) {
        printf("Even-Parity\t");
    }
    else {
        printf("Odd-Parity\t");
    }

    unsigned short pairs = 0;
    while (number != 0) {
        if ((number & 3) == 3) {
            pairs++;
            number >>= 2;
        }
        else {
            number >>= 1;
        }
        
    }
    printf("%hu\n", pairs);

}

unsigned short count(unsigned short number) {

    unsigned short count = 0; 
    while (number != 0) { 
        count += number & 1; 
        number >>= 1; 
    } 
    return count;
}