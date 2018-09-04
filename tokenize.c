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
#include "tokenize.h"

Word** addWord(Word **pTokens, char *word, size_t pTokens_length);

struct Tokens tokenize(char* corpus) {
	size_t pTokens_length = 0;
    Word **pTokens = NULL;  // initialization of outer pointer
    char *currentWord = NULL;  // current word examined in corpus
    int j = 0;  // position of "cursor" inside current word
    bool isOnlyNumber = true;  // indicates wether or not the word is only a number
    // go through the corpus character by character
    int numWords = 0;
    unsigned int i = 0;
    for (i; i < strlen(corpus); i++){
        // if the character is alphanumeric or is dash (for composite words)
        if (isalpha(corpus[i]) || corpus[i] == '-' || isdigit(corpus[i])){
            // if so, increase size of currentWord to allow it to fit
            currentWord = realloc(currentWord, (j + 2)*(sizeof(char)));  // + 1 for the index starting at 0 AND the null terminator
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
                // add the new word to the list
				currentWord[j] = '\0';  // null terminate the string
                pTokens = addWord(pTokens, currentWord, pTokens_length);
                numWords++;
            }
            // reset currentWord cursor, empty currentWord and reset flag
            j = 0;
            currentWord = NULL;
            isOnlyNumber = true;
        }
    }
	// need to add the last word because it doesn't get added in the last
	// iteration of the for loop
	if (currentWord != NULL && !isOnlyNumber) {
		currentWord[j] = '\0';  // null terminate the string
		pTokens = addWord(pTokens, currentWord, pTokens_length);
		numWords++;
	}
	// reset currentWord cursor, empty currentWord and reset flag
	j = 0;
	currentWord = NULL;
	isOnlyNumber = true;

	// // print the results of pTokens (used for testing and showing off)
	// for (int i = 0; i < pTokens_length; i++){
	//     // prints only the amount of character by using precision in the
	//     // printf arguments (%.\s) 
	//     printf("%s\n",pTokens[i]->word);
	// }
	struct Tokens t;
	t.pTokens = pTokens;
	t.pTokens_length = numWords;
	return t;
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

int size:
	determines the actual length of the word since the NULL terminator didn't
	seem to work on previous iterations of the prototype ... yay.

return:
Word ** pTokens:
	returns the new pointer
*/
Word ** addWord(Word **pTokens, char *word, size_t pTokens_length) {
	// reallocated the existing memory of the pTokens pointer with its existing
	// size + 1 just big enough to accomodate a new pointer to a Word struct
	pTokens = realloc(pTokens, (pTokens_length + 1) * sizeof(Word*));
	if (pTokens == NULL) {
		printf("pTokens realloc failed at line %d in %s", __LINE__, __FILE__);
		exit(-1);
	}
	// now that the spot for the outer pointer has been created, we need to
	// create space to hold the struc Word 
	pTokens[pTokens_length] = malloc(sizeof(Word));
	if (pTokens[pTokens_length] == NULL) {
		printf("pTokens[%d] realloc failed at line %d in %s", pTokens_length, __LINE__, __FILE__);
		exit(-1);
	}
	// inside that Word, since the string word can be of varying length, we also
	// have to allocate it dynamically
	pTokens[pTokens_length]->word = malloc(strlen(word)+1);  // +1 to allow null terminator
	// copy the new string inside (can't = because address would be the same)
	if (strncpy_s(pTokens[pTokens_length]->word, strlen(word)+1, word, strlen(word)+1) != 0) {
		printf("strncpy_s failed to write %s at line %d in %s\n", word, __LINE__, __FILE__);
	}
    // increase the global size of pTokens via pTokens_length
    pTokens_length++;
    // and finaly return the pointer ... ouf!
    return pTokens;
}
