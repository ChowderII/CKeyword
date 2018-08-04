// header file for the tokenizer module

typedef struct Word {
    char* word;  // contain the word itself
    int* corpusID;  // contain the list of all corpus this word is in
    double IDF;  // contain the IDF score of that word
}Word;

char* getCorpus(char* PATH);