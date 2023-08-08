/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:45:49 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/08 14:57:48 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*getlist(const size_t size, const size_t elemsize)
{
	static int	*list;

	if (! elemsize)
		return (list);
	list = gccalloc(size, elemsize);
	return (list);
}

void	clear_list(void)
{
	char	nullelem[20];
	int		*list;
	size_t	i;

	list = getlist(0, 0);
	if (! list)
		return ;
	ft_bzero(nullelem, 2 * sizeof * list);
	i = 0;
	while (ft_memcmp(list + i, nullelem, 2 * sizeof * list) && \
	*(list + i) != -1)
	{
		close(*(list + i + 1));
		i += 2;
	}
	free_node(list);
}

void	close_heredoc_fds(int *list)
{
	char	nullelem[20];
	int		*list;
	size_t	i;

	list = getlist(0, 0);
	if (! list)
		return ;
	ft_bzero(nullelem, 2 * sizeof * list);
	i = 0;
	while (ft_memcmp(list + i, nullelem, 2 * sizeof * list) && \
	*(list + i) != -1)
	{
		if (*(list + i) > 2)
			close(*(list + i));
		i += 2;
	}
	free_node(list);
}
