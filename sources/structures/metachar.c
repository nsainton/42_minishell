/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:30:04 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/20 16:22:18 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_uchar	set_mcstate(const t_parser *parser, const char c)
{
	if (! parser->state)
		return (1);
	else if (c == '\'' && parser->state == S_QUOTES)
		return (1);
	else if ((c == '\"' || c == '$') && parser->state == D_QUOTES)
		return (1);
	return (0);
}
