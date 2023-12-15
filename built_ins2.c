#include "shell.h"

/**
 * add_environment_key - Creates a new environment variable
 * @vars: Pointer to the structure of shell variables
 *
 * Return: void
 */
void add_environment_key(shell_vars_t *vars)
{
	unsigned int i;
	char **recenv;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	recenv = malloc(sizeof(char *) * (i + 2));
	if (recenv == NULL)
	{
		display_error(vars, NULL);
		vars->exit_status = 127;
		exiecute_exit(vars);
	}
	for (i = 0; vars->env[i] != NULL; i++)
		recenv[i] = vars->env[i];
	recenv[i] = add_environment_value(vars->av[1], vars->av[2]);
	if (recenv[i] == NULL)
	{
		display_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		release_env(vars->env);
		free(recenv);
		exit(127);
	}
	recenv[i + 1] = NULL;
	free(vars->env);
	vars->env = recenv;
}

/**
 * find_environment_key - Locates an environment variable
 * @env: Array of environment variables
 * @key: Environment variable to find
 *
 * Return: Pointer to the address of the environment variable
 */
char **find_environment_key(char **env, char *key)
{
	unsigned int i, j, l;

	l = get_string_length(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < l; j++)
			if (key[j] != env[i][j])
				break;
		if (j == l && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_environment_value - Creates a new environment variable string
 * @key: Variable name
 * @value: Variable value
 *
 * Return: Pointer to the new string
 */
char *add_environment_value(char *key, char *value)
{
	unsigned int l1, l2, i, j;
	char *new;

	l1 = get_string_length(key);
	l2 = get_string_length(value);
	new = malloc(sizeof(char) * (l1 + l2 + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * convert_string_to_int - Converts a string into an integer
 * @str: String to convert
 *
 * Return: The integer value, or -1 if an error occurs
 */
int convert_string_to_int(char *str)
{
	unsigned int i, num;
	int n = 0, n_test;

	n_test = INT_MAX;
	for (num = 0; n_test != 0; num++)
		n_test /= 10;
	for (i = 0; str[i] != '\0' && i < num; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == num - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		n += str[i] - '0';
		if ((i == num - 2) && (str[i + 1] != '\0') && (n > INT_MAX / 10))
			return (-1);
	}
	if (i > num)
		return (-1);
	return (n);
}
