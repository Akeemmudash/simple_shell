#include "main.h"

/**
 * _free_node - frees a node
 * @ptr: Pointer to node
 */
void _free_node(Node *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

/**
 * delete_linked_list - deletes a linked list
 * @head: Head pointer.
 */
void delete_linked_list(Node *head)
{
	Node *tmp, *next;

	if (head)
	{
		tmp = head;
		while (tmp->next)
		{
			next = tmp->next;
			_free_node(tmp);
			tmp = next;
		}
		_free_node(tmp);
	}
}


/**
 * unset_env_var - removes an environment variable
 * @args: Array of arguments.
 * @envs: Array of environment variables.
 *
 * Return: an integer
 */
int unset_env_var(char **args, char **envs)
{
	Node *head = create_env_list(envs), *next, *curr;
	int i;

	curr = head;
	for (i = 0; args[i]; i++)
		i++;
	if (i > 2)
	{
		perror("Too many Arguments");
		return (-1);
	}
	while (curr->next)
	{
		next = curr->next;
		if (_strcmp(next->name, args[1]) == 0)
		{
			curr->next = NULL;
			curr->next = next->next;
			_free_node(next);
			break;
		}
		curr = curr->next;
	}
	if (!curr->next)
	{
		perror("Env not found");
		return (-1);
	}
	return (1);
}

