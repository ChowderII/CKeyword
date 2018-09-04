typedef struct Hash_Item {
    unsigned char* word;  // holds the string of the word
    int* documentCount; // contains the count information of the word
}Hash_Item;

unsigned long hash(unsigned char *str);