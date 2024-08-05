#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define BUFFER_SIZE 1024

/**
 * typedef struct specifier - Defines a structure for handling format specifiers.
 * @spec: The format specifier character (e.g., 'd' for integer, 's' for string).
 * @handler: Function pointer to the handler function for the corresponding specifier.
 */
typedef struct specifier {
    char spec;
    int (*handler)(va_list args, char *buffer, int *index);
} spec_t;
/* Function prototypes */
int _printf(const char *format, ...);

/* Handler function prototypes */
int handle_char(va_list args, char *buffer, int *index);
int handle_string(va_list args, char *buffer, int *index);
int handle_percent(va_list args, char *buffer, int *index);
int handle_int(va_list args, char *buffer, int *index);
int handle_binary(va_list args, char *buffer, int *index);
int handle_unsigned(va_list args, char *buffer, int *index);
int handle_octal(va_list args, char *buffer, int *index);
int handle_hex(va_list args, char *buffer, int *index, int uppercase);
int handle_pointer(va_list args, char *buffer, int *index);
int handle_non_printable_string(va_list args, char *buffer, int *index);
int handle_reverse_string(va_list args, char *buffer, int *index);
int handle_rot13_string(va_list args, char *buffer, int *index);

/* Helper function prototypes */
void int_to_str(int n, char *str);
void uint_to_str(unsigned int n, char *str);
void hex_to_str(unsigned int n, char *str, int uppercase);
void ptr_to_str(void *ptr, char *str);
void str_reverse(char *str);
void rot13(char *str);

#endif
