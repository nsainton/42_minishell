/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:06:33 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/17 14:41:33 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int errno, char *msg)
{
	printf("error : %s\n", msg);
	free_gc(errno);
	exit(errno);
}

void	print_list_prefix(t_list *lst, char *prefix)
{
	t_list	*tmp;

	if (!lst)
		printf("List is empty ...\n");
	tmp = lst;
	while (tmp != NULL)
	{
		if (!prefix)
			ft_printf("%s\n", (char *) tmp->content);
		else
			ft_printf("%s %s\n", prefix, (char *) tmp->content);
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
