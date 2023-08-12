/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:16:49 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 14:35:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/*
	The array cwd if of size PATH_MAX + 2 to hold a slot for the eventual
	/ that will come at the end of the array
*/
static char *get_cwd_path(const char *command)
{
	char	cwd[PATH_MAX + 2];
	char	*path_string;
	size_t	path_len;
	size_t	command_len;

	if (! getcwd(cwd, PATH_MAX + 1))
		return (NULL);
	path_len = ft_strlen(cwd);
	if (cwd[path_len - 1] != '/')
	{
		*(cwd + path_len - 1) = '/';
		*(cwd + path_len) = 0;
		path_len ++;
	}
	path_string = gccalloc(path_len + ft_strlen(command) + 1);
	if (! path_string)
		return (NULL);
	ft_strcat(path_string, cwd);
	ft_strcat(path_string + path_len, command);
	if (! access(filepath, F_OK))
		return (path_string);
	free(path_string);
	return (NULL);
}

static char	*get_path_string(const char *path, size_t index, \
const char *command)
{
	size_t	len;
	size_t	path_len;

	path_len = ft_strlen(path);
	len = ft_strlen(path) + ft_strlen(command);
}

static int	is_exec(const char *filepath)
{
	return (! (access(filepath, F_OK) || access(filepath, X_OK)));
}

static char	*find_in_path(const char *path, const char *command)
{
	size_t	i;
	char	*command_path;
	char	*test_path;

	i = 0;
	command_path = NULL;
	if (*path == ':')
		command_path = get_cwd_path(command);
	if (command_path && is_exec(command_path)) 
		return (command_path);
	while (*(path + i))
	{
		while (*(path + i) && *(path + i) != ':')
			i ++;
		test_path = get_path_string(path, i
}

