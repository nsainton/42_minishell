/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:48:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 11:58:37 by nsainton         ###   ########.fr       */
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

static size_t	hash(const void *s)
{
	const char	*string;
	size_t		code;
	size_t		i;

	i = 0;
	code = 0;
	string = (char *)s;
	while (*(string + i))
	{
		code += *(string + i) * i;
		i ++;
	}
	return (code);
}

static char	*check_hashmap(struct s_hashmap *map, const char *command)
{
	struct s_list	*path_node;
	char			*path;

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
	const char			*path;
	struct s_hashmap	*map;

	map = getmap(hash, free_node);
	if (! map)
		return (ALLOCATION_ERROR);
	if (ft_strchr(command->command, '/'))
	{
		command->path = command->command;
		return (0);
	}
	command->path = check_hashmap(map, command->command);
	if (command->path)
		return (0);
	path = get_env_var(env, "PATH");
	if (! path)
		return (127);
	command->path = find_in_path(path, command->command);
	if ((command->path && ! access(command->path, X_OK)) && \
	hash_map_add(map, command->path))
		return (ALLOCATION_ERROR);
	return (0);
}
