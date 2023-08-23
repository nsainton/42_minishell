/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_wrappers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:51:12 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 10:34:47 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delone_tab(struct s_tab *tab, const size_t index, \
void (*del)(void *))
{
	void	*zones;

	zones = tab->tab;
	if (del)
		del(zones + index * tab->elemsize);
	ft_memmove(zones + index * tab->elemsize, zones + (index + 1) * \
	tab->elemsize, (tab->len - index) * tab->elemsize);
	tab->len --;
}

void	del_tab_elem(struct s_tab *tab, const void *elem, int (*cmp)(), \
void (*del)(void *))
{
	size_t	i;

	i = 0;
	while (i < tab->len)
	{
		if (! cmp(tab->tab + i * tab->elemsize, elem))
			return (delone_tab(tab, i, del));
		i ++;
	}
}

void	replace_tab_elem(struct s_tab *tab, void *elem, const size_t index, \
void (*del)(void *))
{
	void	*zones;

	if (index >= tab->len)
		return ;
	zones = tab->tab;
	if (del)
		del(zones + index * tab->elemsize);
	ft_memcpy(zones + index * tab->elemsize, elem, tab->elemsize);
}

size_t	get_elem_index(struct s_tab *tab, const void *elem, int (*cmp)())
{
	void	*zones;
	size_t	index;

	zones = tab->tab;
	index = 0;
	while (index < tab->len)
	{
		if (! cmp(zones + index * tab->elemsize, elem))
			return (index);
		index ++;
	}
	return (index);
}

int	copy_tab(struct s_tab *newtab, const struct s_tab *oldtab)
{
	void	*newzones;

	ft_memcpy(newtab, oldtab, sizeof * newtab);
	newzones = gccalloc(oldtab->size, oldtab->elemsize);
	if (! newzones)
		return (1);
	ft_memcpy(newzones, oldtab->tab, oldtab->len * oldtab->elemsize);
	newtab->tab = newzones;
	return (0);
}
