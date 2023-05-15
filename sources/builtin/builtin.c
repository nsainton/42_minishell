/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/11 13:22:17 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_builtin(t_command *cmd, t_data *d)
{
	if (!ft_strncmp(cmd->command, "env", 4))
		return (print_env(d, cmd));
	if (!ft_strncmp(cmd->command, "export", 7))
		return (export_env(d, cmd));
	if (!ft_strncmp(cmd->command, "unset", 6))
		return (unset_env(d, cmd));
	if (!ft_strncmp(cmd->command, "pwd", 4))
		return (print_pwd(cmd));
	if (!ft_strncmp(cmd->command, "echo", 5))
		return (print_echo(d, cmd));
	if (!ft_strncmp(cmd->command, "cd", 3))
		return (cd(cmd, d));
	if (!ft_strncmp(cmd->command, "$?", 3))
		return (print_exit_status(d, cmd));
	if (!ft_strncmp(cmd->command, "exit", 5))
	{
		free_gc();
		exit(0);
	}
	return (127);
}
