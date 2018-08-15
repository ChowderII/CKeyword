/*
Author: Alexandre Boyer
Date-Create: 2018-07-31

This test program will test the performance of the realloc function given our 
objective with the project.
*/

// libraries required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fptr;  // will contain the opened file
    char *line = malloc(255);  // buffer used to store incoming data from the file
    char *corpus = malloc(255);  // array to contain the whole text
    size_t nread;  // holds the number of elements fread() has successfully read
    // if line or corpus' malloc fails, says so and return -1
    if (line == NULL || corpus == NULL){
        printf("mallocs have failed, exiting");
        exit(-1);
    }

  // try to open the lipsum file, if it can't, say so and return -2
  if ((fptr = fopen("data/lipsum.txt","r")) == NULL){
      printf("error opening file, exiting");
      // Program exits if the file pointer returns NULL.
      exit(-2);
  }
  /*
  Here, the program will read blocks of 256 bytes of the file pointed to by
  fptr. nread represents the amount of bytes at a time (useful near the end of 
  file) read from fread. Each block of 256 bytes, corpus is realloc'd new
  memory to hold the additional data. Then the string of line is copied onto
  the existing string of corpus.
  */
  while ((nread = fread(line, 1, 256, fptr)) > 0){
    corpus = realloc(corpus, strlen(corpus) + nread);
    if (corpus == NULL){
        printf("realloc failed, exiting");
        exit(-1);
    }
    // copying exact amount of bytes to corpus
    corpus = strncat(corpus, line, nread);
  }
  // print the corpus, free the variables from the memory and close the file
  printf("%s\n", corpus);
  free(line);
  free(corpus);
  fclose(fptr); 
  
  // return success
  return 0;
}