/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:48 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/18 17:01:52 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_command *cmd, t_env *my_env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = -1;
	cmd->path = NULL;
	path = gc_split(get_env_var(my_env, "PATH"), ':');
	if (!path)
		return (2);
	while (path[++i])
	{
		tmp = gc_strjoin(path[i], "/");
		free_node(path[i]);
		path[i] = gc_strjoin(tmp, cmd->command);
		free_node(tmp);
		if (!access(path[i], F_OK))
		{
			cmd->path = path[i];
			return (0);
		}
	}
	free_node(path);
	return (127);
}

int	ft_arrlen(void **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
