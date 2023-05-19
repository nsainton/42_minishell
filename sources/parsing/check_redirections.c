/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:23:40 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/19 17:39:23 by nsainton         ###   ########.fr       */
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
