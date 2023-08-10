/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:00:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/10 12:43:22 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_data(t_data *d)
{
	d->prev_pipe = -1;
	//d->index = -1;
	d->save_in = -1;
	d->save_out = -1;
	d->pid = gccalloc(d->cmds_nb, sizeof(int));
	if (!d->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	run_command(struct s_data *data, int command_index)
{
	if (pipe(data->p) == -1)
		ft_dprintf(2, "error : %s", strerror(errno));
	if (data->cmds[command_index]->fd_out != STDOUT_FILENO && \
	command_index != data->cmds_nb - 1)
		data->cmds[command_index]->last = 1;
	data->pid[command_index] = fork();
	reinit_sigs();
	exec_command_in_pipeline(data, command_index);
}

int	exec_pipeline(t_data *d)
{
	int	command_index;

	if (save_stds('s'))
		return (EXIT_FAILURE); 
	if (set_data(d))
		return (1);
	command_index = 0;
	/* Here is the function to read all the redocs */
	if (d->cmds_nb == 1)
		exec_one(d);
	while (command_index < d->cmds_nb)
	{
		if (make_redirs(d, d->cmds[command_index]))
		{
			if (command_index != d->cmds_nb - 1)
			{
				close_used_pipes(d, d->cmds[command_index]);
				command_index ++;
			}
			else
				break ;
		}
		run_command(d, command_index);
	/* 	safe_close(d->cmds[0]->fd_in);
		safe_close(d->cmds[0]->fd_out); */
	}
	wait_for_childs(d);
	init_sigs();
	if (d->cmds_nb > 1)
	{
		safe_close(d->p[0]);
		safe_close(d->p[1]);
	}
	if (save_stds('r'))
		return (EXIT_FAILURE);
	return (0);
}

void	exec_command_in_pipeline(t_data *d, const int command_index)
{
	int errnum;

	if (d->pid[command_index] == 0 && d->cmds[command_index]->command)
	{
		signal(SIGQUIT, SIG_DFL);
		dup_in_out(d->cmds[command_index]->fd_in, d->cmds[command_index]->fd_out);
		dup_list(d->cmds[command_index]->fds);
		dup_pipe(d, command_index);
		if (is_builtin(d->cmds[command_index], d) == 1)
		{
			errnum = exec_builtin(d->cmds[command_index], d);
			close_list(d->cmds[command_index]->fds);
			save_stds('c');
			exit_free_gc(errnum);
		}
		else if (!is_builtin(d->cmds[command_index], d))
			exec_w_execve(d, d->cmds[command_index]);
	}
	else if (d->pid[command_index] > 0 && d->cmds[command_index]->command)
	{
		close_used_pipes(d, d->cmds[command_index]);
		close_list(d->cmds[command_index]->fds);
		safe_close (d->cmds[command_index]->fd_in);
		safe_close (d->cmds[command_index]->fd_out);
		/* if (d->cmds[d->index]->last == 1)
		{
			//d->cmds = &d->cmds[d->index + 1];
			//d->cmds_nb -= d->index + 1;
			safe_close (d->p[0]);
			safe_close (d->p[1]);
			//exec_pipeline(d);
		} */
	}
}
