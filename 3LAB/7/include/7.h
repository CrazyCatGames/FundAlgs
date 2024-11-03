#ifndef INC_7_7_H
#define INC_7_7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Liver {
	char *surname;
	char *name;
	char *patronymic;
	int birth_day;
	int birth_month;
	int birth_year;
	char gender;
	double income;
} Liver;

typedef struct Node {
	Liver data;
	struct Node *next;
} Node;

typedef struct StackNode {
	Node *state;
	struct StackNode *next;
} StackNode;


Node *create_node(Liver data);
Node *insert_sorted(Node *head, Liver data);
void free_list(Node *head);

void push_stack(StackNode **stack, Node *head);
Node *pop_stack(StackNode **stack);
void free_stack(StackNode *stack);

Node *load_from_file(const char *filename);
int save_to_file(Node *head, const char *filename);
Node *add_resident(Node *head, const char *surname, const char *name, const char *patronymic,
				   int day, int month, int year, char gender, double income);
Node *delete_resident(Node *head, const char *surname, const char *name);
Node *search_resident(Node *head, const char *surname, const char *name);
void display_residents(const Node *head);
char *copy_string(const char *str);
Node *copy_list(Node *head);
int perform_undo(Node **head, StackNode **undo_stack);

#endif
