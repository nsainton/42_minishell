/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/18 18:18:42 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_gc(void)
{
	t_gc	*collector;
	size_t	index;

	//EPRINT
	collector = getgc();
	if (! collector)
		return ;
	index = 0;
	//ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	while (index < collector->len)
	{
		//ft_dprintf(STDERR_FILENO, "This is the index : %u\n", index);
		if (*(collector->memzones + index))
			free(*(collector->memzones + index));
		index ++;
	}
	free(collector->memzones);
	ft_bzero(collector, sizeof * collector);
	//LPRINT
}

void	free_nodes(t_csizet number)
{
	t_gc	*collector;
	size_t	index;
	size_t	newsize;
	void	**newzone;

	//EPRINT
	collector = getgc();
	if (! collector)
		return ;
	if (collector->len <= number)
	{
		return (free_gc());
	}
	//ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	newsize = collector->len - number;
	//ft_dprintf(STDERR_FILENO, "This is the new len : %u\n", newsize);
	newzone = collector->memzones + newsize;
	index = 0;
	while (index < number)
	{
		free(*(newzone + index));
		*(newzone + index) = NULL;
		index ++;
	}
	collector->len = newsize;
	//LPRINT
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

	//EPRINT
	collector = getgc();
	if (! collector)
		return ;
	//print_collector();
	if (number > collector->len)
		number = collector->len;
	collector->len -= number;
	ft_bzero(collector->memzones + collector->len, number \
	* sizeof * collector->memzones);
	//print_collector();
	//LPRINT
}
