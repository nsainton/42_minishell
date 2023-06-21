/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:33:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/21 22:35:21 by nsainton         ###   ########.fr       */
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
		here_doc(cmd);
	}
	while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->mode == 'r' || cmd->redirs[i]->mode == 'b')
			d->errnum = get_infile(cmd, cmd->redirs[i]);
		if (cmd->redirs[i]->mode == 'w')
			d->errnum = get_outfile_trunc(cmd, cmd->redirs[i]);
		else if (cmd->redirs[i]->mode == 'a')
			d->errnum = get_outfile_append(cmd, cmd->redirs[i]);
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
		c->fd_in = open(r->file, O_RDWR);
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

int	get_outfile_trunc(t_command *c, t_redir *r)
{

	if (c->fd_out != 1)
		close(c->fd_out);
	if (r->file)
	{
		c->fd_out = open(r->file, O_CREAT | O_RDWR | O_TRUNC, 0000644);
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

int	get_outfile_append(t_command *c, t_redir *r)
{
	if (c->fd_out != 1)
		close(c->fd_out);
	if (r->file)
	{
		c->fd_out = open(r->file, O_CREAT | O_RDWR | O_APPEND, 0000644);
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

void	here_doc(t_command *c)
{
	char	*buf;
	int		i;
	int count;
	char *name;

	name = gc_strdup(".heredoc0");
	if (! name)
		return ;
	i = 0;
	//count = ft_arrlen((void *) c->heredocs) - 1;
	/*
	count = 0;
	while (c->heredocs[count])
		count++;
	*/
	count = tablen(*c->heredocs, sizeof **(c->heredocs));
	while (c->heredocs[i])
	{
		name[8] += 1;
		c->heredocs[i]->fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0000644);
		if (c->heredocs[i]->fd < 0)
			ft_dprintf(2, "heredoc : %s\n", strerror(errno));
		ft_dprintf(2, "heredoc : %s\n count :%d", strerror(errno), count);
		while (1)
		{
			write(1, "> ", 2);
			buf = get_next_line(0);
			if (!buf)
				break ;
			gc_add(buf);
			ft_dprintf(2, "heredoc limiter: %s\n", c->heredocs[i]->limiter);
			if (!ft_strncmp(c->heredocs[i]->limiter, buf, ft_strlen(c->heredocs[i]->limiter))
				&& ft_strlen(c->heredocs[i]->limiter) + 1 == ft_strlen(buf))
			{
				free_node(buf);
				close(c->heredocs[i]->fd);
				break ;
			}
			else if (buf)
			{
				write(c->heredocs[i]->fd, buf, ft_strlen(buf));
				write(c->heredocs[i]->fd, "\n", 1);
				free_node(buf);
			}
		}

		if (i == count - 1)
			break ;
		else
		{
			close(c->heredocs[i]->fd);
			i ++;
		}
	}
	c->fd_in = c->heredocs[i]->fd;
	close(c->heredocs[i]->fd);
}
