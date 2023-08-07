/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:33:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/07 12:09:07 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_list(int *descriptors_list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(descriptors_list + i) = -1;
		i ++;
	}
}

static int	connect_heredoc_fds(int *descriptors_list, const int command_fd, \
const int heredoc_fd)
{
	if (*(descriptors_list) == -1)
	{
		*(descriptors_list) = command_fd;
		*(descriptors_list + 1) = heredoc_fd;
		return (0);
	}
	if (close(*(descriptors_list + 1)) == -1)
	{
		*(descriptors_list + 1) = -1;
		return (1);
	}
	*(descriptors_list + 1) = heredoc_fd;
	return (0);
}

static int	update_list(int *descriptors_list, const int command_fd, \
const int heredoc_fd)
{
	size_t	len;
	size_t	i;

	len = tablen(descriptors_list, 2 * sizeof * descriptors_list);
	i =  0;
	while (i < 2 * len && *(descriptors_list + i) != -1 \
	&& *(descriptors_list + i) != command_fd)
		i += 2;
	if (i == 2 * len)
		return (1);
	return (connect_heredoc_fds(descriptors_list + i, command_fd, heredoc_fd));
}

static int	get_heredocs(int *descriptors_list, \
const struct s_command *command, const struct s_env *env, \
const size_t number)
{
	struct s_heredoc_infos	hd;
	size_t					i;
	int						err;

	i = 0;
	while (i < len)
	{
		err = getheredoc(&hd, *command->heredocs + i, env);
		if (err > 0)
			return (1);
		if (! err && \
		update_list(descriptors_list, *(command->heredocs + i)->fd, hd.read_fd))
		{
			clear_list(descriptors_list);
			return (1);
		}
		i ++;
	}
	return (0);
}

static int	match_fds(int *descriptors_list)
{
	size_t	len;
	size_t	i;

	len = tablen(descriptors_list, 2 * sizeof * descriptors_list);
	i = 0;
	while (i < 2 * len)
	{
		if (
int	heredoc(const struct s_command *command, const struct s_env *env)
{
	struct s_heredoc_infos	hd;
	size_t					len;
	size_t					i;
	int						err;
	int						*descriptors_list;

	if (! *command->heredocs)
		return (EXIT_SUCCESS);
	len = tablen(*command->heredocs, sizeof **command->heredocs);
	if (! len)
		return (EXIT_SUCCESS);
	descriptors_list = ft_calloc(len * (2 * sizeof * descriptors_list + 1));
	if (! descriptors_list)
		return (1);
	init_list(descriptors_list, 2 * len);
	if (get_heredocs(descriptors_list, command, env, len))
		return (1);
	/*
	i = 0;
	while (i < len)
	{
		err = getheredoc(&hd, *command->heredocs + i, env);
		if (err > 0)
			return (EXIT_FAILURE);
		if (! err && \
		update_list(descriptors_list, *(command->heredocs + i)->fd, hd.read_fd)
			return (EXIT_FAILURE);
		close(hd.read_fd);
		if (err == 1)
			return (EXIT_FAILURE);
		i++;
	}
	*/
	init_sigs();
	return (EXIT_SUCCESS);
}
