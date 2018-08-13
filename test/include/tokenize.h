// header file for the tokenizer module

typedef struct Word {
    char* word;  // contain the word itself
    int* corpusID;  // contain the list of all corpus this word is in
    double IDF;  // contain the IDF score of that word
    int size;  // size of the word, because apperentally, null terminators don't do their job anymore ...
}Word;

char* getCorpus(char* PATH);