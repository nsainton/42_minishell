/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:22 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/03 19:14:51 by avedrenn         ###   ########.fr       */
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
	if (cmd->args[0][0] == '-' && !cmd->args[0][1])
		return (go_old_pwd(d->env));
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
	if (!old_wd)
	{
		add_env_var("PWD=.", my_env);
		old_wd = get_env_var(my_env,"PWD");
	}
	new_wd = getcwd(NULL, 0);
	if (!new_wd)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (errno);
	}
	errnum = update_env_line(my_env, "PWD", new_wd);
	if (get_env_var(my_env, "OLDPWD"))
		errnum = update_env_line(my_env, "OLDPWD", old_wd);
	else
	{
		add_env_var("OLDPWD=.", my_env);
		errnum = update_env_line(my_env, "OLDPWD", old_wd);
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

int	go_old_pwd(t_env *env)
{
	char	*old_wd;
	
	old_wd = get_env_var(env, "OLDPWD");
	if (!old_wd)
	{
		ft_dprintf(2, "cd : OLDPWD not set \n");
		return (1);
	}
	if (change_dir(old_wd, env))
		return (1);
	return (0);
}