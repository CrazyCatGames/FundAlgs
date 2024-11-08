#include "../include/7.h"

int CheckData(int x) {
	return (x % 4 == 0 && x % 100 != 0) || (x % 400 == 0);
}

int ValidData(int day, int month, int year) {
	if (year <= 0 || month < 1 || month > 12 || day < 1) return 0;

	int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && CheckData(year)) days_in_month[2] = 29;

	return day <= days_in_month[month];
}

Node *LoadFromFile(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) return NULL;

	Node *head = NULL;
	char *line = NULL;
	size_t len = 0;

	while (getline(&line, &len, file) != -1) {
		Liver temp;

		char *token = strtok(line, " ");
		if (token != NULL) {
			temp.surname = strdup(token);
		}

		token = strtok(NULL, " ");
		if (token != NULL) {
			temp.name = strdup(token);
		}

		token = strtok(NULL, " ");
		if (token != NULL) {
			temp.patronymic = strdup(token);
		}

		token = strtok(NULL, " ");
		temp.birth_day = token ? atoi(token) : 0;

		token = strtok(NULL, " ");
		temp.birth_month = token ? atoi(token) : 0;

		token = strtok(NULL, " ");
		temp.birth_year = token ? atoi(token) : 0;

		token = strtok(NULL, " ");
		temp.gender = token ? token[0] : ' ';

		token = strtok(NULL, " ");
		temp.income = token ? atof(token) : 0.0;

		if (temp.birth_day < 0 || temp.birth_month < 0 || temp.birth_year < 0 || temp.income < 0) {
			free(temp.surname);
			free(temp.name);
			free(temp.patronymic);
			fclose(file);
			free(line);
			return NULL;
		}

		if (!ValidData(temp.birth_day, temp.birth_month, temp.birth_year)) {
			free(temp.surname);
			free(temp.name);
			free(temp.patronymic);
			fclose(file);
			free(line);
			return NULL;
		}

		head = InsertSorted(head, temp);
		if (!head) return NULL;
	}

	free(line);
	fclose(file);
	return head;
}

int SaveToFile(Node *head, const char *filename) {
	FILE *file = fopen(filename, "w");
	if (!file) return 1;

	Node *current = head;
	while (current) {
		fprintf(file, "%s %s %s %d %d %d %c %lf\n",
				current->data.surname, current->data.name, current->data.patronymic ? current->data.patronymic : "-",
				current->data.birth_day, current->data.birth_month, current->data.birth_year,
				current->data.gender, current->data.income);
		current = current->next;
	}
	fclose(file);
	return 0;
}

Node *DeleteResident(Node *head, const char *surname, const char *name) {
	Node *current = head;
	Node *prev = NULL;

	while (current) {
		if (strcmp(current->data.surname, surname) == 0 && strcmp(current->data.name, name) == 0) {
			if (prev) {
				prev->next = current->next;
			} else {
				head = current->next;
			}

			free(current->data.surname);
			free(current->data.name);
			if (current->data.patronymic) {
				free(current->data.patronymic);
			}
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
	return head;
}

Node *AddResident(Node *head, const char *surname, const char *name, const char *patronymic,
				  int day, int month, int year, char gender, double income) {
	Liver temp;
	temp.surname = strdup(surname);
	temp.name = strdup(name);
	temp.patronymic = (patronymic && *patronymic) ? strdup(patronymic) : NULL;
	temp.birth_day = day;
	temp.birth_month = month;
	temp.birth_year = year;
	temp.gender = gender;
	temp.income = income;

	head = InsertSorted(head, temp);
	return head;
}

Node *SearchResident(Node *head, const char *surname, const char *name) {
	Node *current = head;
	while (current) {
		if (strcmp(current->data.surname, surname) == 0 &&
			strcmp(current->data.name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void DisplayResidents(const Node *head) {
	const Node *current = head;
	while (current) {
		printf("Surname: %s, Name: %s, Patronymic: %s, Data of birth: %02d.%02d.%04d, Gender: %c, Salary: %.2lf\n",
			   current->data.surname, current->data.name,
			   current->data.patronymic ? current->data.patronymic : "-",
			   current->data.birth_day, current->data.birth_month, current->data.birth_year,
			   current->data.gender, current->data.income);
		current = current->next;
	}
}

int PerformUndo(Node **head, StackNode **undo_stack) {
	int count = 0;
	StackNode *temp = *undo_stack;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}

	int undo_count = (count + 1) / 2;
	if (undo_count == 0) return 1;

	for (int i = 0; i < undo_count; i++) {
		if (*undo_stack == NULL) break;

		StackNode *top = *undo_stack;

		*head = top->state;
		*undo_stack = top->next;

		FreeStack(top);
	}
	return 0;
}
