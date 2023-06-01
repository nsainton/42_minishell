/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:47:01 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/31 11:56:10 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_data(t_data *d)
{
	d->prev_pipe = -1;
	d->index = -1;
	d->pid = gccalloc(d->cmds_nb, sizeof(int));
	if (!d->pid)
		return (1);
	d->cmds_nb = ft_arrlen((void *)d->cmds);
	if (!d->cmds_nb)
		return (1);
	return (0);
}

int	exec_pipeline(t_data *d)
{
	if (set_data(d))
		return (1);
	if (d->cmds_nb == 1)
		exec_one(d);
	while (++d->index < d->cmds_nb)
	{
		if (pipe(d->p) == -1)
			ft_dprintf(2, "error : %s", strerror(errno));
		make_redirs(d, d->cmds[d->index]);
		d->pid[d->index] = fork();
		if (d->pid[d->index] == 0)
		{
			if (d->cmds[d->index]->fd_in != STDIN_FILENO)
				dupnclose(d->cmds[d->index]->fd_in, STDIN_FILENO);
			if (d->cmds[d->index]->fd_out != STDOUT_FILENO)
				dupnclose(d->cmds[d->index]->fd_out, STDOUT_FILENO);
			dup_pipe(d);
			if (is_builtin(d->cmds[d->index], d) == 2)
				exit(exec_builtin(d->cmds[d->index], d));
			else if (is_builtin(d->cmds[d->index], d) == 1)
				exit(0);
			else if (!is_builtin(d->cmds[d->index], d))
			{
				if (check_path(d->cmds[d->index], d->env))
				{
					ft_dprintf(2, "%s : Command not found\n",
						d->cmds[d->index]->command);
					exit(1);
				}
				d->errnum = execve(d->cmds[d->index]->path,
						(char *const *)make_command(d->cmds[d->index]),
						envlist_to_arr(d->env->list_env));
				if (d->errnum)
				{
					ft_dprintf(2, "%s : %s\n", d->cmds[d->index]->command, strerror(errno));
					exit(d->errnum);
				}
			}
		}
		else if (d->pid[d->index] > 0)
		{
			close(d->p[1]);
			if (d->prev_pipe != -1)
				close(d->prev_pipe);
			d->prev_pipe = d->p[0];
			if (d->cmds[d->index]->fd_in != STDIN_FILENO)
				close(d->cmds[d->index]->fd_in);
			if (d->cmds[d->index]->fd_out != STDOUT_FILENO)
				close(d->cmds[d->index]->fd_out);
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
	if (d->index != d->cmds_nb - 1)
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
/* pipe(data->fd);
			data->pid[i] = fork();
			if (data->pid[i] == 0)
			{
				select_pipe(data, i);
				if (open_files(data) == 1)
					exit (1) ;
				if (unforkable_builtins(data->cmd_tab[0]) == 1)
					exit(0);
				if (cmd && !is_builtin(data->cmd_tab[0]))
					execve(cmd, data->cmd_tab, data->new_env);
				else if (is_builtin(data->cmd_tab[0]))
				{
					// g_exit_code = 0;
					exec_builtin(data, data->cmd_tab[0]);
					exit_fork(data, cmd);
				}
				cmd_not_found(data->cmd_tab[0]);
				exit_fork(data, cmd);
			}
			else if (data->pid[i] > 0)
			{
				close(data->fd[1]);
				if (data->prev_pipe != -1)
					close(data->prev_pipe);
				data->prev_pipe = data->fd[0];
			}
		}
		free_data(data, cmd);
	}
	exec_waitpid(data);
	close(data->fd[0]);
	close(data->fd[1]);
} */