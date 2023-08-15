/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:29:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 18:43:55 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(const char *line, const struct s_tab *env, \
size_t *line_index)
{
	size_t	index;
	char	*env_var;

	index = 1;
	while (*(line + index) && (ft_isalnum(*(line + index)) || \
	*(line + index) == '_'))
		index ++;
	*line_index += index;
	env_var = expand_env_var(line, 1, index - 1, env);
	if (! env_var)
		return ("");
	return (env_var);
}

static int	realloc_str(struct s_str *string, const size_t newsize)
{
	char	*tmp;

	tmp = ft_realloc(string->str, string->len, newsize);
	if (! tmp)
		return (1);
	string->str = tmp;
	string->size = newsize;
	return (0);
}

/*
	Same as function below, we keep an extra room for '\n'
*/
static int	add_var(struct s_str *raw_line, const char *line, \
size_t *line_index, const struct s_tab *env)
{
	char	*env_var;
	char	*tmp;
	size_t	len;

	env_var = get_var(line, env, line_index);
	len = ft_strlen(env_var);
	if (len + raw_line->len + 2 > raw_line->size)
	{
		tmp = ft_realloc(raw_line->str, raw_line->len, \
		len + raw_line->len + 2);
		if (! tmp)
			return (1);
		raw_line->str = tmp;
		raw_line->size = len + raw_line->len + 2;
	}
	*(raw_line->str + raw_line->len) = 0;
	raw_line->len += ft_strcat(raw_line->str + raw_line->len, env_var);
	return (0);
}

/*
	We check for expand->len + 2 > expand->size to keep room for the '\n'
	that we're going t add in the write_line function.
*/
static int	parse_heredoc_line(struct s_str *expand, const char *line, \
const struct s_tab *env)
{
	size_t	index;

	index = 0;
	while (*(line + index))
	{
		if ((! index || *(line + index - 1) != '\\') && *(line + index) == \
		'$' && ft_isalpha(*(line + index + 1)))
		{
			if (add_var(expand, line + index, &index, env))
				return (1);
			if (! *(line + index))
				break ;
		}
		if (expand->len + 2 > expand->size && \
		realloc_str(expand, 2 * expand->size))
			return (1);
		tstr_addchar(expand, *(line + index));
		index ++;
	}
	return (0);
}

int	write_line(const char *line, int write_fd, const struct s_tab *env)
{
	struct s_str	expand;
	int				err;

	if (tstr_init(&expand, PARSER_SIZE))
		return (1);
	if (parse_heredoc_line(&expand, line, env))
	{
		free(expand.str);
		return (1);
	}
	tstr_addchar(&expand, '\n');
	err = (write(write_fd, expand.str, expand.len) < 0);
	free(expand.str);
	return (err);
}
