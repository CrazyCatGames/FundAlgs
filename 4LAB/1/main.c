#include "include/1.h"
ssize_t getline(char** lineptr, size_t* n, FILE* stream) {
	if (lineptr == NULL || n == NULL || stream == NULL) {
		return -1;// Некорректные аргументы
	}

	size_t pos = 0;
	int c;

	// Если буфер пустой, выделим начальную память
	if (*lineptr == NULL || *n == 0) {
		*n = 128;// Начальный размер буфера
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL) {
			return -1;// Ошибка выделения памяти
		}
	}

	// Чтение символов по одному
	while ((c = fgetc(stream)) != EOF) {
		// Проверка на конец строки
		if (c == '\n') {
			(*lineptr)[pos++] = c;
			break;
		}

		// Если буфер переполнен, увеличим его
		if (pos + 1 >= *n) {
			*n *= 2;
			char* new_lineptr = (char *)realloc(*lineptr, *n);
			if (new_lineptr == NULL) {
				return -1;
			}
			*lineptr = new_lineptr;
		}

		(*lineptr)[pos++] = c;
	}

	// Проверка на конец файла
	if (pos == 0 && c == EOF) {
		return -1;
	}

	(*lineptr)[pos] = '\0';// Завершаем строку
	return pos;            // Возвращаем длину строки
}


kOpt ProcessFile(const char* filename) {
	if (!filename) return OPT_FILE_OPEN_ERROR;
	FILE* file = fopen(filename, "r");
	if (!file) {
		return OPT_FILE_OPEN_ERROR;
	}

	char* tmp_filename = "C:\\Users\\user\\CLionProjects\\FUNDLABS\\4LAB\\1\\output.txt";
	FILE* file_tmp = fopen(tmp_filename, "w");
	if (!file_tmp) {
		fclose(file);
		return OPT_FILE_OPEN_ERROR;
	}

	char* line = NULL;
	size_t line_cap = 0;
	ssize_t read;
	HashTable* table = NULL;

	kOpt st_act = CreateTable(&table, TABLE_SIZE);
	if (st_act != OPT_SUCCESS) {
		fclose(file);
		fclose(file_tmp);
		return st_act;
	}
	while ((read = getline(&line, &line_cap, file)) != -1) {
		int size_line = strlen(line);

		char* key = (char*) malloc(sizeof(char) * (size_line + 1));
		if (!key) {
			fclose(file);
			fclose(file_tmp);
			FreeTable(table);
			free(file_tmp);
			return OPT_MEMORY_ERROR;
		}

		char* value = (char*) malloc(sizeof(char) * (size_line + 1));
		if (!value) {
			fclose(file);
			fclose(file_tmp);
			FreeTable(table);
			free(key);
			return OPT_MEMORY_ERROR;
		}

		int ch = sscanf(line, "#define %s %[^\n]", key, value);
		if (ch == 2) {
			st_act = InsertTable(&table, key, value);
			if (st_act != OPT_SUCCESS) {
				free(line);
				fclose(file);
				fclose(file_tmp);
				FreeTable(table);
				free(key);
				free(value);
				return st_act;
			}
		} else {
			char* token = strtok(line, " .,\t\n");
			while (token) {
				char* to_replace = FindElement(table, token);
				fprintf(file_tmp, "%s ", to_replace ? to_replace : token);
				token = strtok(NULL, " .,\t\n");
			}
			fprintf(file_tmp, "\n");
			free(key);
			free(value);
		}

	}
	free(line);
	PrintTable(table);
	fclose(file);
	fclose(file_tmp);
	FreeTable(table);
	return OPT_SUCCESS;
}

void print_error(kOpt st) {
	switch (st) {
		case OPT_INPUT_ERROR:
			printf("Error incorrect input.\n");
			break;
		case OPT_MEMORY_ERROR:
			printf("Error alloc memory.\n");
			break;
		case OPT_FILE_OPEN_ERROR:
			printf("Error open file.\n");
			break;
		default:
			break;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Your programm must start with: %s <FILE>\n", argv[0]);
	}
	const char* filename = argv[1];
	kOpt st_act;
	st_act = ProcessFile(filename);
	print_error(st_act);
	return 0;
}