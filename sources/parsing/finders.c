/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:21:42 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 12:18:57 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	find_next(t_cchar *line, size_t index, t_cchar *tofind)
{
	while (*(line + index) && ! ft_strchr(tofind, *(line + index)))
		index ++;
	return (index);
}

size_t	find_prev(t_cchar *line, size_t index, t_cchar *tofind)
{	
	while (index > 0 && ! ft_strchr(tofind, *(line + index)))
		index --;
	return (index);
}

int	find_mode(t_cchar *line, t_csizet index)
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
