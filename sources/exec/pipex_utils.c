/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:01:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 16:02:05 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_status(int status, const int cmds_number, const int rank)
{
	if (WIFEXITED(status))
	{
		printf("exited, status=%d\n", WEXITSTATUS(status)); //Don't forget to remove me
		status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			if (rank == cmds_number)
				ft_printf("Quit (core dumped)\n");
		}
		else
			ft_printf("killed by signal %d\n", WTERMSIG(status));
		status = WTERMSIG(status) + 128;
	}
	else if (WIFSTOPPED(status))
	{
		//printf("stopped by signal %d\n", WSTOPSIG(status));
		status = WSTOPSIG(status) + 128;
	}
	else if (WIFCONTINUED(status))
		printf("continued\n");
	return (status);
}

void	wait_for_childs(t_data	*d)
{
	int	i;
	int	w;
	int	status;

	i = 0;
	status = 0;
	while (i < d->cmds_nb && d->pid[i])
	{
		w = waitpid(d->pid[i], &status, WUNTRACED | WCONTINUED);
		i ++;
		if (w == -1)
			continue ;
		status = update_status(status, d->cmds_nb, i);
		keep_exit_status(status);
	}
}

char	**make_command(t_command	*cmd)
{
	char	**full_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_cmd = gccalloc(ft_arrlen((void **) cmd->args) + 2, sizeof (char *));
	full_cmd[j++] = gc_strdup(cmd->command);
	i = 0;
	while (cmd->args[i])
	{
		full_cmd[j++] = gc_strdup(cmd->args[i]);
		i ++;
	}
	full_cmd[j] = NULL;
	i = 0;
	return (full_cmd);
}

void	close_used_pipes(t_data *d, t_command *cmd)
{
	if (d->p[1] > 2)
		close(d->p[1]);
	if (d->prev_pipe > 2)
		close(d->prev_pipe);
	d->prev_pipe = d->p[0];
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}
