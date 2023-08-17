/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:48:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 13:37:21 by nsainton         ###   ########.fr       */
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
	const char	*name;
	size_t		code;
	size_t		i;

	i = 0;
	code = 0;
	string = (char *)s;
	name = ft_strrchr(string, '/');
	name += (name != NULL);
	if (! name)
		name = string;
	while (*(name + i))
	{
		code += *(name + i) * i;
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

int	getpath(char *command, char **command_path, struct s_tab *env)
{
	const char			*path;
	struct s_hashmap	*map;

	map = getmap(hash, free_node);
	if (! map)
		return (ALLOCATION_ERROR);
	if (ft_strchr(command, '/'))
	{
		*command_path = command;
		return (0);
	}
	*command_path = check_hashmap(map, command);
	if (*command_path)
		return (0);
	path = get_var_value(env, "PATH");
	if (! path)
		return (127);
	*command_path = find_in_path(path, command);
	if ((*command_path && ! access(*command_path, X_OK)) && \
	hash_map_add(map, *command_path))
		return (ALLOCATION_ERROR);
	return (0);
}
