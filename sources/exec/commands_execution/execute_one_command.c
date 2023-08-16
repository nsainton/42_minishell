/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:47:55 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 12:08:35 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "minishell.h"

/*
int	execute_file(struct s_ncommand *command, struct s_env *env)
{}
*/

static int	pre_execution(struct s_redir *redirs, struct s_heredoc *heredocs)
{
	if (save_stds(-1))
		return (1);
	if (make_redirections(redirs, heredocs))
	{
		save_stds(-2);
		return (1);
	}
	return (0);
}

static int	find_command_path(char *command, char *command_path, struct s_tab *env)
{
	int	err;

	err = get_command_path(command, command_path, env);
	if (err)
	{
		if (err == 127)
			ft_printf("minishell: %s: command not found\n", command);
		exit_free_gc(err);
	}
	return (0);

}

static int	execute_file(struct s_ncommand *command, struct s_tab *env)
{
	pid_t	child_pid;
	int		status;
	int		err;

	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	if (! child_pid)
	{
		find_command_path(command->command, command->path, env);
		if (execve(command->path, command->args, env->tab))
			exit_free_gc(1);
	}
	wait(&status);
}

int	execute_command(struct s_ncommand *command, struct s_env *env)
{
	t_builtin	builtin;
	pid_t		child_pid;
	int			status;
	int			err;

	if (pre_execution(command->redirs, command->heredocs))
		return (1);
	if (! command->command)
	{
		save_stds(-2);
		return (0);
	}
	builtin = choose_builtin(command->command);
	if (builtin)
	{
		err = builtin(command->args, env);
		save_stds(-2);
		return (err);
	}
}
