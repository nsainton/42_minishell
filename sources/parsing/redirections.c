/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:20 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 10:00:29 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	find_next_redir(t_cchar *line, size_t index)
{
	while (*(line + index) && *(line + index) != '>' && *(line + index) != '<')
		index ++;
	return (index);
}

static size_t	find_prev_space(t_cchar *line, size_t index)
{
	while (index > 0 && *(line + index) != ' ')
		index --;
	return (index);
}

static size_t	find_next_space(t_cchar *line, size_t index)
{
	while (*(line + index) && *(line + index) != ' ')
		index ++;
	return (index);
}

static int	find_mode(t_cchar *line, t_csizet index)
{
	if (*(line + index) == '>' && *(line + index + 1) == '>')
		return ('a');
	if (*(line + index) == '<' && *(line + index + 1) == '<')
		return ('h');
	if (*(line + index) == '<' && *(line + index + 1) == '>')
		return ('b');
	if (*(line + index) == '>')
		return ('w');
	if (*(line + index) == '<')
		return ('r');
	return (0);
}

static int	push_redirection(t_tab *redirs, char *line, t_csizet index, int fd)
{
	t_redirection	redir;
	char			mode;
	size_t			begredir;
	size_t			nextspace;

	ft_bzero(&redir, sizeof redir);
	begredir = index;
	if (*(line + index) != '<' && *(line + index) != '>')
		begredir = find_next_redir(line, index);
	mode = find_mode(line, begredir);
	if (fd != -1)
		redir.fd = fd;
	else if (mode == 'a' || mode == 'w')
		redir.fd = 1;
	while (*(line + begredir) != '<' && *(line + begredir) != '>')
		begredir ++;
	nextspace = find_next_space(line, begredir);
	redir.file = gc_substr(line, begredir, nextspace - begredir);
	if (! redir.file || add_tab(redirs, &redir))
		return (ALLOCATION_ERROR);
	ft_memmove(line + index, line + nextspace, nextspace - index);
	decrypt_string(redir.file);
	return (NO_ERROR);
}
/*
This function assumes that for example if the line is "echo bonjour >salut"
then index points to the '>'
thus ft_printf("%s\n", line + index) would print : >salut
*/
int	add_redirection(t_tab *redirs, char *line, t_csizet index)
{
	int				err;
	int				fd;
	size_t			space;

	space = find_prev_space(line, index);
	err = 0;
	fd = atoi_until(line, DEC, &err, index - space);
	if (fd < 0 || err)
		return (push_redirection(redirs, line, index, -1));
	else
		return (push_redirection(redirs, line, space + 1, fd));
}
