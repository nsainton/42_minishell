/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/16 08:27:08 by nsainton         ###   ########.fr       */
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

volatile sig_atomic_t	g_termsig = 0;

extern char	**environ;

int	main(int argc, char **argv)
{
	char			*line;
//	char			*name;
//	struct s_env	*env;

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
	/*
	env = create_env((const char **)environ);
	if (! env)
		printf("PB\n");
	*/
	/* Handle allocation error */
	while (1)
	{
		line = readline("minishell> ");
		if (g_termsig)
		{
			printf("we received : %d\n", g_termsig);
			g_termsig = 0;
		}
		if (!line || gc_add(line))
		{
			ft_putendl_fd("exit", 1);
			exit(1);
			//exit_builtin(NULL, NULL);
			break ;
		}
		if (*line)
			add_history(line);
		printf("%s\n", line);
		//if (commands_exec(line, &data));
		/*
			Import exit_message from env_test
			exit_message(MEMORY_MESSAGE);
		*/
		//ft_printf("This is the last env var : %s\n", (char *)ft_lstlast(data.env->list_env)->content);
		//free_from(ft_lstlast(data.env->list_env)->content);
	}
	rl_clear_history();
	return (errno);
}
