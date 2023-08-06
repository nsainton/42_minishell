/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:43:22 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/26 17:57:13 by nsainton         ###   ########.fr       */
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

void	decrypt_string(char *s)
{
	signed char	*str;

	str = (signed char *)s;
	while (*str)
	{
		*str = decrypt_char(*str);
		str ++;
	}
}

int	ft_ispunct(const int c)
{
	return (c == '!' || c == '#' || c == '%' || c == ',' \
	|| c == ':' || c == '.' || c == '-' || c == '@' \
	|| c == '/' || c == '=');
}
