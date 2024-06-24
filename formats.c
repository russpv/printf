#include "ft_printf.h"

/* Defeat any invalid input based on type rules */
static void	_reset_specs(t_spec *specs, t_types type)
{
	if (type == INT)
		specs->sch = "+";
	if (type == HEX || type == PTR)
		specs->base = 16;
	if (type == UINT || type == PTR || type == HEX)
	{
		specs->lch = "";
		specs->signflg = FALSE;
	}
	else if (type == STR)
	{
		specs->pch = ' ';
		specs->lch = "";
		specs->signflg = FALSE;
	}
	else if (type == CHR)
	{
		specs->pch = ' ';
		specs->lch = "";
		specs->signflg = FALSE;
		specs->mpflg = FALSE;
	}
}

void	_do_idu_flags(const char *s, va_list args, t_spec *specs)
{
	int				value;
	unsigned int	uvalue;
	unsigned long	ptr;

	if (*s == 'i' || *s == 'd')
	{
		value = va_arg(args, int);
		_reset_specs(specs, INT);
		_printoutput(type_switch(&value, INT, specs));
	}
	else if (*s == 'u')
	{
		uvalue = va_arg(args, unsigned long);
		_reset_specs(specs, UINT);
		_printoutput(type_switch(&uvalue, UINT, specs));
	}
	else if (*s == 'p')
	{
		ptr = (unsigned long)va_arg(args, void *);
		_reset_specs(specs, PTR);
		_printoutput(type_switch(&ptr, PTR, specs));
	}
	else
		return ;
}

void	_do_cs_flags(const char *s, va_list args, t_spec *specs)
{
	char	*string;
	char	*res;
	char	c;

	res = NULL;
	if (*s == 'c')
	{
		c = (char)va_arg(args, int);
		_reset_specs(specs, CHR);
		res = type_switch(&c, CHR, specs);
	}
	else if (*s == 's')
	{
		string = va_arg(args, char *);
		_reset_specs(specs, STR);
		res = type_switch(string, STR, specs);
	}
	else
		return ;
	_printoutput(res);
}

void	_do_xx_flags(const char *s, va_list args, t_spec *specs)
{
	unsigned int	num;
	char			*res;

	num = 0;
	res = NULL;
	if (*s != 'X' && *s != 'x')
		return ;
	num = va_arg(args, unsigned int);
	_reset_specs(specs, HEX);
	res = type_switch(&num, HEX, specs);
	if (res == NULL)
	{
		res = "(null)";
		ft_putstr(res);
		return ;
	}
	else if (*s == 'X')
		res = _toupper(res);
	ft_putstr(res);
	free(res);
	res = NULL;
}

void	_do_pc(const char *s)
{
	if (*s == '%')
		ft_putchar('%');
	return ;
}