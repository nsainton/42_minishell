/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:53:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/12 12:41:29 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*getgc(void)
{
	static t_gc	collector;

	if (collector.memzones)
		return (&collector);
	collector.memzones = malloc(sizeof * collector.memzones * TRASH_SIZE);
	if (! collector.memzones)
	{
		ft_bzero(&collector, sizeof collector);
		return (NULL);
	}
	collector.size = TRASH_SIZE;
	collector.len = 0;
	return (&collector);
}

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

int	gc_realloc(void)
{
	t_gc	*collector;
	void	*newzone;
	size_t	newsize;

	collector = getgc();
	if (! collector)
		return (ALLOCATION_ERROR);
	newzone = ft_realloc(new
}
int	gc_add(void *ptr)
{
	t_gc	*gc
}
