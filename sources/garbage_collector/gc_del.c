/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/13 11:45:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_gc(t_cint errcode)
{
	t_gc	*collector;
	size_t	index;

	collector = getgc();
	if (! collector)
		return (errcode);
	index = 0;
	while (index < collector->len)
	{
		free(*(collector->memzones + index));
		index ++;
	}
	free(collector->memzones);
	ft_bzero(collector, sizeof * collector);
	return (errcode);
}

int	free_nodes(t_csizet number, t_cint errcode)
{
	t_gc	*collector;
	size_t	index;
	size_t	newsize;
	void	*newzone;

	collector = getgc();
	if (! collector)
		return (NO_COLLECTOR);
	if (collector->len <= number)
		return (free_gc(errcode));
	newsize = collector->len - number;
	newzone = collector->memzones + newsize;
	index = 0;
	while (index < number)
	{
		free(*(newzone + index));
		*(newzone + index) = NULL;
		index ++;
	}
	collector->len = newsize;
	return (errcode);
}
