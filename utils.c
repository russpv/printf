#include "ft_printf.h"

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

void	_init_specs(t_spec *specs)
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
	specs->base = 10;
}

void	_printoutput(void *res)
{
	if (!res)
		ft_putstr("(null)");
	else
	{
		ft_putstr(res);
		free(res);
	}
}

char	*_toupper(char *s)
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
