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
#include "macros.h" /* for msg help and prompt */

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
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_des;
	char **tokens;
	char **env;
	char **alias_list;
} my_program_info;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(my_program_info *data);
} builtins;

#endif
