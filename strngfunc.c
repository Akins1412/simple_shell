#include "shell.h"

/**
 * print_string - Writes a string to the standard output
 * @str: String to be written
 *
 * Return: Number of characters printed or -1 on failure
 */
ssize_t print_string(char *str)
{
	ssize_t n, l;

	n = get_string_length(str);
	l = write(STDOUT_FILENO, str, n);
	if (l != n)
	{
		perror("Syntax Error");
		return (-1);
	}
	return (l);
}

/**
 * duplicate_string - Creates a duplicate of the
 * provided string in a new memory
 * @str_to_duplicate: String to be duplicated
 *
 * Return: Pointer to the new duplicated string
 */
char *duplicate_string(char *str_to_duplicate)
{
	char *ct;

	int l, i;

	if (str_to_duplicate == 0)
		return (NULL);

	for (l = 0; str_to_duplicate[l]; l++)
		;
	ct = malloc((l + 1) * sizeof(char));

	for (i = 0; i <= l; i++)
		ct[i] = str_to_duplicate[i];

	return (ct);
}

/**
 * compare_strings - Compares the lengths of two strings
 * @str1: First string to be compared in length
 * @str2: Second string to be compared
 *
 * Return: 0 on success, any other value indicates a failure
 */
int compare_strings(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0')
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}

/**
 * concatenate_strings - Concatenates two strings
 * @str1: First string
 * @str2: Second string
 *
 * Return: Pointer to the concatenated string
 */

char *concatenate_strings(char *str1, char *str2)
{
	char *news;
	unsigned int l1, l2, newl, i, j;

	l1 = 0;
	l2 = 0;
	if (str1 == NULL)
		l1 = 0;
	else
	{
		for (l1 = 0; str1[l1]; l1++)
			;
	}
	if (str2 == NULL)
		l2 = 0;
	else
	{
		for (l2 = 0; str2[l2]; l2++)
			;
	}
	newl = l1 + l2 + 2;
	news = malloc(newl * sizeof(char));
	if (news == NULL)
		return (NULL);
	for (i = 0; i < l1; i++)
		news[i] = str1[i];
	news[i] = '/';
	for (j = 0; j < l2; j++)
		news[i + 1 + j] = str2[j];
	news[l1 + l2 + 1] = '\0';
	return (news);
}

/**
 * get_string_length - Computes the length of a string
 * @str: String to be measured
 *
 * Return: Length of the string
 */
unsigned int get_string_length(char *str)
{
	unsigned int l;

	l = 0;

	for (l = 0; str[l]; l++)
		;
	return (l);
}
