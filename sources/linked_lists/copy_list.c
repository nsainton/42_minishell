/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:40:02 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/21 15:02:31 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_list	*copy_list(struct s_list *lst)
{
	struct s_list	*copy;
	struct s_list	*node;

	if (! lst)
		return (NULL);
	copy = malloc(sizeof * copy);
	if (! copy)
		return (NULL);
	ft_memcpy(copy, lst, sizeof * copy);
	copy->next = NULL;
	while (lst != NULL)
	{
		node = malloc(sizeof * copy);
		if (! node)
		{
			ft_lstclear(&copy, NULL);
			return (NULL);
		}
		ft_memcpy(node, lst, sizeof * copy);
		ft_lstadd_front(&copy, node);
		lst = lst->next;
	}
	return (copy);
}
