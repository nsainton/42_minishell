/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:47:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/02 16:20:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_first(t_list **begin_list, t_list *prev_elem)
{
	t_list	*beg;

	beg = (*begin_list)->next;
	(*begin_list)->next = prev_elem->next;
	prev_elem->next = *begin_list;
	*begin_list = beg;
}

static void	swap_elems(t_list *prev_first, t_list *prev_second)
{
	t_list	*elem;
	t_list	*next;

	elem = prev_first->next;
	prev_first->next = prev_second->next;
	next = prev_second->next->next;
	prev_first->next->next = elem->next;
	prev_second->next = elem;
	prev_second->next->next = next;
}

static void	compare_elems(t_list *begin_list, int (*cmp)())
{
	t_list	*outer_iterator;
	t_list	*inner_iterator;

	outer_iterator = begin_list;
	while (outer_iterator->next)
	{
		inner_iterator = outer_iterator->next;
		while (inner_iterator->next)
		{
			if (cmp(outer_iterator->next->content, \
			inner_iterator->next->content) > 0)
				swap_elems(outer_iterator, inner_iterator);
			inner_iterator = inner_iterator->next;
		}
		outer_iterator = outer_iterator->next;
	}
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*iterator;

	if (! (begin_list && *begin_list && (*begin_list)->next))
		return ;
	compare_elems(*begin_list, cmp);
	iterator = *begin_list;
	while (iterator->next && cmp((*begin_list)->content, \
	iterator->next->content) > 0)
		iterator = iterator->next;
	if (iterator != *begin_list)
		insert_first(begin_list, iterator);
}
