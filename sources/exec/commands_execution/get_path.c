/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:48:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 13:20:42 by nsainton         ###   ########.fr       */
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

	map = getmap();
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

static char	*get_path_string(const char *path, const char *command)
{
	size_t	len;
	size_t	path_len;

	path_len = ft_strlen(path);
	len = ft_strlen(path) + ft_strlen(command);
}

static char	*find_in_path(const char **path, const char *command)
{
	size_t	i;
	char	*command_path;
	char	*test_path;

	i = 0;
	command_path = NULL;
	while (*(path + i))
	{
		test_path = gc_strjoin(*(path + i)
}

int	getpath(struct s_ncommand *command, struct s_env *env)
{
	const char	**path;
	const char	*path_var;

	if (ft_strchr(command->command, '/'))
	{
		command->path = command->command;
		return (0);
	}
	command->path = check_hashmap(command->command);
	if (command->path)
		return (0);
	path_var = get_env_var(env, "PATH");
	if (! path_var)
		return (127);
	path = gc_split(path_var, ':');
	if (! path)
		return (2);
	command->path = find_in_path(command->command, path);
}
