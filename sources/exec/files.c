/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:33:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/23 11:51:30 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirs(t_data *d, t_command *cmd)
{
	int	i;
	/*
	struct s_ncommand	com;

	ft_bzero(&com, sizeof com);
	com.command = cmd->command;
	com.args = cmd->args;
	ft_printf("Before r\n");
	com.redirs = *cmd->redirs;
	ft_printf("After r and Before h\n");
	com.heredocs = *cmd->heredocs;
	ft_printf("After h\n");
	*/
	i = 0;
	d->errnum = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!cmd->redirs && !cmd->heredocs)
	{
		/*
		ft_printf("No redirs and no heredocs here\n");
		ft_printf("This is the command\n");
		print_command(&com, 1);
		*/
		return (0);
	}
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

int	get_infile(t_command *c, t_redir *r)
{
	if (c->fd_in != 0)
		close(c->fd_in);
	if (r->file)
	{
		c->fd_in = open(r->file, O_RDONLY);
		if (c->fd_in < 0)
		{
			ft_dprintf(2, "infile : %s : %s\n", r->file, strerror(errno));
			return (errno);
		}
	}
	else
		c->fd_in = 0;
	return (0);
}

int	get_outfile(t_command *c, t_redir *r, const int mode)
{

	if (c->fd_out != 1)
		close(c->fd_out);
	if (r->file)
	{
		c->fd_out = open(r->file, O_CREAT | O_RDWR | mode, 0000644);
		if (c->fd_out < 0)
		{
			ft_dprintf(2, "outfile : %s : %s\n", r->file, strerror(errno));
			return (errno);
		}
	}
	else
		c->fd_out = 1;
	return (0);
}
