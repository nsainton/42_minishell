/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/31 14:17:35 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(t_data *d)
{
	d->index = 1;
	make_redirs(d, d->cmds[0]);
	if (d->cmds[0]->command && is_builtin(d->cmds[0], d) == 1)
		exec_builtin(d->cmds[0], d);
	else if (d->cmds[0]->command)
	{
		d->pid[0] = fork();
		if (d->pid[0] < 0)
			ft_dprintf(2, "error : %s", strerror(errno));
		else if (d->pid[0] == 0)
		{
			if (d->cmds[0]->fd_in != STDIN_FILENO)
				dupnclose(d->cmds[0]->fd_in, STDIN_FILENO);
			if (d->cmds[0]->fd_out != STDOUT_FILENO)
				dupnclose(d->cmds[0]->fd_out, STDOUT_FILENO);
			if (!is_builtin(d->cmds[0], d) || is_builtin(d->cmds[0], d) == 2)
			{
				if (check_path(d->cmds[0], d->env))
				{
					ft_dprintf(2, "%s : Command not found\n",
						d->cmds[0]->command);
					exit(1);
				}
				d->errnum = execve(d->cmds[0]->path,
						(char *const *)make_command(d->cmds[0]),
						envlist_to_arr(d->env->list_env));
				if (d->errnum)
				{
					ft_dprintf(2, "%s : %s -> path : %s\n", d->cmds[0]->command, strerror(errno), d->cmds[0]->path);
					exit(errno);
				}
			}
			exit(d->errnum);
		}
	}
	if (d->cmds[0]->fd_in != STDIN_FILENO)
		close(d->cmds[0]->fd_in);
	if (d->cmds[0]->fd_out != STDOUT_FILENO)
		close(d->cmds[0]->fd_out);
	keep_exit_status(d->errnum);
	return (d->errnum);
}

