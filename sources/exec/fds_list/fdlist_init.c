/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdlist_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:51:27 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:11:25 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function initializes the fdlist with the standard file descriptors
	numbers (which are provided already opened to the executable).
	It is to be called at the start of the main routine and at no other
	moment during the lifetime of the program
*/
int	fdlist_init(void)
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
