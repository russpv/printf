#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list args;
	va_start(args, s);

	char *p;

	for (p = (char *)s; *p != 0; p++)
	{
		if (*p == '%')
		{
			p++;
			switch (*p) {
				case 's':
					fputs(va_arg(args, char *), stdout);
					break;
				case '%':
					putchar('%');
					break;
			}
		} else {
			putchar(*p);
		}
	}



	va_end(args);
	return (1);
}
