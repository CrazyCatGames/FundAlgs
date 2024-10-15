#ifndef LAB3_H
#define LAB3_H
#include <stdio.h>


typedef enum kOpts {
    OPT_SUCCESS,
    OPT_ERROR
} kOpts;

typedef struct {
    const char *file_path;
    int line_number;
    int position;
    int found;
} SearchResult;

int FindSubstring(const char *line, const char *substring, int start_pos);
int SearchInFiles(SearchResult *results, const char *substring, int num_files, ...);
unsigned int MyStrlen(const char *str);
char* Mystrstr(const char *substring, const char *string);
ssize_t MyGetline(char **lineptr, size_t *n, FILE *stream);

#endif
