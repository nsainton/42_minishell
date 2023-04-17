/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:33:59 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 14:26:48 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gc_add(void *ptr)
{
	t_gc	*collector;
	int		error;

	//EPRINT
	collector = getgc();
	error = 0;
	/*
	ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	ft_dprintf(STDERR_FILENO, "This is the size : %u\n", collector->size);
	*/
	if (collector->len == collector->size)
		error = gc_realloc();
	if (error)
		return (error);
	*(collector->memzones + collector->len) = ptr;
	collector->len ++;
	/*
	ft_dprintf(STDERR_FILENO, "This is the new len : %u\n", collector->len);
	ft_dprintf(STDERR_FILENO, "This is the new size : %u\n", collector->size);
	LPRINT
	*/
	return (NO_ERROR);
}

int	gc_replace(void *old_ptr, void *new_ptr)
{
	t_gc	*collector;
	size_t	index;

	collector = getgc();
	index = 0;
	while (index < collector->len)
	{
		if (*(collector->memzones + index) == old_ptr)
		{
			*(collector->memzones + index) = new_ptr;
			break ;
		}
		index ++;
	}
	if (index == collector->len)
		return (NOT_IN_COLLECTOR);
	return (NO_ERROR);
}

int	gc_add_array(void **array)
{
	size_t	index;

	if (gc_add(array))
		return (ADD_ERROR);
	index = 0;
	while (*(array + index))
	{
		if (gc_add(*(array + index)))
		{
			remove_nodes(index + 1);
			return (ADD_ERROR);
		}
		index ++;
	}
	return (NO_ERROR);
}
