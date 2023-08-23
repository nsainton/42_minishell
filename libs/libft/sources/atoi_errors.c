/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:20:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/22 17:31:48 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_num_space(t_cchar **s, t_cchar *base, t_uint *abs)
{
	char	*index;
	size_t	len;
	t_uint	max;

	max = (t_uint)INT_MAX + 1;
	*abs = 0;
	len = ft_strlen(base);
	while (**s && **s != ' ')
	{
		index = ft_strchr(base, **s);
		if (! index)
			return (1);
		*abs = *abs * len + index - base;
		if (*abs > max)
			return (1);
		(*s)++;
	}
	return (0);
}

static int	fill_num(t_cchar **s, t_cchar *base, t_uint *abs)
{
	char	*index;
	size_t	len;
	t_uint	max;

	max = (t_uint)INT_MAX + 1;
	*abs = 0;
	len = ft_strlen(base);
	while (**s)
	{
		index = ft_strchr(base, **s);
		if (! index)
			return (1);
		*abs = *abs * len + index - base;
		if (*abs > max)
			return (1);
		(*s)++;
	}
	return (0);
}

int	atoi_errors_space(t_cchar *s, t_cchar *base, int *err)
{
	int		res;
	int		minus;
	t_uint	abs;

	res = 0;
	if (*s == '+' || *s == '-')
	{
		minus = (*s == '+') * 2 - 1;
		s++;
	}
	else
		minus = 1;
	*err = fill_num_space(&s, base, &abs);
	if (*err)
		return (0);
	if (abs == (t_uint)INT_MAX + 1 && minus == 1)
	{
		*err = 1;
		return (0);
	}
	res = (int)(minus * abs);
	return (res);
}

int	atoi_errors(t_cchar *s, t_cchar *base, int *err)
{
	int		res;
	int		minus;
	t_uint	abs;

	res = 0;
	if (*s == '+' || *s == '-')
	{
		minus = (*s == '+') * 2 - 1;
		s++;
	}
	else
		minus = 1;
	*err = fill_num(&s, base, &abs);
	if (*err)
		return (0);
	if (abs == (t_uint)INT_MAX + 1 && minus == 1)
	{
		*err = 1;
		return (0);
	}
	res = (int)(minus * abs);
	return (res);
}
