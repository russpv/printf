#include "ft_printf.h"



/* PRINTF
 * cspdiuxX% flags handled
 */

char	*ctoa_inline(char ch)
{
	if (ch == 0)
		return ("");
	return ((char[]){ch, 0});
}

/* Main switch to handle numerical types */
char	*_myf(void *val, e_types typ, t_spec *specs)
{
	char *res;
	char *res2;
	char *sign;
	long long value = 0;
	char pad = 0;

	res2 = "";
	res = "haha";
	sign = "";
	if (typ == INT)
	{
		value = *(int*)val;
		if (value < 0)
		{
			sign = "-";
			value *= -1;
		}
	}
	if (typ == UINT)
		value = *(unsigned int*)val;
	if (typ == PTR)
		value = (unsigned long)val;
	res = ft_itoa(value); /* takes any decimal. just need a convert() func */
	if (specs->leadpadchar == ' ')
		pad = ' ';
	char *str = ctoa_inline('0');
	printf("ctoa: (%s)\n", str);   //TODO figure out how to easily insert single char string
	char *res3 = ft_strjoin(ctoa_inline(' '), res);
	printf("res3: (%s)\n", res3);
	res2 = ft_strjoin(sign, ft_strjoin(str, res));
	free(res);
	return(res2);
}

void	_do_idu_flags(const char *s, va_list args, t_spec *specs)
{
	int value;
	unsigned int uvalue;
	unsigned long long ptr;
	char *res = NULL;

	if (*s != 'i' && *s != 'd' && *s != 'u' && *s != 'p')
		return ;
	if (*s == 'i' || *s == 'd')
	{
		value = va_arg(args, int);
		res = _myf(&value, INT, specs);
	}
	if (*s == 'u')
	{
		uvalue = va_arg(args, unsigned int);
		res = _myf(&uvalue, UINT, specs);
	}
	if (*s == 'p')
	{
		ptr = (unsigned long long)va_arg(args, void *);
		res = _myf(&ptr, PTR, specs);
	}
	ft_putstr(res);
	free(res);
	res = NULL;
}

void	_do_cs_flags(const char *s, va_list args, t_spec *specs)
{
	char *string;

	(void)specs;
	if (*s == 'c')
	{
		char c = (char)va_arg(args, int);
		ft_putchar(c);
	}
	if (*s == 's')
	{
		string = va_arg(args, char *);
		while (*string)
			ft_putchar(*string++);
	}
}
/* Prints the address of the object pointed to */
void	_do_p_flag(const char *s, va_list args, t_spec *specs)
{
	void *p;

	(void)specs;
	if (*s == 'p')
	{
		p = va_arg(args, void *);
		ft_putnbr((unsigned long long)p);
	}
}

void	_do_xX_flags(const char *s, va_list args, t_spec *specs)
{
	(void)s;
	(void)args;
	(void)specs;
	return ;
}

void	_do_pc(const char *s)
{
	if (*s == '%')
		ft_putchar('%');
	return ;
}




/* Checks for prefix flags only */
int	is_flag(const char *s)
{
	char *set = FLAGS;

	while (*set)
		if (*s == *set++ || ft_isdigit((int)*s))
			return (TRUE);
	return (FALSE);
}
/*
static int	_skip(const char **s)
{
	unsigned int ch;

	ch = **s;
	if (ch == '.' && (unsigned int)*(++(*s)) == ch)
		return (FALSE);
	while ((unsigned int)**s == ch)
		(*s)++;
	return (TRUE);
}*/

static void	_init_specs(t_spec *specs)
{
	specs->minwidth = 0;
	specs->minprec = 0;
	specs->ljust = FALSE;
	specs->sign = FALSE;
	specs->alt = FALSE;
	specs->leadpadchar = ' ';
	specs->padchar = ' ';
}

static int	_parse_qty(const char **s, int *var, void *flag)
{
	unsigned int qty;
	char **p;

	p = (char **)s;
	qty = 0;
	if (flag)
		if ((unsigned int)*(++(*p)) == *(unsigned int*)flag)
			return (FALSE);
	while (ft_isdigit(**s))
		qty += **s++ * 10; /* double check the operator prec */
	*var = qty;
	return (TRUE);
}

/* Reads any permutation of flags prior to quantities and flips its switch */
static int	_parse_specs(const char **s, t_spec *specs)
{
	while (is_flag(*s))
	{
		if (**s == '-') /* consecutive repeats okay */
			specs->ljust = TRUE;
		if (**s == '+') /* repeats okay */
			specs->sign = TRUE;
		if (**s == ' ') /* repeats okay */
		{
			printf("leadpad char found \n"); fflush(stdout);
			specs->leadpadchar = ' ';
		}
		if (**s == '0' && specs->ljust == FALSE) /* repeats okay */\
		{
			specs->padchar = '0';
		}
		if (**s == '#') /* repeats okay */
			specs->alt = TRUE; 
		(*s)++;
	}
	if (ft_isdigit(**s))
			_parse_qty(s, &specs->minwidth, NULL);
	else if (**s == '.') /* NOK */
	{
		if (!_parse_qty(s, &specs->minprec, &(char){'.'}))
			return (FALSE);
	}
	return (TRUE);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	t_spec specs;
	const char *start;

	start = NULL;
	_init_specs(&specs);
	va_start(args, s);
	while (*s)
	{
		if (*s != '%')
			ft_putchar((unsigned int)*s);
		else /* is % */
		{
			s++;
			start = s;
			if (is_flag(s))
			{
				if (!_parse_specs(&s, &specs)) /* if invalid, reset ptr */
				{
					printf(" invalid specs...\n"); fflush(stdout);
					s = start;
					continue ;
				}
			}
			_do_idu_flags(s, args, &specs);
			_do_cs_flags(s, args, &specs);
			_do_p_flag(s, args, &specs);
			_do_xX_flags(s, args, &specs);
			_do_pc(s);
		}
		s++;
	}
	va_end(args);
	return (SUCCESS);
}
