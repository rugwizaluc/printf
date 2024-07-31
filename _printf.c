#include "main.h"
/**
  * _printf - function that prints characters based on format specifier
  * @format: string that takes in format specifier
  * Return: number of characters printed
  */
int _printf(const char *format, ...)
{
    char buffer[1024];
    int j, n = 0, index = 0; 
    va_list args;
    vtype_t specifier[] = {
        {'c', format_c}, {'s', format_s}, {'d', format_d}, {'i', format_d},
        {'u', format_u}, {'%', format_perc}, {'x', format_x}, {'X', format_X},
        {'o', format_o}, {'b', format_b}, {'p', format_p}, {'r', format_r},
        {'R', format_R}, {'\0', NULL}
    };

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (j = 0; format[j] != '\0'; j++)
    {
        while (format[j] != '%' && format[j] != '\0')
        {
            if (index == 1024)
            {
                _write_buffer(buffer, &index);
                reset_buffer(buffer);
                index = 0;
            }
            buffer[index++] = format[j++];
        }

        if (format[j] == '\0')
            break;

        if (format[j] == '%')
        {
            j++;
            for (n = 0; specifier[n].tp != '\0'; n++)
            {
                if (format[j] == specifier[n].tp)
                {
                    specifier[n].f(args, buffer, &index);
                    break;
                }
            }
        }
    }

    va_end(args);

    buffer[index] = '\0';
    _write_buffer(buffer, &index);

    return index; 

}
