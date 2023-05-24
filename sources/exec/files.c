/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:33:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/24 18:49:42 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirs(t_data *d, t_command *cmd)
{
	int	i;

	i = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!cmd->redirs)
		return (0);
	while (cmd->redirs[i].mode)
	{
		if (cmd->redirs[i].mode == 'i')
			d->errnum = get_infile(cmd, &cmd->redirs[i]);
		else if (cmd->redirs[i].mode == 'o')
			d->errnum = get_outfile_trunc(cmd, &cmd->redirs[i]);
		else if (cmd->redirs[i].mode == 'a')
			d->errnum = get_outfile_append(cmd, &cmd->redirs[i]);
		i ++;
	}
	return (0);
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
			ft_dprintf(2, "infile : %s\n", strerror(errno));
			return (errno);
		}
	}
	else
		c->fd_in = 0;
	r->fd = c->fd_in;
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
			ft_dprintf(2, "outfile : %s\n", strerror(errno));
			return (errno);
		}
	}
	else
		c->fd_out = 1;
	r->fd = c->fd_out;
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
			ft_dprintf(2, "outfile : %s\n", strerror(errno));
			return (errno);
		}
	}
	else
		c->fd_out = 1;
	r->fd = c->fd_out;
	return (0);
}

void	here_doc(char **limiters, int nb)
{
	int		file;
	char	*buf;
	int		i;

	i = 0;
	file = open(".heredoc", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (file < 0)
		ft_dprintf(2, "heredoc : %s\n", strerror(errno));
	while (i != nb)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (!buf)
			break ;
		gc_add(buf);
		if (!ft_strncmp(limiters[i], buf, ft_strlen(limiters[i]))
			&& ft_strlen(limiters[i]) + 1 == ft_strlen(buf))
			i++;
		if (i == nb)
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free_node(buf);
	}
	free_node(buf);
	close(file);
}
