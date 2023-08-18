/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:11:33 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 13:32:29 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_unused_pipe(struct s_ncommand *command)
{
	if (command->input_fd != STDIN_FILENO && s_close(command->input_fd))
		return (1);
	if (command->output_fd != STDOUT_FILENO && s_close(command->output_fd))
		return (1);
	return (0);
}

/*
	Here we use heredoc->read_fd instead of heredoc->fd because this
	function runs before any redirection occurs (that is, just after forking
	the process).
*/
static int	close_unused_heredocs(struct s_ncommand *command)
{
	size_t	len;
	size_t	i;

	len = tablen(command->heredocs, sizeof * command->heredocs);
	if (! len)
		return (0);
	i = 0;
	while (i < len)
	{
		if (s_close((command->heredocs + i)->read_fd))
			return (1);
		i ++;
	}
	return (0);
}

/*
	A pipeline is actually an array of commands. These commands may have open
	pipes or heredocs for example and if the command doesn't close the pipes
	This function's goal is to close all pipes and heredoc fds that don't
	belong to it.
	If we don't do such a thing before running the command, the pipes might
	stay open in another command (actually all the commands that are not
	concerned with it and that didn't bother to close it). Thus, the readers
	connected to the read end of the pipe may wait indefinitely even if the
	only writter concerned with the pipe is done writting.
*/
int	cleanup_before_exec(struct s_ncommand *command, const size_t index, \
const size_t commands_nb)
{
	size_t	i;

	i = 0;
	while (i < commands_nb)
	{
		if (i == index)
		{
			i ++;
			continue ;
		}
		if (close_unused_pipe(command) || close_unused_heredocs(command))
			return (1);
		i ++;
	}
	return (0);
}
