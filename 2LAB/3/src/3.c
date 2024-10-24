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

int AddAnswer(SearchResult **results, int *result_count, int *capacity, const char *file_path, int line_number, int position) {
	if (*results == NULL) {
		return OPT_ERROR;
	}

	if (*result_count >= *capacity) {
		*capacity *= 2;
		SearchResult *temp = realloc(*results, *capacity * sizeof(SearchResult));
		if (temp == NULL) {
			return OPT_ERROR;
		}
		*results = temp;
	}

	(*results)[*result_count].file_path = file_path;
	(*results)[*result_count].line_number = line_number;
	(*results)[*result_count].position = position;
	if (!position) {
		(*results)[*result_count].found = 0;
	} else {
		(*results)[*result_count].found = 1;
	}
	(*result_count)++;
	return OPT_SUCCESS;
}

kOpts SearchInFiles(SearchResult **results, int *result_count, int *capacity, const char *substring, int num_files, ...) {
	va_list files_list;
	va_start(files_list, num_files);

	size_t len_substr = MyStrlen(substring);

	for (int i = 0; i < num_files; i++) {
		const char *file_path = va_arg(files_list, const char *);
		FILE *file = fopen(file_path, "r");
		if (!file) {
			AddAnswer(results, result_count, capacity, file_path, 0, 0);
			continue;
		}

		int c;
		int n_char = 0, n_line = 1;
		int idx = 0;
		int n_line_answ = 0, n_char_answer = 0;
		int found = 0;

		while ((c = getc(file)) != EOF) {
			n_char++;
			if (c == '\n') {
				n_line++;
				n_char = 0;
			}

			if (c == substring[idx]) {
				idx++;
				if (idx == 1) {
					n_line_answ = n_line;
					n_char_answer = n_char;
				}

				if (idx == len_substr) {
					if (AddAnswer(results, result_count, capacity, file_path, n_line_answ, n_char_answer) == OPT_ERROR) {
						fclose(file);
						va_end(files_list);
					}

					fseek(file, -idx + 1, SEEK_CUR);
					n_char = 1;
					if (n_line != n_line_answ){
						n_line = n_line_answ + 1;
					}
					idx = 0;
					found = 1;
				}
			} else if (idx > 0) {
				fseek(file, -idx + 1, SEEK_CUR);

				n_char -= (idx - 1);
				if (n_line != n_line_answ){
					n_line = n_line_answ + 1;
				}
				idx = 0;
			}
		}

		if (!found) {
			AddAnswer(results, result_count, capacity, file_path, 0, 0);
		}

		fclose(file);
	}

	va_end(files_list);
	return OPT_SUCCESS;
}