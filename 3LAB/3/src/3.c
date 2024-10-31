#include "../include/3.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool IsAlphaString(const char *str) {
	for (size_t i = 0; str[i] != '\0'; i++) {
		if (!isalpha((unsigned char)str[i])) {
			return false;
		}
	}
	return true;
}

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

int CompareB(const void *a, const void *b) {
	return CompareA(a, b) * -1;
}

char *ReadString(FILE *file) {
	int capacity = 16;
	int length = 0;
	char *str = (char *) malloc(capacity * sizeof(char));
	if (!str) return NULL;

	char ch;
	while ((ch = fgetc(file)) == ' ');
	if (ch != ' '){
		ungetc(ch, file);
	}
	while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != ' ') {
		if (length >= capacity) {
			capacity *= 2;
			char *temp = realloc(str, capacity * sizeof(char));
			if (!temp) {
				free(str);
				return NULL;
			}
			str = temp;
		}

		str[length++] = ch;
	}

	if (length == 0) {
		free(str);
		return NULL;
	}

	str[length] = '\0';
	return str;
}

void FreeEmployee(Employee *data, int size) {
	for (int i = 0; i < size; i++) {
		free(data[i].name);
		free(data[i].surname);
	}
	free(data);
}

kOpt GetEmployee(FILE *file, Employee **output_data, int *size) {
	int capacity = 2;

	Employee *data = (Employee *) malloc(sizeof(Employee) * capacity);
	if (!data) return OPT_ERROR_MEMORY;

	while (1) {
		char *id_buffer = ReadString(file);
		if (!id_buffer) break;

		char *endptr;
		unsigned long id = strtoul(id_buffer, &endptr, 10);

		if (*endptr != '\0') {
			free(id_buffer);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		if (id > UINT_MAX) {
			free(id_buffer);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		data[*size].id = (unsigned int) id;

		data[*size].name = ReadString(file);
		if (!data[*size].name) {
			free(id_buffer);
			FreeEmployee(data, *size);
			return OPT_ERROR_MEMORY;
		}

		data[*size].surname = ReadString(file);
		if (!data[*size].surname) {
			free(id_buffer);
			free(data[*size].name);
			FreeEmployee(data, *size);
			return OPT_ERROR_MEMORY;
		}
		if (!IsAlphaString(data[*size].name) || !IsAlphaString(data[*size].surname)) {
			free(id_buffer);
			free(data[*size].name);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		char *salary_buffer = ReadString(file);
		if (!salary_buffer) {
			free(id_buffer);
			free(data[*size].name);
			free(data[*size].surname);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		double salary = strtod(salary_buffer, &endptr);

		if (*endptr != '\0') {
			free(id_buffer);
			free(salary_buffer);
			free(data[*size].name);
			free(data[*size].surname);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		if (salary < 0) {
			free(salary_buffer);
			free(id_buffer);
			free(data[*size].name);
			free(data[*size].surname);
			FreeEmployee(data, *size);
			return OPT_ERROR_INPUT;
		}

		data[*size].salary = salary;

		(*size)++;
		if (*size == capacity) {
			capacity *= 2;
			Employee *tmp_realloc = (Employee *) realloc(data, capacity * sizeof(Employee));
			if (!tmp_realloc) {
				free(salary_buffer);
				free(id_buffer);
				FreeEmployee(data, *size);
				return OPT_ERROR_MEMORY;
			}
			data = tmp_realloc;
		}
		free(id_buffer);
		free(salary_buffer);
	}

	*output_data = data;
	return OPT_SUCCESS;
}