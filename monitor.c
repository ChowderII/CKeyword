/*
Author: Alexandre Boyer
Date-Create: 2018-07-31

This program is the one interacting with the user and the deeper levels of the
program. It will be in charge of letting the user know what is happening
*/

// libraries required

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dirent.h"
#include <math.h>
#include "tokenize.h"
#include "mathModule.h"

char* prepareText(char* PATH);
#define HASHMAP_SIZE (2 << 16)
int NUM_DOCUMENTS = 0;

int main(void){
    struct dirent *file;
    
    char** documents = NULL;
    // get the corpus of text
    int i = 0;
    printf("preparing text corpus ... ");
	fflush(stdout);
    
    struct dirent *directoryEntry;
    DIR *dr = opendir(".");
    if (dr == NULL){  // if can't open directory
        printf("corpus realloc failed at line %d in %s\n", __LINE__, __FILE__);
        return(-1);
    }
    
    while ((directoryEntry = readdir(dr)) != NULL){
		// test if the second to last character in the file is an 'x' to catch *.txt files only 
        if(directoryEntry->d_name[strlen(directoryEntry->d_name)-2] == 'x'){  // i don't really like this solution, but it seems to be working fine
            printf("NUM_DOCUMENTS = %d %s\n", NUM_DOCUMENTS, directoryEntry->d_name);
            documents = realloc(documents, (NUM_DOCUMENTS+1)*(sizeof(char*)));
			documents[NUM_DOCUMENTS] = malloc(sizeof(char*));
			documents[NUM_DOCUMENTS] = prepareText(directoryEntry->d_name);
            NUM_DOCUMENTS++;
        }
    }
    closedir(directoryEntry);
    
    printf("done\nhashmap memory allocation ... ");
    fflush(stdout);
	Hash_Item* hashmap[HASHMAP_SIZE] = { NULL };  // gigantic hash map to ensure the least collisions as possible
    printf("done\ntokenization ... ");
    fflush(stdout);
    
    i = 0;
    unsigned char* currentWord = NULL;
	struct Tokens *tokens = NULL;
    for(i; i < NUM_DOCUMENTS; i++){  // for every document
		tokens = realloc(tokens, (i + 1) * sizeof(Tokens));
        tokens[i] = tokenize(documents[i]);  // get the tokens
        int j = 0;
        for(j; j < tokens[i].pTokens_length; j++){  // for every token
            unsigned char* currentWord = malloc(strlen(tokens[i].pTokens[j]->word) + 1);  // + 1 for null terminator
			if (strncpy_s(currentWord, strlen(tokens[i].pTokens[j]->word) + 1, tokens[i].pTokens[j]->word, strlen(tokens[i].pTokens[j]->word)) != 0) {
				printf("strncpy_s failed to write %s at line %d in %s\n", tokens[i].pTokens[j]->word, __LINE__, __FILE__);
			}
            int currentIndex = hash(currentWord) % (HASHMAP_SIZE-1); // get the index of the word
            if(hashmap[currentIndex] != NULL){  // if the word allocation already exists in the hashmap
				// need to allocate memory to old the counts but since we can't verify if the pointer has been initialized, we simply reallocate it 
				// the same size everytime, the data isn't lost unless the pointer fails to alloc
                hashmap[currentIndex]->documentCount[i+1]++;  // increment the proper document
                hashmap[currentIndex]->documentCount[0]++;  // increment general document
            }
            else {
                Hash_Item tmp;
                tmp.word = malloc(strlen(tokens[i].pTokens[j]->word) + 1);
				if (strncpy_s(tmp.word, strlen(tokens[i].pTokens[j]->word) + 1, currentWord, strlen(tokens[i].pTokens[j]->word)) != 0) {
					printf("strncpy_s failed to write %s at line %d in %s\n", tmp.word, __LINE__, __FILE__);
				}
                tmp.documentCount = malloc(NUM_DOCUMENTS + 1);  // +1 for the total document count
				hashmap[currentIndex] = malloc(sizeof(Hash_Item));
				if (tmp.documentCount == NULL || hashmap[currentIndex] == NULL) {
					printf("tmp.documentCount or hashmap[currentIndex] malloc failed at line %d in file %s\n", __LINE__, __FILE__);
				}
				size_t k = 0;
				for (k; k <= NUM_DOCUMENTS; k++) {  // >= to include one extra document count (the general document counter)
					tmp.documentCount[k] = 0;
				}
                hashmap[currentIndex] = &tmp;
                hashmap[currentIndex]->documentCount[i+1]++;  // increment the proper document
                hashmap[currentIndex]->documentCount[0]++;  // increment general document
            }
			free(currentWord);
        }
    }
    printf("done\n");
    return 0;
}

char* prepareText(char* PATH){
    FILE *fptr;  // will contain the opened file
    char *corpus = NULL;  // array to contain the whole text
    long fileSize;  // size of the current file in bytes
    
    // try to open the lipsum file, if it can't, say so and return 1
    if (fopen_s(&fptr, PATH,"r") != 0){
        printf("fptr failed to open %s at line %d in %s", PATH, __LINE__, __FILE__);
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    // go through the file to get how big it is
    fseek(fptr, 0, SEEK_END);
    fileSize = ftell(fptr);
    // places the cursor back to the beginning of file to start reading
    rewind (fptr);
    
    corpus = malloc(fileSize+1);
    fread(corpus, 1, fileSize, fptr);  // leave one element for the \0
    corpus[fileSize] = '\0';
    
    // return the corpus, free the variables from the memory and close the file
    fclose(fptr);
    return corpus; 
}
