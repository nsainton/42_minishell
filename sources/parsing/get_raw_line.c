/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:02:53 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/31 14:00:52 by avedrenn         ###   ########.fr       */
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

/*
Reminder : A valid name is a name beginning by an alphabetical character
or an underscore and containing only alphanumerical characters or
underscores
*/
static int	handle_dollar(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	char	current;

	*index += 1;
	current = *(line + *index);
	if (*parser == S_QUOTES || current == ' ' || ! current)
		return (t_str_add(str, '$'));
	if (*(line + *index) == '?')
	{
		*index += 1;
		return (t_str_add(str, ES));
	}
	if (! ft_isalpha(*(line + *index)) && *(line + *index) != '_')
	{
		*index += 1;
		return (NO_ERROR);
	}
	else
		return (copy_env_variable(str, index, line, *parser));
}

static int	handle_specials(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	char	current;

	current = *(line + *index);
	if (current == '$')
		return (handle_dollar(str, index, line, parser));
	*index += 1;
	if (current == '\'' || current == '\"')
			return (! change_state(parser, current) && t_str_add(str, current));
	if (*parser)
		return (t_str_add(str, crypt_char(current)));
	if (current == ' ' && *(line + *index) == ' ')
		return (0);
	return(t_str_add(str, current));
}

int	get_raw_line(t_cchar *line, t_str *newline)
{
	int		parser;
	size_t	index;

	parser = 0;
	if (t_str_alloc(newline, PARSER_SIZE))
		return (ALLOCATION_ERROR);
	index = 0;
	while (*(line + index))
	{
		if (! ft_strchr(SPECIALS, *(line + index)))
		{
			if (t_str_add(newline, *(line + index)))
				return (ALLOCATION_ERROR);
			index ++;
		}
		else if (handle_specials(newline, &index, line, &parser))
			return (ALLOCATION_ERROR);
	}
	return (NO_ERROR);
}
