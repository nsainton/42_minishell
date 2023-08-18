/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/18 14:13:21 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

/*
static void	init(char **envp, t_data *data)
{
	init_sigs();
	data->cmds = NULL;
	data->errnum = 0;
	data->env = get_my_env(envp);
}
*/

/*
void	handle(int sig)
{
	g_termsig = sig;
	//printf("Salut\n");
	//rl_done = 1;
	//rl_pending_input = '\n';
	//write(0, "\n", 1);
	ioctl(0, TIOCSTI, "\n");
}
*/

static void	reset_termsig(void)
{
	printf("we received : %d\n", g_termsig);
	keep_exit_status(g_termsig);
	g_termsig = 0;
	rl_replace_line("", 0);
	rl_on_new_line();
}
	
volatile sig_atomic_t	g_termsig = 0;

extern char	**environ;

int	main(int argc, char **argv)
{
	char			*line;
//	char			*name;
	struct s_env	*env;

	if (argc != 1)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	(void)argv;
	rl_catch_signals = 0;
	init_sigs();
	/*
	name = ttyname(0);
	if (! name)
		printf("No tty\n");
	else
		printf("tty name : %s\n", name);
	*/
	env = create_env((const char **)environ);
	if (! env)
		exit_message(1, MEM_MSG);
	while (1)
	{
		line = readline("minishell> ");
		if (g_termsig)
		{
			reset_termsig();
			continue ;
		}
		if (!line || gc_add(line))
		{
			exit_builtin(NULL, NULL);
			break ;
		}
		if (*line)
			add_history(line);
		keep_exit_status(commands_exec(line, env));
		if (g_termsig)
			reset_termsig();
		/*
			Import exit_message from env_test
			exit_message(MEMORY_MESSAGE);
		*/
		//ft_printf("This is the last env var : %s\n", (char *)ft_lstlast(data.env->list_env)->content);
		//free_from(ft_lstlast(data.env->list_env)->content);
	}
	exit_free_gc(1);
	return (errno);
}
