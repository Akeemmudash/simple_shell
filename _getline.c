#include "main.h"
#define LINE_BUF 1024


/**
 * isDel - Checks whether a character is a valid delimiter.
 * @delims: String containing a set of valid delimiters.
 * @c: Character to be checked.
 * Return: 1 if the character is a valid delimiter, 0 otherwise.
 */
short int isDel(const char *delims, char c)
{
	while (*delims)
	{
		if (c == *delims)
			return (1);
		delims++;
	}
	return (0);
}

/**
 * _strtok - Splits a string into tokens using specified delimiters.
 * @delim: String containing delimiters used to tokenize the string.
 * @str:String to be tokenized.
 * Return: Pointer to next token in string or NULL if there are no more.
 */
char *_strtok(char *str, const char *delim)
{
	static char *curr_ptr;
	char *tmp = NULL;
	int i = 0;

	if (!delim)
		return (NULL);

	if (str && *str)
		curr_ptr = str;

	while (curr_ptr && curr_ptr[i])
	{
		if (!isDel(delim, curr_ptr[i]))
		{
			tmp = curr_ptr[i] ? &curr_ptr[i] : curr_ptr;

			while (curr_ptr[++i])
			{
				if (isDel(delim, curr_ptr[i]))
				{
					curr_ptr[i] = 0;
					curr_ptr = curr_ptr[i + 1] ? &curr_ptr[i + 1] : NULL;
					return (tmp);
				}
			}
			curr_ptr = NULL;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}


/**
 * read_to_buf - Copies the entire content from a file descriptor
 * to a dynamically allocated buffer.
 * @fd: File descriptor to be read from.
 * @lineptr: Pointer to the buffer to store the text.
 * @n: Size of the buffer pointed to by lineptr.
 * Return: A buffer containing the entire text from the file descriptor,
 * or NULL if the operation fails.
 */

char *read_to_buf(int fd, char **lineptr, size_t *n)
{
	char buf[LINE_BUF + 1] = {0};
	char *ptr = *lineptr;
	ssize_t count = 0;
	size_t tot = 0;
	unsigned int prev_size = *n;

	do {
		count = read(fd, buf, LINE_BUF);
		if (count == -1)
			return (NULL);
		if (count == 0)
			return (NULL);
		while (fd == STDIN_FILENO && !_strchr(buf, '\n') && isatty(fd))
		{
			if (_strlen(buf) == 0)
				return (NULL);
			count += read(fd, (buf + count), (LINE_BUF - count));
			if (count == LINE_BUF)
				break;
		}
		if (count + tot > *n)
		{
			ptr = _realloc(ptr, prev_size, (sizeof(*ptr) * (*n + count + 1)));
			if (!ptr)
				return (NULL);
			prev_size = (sizeof(*ptr) * (*n + count + 1));
		}
		_memcpy((ptr + tot), buf, count);
		tot += count;
		ptr[tot] = '\0';
		*n += count;

	} while (count == LINE_BUF);
	*lineptr = ptr;
	return (ptr);
}


/**
 * _getline - Reads a line from a file descriptor using the read function.
 * @fd: File descriptor to be read from.
 * @lineptr: Pointer to the buffer used to store the text.
 * @n: Size of the buffer pointed to by lineptr.
 * Return: The size of the line read excluding the
 * newline character, or -1 if the operation fails.
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char **line_stat_ptr, *tot_stream;
	static size_t f_cnt;
	char *lines = NULL;

	if (!lineptr || !n)
	{
		errno = EINVAL;
		return (-1);
	}
	if (!line_stat_ptr)
		line_stat_ptr = lineptr;
	if (f_cnt == 0 || fd == STDIN_FILENO)
	{
		tot_stream = read_to_buf(fd, lineptr, n);
		if (!tot_stream)
			return (-1);
		*lineptr = tot_stream;
	}
	lines = !f_cnt++ || fd == 0 ? _strtok(*lineptr, "\n") : _strtok(NULL, "\n");
	if (_strcmp(*lineptr, "\n") == 0)
		lines = *lineptr;
	if (!lines)
	{
		*lineptr = tot_stream;
		f_cnt = 0;
		return (-1);
	}
	*lineptr = lines;
	return (_strlen(*lineptr));
}
