/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 14:38:34 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_line(t_cchar *line, t_command **command)
{
	t_str	nl;
	t_tab	com;

	if (allocate_tab(&com, REDIRS_SIZE, sizeof (t_command)))
		return (ALLOCATION_ERROR);
	if (get_raw_line(line, &nl))
		return (ALLOCATION_ERROR);
	if (redirect_without_spaces(nl.str, &nl.len))
		return (SYNTAX_ERROR);
	if (invalid_operator(nl.str, &nl.len))
		return (SYNTAX_ERROR);
	remove_var_symbols((signed char *)nl.str, &nl.len);
	/*
	if (redirections(redirs, &nl))
		return (NULL);
	*/
	if (fill_commands(&com, nl.str))
		return (ALLOCATION_ERROR);
	*command = (t_command *)com.tab;
	return (EXIT_SUCCESS);
}
