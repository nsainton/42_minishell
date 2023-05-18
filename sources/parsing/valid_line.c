/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:02:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/17 15:27:56 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redirect_without_spaces(char *line, size_t *len)
{
	size_t		index;
	signed char	current;
	char		invar;
	int			skipped;

	index = 0;
	current = *(line + index);
	invar = 0;
	while (index++ < *len)
	{
		invar = invar + (current == BEG_VAR) - (current == END_VAR);
		if (current != '>' && current != '<')
		{
			current = *(line + index);
			continue ;
		}
		/*
		if (*(line + index) == ' ' && *(line + index + 1) == current && !invar)
			return (SYNTAX_ERROR);
		*/
		ft_printf("Are we in var : %s\n", (invar == 1)?"YES":"NO");
		skipped = skip_spaces(line, len, index, invar);
		if (! invar && skipped && *(line + index) == current)
		{
			ft_printf("It seems that spaces have been skipped and an error occured\n");
			return (SYNTAX_ERROR);
		}
		current = *(line + index);
		/*
		if (*(line + index) == ' ' && !invar)
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			(*len)--;
		}
		*/
	}
	return (NO_ERROR);
}
