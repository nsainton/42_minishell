/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/14 14:15:13 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_my_env(char **envp)
{
	t_env	*my_env;

	my_env = gcmalloc (sizeof(t_env));
	if (!my_env)
		return (NULL);
	my_env->list_env = NULL;
	my_env->path = NULL;
	if (!envp || !envp[0])
	{
		my_env->is_empty = 1;
		return (my_env);
	}
	else
		my_env->is_empty = 0;
	my_env->list_env = copy_env(envp);
	print_list(my_env->list_env);
	return (my_env);
}

t_list	*copy_env(char **envp)
{
	int		i;
	t_list	*list_env;
	t_list	*new;

	list_env = ft_lstnew_gc((void *) envp[0]);
	i = 1;
	while (envp[i])
	{
		new = ft_lstnew_gc((void *) envp[i]);
		ft_lstadd_back(&list_env, new);
		i ++;
	}
	return (list_env);
}

void	print_env(t_env *my_env)
{
	if (my_env->is_empty)
		printf("\n"); //? regarder reel comportement
	else
		print_list(my_env->list_env);
}
