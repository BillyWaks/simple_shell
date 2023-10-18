#include "shell.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converted into a string.
 * @string: buffer to save the number in string format
 * @base: the base of the number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, if_neg = 0;
	long num = number;
	char letters[] = {"0123456789abcdef"};

	if (num == 0)
		string[index++] = '0';

	if (string[0] == '-')
		if_neg = 1;

	while (num)
	{
		if (num < 0)
			string[index++] = letters[-(num % base)];
		else
			string[index++] = letters[num % base];
		num /= base;
	}
	if (if_neg)
		string[index++] = '-';

	string[index] = '\0';
	_strrev(string);
}


/**
 * _atoi - converts a string to an integer.
 *
 * @s: pointer to str input.
 * Return: integer value for the string
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
