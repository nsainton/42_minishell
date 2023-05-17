/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:02:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/17 09:35:58 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_without_spaces(char *line, size_t *len)
{
	size_t		index;
	signed char	current;
	char		invar;

	index = 0;
	current = *(line + index);
	invar = 0;
	/*
	EPRINT
	ft_printf("This is the line : %s\n", line);
	*/
	while (index++ < *len)
	{
		//ft_printf("This is the current char[%d] : %c\n", index, current);
		invar = invar + (current == BEG_VAR) - (current == END_VAR);
		/*
		if (current == BEG_VAR || current == END_VAR)
			ft_printf("Ahoi captain\n");
		else
			ft_printf("This is BEG_VAR : %d\n", BEG_VAR);
		*/
		if (current != '>' && current != '<')
		{
			current = *(line + index);
			continue ;
		}
		//ft_printf("Before syntax error\n");
		if (*(line + index) == ' ' && *(line + index + 1) == current && !invar)
			//ft_printf("Are we in a variable : %s\n", (invar == 1)?"YES":"NO");
			return (SYNTAX_ERROR);
		//ft_printf("No error \n");
		current = *(line + index);
		if (*(line + index) == ' ' && !invar)
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			(*len)--;
		}
	}
	//LPRINT
	return (NO_ERROR);
}
