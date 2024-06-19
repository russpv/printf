#ifndef FT_PRINTF_H_
# define FT_PRINTF_H_

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

// Temp includes
#include <stdio.h>

# define FLAGS "#-+0 "
# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

typedef enum {
	INT,
	UINT,
	PTR,
	STR
}	e_types;

typedef struct s_spec {
	int	ljust;
	int	sign;
	char	padchar;
	int	alt;
	char	leadpadchar;
	char	type;
	int	minwidth;
	int	minprec;
}	t_spec;

int	ft_printf(const char *, ...);


#endif
