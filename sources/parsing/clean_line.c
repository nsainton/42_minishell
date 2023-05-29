/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:25:08 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 21:00:08 by nsainton         ###   ########.fr       */
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
void	convert_var(signed char *line, size_t *len, t_csizet beg)
{
	size_t		index;
	int			parser;
	size_t		redir;
	size_t		space;

	index = beg + 1;
	redir = find_prev((t_cchar *)line, beg, "<>");
	space = find_prev((t_cchar *)line, beg, " ");
	parser = ((redir > space) || (! redir && ft_strchr("<>", *line)));
	while (*(line + index) != END_VAR)
	{
		if (*(line + index) == ' ' && *(line + index + 1) == ' ' && ! parser)
		{
			ft_memmove(line + index, line + index + 1, *len - index);
			*len -= 1;
			continue ;
		}
		else if (*(line + index) == ' ' && parser)
			*(line + index) = crypt_char(*(line + index));
		index ++;
	}
	ft_memmove(line + beg, line + beg + 1, *len - beg);
	*len -= 1;
	index --;
	/*
	ft_printf("This is the last element : %d\n", *(line + index));
	ft_printf("Is this endvar : %s\n", *(line + index) == END_VAR ? "YESS" : "NO");
	*/
	ft_memmove(line + index, line + index + 1, *len - index);
	*len -= 1;
}


void	remove_var_symbols(signed char *line, size_t *len)
{
	size_t		index;

	index = 0;
	while (index < *len)
	{
		if (*(line + index) == BEG_VAR && index)
			convert_var(line, len, index);
		else if (*(line + index) == BEG_VAR)
			convert_var(line, len, index);
		else
			index ++;
	}
}
