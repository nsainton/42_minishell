/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:05 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/27 12:08:46 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (w == -1)
		{
			//perror("waitpid");
			//exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			printf("exited, status=%d\n", WEXITSTATUS(status));
			status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
				ft_printf("Quit\n");
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
		keep_exit_status(status);
		i ++;
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
	close(d->p[1]);
	if (d->prev_pipe != -1)
		close(d->prev_pipe);
	d->prev_pipe = d->p[0];
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}
