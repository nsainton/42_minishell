/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:02:53 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 09:56:29 by nsainton         ###   ########.fr       */
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

static int	add_exit_status(t_str *str)
{
	char	*status;
	int		error;

	status = gc_itoa(keep_exit_status(-1));
	if (! status)
		return (ALLOCATION_ERROR);
	error = t_str_add_str(str, status);
	if (error)
		return (error);
	free_node(status);
	return (NO_ERROR);
}

/*
Reminder : A valid name is a name beginning by an alphabetical character
or an underscore and containing only alphanumerical characters or
underscores
*/
static int	handle_dollar(t_str *str, t_cstr *line, int *parser, \
const struct s_tab *env)
{
	char	current;

	line->index += 1;
	current = *(line->str + line->index);
	if (*parser == S_QUOTES || current == ' ' || ! current \
	|| ft_ispunct(current))
		return (t_str_add(str, '$'));
	if (*(line->str + line->index) == '?')
	{
		line->index += 1;
		return (add_exit_status(str));
	}
	if (! ft_isalpha(*(line->str + line->index)) \
	&& *(line->str + line->index) != '_')
	{
		line->index += 1;
		return (NO_ERROR);
	}
	else
		return (copy_env_variable(str, line, *parser, env));
}

static int	handle_specials(t_str *str, t_cstr *line, int *parser, \
const struct s_tab *env)
{
	char	current;

	current = *(line->str + line->index);
	if (current == '$')
		return (handle_dollar(str, line, parser, env));
	line->index += 1;
	if (current == '\'' || current == '\"')
		return (! change_state(parser, current) && t_str_add(str, current));
	if (*parser)
		return (t_str_add(str, crypt_char(current)));
	if (current == ' ' && *(line->str + line->index) == ' ')
		return (0);
	return (t_str_add(str, current));
}

int	get_raw_line(t_cchar *line, t_str *newline, \
const struct s_tab *env)
{
	int		parser;
	t_cstr	baseline;

	parser = 0;
	if (t_str_alloc(newline, PARSER_SIZE))
		return (ALLOCATION_ERROR);
	baseline.str = line;
	baseline.index = 0;
	while (*(line + baseline.index))
	{
		if (! ft_strchr(SPECIALS, *(line + baseline.index)))
		{
			if (t_str_add(newline, *(line + baseline.index)))
				return (ALLOCATION_ERROR);
			baseline.index ++;
		}
		else if (handle_specials(newline, &baseline, &parser, env))
			return (ALLOCATION_ERROR);
	}
	return (NO_ERROR);
}
