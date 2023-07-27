/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:38:38 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 12:15:10 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(const char *limiter, int write_fd)
{
	char				*line;
	static unsigned int	line_index;

	line_index++;
	line = readline(HEREDOC_PROMPT);
	while (line && ft_strcmp(line, limiter))
	{
		if (g_termsig == 2 || ft_putendl_fd(line, write_fd) == -1)
		{
			g_termsig = 0;
			close(write_fd);
			return (EXIT_FAILURE);
		}
		free(line);
		line = readline(HEREDOC_PROMPT);
		line_index ++;
	}
	if (! line)
		ft_dprintf(STDERR_FILENO, HEREDOC_WARNING, line_index, limiter);
	else
		free(line);
	close(write_fd);
	return ((line != NULL) - 1);
}

static int	heredoc_open(const char *heredoc_name, struct s_heredoc_infos *hd)
{
	hd->write_fd = open(heredoc_name, O_EXCL | O_CREAT | O_WRONLY | O_TRUNC, \
	00600);
	if (hd->write_fd == -1)
		return (EXIT_FAILURE);
	hd->read_fd = open(heredoc_name, O_RDONLY);
	if (hd->read_fd == -1)
	{
		close(hd->write_fd);
		return (EXIT_FAILURE);
	}
	if (unlink(heredoc_name) == -1)
	{
		close(hd->read_fd);
		close(hd->write_fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	create_random_name(char *name, void *address)
{
	unsigned int	random;
	char			*tmp;

	*name = 0;
	tmp = name;
	tmp += ft_strncat(name, HEREDOC, 100);
	random = (unsigned int)((uintptr_t)address & 0xffffffff);
	put_uns_tab(random, &tmp, HEX, random % 10 + 5);
}

int	getheredoc(struct s_heredoc_infos *hd, struct s_heredoc *heredoc)
{
	char	name[100];
	int		error;

	reinit_sigs();
	ft_bzero(hd, sizeof * hd);
	create_random_name(name, heredoc);
	if (heredoc_open(name, hd))
		return (EXIT_FAILURE);
	error = read_heredoc(heredoc->limiter, hd->write_fd);
	return ((error > 0) * EXIT_FAILURE + (error < 1) * error);
}
