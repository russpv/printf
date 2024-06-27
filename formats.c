#include "ft_printf.h"

/* Defeat any invalid input based on type rules */
static void	_reset_specs(t_spec *specs, t_types type)
{
	if (type == INT)
		specs->sch = "+";
	if (type == HEX || type == PTR)
		specs->base = 16;
	if (type == CHR || type == HEX || type == PTR || type == UINT || \
		type == STR)
		specs->signflg = FALSE;
	if (type == CHR)
		specs->mpflg = FALSE;
}

void	do_idu_formats(const char *s, va_list *args, t_spec *specs)
{
	long long			value;
	unsigned long long	uvalue;
	unsigned long long	ptr;

	if (*s == 'i' || *s == 'd')
	{
		value = va_arg(*args, long long);
		_reset_specs(specs, INT);
		print_output(type_switch(&value, INT, specs), specs);
	}
	else if (*s == 'u')
	{
		uvalue = va_arg(*args, unsigned long long);
		_reset_specs(specs, UINT);
		print_output(type_switch(&uvalue, UINT, specs), specs);
	}
	else if (*s == 'p')
	{
		ptr = (unsigned long long)va_arg(*args, void *);
		_reset_specs(specs, PTR);
		print_output(type_switch(&ptr, PTR, specs), specs);
	}
	else
		return ;
}

void	do_cs_formats(const char *s, va_list args, t_spec *specs)
{
	char	*string;
	char	*res;
	char	c;

	res = NULL;
	if (*s == 'c')
	{
		c = (char)va_arg(args, int);
		_reset_specs(specs, CHR);
		print_output(type_switch(&c, CHR, specs), specs);
	}
	else if (*s == 's')
	{
		string = va_arg(args, char *);
		_reset_specs(specs, STR);
		print_output(type_switch(string, STR, specs), specs);
	}
	else
		return ;
}

void	do_xx_formats(const char *s, va_list args, t_spec *specs)
{
	unsigned long long	num;
	char				*res;

	num = 0;
	res = NULL;
	if (*s != 'X' && *s != 'x')
		return ;
	num = va_arg(args, unsigned long long);
	_reset_specs(specs, HEX);
	res = type_switch(&num, HEX, specs);
	if (res == NULL)
	{
		res = "(null)";
		ft_putstr(res);
		return ;
	}
	else if (*s == 'X')
		res = to_upper(res);
	if (specs->altflg == TRUE)
		res = safe_join(ft_strjoin("0x", ""), res);
	print_output(res, specs);
}

void	do_pc(const char *s)
{
	if (*s == '%')
		ft_putchar('%');
	return ;
}
