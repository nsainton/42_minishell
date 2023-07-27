/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:34:01 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 10:44:58 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env_var(char *arg, struct s_env *environment)
{
	struct s_list	*newvar;

	if (modify_env(environment, arg) == 0)
	{
		newvar = gc_lstnew(arg);
		if (! newvar)
			return (ALLOCATION_ERROR);
		ft_lstadd_back(&environment->list_env, newvar);
	}
	return (EXIT_SUCCESS);
}

static int	add_env_vars(char **args, struct s_env *environment, int *errnum)
{
	unsigned int	i;

	i = 0;
	while (*(args + i))
	{
		if (is_valid_export(*(args + i)) == 20)
			add_env_var(*(args + i), environment); //catch segfault here
		else
			*errnum = 1;
		i ++;
	}
	return (EXIT_SUCCESS);
}

int	export_env(t_data *d, t_command *cmd)
{
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
	d->errnum = 0;
	add_env_vars(cmd->args, d->env, &d->errnum);
	return (d->errnum);
}
