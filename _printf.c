#include "main.h"
/**
 *_printf - Custom implementation of the printf function
 * @format: A format string containing the desired characters and format specifiers
 * Return: The total number of characters printed, or -1 if an error occur * s.
 * Description:
 * The _printf function produces output according to a specified format. It is
 * a custom implementation similar to the standard printf function in C.
 * The function supports a variety of format specifiers
 */
int _printf(const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    int index = 0;
    int f_index, s_index;
    int printed_chars = 0; 
    int i;
    
    spec_t specs[] = {
        {'c', handle_char},
        {'s', handle_string},
        {'%', handle_percent},
        {'d', handle_int},
        {'i', handle_int},
        {'b', handle_binary},
        {'u', handle_unsigned},
        {'o', handle_octal},
        {'x', handle_hex_lower},
        {'X', handle_hex_upper},
        {'p', handle_pointer},
        {'S', handle_non_printable_string},
        {'r', handle_reverse_string},
        {'R', handle_rot13_string},
        {'\0', NULL}
    };

    va_start(args, format);

    if (format == NULL)
        return -1;

    for (f_index = 0; format[f_index] != '\0'; f_index++)
    {
        if (format[f_index] == '%')
        {
            f_index++;
            for (s_index = 0; specs[s_index].spec != '\0'; s_index++)
            {
                if (format[f_index] == specs[s_index].spec)
                {
                    if (format[f_index] == 'X')
                        i = specs[s_index].handler(args, buffer, &index);
                    else
                        i = specs[s_index].handler(args, buffer, &index);
                    
                    printed_chars += i;
                    break;
                }
            }
        }
        else
        {
            buffer[index++] = format[f_index];
            printed_chars++;
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
        printed_chars += index; 
    }

    va_end(args);
    return printed_chars; 
}


