#include "main.h"

/**
  * _memcpy- Copies n bytes from memory area.
  * @dest: Pointer to memory destination area.
  * @src: Pointer to memory src area.
  * @n: Number of bytes to copy from src memory area.
  * Return: Pointer to memory area dest.
  */

void *_memcpy(void *dest, void *src, unsigned int n)
{
	size_t i;
	char *dst = dest, *sc = src;

	for (i = 0; i < n; i++)
		dst[i] = sc[i];
	return (dest);
}

/**
  * free_ptr - Frees a given ptr and returns a given ptr
  * @ptr: pointer to free
  * @ptrReturn: Pointer to return.
  * Return: NULL pointer or passed value
  */

void *free_ptr(void *ptr, void *ptrReturn)
{
	free(ptr);
	return (ptrReturn);
}

/**
  * _realloc - Function reallocates memory block with malloc
  * @ptr: Pointer to the meomry block.
  * @old_size: Old size of memory block.
  * @new_size: New Size of memory block
  * Return: Pointer to (re)allocated memory
  */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *newPtr = 0;

	if (new_size == old_size)
		return (ptr);
	else if (ptr && new_size == 0)
		return (free_ptr(ptr, NULL));
	else if (!ptr)
	{
		newPtr = malloc(new_size);
		if (!newPtr)
			return (NULL);
		_memset(newPtr, 0, new_size);
		return (newPtr);
	}
	else if (new_size > old_size)
	{
		newPtr = malloc(new_size);
		if (!newPtr)
			return (NULL);
		_memset(newPtr, 0, new_size);
		newPtr = _memcpy(newPtr, ptr, old_size);
		return (free_ptr(ptr, newPtr));
	}
	return (ptr);
}
