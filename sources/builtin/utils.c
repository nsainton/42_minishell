/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:06:33 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/10 14:56:20 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_prefix(t_list *lst, char *prefix)
{
	t_list	*tmp;

	if (!lst)
		ft_dprintf(2, "error : list is empty ...\n");
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

char	**envlist_to_arr(t_list *env)
{
	char	**envp;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = gcmalloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup((char *) env->content);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
