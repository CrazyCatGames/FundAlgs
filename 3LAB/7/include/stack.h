#ifndef INC_7_STACK_H
#define INC_7_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "7.h"
#include "list.h"

typedef struct StackNode {
	Node *state;
	struct UndoStack *next;
} StackNode;

void push_stack(StackNode **stack, Node *head);
Node *pop_stack(StackNode **stack);
void free_stack(StackNode *stack);

#endif
