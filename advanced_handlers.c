#include "main.h"
/**
 * handle_binary - Processes an unsigned integer argument and adds its binary representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_binary(va_list args, char *buffer, int *index)
{
    unsigned int n = va_arg(args, unsigned int);
    char str[33];
    int i = 0;

    while (n > 0)
    {
        str[i++] = (n % 2) + '0';
        n /= 2;
    }
    if (i == 0)
        str[i++] = '0';
    str[i] = '\0';

    for (int j = i - 1; j >= 0; j--)
    {
        buffer[(*index)++] = str[j];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return i;
}
/**
 * handle_unsigned - Processes an unsigned integer argument and adds its string representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_unsigned(va_list args, char *buffer, int *index)
{
    unsigned int n = va_arg(args, unsigned int);
    char str[20];
    uint_to_str(n, str);
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
 * handle_octal - Processes an unsigned integer argument and adds its octal representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_octal(va_list args, char *buffer, int *index)
{
    unsigned int n = va_arg(args, unsigned int);
    char str[12];
    int i = 0;

    do {
        str[i++] = (n % 8) + '0';
        n /= 8;
    } while (n > 0);
    str[i] = '\0';

    for (int j = i - 1; j >= 0; j--)
    {
        buffer[(*index)++] = str[j];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return i;
}
/**
 * handle_hex - Processes an unsigned integer argument and adds its hexadecimal representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 * @uppercase: Flag indicating if hexadecimal letters should be uppercase.
 */
int handle_hex(va_list args, char *buffer, int *index, int uppercase)
{
    unsigned int n = va_arg(args, unsigned int);
    char str[20];
    hex_to_str(n, str, uppercase);
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
 * handle_pointer - Processes a pointer argument and adds its hexadecimal representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_pointer(va_list args, char *buffer, int *index)
{
    void *ptr = va_arg(args, void *);
    char str[20];
    ptr_to_str(ptr, str);
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
 * handle_non_printable_string - Processes a string argument and adds its printable representation to the buffer,
 *                               replacing non-printable characters with escape sequences.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_non_printable_string(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    int i = 0,
    char hex[5] = "\\x00";

    while (str[i])
    {
        if ((str[i] > 0 && str[i] < 32) || str[i] >= 127)
        {
            hex_to_str((unsigned int)str[i], hex + 2, 1);
            for (int j = 0; hex[j]; j++)
            {
                buffer[(*index)++] = hex[j];
                if (*index >= BUFFER_SIZE - 1)
                {
                    write(1, buffer, *index);
                    *index = 0;
                }
            }
        }
        else
        {
            buffer[(*index)++] = str[i];
        }
        i++;
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return i;
}
/**
 * handle_reverse_string - Processes a string argument and adds its reversed representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_reverse_string(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    int len = 0;

    while (str[len])
        len++;

    for (int i = len - 1; i >= 0; i--)
    {
        buffer[(*index)++] = str[i];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return len;
}
/**
 * handle_rot13_string - Processes a string argument and adds its ROT13-transformed representation to the buffer.
 * @args: The variadic arguments list.
 * @buffer: The buffer where the resulting string will be stored.
 * @index: Pointer to the current index in the buffer.
 */
int handle_rot13_string(va_list args, char *buffer, int *index)
{
    char *str = va_arg(args, char *);
    char rot13_str[1024];
    int i = 0;

    while (str[i])
    {
        rot13_str[i] = str[i];
        i++;
    }
    rot13_str[i] = '\0';

    rot13(rot13_str);

    i = 0;
    while (rot13_str[i])
    {
        buffer[(*index)++] = rot13_str[i++];
        if (*index >= BUFFER_SIZE - 1)
        {
            write(1, buffer, *index);
            *index = 0;
        }
    }

    return i;
}
