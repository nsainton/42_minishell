/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdlist_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:04:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 10:22:04 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Here are stored the functions to manage the list.
*/

struct s_list	**get_fdlist(void)
{
	static struct s_list	*fdlist;

	return (&fdlist);
}

struct s_list	*ft_list_find(struct s_list *begin_list, \
const void *data_ref, int (*cmp)())
{
	t_list	*p;

	if (! (begin_list && data_ref && cmp))
		return (NULL);
	p = begin_list;
	while (p != NULL)
	{
		if (! cmp(p->content, data_ref))
			return (p);
		p = p->next;
	}
	return (NULL);
}

void	del_node(struct s_list **lst, struct s_list *node, \
void (*del)(void *))
{
	struct s_list	*p;
	struct s_list	*tmp;

	if (*lst == node)
		return (gc_lstdel_front(lst, del));
	p = *lst;
	while (p)
	{
		if (p->next != node)
		{
			p = p->next;
			continue ;
		}
		tmp = p->next;
		p->next = p->next->next;
		gc_lstdelone(tmp, del);
		break ;
	}
}

/*
	Here is the function to clear the list of all open file descriptors
	(if they are non standard). We will call the function gc_lstclear
	with another function that will have static storage class
*/
static void	del_listfd(void *fdaddress)
{
	int	fd;

	fd = *(int *)fdaddress;
	if (fd > 2)
		close (fd);
	free_node(fdaddress);
}

void	clear_fdlist(void)
{
	struct s_list	**fdlist;

	fdlist = get_fdlist();
	gc_lstclear(fdlist, del_listfd);
}
