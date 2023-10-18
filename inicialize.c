/**
 * inicialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */

void inicialize_data(my_shell_info *data, int argc, char *argv[], char **env)
{
        int i = 0;

        data->program = argv[0];
        data->input_line = NULL;
        data->command = NULL;
        data->exec_counter = 0;
        /* define the file descriptor to be readed*/
        if (argc == 1)
                data->fd = STDIN_FILENO;
        else
        {
                data->fd = open(argv[1], O_RDONLY);
                if (data->fd == -1)
                {
                        _printe(data->program);
                        _printe(": 0: Can't open ");
                        _printe(argv[1]);
                        _printe("\n");
                        exit(127);
                }
        }
        data->tokens = NULL;
        data->env = malloc(sizeof(char *) * 50);
        if (env)
        {
                for (; env[i]; i++)
                {
                        data->env[i] = _strdup(env[i]);
                }
        }
        data->env[i] = NULL;
        env = data->env;

        data->alias_list = malloc(sizeof(char *) * 20);
        for (i = 0; i < 20; i++)
        {
                data->alias_list[i] = NULL;
        }
}
