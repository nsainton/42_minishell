/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:02:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 17:41:03 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_without_spaces(char *line, size_t *len)
{
	size_t	index;
	char	current;

	index = 0;
	current = *(line + index);
	EPRINT
	while (index < *len)
	{
		index ++;
		if (current != '>' && current != '<')
		{
			current = *(line + index);
			//ft_printf("CC : %c\n", current);
			continue;
		}
		/*
		ft_printf("We are here\n");
		ft_printf("Current char : %c\n", current);
		ft_printf("Next : %c\n", *(line + index));
		*/
		if (*(line + index) == ' ' && *(line + index + 1) == current)
			return (SYNTAX_ERROR);
		current = *(line + index);
		if (*(line + index) == ' ')
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			(*len) --;
		}
	}
	return (NO_ERROR);
}
