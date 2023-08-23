/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:47:59 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 10:19:43 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

/**
* @brief Makes the redirections for the given command
*
* @params[in] command : A struct s_ncommand variable that holds the command
* we are looking at.
*
* @return An integer that is null if everything went well and that 
* is positive otherwise
*/

static int	get_flags(const int mode)
{
	if (mode == 'b')
		return (O_RDWR | O_CREAT | O_TRUNC);
	if (mode == 'r')
		return (O_RDONLY);
	if (mode == 'a')
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (mode == 'w')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (0);
}

static int	make_redirection(struct s_redir *redir)
{
	int	fd;

	if (save_stds(redir->fd))
		return (1);
	fd = s_open(redir->file, get_flags(redir->mode), 0644);
	if (fd < 0)
	{
		if (redir->mode == 'r')
			ft_dprintf(STDERR_FILENO, \
			"minishell: %s: No such file or directory\n", redir->file);
		return (1);
	}
	if ((s_dup2(fd, redir->fd) < 0) || s_close(fd))
		return (1);
	return (0);
}

/*
	This function's goal is to duplicate the heredoc read_fd that
	we read earlier onto the real heredoc file descriptor specified
	by the user
*/
static int	dup_heredoc(struct s_heredoc *heredoc)
{
	int	err;

	if (heredoc->read_fd == -1)
		return (0);
	if (save_stds(heredoc->fd))
		return (1);
	err = (s_dup2(heredoc->read_fd, heredoc->fd) < 0 || \
	s_close(heredoc->read_fd));
	return (err);
}

/*
static int	apply_tabs(struct s_tab *t1, struct s_tab *t2, \
int (*f1)(void *), int (*f2)(void *))
{
	size_t	i1;
	size_t	i2;
	size_t	l1;
	size_t	l2;

	l1 = tablen(t1->tab, t1->elemsize);
	l2 = tablen(t2->tab, t2->elemsize);
	i1 = 0;
	i2 = 0;
	while (i1 + i2 < l1 + l2)
	{
		if (i1
}
*/

/*
	In the struct s_redir structure there is a integer, a char and a
	char pointer. Even admitting that those would be padded to align with
	the addresses of 3 char pointers, the full size of struct s_redir
	would be at most 30 bytes.
*/
int	make_redirections(struct s_redir *redirections, struct s_heredoc *heredocs)
{
	size_t			i;
	size_t			len;
	size_t			redirs_len;
	size_t			h_index;

	if (! (redirections || heredocs))
		return (0);
	redirs_len = tablen(redirections, sizeof * redirections);
	len = redirs_len + tablen(heredocs, sizeof * heredocs);
	i = 0;
	h_index = 0;
	while (i < len)
	{
		if (h_index < len - redirs_len && i == (heredocs + h_index)->index)
		{
			if (dup_heredoc(heredocs + h_index))
				return (1);
			h_index ++;
		}
		else if (i - h_index < redirs_len && \
		make_redirection(redirections + i - h_index))
			return (1);
		i ++;
	}
	return (0);
}
