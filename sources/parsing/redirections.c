/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:20 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 11:43:20 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	push_redirection(t_tab *redirs, t_str *line, t_csizet index, int fd)
{
	t_redirection	redir;
	char			mode;
	size_t			begredir;
	size_t			nextspace;

	ft_bzero(&redir, sizeof redir);
	begredir = index;
	if (*(line->str + index) != '<' && *(line->str + index) != '>')
		begredir = find_next(line->str, index, "<>");
	mode = find_mode(line->str, begredir);
	if (fd != -1)
		redir.fd = fd;
	else if (mode == 'a' || mode == 'w')
		redir.fd = 1;
	while (*(line->str + begredir) == '<' && *(line->str + begredir) == '>')
		begredir ++;
	nextspace = find_next(line->str, begredir, "<> ");
	redir.file = gc_substr(line->str, begredir, nextspace - begredir);
	if (! redir.file || add_tab(redirs, &redir))
		return (ALLOCATION_ERROR);
	ft_memmove(line->str + index, line->str + nextspace, nextspace - index);
	line->len -= (nextspace - index);
	decrypt_string(redir.file);
	return (NO_ERROR);
}
/*
This function assumes that for example if the line is "echo bonjour >salut"
then index points to the '>'
thus ft_printf("%s\n", line + index) would print : >salut
*/
static int	add_redirection(t_tab *redirs, t_str *line, t_csizet index)
{
	int				err;
	int				fd;
	size_t			space;

	space = find_prev(line->str, index, " ");
	err = 0;
	fd = atoi_until(line->str + space, DEC, &err, index - space);
	if (fd < 0 || err)
		return (push_redirection(redirs, line, index, -1));
	else
		return (push_redirection(redirs, line, space + 1, fd));
	return (UNKNOWN_ERROR);
}

int	redirections(t_tab *redirs, t_str *line)
{
	size_t	index;

	if (allocate_tab(redirs, PARSER_SIZE, sizeof (t_redirection)))
		return (ALLOCATION_ERROR);
	index = 0;
	while (index < line->len)
	{
		if ((*(line->str + index) == '>' || *(line->str + index) == '<'))
		{
			if (add_redirection(redirs, line, index))
				return (ALLOCATION_ERROR);
		}
		else
			index ++;
	}
	return (NO_ERROR);
}
