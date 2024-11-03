#include "../include/7.h"

char *copy_string(const char *str) {
	if (str == NULL) return NULL;
	char *new_str = malloc(strlen(str) + 1);
	if (new_str) {
		strcpy(new_str, str);
	}
	return new_str;
}

// Функция для создания копии списка
Node *copy_list(Node *head) {
	if (!head) return NULL;

	Node *new_head = NULL;
	Node *new_tail = NULL;

	// Идем по списку и создаем копию каждого элемента
	while (head) {
		Node *new_node = malloc(sizeof(Node));
		if (!new_node) {
			free_list(new_head);
			return NULL;
		}

		new_node->data.surname = copy_string(head->data.surname);
		new_node->data.name = copy_string(head->data.name);
		new_node->data.patronymic = copy_string(head->data.patronymic);
		new_node->data.birth_day = head->data.birth_day;
		new_node->data.birth_month = head->data.birth_month;
		new_node->data.birth_year = head->data.birth_year;
		new_node->data.gender = head->data.gender;
		new_node->data.income = head->data.income;
		new_node->next = NULL;

		if (!new_head) {
			new_head = new_node;
		} else {
			new_tail->next = new_node;
		}
		new_tail = new_node;

		head = head->next;
	}

	return new_head;
}

Node *create_node(Liver data) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (!new_node) {
		perror("Ошибка выделения памяти");
		exit(1);
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

Node *insert_sorted(Node *head, Liver data) {
	Node *new_node = create_node(data);
	if (!head || (data.birth_year < head->data.birth_year) ||
		(data.birth_year == head->data.birth_year && data.birth_month < head->data.birth_month) ||
		(data.birth_year == head->data.birth_year && data.birth_month == head->data.birth_month &&
		 data.birth_day < head->data.birth_day)) {
		new_node->next = head;
		return new_node;
	}
	Node *current = head;
	while (current->next &&
		   (current->next->data.birth_year < data.birth_year ||
			(current->next->data.birth_year == data.birth_year && current->next->data.birth_month < data.birth_month) ||
			(current->next->data.birth_year == data.birth_year && current->next->data.birth_month == data.birth_month &&
			 current->next->data.birth_day < data.birth_day))) {
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
	return head;
}

void free_list(Node *head) {
	Node *current = head;
	while (current) {
		free(current->data.surname);
		free(current->data.name);
		if (current->data.patronymic) {
			free(current->data.patronymic);
		}
		Node *temp = current;
		current = current->next;
		free(temp);
	}
}
