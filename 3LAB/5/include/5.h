#ifndef INC_5_5_H
#define INC_5_5_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	unsigned int id;
	char *name;
	char *surname;
	char *group;
	unsigned char *grades;
} Student;

size_t ReadStudents(const char *file_path, Student **students, size_t *size);
void LogStudentById(FILE *logFile, Student *student);
int CompareById(const void *a, const void *b);
int CompareBySurname(const void *a, const void *b);
int CompareByName(const void *a, const void *b);
int CompareByGroup(const void *a, const void *b);
Student* FindStudentsById(Student* students, int count, unsigned int id);
Student* FindStudentsByName(Student* students, int count, const char* name);
Student* FindStudentsBySurname(Student* students, int count, const char* surname);
Student* FindStudentsByGroup(Student* students, int count, const char* group);
float CalculateAverage(Student *student);
void LogStudentsWithHighAverage(FILE* out, Student* students, int count);
char *ReadString(FILE *file);
char *ReadStringForSpace(FILE *file);
void FreeStudents(Student *students, ssize_t count);

#endif
