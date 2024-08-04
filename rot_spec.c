#include "main.h"
/**
 * @handle_rot13 - Handles the 'R' specifier (ROT13 encoding)
 * @args: List of arguments
 * @buffer: Buffer to store characters
 * @index: Index in the buffer
 *
 * @Return: Number of characters stored in the buffer
 */
int rot13(const char *input, char *buffer, int *index)
        {      
    while (*input)
        {
        char c = *input++;
        if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A' + 13) % 26) + 'A';
        } else if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' + 13) % 26) + 'a';
        }
        buffer[(*index)++] = c;
    }
    return *index;
}

int handle_rot13(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify) {
  (void)length_modifier;
  (void)precision;
  (void)width;
  (void)left_justify;
  char *str = va_arg(args, char *);
    if (str == NULL) {
        const char *null_str = "(null)";
        while (*null_str) {
            buffer[(*index)++] = *null_str++;
        }
        return 6;
    }
     return rot13(str, buffer, index);
}
    
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int index = 0, total_printed = 0, i;
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
        {'R', handle_rot13}, 
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

            for (i = 0; spec[i].specifier != '\0'; i++)
            {
                if (format[f_index] == spec[i].specifier)
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
    }

    if (index > 0)
    {
        write(1, buffer, index);
    }
    va_end(args);
 }
