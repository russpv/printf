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

/* init all but lengths */
void	init_specs(t_spec *specs)
{
	specs->initflg = TRUE;
	specs->ljstflg = FALSE;
	specs->signflg = FALSE;
	specs->leadflg = FALSE;
	specs->mpflg = FALSE;
	specs->mwflg = FALSE;
	specs->altflg = FALSE;
	specs->minwidth = 0;
	specs->minprec = 0;
	specs->base = 10;
	specs->type = '0';
	specs->lch = "";
	specs->sch = "";
	specs->pch = ' ';
}

/* Prints heap string to screen */
void	print_output(void *res, t_spec *s)
{
	if (!res)
		ft_putstr("(null)");
	else
	{
		ft_putstr(res);
		free(res);
	}
	s->initflg = FALSE;
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
