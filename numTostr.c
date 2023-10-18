#include "main.h"
#include <limits.h>
/**
 * count_digit - Count the number of digits in the specified base
 * @num: The number to be evaluated
 * @base: The desired numerical base
 *
 * Return: Number of digits.
 */
int count_digit(long num, long base)
{
	num = num >= 0 ? num : -(num);
	return (num < base ? 1 : 1 + count_digit(num / base, base));
}

/**
 * numToStr - Convert number to a string
 * @num: Number
 *
 * Return: String of number
 */
char *numToStr(long num)
{
	int lenStr = num < 0 ? 1 : 0;
	char *str;

	lenStr += (count_digit(num, 10));

	str = _realloc(NULL, 0, (sizeof(*str) * (lenStr + 1)));
	if (!str)
		return (NULL);

	str[lenStr--] = '\0';
	str[0] = num >= 0 ? '0' : '-';
	num = num >= 0 ? num : -(num);

	while (num)
	{
		str[lenStr--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
