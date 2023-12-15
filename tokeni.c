#include "shell.h"


/**
 * tokenize_input - Splits a buffer into tokens using a delimiter
 * @input_buffer: Buffer to tokenize
 * @delimit: Delimiter for tokenization
 *
 * Return: Pointer to an array of pointers to the tokens
 */
char **tokenize_input(char *input_buffer, char *delimit)
{
	char **tokens = NULL;
	size_t i = 0, maxc = 10;

	if (input_buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * maxc);
	if (tokens == NULL)
	{
		perror("Syntax Error");
		return (NULL);
	}
	while ((tokens[i] = custom_strtok(input_buffer, delimit)) != NULL)
	{
		i++;
		if (i == maxc)
		{
			tokens = custom_reallocate(tokens, &maxc);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		input_buffer = NULL;
	}
	return (tokens);
}
