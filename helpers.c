#include "main.h"
#include <string.h>

/**
 * int_to_str - Converts an integer to a string.
 * @n: The integer to be converted.
 * @str: The buffer where the resulting string will be stored.
 * 
 * This function takes an integer value `n` and converts it into a string 
 * representation, storing the result in the buffer pointed to by `str`. 
 */
void int_to_str(int n, char *str)
{
int i = 0, temp, len = 0, neg = 0;

    if (n == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (n < 0)
    {
        neg = 1;
        n = -n;
    }

    while (n > 0)
    {
        str[i++] = n % 10 + '0';
        n /= 10;
    }

    if (neg)
        str[i++] = '-';

    str[i] = '\0';
    len = i;

    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
/**
 * uint_to_str - Converts an unsigned integer to a string.
 * @n: The unsigned integer to be converted.
 * @str: The buffer where the resulting string will be stored.
 * 
 * This function takes an unsigned integer value `n` and converts it into 
 * a string representation, storing the result in the buffer pointed to by 
 * `str`
 */
void uint_to_str(unsigned int n, char *str)
{
    int i = 0, temp, len = 0;

    do {
        str[i++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);

    str[i] = '\0';
    len = i;

    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
/**
 * hex_to_str - Converts an unsigned integer to a hexadecimal string.
 * @n: The unsigned integer to be converted.
 * @str: The buffer where the resulting string will be stored.
 * @uppercase: Flag indicating if the hexadecimal letters should be uppercase.
 * 
 * This function takes an unsigned integer value `n` and converts it into a 
 * hexadecimal string representation, storing the result in the buffer pointed 
 * to by `str`. If `uppercase` is non-zero, the hexadecimal letters will be 
 * uppercase (A-F); otherwise, they will be lowercase (a-f).
 */
void hex_to_str(unsigned int n, char *str, int uppercase)
{
    int i = 0, temp, len = 0;
    char digits[17]; 

    if (uppercase) {
        strcpy(digits, "0123456789ABCDEF");
    } else {
        strcpy(digits, "0123456789abcdef");
    }

    do {
        str[i++] = digits[n % 16];
        n /= 16;
    } while (n > 0);

    str[i] = '\0';
    len = i;

    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
/**
 * ptr_to_str - Converts a pointer to a hexadecimal string.
 * @ptr: The pointer to be converted.
 * @str: The buffer where the resulting string will be stored.
 * 
 * This function takes a pointer value `ptr` and converts it into a hexadecimal 
 * string representation, storing the result in the buffer pointed to by `str`. 
 */
void ptr_to_str(void *ptr, char *str)
{
    unsigned long int n = (unsigned long int)ptr;
    int i = 0, temp, len = 0;

    str[i++] = '0';
    str[i++] = 'x';

    do {
        temp = (n % 16);
        if (temp < 10)
            str[i++] = temp + '0';
        else
            str[i++] = (temp - 10) + 'a';
            n /= 16;
    } while (n > 0);

    str[i] = '\0';
    len = i;

    for (i = 2; i < (len / 2) + 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i + 1];
        str[len - i + 1] = temp;
    }
}
/**
 * str_reverse - Reverses a string in place.
 * @str: The string to be reversed.
 * 
 * This function takes a string `str` and reverses it in place. The reversal 
 * is done by swapping characters from the beginning and end of the string 
 * moving towards the center. The function assumes that the string is 
 * null-terminated. No additional space is allocated for the reversal.
 */
void str_reverse(char *str)
{
    int len = 0, temp;

    while (str[len])
        len++;

    for (int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
/**
 * rot13 - Applies the ROT13 cipher to a string.
 * @str: The string to be transformed.
 *
 * This function takes a string `str` and applies the ROT13 cipher to  * it. 
 * The ROT13 cipher replaces each letter with the letter 13 positions 
 * forward in the alphabet.
 */
void rot13(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z'))
            str[i] = ((str[i] - 'a' + 13) % 26) + 'a';
        else if ((str[i] >= 'A' && str[i] <= 'Z'))
            str[i] = ((str[i] - 'A' + 13) % 26) + 'A';
    }
}
