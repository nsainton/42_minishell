/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:17:00 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/29 10:44:32 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	problematic_space(t_cchar *line, t_csizet index, t_cchar current)
{
	char	first;
	char	second;

	first = *(line + index);
	if (first == ' ')
	{
		second = *(line + index + 1);
		if (current != '|' && (ft_strchr("<>|", second) || ! second))
		{
			syntax_error(second);
			return (SYNTAX_ERROR);
		}
		if (current == '|' && (second == '|' || ! second))
		{
			syntax_error(second);
			return (SYNTAX_ERROR);
		}
	}
	return (NO_ERROR);
}

static int	invalid_o_redir(t_cchar *line, t_csizet index)
{
	char	first;

	first = *(line + index);
	if (first == '|')
	{
		if (index > 1 && *(line + index - 2) == '>')
		{
			syntax_error('|');
			return (SYNTAX_ERROR);
		}
	}
	return (NO_ERROR);
}

static int	invalid_pipe(t_cchar *line, t_csizet index)
{
	char	first;

	if (index == 1 || (index == 2 && *(line + index - 2) == ' '))
	{
		syntax_error('|');
		return (SYNTAX_ERROR);
	}
	first = *(line + index);
	if (first == '|')
	{
		syntax_error('|');
		return (SYNTAX_ERROR);
	}
	return (NO_ERROR);
}

int	invalid_redir(t_cchar *line, t_csizet index, t_cchar current)
{
	if (problematic_space(line, index, current))
		return (SYNTAX_ERROR);
	if (current == '>' && invalid_o_redir(line, index))
		return (SYNTAX_ERROR);
	if (current == '|' && invalid_pipe(line, index))
		return (SYNTAX_ERROR);
	return (NO_ERROR);
}
