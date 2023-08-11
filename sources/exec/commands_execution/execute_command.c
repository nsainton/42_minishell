/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:03:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 14:10:07 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(struct s_ncommand *commands, struct s_env *env)
{
	size_t	commands_nb;

	commands_nb = tablen(commands, sizeof * commands);
	if (make_pipes(commands) || heredocs(commands, commands_nb, env))
	{
		clear_fdlist();
		return (1);
	}
	print_commands(commands);
	//print_fdlist();
	clear_fdlist();
	return (0);
}
