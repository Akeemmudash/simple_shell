#include "main.h"

/**
  * tokens_to_arr - This function creates an array of strings from tokens
  * @lineptr_copy: This holds a copy of string to be tokenized
  * @num_tokens: The number of tokens present in the string.
  * @delim: The delimiter to be used.
  * Return: Pointer to Pointer of strings or NULL.
  */
char **tokens_to_arr(char *lineptr_copy, int num_tokens, const char *delim)
{
	char **args = NULL, *token = NULL;
	int i = 0;

	args = _realloc(NULL, 0, sizeof(char *) * (num_tokens + 1));
	if (!args)
	{
		_free_func(&lineptr_copy, 0);
		perror("line_to_args");
		return (NULL);
	}

	token = _strtok(lineptr_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		args[i] = _realloc(NULL, 0, sizeof(char) * (_strlen(token) + 1));
		if (!args[i])
		{
			_free_func(&lineptr_copy, 0);
			_free_func(args, i);
			perror("line_to_args");
			return (NULL);
		}

		_strcpy(args[i], token);
		token = _strtok(NULL, delim);
	}
	args[num_tokens] = NULL;
	return (args);
}

/**
  * line_to_args - This function returns the args in the string passed.
  * @lineptr: This holds the string(line) to be split to args
  * @delim: The delimiter to be used.
  * Return: Pointer to Pointer of strings or NULL.
  */
char **line_to_args(char *lineptr, const char *delim)
{
	char *lineptr_copy = NULL, *token = NULL, **args = NULL;
	int num_tokens = 0;

	lineptr_copy = _strdup(lineptr);
	if (!lineptr_copy)
	{
		perror("line_to_args");
		return (NULL);
	}
	token = _strtok(lineptr, delim);
	if (!token)
	{
		_free_func(&lineptr_copy, 0);
		return (NULL);
	}

	while (token)
	{
		num_tokens++;
		token = _strtok(NULL, delim);
	}

	args = tokens_to_arr(lineptr_copy, num_tokens, delim);
	_free_func(&lineptr_copy, 0);
	return (args);
}


/**
  * emul_tty - This function loopss for the shell
  * @lineptr: This holds the string(line) to be split to args
  * @argv: Pointer to pointer of strings
  * @envs: A NULL-terminated arr of str containing the current environment
  */

void emul_tty(char **lineptr, char **argv, char **envs)
{
	ssize_t nchars = 0;
	char **args = NULL, *prompt = "($) ", delim[] = " \n\t";
	size_t n = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, prompt, _strlen(prompt));
		errno = 0;
		nchars = _getline(lineptr, &n, STDIN_FILENO);

		if (nchars == -1)
		{
			if (errno)
				perror("main");
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}
		cmd_counter(1);
		args = line_to_args(*lineptr, delim);
		if (!args)
			continue;
		if (check_builtin(args, envs, argv, lineptr))
			_free_func(args, -1);
		else
		{
			execmd(argv, args);
			_free_func(args, -1);
		}
	}
}

/**
 * catch_sigint - Handles signal SIGINT (ctrl + c) sent to the program
 * @opt: Unused parameter
 */
void catch_sigint(__attribute__((unused))int opt)
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "($) ", 4);
}

/**
  * main - This program mimics the UNIX shell.
  * @argc: Number of arguments passed in
  * @argv: A NULL-teminated array of strings passed to CLI.
  * @envs: A NULL-terminated arr of str containint the current environment
  * Return: Exit status code.
  */
int main(int __attribute__((unused))argc, char *argv[], char **envs)
{
	char *lineptr = NULL;
	Node *head = create_env_list(envs);

	signal(SIGINT, catch_sigint);
	while (1)
	{
		emul_tty(&lineptr, argv, envs);
		break;
	}
	_free_func(&lineptr, 0);
	delete_linked_list(head);
	return (0);
}
