/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdlist_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:51:27 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 10:55:04 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fdlist_init()
{
	struct s_list	**fdlist;
	struct s_list	*newnode;
	int				fd;

	fdlist = get_fdlist();
	fd = 0;
	while (fd < 3)
	{
		newnode = gc_lstnew_cpy(&fd, sizeof fd);
		if (! newnode)
			return (1);
		ft_lstadd_front(fdlist, newnode);
		fd ++;
	}
	return (0);
}
