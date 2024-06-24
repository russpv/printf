#include "ft_printf.h"

/* PRINTF
 * cspdiuxX% flags handled
 */


/* Creates padding strings */
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

/* Adjusts string for flag input */
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
		if (value < 0)
		{
			specs->schar = "-";
			specs->signflag = TRUE;
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
	if (typ == UINT)
	{
		value = *(unsigned int *)val;
		res = ft_itoa(value);
		if (!res)
			return (NULL);
	}
	if (typ == PTR)
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
		{
			tmp = ft_substr(res, 0, specs->minprec);
			specs->len = ft_strlen(tmp);
			free(res);
			res = tmp;
		}
		if (specs->minwidthflag && specs->minwidth > specs->len)
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
	{
		if (specs->minprecflag)
		{
			if (specs->minprec == 0 && (ft_strncmp(res, "0", 1) == 0))
				res = ft_strjoin("", "");
			if (ft_strlen(res) < specs->minprec)
			{
				tmp = _repeat(specs->minprec - ft_strlen(res), '0');
				if (!tmp)
					return (NULL);
				res2 = ft_strjoin(tmp, res);
				if (!res2)
					return (NULL);
				free(res);
				free(tmp);
				tmp = NULL;
				res = res2;
			}
		}
		specs->len = ft_strlen(res) + specs->leadcharflag
			* ft_strlen(specs->lchar) + specs->signflag
			* ft_strlen(specs->schar);
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
		if (specs->minwidth > specs->len)
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
			res2 = ft_strjoin(specs->lchar, res);
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

/* Stuff after '.' */
static int	_parse_qty(const char **s, size_t *var, int check, int *flag)
{
	unsigned int	qty;

	qty = 0;
	if (check == TRUE)
	{
		*flag = TRUE;
		if (*(++(*s)) == '.')
			return (FALSE);
	}
	while (ft_isdigit(**s))
	{
		*flag = TRUE;
		qty = qty * 10 + (**s - '0');
		(*s)++;
	}
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
			specs->lchar = " ";
		if (**s == '0' && specs->ljustflag == FALSE)
			specs->pch = '0';
		if (**s == '#')
			specs->altflag = TRUE;
		(*s)++;
	}
	if (ft_isdigit(**s))
	{
		_parse_qty(s, &specs->minwidth, FALSE, &specs->minwidthflag);
	}
	if (**s == '.')
	{
		if (_parse_qty(s, &specs->minprec, TRUE, &specs->minprecflag) == FALSE)
		{
			return (FALSE);
		}
		if (specs->minprecflag == TRUE)
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
		else
		{
			_init_specs(&specs);
			s++;
			start = s;
			if (is_flag(s) == TRUE || ft_isdigit(*s) || *s == '.')
			{
				if (_parse_specs(&s, &specs) == FALSE)
				{
					s = start;
					continue ;
				}
			}
			_do_idu_flags(s, args, &specs);
			_do_cs_flags(s, args, &specs);
			_do_xx_flags(s, args, &specs);
			_do_pc(s);
		}
		s++;
	}
	va_end(args);
	return (SUCCESS);
}
