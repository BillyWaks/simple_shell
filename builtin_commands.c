#include "shell.h"

/**
 * _exit - exit the program with error code
 * @data: struct for the program's data
 * Return: zero on sucess
 */
int my_exit(my_shell_info *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
					&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * _cd - changes current directory
 * @data: struct for the program's data
 * Return: zero on sucess
 */
int _cd(my_shell_info *data)
{
	char *home_dir = env_get_key("HOME", data), *prev_dr = NULL;
	char dir_prev[128] = {0};
	int err_cd = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			prev_dr = env_get_key("OLDPWD", data);
			if (prev_dr)
				err_cd = set_wd(data, prev_dr);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (err_cd);
		}
		else
		{
			return (set_wd(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(dir_prev, 128);

		return (set_wd(data, home_dir));
	}
	return (0);
}

/**
 * set_wd - sets work directory
 * @data: struct for the program's data
 * @curr_dir: path to be set as working directory
 * Return: zero on sucess
 */
int set_wd(my_shell_info *data, char *curr_dir)
{
	char dir_prev[128] = {0};
	int err_code = 0;

	getcwd(dir_prev, 128);

	if (!str_compare(dir_prev, curr_dir, 0))
	{
		err_code = chdir(curr_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", curr_dir, data);
	}
	env_set_key("OLDPWD", dir_prev, data);
	return (0);
}

/**
 * _help - shows env running the shell
 * @data: struct for the program's data
 * Return: zero on success
 */
int _help(my_shell_info *data)
{
	int i, len = 0;
	char *msg[6] = {NULL};

	msg[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(msg[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command);
		return (5);
	}
	msg[1] = HELP_EXIT_MSG;
	msg[2] = HELP_ENV_MSG;
	msg[3] = HELP_SETENV_MSG;
	msg[4] = HELP_UNSETENV_MSG;
	msg[5] = HELP_CD_MSG;

	for (i = 0; msg[i]; i++)
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], msg[i], len))
		{
			_print(msg[i] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command);
	return (0);
}

/**
 * _alias - manipulates aliases
 * @data: struct for the program's data
 * Return: zero on sucess
 */
int _alias(my_shell_info *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}
	return (0);
}
