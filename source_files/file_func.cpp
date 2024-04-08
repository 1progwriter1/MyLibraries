#include <stdio.h>
#include "../headers/file_func.h"
#include <assert.h>
#include "../headers/systemdata.h"
#include "../headers/func.h"
#include <sys/stat.h>

char *readbufStruct(struct Text *filedata) {

    assert(filedata);
    assert(filedata->filename);

    char *buf = (char *) calloc (filedata->filelen + 1, sizeof (char));
    fread(buf, sizeof (char), filedata->filelen, filedata->filename);

    filedata->NumOfStr = NumOfStr(buf, filedata->filelen);

    return buf;
}

char *readbuf(const char *filename) {

    assert(filename);

    unsigned long len_of_file = filelen(filename);
    FILE *fn = fileopen(filename, READ);
    if (!fn)
        return NULL;

    char *buf = (char *) calloc (len_of_file + 1, sizeof (char));
    fread(buf, sizeof (char), len_of_file, fn);
    if (ferror(fn)) {
        printf(RED "Ошибка при чтении файла" END_OF_COLOR "\n");
        return NULL;
    }

    fileclose(fn);

    return buf;
}

long long int NumOfStr(const char *str, size_t len) {

    assert(str);

    int c = 0, col = 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\n')
            col++;
    }
    return col;
}

void SetStructText(struct Text *data, const char *filename) {

    assert(data);

    data->filelen  = filelen (filename);
    data->filename = fileopen(filename, READ);
    data->NumOfWords = 0;
    data->NumOfStr   = 0;

}

void cleanfile(const char *filename) {

    assert(filename);

    FILE *fn = fileopen(filename, WRITE);
}

FILE *fileopen(const char *filename, const char mode[]) {

    assert(filename);

    FILE *fn = fopen(filename, mode);

    if (fn == nullptr)
        perror("");

    return fn;
}

void fileclose(FILE *fn) {

    assert(fn);

    if (fn != stdout)
        if (fclose(fn) != 0)
            fprintf(stderr, "File not closed\n");
}

unsigned long filelen(const char *filename) {

    assert(filename);

    struct stat buf = {};
    if (stat(filename, &buf) == - 1)
        return ERROR;

    return buf.st_size;
}

