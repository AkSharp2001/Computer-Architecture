#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 0;
    }
    char sentence[100];
    
    for (int i = 1; i < argc; i++) {
       strcat(sentence, argv[i]);
    }  

    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == 'a' || sentence[i] == 'e' || sentence[i] == 'i' || sentence[i] == 'o' || 
        sentence[i] == 'u' || sentence[i] == 'A' || sentence[i] == 'E' || sentence[i] == 'I' ||
        sentence[i] == 'O' || sentence[i] == 'U') {
            printf("%c", sentence[i]);  
        }
    }
    printf("\n");

    return 0;
}
