#include "shell.h"

/**
 * _env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero on success
 */
int my_env(my_shell_info *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_cpy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_cpy = _strdup(env_get_key(cpname, data));
				if (var_cpy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpname, var_cpy, data);
					free(var_cpy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command);
		errno = 127;
	}
	return (0);
}

/**
 * set_env - sets environment variables
 * @data: struct for the program's data
 * Return: zero on sucess
 */
int my_set_env(my_shell_info *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command);
		return (5);
	}
	env_set_key(data->tokens[1], data->tokens[2], data);
	return (0);
}

/**
 * unset_env - unsets environment variables
 * @data: struct for the program's data'
 * Return: 0 on success
 */
int my_unset_env(my_shell_info *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
