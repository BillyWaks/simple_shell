#include "shell.h"
/**
 * _strtok - splits string based on specified delimiter
 * @input: pointer to input string
 * @delim: characters to use as delimiters for input
 * Return: pointer to created token
 */
char *_strtok(char *input, char *delim)
{
	int j;
	static char *str;
	char *copy;

	if (input != NULL)
		str = input;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
	}
	copy = str;
	if (*copy == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copy);
			}
		}
	}
	return (copy);
}
