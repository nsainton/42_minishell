/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 11:16:17 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

void	free_gc(void)
{
	t_gc	*collector;
	size_t	index;

	collector = getgc();
	if (! collector)
		return ;
	index = 0;
	while (index < collector->len)
	{
		free(*(collector->memzones + index));
		index ++;
	}
	free(collector->memzones);
	ft_bzero(collector, sizeof * collector);
}

void	free_from(void *node)
{
	size_t	index;
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return ;
	index = get_index(node);
	if (index >= collector->len)
		return ;
	free_nodes(collector->len - 1 - index);
}

void	free_nodes(t_csizet number)
{
	t_gc	*collector;
	size_t	index;
	size_t	newsize;
	void	**newzone;

	collector = getgc();
	if (! collector)
		return ;
	if (collector->len <= number)
	{
		return (free_gc());
	}
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
}

void	free_node(void *node)
{
	t_gc	*collector;
	size_t	index;

	collector = getgc();
	if (! collector)
		return ;
	index = 0;
	if (! collector->len)
		return (free_gc());
	while (index < collector->len)
	{
		if (*(collector->memzones + index) == node)
			break ;
		index ++;
	}
	if (index == collector->len)
		return ;
	*(collector->memzones + index) = *(collector->memzones \
	+ collector->len - 1);
	*(collector->memzones + collector->len - 1) = NULL;
	collector->len --;
	free(node);
}

void	remove_nodes(size_t number)
{
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return ;
	if (number > collector->len)
		number = collector->len;
	collector->len -= number;
	ft_bzero(collector->memzones + collector->len, number \
	* sizeof * collector->memzones);
}
