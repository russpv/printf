#include "ft_printf.h"

/* add the sign char or lead char for uihp */
static inline char	*_append_char(const char *ch, const char *res)
{
	char *res2;

	if (!res)
		return (NULL);
	res2 = ft_strjoin(ch, res);
	free(res);
	res = NULL;
	if (!res2)
		return (NULL);
	return (res2);
}

/* Returns NULL if args are NULL, else returns ptr to new string */
static inline char	*_safe_join(const char *s1, const char *s2)
{
	char *tmp;
	
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		free (s2);
		return (NULL);
	}
	else if (s1 && !s2)
	{
		free (s1);
		return (NULL);
	}
	tmp = ft_strjoin(s1, s2);
	free (s2);
	free (s1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

/* Should work for STR/CHR/UIHP */
char	*_apply_minprecision(const char *s, t_spec *specs)
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
		return (res2);
	}
}
/* Applies flags for STR and CHR
 * String:
 * - NULL is "(null)" unless minprec truncates, any minwidth prints "(null)" TODO: doublecheck
 *
 * Char:
 * - '\0' counts as 1 len for padding flags
*/ 
char	*_do_flags_cs(char *res, t_spec *s)
{
	if (!res && (s->minprecflg == TRUE && s->minprec < 6)) // print "" if small minprec  TODO:check redudnant
		res = ft_substr("", 0, 0);
	else if (!res && (s->minwidthflg || (s->minprecflg == TRUE
				&& s->minprec >= 6))) //TODO why is this redundant, double check
		res = ft_substr("(null)", 0, 6); // print "(null)" if enuf minprec + any minw
	else if (res) // create new string for char
		res = ft_substr((char *)val, 0, ft_strlen((char *)val));
	if (!res)
		return (NULL);
	s->len = ft_strlen(res); //TODO check if rest here is redudnant
	if (typ == CHR && s->len == 0) // null char counts as 1 for mw/mp
		s->len = 1;
	if (s->minprecflg && s->minprec < s->len)
	{
		tmp = ft_substr(res, 0, s->minprec);
		s->len = ft_strlen(tmp);
		free(res);
		res = tmp;
	}
	if (s->minwidthflg && s->minwidth > s->len)
	{
		tmp = _repeat(s->minwidth - s->len, s->pch);
		if (s->ljstflg == TRUE)
			res2 = ft_strjoin(res, tmp);
		else
			res2 = ft_strjoin(tmp, res);
		free(tmp);
		free(res);
		res = res2;
	}
	return (res);
}

/* Apply flags for UINT/INT/HEX/PTR */
char	*_do_flags_UIHP(char *r, t_spec *s)
{
	char *tmp;
	
	if (s->mpflg) // apply minprecision
		r = _apply_minprecision(r, s);
	if (!res)
		return (NULL);
	s->len = ft_strlen(r) + s->leadflg * ft_strlen(s->lch) + s->signflg * ft_strlen(s->sch);
	if (s->signflg && (s->minprec || s->pch != '0')) // apply sign before minwidth
	{
		s->signflg = FALSE;
		r = _append_char(s->sch, r);
	}
	if (s->minwidth > s->len) // apply minwidth
	{
		s->padlen = s->minwidth - s->len;
		tmp = _repeat(s->padlen, s->pch);
		if (s->ljstflg == TRUE)
			r = _safe_join(r, tmp);
		else
			r = _safe_join(tmp, r);
	}
	if (s->leadflg) // apply lead
		r = _append_char(s->lch, r);
	if (s->signflg && !s->minprec) // apply signchar post-
		r = _append_char(s->sch, r);
	if (!r)
		return (NULL);
	return (r);
}

/* Adds default hex prefix or returns "(nil)" for PTR */
char	*_apply_0x_nil(char *res)
{
	res = _safe_join(ft_strjoin("0x", ""), res);
	if (ft_strncmp(res, "0x0", ft_strlen(res)) == 0)  //TODO check strncmp is safe
	{
		free(res);
		res = ft_strjoin("(nil)", "");
	}
	if (!res)
		return (NULL);
	return (res);
}

/*
 *
 * PTR
 * - Default print in HEX with '0x' prefix
 * - Prints "(nil)" for 0x0 NULL
 */ 
char	*_myf(void *val, t_types typ, t_spec *specs)
{
	char		*res;
	long long	value;

	value = 0;
	if (typ == STR || typ == CHR)
		res = (char *)val;
	if (typ == STR || typ == CHR)
		res = _do_flags_cs(res, specs);
	if (typ == INT)
		value = *(int *)val;
	if (typ == HEX || type == UINT || typ == PTR)
		value = *(unsigned long *)val;
	if (value < 0)
	{
		specs->sch = "-";
		specs->signflg = TRUE;
		value *= -1;
	}
	if (typ == HEX || type == UINT || typ == PTR || typ == INT)
		res = ft_itoa_base(value, specs->base);
	if (typ == PTR)
		res = _apply_0x_nil(res);
	if (typ == HEX || type == UINT || typ == PTR || typ == INT)
		res = _do_flags_UIHP(res, specs);
	if (!res)
		return (NULL);
	return (res);
}
