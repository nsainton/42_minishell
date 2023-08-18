/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:03:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 18:00:08 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_pipe(const int fd_in, const int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if ((s_dup2(fd_in, STDIN_FILENO) < 0) || s_close(fd_in))
			return (1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if ((s_dup2(fd_out, STDOUT_FILENO) < 0) || s_close(fd_out))
			return (1);
	}
	return (0);
}

static int	pipeline_status(void)
{
	int		status;
	int		tmp_status;
	pid_t	child_pid;
	pid_t	tmp_pid;

	status = 0x100;
	child_pid = -1;
	tmp_pid = wait(&tmp_status);
	while (tmp_pid > -1)
	{
		if (tmp_pid > child_pid)
		{
			child_pid = tmp_pid;
			status = tmp_status;
		}
		tmp_pid = wait(&tmp_status);
	}
	return (handle_exit_status(status));
}

static int	execute_pipeline_command(struct s_ncommand *commands, \
const size_t command_index, const size_t commands_nb, \
struct s_env *env)
{
	int	err;

	signal(SIGPIPE, SIG_IGN);
	if (apply_pipe((commands + command_index)->input_fd, \
	(commands + command_index)->output_fd))
		exit_free_gc(1);
	if (cleanup_before_exec(commands, command_index, commands_nb))
		exit_free_gc(1);
	err = execute_command(commands + command_index, env);
	clear_fdlist();
	return (err);
}

static int	execute_pipeline(struct s_ncommand *commands, \
const size_t commands_nb, struct s_env *env)
{
	size_t	i;
	int		child_pid;

	i = 0;
	while (i < commands_nb)
	{
		child_pid = fork();
		if (child_pid < 0)
			break ;
		if (! child_pid)
			exit_free_gc(execute_pipeline_command(commands, i, \
			commands_nb, env));
		i ++;
	}
	clear_fdlist();
	return (pipeline_status());
}

/**
* @brief Executes the command or pipeline received after the parsing
* of the provided command line
*
* @details None at the moment
*
* @param[in] commands : An array of struct s_ncommand that is null 
* terminated and that holds, for each of its elements, one command 
* of the provided pipeline
* @param[in] env : The structure holding the environment that has been 
* properly formatted in an earlier function
*
* @return the status exit code of the command or pipeline provided. 
* Might not return if there is one command and this one command is exit.
*/
int	execute_commands(struct s_ncommand *commands, struct s_env *env)
{
	size_t	commands_nb;
	int		err;

	commands_nb = tablen(commands, sizeof * commands);
	if (make_pipes(commands) || \
	heredocs(commands, commands_nb, env->env_list))
	{
		clear_fdlist();
		return (1);
	}
	if (commands_nb < 2)
	{
		err = execute_command(commands, env);
		clear_fdlist();
		return (err);
	}
	return (execute_pipeline(commands, commands_nb, env));
}
