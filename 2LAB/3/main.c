#include "include/3.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <substring> <file1> [file2 ... fileN]\n", argv[0]);
        return 1;
    }

    const char *substring = argv[1];
    int num_files = argc - 2;

    SearchResult results[50];

    int result_count = SearchInFiles(results, substring, num_files, argv[2], argv[3], argv[4]);
    for (int i = 0; i < result_count; i++) {
        if (results[i].found == 1) {
            printf("Substring '%s' found in line %d, position: %d. File: %s\n",
                   substring, results[i].line_number, results[i].position, results[i].file_path);
        } else {
            printf("Substring '%s' not found in file: %s\n", substring, results[i].file_path);
        }
    }

    return 0;
}