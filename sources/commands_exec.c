/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:00:27 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:37:29 by nsainton         ###   ########.fr       */
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
	/*
	data->cmds = get_commands_reference(commands);
	if (! data->cmds)
		return ;
	data->cmds_nb = tablen(data->cmds, sizeof * data->cmds);
	if (!data->cmds_nb)
		return ;
	exec_pipeline(data);
	*/
	//data->cmds = NULL;
	return (execute_commands(commands, env));
}
