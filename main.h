#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#define BUFFER_SIZE 1024

typedef struct {
    char specifier;
    int (*func)(va_list args);
} spec_t;

typedef struct {
    char specifier;
  int (*func)(va_list args, char *buffer, int *index);
} spec_t;

typedef struct {
    char specifier;
    int (*func)(va_list args, char *buffer, int *index, char length_modifier, int precision);
} spec_t;

typedef struct {
    char specifier;
  int (*func)(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify);
} spec_t;

int handle_char(va_list args);
int handle_string(va_list args);
int handle_perc(va_list args);
int handle_binary(va_list args);
int _printf(const char *format, ...);
int handle_char(va_list args, char *buffer, int *index);
int handle_string(va_list args, char *buffer, int *index);
int handle_percent(va_list args, char *buffer, int *index);
int handle_binary(va_list args, char *buffer, int *index);
int handle_pointer(va_list args, char *buffer, int *index);
void uintToStr(unsigned long num, char *buffer, int base, int uppercase, int *index, int precision);
int handle_int(va_list args, char *buffer, int *index, char length_modifier, int precision);
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier, int precision);
int handle_octal(va_list args, char *buffer, int *index, char length_modifier, int precision);
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int precision, int uppercase);
void uintToStr(unsigned long number, char *buffer, int base, int uppercase, int *index);
int handle_int(va_list args, char *buffer, int *index, char length_modifier);
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier);
int handle_octal(va_list args, char *buffer, int *index, char length_modifier);
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int uppercase);
void uintToStr(unsigned long num, char *buffer, int base, int uppercase, int *index, int precision, int width, int left_justify);
int handle_int(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify);
int handle_unsigned(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify);
int handle_octal(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify);
int handle_hex(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify, int uppercase);
int rot13(const char *input, char *buffer, int *index);
int handle_rot13(va_list args, char *buffer, int *index, char length_modifier, int precision, int width, int left_justify);
#endif
