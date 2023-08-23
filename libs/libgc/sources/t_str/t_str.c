/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:02:33 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 15:00:24 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

int	t_str_add(t_str *str, t_cchar c)
{
	int	error;

	if (str->len >= str->size - 1)
	{
		error = t_str_realloc(str);
		if (error)
			return (error);
	}
	*(str->str + str->len) = c;
	str->len ++;
	return (COLLECTOR_NO_ERROR);
}

int	t_str_add_str(t_str *str, t_cchar *toadd)
{
	size_t	available;
	size_t	len_to_add;
	int		error;

	available = str->size - 1 - str->len;
	len_to_add = ft_strlen(toadd);
	while (available < len_to_add)
	{
		error = t_str_realloc(str);
		if (error)
			return (error);
		available = str->size - 1 - str->len;
	}
	ft_strncat(str->str, toadd, len_to_add);
	str->len += len_to_add;
	return (COLLECTOR_NO_ERROR);
}

int	t_str_alloc(t_str *str, t_csizet size)
{
	ft_bzero(str, sizeof * str);
	str->str = gccalloc(size + 1, sizeof * str->str);
	if (! str->str)
		return (COLLECTOR_ALLOCATION_ERROR);
	*str->str = 0;
	str->len = 0;
	str->size = size + 1;
	return (COLLECTOR_NO_ERROR);
}

int	t_str_realloc(t_str *str)
{
	char	*ns;

	if (str->size >= SIZE_MAX / 2)
		return (COLLECTOR_OVERFLOW);
	ns = gccalloc(2 * str->size - 1, sizeof * ns);
	if (! ns)
		return (COLLECTOR_ALLOCATION_ERROR);
	*ns = 0;
	ft_memmove(ns, str->str, str->len);
	free_node(str->str);
	str->str = ns;
	str->size = 2 * str->size - 1;
	return (COLLECTOR_NO_ERROR);
}
