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
