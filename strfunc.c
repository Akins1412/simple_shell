#include "shell.h"

/**
 * print_string - Writes a string to the standard output
 * @str: String to be written
 *
 * Return: Number of characters printed or -1 on failure
 */
ssize_t print_string(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Syntax Error");
		return (-1);
	}
	return (len);
}

/**
 * duplicate_string - Creates a duplicate of the provided string in a new memory space
 * @str_to_duplicate: String to be duplicated
 *
 * Return: Pointer to the new duplicated string
 */
char *duplicate_string(char *str_to_duplicate)
{
	char *copy;

	int len, i;

	if (strtodup == 0)
		return (NULL);

	for (len = 0; strtodup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		copy[i] = strtodup[i];

	return (copy);
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
	while (strcmp1[i] == strcmp2[i])
	{
		if (strcmp1[i] == '\0')
			return (0);
		i++;
	}
	return (strcmp1[i] - strcmp2[i]);
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
	char *newstring;
	unsigned int len1, len2, newlen, i, j;

	len1 = 0;
	len2 = 0;
	if (strc1 == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; strc1[len1]; len1++)
			;
	}
	if (strc2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; strc2[len2]; len2++)
			;
	}
	newlen = len1 + len2 + 2;
	newstring = malloc(newlen * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		newstring[i] = strc1[i];
	newstring[i] = '/';
	for (j = 0; j < len2; j++)
		newstring[i + 1 + j] = strc2[j];
	newstring[len1 + len2 + 1] = '\0';
	return (newstring);
}

/**
 * get_string_length - Computes the length of a string
 * @str: String to be measured
 *
 * Return: Length of the string
 */
unsigned int get_string_length(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
