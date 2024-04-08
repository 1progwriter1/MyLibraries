#ifndef FILE_FUNCTIONS
#define FILE_FUNCTIONS

#include <stdio.h>

struct Text {
        long long int filelen;
        FILE *filename;
        long long int NumOfWords;
        long long int NumOfStr;
};

void SetStructText(struct Text *data, const char *filename);

void cleanfile(const char *filename);

FILE *fileopen(const char *filename, const char mode[]);

void fileclose(FILE *fn);

unsigned long filelen(const char *filename);

long long int NumOfStr(const char *str, size_t len);

char *readbufStruct(struct Text *filedata);

char *readbuf(const char *filename);

#endif
