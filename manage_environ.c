#include "shell.h"

/**
 * get_key - gets value of an environment variable
 * @key: the environment variable
 * @data: struct of the program's data
 * Return: a pointer to the variable
 */
char *get_key(char *key, my_shell_info *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
				data->env[i][key_len] == '=')
		{
			return (data->env[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * set_key - overwrites the value of the environment variable
 * creates it if it does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int set_key(char *key, char *value, my_shell_info *data)
{
	int i, key_len = 0, new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
				data->env[i][key_len] == '=')
		{
			new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = _strcnt(_strdup(key), "=");
	data->env[i] = _strcnt(data->env[i], value);

	if (new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remkey - removes a key from the environment
 * @key: key to remove
 * @data: sructure of the program's data
 * Return: 1 o success, 0 on failure
 */
int env_remkey(char *key, my_shell_info *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_len = _strlen(key);

	for (i = 0; data->env[i]; i++)
	{
		if (_strcmp(key, data->env[i], key_len) &&
				data->env[i][key_len] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_env - prints the current environment variables
 * @data: struct for the program's data
 * Return: nothing
 */
void print_env(my_shell_info *data)
{
	int x;

	for (x = 0; data->env[x]; x++)
	{
		_print(data->env[x]);
		_print("\n");
	}
}
