/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:30:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/18 18:32:27 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	change_state
int	parse_line(t_cchar *line, t_parser *parser)
{
	size_t	index;

	if (init_parser(parser))
		return (ALLOCATION_ERROR);
	index = 0;
	while (*(line + index))
	{

