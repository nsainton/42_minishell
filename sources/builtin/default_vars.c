/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:49:49 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 10:51:20 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	We allocate shlvl / 10 + 2 here to have the right number of digits
	and keep a room for the null terminator.
*/
static int	set_shlvl(struct s_tab *env_list, const int init)
{
	char	*newlvl;
	int		shlvl;
	size_t	len;
	char	*shlvl_value;

	shlvl_value = get_var_value(env_list, "SHLVL");
	if (! shlvl_value)
		shlvl = 0;
	else
		shlvl = ft_atoi(shlvl_value);
	if (shlvl <= 0 && init)
		shlvl = 0;
	else
		shlvl ++;
	newlvl = gccalloc(ft_strlen("SHLVL=") + shlvl / 10 + 2, sizeof * newlvl);
	if (! newlvl)
		return (ALLOCATION_ERROR);
	len = ft_strcat(newlvl, "SHLVL=");
	put_nb_tab(shlvl, newlvl + len, DEC);
	return (set_var(env_list, newlvl));
}

static int	init_shlvl(struct s_tab *env_list)
{
	char	*shlvl_value;
	int		err;

	shlvl_value = get_var_value(env_list, "SHLVL");
	if (! shlvl_value)
	{
		shlvl_value = gc_strdup("SHLVL=1");
		err = (! shlvl_value || add_tab(env_list, &shlvl_value));
		return (err * ALLOCATION_ERROR);
	}
	return (set_shlvl(env_list, 1));
}

/*
	We allocate PATH_MAX + 5 and give cwd + 4 to getcwd
	to keep room for the "PWD=" declaration we need at the
	beginning of the env variable
*/
static int	set_pwd(struct s_tab *env_list)
{
	char	cwd[PATH_MAX + 5];
	char	*pwd;

	if (! getcwd(cwd + 4, PATH_MAX + 1))
		return (1);
	ft_memcpy(cwd, "PWD=", ft_strlen("PWD="));
	pwd = gc_strdup(cwd);
	if (! pwd)
		return (1);
	return (set_var(env_list, pwd));
}

static int	set_default_var(struct s_tab *env_list, const char *var_name, \
const char *default_value)
{
	char	*tmp;

	tmp = get_var_value(env_list, var_name);
	return (! tmp && set_var_value(env_list, var_name, default_value));
}

int	default_vars(struct s_tab *env_list)
{
	char	*tmp;

	if (init_shlvl(env_list))
		return (1);
	tmp = get_var_value(env_list, "PWD");
	if (! tmp && set_pwd(env_list))
		return (1);
	if (set_default_var(env_list, "_", "/usr/bin/env"))
		return (1);
	if (set_default_var(env_list, "PS1", PS1))
		return (1);
	if (set_default_var(env_list, "PS2", PS2))
		return (1);
	return (0);
}
