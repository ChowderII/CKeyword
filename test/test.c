#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/tokenize.h"

int main(void) {
    Word *(*pTokens) = NULL;  // empty pointer of pointer to Word struct
    pTokens = malloc(sizeof(Word*)*3);
    pTokens[0]->word = malloc(strlen("TEST"));
    pTokens[0]->word = "TEST";
    printf("%s", pTokens[0]->word);
    return 0;
}