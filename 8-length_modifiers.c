#include "main.h"
/**
 * 
 * @uint_to_str - Converts an unsigned long integer to a string representation
 * @num: The unsigned long integer to convert
 * @buffer: The buffer to store the resulting string
 * @base: The numerical base for conversion (e.g., 10 for decimal, 8 for octal, 16 for hexadecimal)
 * @uppercase: A flag indicating whether to use uppercase letters for hex digits (1 for uppercase, 0 for lowercase)
 * @index: Pointer to the index in the buffer where the conversion should start and update to the end of the string
 *
 * This function converts an unsigned long integer to its string representation in the specified base. The result is 
 * stored in the provided buffer starting at the given index. The `uppercase` flag determines whether hexadecimal 
 * digits should be in uppercase or lowercase.
 */
void uintToStr(unsigned long number, char *buffer, int base, int uppercase, int *index)
{
    char digits[] = "0123456789abcdef";
    char tmp[64];
    int tmp_index = 0;

    if (uppercase)
        for (int i = 0; i < 16; i++)
            digits[i] = (char) toupper(digits[i]);

    if (number == 0)
        buffer[(*index)++] = '0';
    else
    {
        while (number > 0)
        {
            tmp[tmp_index++] = digits[number % base];
            number /= base;
        }
        for (--tmp_index; tmp_index >= 0; --tmp_index)
            buffer[(*index)++] = tmp[tmp_index];
    }
}
/**
 * @handle_int - Handles the 'd' and 'i' specifiers
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 *
 * @Return: number of characters stored in the buffer
 */
int handle_int(va_list args, char *buffer, int *index, char length_modifier)
{
    long number;
    int negative = 0;

    if (length_modifier == 'l')
        number = va_arg(args, long);
    else if (length_modifier == 'h')
        number = (short) va_arg(args, int);
    else
        number = va_arg(args, int);

    if (number < 0)
    {
        negative = 1;
        number = -number;
    }

    if (negative)
        buffer[(*index)++] = '-';

    uintToString((unsigned long) number, buffer, 10, 0, index);

    return 0;
}
/**
 * @handle_unsigned - Handles the 'u' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 *
 * @Return: number of characters stored in the buffer
 */
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier)
{
    unsigned long number;

    if (length_modifier == 'l')
        number = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        number = (unsigned short) va_arg(args, unsigned int);
    else
        number = va_arg(args, unsigned int);

    uintToString(number, buffer, 10, 0, index);

    return 0;
}
/**
 * @handle_octal - Handles the 'o' specifier
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_octal(va_list args, char *buffer, int *index, char length_modifier)
{
    unsigned long number;

    if (length_modifier == 'l')
        number = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        number = (unsigned short) va_arg(args, unsigned int);
    else
        number = va_arg(args, unsigned int);

    uintToString(number, buffer, 8, 0, index);

    return 0;
}

/**
 * @handle_hex - Handles the 'x' and 'X' specifiers
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @uppercase: Flag indicating if uppercase letters are needed
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int uppercase)
{
    unsigned long number;

    if (length_modifier == 'l')
        number = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        number = (unsigned short) va_arg(args, unsigned int);
    else
        number = va_arg(args, unsigned int);

    uintToString(number, buffer, 16, uppercase, index);

    return 0;
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
    char length_modifier = '\0';

    /* Array of specifier-function pairs */
    spec_t spec[] = {
        {'d', handle_int},
        {'i', handle_int},
        {'u', handle_unsigned},
        {'o', handle_octal},
        {'x', handle_hex},
        {'X', handle_hex},
        {'\0', NULL} /* End of array */
    };

    va_start(args, format);

    if (format == NULL)
        return -1;

    for (int f_index = 0; format[f_index] != '\0'; f_index++)
    {
        if (format[f_index] == '%')
        {
            f_index++;

            if (format[f_index] == 'l' || format[f_index] == 'h')
            {
                length_modifier = format[f_index];
                f_index++;
            }

            for (i = 0; spec[i].specifier != '\0'; i++)
            {
                if (format[f_index] == spec[i].specifier)
                {
                    if (format[f_index] == 'x' || format[f_index] == 'X')
                    {
                    handle_hex(args, buffer, &index, length_modifier, (format[f_index] == 'X'));
                    }
                    else
                    {
                    spec[i].func(args, buffer, &index, length_modifier);
                    }
                    break;
                }
            }

            if (spec[i].specifier == '\0' && format[f_index] != '\0')
            {
                buffer[index++] = '%';
                if (length_modifier)
                    buffer[index++] = length_modifier;
                buffer[index++] = format[f_index];
            }

            length_modifier = '\0';  /* Reset length modifier after use */
        }
        else
        {
            buffer[index++] = format[f_index];
            
        }

        if (index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, index);
            index = 0;
        }
    }

    if (index > 0)
    {
        write(1, buffer, index);
    }

    va_end(args);
 }
