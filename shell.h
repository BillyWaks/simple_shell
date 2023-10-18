#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <unistd.h> /* for fork, execve*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <fcntl.h> /* for open files*/
#include <signal.h> /* for signal management */

#include "macros.h"

#define BUFFER_SIZE 1024

/****STRUCTURES****/

/**
 * struct info- struct for the program's data
 * @program: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @fd: file descriptor to the input of commands
 * @token: pointer to array of tokenized input
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program;
	char *prompt;
	char *input_line;
	char *command;
	int exec_counter;
	int fd;
	char *token;
	char **tokens;
	char **array;
	char **env;
	char **alias_list;
} my_shell_info;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(my_shell_info *data);
} builtins;

/*** MAIN FUNCTIONS ***/

/** _getline.c **/
int _getline(my_shell_info *data);
int logic_check(char *commands[], int i, char operators[]);

/** main.c **/
void inicialize_data(my_shell_info *data, int argc, char *argv[], char **env);
void handle_ctrl_c(int opr);
void initialize_data(my_shell_info *data, int argc, char *argv[], char **env);
void sisifo(char *prompt, my_shell_info *data);
int main(int argc, char *argv[], char *env[]);
void free_all_data(my_shell_info *data);
void free_recurrent_data(my_shell_info *data);
void free_array_of_pointers(char **directories);
int _print_error(int errorcode, my_shell_info *data);
void tokenize(my_shell_info *data);
int _print_error(int errorcode, my_shell_info *data);
void expand_variables(my_shell_info *data);
void expand_alias(my_shell_info *data);
int execute(my_shell_info *data);
int str_length(char *string); 
char *str_duplicate(char *string);

/** strings.c **/
int str_compare(char *string1, char *string2, int number);
int str_length(char *string);
char *str_duplicate(char *string);
void str_reverse(char *string);
char *str_concat(char *string1, char *string2);

/** alias.c **/
int set_alias(char *alias_string, my_shell_info *data);
char *get_alias(my_shell_info *data, char *alias);
int print_alias(my_shell_info *data, char *alias);

/** print.c **/
int _print(char *string);
int _printe(char *string); 
int _print_error(int errorcode, my_shell_info *data);

/** convert_numbers.c **/
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);

/** expand.c **/
void expand_variables(my_shell_info *data);
void expand_alias(my_shell_info *data);
int buffer_add(char *buffer, char *str_to_add);

/** manage_env.c **/
char *env_get_key(char *key, my_shell_info *data);
int env_set_key(char *key, char *value, my_shell_info *data);
int env_remove_key(char *key, my_shell_info *data);
void print_environ(my_shell_info *data);

/** tokenize.c **/
void str_tokenizer(my_shell_info *data);

/** strtok.c **/
char *_strtok(char *line, char *delim);

/** execute.c **/
int execute(my_shell_info *data);

/** builtins_list.c **/
int builtins_list(my_shell_info *data);

/** builtin_commands.c **/
int _cd(my_shell_info *data);
int set_wd(my_shell_info *data, char *curr_dir);
int _help(my_shell_info *data);
int _alias(my_shell_info *data);
int my_exit(my_shell_info *data);

/** builtins_env.c **/
int my_env(my_shell_info *data);
int my_set_env(my_shell_info *data);
int my_unset_env(my_shell_info *data);

/** path.c **/
int check_file(char *full_path);
int find_program(my_shell_info *data);
char **tokenize_path(my_shell_info *data);

#endif
