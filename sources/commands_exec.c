/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:00:27 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/21 14:58:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_exec(const char *line, struct s_env *env)
{
	struct s_ncommand	*commands;

	if (split_line(line, &commands, env->env_list))
	{
		keep_exit_status(SYNTAX_ERROR);
		return (SYNTAX_ERROR);
	}
	return (execute_commands(commands, env));
}
