#include "include/7.h"

int ReadString(char **str) {
	*str = (char *) malloc(16 * sizeof(char));
	if (!*str) {
		return -2;
	}
	int capacity = 16, length = 0;
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF) {
		if (length + 1 >= capacity) {
			capacity *= 2;
			char *tmp = (char *) realloc(*str, capacity);
			if (!tmp) {
				return -1;
			}
			*str = tmp;
		}
		(*str)[length++] = ch;
	}
	if (*str) {
		(*str)[length] = '\0';
	}
	return 0;
}

int DayMonth(int month, int year) {
	if (month == 2) {
		return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	return 31;
}

int IsValidDate(int day, int month, int year) {
	if (year < 0) return 0;
	if (month < 1 || month > 12) return 0;
	if (day < 1 || day > DayMonth(month, year)) return 0;

	return 1;
}

int main() {
	Node *head = NULL;
	StackNode *undo_stack = NULL;
	char command[20];
	char *filename = NULL;

	printf("Enter filename: ");
	int term = ReadString(&filename);
	if (term == -1) {
		free(filename);
		fprintf(stderr, "Error alloc memory.\n");
		return 1;
	} else if (term == -2) {
		fprintf(stderr, "Error alloc memory.\n");
		return 1;
	}

	head = LoadFromFile(filename);
	if (head) {
		printf("Data uploaded from %s.\n", filename);
	} else {
		fprintf(stderr, "Error upload data.\n");
		FreeList(head);
		FreeStack(undo_stack);
		free(filename);
		return 1;
	}

	while (1) {
		printf("\nEnter a command (search, add, delete, edit, display, save, undo, quit): ");
		scanf("%s", command);
		getchar();

		if (strcmp(command, "add") == 0) {
			char *surname = NULL, *name = NULL, *patronymic = NULL;
			int day, month, year;
			char gender;
			double income;

			printf("Enter surname: ");
			char tmp = ReadString(&surname);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}
			printf("Enter name: ");
			tmp = ReadString(&name);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}
			printf("Enter patronymic (or '-'): ");
			tmp = ReadString(&patronymic);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(patronymic);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}

			while (1) {
				printf("Enter date of birth (day month year): ");
				scanf("%d %d %d", &day, &month, &year);
				getchar();
				if (IsValidDate(day, month, year)) {
					break;
				}
				printf("Invalid date. Please try again.\n");
			}

			while (1) {
				printf("Enter gender (M/W): ");
				scanf(" %c", &gender);
				if ((gender == 'M' || gender == 'W')) {
					break;
				}
				printf("Invalid gender. Please enter 'M' or 'W'.\n");
			}

			while (1) {
				printf("Enter salary: ");
				scanf("%lf", &income);
				if (income >= 0) {
					break;
				}
				printf("Invalid salary. Please enter a non-negative number.\n");
			}

			if (PushStack(&undo_stack, head)) {
				free(patronymic);
				free(surname);
				free(name);
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				fprintf(stderr, "Error malloc memory.\n");
				return 1;
			}

			head = AddResident(head, surname, name, patronymic, day, month, year, gender, income);
			printf("Liver added.\n");
			free(patronymic);
			free(surname);
			free(name);

		} else if (strcmp(command, "search") == 0) {
			char *surname = NULL, *name = NULL;
			printf("Enter surname: ");
			int tmp = ReadString(&surname);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}
			printf("Enter name: ");
			tmp = ReadString(&name);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}

			if (PushStack(&undo_stack, head)){
				free(surname);
				free(name);
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				fprintf(stderr, "Error malloc memory.\n");
				return 1;
			}

			Node *current = SearchResident(head, surname, name);
			if (current) {
				printf("Surname: %s, Name: %s, Patronymic: %s, Data of birth: %02d.%02d.%04d, Gender: %c, Salary: %.2lf\n",
					   current->data.surname, current->data.name,
					   current->data.patronymic ? current->data.patronymic : "-",
					   current->data.birth_day, current->data.birth_month, current->data.birth_year,
					   current->data.gender, current->data.income);
			} else {
				printf("Liver didn't found.\n");
			}

			free(surname);
			free(name);

		} else if (strcmp(command, "delete") == 0) {
			char *surname = NULL, *name = NULL;
			printf("Enter surname: ");
			int tmp = ReadString(&surname);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}
			printf("Enter name: ");
			tmp = ReadString(&name);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}

			if (PushStack(&undo_stack, head)){
				free(surname);
				free(name);
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				fprintf(stderr, "Error malloc memory.\n");
				return 1;
			}

			head = DeleteResident(head, surname, name);
			printf("Liver removed.\n");

			free(surname);
			free(name);

		} else if (strcmp(command, "edit") == 0) {
			char *surname = NULL, *name = NULL;
			printf("Enter surname: ");
			int tmp = ReadString(&surname);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}
			printf("Enter name: ");
			tmp = ReadString(&name);
			if (tmp == -1) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				free(name);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			} else if (tmp == -2) {
				fprintf(stderr, "Error alloc memory.\n");
				FreeList(head);
				free(surname);
				FreeStack(undo_stack);
				free(filename);
				return 1;
			}

			Node *resident = SearchResident(head, surname, name);
			if (resident) {
				if (PushStack(&undo_stack, head)){
					free(surname);
					free(name);
					FreeList(head);
					FreeStack(undo_stack);
					free(filename);
					fprintf(stderr, "Error malloc memory.\n");
					return 1;
				}

				printf("Editing resident %s %s\n", surname, name);

				char *new_surname = NULL, *new_name = NULL, *new_patronymic = NULL;
				int day, month, year;
				double income;
				char gender;

				printf("Enter new surname (or press enter to keep current): ");
				ReadString(&new_surname);
				if (strlen(new_surname) > 0) {
					free(resident->data.surname);
					resident->data.surname = new_surname;
				} else {
					free(new_surname);
				}

				printf("Enter new name (or press enter to keep current): ");
				ReadString(&new_name);
				if (strlen(new_name) > 0) {
					free(resident->data.name);
					resident->data.name = new_name;
				} else {
					free(new_name);
				}

				printf("Enter new patronymic (or '-' to remove, press enter to keep current): ");
				ReadString(&new_patronymic);
				if (strcmp(new_patronymic, "-") == 0) {
					free(resident->data.patronymic);
					resident->data.patronymic = NULL;
					free(new_patronymic);
				} else if (strlen(new_patronymic) > 0) {
					free(resident->data.patronymic);
					resident->data.patronymic = new_patronymic;
				} else {
					free(new_patronymic);
				}
				while (1) {
					printf("Enter new date of birth (day month year): ");
					scanf("%d %d %d", &day, &month, &year);
					getchar();
					if (IsValidDate(day, month, year)) {
						resident->data.birth_day = day;
						resident->data.birth_month = month;
						resident->data.birth_year = year;
						break;
					} else {
						printf("Invalid date. Please try again.\n");
					}
				}

				while (1) {
					printf("Enter new gender (M/W): ");
					scanf(" %c", &gender);
					getchar();
					if ((gender == 'M' || gender == 'W')) {
						resident->data.gender = gender;
						break;
					} else {
						printf("Invalid gender. Please enter 'M' or 'W'.\n");
					}
				}

				while (1) {
					printf("Enter new salary: ");
					scanf("%lf", &income);
					getchar();
					if (income >= 0) {
						resident->data.income = income;
						break;
					} else {
						printf("Invalid salary. Please enter a positive number.\n");
					}
				}

				printf("Resident updated.\n");
			} else {
				printf("Resident not found.\n");
			}

			free(surname);
			free(name);

		} else if (strcmp(command, "display") == 0) {
			DisplayResidents(head);

		} else if (strcmp(command, "save") == 0) {
			char *filenameout = NULL;
			printf("Enter file path to save data: ");
			int tmp = ReadString(&filenameout);
			if (tmp == -2) {
				FreeList(head);
				FreeStack(undo_stack);
				return 1;
			} else if (tmp == -1) {
				FreeList(head);
				FreeStack(undo_stack);
				free(filenameout);
				return 1;
			}
			if (strcmp(filename, filenameout) == 0) {
				free(filenameout);
				fprintf(stderr, "Input file can't be output file. Saving is failed.\n");
				continue;
			}
			if (SaveToFile(head, filenameout)) {
				fprintf(stderr, "Error open file.\n");
				break;
			}
			printf("Data saved in file: %s.\n", filenameout);
			free(filenameout);

		} else if (strcmp(command, "undo") == 0) {
			!PerformUndo(&head, &undo_stack) ? printf("Undo completed.\n") : printf("Nothing to undo.\n");

		} else if (strcmp(command, "quit") == 0) {
			break;

		} else {
			printf("Unknown command\n");
		}
	}

	FreeList(head);
	FreeStack(undo_stack);
	free(filename);
	return 0;
}