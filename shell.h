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

#define PROMPT_MSG "$ "
#define BUFFER_SIZE 1024

/****STRUCTURES****/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_des: file descriptor to the input of commands
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
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/** main.c **/
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
int _printe(char *string);
char *str_duplicate(char *string);
int str_length(char *string);

#endif
