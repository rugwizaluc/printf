#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * format_b - function to convert unsigned integer to binary
 * @args: arguments to the function
 * @buffer: values storage
 * @index: tracks the index position
 */
void format_b(va_list args, char *buffer, int index)
{
	unsigned int n;
	int i;
	char *binaryDigits;
	char *binary;

	n = va_arg(args, unsigned int);
	binaryDigits = "01";
	binary = malloc(33 * sizeof(char));
	if (binary == NULL)
		return;
	if (n == 0)
	{
		buffer[index] = '0';
		index++;
	}
	else
	{
		for (i = 0; n != 0; i++)
		{
			binary[i] = binaryDigits[n % 2];
			n /= 2;
		}
                int binary_index;
		binary_index = i - 1;
		while (binary_index >= 0)
		  {
			buffer[index] = binary[binary_index];
			index++;
			binary_index--;
		  }
	}
	free(binary);
}
