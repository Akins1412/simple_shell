#include "shell.h"

/**
 * display_error - outputs error messages to the standard error stream
 * @vars: pointer to the variables structure
 * @msg: message to be displayed
 *
 * Returns: void
 */
void display_error(shell_vars_t *vars, char *message)
{
	char *count;

	custom_puts2(vars->argv[0]);
	custom_puts2(": ");
	count = custom_uitoa(vars->count);
	custom_puts2(count);
	free(count);
	custom_puts2(": ");
	custom_puts2(vars->av[0]);
	if (message)
	{
		custom_puts2(message);
	}
	else
		perror("");
}

/**
 * custom_puts2 - outputs a string to the standard error stream
 * @str: string to be printed
 *
 * Returns: void
 */
void custom_puts2(char *str)
{
	ssize_t n, l;

	n = get_string_length(str);
	l = write(STDERR_FILENO, str, n);
	if (l != n)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * custom_uitoa - converts an unsigned integer to a string
 * @count: unsigned integer to be converted
 *
 * Returns: pointer to the resulting string
 */
char *custom_uitoa(unsigned int count)
{
	char *nstr;
	unsigned int temp, num;

	temp = count;
	for (num = 0; temp != 0; num++)
		temp /= 10;
	nstr = malloc(sizeof(char) * (num + 1));
	if (nstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	nstr[num] = '\0';
	for (--num; count; --num)
	{
		nstr[num] = (count % 10) + '0';
		count /= 10;
	}
	return (nstr);
}
