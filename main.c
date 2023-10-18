#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
        my_shell_info data_struct = {NULL}, *data = &data_struct;
        char *prompt = "";

        inicialize_data(data, argc, argv, env);

        signal(SIGINT, handle_ctrl_c);

        if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
        {/* We are in the terminal, interactive mode */
                errno = 2;/*???????*/
                prompt = PROMPT_MSG;
        }
        errno = 0;
        sisifo(prompt, data);
        return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
        _print("\n");
        _print(PROMPT_MSG);
}

/**
 * sisifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void sisifo(char *prompt, my_shell_info *data)
{
        int error_code = 0, string_len = 0;

        while (++(data->exec_counter))
        {
                _print(prompt);
                error_code = string_len = _getline(data);

                if (error_code == EOF)
                {
                        free_all_data(data);
                        exit(errno); /* if EOF is the fisrt Char of string, exit*/
                }
                if (string_len >= 1)
                {
                        expand_alias(data);
                        expand_variables(data);
                        str_tokenizer(data);
                        if (data->tokens[0])
                        { /* if a text is given to prompt, execute */
                                error_code = execute(data);
                                if (error_code != 0)
                                        _print_error(error_code, data);
                        }
                        free_recurrent_data(data);
                }
        }
}
