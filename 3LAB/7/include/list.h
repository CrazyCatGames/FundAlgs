#ifndef INC_7_LIST_H
#define INC_7_LIST_H

#include "7.h"

typedef struct Node {
	Liver data;
	struct Node *next;
} Node;

Node *create_node(Liver data);
Node *insert_sorted(Node *head, Liver data);
void free_list(Node *head);

#endif
