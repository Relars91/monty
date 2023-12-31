#include "monty.h"

/**
 * _strlen - string length
 * @s: string
 * Return: length of string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; *(s + i); ++i)
		;
	return (i);
}


/**
 * skip_spaces - skip whitespaces
 * @s: a string
 *
 * Return: pointer to where is the first non space char or NULL
 */
char *skip_spaces(char *s)
{
	if (!s)
		return (NULL);

	while (*s && (*s == ' ' || *s == '\t' || *s == '\v'))
		++s;
	if (*s == '\0' || *s == '\n' || *s == '#') /*empty string or comment*/
		return (NULL);
	return (s);
}

/*use strncmp with this return value, opcode and strlen(opcode)*/


/**
 * reach_number - get the first number in a string
 * @s:
 * the string should contain only spaces and a valid opcode before
 * Return: a pointer to where the number (and a number is not 4e) is or NULL
 */
char *reach_number(char *s)
{
	char *c;
	int res, i, neg = 1;

	res = i = 0;
	if (!s)
		return (NULL);

	while (*s && (*s < '0' || *s > '9'))
	{
		if (*s == '-')
			neg = -1;
		i++;
		++s;
	}

	if (*s == '\0')
		return (NULL);
	c = s;
	while (*c && *c >= '0' && *c <= '9')
		c++;

	if (!(*c == '\0' || *c == '\n' || *c == ' ' || *c == '\t'))
	return (NULL);

	res = atoi(s) * neg;
	if (res < 0)
	{
		s[i - 1] = '-';
		return (s - 1);
	}
	return (s);
}

/*use atoi with this return value*/


/**
 * _strcmp - compare 2 strings see strcmp()
 * @s1: string to compare
 * @s2: string used as reference
 * Return: It returns the difference in value of the first characters where
 * s1 and s2 disagree
*/
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) != '\0' && *(s2 + i) != '\0')
		i++;
	return (*(s1 + i) - *(s2 + i));
}



/**
 * _strncmp - compare 2 strings see strcmp()
 * @s1: string to compare
 * @s2: opcode
 * @n: length of opcode to compare
 * Return: It returns 0 if OK
*/
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	while (*(s1 + i) != '\0' && *(s2 + i) != '\0' && i < n)
	{
		if (*(s1 + i) == *(s2 + i))
		{
			++i;
		}
		else
		{
			return (*(s1 + i) - *(s2 + i));
		}
	}
	if (i == n && (*(s1 + i) == ' ' || *(s1 + i) == '\t' ||
		       *(s1 + i) == '\0' || *(s1 + i) == '\n'))
		return (0);
	return (EXIT_FAILURE); /* one of the strings was too short, not the best*/
}
