/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/22 21:23:08 by nsainton         ###   ########.fr       */
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
		//ft_printf("This is the last pointer in the env : %s\n", ft_lstlast(data.env->list_env)->content);
		free_from(ft_lstlast(data.env->list_env)->content);
	}
	rl_clear_history();
	return (errno);
}
