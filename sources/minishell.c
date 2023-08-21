/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/21 11:27:02 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static void	reset_termsig(void)
{
	if (g_termsig)
		keep_exit_status(g_termsig);
	g_termsig = 0;
}

volatile sig_atomic_t	g_termsig = 0;

extern char	**environ;

static const char	*get_prompt(const struct s_tab *env, \
const char *prompt_var)
{
	const char	*prompt;

	prompt = get_var_value(env, prompt_var);
	if (! prompt)
		prompt = "";
	return (prompt);
}

static _Noreturn void	exec_interactive(struct s_env *env)
{
	const char	*prompt;
	char		*line;

	while (1)
	{
		prompt = get_prompt(env->env_list, "PS1");
		line = readline(prompt);
		if (g_termsig)
		{
			reset_termsig();
			continue ;
		}
		if (!line || gc_add(line))
			exit_builtin(NULL, NULL);
		if (*line)
			add_history(line);
		prompt = get_prompt(env->env_list, "PS3");
		if (*prompt)
			ft_putendl_fd(prompt, STDERR_FILENO);
		keep_exit_status(commands_exec(line, env));
		reset_termsig();
	}
	exit_free_gc(1);
}

static _Noreturn void	exec_non_interactive(struct s_env *env)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while(1)
	{
		line = get_next_line(STDIN_FILENO);
		if (! line || gc_add(line))
			exit_builtin(NULL, NULL);
		keep_exit_status(commands_exec(line, env));
	}
}

/*
	bash should be launched in interactive mode if its stdin
	and stderr are connected to a tty (`man 3 isatty`).
	SEE ALSO: 'INVOCATION' in `man bash`
*/
int	main(int argc, char **argv)
{
	struct s_env	*env;

	if (argc != 1)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	(void)argv;
	init_sigs();
	env = create_env((const char **)environ);
	if (! env)
		exit_message(1, MEM_MSG);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		exec_interactive(env);
	exec_non_interactive(env);
	return (errno);
}
