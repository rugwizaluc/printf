#include "main.h"
/**
 * uintTostr - Converts an unsigned long integer to a string representation
 *               with a specified base and stores it in a buffer.
 * @num: The unsigned long integer to convert.
 * @buffer: The buffer to store the resulting string.
 * @base: The numerical base for conversion (e.g., 10 for decimal, 8 for octal, 16 for hexadecimal).
 * @uppercase: A flag indicating whether to use uppercase letters for hex digits (1 for uppercase, 0 for lowercase).
 * @index: Pointer to the current index in the buffer; updated as characters are added.
 * @precision: The minimum number of digits to include in the output. If the number has fewer digits, it is padded with leading zeros.
 *
 * Description:
 * This function converts an unsigned long integer to its string representation
 * in the specified base and stores the result in the provided buffer starting
 * at the given index. The result is left-padded with zeros to meet the specified
 * precision if necessary. The 'uppercase' flag controls whether hexadecimal
 * letters are in uppercase ('A'-'F') or lowercase ('a'-'f'). The 'index' pointer
 * is used to track the position in the buffer where the next character should be
 * placed and is updated as characters are added.
 */
void uintToStr(unsigned long num, char *buffer, int base, int uppercase, int *index, int precision)
{
    char digits[] = "0123456789abcdef";
    char tmp[64];
    int tmp_index = 0;

    if (uppercase)
        for (int i = 0; i < 16; i++)
            digits[i] = (char) toupper(digits[i]);

    if (num == 0 && precision != 0)
    {
        buffer[(*index)++] = '0';
    }
    else
    {
        while (num > 0)
        {
            tmp[tmp_index++] = digits[num % base];
            num /= base;
        }

        while (tmp_index < precision) /* Add leading zeros to meet precision */
        {
            tmp[tmp_index++] = '0';
        }

        for (--tmp_index; tmp_index >= 0; --tmp_index)
            buffer[(*index)++] = tmp[tmp_index];
    }
}

/**
 * handle_int - Handles the 'd' and 'i' specifiers with precision
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 *
 * Return: Number of characters stored in the buffer
 */
int handle_int(va_list args, char *buffer, int *index, char length_modifier, int precision)
{
    long num;
    int negative = 0;

    if (length_modifier == 'l')
        num = va_arg(args, long);
    else if (length_modifier == 'h')
        num = (short) va_arg(args, int);
    else
        num = va_arg(args, int);

    if (num < 0)
    {
        negative = 1;
        num = -num;
    }

    if (negative)
        buffer[(*index)++] = '-';

    uintToStr((unsigned long) num, buffer, 10, 0, index, precision);

    return 0;
}

/**
 * handle_unsigned - Handles the 'u' specifier with precision
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 *
 * Return: Number of characters stored in the buffer
 */
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier, int precision)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short) va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 10, 0, index, precision);

    return 0;
}

/**
 * handle_octal - Handles the 'o' specifier with precision
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 *
 * Return: Number of characters stored in the buffer
 */
int handle_octal(va_list args, char *buffer, int *index, char length_modifier, int precision)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short) va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 8, 0, index, precision);

    return 0;
}

/**
 * handle_hex - Handles the 'x' and 'X' specifiers with precision
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @uppercase: Flag indicating if uppercase letters are needed
 *
 * Return: Number of characters stored in the buffer
 */
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int precision, int uppercase)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short) va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 16, uppercase, index, precision);

    return 0;
}

/**
 * _printf - Produces output according to a format
 * @format: Character string to be printed
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int index = 0, total_printed = 0, i;
    char length_modifier = '\0';
    int precision = -1;

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
            length_modifier = '\0';
            precision = -1;

            if (format[f_index] == 'l' || format[f_index] == 'h')
            {
                length_modifier = format[f_index];
                f_index++;
            }

            if (format[f_index] == '.')
            {
                f_index++;
                precision = 0;

                while (format[f_index] >= '0' && format[f_index] <= '9')
                {
                    precision = precision * 10 + (format[f_index] - '0');
                    f_index++;
                }
            }

            for (i = 0; spec[i].specifier != '\0'; i++)
            {
                if (format[f_index] == spec[i].specifier)
                {
                    if (format[f_index] == 'x' || format[f_index] == 'X')
                    {
                    handle_hex(args, buffer, &index, length_modifier, precision, (format[f_index] == 'X'));
                    }
                    else
                    {
                    spec[i].func(args, buffer, &index, length_modifier, precision);
                    }
                    break;
                }
            }

            if (spec[i].specifier == '\0' && format[f_index] != '\0')
            {
                buffer[index++] = '%';
                if (length_modifier)
                    buffer[index++] = length_modifier;
                if (precision >= 0)
                {
                    buffer[index++] = '.';
                    buffer[index++] = precision + '0';
                }
                buffer[index++] = format[f_index];
            }
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

