#include "../include/3.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int MyStrlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int AddAnswer(SearchResult *results, int result_count, const char *file_path, int line_number, int position) {
    if (results == NULL) {
        return OPT_ERROR;
    }

    results[result_count].file_path = file_path;
    results[result_count].line_number = line_number;
    results[result_count].position = position;
    results[result_count].found = 1;

    return OPT_SUCCESS;
}

int SearchInFiles(SearchResult *results, const char *substring, int num_files, ...) {
    va_list files_list;
    va_start(files_list, num_files);

    int result_count = 0;
    size_t len_substr = MyStrlen(substring);

    for (int i = 0; i < num_files; i++) {
        const char *file_path = va_arg(files_list, const char *);
        FILE *file = fopen(file_path, "r");
        if (!file) {
            results[result_count].file_path = file_path;
            results[result_count].found = 0;
            result_count++;
            continue;
        }

        int c;
        int n_char = 0, n_line = 1;
        int idx_substr = 0;
        int n_line_answ = 0, n_char_answ = 0;
        int count_new_str = 0;
        int found = 0;

        while ((c = getc(file)) != EOF) {
            n_char++;
            if (c == '\n') {
                n_line++;
                n_char = 0;
            }

            if (c == substring[idx_substr]) {
                idx_substr++;
                if (idx_substr == 1) {
                    n_line_answ = n_line;
                    n_char_answ = n_char;
                }

                if (idx_substr == len_substr) {
                    if (AddAnswer(results, result_count, file_path, n_line_answ, n_char_answ) == OPT_ERROR) {
                        fclose(file);
                        va_end(files_list);
                        return -1;
                    }

                    fseek(file, -idx_substr + 1, SEEK_CUR);
                    count_new_str = 0;
                    for (int j = 0; j < idx_substr; j++) {
                        if (substring[j] == '\n')
                            count_new_str++;
                    }

                    n_char -= (idx_substr - 1);
                    n_line -= count_new_str;
                    idx_substr = 0;
                    found = 1;
                    result_count++;
                }
            } else if (idx_substr > 0) {
                fseek(file, -idx_substr + 1, SEEK_CUR);
                count_new_str = 0;
                for (int j = 0; j < idx_substr; j++) {
                    if (substring[j] == '\n')
                        count_new_str++;
                }

                if (c == '\n')
                    count_new_str++;

                n_char -= (idx_substr - 1);
                n_line -= count_new_str;
                idx_substr = 0;
            }
        }

        if (found == 0) {
            results[result_count].file_path = file_path;
            results[result_count].found = 0;
            result_count++;
        }

        fclose(file);
    }

    va_end(files_list);
    return result_count;
}
