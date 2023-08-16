/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:47:55 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 09:22:13 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "minishell.h"

/*
int	execute_file(struct s_ncommand *command, struct s_env *env)
{}
*/

int	execute_command(struct s_ncommand *command, struct s_env *env)
{
	t_builtin	builtin;
	pid_t		child_pid;
	int			status;

	if (! command->command)
		return (0);
	builtin = choose_builtin(command->command);
	if (builtin)
		return (builtin(command->args, env));
	child_pid = fork();
	if (child_pid < 0)
		return (1);
	if (! child_pid)
		execute_file(command, env);
	wait(
}
