/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:47:55 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 12:33:53 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "signal_messages.h"

/*
int	execute_file(struct s_ncommand *command, struct s_env *env)
{}
*/

static int	pre_execution(struct s_redir *redirs, \
struct s_heredoc *heredocs)
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

static char	*find_command_path(char *command, struct s_tab *env)
{
	int		err;
	char	*path;

	err = getpath(command, &path, env);
	if (err || ! path)
	{
		if (err == 127)
			ft_printf("minishell: %s: no such file or directory\n", \
			command);
		if (! err)
		{
			ft_printf("minishell: %s: command not found\n", command);
			err = 127;
		}
		exit_free_gc(err);
	}
	return (path);
}

static int	handle_exit_status(const int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFCONTINUED(wstatus))
		return (18);
	if (WIFSIGNALED(wstatus))
	{
		ft_putstr_fd(choose_sig(WTERMSIG(wstatus)), STDOUT_FILENO);
		if (WCOREDUMP(wstatus))
			ft_putstr_fd(CORE_MESSAGE, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (128 + WTERMSIG(wstatus));
	}
	//ft_printf("%s", choose_sig(WIFSIGNALED(wstatus)));
	ft_putendl_fd(choose_sig(WIFSIGNALED(wstatus)), STDOUT_FILENO);
	return (128 + WSTOPSIG(wstatus));
}

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

/*
	In this function we give command->args - 1 to execve
	because command->args is the second element (index 1)
	of an array that is the result of a split over the spaces
	during the parsing phase. The command name is thus the
	first element of this array and the element we should give
	to execve.
	See sources/parsing/fill_command.c in case of bug that could
	occur because of that assignment. However as the memory
	for commands is freed at the very end, such a bug shouldn't
	occur.
*/
static int	execute_file(struct s_ncommand *command, struct s_tab *env)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid < 0)
		return (1);
	if (! child_pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		//signal(SIGPIPE, SIG_DFL);
		if (apply_pipe(command->input_fd, command->output_fd) || \
		make_redirections(command->redirs, command->heredocs))
			exit_free_gc(1);
		command->path = find_command_path(command->command, env);
//		clear_list();
		if (execve(command->path, command->args - 1, env->tab))
			exit_free_gc(1);
	}
	wait(&status);
	return (status);
}

static int	execute_builtin(t_builtin builtin, \
struct s_ncommand *command, struct s_env *env)
{
	int	err;

	err = pre_execution(command->redirs, command->heredocs);
	if (err)
		return (1);
	err = builtin((const char **)command->args, env);
	save_stds(-2);
	return (err);
}

int	execute_command(struct s_ncommand *command, struct s_env *env)
{
	t_builtin	builtin;
	int			status;
	int			err;

	if (! command->command)
	{
		err = pre_execution(command->redirs, command->heredocs);
		save_stds(-2);
		return (err);
	}
	builtin = choose_builtin(command->command);
	if (builtin)
		return (execute_builtin(builtin, command, env));
	status = execute_file(command, env->env_list);
	return (handle_exit_status(status));
}
