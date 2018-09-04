// header file for the tokenizer module
typedef struct Word {
    char* word;  // contain the word itself
}Word;

struct Tokens {    
    Word **pTokens;
    int pTokens_length;
}Tokens;

struct Tokens tokenize(char* corpus);