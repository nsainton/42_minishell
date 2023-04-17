/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/17 16:15:22 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_env(t_env *my_env, char **args)
{
	int	errnum;
	int	i;

	if (!args[0])
	{
		print_list_prefix(my_env->list_env, "declare -x");
		return (SUCCESS);
	}
	i = 0;
	errnum = 0;
	while (args[i])
	{
		if (is_valid_export(args[i]) == 20)
			ft_lstadd_back(&my_env->list_env, ft_lstnew_gc(args[i]));
		else
			errnum ++;
		i++;
	}
	return (errnum);
}

int	is_valid_export(char *arg)
{
	if (ft_strchr(arg, '=') == NULL)
		return (0);
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') || !is_valid_name(arg))
	{
		printf("export: %s : not a valid identifier\n", arg);
		return (1);
	}
	return (20);
}

/*    name   A  word  consisting  only  of alphanumeric characters and under‐
              scores, and beginning with an alphabetic character or an  under‐
              score.  Also referred to as an identifier. */

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
