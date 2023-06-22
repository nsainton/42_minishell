/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/22 18:04:59 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_data		data;

	if (ac != 1 && ac != 3)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	(void)av;
	init_sigs();
	data.cmds = NULL;
	data.errnum = 0;
	data.env = get_my_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line || gc_add(line))
		{
			ft_printf("We are freeing the garbage collector\n");
			free_gc();
			break ;
		}
		if (*line)
			add_history(line);
		commands_exec(line, &data);
		free_from(ft_lstlast(data.env->list_env));
	}
	rl_clear_history();
	//ft_lstclear(&(data.env)->list_env, NULL);
	//free(data.env);
	return (errno);
}
