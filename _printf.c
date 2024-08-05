#include "main.h"
/**
 * _printf - A simplified implementation of the printf function.
 * @format: The format string containing text and format specifiers.
 * @...: Variadic arguments to be formatted according to the format string.
 */
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int index = 0,

    spec_t specs[] = {
        {'c', handle_char},
        {'s', handle_string},
        {'%', handle_percent},
        {'d', handle_int},
        {'i', handle_int},
        {'b', handle_binary},
        {'u', handle_unsigned},
        {'o', handle_octal},
        {'x', handle_hex},
        {'X', handle_hex},
        {'p', handle_pointer},
        {'S', handle_non_printable_string},
        {'r', handle_reverse_string},
        {'R', handle_rot13_string},
        {'\0', NULL}
    };

    va_start(args, format);

    if (format == NULL)
        return -1;

    for (int f_index = 0; format[f_index] != '\0'; f_index++)
    {
        if (format[f_index] == '%')
        {
            f_index++;
            for (int s_index = 0; specs[s_index].spec != '\0'; s_index++)
            {
                if (format[f_index] == specs[s_index].spec)
                {
                    if (format[f_index] == 'X')
                        specs[s_index].handler(args, buffer, &index);
                    else
                        specs[s_index].handler(args, buffer, &index);
                    break;
                }
            }
        }
        else
        {
            buffer[index++] = format[f_index];
            if (index >= BUFFER_SIZE - 1)
            {
                write(1, buffer, index);
                index = 0;
            }
        }
    }

    if (index > 0)
    {
        write(1, buffer, index);
    }

    va_end(args);
}
