/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:47:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/02 20:37:34 by nsainton         ###   ########.fr       */
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
	t_list	*tmp;

	tmp = prev_first->next;
	prev_first->next = prev_second->next;
	prev_second->next = tmp;
	tmp = tmp->next;
	prev_second->next->next = prev_first->next->next;
	prev_first->next->next = tmp;
}

/*
static void	print_node(void *node)
{
	ft_printf("This is the node : %s\n", (char *)node);
}
*/

static void	compare_elems(t_list *begin_list, int (*cmp)())
{
	t_list	*outer_iterator;
	t_list	*inner_iterator;
	unsigned int	i;

	i = 0;
	outer_iterator = begin_list;
	while (outer_iterator->next)
	{
		/*
		ft_printf("Printing full list\n");
		ft_lstiter(begin_list, print_node);
		*/
		//getchar();
		inner_iterator = outer_iterator->next;
		while (inner_iterator->next)
		{
			//ft_printf("This is the inner content : %s\n", (char *)inner_iterator->content);
			if (cmp(outer_iterator->next->content, \
			inner_iterator->next->content) > 0)
			{
				/*
				ft_printf("Going to swap %s and %s\n", (char *)outer_iterator->next->content, (char *)inner_iterator->next->content);
				ft_printf("LIST BEFORE SWAPPING---------%u\n", i);
				ft_lstiter(begin_list, print_node);
				*/
				swap_elems(outer_iterator, inner_iterator);
				/*
				ft_printf("LIST AFTER SWAPPING-------%u\n", i);
				ft_lstiter(begin_list, print_node);
				*/
				i ++;
			}
			//if (inner_iterator->next)
			else
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
	{
		iterator = iterator->next;
		ft_printf("This is the content : %s\n", (char *)iterator->content);
	}
	if (iterator != *begin_list)
		insert_first(begin_list, iterator);
}
