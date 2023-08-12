/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:48:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 11:23:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	find_in_path(const char *command, const char **path)
{
	size_t	i;

	i = 0;
}
*/

/*
int	getpath(struct s_ncommand *command, struct s_env *env)
{
	const char	**path;
	const char	*path_var;

	if (ft_strchr(command->command, '/'))
	{
		command->path = command->command;
		return (0);
	}
	path_var = get_env_var(env, "PATH");
	if (! path_var)
		return (127);
	path = gc_split(path_var, ':');
	if (! path)
		return (2);
	command->path = find_in_path(command->command, path);
}
*/
