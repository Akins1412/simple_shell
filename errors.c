#include "shell.h"

/**
 * display_error - outputs error messages to the standard error stream
 * @vars: pointer to the variables structure
 * @msg: message to be displayed
 *
 * Returns: void
 */
void display_error(ShellVars *shell_vars, char *message)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (msg)
	{
		_puts2(msg);
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
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
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
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}
