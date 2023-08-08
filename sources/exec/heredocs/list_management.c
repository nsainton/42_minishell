/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:45:49 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/08 17:20:57 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*getlist(const size_t size, const size_t elemsize)
{
	static int	*list;

	if (! (size || elemsize))
	{
		list = NULL;
		return (list);
	}
	if (! (size && elemsize))
		return (list);
	list = gccalloc(size, elemsize);
	return (list);
}

void	clear_list(void)
{
	char	nullelem[20];
	int		*list;
	size_t	i;
	size_t	elemsize;

	elemsize = 2 * sizeof * list;
	list = getlist(0, elemsize);
	if (! list)
		return ;
	ft_bzero(nullelem, elemsize);
	i = 0;
	while (ft_memcmp(list + i, nullelem, elemsize) && \
	*(list + i) != -1)
	{
		close(*(list + i + 1));
		i += 2;
	}
	free_node(list);
	getlist(0, 0);
}

void	close_heredoc_fds(void)
{
	char	nullelem[20];
	int		*list;
	size_t	i;
	size_t	elemsize;

	elemsize = 2 * sizeof * list;
	list = getlist(0, elemsize);
	if (! list)
		return ;
	ft_bzero(nullelem, elemsize);
	i = 0;
	while (ft_memcmp(list + i, nullelem, elemsize) && \
	*(list + i) != -1)
	{
		if (*(list + i) > 2)
			close(*(list + i));
		i += 2;
	}
	free_node(list);
	getlist(0, 0);
}
