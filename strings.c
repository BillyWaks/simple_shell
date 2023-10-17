#include "shell.h"

/**
 * _strlen - returns the string length
 * @str: string input
 * Return: length of the string.
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * _strdup - duplicates a string input
 * @str: String to be duplicated
 * Return: pointer to duplicate of str
 */
char *_strdup(char *str)
{
	char *dup;
	int len, i;

	if (str == NULL)
		return (NULL);

	len = _strlen(str) + 1;

	dup = malloc(sizeof(char) * len);

	if (dup == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		dup[i] = str[i];
	}

	return (dup);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * @num: bytes to be compared
 * Return: 1 if the strings are equal similar
 */
int _strcmp(char *str1, char *str2, int num)
{
	int i;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (num == 0)
	{
		if (_strlen(str1) != _strlen(str2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < num ; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * _strcnt - concatenates two strings.
 * @str1: first string
 * @str2: second string
 *
 * Return: pointer to the concatenation of str1 and str2
 */
char *_strcnt(char *str1, char *str2)
{
	char *conc;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = _strlen(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = _strlen(str2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (conc == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; str1[len1] != '\0'; len1++)
		conc[len1] = str1[len1];
	free(str1);
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		conc[len1] = str2[len2];
		len1++;
	}
	conc[len1] = '\0';
	return (conc);
}

/**
 * _strrev - reverses a string.
 *
 * @str: pointer to string.
 * Return: nothing
 */
void _strrev(char *str)
{
	int i = 0, len = _strlen(str) - 1;
	char tmp;

	while (i < len)
	{
		tmp = str[i];
		str[i++] = str[len];
		str[len--] = tmp;
	}
}
