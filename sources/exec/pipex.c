/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/02 16:05:19 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	sub_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(write_fd, STDOUT_FILENO);
}

void	close_used_pipes(t_pipex *p)
{
	if (p->i - 2 >= 0 && p->i + 1 <= p->pipes_nb)
	{
		close(p->pipes[p->i - 2]);
		close(p->pipes[p->i + 1]);
	}
	else if (p->i == 0)
	{
		close(p->infile);
		close(p->pipes[p->i + 1]);
	}
	else if (p->i == p->pipes_nb)
	{
		close(p->pipes[p->i - 2]);
		close(p->outfile);
	}
}

void	exec_command(t_pipex	p)
{
	p.pid = fork();
	if (p.pid < 0)
		ft_error(NULL, errno);
	else if (p.pid == 0)
	{
		if (p.i == 0)
			sub_dup2(p.infile, p.pipes[1]);
		else if (p.i == p.pipes_nb)
			sub_dup2(p.pipes[p.i - 2], p.outfile);
		else
			sub_dup2(p.pipes[p.i - 2], p.pipes[p.i + 1]);
		p.cmds = ft_split(p.cmd, ' ');
		p.path = get_right_path(p.cmds[0], &p);
		if (!p.path)
		{
			ft_free_pip(p.cmds, NULL);
			ft_error(NULL, errno);
		}
		if (execve(p.path, p.cmds, environ))
		{
			ft_free_pip(p.cmds, &p);
			ft_error(NULL, errno);
		}
	}
	close_used_pipes(&p);
}
 */

void	go_pipe(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->pipes_nb)
	{
		if (pipe(d->pipes + i) < 0)
		{
			free_gc();
			exit(errno); // ?oui
		}
		i = i + 2;
	}
}

int	exec_pipeline(t_data	*d)
{
	int		i;

	if (d->cmds_nb == 0)
		return (1);
	i = 0;
	while (i < d->cmds_nb)
	{
		get_infile(d->cmds[i]);
		get_outfile(d->cmds[i]);
		if (d->cmds[i]->command)
			exec_command(d);

		i++;
	}

	d->pipes_nb = (d->cmds_nb - 1) * 2;
	d->pipes = gccalloc(d->pipes_nb, sizeof(int));
	if (!d->pipes)
	{
		ft_dprintf(2, "error : malloc has failed");
		return (errno);
	}
	go_pipe(d);
//	REPRENDRE ICI :
/* 	i = p.here_doc - 1;
	p.i = 0;
	while (++i < p.cmds_nb + p.here_doc)
	{
		p.cmd = p.args[i + 2];
		exec_command(p);
		p.i += 2;
	}
	waitpid(-1, NULL, 0);
	free(p.pipes);
	return (0); */
}