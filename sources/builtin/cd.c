/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:22 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/27 09:54:51 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(const char *directory, struct s_env *environment)
{
	if (chdir(directory))
	{
		ft_dprintf(2, "cd : %s : %s\n", directory, strerror(errno));
		keep_exit_status(1);
		return (1);
	}
	set_new_pwd(environment);
	return (0);
}

int	cd(t_command *cmd, t_data *d)
{
	int	len;

	if (!cmd->args[0])
		return (go_home(d->env, 1));
	len = ft_arrlen((void *) cmd->args);
	if (len > 1)
	{
		ft_dprintf(2, "cd : too many arguments\n");
		return (1);
	}
	if (cmd->args[0][0] == '~')
	{
		go_home(d->env, 0);
		cmd->args[0][0] = '.';
	}
	if (cmd->args[0][0])
		return (change_dir(cmd->args[0], d->env));
	return (0);
}

int	set_new_pwd(t_env *my_env)
{
	char	*new_wd;
	char	*old_wd;
	int		errnum;

	errnum = 0;
	old_wd = get_env_var(my_env, "PWD");
/* 	if (!old_wd)
		ft_dprintf(2, "cd : no pwd variable in env\n"); */
	new_wd = getcwd(NULL, 0);
	if (!new_wd)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (errno);
	}
	if (old_wd && new_wd)
	{
		errnum = update_env_line(my_env, "OLDPWD", old_wd);
		if (!errnum)
			errnum = update_env_line(my_env, "PWD", new_wd);
	}
	free(new_wd);
	return (errnum);
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
