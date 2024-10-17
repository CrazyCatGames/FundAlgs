#include "include/3.h"
#include <stdio.h>

int main() {

    const char *substring = "a1\ta";
    int num_files = 3;

    const char *file1 = "C:\\Users\\user\\CLionProjects\\FUNDLABS\\2LAB\\3\\examples\\file1.txt";
    const char *file2 = "C:\\Users\\user\\CLionProjects\\FUNDLABS\\2LAB\\3\\examples\\file2.txt";
    const char *file3 = "C:\\Users\\user\\CLionProjects\\FUNDLABS\\2LAB\\3\\examples\\file3.txt";
    SearchResult results[50];

    int result_count = SearchInFiles(results, substring, num_files, file1, file2, file3);
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