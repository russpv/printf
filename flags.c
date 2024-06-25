#include "ft_printf.h"

/* Applies flags for STR and CHR
 * String:
 * - NULL is "(null)" unless minprec truncates,
	any minwidth prints "(null)" TODO: doublecheck
 * Char:
 * - '\0' counts as 1 len for padding flags
 * r: stack string
 * s: struct
 * typ: specifier
 * val: va_arg
 */
static inline char	*_do_flags_CS(char *r, t_spec *s, t_types typ, void *val)
{
	if (!r && (s->mpflg == TRUE && s->minprec < 6)) // print "" if small minprec  TODO:check redudnant
		r = ft_substr("", 0, 0);
	else if (!r && (s->mwflg || (s->mpflg == TRUE && s->minprec >= 6))) // TODO why is this redundant, double check
		r = ft_substr("(null)", 0, 6); // print "(null)" if enuf minprec + any minw
	else if (r) // create new string for char
		r = ft_substr((char *)val, 0, ft_strlen((char *)val));
	if (!r)
		return (NULL);
	s->len = ft_strlen(r);         // TODO check if rest here is redudnant
	if (typ == CHR && s->len == 0) // null char counts as 1 for mw/mp
		s->len = 1;
	if (s->mpflg && s->minprec < s->len)
		r = apply_minprecision_char(r, s);
	if (s->mwflg && s->minwidth > s->len)
		r = apply_minwidth(r, s);
	if (!r)
		return (NULL);
	return (r);
}

/* Apply flags for UINT/INT/HEX/PTR */
static inline char	*_do_flags_HIPU(char *r, t_spec *s)
{
	if (s->mpflg) // apply minprecision
		r = apply_minprecision_num(r, s);
	if (!r)
		return (NULL);
	s->len = ft_strlen(r) + s->leadflg * ft_strlen(s->lch) + s->signflg
		* ft_strlen(s->sch);
	if (s->signflg && (s->minprec || s->pch != '0')) // apply sign before minwidth
	{
		s->signflg = FALSE;
		r = append_char(s->sch, r);
	}
	if (s->minwidth > s->len)
		r = apply_minwidth(r, s);
	if (s->leadflg) // apply lead
		r = append_char(s->lch, r);
	if (s->signflg && !s->minprec) // apply signchar post-
		r = append_char(s->sch, r);
	if (!r)
		return (NULL);
	return (r);
}

/* Adds default hex prefix or returns heap "(nil)" for PTR 
** r: must be heap string
*/
static inline char	*_apply_0x_nil(char *r)
{
	r = safe_join(ft_strjoin("0x", ""), r);
	if (ft_strncmp(r, "0x0", ft_strlen(r)) == 0) // TODO check strncmp is safe
	{
		free(r); // valid free()
		r = ft_strjoin("(nil)", "");
	}
	if (!r)
		return (NULL);
	return (r);
}

/* Sets negative sign char and flag for printing INT */
static inline void	_handle_neg(unsigned long long *value, void *val, t_spec *s)
{
	long long num;
	
	num = *(long long *)val;
	if (num < 0)
	{
		s->sch = "-";
		s->signflg = TRUE;
		*value = (unsigned long long)(-num);
	}
	else
		*value = *(unsigned long long *)val;
}

/* Switchboard for handling flags by arg specifier 
** Returns heap string
** HEX, PTR, UINT are positive-only 
** 
*/
char	*type_switch(void *val, t_types typ, t_spec *specs)
{
	char				*res;
	unsigned long long	value;		

	value = 0;
	if (typ == CHR || typ == STR)
		res = (char *)val;
	if (typ == CHR || typ == STR)
		res = _do_flags_CS(res, specs, typ, val);
	if (typ == INT)
	{	
		_handle_neg(&value, val, specs);
		printf("sw: val (%llu) (%lld)\n", value, *(long long*)val);
	}
	if (typ == HEX || typ == PTR || typ == UINT)
		value = *(unsigned long long *)val;	
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
