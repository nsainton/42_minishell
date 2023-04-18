/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:29:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/18 18:18:52 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof * parser);
	parser->meta = gcmalloc(PARSER_SIZE);
	if (! parser->meta)
		return (ALLOCATION_ERROR);
	parser->size = PARSER_SIZE;
	return (NO_ERROR);
}

static int	realloc_parser(t_parser *parser)
{
	t_metachar	*meta;
	size_t		elemsize;

	elemsize = sizeof * parser->meta;
	if (parser->size >= SIZE_MAX / (2 * elemsize))
		return (OVERFLOW);
	meta = gcrealloc(parser->meta, parser->size * elemsize, 2 \
	* parser->size * elemsize);
	if (! meta)
		return (ALLOCATION_ERROR);
	parser->meta = meta;
	parser->size *= 2;
	return (NO_ERROR);
}

int	add_parser(t_parser *parser, const t_metachar mc)
{
	if (parser->len == parser->size && realloc_parser(parser))
		return (ALLOCATION_ERROR);
	*(parser->meta + parser->len) = mc;
	parser->len ++;
	return (NO_ERROR);
}

int	add_parser_char(t_parser *parser, t_cchar c, t_cchar state)
{
	return (add_parser(parser, (const t_metachar){c, state}));
}
