#include "shell.h"

/**
 * handle_ctrl_c - Handle SIGINT (Ctrl+C) signal by printing a new line.
 * @opr UNUSED: Unused parameter (required by signal handler).
 */
void handle_ctrl_c(int opr)
{
	(void)opr; /* Cast opr to void to indicate it's intentionally unused */
	putchar('\n');
	fputs(PROMPT_MSG, stdout);
	fflush(stdout);
}

/**
 * initialize_data - Initialize the program's data structure.
 * @data: Pointer to the program's data structure.
 * @argv: Array of arguments passed to the program execution.
 * @env: Environment variables passed to the program execution.
 * @argc: The number of values received from the command line.
 */
void initialize_data(my_shell_info *data, int argc, char *argv[], char **env)
{
	int i;
	data->program = argv[0];
	data->input_line = NULL;
	data->command = NULL;
	data->exec_counter = 0;
	data->fd = (argc == 1) ? STDIN_FILENO : open(argv[1], O_RDONLY);

	if (data->fd == -1)
	{
		perror(data->program);
		exit(EXIT_FAILURE);
	}

	/* Allocate memory for env and alias_list */
	data->env = env;
	data->alias_list = malloc(sizeof(char *) * 20);

	if (data->alias_list == NULL)
	{
		perror(data->program);
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * sisifo - Start an infinite loop to display the shell prompt.
 * @prompt: The prompt to be printed.
 * @data: Pointer to the program's data structure.
 */
void sisifo(char *prompt, my_shell_info *data)
{
	int error_code;

	while (++data->exec_counter)
	{
		fputs(prompt, stdout);
		fflush(stdout);

		error_code = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}

		if (error_code >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
				{
					_print_error(error_code, data);
				}
			}
			free_recurrent_data(data);
		}
	}
}

/**
 * main - Initialize the program's variables and enter the shell loop.
 * @argc: The number of values received from the command line.
 * @argv: The values received from the command line.
 * @env: The environment variables.
 * Return: Always 0.
 */
int main(int argc, char *argv[], char *env[])
{
	my_shell_info data_struct = {0}, *data = &data_struct;

	char *prompt = "";

	initialize_data(data, argc, argv, env);
	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);

	return (0);
}

