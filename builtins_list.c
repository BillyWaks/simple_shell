#include "shell.h"

/**
 * _builtins - search for match and execute the  builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int _builtins(my_shell_info *data)
{
	int i;
	builtins options[] = {
		{"exit", _exit},
		{"help", _help},
		{"cd", _cd},
		{"alias", _alias},
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (str_compare(options[i].builtin, data->command, 0))
			return (options[i].function(data));
	}
	return (-1);
}
