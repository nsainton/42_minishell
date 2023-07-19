/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:05 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/25 23:36:42 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wait_for_childs(t_data	*d)
{
	int	i;
	int	w;
	int status;

	i = 0;
	status = 0;
	while (i < d->cmds_nb && d->pid[i])
	{
		w = waitpid(d->pid[i], &status, WUNTRACED | WCONTINUED);
		if (w == -1) {
			perror("waitpid");
			//exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
			status = WEXITSTATUS(status);
		} else if (WIFSIGNALED(status)) {
			printf("killed by signal %d\n", WTERMSIG(status));
			status = WTERMSIG(status) + 128;
		} else if (WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
			status = WSTOPSIG(status) + 128;
		} else if (WIFCONTINUED(status)) {
			printf("continued\n");
		}
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

void	sub_dup2(int read_fd, int write_fd)
{
	if (dup2(read_fd, STDIN_FILENO) == -1)
		ft_dprintf(2, "dup2 read fd (%d)error: %s\n", read_fd, strerror(errno));
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		ft_dprintf(2, "dup2 write fd error: %s\n", strerror(errno));

}

void	close_used_pipes(t_data *d, t_command *cmd)
{
	if (d->index == d->cmds_nb - 1)
	{
		close(cmd->fd_out);
		close(d->prev_pipe);
		close(d->p[1]);
	}
	else if (d->index == 0)
	{
		close(cmd->fd_in);
		close(d->p[1]);
	}
	else
	{
		close(d->p[1]);
		close(d->prev_pipe);
	}
}
