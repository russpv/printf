#include "ft_printf.h"

/* Applies minimum width pre or post padding */
char    *_apply_minwidth(const char *r, t_spec *s)
{
  char *tmp;

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

/* Applies flags for STR and CHR
 * String:
 * - NULL is "(null)" unless minprec truncates, any minwidth prints "(null)" TODO: doublecheck
 * Char:
 * - '\0' counts as 1 len for padding flags
*/ 
static inline char	*_do_flags_CS(char *r, t_spec *s, t_types typ, void *val)
{
	if (!r && (s->mpflg == TRUE && s->minprec < 6)) // print "" if small minprec  TODO:check redudnant
		r = ft_substr("", 0, 0);
	else if (!r && (s->mwflg || (s->mpflg == TRUE
				&& s->minprec >= 6))) //TODO why is this redundant, double check
		r = ft_substr("(null)", 0, 6); // print "(null)" if enuf minprec + any minw
	else if (r) // create new string for char
		r = ft_substr((char *)val, 0, ft_strlen((char *)val));
	if (!r)
		return (NULL);
	s->len = ft_strlen(r); //TODO check if rest here is redudnant
	if (typ == CHR && s->len == 0) // null char counts as 1 for mw/mp
		s->len = 1;
    if (s->mpflg && s->minprec < s->len)
	    r = _apply_minprecision_char(r, s);
	if (s->mwflg && s->minwidth > s->len)
	    r = _apply_minwidth(r, s);
    if (!r)
        return (NULL);
	return (r);
}

/* Apply flags for UINT/INT/HEX/PTR */
static inline char	*_do_flags_HIPU(char *r, t_spec *s)
{
	char *tmp;
	
	if (s->mpflg) // apply minprecision
		r = _apply_minprecision_num(r, s);
	if (!r)
		return (NULL);
	s->len = ft_strlen(r) + s->leadflg * ft_strlen(s->lch) + s->signflg * ft_strlen(s->sch);
	if (s->signflg && (s->minprec || s->pch != '0')) // apply sign before minwidth
	{
		s->signflg = FALSE;
		r = _append_char(s->sch, r);
	}
	if (s->minwidth > s->len)
        r = _apply_minwidth(r, s);
	if (s->leadflg) // apply lead
		r = _append_char(s->lch, r);
	if (s->signflg && !s->minprec) // apply signchar post-
		r = _append_char(s->sch, r);
	if (!r)
		return (NULL);
	return (r);
}

/* Adds default hex prefix or returns "(nil)" for PTR */
static inline char	*_apply_0x_nil(char *r)
{
	r = safe_join(ft_strjoin("0x", ""), r);
	if (ft_strncmp(r, "0x0", ft_strlen(r)) == 0)  //TODO check strncmp is safe
	{
		free(r);
		r = ft_strjoin("(nil)", "");
	}
	if (!r)
		return (NULL);
	return (r);
}

/* Switchboard for handling flags by arg specifier */
char	*type_switch(void *val, t_types typ, t_spec *specs)
{
	char		*res;
	long long	value;

	value = 0;
	if (typ == CHR || typ == STR)
		res = (char *)val;
	if (typ == CHR || typ == STR)
		res = _do_flags_CS(res, specs, typ, val);
	if (typ == INT)
		value = *(int *)val;
	if (typ == HEX || typ == PTR || typ == UINT)
		value = *(unsigned long *)val;
	if (value < 0)
	{
		specs->sch = "-";
		specs->signflg = TRUE;
		value *= -1;
	}
	if (typ == HEX || typ == INT || typ == PTR || typ == UINT)
		res = ft_itoa_base(value, specs->base);
	if (typ == PTR)
		res = _apply_0x_nil(res);
	if (typ == HEX || typ == INT || typ == PTR || typ == UINT)
		res = _do_flags_HIPU(res, specs);
	if (!res)
		return (NULL);
	return (res);
}
