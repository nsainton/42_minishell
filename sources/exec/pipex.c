/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/30 14:40:35 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(t_data *d)
{
	d->index = 1;
	make_redirs(d, d->cmds[0]);
	if (which_builtin(d->cmds[0], d) == 127)
	{

		if (d->cmds[0]->command)
		{
			d->errnum = check_path(d->cmds[0], d->env);
			if (!d->errnum)
			{
				sub_dup2(d->cmds[0]->fd_in, d->cmds[0]->fd_out);
				exec_command(d, d->cmds[0]);
			}
			else
				ft_dprintf(2, "%s : %s\n", d->cmds[0]->command,
					strerror(d->errnum));
		}
	}
	return (d->errnum);
}

void	exec_command(t_data *d, t_command *cmd)
{
	d->pid = fork();
	if (d->pid < 0)
		ft_dprintf(2, "error : %s", strerror(errno));
	else if (d->pid == 0)
	{
		d->errnum = execve(cmd->path, (char *const *)make_command(cmd),
				envlist_to_arr(d->env->list_env));
		if (d->errnum)
			ft_dprintf(2, "%s : %s\n", cmd->command, strerror(errno));
		exit(d->errnum);
	}
}

void	exec_command_pipe(t_data *d, t_command *cmd)
{
	d->pid = fork();
	if (d->pid < 0)
		ft_dprintf(2, "error : %s", strerror(errno));
	else if (d->pid == 0)
	{
		if (d->index == 0)
			sub_dup2(cmd->fd_in, d->p[1]);
		else if (d->index == d->cmds_nb - 1)
			sub_dup2(d->prev_pipe, cmd->fd_out);
		else
			sub_dup2(d->prev_pipe, d->p[1]);
		if (which_builtin_exec(d->cmds[d->index], d) == 127)
			d->errnum = execve(cmd->path, (char *const *)make_command(cmd),
					envlist_to_arr(d->env->list_env));
		if (d->errnum)
			ft_dprintf(2, "%s : %s\n", cmd->command, strerror(errno));
		exit(d->errnum);
	}
	close_used_pipes(d, cmd);

}

int	exec_pipeline(t_data *d)
{
	d->prev_pipe = -1;
	d->index = -1;
	d->pid = gc_calloc(d->cmds_nb, sizeof(int));
	if (!d->pid)
		return (1);
	if (d->cmds_nb == 1)
		exec_one(d);
	while (++d->index < d->cmds_nb)
	{
		if (pipe(d->p) == -1)
			ft_dprintf(2, "error : %s", strerror(errno));
		make_redirs(d, d->cmds[d->index]);
		if (which_builtin(d->cmds[d->index], d) == 127)
		{
			if (d->cmds[d->index]->command)
			{
				d->errnum = check_path(d->cmds[d->index], d->env);
				if (!d->errnum)
					exec_command_pipe(d, d->cmds[d->index]);
				else
					ft_dprintf(2, "%s : %s\n", d->cmds[d->index]->command,
						strerror(d->errnum));
			}
		}
		d->prev_pipe = d->p[0];
	}
	if (d->cmds_nb > 1)
	{
		ft_dprintf(2, "J'attends la fin de exec pipeline\n");
		sub_dup2(d->save_in, d->save_out);
	}
	waitpid(-1, NULL, 0);

	close(d->p[0]);
	close(d->p[1]);
	ft_dprintf(2, "J'ai atteint la fin de exec pipeline\n");
	return (0);
}
