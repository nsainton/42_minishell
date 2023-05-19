/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:33:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/18 18:04:24 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirs(t_data *d, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirs[i])
	{
		cmd->fd_in = open(cmd->in, O_RDWR);
		if (cmd->fd_in < 0)
		{
			ft_dprintf(2, "infile : %s\n", strerror(errno));
			return (1);
		}
	}
	else
		cmd->fd_in = 0;
	if (cmd->out)
	{
		cmd->fd_out = open(cmd->out, O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (cmd->fd_out < 0)
		{
			ft_dprintf(2, "outfile : %s\n", strerror(errno));
			return (1);
		}
	}
	else
		cmd->fd_out = 1;
	return (0);
}
void	get_infile(t_command *c)
{
	if (c->in)
	{
		c->fd_in = open(c->in, O_RDWR);
		if (c->fd_in < 0)
			ft_dprintf(2, "infile : %s\n", strerror(errno));
	}
	else
		c->fd_in = 0;
}

void	get_outfile(t_command *c)
{
	if (c->out)
	{
		c->fd_out = open(c->out, O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (c->fd_out < 0)
			ft_dprintf(2, "outfile : %s\n", strerror(errno));
	}
	else
		c->fd_out = 1;
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
