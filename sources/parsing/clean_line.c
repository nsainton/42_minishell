/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:25:08 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 10:49:16 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	clean_line(char *line, size_t *len)
{
	size_t		index;
	signed char	invar;
	char		current;

	index = 0;
	invar = 0;
	current = *(line + index);
	while (index++ < *len)
	{
		invar = 
*/
/*
Index is pointing to the char BEG_VAR in the line
*/
void	convert_var(signed char *line, size_t *len, t_csizet beg, char prev)
{
	size_t		index;
	int			parser;
	signed char	current;

	index = beg + 1;
	parser = (prev == '>' || prev == '<');
	while (*(line + index) != END_VAR)
	{
		if (*(line + index) == ' ' && *(line + index + 1) == ' ' && ! parser)
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			*len -= 1;
			continue ;
		}
		*(line + index) = crypt_char(*(line + index));
		index ++;
	}
	ft_memmove(line + beg, line + beg + 1, *len - beg);
	ft_memove(line + index, line + index + 1, *len - index - 1);
	*len -= 2;
}


void	remove_var_symbols(signed char *line, size_t *len)
{
	size_t		index;
	int			invar;
	signed char	current;

	index = 0;
	invar = 0;
	while (index < *len)
	{
		if (*(line + index) == BEG_VAR && index)
			convert_var(line, len, index, *(line + index - 1);
		else if (*(line + index) == BEG_VAR)
			convert_var(line, len, index, 0);
		else
			index ++;
	}
}
