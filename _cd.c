#include "main.h"

/**
  * get_env_value - Retrieves the value of an environment variable
  * from a linked list.
  * @name: Name of the environment variable.
  * @envs: Array of environment variables.
  * Return: String containing the value of the variable.
  */

char *get_env_value(char *name, char **envs)
{
	Node *curr = create_env_list(envs);

	while (curr)
	{
		if (_strcmp(curr->name, name) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
/**
  *change_d - change to current directory.
  * @path: FUll path to move to
  * @envs: Environment variable
  * @as: Arguments
  * @av: A NULL-terminated arr of str passed into the CLI
  * @cDir: Directory before move
  * @d: 1 if argument passed was a dash
  *
  */

void change_d(char *path, char **envs, char *cDir, int d, char **av, char **as)
{
	char *args_cust[4] = {NULL};
	int cdStatus = 0;

	cdStatus = chdir(path);
	if (path && cdStatus == 0)
	{
		args_cust[0] = "setenv";
		args_cust[1] = "OLDPWD";
		args_cust[2] = cDir;
		set_env_var(args_cust, envs);

		args_cust[1] = "PWD";
		args_cust[2] = path;
		set_env_var(args_cust, envs);
		if (d)
		{
			write(STDOUT_FILENO, path, _strlen(path));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		custom_err(as[0], av, as, 2);
}


/**
  * _cd - Change current process directory
  * @args: Arguments
  * @envs: Environment variables
  * @argv: Arguments passed into UNIX shell
  * Return: Non-zero value
  */


int _cd(char **args, char **envs, char **argv)
{
	int dash = 0, do_not_free = 0;
	char *path = NULL;
	char *curDir = NULL, buf[PATH_MAX + 1] = {0};

	curDir = getcwd(buf, PATH_MAX + 1);

	if (!curDir)
	{
		perror("cd: ");
		return (-1);
	}
		if (!args[1])
			path = _strdup(get_env_value("HOME", envs));
		else if (_strcmp(args[1],  "-") == 0)
		{
			path = get_env_value("OLDPWD", envs);
			path = path ? _strdup(path) : _strdup(get_env_value("PWD", envs));
			dash = 1;
		}
		else
		{
			path = args[1];
			do_not_free = 1;
		}
		change_d(path, envs, curDir, dash, argv, args);
		if (!do_not_free)
			_free_func(&path, 0);
		return (1);
}
