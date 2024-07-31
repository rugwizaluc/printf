#include "main.h"
/**
 * format_perc - percentage specifier
 * @args: arguments to va_list
 * @buffer: write to buffer
 * @index: index to traverse buffer
 * Return: void
 */
void format_perc(
__attribute__((unused))va_list args, char *buffer, int index)
{
	buffer[index] = '%';
	index++;
}
