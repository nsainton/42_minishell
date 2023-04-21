/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/21 17:15:19 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_builtin(t_command *cmd, t_env *my_env)
{
	if (!ft_strncmp(cmd->command, "env", 4))
		return (print_env(my_env, cmd));
	if (!ft_strncmp(cmd->command, "export", 7))
		return (export_env(my_env, cmd));
	if (!ft_strncmp(cmd->command, "unset", 6))
		return (unset_env(my_env, cmd));
	if (!ft_strncmp(cmd->command, "pwd", 4))
		return (print_pwd(cmd));
	if (!ft_strncmp(cmd->command, "echo", 5))
		return (print_echo(cmd));
	return (127);
}
