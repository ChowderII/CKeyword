#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/tokenize.h"

int main(void) {
    Word *(*pTokens) = NULL;
    pTokens = malloc(sizeof(Word*));
    Word test = {.word = "TEST"};
    *pTokens[0] = &test;
}