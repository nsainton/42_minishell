/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:01:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:39:21 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
		while (is_valid_unset(args[i]) && environment->list_env)
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

int	is_valid_unset(char *arg)
{
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') || !is_valid_name(arg))
	{
		ft_dprintf(2, "unset: %s : not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}
*/
