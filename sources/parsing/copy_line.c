/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 17:05:18 by nsainton         ###   ########.fr       */
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

static int	copy_env_variable(t_str *str, size_t *index, t_cchar *line)
{
	size_t	base_index;
	char	current;
	char	*var_name;
	char	*var;

	base_index = *index;
	current = *(line + *index);
	while (current && (ft_isalnum(current) || current == '_'))
	{
		(*index)++;
		current = *(line + *index);
	}
	var_name = gc_substr(line, base_index, *index - base_index);
	if (! var_name)
		return (ALLOCATION_ERROR);
	var = getenv(var_name);
	free_node(var_name);
	if (! var)
		return (NO_ERROR);
	return (t_str_add_str(str, var));
}

/*
Reminder : A valid name is a name beginning by an alphabetical character
or an underscore and containing only alphanumerical characters or 
underscores
*/
static int	handle_dollar(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	*index += 1;
	if (*parser == S_QUOTES || *(line + index) == ' ')
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
		return (copy_env_variable(str, index, line));
}

static int	handle_specials(t_str *str, size_t *index, t_cchar *line, \
int *parser)
{
	char	current;

	EPRINT
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
		if (! ft_strchr(SPECIALS, *(line + index)))
		{
			if (t_str_add(&nl, *(line + index)))
				return (NULL);
			index ++;
		}
		else if (handle_specials(&nl, &index, line, &parser))
			return (NULL);
	}
	return (nl.str);
}
