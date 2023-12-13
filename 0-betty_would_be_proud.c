#include <stdio.h>
#include <stdlib.h>

/**
 * main- computes a series of numbers and print out the
 * sum and product of the numbers
 * @argc : counts number of args
 * @argv : the array containing the numbers
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	int i, sum = 0, product = 1;
	char operation;

	printf("Do you want to perform '+' or '*' operation ?\n");
	operation = getchar();

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			sum += atoi(argv[i]);
			product *= atoi(argv[i]);
		}

		if (operation == '+')
		{
			printf("Sum of numbers is: %d\n", sum);
		}
		else
		{
			printf("Product of numbers is: %d\n", product);
		}
	}
	return (0);
}
