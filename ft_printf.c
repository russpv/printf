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

/* Flag determines either normal numbers or precision after '.' */
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

/* Reads any permutation of flags and quantities */
static int	_parse_specs(const char **s, t_spec *specs)
{
	while (is_flag(*s))
	{
		if (**s == '-')
			specs->ljstflg = TRUE;
		if (**s == '+')
			specs->signflg = TRUE;
		if (**s == ' ' && specs->signflg == FALSE)
			specs->lch = " ";
		if (**s == '0' && specs->ljstflg == FALSE)
			specs->pch = '0';
		if (**s == '#')
			specs->altflg = TRUE;
		(*s)++;
	}
	if (ft_isdigit(**s))
		_parse_qty(s, &specs->minwidth, FALSE, &specs->mwflg);
	if (**s == '.')
	{
		if (_parse_qty(s, &specs->minprec, TRUE, &specs->mpflg) == FALSE)
			return (FALSE);
		if (specs->mpflg == TRUE)
			specs->pch = ' ';
	}
	return (TRUE);
}

static void	_do_flags(const char *s, va_list args, t_spec *specs)
{
	_do_idu_flags(s, args, specs);
	_do_cs_flags(s, args, specs);
	_do_xx_flags(s, args, specs);
	_do_pc(s);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	t_spec		specs;
	const char	*start = s;

	va_start(args, s);
	while (*s)
	{
		if (*s != '%')
			ft_putchar((unsigned int)*s); // TODO: add '++'
		else
		{
			_init_specs(&specs);
			s++;
			if (is_flag(s) == TRUE || ft_isdigit(*s) || *s == '.')
			{
				if (_parse_specs(&s, &specs) == FALSE) // Invalid input, abort
				{
					s = start; // TODO: add '++' 
					continue ;
				}
			}
			_do_flags(s, args, &specs);
		}
		s++; // TODO: remove
	}
	va_end(args);
	return (SUCCESS);
}
