/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:24:23 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 11:09:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_elem(t_list *prev, t_list *elem, \
void (*free_fct)(void *))
{
	t_list	*tmp;

	tmp = elem->next;
	if (free_fct)
		free_fct(elem->content);
	free(elem);
	prev->next = tmp;
}

static void	ft_remove_first(t_list **begin_list, \
void (*free_fct)(void *))
{
	t_list	*p;

	p = (*begin_list)->next;
	if (free_fct)
		free_fct((*begin_list)->content);
	free(*begin_list);
	*begin_list = p;
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, \
int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*p;
	t_list	*q;

	if (! (begin_list && *begin_list && data_ref && cmp))
		return ;
	while (*begin_list && ! cmp((*begin_list)->content, data_ref))
		ft_remove_first(begin_list, free_fct);
	p = *begin_list;
	if (! p)
		return ;
	q = p->next;
	while (q)
	{
		if (! cmp(q->content, data_ref))
		{
			ft_remove_elem(p, q, free_fct);
			q = p->next;
			if (! q)
				return ;
		}
		p = q;
		q = p->next;
	}
}
