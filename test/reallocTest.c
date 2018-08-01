/*
Author: Alexandre Boyer
Date-Create: 2018-07-31

This test program will test the performance of the realloc function given our 
objective with the project.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <unistd.h>

int main(void){
    FILE *fptr;  // will contain the opened file
    // buffer used to store incoming data from the file
    // char lipsum[255];  // array that will contain the whole text, must use
    // realloc on it to increase it's size dynamically as the array gets bigger

  if ((fptr = fopen("data/lipsum.txt","r")) == NULL){
      printf("Error! opening file");
      // Program exits if the file pointer returns NULL.
      exit(1);
  }
  printf("Value: %c", fgetc(fptr));
  fclose(fptr); 
  
  return 0;
}