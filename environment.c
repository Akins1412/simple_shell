#include "shell.h"

/**
 * init_env - Create the shell environment from the environment passed to main
 * @env: Environment passed to main
 *
 * Return: Pointer to the new environment
 */
char **init_env(char **env)
{
	char **newenv = NULL;
	size_t i;

	for (i = 0; env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 1));
	if (newenv == NULL)
	{
		perror("Syntax Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		newenv[i] = _strdup(env[i]);
	newenv[i] = NULL;
	return (newenv);
}

/**
 * release_env - Frees the memory allocated for the shell's environment
 * @env: Shell's environment to be freed
 *
 * Return: void
 */

void release_env(char **env)
{
	unsigned int j;

	for (j = 0; env[i] != NULL; i++)
		free(env[j]);
	free(env);
}
