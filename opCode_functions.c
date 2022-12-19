#include "monty.h"

/**
 * _push - pushes an element to the stack
 * @stack: head node of stack linked list
 * @line_number: opcode line number
 * Return: Nothing
 */

void _push(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *new = malloc(sizeof(stack_t));

	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (*stack == NULL)
	{
		new->prev = NULL;
		new->next = NULL;
		*stack = new;
		top = new;
	}
	else
	{
		top->next = new;
		new->next = NULL;
		new->prev = top;
		top = new;
	}

}

/**
 * _pall - prints all the values on the stack starting from the top
 * @stack: Address of stack
 * @line_number: opcode line number
 * Return: Nothing
 */
void _pall(stack_t **stack __attribute__((unused)),
		unsigned int line_number __attribute__((unused)))
{
	stack_t *temp = top;

	while (top)
	{
		printf("%d\n", top->n);
		top = top->prev;
	}
	top = temp;
}
