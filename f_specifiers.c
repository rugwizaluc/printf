#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * format_d - Format specifier for int
 * @args: arguments passed to the function
 * @buffer: values stored
 * @index: Traverses the index position
 */
void format_d(va_list args, char *buffer, int index)
{
	int i, j, len;
	char *str;

	i = va_arg(args, int);

	len = num_len(i);
	if (i < 0)
	{
		len++;
	}
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return;
	itos(str, i);
	for (i = index, j = 0; j < numlen; index++; i++; j++)
	{
		if (index == 1024)
		{
			_write_buffer(buffer, &index);
			reset_buffer(buffer);
			index = 0;
		}
		buffer[index] = str[j];
	}
	free(str);
}
/**
 * format_u - function to print unsigned integer in decimal base
 * @args: arguments passed to the function
 * @buffer: buffer to store the formatted string
 * @index: index to traverse the buffer
 *
 * Return: void
 */
void format_u(va_list args, char *buffer, int index)
{
	int i;
	int j, len;
	char *str;

	i = va_arg(args, int);
	len = num_len(i);
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return;
	utos(str, i);
	for (i = index, j = 0; j < numlen; index++; i++; j++)
	{
		if (index == 1024)
		{
			_write_buffer(buffer, &index);
			reset_buffer(buffer);
			index = 0;
		}
		buffer[index] = str[j];
	}
	free(str);
}
/**
 * format_h - Function converting unsigned int to hexadecimal
 * @args: arguments passed to the function
 * @buffer: buffer to store the formatted string
 * @index: index to traverse the buffer
 *
 * Return: void
 */
void format_h(va_list args, char *buffer, int index)
{
	unsigned int n;
	int i;
	char *hexvalues;
	char *hex;

	n = va_arg(args, unsigned int);
	hexvalues = "0123456789abcdef";
	hex = malloc(9 * sizeof(char));
	if (hex == NULL)
		return;
	for (i = 0; n != 0; i++)
	{
		hex[i] = hexvalues[n % 16];
		n /= 16;
	}
	for (i--; i >= 0; index++; i--)
	{
		buffer[index] = hex[i];
	}
	free(hex);
}
/**
 * format_ch - Function to print unsigned integer into hexadecimal 
 * @args:arguments passed to the function
 * @buffer:buffer to store the formatted string
 * @index:index to traverse the buffer
 *
 * Return: void
 */
void format_ch(va_list args, char *buffer, int index)
{
	unsigned int n;
	int i;
	char *hexvalues;
	char *hex;

	n = va_arg(args, unsigned int);
	hexvalues = "0123456789ABCDEF";
	hex = malloc(9 * sizeof(char));
	if (hex == NULL)
		return;
	for (i = 0; n != 0; i++)
	{
		hex[i] = hexvalues[n % 16];
		n /= 16;
	}
	for (i--; i >= 0; index++; i--)
	{
		buffer[index] = hex[i];
	}
	free(hex);
}
/**
 * format_o - function to print an integer as an octal base number
 * @args: arguments passed to the function
 * @buffer:buffer to store the formatted string
 * @index:index to traverse the buffer
 *
 * Return: void
 */
void format_o(va_list args, char *buffer, int index)
{
	unsigned int n;
	int i;
	char *octValues;
	char *oct;

	n = va_arg(args, unsigned int);
	octValues = "0123456789ABCDEF";

	oct = malloc(12 * sizeof(char));
	if (oct == NULL)
		return;
	for (i = 0; n != 0; i++)
	{
		oct[i] = octvalues[n % 8];
		n /= 8;
	}
	for (i--; i >= 0; index++ ; i--)
	{
		buffer[index] = oct[i];
	}
	free(oct);
}


