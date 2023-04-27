/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:30:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 18:01:18 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pstate(t_parser *parser, t_cchar meta)
{
	if (meta == '\'' && parser->state != D_QUOTES)
		parser->state = (parser->state != S_QUOTES) * S_QUOTES;
	else if (meta == '\"' && parser->state != S_QUOTES)
		parser->state = (parser->state != D_QUOTES) * D_QUOTES;
}

int	parse_shell_line(t_cchar *line, t_parser *parser)
{
	size_t		index;
	t_metachar	mc;

	if (init_parser(parser))
		return (ALLOCATION_ERROR);
	index = 0;
	ft_bzero(&mc, sizeof mc);
	while (*(line + index))
	{
		mc.c = *(line + index);
		mc.state = set_mcstate(parser, mc.c);
		if (add_parser(parser, mc))
			return (ALLOCATION_ERROR);
		change_pstate(parser, mc.c);
		index ++;
	}
	return (0);
}

int	copy_right_chars(t_parser *parser)
{
	t_metachar	*mc;
	size_t		index;
	size_t		mc_len;

	mc = gcmalloc(sizeof * mc * (parser->len));
	if (! mc)
		return (ALLOCATION_ERROR);
	mc_len = 0;
	index = 0;
	while (index < parser->len)
	{
		index ++;
		if (((parser->meta + index - 1)->c == '\'' \
		|| (parser->meta + index - 1)->c == '\"') \
		&& (parser->meta + index - 1)->state)
			continue ;
		*(mc + mc_len) = *(parser->meta + index - 1);
		mc_len ++;
	}
	parser->size = parser->len;
	parser->len = mc_len;
	free_node(parser->meta);
	parser->meta = mc;
	return (NO_ERROR);
}

/*
t_list	*create_strings_array(t_parser *parser)
{
	t_list	*commands;
	t_list	*command;

	commands = NULL;
	command = NULL;
*/
