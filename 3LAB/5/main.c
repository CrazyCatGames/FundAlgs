#include "include/5.h"

bool CorrectID(char *str);
bool CorrertStr(char *str);
void ClearStdin();
void InteractiveMenu(Student *students, int count, FILE *out);
void PrintStudentTable(Student *students, int count);

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Error. Use: %s <input_file> <output_file>\n", argv[0]);
		return 1;
	}
	Student *students;
	size_t count;
	size_t status = ReadStudents(argv[1], &students, &count);
	switch (status) {
		case -1:
			fprintf(stderr, "Error open file.\n");
			return 1;
		case -2:
			fprintf(stderr, "Error alloc memory.\n");
			return 2;
		case -3:
			fprintf(stderr, "Error read data.\n");
			return 3;
	}

	if (count == -1) {
		printf("Error reading from file.\n");
		return 2;
	}

	FILE *out = fopen(argv[2], "w");
	if (!out) {
		printf("Error opening file.\n");
		FreeStudents(students, count);
		return 3;
	}
	InteractiveMenu(students, count, out);
	FreeStudents(students, count);
	fclose(out);
}

bool CorrectID(char *str) {
	char *token = strtok(str, " ");
	if (token == NULL) {
		return false;
	}
	for (int i = 0; token[i] != '\0'; i++) {
		if (!isdigit(token[i])) {
			return false;
		}
	}

	token = strtok(NULL, " ");
	if (token != NULL) {
		return false;
	}

	return true;
}

bool CorrertStr(char *str) {
	char *token = strtok(str, " ");
	if (token == NULL) {
		return false;
	}

	token = strtok(NULL, " ");
	if (token != NULL) {
		return false;
	}

	return true;
}

void ClearStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	ungetc(c, stdin);
}

void InteractiveMenu(Student *students, int count, FILE *out) {
	char choice;
	char input[10];
	printf("\nMenu:\n");
	printf("1. Find student by ID\n");
	printf("2. Find students by surname\n");
	printf("3. Find students by name\n");
	printf("4. Find students by group\n");
	printf("5. Sort students by ID\n");
	printf("6. Sort students by surname\n");
	printf("7. Sort students by name\n");
	printf("8. Sort students by group\n");
	printf("9. Log students with above average grades\n");
	printf("p. Show student table\n");
	printf("0. Exit\n");

	do {
		printf("Choose an option: ");
		char t;
		if ((t = getchar()) == EOF) {
			printf("Exiting...\n");
			break;
		}
		ungetc(t, stdin);

		scanf("%9s", input);

		if (strlen(input) != 1 || sscanf(input, "%s", &choice) != 1) {
			ClearStdin();
			printf("Invalid input, please try again.\n");
			continue;
		}

		if ((t = getchar()) != '\n') {
			printf("Invalid input, please try again.\n");
			ClearStdin();
			continue;
		}

		ungetc(t, stdin);

		switch (input[0]) {
			case '1': {
				unsigned int id;
				printf("Enter student ID: ");
				char *in = ReadStringForSpace(stdin);
				if (!in) {
					fprintf(stderr, "Error alloc memory.\n");
					break;
				}

				if (!CorrectID(in)) {
					printf("Invalid input, please try again.\n");
					free(in);
					continue;
				}

				char *end;
				id = strtoul(in, &end, 10);
				if (*end != '\0') {
					printf("Incorrect input.\n");
					break;
				}

				Student *found_students = NULL;
				size_t found_count = 0;
				bool flag = false;
				for (size_t i = 0; i < count; i++) {
					if (students[i].id == id) {
						found_students = realloc(found_students, (found_count + 1) * sizeof(Student));
						if (!found_students) {
							fprintf(stderr, "Error realloc memory.\n");
							break;
						}
						flag = true;
						found_students[found_count] = students[i];
						found_count++;
					}
				}

				if (found_count > 0) {
					printf("Students found:\n");
					for (size_t i = 0; i < found_count; i++) {
						printf("%s %s, Group: %s\n", found_students[i].name, found_students[i].surname, found_students[i].group);
						LogStudentById(out, &students[i]);
					}
				} else {
					printf("Student with ID %u not found.\n", id);
				}
				if (flag) free(found_students);
				free(in);
				break;
			}
			case '2': {
				char *surname;
				printf("Enter student surname: ");
				surname = ReadStringForSpace(stdin);
				if (!surname) {
					fprintf(stderr, "Error alloc memory.\n");
					break;
				}
				if (!CorrertStr(surname)) {
					printf("Invalid input, please try again.\n");
					free(surname);
					continue;
				}

				Student *found_students = NULL;
				size_t found_count = 0;
				bool flag = false;
				for (size_t i = 0; i < count; i++) {
					if (strcmp(students[i].surname, surname) == 0) {
						found_students = realloc(found_students, (found_count + 1) * sizeof(Student));
						if (!found_students) {
							fprintf(stderr, "Error realloc memory.\n");
							break;
						}
						flag = true;
						found_students[found_count] = students[i];
						found_count++;
					}
				}

				if (found_count > 0) {
					printf("Students found:\n");
					for (size_t i = 0; i < found_count; i++) {
						printf("%s %s, Group: %s\n", found_students[i].name, found_students[i].surname, found_students[i].group);
					}
				} else {
					printf("Student with surname %s not found.\n", surname);
				}
				if (flag) free(found_students);
				free(surname);
				break;
			}
			case '3': {
				char *name;
				printf("Enter student name: ");
				name = ReadStringForSpace(stdin);
				if (!name) {
					fprintf(stderr, "Error alloc memory.\n");
					break;
				}
				if (!CorrertStr(name)) {
					printf("Invalid input, please try again.\n");
					free(name);
					continue;
				}

				Student *found_students = NULL;
				size_t found_count = 0;
				bool flag = false;
				for (size_t i = 0; i < count; i++) {
					if (strcmp(students[i].name, name) == 0) {
						found_students = realloc(found_students, (found_count + 1) * sizeof(Student));
						if (!found_students) {
							fprintf(stderr, "Error realloc memory.\n");
							break;
						}
						flag = true;
						found_students[found_count] = students[i];
						found_count++;
					}
				}

				if (found_count > 0) {
					printf("Students found:\n");
					for (size_t i = 0; i < found_count; i++) {
						printf("%s %s, Group: %s\n", found_students[i].name, found_students[i].surname, found_students[i].group);
					}
				} else {
					printf("Student with name %s not found.\n", name);
				}
				if (flag) free(found_students);
				free(name);
				break;
			}
			case '4': {
				char *group;
				printf("Enter student group: ");
				group = ReadStringForSpace(stdin);
				if (!group) {
					fprintf(stderr, "Error alloc memory.\n");
					break;
				}
				if (!CorrertStr(group)) {
					printf("Invalid input, please try again.\n");
					free(group);
					continue;
				}
				Student *found_students = NULL;
				size_t found_count = 0;
				bool flag = false;
				for (size_t i = 0; i < count; i++) {
					if (strcmp(students[i].group, group) == 0) {
						found_students = realloc(found_students, (found_count + 1) * sizeof(Student));
						if (!found_students) {
							fprintf(stderr, "Error realloc memory.\n");
							break;
						}
						flag = true;
						found_students[found_count] = students[i];
						found_count++;
					}
				}

				if (found_count > 0) {
					printf("Students found:\n");
					for (size_t i = 0; i < found_count; i++) {
						printf("%s %s, Group: %s\n", found_students[i].name, found_students[i].surname, found_students[i].group);
					}
				} else {
					printf("Student in group %s not found.\n", group);
				}
				if (flag) free(found_students);
				free(group);
				break;
			}
			case '5': {
				qsort(students, count, sizeof(Student), CompareById);
				printf("Students sorted by ID.\n");
				break;
			}
			case '6': {
				qsort(students, count, sizeof(Student), CompareBySurname);
				printf("Students sorted by surname.\n");
				break;
			}
			case '7': {
				qsort(students, count, sizeof(Student), CompareByName);
				printf("Students sorted by name.\n");
				break;
			}
			case '8': {
				qsort(students, count, sizeof(Student), CompareByGroup);
				printf("Students sorted by group.\n");
				break;
			}
			case '9':
				LogStudentsWithHighAverage(out, students, count);
				printf("Students with above average grades logged.\n");
				break;
			case '0':
				printf("Exiting...\n");
				break;
			case 'p':
				PrintStudentTable(students, count);
				break;
			default:
				printf("Invalid option, please try again.\n");
				break;
		}
	} while (input[0] != '0');
}

void PrintStudentTable(Student *students, int count) {
	printf("\n%-10s | %-15s | %-15s | %-10s | %-10s\n", "ID", "Name", "Surname", "Group", "Grades");
	printf("-----------------------------------------------------------------------------\n");
	for (int i = 0; i < count; i++) {
		printf("%-10u | %-15s | %-15s | %-10s | %d %d %d %d %d\n",
			   students[i].id, students[i].name, students[i].surname,
			   students[i].group, students[i].grades[0], students[i].grades[1], students[i].grades[2], students[i].grades[3], students[i].grades[4]);
	}
	printf("-----------------------------------------------------------------------------\n");
}
