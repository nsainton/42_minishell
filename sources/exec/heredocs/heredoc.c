/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:33:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 10:28:05 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_heredocs(const struct s_ncommand *command, \
const struct s_tab *env)
{
	size_t					i;
	size_t					len;
	int						err;
	struct s_heredoc_infos	hd;

	if (! command->heredocs)
		return (0);
	len = tablen(command->heredocs, sizeof * command->heredocs);
	i = 0;
	while (i < len)
	{
		err = get_heredoc(&hd, command->heredocs + i, env);
		if (err > 0)
			return (1);
		if (! err)
			(command->heredocs + i)->read_fd = hd.read_fd;
		else
			(command->heredocs + i)->read_fd = -1;
		i ++;
	}
	return (0);
}

int	heredocs(const struct s_ncommand *commands, const size_t commands_nb, \
const struct s_tab *env)
{
	size_t			i;

	i = 0;
	while (i < commands_nb)
	{
		if (get_heredocs(commands + i, env))
			return (1);
		i ++;
	}
	return (0);
}
