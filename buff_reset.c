#include "main.h"
#include <stdio.h>
/**
  * reset_buffer - function that initializes and resets a buffer
  * @buffer: buffer size
  */
void buffer_reset(char *buffer)
{
	int n;

	for (n = 0; n < 1024; n++)
	{
		buffer[n] = 0;
	}
	buffer[n] = '\0';
}
