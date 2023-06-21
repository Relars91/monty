#include "monty.h"

/**
 * get_opcode - function that returns a function pointer to buildin function
 * @opcode: string with the opcode
 *
 * Return: fucntion pointer to function
 */
void (*get_opcode(char *opcode))(stack_t **stack, unsigned int line_number)
{
	unsigned int i = 0;
	instruction_t instructions[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{"stack", _stack},
		{"queue", _queue},
		{NULL, NULL}
	};

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
			break;
	}
	return (instructions[i].f);
}

/**
 * init_vars - initializates tthe variables of a vars_t structure
 * @vars: pointer to a vars_t estructure
 *
 * Return: nothing
 */
void init_vars(vars_t *vars)
{
	vars->line = NULL;
	vars->len_line = 0;
	vars->fp = NULL;
	vars->opcode = NULL;
	vars->op = NULL;
	vars->stack = NULL;
	vars->lines = 1;
}
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of srings with the arguments
 *
 * Return: 0 on succes
 */
int main(int argc, char *argv[])
{
	vars_t vars;

	e_vars.len_stack = 0;
	e_vars.stack_mode = STACK;
	init_vars(&vars);
	on_exit(exit_handler, &vars);
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	vars.fp = fopen(argv[1], "r");
	if (vars.fp == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	for (; getline(&(vars.line), &(vars.len_line), vars.fp) != -1; vars.lines++)
	{
		vars.opcode = strtok(vars.line, " \n\t\r");
		e_vars.op_arg = strtok(NULL, " \n\t\r");
		if (vars.opcode == NULL || vars.opcode[0] == '#')
			continue;
		vars.op = get_opcode(vars.opcode);
		if (vars.op != NULL)
			vars.op(&(vars.stack), vars.lines);
		else
		{
			dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
				vars.lines, vars.opcode);
			exit(EXIT_FAILURE);
		}
		free(vars.line);
		vars.line = NULL;
	}
	exit(EXIT_SUCCESS);
}

/**
 * exit_handler - handles the exit with the function on exit
 * @status: exit status (UNUSED)
 * @arg: argument in this case a vars_t structure
 *
 * Return: nothing
 */
void exit_handler(int status, void *arg)
{
	vars_t *vars = (vars_t *) arg;

	(void) status;
	if (vars->line != NULL)
		free(vars->line);
	if (vars->fp != NULL)
		fclose(vars->fp);
	if (vars->stack != NULL)
		free_stack(vars->stack);
}
