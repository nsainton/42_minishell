/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:17:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 14:28:25 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	gc_len(void)
{
	t_gc	*collector;

	//EPRINT
	collector = getgc();
	if (! collector)
		return (0);
	//LPRINT
	return (collector->len);
}

void	print_collector(void)
{
	t_gc	*collector;
	size_t	index;
	size_t	size;

	//EPRINT
	collector = getgc();
	if (! collector)
		return ;
	index = 0;
	size = collector->size;
	ft_dprintf(STDERR_FILENO, "Printing collector\n");
	while (index < size)
	{
		ft_dprintf(STDERR_FILENO, "This is the pointer #%u : %p\n", \
		index, *(collector->memzones + index));
		index ++;
	}
	ft_dprintf(STDERR_FILENO, "Collector Printed\n");
	//LPRINT
}

void	*wrap_pointer(void *ptr)
{
	if (! (ptr && gc_add(ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}
