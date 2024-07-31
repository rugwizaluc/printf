#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
/**
 * struct vtype - structure to hold char and function pointers
 * @tp: character
 * @f: function
 * 
 */
typedef struct vtype
{
	char tp;
	void (*f)();
} vtype_t;
int _printf(const char *format, ...);
<<<<<< HEAD
void print_char(va_list args);
void print_int(va_list args);
void print_float(va_list args);
void print_string(va_list args);
void _write_buffer(char *buffer, int index);
int _strlen(char *s);
char *_memcpy(char *dest, char *src, unsigned int n);
void format_s(va_list args, char *buffer, int index);
void format_c(va_list args, char *buffer, int index);
void format_d(va_list args, char *buffer, int index);
char *itos(char str[], long int num);
char *utos(char str[], int num);
int num_len(int num);
int float_len(double f);
void format_i(va_list args, char *buffer, int index);
void format_u(va_list args, char *buffer, int index);
void format_perc(va_list args, char *buffer, int index);
void format_p(va_list args, char *buffer, int index);
void format_lx(va_list args, char *buffer, int index);
char *tostring(char str[], int num);
int num_len(int num);
void reset_buffer(char buffer[]);
void *rot13(char *s);
void rev_string(char *s);
void format_h(va_list args, char *buffer, int index);
void format_ch(va_list args, char *buffer, int index);
void format_o(va_list args, char *buffer, int index);
void format_b(va_list args, char *buffer, int index);
void format_r(va_list args, char *buffer, int index);
void format_R(va_list args, char *buffer, int index);
#endif 


