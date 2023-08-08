/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/08 17:44:30 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char **envp, t_data *data)
{
	init_sigs();
	data->cmds = NULL;
	data->errnum = 0;
	data->env = get_my_env(envp);
}

volatile sig_atomic_t	g_termsig = 0;

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_data		data;

	//ft_printf("Program invocation name : %s\n", program_invocation_name);
	if (ac != 1)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	(void)av;
	init(envp, &data);
	while (1)
	{
		line = readline("minishell> ");
		if (!line || gc_add(line))
		{
			ft_putendl_fd("exit", 1);
			exit_builtin(NULL, NULL);
			break ;
		}
		if (*line)
			add_history(line);
		commands_exec(line, &data);

		//ft_printf("This is the last env var : %s\n", (char *)ft_lstlast(data.env->list_env)->content);
		//free_from(ft_lstlast(data.env->list_env)->content);
	}
	rl_clear_history();
	return (errno);
}
