/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/15 12:56:55 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	We free_node if using set_var_value because set_var_value allocates
	memory (which set_var doesn't)
*/
static int	export_var(const char *variable, struct s_env *env)
{
	char	*var_name;
	size_t	i;
	int		err;

	i = 0;
	while (*(variable + i) && *(variable + i) != '=')
		i ++;
	var_name = gccalloc(i + 1, sizeof * var_name);
	if (! var_name)
		return (ALLOCATION_ERROR);
	ft_memcpy(var_name, variable, i);
	if (! *(variable + i))
		return (set_var(env->export_list, var_name));
	err = (set_var_value(env->env_list, var_name, variable + i) || \
	set_var_value(env->export_list, var_name, variable + i));
	free_node(var_name);
	return (err);
}

int	export(const char **args, struct s_env *env)
{
	int		err;

	err = 0;
	if (! (args && *args))
		return (print_exportlist(env->export_list));
	while (*args)
	{
		if (! valid_identifier(*args))
		{
			ft_dprintf(STDERR_FILENO, \
			"minishell: export: `%s': not a valid identifier\n", *args);
			err = 1;
			args ++;
			continue ;
		}
		if (export_var(*args, env))
			return (ALLOCATION_ERROR);
		args ++;
	}
	return (err);
}
/*
int	export_env(t_data *d, t_command *cmd)
{
	int	i;

	if (d->env->is_empty)
	{
		ft_dprintf(2, "env : export : No such file or directory\n");
		return (127);
	}
	if (!cmd->args[0])
	{
		print_list_prefix(d->env->list_env, "declare -x");
		return (SUCCESS);
	}
	i = 0;
	d->errnum = 0;
	while (cmd->args[i])
	{
		if (is_valid_export(cmd->args[i]) == 20)
		{
			if (modify_env(d->env, cmd->args[i]) == 0)
				ft_lstadd_back(&d->env->list_env, gc_lstnew(cmd->args[i]));
		}
		else
			d->errnum = 1;
		i++;
	}
	return (d->errnum);
}
*/

/*
int	is_valid_export(char *arg)
{
	if (ft_strchr(arg, '=') == NULL)
		return (0);
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') || !is_valid_name(arg))
	{
		ft_dprintf(2, "export: %s : not a valid identifier\n", arg);
		return (1);
	}
	return (20);
}
*/

/*    name   A  word  consisting  only  of alphanumeric characters and under‐
              scores, and beginning with an alphabetic character or an  under‐
              score.  Also referred to as an identifier. */

/*
int	is_valid_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i ++;
	}
	return (1);
}
*/

/*
int	modify_env(struct s_env *my_env, char *export)
{
	int				len;
	struct s_list	*tmp;
	char			*end;
	char			*line;

	len = 0;
	end = ft_strchr(export, '=');
	tmp = my_env->list_env;
	while (&export[len] != end)
		len++;
	while (my_env->list_env)
	{
		line = (char *) my_env->list_env->content;
		if (!ft_strncmp(export, line, len) && line[len] == '=')
		{
			my_env->list_env->content = export;
			my_env->list_env = tmp;
			return (1);
		}
		my_env->list_env = my_env->list_env->next;
	}
	my_env->list_env = tmp;
	return (0);
}
*/
