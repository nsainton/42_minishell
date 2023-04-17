/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:32:16 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 16:41:02 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_lstdelone(t_list *lst, void (*del) (void *))
{
	del(lst->content);
	return (free_node(lst));
}

static void	gc_lstfreenodes(t_list **lst)
{
	t_list	*p;
	t_list	*q;

	p = *lst;
	while (p->next)
	{
		q = p->next;
		free_node(p);
		p = q;
	}
	free_node(p);
	*lst = NULL;
}

void	gc_lstclear(t_list **lst, void (*del) (void *))
{
	t_list *p;
	t_list	*q;

	p = *lst;
	if (p == NULL)
		return ;
	if (! del)
		return (gc_lstfreenodes(lst));
	while (p->next != NULL)
	{
		q = p->next;
		del(p->content);
		free_node(p);
		p = q;
	}
	*lst = NULL;
	del(p->content);
	free_node(p);
}

void	gc_lstdel_front(t_list **lst, void (*del) (void *))
{
	t_list *tmp;

	if (*lst == NULL)
		return ;
	tmp = *lst;
	*lst = (*lst)->next;
	if (del)
		return (gc_lstdelone(tmp, del));
	free_node(tmp);
}
