/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/20 15:28:22 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(t_data *d)
{
	d->index = 1;
	if (make_redirs(d, d->cmds[0]) != 0)
		return(d->errnum);
	if (d->cmds[0]->command && is_builtin(d->cmds[0], d))
		exec_builtin_parent(d, d->cmds[0]);	
	else if (d->cmds[0]->command)
	{
		d->pid[0] = fork();
		if (d->pid[0] < 0)
			ft_dprintf(2, "error : %s", strerror(errno));
		else if (d->pid[0] == 0)
			exec_w_execve(d, d->cmds[0]);
	}
	ft_printf("This is my errnum : %d\n", d->errnum);
	keep_exit_status(d->errnum);
	return (d->errnum);
}

int	exec_builtin_parent(t_data *d, t_command *cmd)
{
	if (strcmp(cmd->command, "exit"))
	{	
		d->save_in = dup(STDIN_FILENO);
		d->save_out = dup(STDOUT_FILENO);
	}
	dup_in_out(cmd->fd_in, cmd->fd_out);
	keep_exit_status(exec_builtin(cmd, d));
	dupnclose(d->save_in, STDIN_FILENO);
	dupnclose(d->save_out, STDOUT_FILENO);
	return (0);
}

void	exec_w_execve(t_data *d, t_command *cmd)
{
	dup_in_out(cmd->fd_in, cmd->fd_out);
	if (check_path(cmd, d->env))
	{
		ft_dprintf(2, "%s : Command not found\n",
			cmd->command);
		exit_free_gc(127);
	}
	d->errnum = execve(cmd->path,
			(char *const *)make_command(cmd), envlist_to_arr(d->env->list_env));
	if (d->errnum)
	{
		ft_dprintf(2, "%s : %s -> path : %s\n", cmd->command, strerror(errno), cmd->path);
		exit_free_gc(errno);
	}
}