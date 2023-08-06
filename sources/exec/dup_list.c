/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:01:44 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 16:17:56 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_in_out(struct s_command *cmd, t_redir *redir, int *error)
{
	if (redir->fd == 0 && (redir->mode == 'r' || redir->mode == 'b'))
		*error = get_infile(cmd, redir);
	else if (redir->fd == 1 && redir->mode == 'w')
		*error = get_outfile(cmd, redir, O_TRUNC);
	else if (redir->fd == 1 && redir->mode == 'a')
		*error = get_outfile(cmd, redir, O_APPEND);
	else
		*error = INT_MAX;
	return (*error);
}

int	make_dups_list(t_command *cmd, t_redir *redir)
{
	int				*dup_fds;
	struct s_list	*newfd;
	int				error;

	dup_fds = gcmalloc(2 * sizeof * dup_fds);
	if (!dup_fds)
		return (EXIT_FAILURE);
	dup_fds[0] = redir->fd;
	if (get_fd_in_out(cmd, redir, &error) != INT_MAX)
		return (error);
	else
	{
		dup_fds[1] = open_file_fd(redir, redir->mode);
		if (dup_fds[1] >= 0)
		{
			newfd = gc_lstnew(dup_fds);
			if (! newfd)
			{
				close_list(cmd->fds);
				exit_free_gc(ALLOCATION_ERROR);
			}
			ft_lstadd_back(&cmd->fds, gc_lstnew(dup_fds));
		}
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
			safe_close(fds[0]);
			safe_close(fds[1]);
		}
		tmp = tmp->next;
	}
}
