/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:33:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/26 12:13:49 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_command *command)
{
	struct s_heredoc_infos	hd;
	size_t					len;
	size_t					i;
	int						err;

	if (! *command->heredocs)
		return (EXIT_SUCCESS);
	len = tablen(*command->heredocs, sizeof **command->heredocs);
	if (! len)
		return (EXIT_SUCCESS);
	i = 0;
	reinit_sigs();
	while (i < len)
	{
		err = getheredoc(&hd, *command->heredocs + i);
		if (err > 0)
			return (EXIT_FAILURE);
		if (! err & (dup2(hd.read_fd, (*command->heredocs + i)->fd) == -1))
			err = 1;
		close(hd.read_fd);
		if (err == 1)
			return (EXIT_FAILURE);
		i++;
	}
	init_sigs();
	return (EXIT_SUCCESS);
}
