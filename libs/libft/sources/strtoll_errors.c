/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoll_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:24:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 10:51:23 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_ll	fill_num(t_cchar **s, t_cchar *base, t_ull *abs)
{
	char	*index;
	size_t	len;
	t_ull	max;

	max = (t_ull)LLONG_MAX + 1;
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

t_ll	strtoll_errors(t_cchar *s, t_cchar *base, int *err)
{
	t_ll	res;
	int		minus;
	t_ull	abs;

	res = 0;
	if (*s == '+' || *s == '-')
	{
		minus = (*s == '+') * 2 - 1;
		s ++;
	}
	else
		minus = 1;
	*err = fill_num(&s, base, &abs);
	if (*err)
		return (0);
	if (abs == (t_ull)LLONG_MAX + 1 && minus == 1)
	{
		*err = 1;
		return (0);
	}
	res = (t_ll)(minus * abs);
	return (res);
}
