#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list a_list;
	va_start(a_list, s);
	va_end(a_list);
	return (1);
}
