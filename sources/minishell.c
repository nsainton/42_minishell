/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/24 14:59:18 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **av, char **envp, t_data *data)
{
	(void)av;
	data->cmds = NULL;
	data->errnum = 0;
	data->env = get_my_env(envp);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_data		data;

	if (ac != 1 && ac != 3)
	{
		ft_printf("%s\n", USAGE);
		return (EXIT_FAILURE);
	}
	init_sigs();
	init(av, envp, &data);
	while (1)
	{
		line = readline("minishell> ");
		if (!line || gc_add(line))
		{
			free_gc();
			break ;
		}
		if (*line)
			add_history(line);
		commands_exec(line, &data);
		free_from(ft_lstlast(data.env->list_env)->content);
	}
	rl_clear_history();
	return (errno);
}
