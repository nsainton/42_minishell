/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:47:49 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 12:31:16 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands_exec(t_cchar *line, t_data *data)
{
	t_ncommand	*commands;

	if (split_line(line, &commands, data->env))
	{
		//ft_printf("Syntax error while splitting line\n");
		keep_exit_status(SYNTAX_ERROR);
		return ;
	}
	data->cmds = get_commands_reference(commands);
	if (! data->cmds)
	{
		//ft_printf("No commands in data\n");
		return ;
	}
	data->cmds_nb = tablen(data->cmds, sizeof * data->cmds);
	if (!data->cmds_nb)
		return ;
	exec_pipeline(data);
	data->cmds = NULL;
}

/* int	search_for_eof(char *line)
{
	int	i;

	i = 0;
	while( line[i] )
	{
		printf("%d, ", line[i]);
		if (line[i] == 4)
			return (1);
		i ++;
	}
	return (0);
} */