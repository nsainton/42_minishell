/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:48:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 10:23:22 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_fullname(const char *path, const char *name)
{
	const char	*varname;

	varname = ft_strrchr(path, '/');
	varname = varname + (varname != NULL);
	if (! varname)
		varname = path;
	return (ft_strcmp(varname, name));
}

static char *check_hashmap(const char *command)
{
	struct s_hashmap	*map;
	struct s_list		*path_node;
	char			*path;

	map = getmap(NULL, NULL); //CHANGE ME !!!
	if (! map)
		return (NULL);
	path_node = hash_map_find(map, command, is_fullname);
	if (! path_node)
		return (NULL);
	path = path_node->content;
	if (access(path, F_OK) || access(path, X_OK))
	{
		hash_map_delete(map, path_node);
		return (NULL);
	}
	return (path);
}

int	getpath(struct s_ncommand *command, struct s_env *env)
{
	const char	*path;

	if (ft_strchr(command->command, '/'))
	{
		command->path = command->command;
		return (0);
	}
	command->path = check_hashmap(command->command);
	if (command->path)
		return (0);
	path = get_env_var(env, "PATH");
	if (! path)
		return (127);
	command->path = find_in_path(command->command, path);
	return (0);
}
