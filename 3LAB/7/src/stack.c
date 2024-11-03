#include "../include/7.h"

void push_stack(StackNode **stack, Node *head) {
	StackNode *new_node = malloc(sizeof(StackNode));
	new_node->state = copy_list(head);
	new_node->next = *stack;
	*stack = new_node;
}

Node *pop_stack(StackNode **stack) {
	if (!*stack) return NULL;
	StackNode *top = *stack;
	Node *state = top->state;
	*stack = top->next;
	free(top);
	return state;
}

void free_stack(StackNode *stack) {
	while (stack) {
		StackNode *temp = stack;
		stack = stack->next;
		free_list(temp->state);
		free(temp);
	}
}