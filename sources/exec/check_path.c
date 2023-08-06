/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:48 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/27 14:38:30 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_command(char **path, struct s_command *command)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (*(path + i))
	{
		tmp = gc_strjoin(path[i], "/");
		if (! tmp)
			exit_free_gc(ALLOCATION_ERROR);
		free_node(*(path + i));
		*(path + i) = gc_strjoin(tmp, command->command);
		free_node(tmp);
		if (! *(path + i))
			exit_free_gc(ALLOCATION_ERROR); //Don't forget to update the wait_for_childs function to take care of exit status
		if (! (access(*(path + i), X_OK) || access (*(path + i), F_OK)))
		{
			command->path = *(path + i);
			return (EXIT_SUCCESS);
		}
		i ++;
	}
	return (127);
}

int	check_path(t_command *cmd, t_env *my_env)
{
	char	*big_path;
	char	**path;

	cmd->path = NULL;
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		cmd->path = cmd->command;
		if (!access(cmd->path, X_OK) && !is_a_directory(cmd->path))
			return (0);
		return (126);
	}
	big_path = get_env_var(my_env, "PATH");
	if (!big_path)
		return (127);
	path = gc_split(big_path, ':');
	if (!path)
		return (2);
	return (find_command(path, cmd));
}

/*
int	check_path(t_command *cmd, t_env *my_env)
{
	char	*big_path;
	char	**path;
	char	*tmp;
	int		i;

	cmd->path = NULL;
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		cmd->path = cmd->command;
		if (!access(cmd->path, X_OK) && !is_a_directory(cmd->path))
			return (0);
		return (126);
	}
	i = -1;
	big_path = get_env_var(my_env, "PATH");
	if (!big_path)
		return (127);
	path = gc_split(big_path, ':');
	if (!path)
		return (2);
	while (path[++i])
	{
		tmp = gc_strjoin(path[i], "/");
		free_node(path[i]);
		path[i] = gc_strjoin(tmp, cmd->command);
		free_node(tmp);
		if (!access(path[i], F_OK) && !access(path[i], X_OK))
		{
			cmd->path = path[i];
			return (0);
		}
	}
	free_node(path);
	return (127);
}
*/

int	is_a_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		perror("Error in stat function\n");
		return (0);
	}
	return ((sb.st_mode & S_IFMT) == S_IFDIR);
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
