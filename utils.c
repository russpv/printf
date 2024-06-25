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

void	init_specs(t_spec *specs)
{
	specs->minwidth = 0;
	specs->minprec = 0;
	specs->ljstflg = FALSE;
	specs->leadflg = FALSE;
	specs->mpflg = FALSE;
	specs->signflg = FALSE;
	specs->sch = "";
	specs->altflg = FALSE;
	specs->lch = "";
	specs->pch = ' ';
	specs->base = 10;
}

/* Prints heap string to screen */
void	print_output(void *res)
{
	if (!res)
		ft_putstr("(null)");
	else
	{
		ft_putstr(res);
		free(res);
	}
}

char	*to_upper(char *s)
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
