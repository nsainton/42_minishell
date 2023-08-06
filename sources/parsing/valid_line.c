/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:02:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/23 09:50:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	skip_spaces(char *line, size_t *len, size_t index, char invar)
{
	size_t	temporary_index;

	EPRINT
	if (invar)
		return (0);
	ft_printf("This is the line : %s\n", line);
	temporary_index = index;
	ft_printf("We start from here : %s\n", line + index);
	while (temporary_index < *len && *(line + temporary_index) == ' ')
		temporary_index++ ;
	ft_printf("We end up here : %s\n", line + temporary_index);
	if (temporary_index > index)
	{
		ft_memmove(line + index, line + temporary_index, \
		*len - temporary_index + 1);
		return (0);
	}
	ft_printf("This is the confirmation : %s\n", line + index);
	(*len) -= (temporary_index - index);
	LPRINT
	return (1);
}
*/

/*
static int	invalid_redir(char *line, size_t index, t_cchar current)
{
	char	first;
	char	second;

	first = *(line + index);
	if (current != '|' && first == ' ')
	{
		second = *(line + index + 1);
		if (second == '>' || second == '<' || ! second \
		|| second == '|')
		{
			syntax_error(second);
			return (SYNTAX_ERROR);
		}
	}
	if (current == '>' && first == '|')
	{
		if (index > 1 && *(line + index - 2) == '>')
		{
			syntax_error('|');
			return (SYNTAX_ERROR);
		}
	}
	return (NO_ERROR);
}
*/

int	redirect_without_spaces(char *line, size_t *len)
{
	size_t		index;
	signed char	current;

	index = 0;
	current = *(line + index);
	while (index++ < *len)
	{
		if (! ft_strchr("<>|", current))
		{
			current = *(line + index);
			continue ;
		}
		if (invalid_redir(line, index, current))
			return (SYNTAX_ERROR);
		current = *(line + index);
		if (*(line + index) == ' ')
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			(*len)--;
		}
	}
	return (NO_ERROR);
}

static int	fd_and_file(char *line, t_csizet index)
{
	size_t	nextredir;
	int		fd;
	int		err;
	char	*errstring;

	nextredir = index;
	while (*(line + nextredir) \
	&& *(line + nextredir) != '>' && *(line + nextredir) != '<')
		nextredir ++;
	if (nextredir == index)
		return (NO_ERROR);
	fd = atoi_until(line + index, DEC, &err, nextredir - index);
	if (fd < 0 || err || ! *(line + nextredir))
		return (NO_ERROR);
	errstring = gc_substr(line, index, nextredir - index);
	if (! errstring)
		return (SYNTAX_ERROR);
	syntax_errors(errstring);
	free_node(errstring);
	return (SYNTAX_ERROR);
}

int	invalid_operator(char *line, size_t *len)
{
	size_t	index;

	index = 0;
	while (*(line + index))
	{
		if (*(line + index) == '<' && (check_in_redir(line, index + 1) \
		|| fd_and_file(line, index + 1)))
			return (SYNTAX_ERROR);
		else if (*(line + index) == '>' && (check_o_redir(line, len, index + 1) \
		|| fd_and_file(line, index + 1)))
			return (SYNTAX_ERROR);
		index ++;
	}
	return (NO_ERROR);
}
