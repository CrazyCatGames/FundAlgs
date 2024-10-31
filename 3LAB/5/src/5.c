#include "../include/5.h"

#define COUNT_EXAMS 5

int CompareById(const void *a, const void *b) {
	return ((Student *) a)->id - ((Student *) b)->id;
}
int CompareBySurname(const void *a, const void *b) {
	return strcmp(((Student *) a)->surname, ((Student *) b)->surname);
}
int CompareByName(const void *a, const void *b) {
	return strcmp(((Student *) a)->name, ((Student *) b)->name);
}
int CompareByGroup(const void *a, const void *b) {
	return strcmp(((Student *) a)->group, ((Student *) b)->group);
}

void FreeStudents(Student *students, ssize_t count) {
	for (ssize_t i = 0; i < count; i++) {
		free(students[i].name);
		free(students[i].group);
		free(students[i].surname);
		free(students[i].grades);
	}
	free(students);
}

char *ReadString(FILE *file) {
	char c = fgetc(file);
	while (isspace(c)) {
		c = fgetc(file);
	}
	ungetc(c, file);
	char *str = NULL;
	int length = 0;
	int capacity = 16;
	str = (char *) malloc(capacity * sizeof(char));
	if (!str) {
		return NULL;
	}
	char ch;
	while (fscanf(file, "%c", &ch) == 1 && ch != ' ' && ch != '\n') {
		if (length + 1 >= capacity) {
			capacity *= 2;
			char *tmp = (char *) realloc(str, capacity * sizeof(char));
			if (!tmp) {
				free(str);
				return NULL;
			}
			str = tmp;
		}
		str[length++] = ch;
	}
	str[length] = '\0';

	return str;
}

size_t ReadStudents(const char *file_path, Student **students, size_t *count) {
	FILE *file = fopen(file_path, "r");
	if (!file) {
		return -1;
	}
	size_t capacity = 2;
	*students = (Student *) malloc(capacity * sizeof(Student));
	if (!*students) {
		fclose(file);
		return -2;
	}

	*count = 0;

	while (1) {
		if (*count >= capacity) {
			capacity *= 2;
			Student *tmp = (Student *) realloc(*students, capacity * sizeof(Student));
			if (!tmp) {
				FreeStudents(*students, *count);
				fclose(file);
				return -2;
			}
			*students = tmp;
		}

		Student *current_student = &(*students)[*count];
		if (fscanf(file, "%u", &current_student->id) != 1) {
			break;
		}

		current_student->name = ReadString(file);
		current_student->surname = ReadString(file);
		current_student->group = ReadString(file);
		if (!current_student->name || !current_student->surname || !current_student->group) return -2;

		if (!current_student->name || !current_student->surname || !current_student->group) {
			FreeStudents(*students, *count);
			fclose(file);
			return -3;
		}
		current_student->grades = (unsigned char *) malloc(sizeof(unsigned char) * COUNT_EXAMS);
		if (!current_student->grades) {
			FreeStudents(*students, *count);
			fclose(file);
			return -2;
		}
		for (int j = 0; j < COUNT_EXAMS; j++) {
			fscanf(file, "%hhu", &current_student->grades[j]);
		}
		(*count)++;
	}
	fclose(file);
	return 0;
}

float CalculateAverage(Student *student) {
	float sum = 0;
	for (int i = 0; i < COUNT_EXAMS; i++) {
		sum += student->grades[i];
	}
	return sum / COUNT_EXAMS;
}

void LogStudentById(FILE *logFile, Student *student) {
	if (student) {
		fprintf(logFile, "Student: %s %s, Group: %s, Medium grade: %.2f\n", student->name, student->surname,
				student->group, CalculateAverage(student));
	}
}

float CalculateAverageGrade(Student *students, int count) {
	float total = 0.0;
	for (int i = 0; i < count; i++) {
		total += CalculateAverage(&students[i]);
	}
	return total / count;
}

void LogStudentsWithHighAverage(FILE *out, Student *students, int count) {
	float average = CalculateAverageGrade(students, count);
	for (int i = 0; i < count; i++) {
		if (CalculateAverage(&students[i]) > average) {
			fprintf(out, "%s %s\n", students[i].name, students[i].surname);
		}
	}
}

char *ReadStringForSpace(FILE *file) {
	char c = fgetc(file);
	while (isspace(c)) {
		c = fgetc(file);
	}

	ungetc(c, file);
	char *str = NULL;
	int length = 0;
	int capacity = 16;
	str = (char *) malloc(capacity * sizeof(char));
	if (!str) {
		return NULL;
	}

	char ch;
	while (fscanf(file, "%c", &ch) == 1 && ch != '\n') {
		if (length + 1 >= capacity) {
			capacity *= 2;
			char *tmp = (char *) realloc(str, capacity * sizeof(char));
			if (!tmp) {
				free(str);
				return NULL;
			}
			str = tmp;
		}
		str[length++] = ch;
	}
	str[length] = '\0';

	return str;
}