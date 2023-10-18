#include "shell.h"

/**
 * alias_print - shows adds and removes aliases
 * @data: pointer to program's data
 * @alias: alias to be printed
 * Return: zero on sucsess
 */
int alias_print(my_shell_info *data, char *alias)
{
	int i, j, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = _strlen(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (_strcmp(data->alias_list[i], alias, alias_len)
						&&	data->alias_list[i][alias_len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * alias_get - gets aliases
 * @name: name of the alias requested
 * @data: struct for the program's data
 * Return: zero on sucess
 */
char *alias_get(my_shell_info *data, char *name)
{
	int i, alias_len;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = _strlen(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (_strcmp(name, data->alias_list[i], alias_len) &&
				data->alias_list[i][alias_len] == '=')
		{
			return (data->alias_list[i] + alias_len + 1);
		}
	}
	return (NULL);
}

/**
 * set_alias - sets aliases
 * @alias_str: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_str, my_shell_info *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_str == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_str[i]; i++)
		if (alias_str[i] != '=')
			buffer[i] = alias_str[i];
		else
		{
			temp = alias_get(data, alias_str + i + 1);
			break;
		}
	for (j = 0; data->alias_list[j]; j++)
		if (_strcmp(buffer, data->alias_list[j], i) &&
				data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = _strdup(buffer);
	}
	else
		data->alias_list[j] = _strdup(alias_str);
	return (0);
}
