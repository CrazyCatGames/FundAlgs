#include "../include/3.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kOpt ValidateInput(int argc, char **argv) {
	if (argc != 4 || (argv[2][0] != '/' && argv[2][0] != '-') || argv[2][2] != '\0') return OPT_ERROR_INPUT;

	char full_path_1[BUFSIZ], full_path_2[BUFSIZ];
	if (!realpath(argv[1], full_path_1) || !realpath(argv[3], full_path_2)) return OPT_ERROR_INPUT;
	if (!strcmp(full_path_1, full_path_2)) return OPT_ERROR_INPUT;
	return OPT_SUCCESS;
}

kOpt ValidateData(Employee data) {
	unsigned long long len = strlen(data.name);
	for (int i = 0; i < len; ++i) {
		if (!((data.name[i] >= 'a' && data.name[i] <= 'z') || (data.name[i] >= 'A' && data.name[i] <= 'Z'))) return OPT_ERROR_INPUT;
	}

	len = strlen(data.surname);
	for (int i = 0; i < len; ++i) {
		if (!((data.surname[i] >= 'a' && data.surname[i] <= 'z') || (data.surname[i] >= 'A' && data.surname[i] <= 'Z'))) return OPT_ERROR_INPUT;
	}

	if (data.salary < EPS) {
		return OPT_ERROR_INPUT;
	}

	return OPT_SUCCESS;
}

int CompareA(const void *a, const void *b) {
	const Employee *temp_a = (const Employee *) a;
	const Employee *temp_b = (const Employee *) b;
	if (temp_a->salary - temp_b->salary > EPS) {
		return 1;
	}

	if (temp_b->salary - temp_a->salary > EPS) {
		return -1;
	}

	int temp = strcmp(temp_a->surname, temp_b->surname);
	if (temp) return temp;

	temp = strcmp(temp_a->name, temp_b->name);
	if (temp) return temp;

	return temp_a->id - temp_b->id;
}

int CompareB(const void* a, const void *b){
	return CompareA(a, b) * -1;
}

kOpt GetEmployee(FILE *file, Employee **output_data, int *size) {
	int capacity = 2, count_read;
	if (!output_data) return OPT_ERROR_INPUT;

	*output_data = NULL;

	Employee *data = (Employee *) malloc(sizeof(Employee) * capacity);
	if (!data) return OPT_ERROR_MEMORY;

	while ((count_read = fscanf(file, "%u %s %s %lf\n", &data[*size].id, data[*size].name, data[*size].surname, &data[*size].salary)) == 4) {
		if (ValidateData(data[(*size)])) {
			free(data);
			return OPT_ERROR_INPUT;
		}
		(*size)++;
		if (*size == capacity) {
			capacity *= 2;
			Employee *tmp_realloc = (Employee *) realloc(data, capacity * sizeof(Employee));
			if (!tmp_realloc) {
				free(data);
				return OPT_ERROR_MEMORY;
			}
			data = tmp_realloc;
		}
	}

	if (count_read < 4 && count_read > 0) {
		free(data);
		return OPT_ERROR_INPUT;
	}
	*output_data = data;
	return OPT_SUCCESS;
}