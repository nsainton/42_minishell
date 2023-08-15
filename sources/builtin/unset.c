/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:01:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 17:35:09 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_opt(const char *variable)
{
	if (*variable != '-')
		return (0);
	if (*(variable + 1) && *(variable + 1) != '-')
		return (1);
	if (! *(variable + 1))
		return (0);
	return (*(variable + 2));
}

static void	option_error(const char *variable)
{
	ft_dprintf(STDERR_FILENO, "minishell: unset: %.2s: invalid option\n\
unset: usage: unset\n", variable);
}

int	unset(const char **args, struct s_env *env)
{
	if (! (args && *args))
		return (0);
	if (is_opt(*args))
	{
		option_error(*args);
		return (SYNTAX_ERROR);
	}
	while (*args)
	{
		del_tab_elem(env->env_list, *args, \
		compare_names, del_string_tab);
		del_tab_elem(env->export_list, *args, \
		compare_names, del_string_tab);
	}
	return (0);
}
