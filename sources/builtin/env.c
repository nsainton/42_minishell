/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/21 17:46:42 by avedrenn         ###   ########.fr       */
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

int	print_env(t_env *my_env, t_command *cmd)
{
	if (my_env->is_empty)
		printf("\n"); //? regarder reel comportement
	else if (cmd->args[0] || cmd->options[0])
		printf("env : env in minishell doesn't support arguments or options\n");
	else
		print_list_prefix(my_env->list_env, NULL);
	return (SUCCESS);
}

int	unset_env(t_env *my_env, t_command *cmd)
{
	int		i;
	t_list	*tmp;
	char	*line;

	if (!cmd->args[0])
		return (SUCCESS);
	i = 0;
	tmp = my_env->list_env;
	while (cmd->args[i])
	{
		while (my_env->list_env)
		{
			line = (char *) my_env->list_env->content;
			if (!ft_strncmp(cmd->args[i], line, ft_strlen(cmd->args[i]))
				&& line[ft_strlen(cmd->args[i])] == '=')
				delete_env_line(tmp, my_env->list_env);
			my_env->list_env = my_env->list_env->next;
		}
		i++;
	}
	my_env->list_env = tmp;
	return (SUCCESS);
}

void	delete_env_line(t_list *start, t_list *to_del)
{
	while (start->next != to_del)
		start = start->next;
	start->next = to_del->next;
	to_del->content = 0;
	//free to_del ? (ou gc freenode ? )
}
