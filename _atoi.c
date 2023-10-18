#include "main.h"

/**
  * _atoi - Converts provided string to an integer.
  * @s: The string to be converted.
  * Return: The converted integer
  */

int _atoi(char *s)
{
	int num_found = 0, sign = 1, value = 0, i = 0;

	while (s && s[i])
	{
		if (num_found)
		{
			if (!(s[i] >= 48 && s[i] <= 57))
				return (-1);
			value *= 10;
			value = value < 0 ? value - (s[i] - '0') : value + (s[i] - '0');
			i++;
		}
		else
		{
			if (s[i] >= 48 && s[i] <= 57)
			{
				num_found = 1;
				value = (s[i] - '0') * sign;
			}
			else if (i == 0 && ((s[i] == '+') || (s[i] == '-')))
				sign = s[i] == '-' ? -1 : 1;
			else
				return (-1);
			i++;
		}
	}
	return (value >= 0 ? value : -1);
}
