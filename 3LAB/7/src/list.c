#include "../include/7.h"

char *CopyString(const char *str) {
	if (str == NULL) return NULL;
	char *new_str = malloc(strlen(str) + 1);
	if (new_str) {
		strcpy(new_str, str);
	} else {
		return NULL;
	}
	return new_str;
}

Node *CopyList(Node *head) {
	if (!head) return NULL;

	Node *new_head = NULL;
	Node *new_tail = NULL;

	while (head) {
		Node *new_node = (Node *) malloc(sizeof(Node));
		if (!new_node) {
			FreeList(new_head);
			return NULL;
		}

		new_node->data.surname = CopyString(head->data.surname);
		new_node->data.name = CopyString(head->data.name);
		new_node->data.patronymic = CopyString(head->data.patronymic);
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

Node *CreateNode(Liver data) {
	Node *new_node = (Node *) malloc(sizeof(Node));
	if (!new_node) return NULL;

	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

Node *InsertSorted(Node *head, Liver data) {
	Node *new_node = CreateNode(data);
	if (!new_node) return NULL;

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

void FreeList(Node *head) {
	Node *current = head;
	while (current) {
		free(current->data.surname);
		free(current->data.name);
		if (current->data.patronymic) free(current->data.patronymic);

		Node *temp = current;
		current = current->next;
		free(temp);
	}
}
