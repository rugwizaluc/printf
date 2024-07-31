#include "main.h"

/**
 * _printf - the function produces output according to a format
 * @format: format specifier
 * Return: The number of characters printed
 */

int _printf(const char *format, ...)
{
	unsigned int i;
	int num_char = 0;

	va_list str_args;

	va_start(str_args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i + 1] == 'c')
		{
			_putchar(va_arg(str_args, int));
		}
		else if (format[i] != '%')
		{
			_putchar(format[i]);
		}
		num_char++;
	}
	return (num_char);
}