/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:56 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 09:59:05 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_line(const char *line, struct s_ncommand **command, \
const struct s_tab *env)
{
	struct s_str	nl;
	struct s_tab	com;

	if (allocate_tab(&com, REDIRS_SIZE, sizeof (t_ncommand)))
		return (ALLOCATION_ERROR);
	if (get_raw_line(line, &nl, env))
		return (ALLOCATION_ERROR);
	if (redirect_without_spaces(nl.str, &nl.len))
		return (SYNTAX_ERROR);
	if (invalid_operator(nl.str, &nl.len))
		return (SYNTAX_ERROR);
	remove_var_symbols((signed char *)nl.str, &nl.len);
	if (fill_commands(&com, nl.str))
		return (ALLOCATION_ERROR);
	*command = (t_ncommand *)com.tab;
	return (EXIT_SUCCESS);
}
