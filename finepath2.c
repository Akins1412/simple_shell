/**
 * findPath - finds the PATH variable in the environment
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *findPath(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}
/**
 * checkPath - checks if the command is present in the PATH
 * @vars: variables
 *
 * Return: void
 */
void checkPath(shell_vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (checkForDirectory(vars->av[0]))
		r = executeCwd(vars);
	else
	{
		path = findPath(vars->env);
		if (path != NULL)
		{
			path_dup = duplicate_string(path + 5);
			path_tokens = tokenize_input(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = concatenate_strings(path_tokens[i], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = executePath(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->exit_status = 127;
				exiecute_exit(vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			display_error(vars, ": not found\n");
			vars->exit_status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		exiecute_exit(vars);
}
