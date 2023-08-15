/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:22 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/15 10:52:16 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	cd(const char **args, struct s_env *env)
{
//	int	len;

	if (! *args)
		return (go_home(env, 1));
	if (*(args + 1))
	{
		ft_dprintf(2, "cd : too many arguments\n");
		return (1);
	}
	/*
	if (cmd->args[0][0] == '~')
	{
		go_home(d->env, 0);
		cmd->args[0][0] = '.';
	}
	*/
	if (! ft_strcmp(*args, "-"))
		return (go_old_pwd(env));
	return (change_dir(*args, env));
}

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

int	set_wd(struct s_env *env)
{
	char	*owd;
	char	current[PATH_MAX + 1];
	int		errnum;

	if (set_oldpwd(env))
		return (ALLOCATION_ERROR);
	owd = get_env_var(env, "OLDPWD");
	if (! getcwd(current, PATH_MAX + 1))
		return (1);
	if (! get_env_var("PWD"))
		return (0);
	if (set_var_value(env->env_list, "PWD", current) || \
	set_var_value(env->export_list, "PWD", current))
		return (ALLOCATION_ERROR);
	return (0);
}

int	go_home(t_env *my_env, int set_old)
{
	char	*home_path;
	int		errnum;

	errnum = 0;
	home_path = get_env_var(my_env, "HOME");
	if (!home_path)
	{
		ft_dprintf(2, "error : no home path in env\n");
		return (errnum --);
	}
	else
	{
		if (chdir(home_path))
		{
			ft_dprintf(2, "%s\n", strerror(errno));
			return (errno);
		}
		if (set_old)
			errnum = set_new_pwd(my_env);
		return (errnum);
	}
}

int	go_old_pwd(struct s_env *env)
{
	char	*old_wd;
	
	old_wd = get_env_var(env, "OLDPWD");
	if (!old_wd)
	{
		ft_dprintf(2, "cd : OLDPWD not set \n");
		return (1);
	}
	return (change_dir(old_wd, env));
}
