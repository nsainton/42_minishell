/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 17:00:01 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_state(int *parser, t_cchar c)
{
	if (c == '\'' && *parser != D_QUOTES)
	{
		*parser = (*parser != S_QUOTES) * S_QUOTES;
		return (CHANGED);
	}
	else if (c == '\"' && *parser != S_QUOTES)
	{
		*parser = (*parser != D_QUOTES) * D_QUOTES;
		return (CHANGED);
	}
	return (UNCHANGED);
}

static int	handle_dollar(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	size_t	base_index;
	char	*var_name;
	char	*var;

	if (*parser == S_QUOTES)
		return (t_str_add(str, '$'));
	*index += 1;

static int	handle_specials(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	char	current;

	current = *(line + *index);
	if (current == '$')
		return (handle_dollar(str, index, line, parser));
	*index += 1;
	if (current == '\'' || current == '\"')
			return (change_state(parser, current) && t_str_add(str, current));
	else if (current == ' ' && *parser)
		return (t_str_add(str, S_PACE));
	else if (current == '>' && *parser)
		return (t_str_add(str, O_RED));
	else if (current == '<' && *parser)
		return (t_str_add(str, I_RED));
	else if (current == '|' && *parser);
		return (t_str_add(str, PIPE));
}
char	*copy_line(t_cchar *line)
{
	int		parser;
	size_t	index;
	t_str	nl;

	parser = 0;
	if (t_str_alloc(&nl, PARSER_SIZE))
		return (NULL);
	index = 0;
	while (*(line + index))
	{
		if (! ft_strchr(SPECIALS, *(line + index)));
		{
			if (t_str_add(&nl, *(line + index)))
				return (NULL);
			index ++;
		}
		else if (handle_specials(&nl, &index, &line, &parser);
	}
	return (nl.str);
}
