#include "ft_printf.h"

/* Returns NULL if args are NULL, else returns ptr to new string */
char	*safe_join(const char *s1, const char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		free(s2);
		return (NULL);
	}
	else if (s1 && !s2)
	{
		free(s1);
		return (NULL);
	}
	res = ft_strjoin(s1, s2);
	free(s2);
	free(s1);
	if (!res)
		return (NULL);
	return (res);
}

/* add the sign char or lead char for HIPU */
char	*append_char(const char *ch, const char *r)
{
	char	*res2;

	res2 = safe_join(ch, r);
	if (!res2)
		return (NULL);
	return (res2);
}

/* Applies minimum precision to numerics
 * Truncates 0
 * Adds prepadding with '0'
 */
char	*apply_minprecision_num(const char *r, t_spec *s)
{
	char	*res2;
	char	*tmp;

	if (s->minprec == 0 && (ft_strncmp(r, "0", 1) == 0)) // 0 has no minprec
		r = ft_strjoin("", "");
	if (ft_strlen(r) < s->minprec)
	// '0' padding TODO: empty string with padding?
	{
		tmp = _repeat(s->minprec - ft_strlen(r), '0');
		res2 = safe_join(tmp, r);
		if (!res2)
			return (NULL);
		return (res2);
	}
}

/* Applies minimum precision to strings by truncation */
char	*apply_minprecision_char(const char *r, t_spec *s)
{
	char	*res2;

	res2 = ft_substr(r, 0, s->minprec);
	free(r);
	if (!res2)
		return (NULL);
	s->len = ft_strlen(res2);
	return (res2);
}

/* Applies minimum width pre or post padding */
char	*apply_minwidth(const char *r, t_spec *s)
{
	char	*tmp;

	s->padlen = s->minwidth - s->len;
	tmp = _repeat(s->padlen, s->pch);
	if (s->ljstflg == TRUE)
		r = safe_join(r, tmp);
	else
		r = safe_join(tmp, r);
	free(tmp);
	if (!r)
		return (NULL);
	return (r);
}
