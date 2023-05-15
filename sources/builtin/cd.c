/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:22 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/11 13:23:26 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_command *cmd, t_data *d)
{
	if (!cmd->args[0])
		return (go_home(d->env, 1));
	if (cmd->args[0][0] == '~')
	{
		go_home(d->env, 0);
		cmd->args[0][0] = '.';
	}
	if (cmd->args[0][0])
	{
		if (chdir(cmd->args[0]))
		{
			ft_dprintf(2, "cd : %s : %s\n", cmd->args[0],
				strerror(errno));
				d->errnum = errno;
			return (errno);
		}
		d->errnum = set_new_pwd(d->env);
		return (d->errnum);
	}
	return (d->errnum);
}


int	set_new_pwd(t_env *my_env)
{
	char	*new_wd;
	char	*old_wd;
	int		errnum;

	errnum = 0;
	old_wd = get_env_var(my_env, "PWD");
	if (!old_wd)
		ft_dprintf(2, "cd : no pwd variable in env\n");
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
