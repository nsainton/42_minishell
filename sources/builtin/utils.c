/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:06:33 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/14 14:18:06 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		printf("List is empty ...\n");
	tmp = lst;
	while (tmp != NULL)
	{
		ft_printf("%s\n", (char *) tmp->content);
		tmp = tmp->next;
	}
}

t_list	*ft_lstnew_gc(void *content)
{
	t_list	*new_elem;

	new_elem = gcmalloc(sizeof(*new_elem));
	if (new_elem == NULL)
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	new_elem->priority = 0;
	return (new_elem);
}
