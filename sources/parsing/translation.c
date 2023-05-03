/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:43:22 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/03 15:39:50 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	crypt_char(t_cint c)
{
	if (c == ' ')
		return (S_PACE);
	if (c == '>')
		return (O_RED);
	if (c == '<')
		return (I_RED);
	if (c == '|')
		return (PIPE);
	return (c);
}

int	decrypt_char(t_cint c)
{
	if (c == S_PACE)
		return (' ');
	if (c == O_RED)
		return ('>');
	if (c == I_RED)
		return ('<');
	if (c == PIPE)
		return ('|');
	return (c);
}
