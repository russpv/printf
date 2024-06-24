#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// Temp includes
# include <stdio.h>

# define FLAGS "#-+0 "
# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

typedef enum e_types
{
	INT,
	UINT,
	PTR,
	STR,
	HEX,
	CHR
}						t_types;

typedef struct s_spec
{
	int					ljstflg;
	int					signflg;
	int					leadflg;
	int					mpflg;
	int					mwflg;
	int					altflg;
	unsigned int		base;
	char				*sch;
	char				pch;
	char				*lch;
	char				type;
	size_t				minwidth;
	size_t				minprec;
	size_t				len;
	size_t				padlen;
}						t_spec;
typedef enum e_bool
{
	a,
	b
}						t_bool;
typedef unsigned char	t_uint8_t;
/* 4 bytes */
typedef unsigned int	t_uint32_t;
/* 16 bytes */
typedef struct s_16
{
	t_uint8_t			data[16];
}						t_block_16;
/* 32 bytes */
typedef struct s_32
{
	t_uint8_t			data[32];
}						t_block_32;
typedef struct s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;
/* Must be at least 8-bytes */
typedef unsigned long	long(t_uint64_t);
/* 64-bit ptr */
typedef unsigned long	long(t_uintptr_t);

# define BIGBLOCKSZ 32
/* 16-bytes */
# define BLOCK 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFULL
# define BLOCKSZ 16
/* 8 bytes */
# define SUBBLOCK 0xFFFFFFFFFFFFFFFFUL
# define SUBBLOCKSZ 8
/* 8-byte ptr */
# define PTRSZ 8
# define ULSZ 4

int						ft_printf(const char *s, ...);
char	*type_switch(void *val, t_types typ, t_spec *specs);

/* Flags */
char	*safe_join(const char *s1, const char *s2);
char	*append_char(const char *ch, const char *r);
char	*apply_minprecision_num(const char *r, t_spec *s);
char    *apply_minprecision_char(const char *r, t_spec *s);



/* Utils */
int						is_flag(const char *s);
void					_init_specs(t_spec *specs);
void					_printoutput(void *res);
char					*_toupper(char *s);

/* Format handlers */
void					_do_idu_flags(const char *s, va_list args,
							t_spec *specs);
void					_do_cs_flags(const char *s, va_list args,
							t_spec *specs);
void					_do_xx_flags(const char *s, va_list args,
							t_spec *specs);
void					_do_pc(const char *s);

/* libft */
void					ft_putnbr(long n);
void					ft_putchar(unsigned int c);
void					ft_putstr(char const *s);
size_t					ft_strlen(const char *s);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
t_bool					ft_isdigit(int c);
char					*ft_itoa(long long n);
char					*ft_itoa_base(long long n, unsigned int base);
void					*ft_memset(void *str, int c, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
