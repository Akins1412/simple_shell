#include "shell.h"

/**
 * identify_builtin - Checks if the command is a built-in
 * @vars: Shell variables
 * Return: Pointer to the corresponding function or NULL
 */
void (*identify_builtin(shell_vars_t  * vars))(shell_vars_t  * vars)
{
	unsigned int i;
	builtin_t find[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; find[i].f != NULL; i++)
	{
		if (custom_strdup(vars->av[0], find[i].name) == 0)
			break;
	}
	if (find[i].f != NULL)
		find[i].f(vars);
	return (find[i].f);
}

/**
 * execute_exit - Exits the program
 * @vars: Shell variables
 *
 * Return: void
 */
void execute_exit(shell_vars_t *vars)
{
	int stat;

	if (custom_strdup(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		stat = _atoi(vars->av[1]);
		if (stat == -1)
		{
			vars->stat = 2;
			display_error(vars, ": Illegal number: ");
			custom_puts2(vars->av[1]);
			custom_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->stat = stat;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	release_env(vars->env);
	exit(vars->stat);
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
		custom_puts(vars->env[i]);
		custom_puts("\n");
	}
	vars->status = 0;
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
		vars->status = 2;
		return;
	}
	ke = find_environment_key(vars->env, vars->av[1]);
	if (ke == NULL)
		insert_key(vars);
	else
	{
		var = insert_key(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			display_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*ke);
		*ke = var;
	}
	vars->status = 0;
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
		vars->status = 2;
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
		vars->status = 127;
		exiecute_exit(vars);
	}
	for (i = 0; vars->env[i] != *ke; i++)
		recenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	recenv[i] = NULL;
	free(*ke);
	free(vars->env);
	vars->env = recenv;
	vars->status = 0;
}
