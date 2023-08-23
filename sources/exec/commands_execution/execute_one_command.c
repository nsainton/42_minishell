/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:47:55 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 09:48:45 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "signal_messages.h"

static char	*find_command_path(char *command, struct s_tab *env)
{
	int		err;
	char	*path;

	err = getpath(command, &path, env);
	if (err || ! path)
	{
		if (err)
			ft_printf("minishell: %s: no such file or directory\n", \
			command);
		if (! err)
			ft_printf("minishell: %s: command not found\n", command);
		exit_free_gc(127);
	}
	return (path);
}

int	handle_exit_status(const int wstatus)
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
	ft_putendl_fd(choose_sig(WIFSIGNALED(wstatus)), STDOUT_FILENO);
	return (128 + WSTOPSIG(wstatus));
}

static void	execution_failed(const char *command_path)
{
	struct stat	statbuf;
	int			is_dir;

	is_dir = 1;
	if (stat(command_path, &statbuf) || ! S_ISDIR(statbuf.st_mode))
		is_dir = 0;
	if (is_dir)
		ft_dprintf(STDERR_FILENO, "minishell: %s: Is a directory\n", \
		command_path);
	else
		ft_dprintf(STDERR_FILENO, "minishell: %s: permission denied\n", \
		command_path);
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
	status = 0x100;
	if (child_pid < 0)
		return (1);
	if (! child_pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		command->path = find_command_path(command->command, env);
		execve(command->path, command->args - 1, env->tab);
		execution_failed(command->path);
		exit_free_gc(126);
	}
	wait(&status);
	return (status);
}

int	execute_command(struct s_ncommand *command, struct s_env *env)
{
	t_builtin	builtin;
	int			status;
	int			err;

	err = make_redirections(command->redirs, command->heredocs);
	if (err || ! command->command)
	{
		save_stds(-2);
		return (err);
	}
	builtin = choose_builtin(command->command);
	if (builtin)
	{
		err = builtin((const char **)command->args, env);
		save_stds(-2);
		return (err);
	}
	status = execute_file(command, env->env_list);
	save_stds(-2);
	return (handle_exit_status(status));
}
