/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:16:50 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/24 16:21:40 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirs(t_data *d, t_command *cmd)
{
	int	i;
	i = 0;
	d->errnum = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!cmd->redirs && !cmd->heredocs)
		return (0);
	if (cmd->heredocs)
	{
		//ft_printf("There are some heredocs here \n");
		heredoc(cmd);
	}
	while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->mode == 'r' || cmd->redirs[i]->mode == 'b')
			d->errnum = get_infile(cmd, cmd->redirs[i]);
		if (cmd->redirs[i]->mode == 'w')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_TRUNC);
		else if (cmd->redirs[i]->mode == 'a')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_APPEND);
		i ++;
	}

	return (d->errnum);
}