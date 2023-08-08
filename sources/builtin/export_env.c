/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:34:01 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/08 13:23:09 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_var(char *arg, struct s_env *environment)
{
	struct s_list	*newvar;

	if (modify_env(environment, arg) == 0)
	{
		newvar = gc_lstnew(arg);
		if (! newvar)
		{
			ft_dprintf(STDERR_FILENO, "minishell: allocation error\n");
			exit_free_gc(ALLOCATION_ERROR);
		}
		ft_lstadd_back(&environment->list_env, newvar);
	}
	return (EXIT_SUCCESS);
}

int	add_env_vars(char **args, struct s_env *environment, int *errnum)
{
	unsigned int	i;

	i = 0;
	while (*(args + i))
	{
		if (is_valid_export(*(args + i)) == 20)
			add_env_var(*(args + i), environment);
		else
			*errnum = 1;
		i ++;
	}
	return (EXIT_SUCCESS);
}

int	export_env(t_data *d, t_command *cmd)
{
	struct s_list	*lst;

	/* if (d->env->is_empty)
	struct s_list *lst;

	if (d->env->is_empty)
	{
		ft_dprintf(2, "env : export : No such file or directory\n");
		return (127);
	} */
	if (!cmd->args[0])
	{
		lst = copy_list(d->env->list_env);
		if (! lst)
			return (1);
		ft_list_sort(&lst, ft_strcmp);
		print_list_prefix(lst, "export");
		ft_lstclear(&lst, NULL);
		return (SUCCESS);
	}
	d->errnum = 0;
	add_env_vars(cmd->args, d->env, &d->errnum);
	return (d->errnum);
}
