#include "../../include/util.h"
#include "../../include/screen.h"
#include <stdarg.h>

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);             //    dest[i] = source[i]
    }
}

void memory_set(uint8 *dest, uint8 val, uint32 len) {
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {          
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';         
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
    return str;
}
string int_to_string(int n)
{
	string ch = malloc(50);
	int_to_ascii(n,ch);
	int len = strlength(ch);
	int i = 0;
	int j = len - 1;
	while(i<(len/2 + len%2))
	{
		char tmp = ch[i];
		ch[i] = ch[j];
		ch[j] = tmp;
		i++;
		j--;
	}
	return ch;
}

int str_to_int(string ch)
{
	int n = 0;
	int p = 1;
	int strlen = strlength(ch);
	int i;
	for (i = strlen-1;i>=0;i--)
	{
		n += ((int)(ch[i] - '0')) * p;
		p *= 10;
	}
	return n;
}

string char_to_string(char ch) {
	string str;
	str[0] = ch;

	return str;
}

void * malloc(int nbytes)
{
	char variable[nbytes];
	return &variable;
}

void printf_list(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	uint8 *ptr;

	for (ptr = format; *ptr != '\0'; ptr++) {
		if (*ptr == '%') {
			ptr++;
			switch (*ptr) {
				case 's':
					printf(va_arg(ap, uint8 *));
					break;
				//case 'c':
					//printf(char_to_string(va_arg(ap, uint8 *)));
				case 'd':
					printf(int_to_string(va_arg(ap, uint8 *)));
					break;
				case '%':
					printfch('%');
					break;
			}
		} else {
			printfch(*ptr);
		}
	}

	va_end(ap);
}
