/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:47:01 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/25 23:48:10 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_data(t_data *d)
{
	d->prev_pipe = -1;
	d->index = -1;
	d->pid = gccalloc(d->cmds_nb, sizeof(int));
	if (!d->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	exec_pipeline(t_data *d)
{
	if (set_data(d))
		return (1);
	if (d->cmds_nb == 1)
	{
		if (exec_one(d) != 0)
			return (0);
	}
	while (++d->index < d->cmds_nb)
	{
		if (pipe(d->p) == -1)
			ft_dprintf(2, "error : %s", strerror(errno));
		if (make_redirs(d, d->cmds[d->index]))
			d->index ++;
		if (d->cmds[d->index]->fd_out != STDOUT_FILENO && d->index != d->cmds_nb - 1)
			d->cmds[d->index]->last = 1;
		d->pid[d->index] = fork();
		if (d->pid[d->index] == 0 && d->cmds[d->index]->command)
		{
			if (d->cmds[d->index]->fd_in != STDIN_FILENO)
				dupnclose(d->cmds[d->index]->fd_in, STDIN_FILENO);
			if (d->cmds[d->index]->fd_out != STDOUT_FILENO)
				dupnclose(d->cmds[d->index]->fd_out, STDOUT_FILENO);
			dup_pipe(d);
			if (is_builtin(d->cmds[d->index], d) == 1)
				exit_free_gc(exec_builtin(d->cmds[d->index], d));
			else if (!is_builtin(d->cmds[d->index], d))
			{
				if (check_path(d->cmds[d->index], d->env))
				{
					ft_dprintf(2, "%s : Command not found\n",
						d->cmds[d->index]->command);
					exit_free_gc(127);
				}
				d->errnum = execve(d->cmds[d->index]->path,
						(char *const *)make_command(d->cmds[d->index]),
						envlist_to_arr(d->env->list_env));
				if (d->errnum)
				{
					ft_dprintf(2, "%s : %s\n", d->cmds[d->index]->command, strerror(errno));
					exit_free_gc(d->errnum);
				}
			}
		}
		else if (d->pid[d->index] > 0 && d->cmds[d->index]->command)
		{
			close(d->p[1]);
			if (d->prev_pipe != -1)
				close(d->prev_pipe);
			d->prev_pipe = d->p[0];
			if (d->cmds[d->index]->fd_in != STDIN_FILENO)
				close(d->cmds[d->index]->fd_in);
			if (d->cmds[d->index]->fd_out != STDOUT_FILENO)
				close(d->cmds[d->index]->fd_out);
			if (d->cmds[d->index]->last == 1)
			{
				d->cmds = &d->cmds[d->index + 1];
				d->cmds_nb -= d->index + 1;
				close (d->p[0]);
				close (d->p[1]);
				exec_pipeline(d);
			}
		}
	}
	wait_for_childs(d);
	
	if (d->cmds_nb > 1)
	{
		close (d->p[0]);
		close (d->p[1]);
	}
	return (0);
}


void	dup_pipe(t_data *d)
{
	if (d->index != d->cmds_nb - 1 && !d->cmds[d->index]->last)
		dup2(d->p[1], STDOUT_FILENO);
	if (d->index != 0)
		dupnclose(d->prev_pipe, STDIN_FILENO);
	close(d->p[0]);
	close(d->p[1]);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	keep_exit_status(const int exit_status)
{
	static int	status;

	if (exit_status < 0)
		return (status);
	status = exit_status;
	return (0);
}
