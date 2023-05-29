/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/29 17:32:57 by nsainton         ###   ########.fr       */
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
			if (split_line(line, &commands))
				free_gc();
			else
			{
				data.cmds = get_commands_reference(commands);
				if (! data.cmds)
				{
					free_gc();
					ft_printf("No commands in data\n");
					continue ;
				}
				else
				{
					data.cmds_nb = ft_arrlen((void **)data.cmds);
    				if (data.cmds_nb != 0)
					{
        				exec_pipeline(&data);
					}
					free_gc();
				}
			}
		}
		else
		{
			ft_printf("No line\n");
			free_gc();
			exit(0);
		}
	}
	return (errno);
}
