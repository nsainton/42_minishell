/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 13:51:25 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_gc(t_cint errcode)
{
	t_gc	*collector;
	size_t	index;

	//EPRINT
	collector = getgc();
	if (! collector)
		return (errcode);
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
	return (errcode);
}

int	free_nodes(t_csizet number, t_cint errcode)
{
	t_gc	*collector;
	size_t	index;
	size_t	newsize;
	void	**newzone;

	//EPRINT
	collector = getgc();
	if (! collector)
		return (errcode);
	if (collector->len <= number)
		return (free_gc(errcode));
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
	return (errcode);
}

int	free_node(void *node, t_cint errcode)
{
	t_gc	*collector;
	size_t	index;

	collector = getgc();
	if (! collector)
		return (NO_COLLECTOR);
	index = 0;
	if (! collector->len)
		return (free_gc(errcode));
	while (index < collector->len)
	{
		if (*(collector->memzones + index) == node)
			break ;
		index ++;
	}
	if (index == collector->len)
		return (NOT_IN_COLLECTOR);
	*(collector->memzones + index) = *(collector->memzones \
	+ collector->len - 1);
	*(collector->memzones + collector->len - 1) = NULL;
	collector->len --;
	free(node);
	return (errcode);
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
