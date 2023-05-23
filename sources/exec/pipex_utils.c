/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:05 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/22 17:28:13 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(write_fd, STDOUT_FILENO);
}

void	close_used_pipes(t_data *d, t_command *cmd)
{
	if (d->index - 2 >= 0 && d->index + 1 <= d->pipes_nb)
	{
		close(d->pipes[d->index - 2]);
		close(d->pipes[d->index + 1]);
	}
	else if (d->index == 0)
	{
		close(cmd->fd_in);
		close(d->pipes[d->index + 1]);
	}
	else if (d->index == d->pipes_nb)
	{
		close(d->pipes[d->index - 2]);
		close(cmd->fd_out);
	}
}