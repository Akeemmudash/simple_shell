#include "main.h"

/**
  * split_str - Splits a string using a specified delimiter
  * and appends a slash at the end of each segment.
  * @str: String to be split.
  * @delim: Delimiter to be used.
  * Return: Pointer to an array of NULL-terminated strings.
  */

char **split_str(char *str, char *delim)
{
	char *str_copy, **pp, *token;
	int i, num_tokens = 0;

	str_copy = _strdup(str);
	if (!str_copy)
		return (NULL);
	token = _strtok(str_copy, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = _strtok(NULL, delim);
	}
	pp = _realloc(NULL, 0, sizeof(char *) * (num_tokens + 1));
	if (!pp)
	{
		_free_func(&str_copy, 0);
		perror("split_str function");
		return (NULL);
	}
	_strcpy(str_copy, str);
	token = _strtok(str_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		pp[i] = _realloc(NULL, 0, sizeof(char) * _strlen(token) + 2);
		if (!pp[i])
		{
			_free_func(pp, i);
			_free_func(&str_copy, 0);
			perror("split_str function");
			return (NULL);
		}
		_strcpy(pp[i], token);
		_strcat(pp[i], "/");
		token = _strtok(NULL, delim);
	}
	pp[i] = NULL;
	_free_func(&str_copy, 0);
	return (pp);
}
