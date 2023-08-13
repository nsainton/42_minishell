/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_wrappers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:51:12 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 17:00:46 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void delone_tab(struct s_tab *tab, const size_t index, \
void (*del)(void *))
{
	void	*zones;

	zones = tab->zones;
	if (del)
		del(zones + index * tab->elemsize);
	ft_memmove(zones + index * tab->elemsize, zones + (index + 1) * \
	tab->elemsize, (tab->len - index) * tab->elemsize);
	tab->len --;
}
void	del_tab_elem(struct s_tab *tab, void *elem, int (*cmp)(), \
void (*del)(void *))
{
	size_t	i;

	i = 0;
	while (i < tab->len)
	{
		if (cmp(tab->zones + i * tab->elemsize, elem))
			return (delone_tab(tab, i, del));
		i ++;
	}
}
