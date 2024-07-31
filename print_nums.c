#include "main.h"

/**
 * print_int - the function prints an integer
 * @args: argument to be printed
 * Return: the number of characters to be printed
 */

int print_int(va_list args)
{
	int num_args, last_num, digit, expo, i;

	int num = va_args(args, int);

	last_num = num % 10;
	expo = 1;
	i = 1;
	num = num / 10;
	num_args = num;

	if (last_num < 10)
	{
		_putchar('-');
		num_args = -num_args;
		num = -num;
		last_num = -last_num;
	}
	if (num_args > 0)
	{
		while (num_args != 0)
		{
			expo = expo * 10;
			num_args = num_args / 10;
		}
		num_args = num;
		while (expo >= 1)
		{
			digit = num_args / expo;
			_putchar(digit + '0');
			num_args = num_args - (digit * expo);
			expo = expo / 10;
			i++;
		}
	}
	_putchar(last_num + '0');
	return (i);
}

#include "main.h"

/**
 * print_double - the function prints a double
 * @args: argument to be printed
 * Return: the number of characters to be printed
 */

int print_double(va_list args)
{
	int num_args, last_num, digit, expo, i;
	int num = va_args(args, int);

	last_num = num % 10;
	expo = 1;
	i = 1;
	num = num / 10;
	num_args = num;

	if (last_num < 10)
	{
		_putchar('-');
		num_args = -num_args;
		num = -num;
		last_num = -last_num;
	}
	if (num_args > 0)
	{
		while (num_args != 0)
		{
			expo = expo * 10;
			num_args = num_args / 10;
		}
		num_args = num;
		while (expo >= 1)
		{
			digit = num_args / expo;
			_putchar(digit + '0');
			num_args = num_args - (digit * expo);
			expo = expo / 10;
			i++;
		}
	}
	_putchar(last_num + '0');
	return (i);
}
