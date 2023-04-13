/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:21 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/13 18:38:55 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_gc(t_cint errcode)
{
	t_gc	*collector;
	size_t	index;

	ft_dprintf(STDERR_FILENO, "In function : %s\n", __func__);
	collector = getgc();
	if (! collector)
		return (errcode);
	index = 0;
	ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	while (index < collector->len)
	{
		ft_dprintf(STDERR_FILENO, "This is the index : %u\n", index);
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
	void	**newzone;

	ft_dprintf(STDERR_FILENO, "In function : %s\n", __func__);
	collector = getgc();
	if (! collector)
		return (NO_COLLECTOR);
	if (collector->len <= number)
		return (free_gc(errcode));
	ft_dprintf(STDERR_FILENO, "This is the len : %u\n", collector->len);
	newsize = collector->len - number;
	ft_dprintf(STDERR_FILENO, "This is the new len : %u\n", newsize);
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
