/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:29:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/20 18:08:41 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof * parser);
	parser->meta = gcmalloc(PARSER_SIZE * sizeof * parser->meta);
	if (! parser->meta)
		return (ALLOCATION_ERROR);
	parser->size = PARSER_SIZE;
	return (NO_ERROR);
}

static int	realloc_parser(t_parser *parser)
{
	t_metachar	*meta;
	size_t		elemsize;

	//EPRINT
	//print_parser_infos(parser);
	elemsize = sizeof * parser->meta;
	if (parser->size >= SIZE_MAX / (2 * elemsize))
		return (OVERFLOW);
	meta = gcrealloc(parser->meta, parser->size * elemsize, 2 \
	* parser->size * elemsize);
	if (! meta)
		return (ALLOCATION_ERROR);
	parser->meta = meta;
	parser->size *= 2;
	//print_parser_infos(parser);
	//LPRINT
	return (NO_ERROR);
}

int	add_parser(t_parser *parser, const t_metachar mc)
{
	//EPRINT
	//print_parser_infos(parser);
	if (parser->len == parser->size && realloc_parser(parser))
		return (ALLOCATION_ERROR);
	*(parser->meta + parser->len) = mc;
	parser->len ++;
	//print_parser_infos(parser);
	//LPRINT
	return (NO_ERROR);
}

char	*parser_to_string(t_parser *parser)
{
	char	*new_string;
	size_t	index;

	new_string = gcmalloc(sizeof * new_string * (parser->len + 1));
	if (! new_string)
		return (NULL);
	index = 0;
	while (index < parser->len)
	{
		*(new_string + index) = (parser->meta + index)->c;
		index ++;
	}
	*(new_string + index) = 0;
	return (new_string);
}

void	print_parser_infos(t_parser *parser)
{
	ft_dprintf(STDERR_FILENO, "This is the len : %u\n", parser->len);
	ft_dprintf(STDERR_FILENO, "This is the size : %u\n", parser->size);
}

void	print_parser(t_parser *parser)
{
	char	*ns;

	ns = parser_to_string(parser);
	if (! ns)
		return ;
	ft_printf("This is the parser : %s\n", ns);
	free_node(ns);
}
