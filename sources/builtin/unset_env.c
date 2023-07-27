/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:01:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 10:20:26 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(char **args, struct s_env *environment)
{
	size_t	i;
	size_t	arglen;
	t_list	*tmp;
	char	*line;

	i = 0;
	tmp = environment->list_env;
	while (args[i])
	{
		arglen = ft_strlen(args[i]);
		while (environment->list_env)
		{
			line = (char *)environment->list_env->content;
			if (!ft_strncmp(args[i], line, arglen) && line[arglen] == '=')
				delete_env_line(tmp, environment->list_env);
			environment->list_env = environment->list_env->next;
		}
		i++;
	}
	environment->list_env = tmp;
}

int	unset_env(t_data *d, t_command *cmd)
{
	d->errnum = 0;
	if (d->env->is_empty)
	{
		ft_dprintf(2, "env : unset : No such file or directory\n");
		return (127);
	}
	if (!cmd->args[0])
		return (SUCCESS);
	remove_env_var(cmd->args, d->env);
	return (SUCCESS);
}
