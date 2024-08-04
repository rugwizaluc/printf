#include "main.h"
/**
*@uintToString: Function 
* @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @width: Minimum number of characters to be printed
 * @left_justify: Flag indicating if the result should be left-justified
 *
 * @Return: Number of characters stored in the buffer
 */
void uintToStr(unsigned long num, char *buffer, int base, int uppercase, int *index, int precision, int width, int left_justify)
{
    char digits[] = "0123456789abcdef";
    char tmp[64];
    int tmp_index = 0, num_len = 0;

    if (uppercase)
        for (int i = 0; i < 16; i++)
            digits[i] = (char)toupper(digits[i]);

    if (num == 0 && precision != 0)
    {
        tmp[tmp_index++] = '0';
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
    }

    num_len = tmp_index;

    if (!left_justify)
    {
      while (num_len < width) /* Add leading spaces to meet width */
        {
            buffer[(*index)++] = ' ';
            width--;
        }
    }

    for (--tmp_index; tmp_index >= 0; --tmp_index)
        buffer[(*index)++] = tmp[tmp_index];

    if (left_justify)
    {
      while (num_len < width) /* Add trailing spaces to meet width */
        {
            buffer[(*index)++] = ' ';
            width--;
        }
    }
}

/**
 * @handle_int - Handles the 'd' and 'i' specifiers with precision and width
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @width: Minimum number of characters to be printed
 * @left_justify: Flag indicating if the result should be left-justified
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_int(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify)
{
    long num;
    int negative = 0;

    if (length_modifier == 'l')
        num = va_arg(args, long);
    else if (length_modifier == 'h')
        num = (short)va_arg(args, int);
    else
        num = va_arg(args, int);

    if (num < 0)
    {
        negative = 1;
        num = -num;
    }

    if (negative)
        buffer[(*index)++] = '-';

    uintToStr((unsigned long)num, buffer, 10, 0, index, precision, width, left_justify);

    return 0;
}

/**
 * @handle_unsigned - Handles the 'u' specifier with precision and width
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @width: Minimum number of characters to be printed
 * @left_justify: Flag indicating if the result should be left-justified
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short)va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 10, 0, index, precision, width, left_justify);

    return 0;
}

/**
 * @handle_octal - Handles the 'o' specifier with precision and width
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @width: Minimum number of characters to be printed
 * @left_justify: Flag indicating if the result should be left-justified
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_octal(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short)va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 8, 0, index, precision, width, left_justify);

    return 0;
}

/**
 * @handle_hex - Handles the 'x' and 'X' specifiers with precision and width
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 * @length_modifier: Length modifier ('l' or 'h')
 * @precision: Minimum number of digits to appear
 * @width: Minimum number of characters to be printed
 * @left_justify: Flag indicating if the result should be left-justified
 * @uppercase: Flag indicating if uppercase letters are needed
 *
 * @Return: Number of characters stored in the buffer
 */
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify, int uppercase)
{
    unsigned long num;

    if (length_modifier == 'l')
        num = va_arg(args, unsigned long);
    else if (length_modifier == 'h')
        num = (unsigned short)va_arg(args, unsigned int);
    else
        num = va_arg(args, unsigned int);

    uintToStr(num, buffer, 16, uppercase, index, precision, width, left_justify);
    return 0;
}

/**
 * @_printf - Produces output according to a format
 * @format: Character string to be printed
 * @Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int index = 0, i;
    char length_modifier = '\0';
    int precision = -1, width = 0, left_justify = 0;

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
            width = 0;
            left_justify = 0;

            if (format[f_index] == '-')
            {
                left_justify = 1;
                f_index++;
            }

            while (format[f_index] >= '0' && format[f_index] <= '9')
            {
                width = width * 10 + (format[f_index] - '0');
                f_index++;
            }

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
        }
    }

            for (i = 0; spec[i].specifier != '\0'; i++)
            {
                if (format[f_index] == spec[i].specifier)
                {
                    if (format[f_index] == 'x' || format[f_index] == 'X')
                    {
                    handle_hex(args, buffer, &index, length_modifier, precision, width, left_justify, (format[f_index] == 'X'));
                    }
                    else
                    {
                    spec[i].func(args, buffer, &index, length_modifier, precision, width, left_justify);
                    break;
                }
            }

            if (spec[i].specifier == '\0')
            {
                /* Handle unknown specifier by printing '%' and the following character */
                buffer[index++] = '%';
                if (length_modifier)
                    buffer[index++] = length_modifier;
                if (precision >= 0)
                {
                    buffer[index++] = '.';
                    buffer[index++] = precision + '0';
                }
                if (width > 0)
                {
                    buffer[index++] = width + '0';
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
        if (index > 0)
    {
        write(1, buffer, index);
    }

    va_end(args);
    }
