#ifndef INC_7_7_H
#define INC_7_7_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


Node *CreateNode(Liver data);
Node *InsertSorted(Node *head, Liver data);
void FreeList(Node *head);

int PushStack(StackNode **stack, Node *head);
void FreeStack(StackNode *stack);

Node *LoadFromFile(const char *filename);
int SaveToFile(Node *head, const char *filename);
Node *AddResident(Node *head, const char *surname, const char *name, const char *patronymic,
				  int day, int month, int year, char gender, double income);
Node *DeleteResident(Node *head, const char *surname, const char *name);
Node *SearchResident(Node *head, const char *surname, const char *name);
void DisplayResidents(const Node *head);
char *CopyString(const char *str);
Node *CopyList(Node *head);
int PerformUndo(Node **head, StackNode **undo_stack);

#endif
