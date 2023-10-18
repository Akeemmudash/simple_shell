#include "main.h"
/**
 * _free_func - This frees up malloc'd space
 * @ptr: Pointer/Array of ptrs to be freed
 * @length: Size of arr to be freed or -1 if NULL terminated
 */


void _free_func(char **ptr, int length)
{
	int i = 0;

	if (length == 0)
		free(*ptr);
	else if (length > 0)
	{
		while (ptr && *ptr && i < length)
			free(ptr[i++]);
		free(ptr);
	}
	else if (ptr && length == -1)
	{
		while (ptr && *ptr && ptr[i])
		{
			free(ptr[i++]);
			if (ptr[i] == NULL)
				free(ptr[i]);
		}
		free(ptr);
	}
}
