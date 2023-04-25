/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:02:33 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 16:23:27 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	t_str_add(t_str *str, t_cchar c)
{
	if (str->len >= str->size - 1 && t_str_realloc(str))
		return (ALLOCATION_ERROR);
	*(str->str + str->len) = c;
	str->len ++;
	return (NO_ERROR);
}
	
int	t_str_alloc(t_str *str, t_csizet size)
{
	ft_bzero(str, sizeof * str);
	str->str = gccalloc(size + 1, sizeof * str->str);
	if (! str->str)
		return (ALLOCATION_ERROR);
	*str->str = 0;
	str->len = 0;
	str->size = size + 1;
	return (NO_ERROR);
}

int t_str_realloc(t_str *str)
{
	char	*ns;

	if (str->size >= SIZE_MAX / 2)
		return (OVERFLOW);
	ns = gccalloc(2 * str->size - 1, sizeof * ns);
	if (! ns)
		return (ALLOCATION_ERROR);
	*ns = 0;
	ft_memmove(ns, str->str, str->len);
	free_node(str->str);
	str->str = ns;
	str->size = 2 * str->size - 1;
	return (NO_ERROR);
}
