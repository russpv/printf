#include "ft_printf.h"

/* PRINTF
 * cspdiuxX% flags handled
 */

static inline char	*_toupper(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		*tmp = ft_toupper(*tmp);
		tmp++;
	}
	return (s);
}
static inline char	*_repeat(size_t len, char ch)
{
	char	*new;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = 0;
	ft_memset(new, ch, len);
	return (new);
}

/* Main switch to handle numerical types
 **/
char	*_myf(void *val, t_types typ, t_spec *specs)
{
	char		*res;
	char		*res2;
	long long	value;
	char		*tmp;

	res = NULL;
	res2 = NULL;
	value = 0;
	if (typ == INT)
	{
		value = *(int *)val;
		if (value < 0) /* have to print "-" and ignore lchar */
		{
			specs->schar = "-";
			specs->signflag = TRUE; /* defeat sign ("+") for leadpadchar */
			value *= -1;
		}
		res = ft_itoa_base(value, 10);
		if (!res)
			return (NULL);
	}
	if (typ == HEX)
	{
		value = *(unsigned int *)val;
		res = ft_itoa_base(value, 16);
		if (!res)
			return (NULL);
	}
	if (typ == UINT) /* no flags valid */
	{
		value = *(unsigned int *)val;
		res = ft_itoa(value);
		if (!res)
			return (NULL);
	}
	if (typ == PTR) /* always hex with 0x */
	{
		value = *(unsigned long *)val;
		res = ft_itoa_base(value, 16);
		if (!res)
			return (NULL);
		res2 = ft_strjoin("0x", res);
		free(res);
		if (!res2)
			return (NULL);
		if (ft_strncmp(res2, "0x0", ft_strlen(res2)) == 0)
		{
			free(res2);
			res2 = ft_strjoin("(nil)", "");
		}
		res = res2;
	}
	if (typ == STR || typ == CHR)
	{
		res = (char *)val;
		if (!res && (specs->minprecflag == TRUE && specs->minprec < 6))
			res = ft_substr("", 0, 0);
		else if (!res && (specs->minwidthflag || (specs->minprecflag == TRUE
					&& specs->minprec >= 6)))
			res = ft_substr("(null)", 0, 6);
		else if (res)
		{
			res = ft_substr((char *)val, 0, ft_strlen((char *)val));
			if (!res)
				return (NULL);
		}
		specs->len = ft_strlen(res);
		if (typ == CHR && specs->len == 0)
			specs->len = 1;
		if (specs->minprecflag && specs->minprec < specs->len)
			/* do truncation */
		{
			tmp = ft_substr(res, 0, specs->minprec);
			specs->len = ft_strlen(tmp);
			free(res);
			res = tmp;
		}
		if (specs->minwidthflag && specs->minwidth > specs->len) /* minwidth */
		{
			tmp = _repeat(specs->minwidth - specs->len, specs->pch);
			if (specs->ljustflag == TRUE)
				res2 = ft_strjoin(res, tmp);
			else
				res2 = ft_strjoin(tmp, res);
			free(tmp);
			free(res);
			res = res2;
		}
		return (res);
	}
	if (typ == UINT || typ == INT || typ == HEX || typ == PTR)
		/* res is populated */
	{
		/* Do precision padding for nums. Truncation for str.*/
		if (specs->minprecflag)
		{
			if (specs->minprec == 0 && (ft_strncmp(res, "0", 1) == 0))
				/*zero invis if 0 prec */
				res = ft_strjoin("", "");                             
					/* truncation */
			if (ft_strlen(res) < specs->minprec)                      
				/* leading zeros */
			{
				tmp = _repeat(specs->minprec - ft_strlen(res), '0');
				if (!tmp)
					return (NULL);
				res2 = ft_strjoin(tmp, res);
				if (!res2)
					return (NULL);
				//				printf("MYF: precision done (%s)\n", res2); fflush(stdout);
				free(res);
				free(tmp);
				tmp = NULL;
				res = res2;
			}
		}
		specs->len = ft_strlen(res) + specs->leadcharflag
			* ft_strlen(specs->lchar) + specs->signflag
			* ft_strlen(specs->schar);
		/* Do sign */
		if (specs->signflag && (specs->minprec || specs->pch != '0'))
		{
			specs->signflag = FALSE;
			res2 = ft_strjoin(specs->schar, res);
			free(res);
			res = NULL;
			if (!res2)
				return (NULL);
			res = res2;
		}
		if (specs->minwidth > specs->len) /* Do minwidth padding */
		{
			if (specs->ljustflag == TRUE)
			{
				specs->postlen = specs->minwidth - specs->len;
				tmp = _repeat(specs->postlen, specs->pch);
				res2 = ft_strjoin(res, tmp);
			}
			else
			{
				specs->prelen = specs->minwidth - specs->len;
				tmp = _repeat(specs->prelen, specs->pch);
				res2 = ft_strjoin(tmp, res);
			}
			free(res);
			res = NULL;
			if (!tmp)
				return (NULL);
			free(tmp);
			tmp = NULL;
			if (!res2)
				return (NULL);
			res = res2;
		}
		if (specs->leadcharflag)
		{
			res2 = ft_strjoin(specs->lchar, res); /* Do leadchar */
			free(res);
			if (!res2)
				return (NULL);
			res = res2;
		}
		if (specs->signflag && !specs->minprec)
		{
			res2 = ft_strjoin(specs->schar, res);
			free(res);
			res = NULL;
			if (!res2)
				return (NULL);
			res = res2;
		}
		return (res);
	}
	return (NULL);
}

/* Defeat any invalid input based on type rules */
static void	_reset_specs(t_spec *specs, t_types type)
{
	if (type == UINT)
	{
		specs->signflag = FALSE;
		specs->lchar = ""; /* ' ' '+' '-' concept invalid */
	}
	else if (type == PTR)
	{
		specs->signflag = FALSE;
		specs->lchar = "";
	}
	else if (type == INT)
	{
		specs->schar = "+"; /* set to "" by default */
	}
	else if (type == STR)
	{
		specs->pch = ' ';
		specs->lchar = "";
		specs->signflag = 0;
	}
	else if (type == HEX)
	{
		specs->signflag = FALSE;
		specs->lchar = "";
	}
	else if (type == CHR)
	{
		specs->pch = ' ';
		specs->lchar = "";
		specs->signflag = 0;
		specs->minprecflag = FALSE;
	}
}
void	_do_idu_flags(const char *s, va_list args, t_spec *specs)
{
	int				value;
	unsigned int	uvalue;
	unsigned long	ptr;
	char			*res;

	res = NULL;
	if (*s != 'i' && *s != 'd' && *s != 'u' && *s != 'p')
		return ;
	if (*s == 'i' || *s == 'd')
	{
		value = va_arg(args, int);
		_reset_specs(specs, INT);
		res = _myf(&value, INT, specs);
	}
	if (*s == 'u')
	{
		uvalue = va_arg(args, unsigned int);
		_reset_specs(specs, UINT);
		res = _myf(&uvalue, UINT, specs);
	}
	if (*s == 'p')
	{
		ptr = (unsigned long)va_arg(args, void *);
		_reset_specs(specs, PTR);
		res = _myf(&ptr, PTR, specs);
	}
	if (res == NULL)
		res = "(null)";
	ft_putstr(res);
	free(res);
	res = NULL;
}

void	_do_cs_flags(const char *s, va_list args, t_spec *specs)
{
	char	*string;
	char	*res;
	char	c;

	res = NULL;
	if (*s != 'c' && *s != 's')
		return ;
	if (*s == 'c')
	{
		c = (char)va_arg(args, int);
		_reset_specs(specs, CHR);
		res = _myf(&c, CHR, specs);
	}
	if (*s == 's')
	{
		string = va_arg(args, char *);
		_reset_specs(specs, STR);
		res = _myf(string, STR, specs);
	}
	if (res == NULL)
		ft_putstr("(null)");
	else
	{
		ft_putstr(res);
		free(res);
		res = NULL;
	}
}

void	_do_xX_flags(const char *s, va_list args, t_spec *specs)
{
	unsigned int	num;
	char			*res;

	num = 0;
	res = NULL;
	if (*s != 'X' && *s != 'x')
		return ;
	num = va_arg(args, unsigned int);
	_reset_specs(specs, HEX);
	res = _myf(&num, HEX, specs);
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

/* Checks for prefix flags only
 * If char matches in any of set.
 */
int	is_flag(const char *s)
{
	const char	*set = FLAGS;

	if (!*s)
		return (FALSE);
	while (*set)
		if (*s == *set++)
			return (TRUE);
	return (FALSE);
}

static void	_init_specs(t_spec *specs)
{
	specs->minwidth = 0;
	specs->minprec = 0;
	specs->ljustflag = FALSE;
	specs->leadcharflag = FALSE;
	specs->minprecflag = FALSE;
	specs->signflag = FALSE;
	specs->schar = "";
	specs->altflag = FALSE;
	specs->lchar = "";
	specs->pch = ' ';
}

/* Stuff after '.' */
static int	_parse_qty(const char **s, size_t *var, int check, int *flag)
{
	unsigned int	qty;

	qty = 0;
	if (check == TRUE)
	{
		*flag = TRUE; /* blank okay */
		if (*(++(*s)) == '.')
			return (FALSE);
	}
	while (ft_isdigit(**s))
	{
		*flag = TRUE;
		qty = qty * 10 + (**s - '0');
		(*s)++;
	} /* double check the operator prec */
	*var = qty;
	return (TRUE);
}

/* Reads any permutation of flags prior to quantities and flips its switch */
static int	_parse_specs(const char **s, t_spec *specs)
{
	while (is_flag(*s))
	{
		if (**s == '-')
			specs->ljustflag = TRUE;
		if (**s == '+')
			specs->signflag = TRUE;
		if (**s == ' ' && specs->signflag == FALSE)
			/* ' ' or sign when no widths */
			specs->lchar = " ";
		if (**s == '0' && specs->ljustflag == FALSE) /* '0' only w/in prec,
			then minwidth */
			specs->pch = '0';                        /* if prec, ignored */
		if (**s == '#')                              /* repeats okay */
			specs->altflag = TRUE;
		(*s)++;
	}
	if (ft_isdigit(**s))
	{
		_parse_qty(s, &specs->minwidth, FALSE, &specs->minwidthflag);
	}
	if (**s == '.') /* NOK */
	{
		if (_parse_qty(s, &specs->minprec, TRUE, &specs->minprecflag) == FALSE)
		{
			return (FALSE);
		}
		if (specs->minprecflag == TRUE) /* reset pch. lchar can remain " " */
			specs->pch = ' ';
	}
	return (TRUE);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	t_spec		specs;
	const char	*start;

	start = NULL;
	va_start(args, s);
	while (*s)
	{
		if (*s != '%')
			ft_putchar((unsigned int)*s);
		else /* is % */
		{
			_init_specs(&specs);
			s++;
			start = s;
			if (is_flag(s) == TRUE || ft_isdigit(*s) || *s == '.')
			{
				if (_parse_specs(&s, &specs) == FALSE) /* if invalid,
					reset ptr */
				{
					s = start;
					continue ;
				}
			}
			_do_idu_flags(s, args, &specs);
			_do_cs_flags(s, args, &specs);
			_do_xX_flags(s, args, &specs);
			_do_pc(s);
		}
		s++;
	}
	va_end(args);
	return (SUCCESS);
}
