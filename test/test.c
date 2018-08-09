#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/tokenize.h"

Word** addWord(Word **pTokens, char *word, int corpusID);
int pTokens_length = 0;

int main(void) {
    char *testString = "Lorem ipsum el dolore";
    Word *(*pTokens) = NULL;  // empty pointer of pointer to Word struct
    pTokens = addWord(pTokens, "TEST", 1);
    pTokens[0]->IDF = 3.1;
    printf("%s, %f, %d", pTokens[0]->word, pTokens[0]->IDF, pTokens[0]->corpusID[0]);
    return 0;
}  

Word ** addWord(Word **pTokens, char *word, int corpusID){
    pTokens = realloc(pTokens, (pTokens_length +1) * sizeof(Word*));
    pTokens[pTokens_length] = malloc(sizeof(Word));
    pTokens[pTokens_length]->word = malloc(strlen(word));
    pTokens[pTokens_length]->word = strncpy(pTokens[pTokens_length]->word,
        word, strlen(word));
    pTokens[pTokens_length]->corpusID = malloc(sizeof(int));
    pTokens[pTokens_length]->corpusID[0] = corpusID;
    pTokens_length++;
    return pTokens;
}