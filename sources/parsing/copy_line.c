/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 11:06:56 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_line(t_cchar *line)
{
	t_str	nl;

	if (get_raw_line(line, &nl))
		return (NULL);
	if (redirect_without_spaces(nl.str, &nl.len))
		return (NULL);
	if (invalid_operator(nl.str, &nl.len))
		return (NULL);
	return (nl.str);
}
