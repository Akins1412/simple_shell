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
 * shell variables Structure - Holds shell-related variables
 * @av: Command line arguments
 * @buffer: Buffer containing the command
 * @env: Environment variables
 * @count: Count of entered commands
 * @argv: Arguments at the opening of the shell
 * @exit_status: Exit status of the shell
 * @commands: Double pointer to commands
 */
typedef struct shell variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int exit_status;
	char **commands;
} shell vars;


/**
 * builtin command Structure - Holds information for shell builtin commands
 * @name: Name of the builtin command
 * @function: Function pointer to the corresponding builtin function
 */
typedef struct builtin command
{
	char *name;
	void (*function)(shell vars *);
} builtin cmd;

char **initialize_env(char **env);
void release_env(char **env);

ssize_t print_string(char *str);
char *duplicate_string(char *str_to_duplicate);
int compare_strings(char *str1, char *str2);
char *concatenate_strings(char *str1, char *str2);
unsigned int get_string_length(char *str);

void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *vars);
void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);

void check_for_path(vars_t *vars);
int path_execute(char *command, vars_t *vars);
char *find_path(char **env);
int execute_cwd(vars_t *vars);
int check_for_dir(char *str);

void add_key(vars_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

void print_error(vars_t *vars, char *msg);
void _puts2(char *str);
char *_uitoa(unsigned int count);

#endif /* _SHELL_H_ */
