/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:38:38 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 08:07:17 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The code should be well structured and this function shouldn't
	exist. Dakara, I don't know yet how to do
*/
static int cleanup(char *line, int fd, const unsigned int line_index, \
const char *limiter)
{
	if (! line)
		ft_dprintf(STDERR_FILENO, HEREDOC_WARNING, line_index, limiter);
	else
		free(line);
	if (s_close(fd))
		return (1);
	return ((line != NULL) - 1);
}

static int	read_heredoc(const char *limiter, int write_fd, \
const struct s_tab *env)
{
	char				*line;
	char				*expanded_line;
	static unsigned int	line_index;

	line_index++;
	line = readline(PS2);
	while (line)
	{
		expanded_line = read_heredoc_line(line, env);
		if (g_termsig == 130 || ! expanded_line)
		{
			free(line);
			s_close(write_fd);
			return (EXIT_FAILURE);
		}
		ft_printf("This is the retrieved line : `%s'\n");
		if (! ft_strncmp(expanded_line, limiter, \
		ft_strlen(expanded_line) - 1) && ft_strlen(expanded_line) > 1)
			break ;
		free(line);
		write(write_fd, expanded_line, ft_strlen(expanded_line));
		line = readline(PS2);
		line_index ++;
	}
	return (cleanup(line, write_fd, line_index, limiter));
}

static int	heredoc_open(const char *heredoc_name, \
struct s_heredoc_infos *hd)
{
	hd->write_fd = s_open(heredoc_name, O_EXCL | O_CREAT | \
	O_WRONLY | O_TRUNC, 00600);
	if (hd->write_fd < 0)
		return (EXIT_FAILURE);
	hd->read_fd = s_open(heredoc_name, O_RDONLY, 0);
	if (hd->read_fd < 0)
		return (EXIT_FAILURE);
	if (unlink(heredoc_name) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	create_random_name(char *name, const void *address)
{
	unsigned int	random;
	char			*tmp;

	*name = 0;
	tmp = name;
	tmp += ft_strncat(name, HEREDOC, 100);
	random = (unsigned int)((uintptr_t)address & 0xffffffff);
	put_uns_tab(random, &tmp, HEX, random % 10 + 5);
}

int	get_heredoc(struct s_heredoc_infos *hd, \
struct s_heredoc *heredoc, \
const struct s_tab *env)
{
	char	name[100];
	int		error;

	ft_bzero(hd, sizeof * hd);
	create_random_name(name, heredoc);
	if (heredoc_open(name, hd))
		return (EXIT_FAILURE);
	ft_printf("This is the limiter : `%s'\n", heredoc->limiter);
	error = read_heredoc(heredoc->limiter, hd->write_fd, env);
	return ((error > 0) * EXIT_FAILURE + (error < 1) * error);
}
