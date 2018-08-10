/*
Author: Alexandre Boyer
Date-Create: 2018-08-03

This test program will test the performance of the realloc function given our 
objective with the project.
*/

// libraries required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "include/tokenize.h"

Word** addWord(Word **pTokens, char *word, int corpusID);
int pTokens_length = 0;

int main (void) {
    char *corpus = NULL;  // contains the text to be tokenized
    corpus = getCorpus("data/lipsum.txt");  // go gets it
    Word **pTokens = NULL;  // initialization of outer pointer
    
    char *currentWord = NULL;  // current word examined in corpus
    int j = 0;  // position of "cursor" inside current word
    bool isOnlyNumber = true;  // indicates wether or not the word is only a number
    // go through the corpus character by character
    for (int i = 0; i < strlen(corpus); i++){
        // if the character is alphanumeric or is dash (for composite words)
        if (isalpha(corpus[i]) || corpus[i] == '-' || isdigit(corpus[i])){
            // if so, increase size of currentWord to allow it to fit
            currentWord = realloc(currentWord, j*(sizeof(char))+1);
            if (!currentWord) {
                printf("currentWord realloc failed at line %d in %s\n", __LINE__, __FILE__);
                exit(-1);
            }
            // place the character inside and remove upper cases
            currentWord[j++] = tolower((unsigned char)corpus[i]);
            // if the character is a letter, then the word isn't only a number
            // and can thus be considered
            if (isalpha(corpus[i]) && isOnlyNumber)
                isOnlyNumber = false;
        }
        else { // space or something else
            // if the word is not empty or only a number
            if (currentWord != NULL && !isOnlyNumber){
                // add the new word to the list with the corpusID (here 12 is 
                // just a placeholder)
                pTokens = addWord(pTokens, currentWord, 12);
            }
            // reset currentWord cursor, empty currentWord and reset flag
            j = 0;
            currentWord = NULL;
            isOnlyNumber = true;
        }
    }
    // need to add the last word because it doesn't get added in the last
    // iteration of the for loop
    if (currentWord != NULL && !isOnlyNumber){
        // add the new word to the list with the corpusID (here 12 is 
        // just a placeholder)
        pTokens = addWord(pTokens, currentWord, 12);
    }
    // reset currentWord cursor, empty currentWord and reset flag
    j = 0;
    currentWord = NULL;
    isOnlyNumber = true;
    
    // print the results of pTokens (used for testing and showing off)
    for (int i = 0; i < pTokens_length; i++)
        printf("%s\n", pTokens[i]->word);
    // free pTokens
    free(pTokens);
    return 0;
}

char* getCorpus(char* PATH){
    FILE *fptr;  // will contain the opened file
    char *line = malloc(2048);  // buffer used to store incoming data from the file
    char *corpus = malloc(2048);  // array to contain the whole text
    if (!line || !corpus) {
        printf("line or corpus malloc failed at line %d in %s\n", __LINE__, __FILE__); 
        exit(-1);
    }
    size_t nread;  // holds the number of elements fread() has successfully read
  // try to open the lipsum file, if it can't, say so and return -2
  if ((fptr = fopen(PATH,"r")) == NULL){
      printf("fptr failed to open %s at line %d in %s", PATH, __LINE__, __FILE__);
      // Program exits if the file pointer returns NULL.
      exit(-2);
  }
  /*
  Here, the program will read blocks of 2 kilobytes of the file pointed to by
  fptr. nread represents the amount of bytes at a time (useful near the end of 
  file) read from fread. Each block of 2 kilobytes, corpus is realloc'd new
  memory to hold the additional data. Then the string of line is copied onto
  the existing string of corpus.
  */
  while ((nread = fread(line, 1, 2048, fptr)) > 0){
    corpus = realloc(corpus, strlen(corpus) + nread);
    if (!corpus){
        printf("coprus realloc failed at line %d in %s\n", __LINE__, __FILE__);
        exit(-1);
    }
    // copying exact amount of bytes to corpus
    corpus = strncat(corpus, line, nread);
  }
  // return the corpus, free the variables from the memory and close the file
  free(line);
  fclose(fptr);
  return corpus;
}

/*
This function adds a word to the pTokens pointer of pointers. 
arguments:
Word **pTokens
    this is the pointer to the list of struct pointers, its new values gets
    returned at the end of the function
    NOTE: pTokens MUST be already initialized, to NULL or malloc'd

char *word:
    this is the word to be added in the list

int corpusID:
    represents which document is this word found in 
    
return:
Word ** pTokens:
    returns the new pointer
*/
Word ** addWord(Word **pTokens, char *word, int corpusID){
    // reallocated the existing memory of the pTokens pointer with its existing
    // size + 1 just big enough to accomodate a new pointer to a Word struct
    pTokens = realloc(pTokens, (pTokens_length +1) * sizeof(Word*));
    if (!pTokens){
        printf("pTokens realloc failed at line %d in %s", __LINE__, __FILE__);
        exit(-1);
    }
    // now that the spot for the outer pointer has been created, we need to
    // create space to hold the struc Word
    pTokens[pTokens_length] = malloc(sizeof(Word));
    if (!pTokens[pTokens_length]){
        printf("pTokens[%d] realloc failed at line %d in %s", pTokens_length, __LINE__, __FILE__);
        exit(-1);
    }
    // inside that Word, since the string word can be of varying length, we also
    // have to allocate it dynamically
    pTokens[pTokens_length]->word = malloc(strlen(word));
    // copy the new string inside (can't = because address would be the same)
    pTokens[pTokens_length]->word = strncpy(pTokens[pTokens_length]->word,
        word, strlen(word));
    // since corpusID is an array of integer, we also have to allocate it the 
    // proper space
    pTokens[pTokens_length]->corpusID = malloc(sizeof(int));
    // we then assign it its first corpusID value
    pTokens[pTokens_length]->corpusID[0] = corpusID;
    // increase the global size of pTokens via pTokens_length
    pTokens_length++;
    // and finaly return the pointer ... ouf!
    return pTokens;
}