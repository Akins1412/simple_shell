#include "shell.h"

/**
 * check_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int check_match(char c, const char *string)
{
	unsigned int i;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (c == string[i])
			return (1);
	}
	return (0);
}

/**
 * new_strtok - custom strtok
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *new_strtok(char *str, const char *delimit)
{
	static char *tokbegin;
	static char *tokenxt;
	unsigned int i;

	if (str != NULL)
		tokenxt = str;
	tokbegin = tokenxt;
	if (tokbegin == NULL)
		return (NULL);
	for (i = 0; tokenxt[i] != '\0'; i++)
	{
		if (check_match(tokenxt[i], delimit) == 0)
			break;
	}
	if (tokenxt[i] == '\0' || tokenxt[i] == '#')
	{
		tokenxt = NULL;
		return (NULL);
	}
	tokbegin = tokenxt + i;
	next_token = token_start;
	for (i = 0; tokenxt[i] != '\0'; i++)
	{
		if (check_match(tokenxt[i], delimit) == 1)
			break;
	}
	if (tokenxt[i] == '\0')
		tokenxt = NULL;
	else
	{
		tokenxt[i] = '\0';
		tokenxt = tokenxt + i + 1;
		if (*tokenxt == '\0')
			tokenxt = NULL;
	}
	return (tokbegin);
}
