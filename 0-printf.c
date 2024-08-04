#include "main.h"
/**
 * @handle_char - Handles the 'c' specifier
 * @args: List of arguments
 *
 * @Return: Number of characters printed
 */
int handle_char(va_list args)
{
    char character = va_arg(args, int);
    return (write(1, &character, 1));
}

/**
 * @handle_string - Handles the 's' specifier
 * @args: List of arguments
 *
 * @Return: Number of characters printed
 */
int handle_string(va_list args)
{
    char *string = va_arg(args, char *);
    int length = 0;

    if (string == NULL)
        return (-1);
        while (string[length++])
    return (write(1, string, length));
}

/**
 * @handle_perc - Handles the '%' specifier
 * @args: List of arguments (unused)
 *
 * @Return: Number of characters printed
 */
int handle_perc(va_list args)
{
    /* Avoid unused parameter warning */
    args = args; 
    return (write(1, "%", 1));
}
/**
 * @handle_binary - Handles the 'b' specifier
 * @args: List of arguments
 *
 * @Return: Number of characters printed
 */
int handle_binary(va_list args)
{
unsigned int number = va_arg(args, unsigned int);
char tmp[32];
int index = 31;

if (number == 0)
{
    return (write(1, "0", 1));
}
tmp[31] = '\0'; /* Null-terminate the string */

while (number > 0)
{
    tmp[--index] = (number % 2) ? '1' : '0';
    number /= 2;
}

/*  write the binary representation to the output */
int bytes = 31 - i;
return write(1, &buffer[i], bytes);
}
/**
 * @_printf - Produces output according to a format
 * @format: Character string to be printed
 *
 * @Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int index;

    /* Array of specifier-function pairs */
    spec_t spec[] = {
        {'c', handle_char},
        {'s', handle_string},
        {'%', handle_percent},
	{'b', handle_binary},
        {'\0', NULL} /* End of array */
    };

    va_start(args, format);

    if (format == NULL)
        return (-1);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;

            /* Find and call the corresponding handler function */
            for (index = 0; spec[index].specifier != '\0'; index++)
            {
                if (*format == spec[index].specifier)
                {
                    spec[index].func(args);
                    break;
                }
            }

            /* If no handler found, print the format literally */
            if (spec[index] == '\0')
            {
                write(1, "%", 1);
                write(1, format, 1);
            }
        }
        else
        {
            write(1, format, 1);
        }
        format++;
    }

    va_end(args);
    return (0);
}

