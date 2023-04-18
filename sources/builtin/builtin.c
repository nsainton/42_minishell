/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/18 12:55:02 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_builtin(char *cmd, char **args, t_env *my_env)
{
	if (!ft_strncmp(cmd, "env", 4))
		return (print_env(my_env, args));
	if (!ft_strncmp(cmd, "export", 7))
		return (export_env(my_env, args));
	if (!ft_strncmp(cmd, "unset", 6))
		return (unset_env(my_env, args));
	if (!ft_strncmp(cmd, "pwd", 4))
		return (print_pwd(args));
	return (127);
}