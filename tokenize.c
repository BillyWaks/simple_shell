#include "shell.h"
/**
 * str_tokenizer - separates input based on a delimiter
 * @data: a pointer to the program's data
 * Return: an array containing tokens from user input
 */
void str_tokenizer(my_shell_info *data)
{
	char *delim = " \t";
	int i, j, counter = 2, length;

	length = _strlen(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}
	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (data->input_line[i] == delim[j])
				counter++;
		}
	}
	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delim));
	data->command = str_duplicate(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(_strtok(NULL, delim));
	}
}
