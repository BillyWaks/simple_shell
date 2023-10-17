#include "shell.h"

/**
 * _getline - reads input string from user
 * @data: struct for the program's data
 *
 * Return: number of bytes read
 */
int _getline(my_shell_info *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands[10] = {NULL};
	static char operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!commands[0] || (operators[0] == '&' && errno != 0) ||
			(operators[0] == '|' && errno == 0))
	{
		for (i = 0; commands[i]; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}
		bytes_read = read(data->fd, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);
		i = 0;
		do {
			commands[i] = str_duplicate(strtok(i ? NULL : buff, "\n;"));
			i = logic_check(commands, i, operators);
		} while (commands[i++]);
	}
	data->input_line = commands[0];
	for (i = 0; commands[i]; i++)
	{
		commands[i] = commands[i + 1];
		operators[i] = operators[i + 1];
	}
	return (str_length(data->input_line));
}

/**
 * logic_check - checks and split for && and || operators
 * @commands: array of the commands.
 * @i: index in the commands to be checked
 * @operators: array of the logical operators for each previous command
 *
 * Return: index of the last command in the commands.
 */
int logic_check(char *commands[], int i, char operators[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; commands[i] != NULL  && commands[i][j]; j++)
	{
		if (commands[i][j] == '&' && commands[i][j + 1] == '&')
		{
			tmp = commands[i];
			commands[i][j] = '\0';
			commands[i] = str_duplicate(commands[i]);
			commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			operators[i] = '&';
			free(tmp);
			j = 0;
		}
		if (commands[i][j] == '|' && commands[i][j + 1] == '|')
		{
			tmp = commands[i];
			commands[i][j] = '\0';
			commands[i] = str_duplicate(commands[i]);
			commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			operators[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}
