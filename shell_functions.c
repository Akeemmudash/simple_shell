#include "main.h"


/**
  *_getenv - This function returns the val of a specified env var
  *@env_name: The name of the environment variable
  *Return: The value if successful else NULL
  */

char *_getenv(char *env_name)
{
	int i = 0;
	char *value = NULL;

	while (environ[i])
	{
		if (_strncmp(environ[i], env_name, _strlen(env_name)) == 0)
		{
			value = environ[i] + _strlen(env_name) + 1;
			break;
		}
		i++;
	}
	return (value);
}


/**
  *get_PATH - This function splits the val of the PATH in to tokens of an arr
  *Return: The Pointer to array if successful else NULL
  */
char **get_PATH(void)
{
	char *path = NULL;
	char **path_arr = NULL;

	path = _getenv("PATH");
	if (path)
		path_arr = split_str(path, ":");
	return (path_arr);
}

/**
  * create_process - This function creates a child process
  * @args: Pointer to arr of strings used as arg for execve
  * @env: A NULL-terminated arr of str containint the current environment.
  * @path: Full path to executable.
  * Return: Exit status code
  */

short int create_process(char *path, char **args, char **env)
{
	pid_t child_pid;
	int wStatus, retCode = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		retCode = -1;
	}

	else if (child_pid == 0)
	{
		/*Code will be executed by child */
		execve(path, args, env);
		/*Execve shouldn't return here. If it does, it must have failed*/
		perror(path);
		retCode = -1;
	}

	else
	{
		/*This code is run by parent process, Wait for child to terminate*/
		if (waitpid(child_pid, &wStatus, 0) == -1)
		{
			perror("waitpid");
			retCode = -1;
		}
	}
	return (retCode);
}


/**
  * concat_str - This vrdic fn concantenates variable num of strings
  * @n: This holds the string(line) to be split to args
  * Return: Null-byte terminated concatenated string
  */
char *concat_str(const unsigned int n, ...)
{
	va_list str_list;
	char *str = NULL, *new_str = NULL;
	unsigned int i = 0, tot_len = 0, prev_size = 0;

	va_start(str_list, n);
	while (i < n)
	{
		str = va_arg(str_list, char *);
		tot_len += _strlen(str);
		new_str = _realloc(new_str, prev_size, (sizeof(*new_str) * (tot_len + 1)));

		if (!new_str)
		{
			_free_func(&new_str, 0);
			perror("concat_str function");
			return (NULL);
		}
		prev_size = (sizeof(*new_str) * (tot_len + 1));
		if (i == 0)
			new_str = strcpy(new_str, str);
		else
			_strcat(new_str, str);

		i++;
	}
	va_end(str_list);
	return (new_str);
}


/**
  * execmd - This Fn handles the execution of a given command.
  * @args: Array of arguments passed into our shell
  * @argv: A NULL-terminated arr of str passed into the CLI
  */
void execmd(char **argv, char **args)
{
	char *command = NULL, **path_arr = NULL, *full_path = NULL;
	unsigned short process_code = 0;

	command = args[0];
	if (access(command, F_OK) == 0)
	{
		process_code = create_process(command, args, environ);
		return;
	}
	else if (_strchr(command, '/') != NULL)
	{
		custom_err(command, argv, args, 0);
		/*set exit code to 127*/
	}
	else
	{
		path_arr = get_PATH();
		full_path = path_arr ? _which(args, path_arr) : NULL;
		if (full_path)
		{
			process_code = create_process(full_path, args, environ);
			_free_func(&full_path, 0);
		}
		else
		{
			custom_err(command, argv, args, 0);
			/*set exit code to 127*/

		}
	}
	process_code = process_code;
}
