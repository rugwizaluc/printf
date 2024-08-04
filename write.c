#include "main.h"
/**
 * @handle_char - Handles the 'c' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_char(va_list args, char *buffer, int *index)
{
    char character = va_arg(args, int);
    buffer[(*index)++] = character;
    return (1);
}

/**
 * @handle_string - Handles the 's' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_string(va_list args, char *buffer, int *index)
{
    char *string = va_arg(args, char *);
    int length = 0;

    if (string == NULL)
        string = "(null)";

    while (string[length])
    {
        buffer[(*index)++] = string[length++];
    }

    return (length);
}
/**
 * @handle_percent - Handles the '%' specifier
 * @args: List of arguments (unused)
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_percent(va_list args, char *buffer, int *index)
{
    (void)args; /* Avoid unused parameter warning */
    buffer[(*index)++] = '%';
    return (1);
}

/**
 * @handle_binary - Handles the 'b' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_binary(va_list args, char *buffer, int *index)
{
    unsigned int number = va_arg(args, unsigned int);
    char tmp[32];
    int tmp_index = 31;
    int length = 0;

    if (number == 0)
    {
        buffer[(*index)++] = '0';
        return (1);
    }

    tmp[tmp_index] = '\0';
    while (number > 0)
    {
        tmp[--tmp_index] = (number % 2) ? '1' : '0';
        number /= 2;
    }

    while (tmp[tmp_index])
    {
        buffer[(*index)++] = tmp[tmp_index++];
        length++;
    }
    return (length);
}
/**
 * handle_pointer - Handles the 'p' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_pointer(va_list args, char *buffer, int *index)
{
    void *ptr = va_arg(args, void *);
    unsigned long address = (unsigned long)ptr;
    int length = 0;

    if (ptr == NULL)
    {
        const char *null_str = "(nil)";
        while (null_str[length])
        {
            buffer[(*index)++] = null_str[length++];
        }
        return (length);
    }

    /* Write "0x" prefix to buffer */
    buffer[(*index)++] = '0';
    buffer[(*index)++] = 'x';
    length += 2;

    /* Convert address to hexadecimal string manually */
    char digits[] = "0123456789abcdef";
    char tmp[16];
    int tmp_index = 0;

    /* Handle zero address case separately */
    if (address == 0)
    {
        buffer[(*index)++] = '0';
        length++;
    }
    else
    {
        while (address > 0)
        {
            tmp[tmp_index++] = digits[address % 16];
            address /= 16;
        }
        for (--tmp_index; tmp_index >= 0; --tmp_index)
        {
            buffer[(*index)++] = tmp[tmp_index];
            length++;
        }
    }

    return length;
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
    char buffer[BUFFER_SIZE];
    int index = 0, i;

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
            for (i = 0; spec[i].specifier != '\0'; i++)
            {
                if (*format == spec[i].specifier)
                {
                    spec[i].func(args, buffer, &index);
                    break;
                }
            }
            if (spec[i].specifier == '\0' && *format != '\0')
            {
                buffer[index++] = '%';
                buffer[index++] = *format;
            }
        }
        else
        {
            buffer[index++] = *format;
        }

        if (index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, index);
            index = 0;
        }

        format++;
    }

    if (index > 0)
    {
        write(1, buffer, index);
    }

    va_end(args);
}
