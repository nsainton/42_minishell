/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:22 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/15 12:00:02 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_oldpwd(struct s_env *env)
{
	const char	*directory;

	directory = get_var_value(env->env_list, "PWD");
	if (! directory)
		directory = "";
	if (set_var_value(env->env_list, "OLDPWD", directory))
		return (ALLOCATION_ERROR);
	if (set_var_value(env->export_list, "OLDPWD", directory))
		return (ALLOCATION_ERROR);
	return (0);
}

static int	set_wd(struct s_env *env)
{
	char	current[PATH_MAX + 1];

	if (set_oldpwd(env))
		return (ALLOCATION_ERROR);
	if (! getcwd(current, PATH_MAX + 1))
		return (1);
	if (! get_var_value(env->env_list, "PWD"))
		return (0);
	if (set_var_value(env->env_list, "PWD", current) || \
	set_var_value(env->export_list, "PWD", current))
		return (ALLOCATION_ERROR);
	return (0);
}

static int	change_dir(const char *directory, struct s_env *environment)
{
	if (chdir(directory))
	{
		ft_dprintf(STDERR_FILENO, "cd : %s : %s\n", directory, \
		strerror(errno));
		return (1);
	}
	return (set_wd(environment));
}

static int	go_to_path(struct s_env *env, const char *path_var)
{
	char	*path;

	path = get_var_value(env->env_list, path_var);
	if (!path)
	{
		ft_dprintf(2, "minishell : cd: %s not set\n", path_var);
		return (1);
	}
	return (change_dir(path, env));
}

int	cd(const char **args, struct s_env *env)
{
	if (! *args)
		return (go_to_path(env, "HOME"));
	if (*(args + 1))
	{
		ft_dprintf(2, "cd : too many arguments\n");
		return (1);
	}
	if (! ft_strcmp(*args, "-"))
		return (go_to_path(env, "OLDPWD"));
	return (change_dir(*args, env));
}
