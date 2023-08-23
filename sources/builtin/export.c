/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/23 10:48:33 by nsainto          ###   ########.fr       */
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
	err = (set_var_value(env->env_list, var_name, variable + i + 1) || \
	set_var_value(env->export_list, var_name, variable + i + 1));
	free_node(var_name);
	return (err);
}

static int	is_opt(const char *variable)
{
	return ((*variable == '-') && *(variable + 1));
}

static void	option_error(const char *variable)
{
	ft_dprintf(STDERR_FILENO, "minishell: export: %.2s: invalid option\n\
export: usage: export\n", variable);
}

int	export(const char **args, struct s_env *env)
{
	int		err;

	err = 0;
	if (! (args && *args))
		return (print_exportlist(env->export_list));
	if (is_opt(*args))
	{
		option_error(*args);
		return (SYNTAX_ERROR);
	}
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
