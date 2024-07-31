#include "main.h"
#include <stdlib.h>
/**
 * format_p - function that print a pointer address
 * @args: argument list
 * @buffer: values stored
 * @index: tracks the index position
 */
void format_p(va_list args, char *buffer, int index)
{
	format_lx(args, buffer, index);
}
/**
 * format_lx - function that prints a long address
 * @args: argument list
 * @buffer: values stored
 * @index: tracks the index position
 */
void format_lx(va_list args, char *buffer, int index)
{
	unsigned long int n;
	int i;
	char *hexvalues;
	char *hex;
	void *a;
	char *b;

	a = va_arg(valist, void *);
	b = "(nil)";
	if (a == NULL)
		for (i = 0; i < 5; i++, index++)
			buffer[index] = b[i];
	n = (unsigned long int)a;
	hexvalues = "0123456789abcdef";
	hex = malloc(14 * sizeof(char));

	for (i = 0; n != 0; i++)
	{
		hex[i] = hexvalues[n % 16];
		n /= 16;
	}
	i += 2;
	hex[13] = '0';
	hex[12] = 'x';
	for (i--; i >= 0; index++, i--)
	{
		buffer[index] = hex[i];
	}
}
