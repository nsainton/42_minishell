/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/20 18:13:02 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_ncommand	*commands;
	t_data		data;

	if (argc > 1 || !argv)
		return (1);
	init_sigs();
	data.cmds = NULL;
	data.errnum = 0;
	data.env = get_my_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (line && ! gc_add(line))
		{
			add_history(line);
			if (split_line(line, &commands, data.env))
				free_gc();
			else
			{
				print_commands(commands);
				/*
				data.cmds = get_commands_reference(commands);
				if (! data.cmds)
				{
					free_from(ft_lstlast(data.env->list_env));
					continue ;
				}
				else
				{
					data.cmds_nb = ft_arrlen((void **)data.cmds);
					if (data.cmds_nb != 0)
						exec_pipeline(&data);
					data.cmds = NULL;
					//print_collector();
					free_from(ft_lstlast(data.env->list_env));
				}
				*/
				free_gc();
			}
		}
		else
		{
			free_gc();
			break ;
		}
	}

	//ft_lstclear(&(data.env)->list_env, NULL);
	//free(data.env);
	return (errno);
}
