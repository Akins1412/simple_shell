#include "shell.h"
/**
 * executePath - executes a command in the specified path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int executePath(char *command, shell_vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			display_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				display_error(vars, NULL);
		}
		else
		{
			wait(&vars->ext_status);
			if (WIFEXITED(vars->exit_status))
				vars->exit_status = WEXITSTATUS(vars->exit_status);
			else if (WIFSIGNALED(vars->exit_status) && WTERMSIG(vars->exit_status) == SIGINT)
				vars->exit_status = 130;
			return (0);
		}
		vars->exit_status = 127;
		return (1);
	}
	else
	{
		display_error(vars, ": Permission denied\n");
		vars->exit_status = 126;
	}
	return (0);
}
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
/**
 * executeCwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int executeCwd(shell_vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				display_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					display_error(vars, NULL);
			}
			else
			{
				wait(&vars->exit_status);
				if (WIFEXITED(vars->exit_status))
					vars->exit_status = WEXITSTATUS(vars->exit_status);
				else if (WIFSIGNALED(vars->exit_status) && WTERMSIG(vars->exit_status) == SIGINT)
					vars->exit_status = 130;
				return (0);
			}
			vars->exit_status = 127;
			return (1);
		}
		else
		{
			display_error(vars, ": Permission denied\n");
			vars->exit_status = 126;
		}
		return (0);
	}
	display_error(vars, ": not found\n");
	vars->exit_status = 127;
	return (0);
}
/**
 * checkIfCommandInPath - checks if the command includes a path
 * @command: command string
 *
 * Return: 1 on success, 0 on failure
 */
int checkForDirectory(char *string)
{
	unsigned int i;

	for (i = 0; string[i]; i++)
	{
		if (string[i] == '/')
			return (1);
	}
	return (0);
}
