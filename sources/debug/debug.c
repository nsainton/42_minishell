/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:42:48 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/20 17:53:07 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_bin(void *elem, t_csizet elemsize)
{
	char	toprint[200];
	size_t	index;
	char	*bin;

	bin = (char *)elem;
	index = 0;
	while (index < elemsize)
	{
		if (*(bin + index) == 0)
			*(toprint + index) = '0';
		else
			*(toprint + index) = '1';
		index ++;
	}
	*(toprint + index) = 0;
	write(1, toprint, ft_strlen(toprint));
}

void	print_tab_bin(t_tab *tab)
{
	size_t	index;

	index = 0;
	while (index < tab->len)
	{
		print_bin(tab->tab + index * tab->elemsize, tab->elemsize);
		//write(1, tab->tab + index * tab->elemsize, tab->elemsize);
		write(1, "\n", 1);
		index ++;
	}
}

