/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:53:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/12 17:50:49 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*getgc(void)
{
	static t_gc	collector;

	if (collector.memzones)
		return (&collector);
	if (! TRASH_SIZE)
		return (NULL);
	collector.memzones = ft_calloc(TRASH_SIZE, sizeof * collector.memzones);
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
	size_t	elemsize;

	collector = getgc();
	if (! collector)
		return (NO_COLLECTOR);
	newsize = 2 * collector->size;
	if (newsize < collector->size)
		return (OVERFLOW);
	elemsize = sizeof * collector->memzones;
	newzone = ft_realloc(collector->memzones, \
	collector->size * elemsize, newsize * elemsize);
	if (! newzone)
		return (ALLOCATION_ERROR);
	ft_bzero(newzone + collector->size, (newsize - collector->size) * elemsize);
	collector->memzones = newzone;
	collector->size = newsize;
	return (0);
}

int	gc_add(void *ptr)
{
	t_gc	*collector;
	int		error;

	collector = getgc();
	if (! collector)
		return (NO_COLLECTOR);
	error = 0;
	if (collector->len == collector->size)
		error = gc_realloc();
	if (error)
		return (free_gc(error));
	*(collector->memzones + collector->len) = ptr;
	collector->len ++;
	return (0);
}
