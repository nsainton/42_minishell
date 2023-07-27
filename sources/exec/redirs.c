/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:16:50 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/27 12:04:05 by nsainton         ###   ########.fr       */
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
	if (cmd->heredocs && heredoc(cmd))
		return (EXIT_FAILURE);
	cmd->fds = gc_lstnew(NULL);
	while (cmd->redirs && cmd->redirs[i])
	{
		d->errnum = make_dups_list(cmd, cmd->redirs[i]);
		i ++;
	}
	/* while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->mode == 'r' || cmd->redirs[i]->mode == 'b')
			d->errnum = get_infile(cmd, cmd->redirs[i]);
		if (cmd->redirs[i]->mode == 'w')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_TRUNC);
		else if (cmd->redirs[i]->mode == 'a')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_APPEND);
		i ++;
	} */
	return (d->errnum);
}

int	make_dups_list(t_command *cmd, t_redir *redir)
{
	int	*dup_fds;

	dup_fds = gcmalloc(2 * sizeof * dup_fds);
	if (!dup_fds)
		return (EXIT_FAILURE);
	dup_fds[0] = redir->fd;
	if (redir->fd == 0 && (redir->mode == 'r' || redir->mode == 'b'))
		return (get_infile(cmd, redir));
	else if (redir->fd == 1 && redir->mode == 'w')
		return (get_outfile(cmd, redir, O_TRUNC));
	else if (redir->fd == 1 && redir->mode == 'a')
		return (get_outfile(cmd, redir, O_APPEND));
	else
	{
		dup_fds[1] = open_file_fd(redir, redir->mode);
		if (dup_fds[1] >= 0)
			ft_lstadd_back(&cmd->fds, gc_lstnew(dup_fds));
		//dupnclose(dup_fds[0], dup_fds[1]);
	}
	return (0);
}

int	dup_list(t_list *lst_dups)
{
	t_list	*tmp;
	int		*fds;

	if (!lst_dups)
		return (0);
	tmp = lst_dups;
	while (tmp != NULL)
	{
		if (tmp->content)
		{
			fds = (int *)tmp->content;
			ft_printf("%d, %d", fds[0], fds[1]);
			dupnclose(fds[1], fds[0]);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_list(t_list *lst_dups)
{
	t_list	*tmp;
	int		*fds;

	if (!lst_dups)
		return ;
	tmp = lst_dups;
	while (tmp != NULL)
	{
		if (tmp->content)
		{
			fds = (int *)tmp->content;
			if (fds[0] > 2)
			{
				//ft_printf("Closing : %d\n", fds[0]);
				if (close(fds[0]) == -1)
					perror("close");
			}
			if (fds[1] > 2)
			{
				//ft_printf("Closing : %d\n", fds[1]);
				if (close(fds[1]) == -1)
					perror("close");
			}
		}
		tmp = tmp->next;
	}
}

int	open_file_fd(t_redir *r, char mode)
{
	int	new_fd;

	new_fd = -1;
	if (r->file && (mode == 'r' || mode == 'b'))
		new_fd = open(r->file, O_RDONLY);
	else if (r->file && mode == 'w')
		new_fd = open(r->file, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	else if (r->file && mode == 'a')
		new_fd = open(r->file, O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (new_fd < 0)
	{
		ft_dprintf(2, "file : %s : %s\n", r->file, strerror(errno));
		return (errno);
	}
	return (new_fd);
}
