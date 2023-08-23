/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:17 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 11:15:09 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INT_H
# define LIBFT_INT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <sys/types.h>
# include "ansicolorcodes.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# ifdef FILES
#  undef FILES
# endif
# define FILES 123
# ifdef PBUFFER_SIZE
#  undef PBUFFER_SIZE
# endif
# define PBUFFER_SIZE 1000
# define DEC "0123456789"
# define HEX "0123456789abcdef"
# define HEX_MAJ "0123456789ABCDEF"
# define FLAGS "# +-0"
# define SPECIFIERS "cspdiuxX%"
# define P_CONV "cspdiuxX"
# define ADMITTED "c;s;p;d;i;u;x;X;%;"
# define SEPARATOR ";"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				priority;
}				t_list;

typedef struct s_pbuffer
{
	char			buffer[PBUFFER_SIZE];
	int				len;
	int				width;
	int				prec;
	intptr_t		fd;
	int				printed;
	unsigned char	str:1;
}				t_pbuffer;

typedef struct s_print
{
	char	modifier[3];
	char	beg;
	char	pad;
	char	align;
}				t_print;

typedef struct s_gline
{
	char	*line;
	size_t	line_index;
}				t_gline;

typedef struct s_str
{
	char	*str;
	size_t	len;
	size_t	size;
}				t_str;

typedef struct s_cstr
{
	const char	*str;
	size_t		index;
}				t_cstr;

typedef enum e_pflags
{
	SHARP = 1 << 0,
	SPACE = 1 << 1,
	PLUS = 1 << 2,
	DASH = 1 << 3,
	ZERO = 1 << 4,
	DOT = 1 << 5
}				t_pflags;

/*
Think about using the enum in ft_printf
instead of the array of chars
*/

typedef long long int			t_ll;

typedef t_ll					t_llong;

typedef unsigned long long int	t_ull;

typedef t_ull					t_ullong;

typedef signed long long int	t_sllong;

typedef t_sllong				t_sll;

typedef unsigned char			t_uchar;

typedef const t_uchar			t_cuchar;

typedef signed char				t_schar;

typedef const signed char		t_cschar;

typedef signed int				t_sint;

typedef unsigned int			t_uint;

typedef const int				t_cint;

typedef const char				t_cchar;

typedef const size_t			t_csizet;

typedef const t_ll				t_cllong;

typedef const void				t_cvoid;

typedef void					(*t_pfunc)(t_pbuffer *, va_list *, char[128]);

typedef int						(*t_colorfunc)(t_cvoid *, t_cchar *, t_cint);

typedef void					(*t_delfunc)(void *);

typedef t_list					t_alloc;

typedef const t_list			t_clist;

#endif
