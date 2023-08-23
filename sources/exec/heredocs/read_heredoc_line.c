/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:29:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 07:56:44 by nsainto          ###   ########.fr       */
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

/*
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
*/

/*
	Same as function below, we keep an extra room for '\n'
*/
static int	add_var(struct s_str *raw_line, const char *line, \
size_t *line_index, const struct s_tab *env)
{
	char	*env_var;

	env_var = get_var(line, env, line_index);
	return (t_str_add_str(raw_line, env_var));
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
		if (expand->len + 2 > expand->size && t_str_realloc(expand))
			return (1);
		t_str_add(expand, *(line + index));
		index ++;
	}
	return (0);
}

char	*read_heredoc_line(const char *line, const struct s_tab *env)
{
	struct s_str	expand;

	if (t_str_alloc(&expand, PARSER_SIZE))
		return (NULL);
	if (parse_heredoc_line(&expand, line, env))
	{
		free_node(expand.str);
		return (NULL);
	}
	if (t_str_add(&expand, '\n'))
	{
		free_node(expand.str);
		return (NULL);
	}
	return (expand.str);
}
