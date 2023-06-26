/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/25 23:44:20 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *cmd, t_data *d)
{
	if (!ft_strncmp(cmd->command, "export", 7))
		return (d->errnum = export_env(d, cmd));
	if (!ft_strncmp(cmd->command, "unset", 6))
		return (unset_env(d, cmd));
	if (!ft_strncmp(cmd->command, "cd", 3))
		return (cd(cmd, d));
	if (!ft_strncmp(cmd->command, "exit", 5))
		return(exit_builtin(cmd->args, &d->errnum));
	if (!ft_strncmp(cmd->command, "env", 4))
		return (print_env(d, cmd));
	if (!ft_strncmp(cmd->command, "pwd", 4))
		return (print_pwd(cmd));
	if (!ft_strncmp(cmd->command, "echo", 5))
		return (print_echo(d, cmd));
	if (!ft_strncmp(cmd->command, "$?", 3))
		return (print_exit_status(d, cmd));
	return (127);
}

int	is_builtin(t_command *cmd, t_data *d)
{
	char exit[2];

	*exit = ES;
	*(exit + 1) = 0;
	if (!ft_strncmp(cmd->command, "export", 7))
		return (1);
	if (!ft_strncmp(cmd->command, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd->command, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd->command, "exit", 5))
		return (1);
	if (!ft_strncmp(cmd->command, "env", 4))
		return (2);
	if (!ft_strncmp(cmd->command, "pwd", 4))
		return (2);
	if (!ft_strncmp(cmd->command, "echo", 5))
		return (2);
	if (!ft_strncmp(cmd->command, exit , 1))
		return (2);
	return (d->errnum = 0);
}
