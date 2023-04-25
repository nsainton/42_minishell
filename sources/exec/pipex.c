/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/25 17:06:55 by avedrenn         ###   ########.fr       */
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

void	go_pipe(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->pipes_nb)
	{
		if (pipe(p->pipes + i) < 0)
		{
			free(p->pipes);
			ft_error(NULL, errno);
		}
		i = i + 2;
	}
}

int	exec_pipeline(t_command **cmds, t_env *my_env)
{
	int		i;

	get_infile(&p);
	get_outfile(&p, argc);
	p.cmds_nb = argc - 3 - p.here_doc;
	p.pipes_nb = (p.cmds_nb - 1) * 2;
	p.pipes = ft_calloc(p.pipes_nb, sizeof(int));
	if (!p.pipes)
		ft_error("A malloc has failed", 0);
	go_pipe(&p);
	i = p.here_doc - 1;
	p.i = 0;
	while (++i < p.cmds_nb + p.here_doc)
	{
		p.cmd = p.args[i + 2];
		exec_command(p);
		p.i += 2;
	}
	waitpid(-1, NULL, 0);
	free(p.pipes);
	return (0);
} */