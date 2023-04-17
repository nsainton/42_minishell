/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:53:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 13:34:45 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*getgc(void)
{
	static t_gc	collector;

	//EPRINT
	if (collector.memzones)
		return (&collector);
	if (! TRASH_SIZE)
		return (NULL);
	//ft_dprintf(STDERR_FILENO, "Allocating memzones\n");
	collector.memzones = ft_calloc(TRASH_SIZE, sizeof * collector.memzones);
	if (! collector.memzones)
	{
		ft_bzero(&collector, sizeof collector);
		return (NULL);
	}
	collector.size = TRASH_SIZE;
	collector.len = 0;
	//LPRINT
	return (&collector);
}

int	gc_realloc(void)
{
	t_gc	*collector;
	void	**newzone;
	size_t	newsize;
	size_t	elemsize;

	//EPRINT
	collector = getgc();
	/*
	ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	ft_dprintf(STDERR_FILENO, "This is the size : %u\n", collector->size);
	print_collector();
	*/
	newsize = 2 * collector->size;
	if (newsize < collector->size)
		return (OVERFLOW);
	elemsize = sizeof * collector->memzones;
	/*
	ft_dprintf(STDERR_FILENO, "Elem size is : %u\n", elemsize);
	ft_dprintf(STDERR_FILENO, "True size : %u\n", collector->size * elemsize);
	ft_dprintf(STDERR_FILENO, "True new size : %u\n", newsize * elemsize);
	*/
	newzone = ft_realloc(collector->memzones, \
	collector->size * elemsize, newsize * elemsize);
	if (! newzone)
		return (ALLOCATION_ERROR);
	/*
	ft_dprintf(STDERR_FILENO, "This is the first part of the new collector\n");
	print_collector();
	ft_dprintf(STDERR_FILENO, "This was the first part of the new collector\n");
	*/
	ft_bzero(newzone + collector->size, collector->size * elemsize);
	collector->memzones = newzone;
	collector->size = newsize;
	/*
	ft_dprintf(STDERR_FILENO, "This is the new len : %u\n", collector->len);
	ft_dprintf(STDERR_FILENO, "This is the new size : %u\n", collector->size);
	print_collector();
	LPRINT
	*/
	return (NO_ERROR);
}
