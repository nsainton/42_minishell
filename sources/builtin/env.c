/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/23 11:02:42 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_string_tab(void *str)
{
	free_node(*(char **)str);
}

void	print_env(struct s_tab *env)
{
	char	**env_variables;
	size_t	i;

	env_variables = (char **)env->tab;
	i = 0;
	while (i < env->len)
	{
		ft_putendl_fd(*(env_variables + i), STDOUT_FILENO);
		i ++;
	}
}

int	env(const char **args, struct s_env *environnement)
{
	if (! (args && *args))
	{
		print_env(environnement->env_list);
		return (0);
	}
	if (**args == '-')
	{
		ft_dprintf(STDERR_FILENO, "env: unrecognized option '%s'\n\
Try 'reading minishell subject' for more information\n", *args);
		return (125);
	}
	ft_dprintf(STDERR_FILENO, "env: no argument allowed\nSorry bruv\n");
	return (125);
}
