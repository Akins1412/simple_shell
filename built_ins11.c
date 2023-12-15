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
