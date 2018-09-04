/*
Author: Alexandre Boyer
Date-Create: 2018-08-15

This program contain the mathematics module of the program.
*/

// libraries required
#include <math.h>

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

double TFBoolean(int numAppearance) {
	if (numAppearance >= 1) {
		return (double)1;
	}
	else {
		return (double)0;
	}
}

double TFRawCount(int numAppearance) {
	return (double)numAppearance;
}

double TFLogNorm(int numAppearance) {
	return (double)log((double)(1 + numAppearance));
}

double TFTermFrequency(int numAppearance, int documentLength) {
	return (double)numAppearance/ (double)documentLength;
}