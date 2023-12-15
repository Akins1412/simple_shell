#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct shell_variables - Holds shell-related variables
 * @av: Command line arguments
 * @buffer: Buffer containing the command
 * @env: Environment variables
 * @count: Count of entered commands
 * @argv: Arguments at the opening of the shell
 * @exit_status: Exit status of the shell
 * @commands: Double pointer to commands
 */
typedef struct shell_variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int exit_status;
	char **commands;
} shell_vars_t;


/**
 * struct builtin - Holds information for shell builtin commands
 * @name: Name of the builtin command
 * @function: Function pointer to the corresponding builtin function
 */
typedef struct builtin
{
	char *name;
	void (*function)(shell_vars_t *);
} builtin_t;

char **initialize_env(char **env);
void release_env(char **env);

ssize_t print_string(char *str);
char *duplicate_string(char *str_to_duplicate);
int compare_strings(char *str1, char *str2);
char *concatenate_strings(char *str1, char *str2);
unsigned int get_string_length(char *str);

void (*identify_builtin(shell_vars_t  *vars))(shell_vars_t  *vars);
void exiecute_exit(shell_vars_t  *vars);
void display_environment(shell_vars_t *vars);
void execute_setenv(shell_vars_t *vars);
void execute_unsetenv(shell_vars_t *vars);

char **tokenize_input(char *input_buffer, char *delimit);
char **custom_reallocate(char **point, size_t *size);
char *custom_strtok(char *str, const char *delim);

void checkPath(shell_vars_t *vars);
int executePath(char *command, shell_vars_t *vars);
char *findPath(char **env);
int executeCwd(shell_vars_t *vars);
int checkForDirectory(char *str);

void display_error(shell_vars_t *vars, char *message);
void custom_puts2(char *str);
char *custom_uitoa(unsigned int count);

void add_environment_key(shell_vars_t *vars);
char **find_environment_key(char **env, char *key);
char *add_environment_value(char *key, char *value);
int convert_string_to_int(char *str);

#endif /* _SHELL_H_ */
