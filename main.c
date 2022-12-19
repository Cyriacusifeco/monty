#include "monty.h"
stack_t *top = NULL;


/**
 * main - Entry point for monty program
 * @ac: argument count
 * @argv: command line argument vector
 * Return: 0 on success
 */

int main(int ac, char *argv[])
{
	stack_t *stack = NULL;


	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	read_file(&stack, argv[1]);

return (0);
}



/**
 * read_file - As the name implies
 * @stack: head of the stack
 * @file_name: the file to be read
 * Return: returns nothing.
 */

void read_file(stack_t **stack, char *file_name)
{

	int numChar;
	char *line = NULL;
	size_t buf = 0;
	int line_number = 0;

	FILE *fileHandle = fopen(file_name, "r");

	if (file_name == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}

	while ((numChar = getline(&line, &buf, fileHandle)) != -1)
	{
		line_number++;

		select_opCode(stack, line_number, line);
	}


	if (fclose(fileHandle) == -1)
		exit(EXIT_FAILURE);
	free(line);
}

/**
 * select_opCode - selects the operation to execute
 * @stack: Address of the head node.
 * @line_number: tracks the file's line number
 * @line: strings of command in file
 * Return: nothing.
 */

void select_opCode(stack_t **stack, int line_number, char *line)
{
	int i, len, index = 0;
	char *result;

	instruction_t ops[] = {
	{"push", _push},
	{"pall", _pall},
	{NULL, NULL}
};

	for (i = 0; ops[i].opcode != NULL; i++)
	{
		result = strstr(line, ops[i].opcode);

		if (result != NULL)
		{
			index = ((result - line) + strlen(ops[i].opcode));
			len = strlen(line);

			ops[i].f(stack, line_number);

			get_data(line, index, len);

			break;
		}
	}


}

/**
 * get_data - gets and adds data to stack
 * @line: command string
 * @index: keeps track of string position
 * @len: string lenght
 *
 * Return: nothing
 */

void get_data(char *line, int index, int len)
{
	int i = 0, num = 0;


	char *token = malloc(sizeof(char) * (len - index));

	if (token == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (line[index] != '\n')
	{
		if (line[index] != ' ' || line[index] != '\t')
		{
			token[i] = line[index];
		}

		i++;
		index++;
	}

	token[i] = '\0';

	num = atoi(token);

	if (num == -1)
	{
		printf("L<line_number>: unknown instruction <opcode>");
		exit(EXIT_FAILURE);
	}
	else
		top->n = num;

	free(token);
}
