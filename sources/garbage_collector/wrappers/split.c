/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:31:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 14:29:40 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**gc_split(t_cchar *s, char c)
{
	char	**ns;
	size_t	index;

	ns = ft_split(s, c);
	if (! (ns && gc_add_array((void **)ns)))
		return (ns);
	index = 0;
	while (*(ns + index))
	{
		free(*(ns + index));
		index ++;
	}
	free(ns);
	return (NULL);
}
