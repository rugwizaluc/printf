#include "main.h"
/**
 * handle_char - Processes a character argument and adds it to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_char(va_list args, char *buffer, int *index)
{
    buffer[(*index)++] = (char)va_arg(args, int);
    return 1;
}
/**
 * handle_string - Processes a string argument and adds it to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_string(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    int i = 0;

    while (str[i])
    {
        buffer[(*index)++] = str[i++];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return i;
}
/**
 * handle_percent - Processes a percent '%' character and adds it to the buffer.
 * @args: The variadic arguments list (not used in this case).
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_percent(va_list args, char *buffer, int *index)
{
    (void)args;
    buffer[(*index)++] = '%';
    return 1;
}
/**
 * handle_int - Processes an integer argument and adds its string representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_int(va_list args, char *buffer, int *index)
{
    int n = va_arg(args, int);
    char *str = malloc(12 * sizeof(char));
    if (str == NULL)
        return -1;
    int_to_str(n, str);
    int i = 0;

    while (str[i])
    {
        buffer[(*index)++] = str[i++];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }
    free(str);
    return i;
}
