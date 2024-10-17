#ifndef LAB3_H
#define LAB3_H
#include <stdio.h>


typedef enum kOpts {
    OPT_SUCCESS,
    OPT_ERROR
} kOpts;

typedef struct SearchResult{
    const char *file_path;
    int line_number;
    int position;
    int found;
} SearchResult;

int SearchInFiles(SearchResult *results, const char *substring, int num_files, ...);
unsigned int MyStrlen(const char *str);
char* Mystrstr(const char *substring, const char *string);

#endif
