/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:16:49 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 09:26:43 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	is_regular(const char *filepath, const int check_exec)
{
	struct stat	statbuf;
	int			reg;

	if (stat(filepath, &statbuf))
		return (0);
	reg = S_ISREG(statbuf.st_mode);
	if (! (check_exec && reg))
		return (reg);
	return (! access(filepath, X_OK));
}

/*
	The array cwd if of size PATH_MAX + 2 to hold a slot for the eventual
	/ that will come at the end of the array
*/
static char	*get_cwd_path(const char *command)
{
	char	cwd[PATH_MAX + 2];
	char	*path_string;
	size_t	path_len;

	if (! getcwd(cwd, PATH_MAX + 1))
		return (NULL);
	path_len = ft_strlen(cwd);
	if (cwd[path_len - 1] != '/')
	{
		*(cwd + path_len) = '/';
		*(cwd + path_len + 1) = 0;
		path_len ++;
	}
	path_string = gccalloc(path_len + ft_strlen(command) + 1, \
	sizeof * path_string);
	if (! path_string)
		return (NULL);
	ft_strcat(path_string, cwd);
	ft_strcat(path_string + path_len, command);
	if (is_regular(path_string, 0))
		return (path_string);
	free_node(path_string);
	return (NULL);
}

/*
	Same reason as the function above. If there is no '/' at the end
	of the path, we need to add one and thus will need an extra slot
*/
static char	*get_path_string(const char *path, size_t pathlen, \
const char *command)
{
	size_t	len;
	size_t	added;
	char	*path_string;

	if (! pathlen)
		return (get_cwd_path(command));
	len = pathlen + ft_strlen(command) + (*(path + pathlen - 1) != '/') + 1;
	path_string = gccalloc(len, sizeof * path_string);
	if (! path_string)
		return (NULL);
	added = ft_strncat(path_string, path, pathlen);
	if (*(path_string + added - 1) != '/')
		added += ft_strncat(path_string + added, "/", 1);
	ft_strcat(path_string + added, command);
	if (is_regular(path_string, 0))
		return (path_string);
	free_node(path_string);
	return (NULL);
}

static size_t	pathlen(const char **path)
{
	size_t	i;

	if (**path == ':')
		(*path)++;
	i = 0;
	while (*(*path + i) && *(*path + i) != ':')
		i ++;
	return (i);
}

/*
	First, if path begins by a semicolumn, we look for an exec in the
	current directory. Then for each directory in path, we compute
	the "len" of directory name and look for a command in this directory.
	If the directory name is not right, the command will just not be found.
	If the command is an executable, we return it right away, if not we
	store it (if there was no command before) and look for an executable
	into the remaining directories of the path.
	To look into the path directories, we start by skipping the first
	semicolumn and then read the directory name, we then find the
	corresponding command and act upon what we found
*/
char	*find_in_path(const char *path, const char *command)
{
	size_t	i;
	char	*command_path;
	char	*test_path;

	i = 0;
	command_path = NULL;
	if (*path == ':')
		command_path = get_cwd_path(command);
	if (command_path && is_regular(command_path, 1)) 
		return (command_path);
	while (*(path + i))
	{
		i = pathlen(&path);
		test_path = get_path_string(path, i, command);
		if (test_path && is_regular(test_path, 1))
			return (test_path);
		if (! command_path)
			command_path = test_path;
		path += i;
		i = 0;
	}
	return (command_path);
}
