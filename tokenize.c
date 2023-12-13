#include "shell.h"


/**
 * tokenize_input - Splits a buffer into tokens using a delimiter
 * @input_buffer: Buffer to tokenize
 * @delimiter: Delimiter for tokenization
 *
 * Return: Pointer to an array of pointers to the tokens
 */
char **tokenize_input(char *input_buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t i = 0, mcount = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Syntax Error");
		return (NULL);
	}
	while ((tokens[i] = custom_strtok(buffer, delimiter)) != NULL)
	{
		i++;
		if (i == mcount)
		{
			tokens = resize_array(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
