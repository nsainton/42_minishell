/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:00:40 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/18 16:57:17 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_dup2(int read_fd, int write_fd)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(write_fd, STDOUT_FILENO);
}

void	close_used_pipes(t_data *d, t_command *cmd)
{
	if (d->index - 2 >= 0 && d->index + 1 <= d->pipes_nb)
	{
		close(d->pipes[d->index - 2]);
		close(d->pipes[d->index + 1]);
	}
	else if (d->index == 0)
	{
		close(cmd->fd_in);
		close(d->pipes[d->index + 1]);
	}
	else if (d->index == d->pipes_nb)
	{
		close(d->pipes[d->index - 2]);
		close(cmd->fd_out);
	}
}

void	exec_command(t_data *d, t_command *cmd)
{
	d->pid = fork();
	if (d->pid < 0)
		ft_dprintf(2, "error : %s", strerror(errno));
	else if (d->pid == 0)
	{
		if (d->index == 0)
			sub_dup2(cmd->fd_in, d->pipes[1]);
		else if (d->index == d->pipes_nb)
			sub_dup2(d->pipes[d->index - 2], cmd->fd_out);
		else
			sub_dup2(d->pipes[d->index - 2], d->pipes[d->index + 1]);
		d->errnum = execve(cmd->path, (char *const *)make_command(cmd),
				envlist_to_arr(d->env->list_env));
		if (d->errnum)
			ft_dprintf(2, "%s : %s\n", cmd->command, strerror(errno));
		exit(d->errnum);
	}
	close_used_pipes(d, cmd);
}

char	**make_command(t_command	*cmd)
{
	char	**full_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_cmd = gccalloc(ft_arrlen(((void **) cmd->args) + 2), sizeof (char *));
	full_cmd[j++] = gc_strdup(cmd->command);

	i = 0;
	while (cmd->args[i])
	{
		full_cmd[j++] = gc_strdup(cmd->args[i]);
		i ++;
	}
	full_cmd[j] = NULL;
	i = 0;
	while (full_cmd[i])
		ft_dprintf(2, "full_cmd : %s\n", full_cmd[i++]);
	return (full_cmd);
}


int	go_pipe(t_data *d)
{
	int	i;

	d->pipes = gccalloc(d->pipes_nb, sizeof(int));
	if (!d->pipes)
	{
		ft_dprintf(2, "error : malloc has failed");
		return (errno);
	}
	i = 0;
	while (i < d->pipes_nb)
	{
		if (pipe(d->pipes + i) < 0)
			return (errno); // ?oui
		i = i + 2;
	}
	return (0);
}

int	exec_pipeline(t_data	*d)
{
	int		i;

	if (d->cmds_nb == 0)
		return (1);
	d->pipes_nb = (d->cmds_nb - 1) * 2;
	d->errnum = go_pipe(d);
	if (d->errnum)
		return (d->errnum);
	i = 0;
	d->index = 0;
	/* if (d->here_doc)
	{
		here_doc(d->limiters, d->here_doc);
		if (open(".heredoc", O_RDONLY) < 0)
		{
			unlink(".heredoc");
			ft_dprintf(2, "heredoc unlink : %s\n", strerror(errno));
			d->errnum = errno;
		}
	} */

	while (i < d->cmds_nb)
	{
		if (which_builtin(d->cmds[i], d) == 127)
		{
			get_infile(d->cmds[i]);
			get_outfile(d->cmds[i]);
			ft_printf("exec_pipeline\n");
			if (d->cmds[i]->command)
			{
				d->errnum = check_path(d->cmds[i], d->env);
				if (!d->errnum)
					exec_command(d, d->cmds[i]);
				else
					ft_dprintf(2, "%s : %s\n", d->cmds[i]->command, strerror(d->errnum));
			}
		}
		d->index += 2;
		i++;
	}
	waitpid(-1, NULL, 0);
	free_node(d->pipes);
	return (0);
}