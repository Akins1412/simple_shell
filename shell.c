#include "shell.h"

/* global variable for ^C handling */
unsigned int signal_flag;

/**
 * sig_handler - handles the interrupt signal (^C)
 * @xxy: unused variable (required for the signal function prototype)
 *
 * Return: void
 */
static void signal_handler(int xxy)
{
	(void) xxy;
	if (signal_flag == 0)
		print_string("\n$ ");
	else
		print_string("\n");
}

/**
 * main - the main function for the shell
 * @argc: the number of arguments passed to main
 * @argv: the array of arguments passed to main
 * @environment: the array of environment variables
 *
 * Return: 0 on success, exit status on failure, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t buffer = 0;
	unsigned int pipe_present = 0, i;
	shell_vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = init_env(environment);
	signal(SIGINT, signal_handler);
	if (!isatty(STDIN_FILENO))
		pipe_present = 1;
	if (pipe_present == 0)
		print_string("$ ");
	signal_flag = 0;
	while (getline(&(vars.buffer), &buffer, stdin) != -1)
	{
		signal_flag = 1;
		vars.count++;
		vars.commands = tokenize_input(vars.buffer, ";");
		for (i = 0; vars.commands && vars.commands[i] != NULL; i++)
		{
			vars.av = tokenize_input(vars.commands[i], "\n \t\r");
			if (vars.av && vars.av[0])
				if (identify_builtin(&vars) == NULL)
					checkPath(&vars);
			free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		signal_flag = 0;
		if (pipe_present == 0)
			print_string("$ ");
		vars.buffer = NULL;
	}
	if (pipe_present == 0)
		print_string("\n");
	release_env(vars.env);
	free(vars.buffer);
	exit(vars.exit_status);
}

