#include "../include/7.h"

int PushStack(StackNode **stack, Node *head) {
	StackNode *new_node = (StackNode *) malloc(sizeof(StackNode));
	if (!new_node) return 1;

	new_node->state = CopyList(head);
	new_node->next = *stack;
	*stack = new_node;
	return 0;
}

void FreeStack(StackNode *stack) {
	while (stack) {
		StackNode *temp = stack;
		stack = stack->next;
		FreeList(temp->state);
		free(temp);
	}
}