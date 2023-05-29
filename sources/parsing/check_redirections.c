/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:23:40 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 10:14:31 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_redir(t_cchar *line, t_csizet index)
{
	char	next;

	if (! ft_strchr(REDIRS, *(line + index)) && *(line + index))
		return (NO_ERROR);
	if (*(line + index) == '|' || ! *(line + index))
	{
		syntax_error(*(line + index));
		return (SYNTAX_ERROR);
	}
	next = *(line + index + 1);
	if (*(line + index) == '<' && (ft_strchr(REDIRS, next) || ! next))
	{
		syntax_error(next);
		return (SYNTAX_ERROR);
	}
	if (*(line + index) == '>' && (ft_strchr(REDIRS, next) || ! next))
	{
		syntax_error(next);
		return (SYNTAX_ERROR);
	}
	return (NO_ERROR);
}

static int	suppress_pipe(char *line, size_t *len, t_csizet index)
{
	char	next;

	next = *(line + index + 1);
	if (! next || ft_strchr(REDIRS, next))
	{
		syntax_error(next);
		return (SYNTAX_ERROR);
	}
	ft_memmove(line + index, line + index + 1, *len - index);
	(*len) --;
	return (NO_ERROR);
}

int	check_o_redir(char *line, size_t *len, t_csizet index)
{
	char	next;

	if (! ft_strchr(REDIRS, *(line + index)) && *(line + index))
		return (NO_ERROR);
	if (*(line + index) == '<' || ! *(line + index))
	{
		syntax_error(*(line + index));
		return (SYNTAX_ERROR);
	}
	next = *(line + index + 1);
	if (*(line + index) == '>' && (ft_strchr(REDIRS, next) || ! next))
	{
		syntax_error(next);
		return (SYNTAX_ERROR);
	}
	if (*(line + index) == '|' && suppress_pipe(line, len, index))
		return (SYNTAX_ERROR);
	return (NO_ERROR);
}
