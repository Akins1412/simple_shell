#include "shell.h"

/**
 * identify_builtin - Checks if the command is a built-in
 * @vars: Shell variables
 * Return: Pointer to the corresponding function or NULL
 */
void (*identify_builtin(shell_vars_t  *vars))(shell_vars_t  *vars)
{
	unsigned int i;
	builtin_t find[] = {
		{"exit", exiecute_exit},
		{"env", display_environment},
		{"setenv", execute_setenv},
		{"unsetenv", execute_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; find[i].function != NULL; i++)
	{
		if (compare_strings(vars->av[0], find[i].name) == 0)
			break;
	}
	if (find[i].function != NULL)
		find[i].function(vars);
	return (find[i].function);
}

/**
 * execute_exit - Exits the program
 * @vars: Shell variables
 *
 * Return: void
 */
void exiecute_exit(shell_vars_t  *vars)
{
	int stat;

	if (compare_strings(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		stat = convert_string_to_int(vars->av[1]);
		if (stat == -1)
		{
			vars->exit_status = 2;
			display_error(vars, ": Illegal number: ");
			custom_puts2(vars->av[1]);
			custom_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->exit_status = stat;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	release_env(vars->env);
	exit(vars->exit_status);
}

/**
 * display_environment - Prints the current environment
 * @vars: Structure of shell variables
 *
 * Return: void
 */
void display_environment(shell_vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		print_string(vars->env[i]);
		print_string("\n");
	}
	vars->exit_status = 0;
}

/**
 * execute_setenv - Creates a new environment variable or edits an existing one
 * @vars: Pointer to the structure of shell variables
 *
 * Return: void
 */
void execute_setenv(shell_vars_t *vars)
{
	char **ke;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		display_error(vars, ": Incorrect number of arguments\n");
		vars->exit_status = 2;
		return;
	}
	ke = find_environment_key(vars->env, vars->av[1]);
	if (ke == NULL)
		add_environment_key(vars);
	else
	{
		var = add_environment_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			display_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			release_env(vars->env);
			exit(127);
		}
		free(*ke);
		*ke = var;
	}
	vars->exit_status = 0;
}

/**
 * execute_unsetenv - Removes an environment variable
 * @vars: Pointer to a structure of shell variables
 *
 * Return: void
 */
void execute_unsetenv(shell_vars_t *vars)
{
	char **ke, **recenv;

	unsigned int i, j;

	if (vars->av[1] == NULL)
	{
		display_error(vars, ": Incorrect number of arguments\n");
		vars->exit_status = 2;
		return;
	}
	ke = find_environment_key(vars->env, vars->av[1]);
	if (ke == NULL)
	{
		display_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	recenv = malloc(sizeof(char *) * i);
	if (recenv == NULL)
	{
		display_error(vars, NULL);
		vars->exit_status = 127;
		exiecute_exit(vars);
	}
	for (i = 0; vars->env[i] != *ke; i++)
		recenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		recenv[i] = vars->env[j];
	recenv[i] = NULL;
	free(*ke);
	free(vars->env);
	vars->env = recenv;
	vars->exit_status = 0;
}
