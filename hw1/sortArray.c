#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    return 0;
  }
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL) {
    return 0;
  }
  int length;
  fscanf(fp, "%d/n", &length);

  int* array = (int*) malloc(length*sizeof(int));
  int temp;
  int j = 0;
  int k = length - 1;
  
  for (int i = 0; i < length; i++)
  {
    fscanf(fp, "%d\t", &temp);
    if (temp % 2 == 0) {
      array[j++] = temp;
    }
    else {
      array[k--] = temp;
    }    
  }

  int index = 0;
  while (index < length && array[index] % 2 == 0) {
    index++;
  }

  for (int i = 0; i < length; i++) {
    if (i < index) {
      for (int j = i+1; j < index; j++) {
	      if (array[i] > array[j]) {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
	      }
      }
    }
    else {
      for (int j = i+1; j < length; j++) {
        if (array[j] > array[i]) {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
	      }
      }
    }
  }

  for (int i = 0; i < length; i++) {
    printf("%d\t", array[i]);
  }
  printf("\n");

  free(array);
  fclose(fp);

}