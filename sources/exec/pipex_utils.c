/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:05 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/24 19:13:36 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (read_fd != STDIN_FILENO)
	{
		if (dup2(read_fd, STDIN_FILENO) == -1)
			ft_dprintf(2, "dup2 read fd error: %s\n", strerror(errno));
	}
	if (write_fd != STDOUT_FILENO)
	{
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			ft_dprintf(2, "dup2 write fd error: %s\n", strerror(errno));
	}
}

void	close_used_pipes(t_data *d, t_command *cmd)
{
	if (d->index == d->cmds_nb - 1)
	{
		close(cmd->fd_out);
		close(d->prev_pipe);
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