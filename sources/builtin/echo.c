/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:42:11 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/21 17:59:48 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + i])
			printf(" ");
		i ++;
	}
	if (!cmd->options[0])
	{
		printf("\n");
		return (0);
	}
	else if (cmd->options[0][1] != 'n')
	{
		printf("\nminishell doesn't support %s option.\n", cmd->options[0]);
		return (1);
	}
	else
		return (0);
}
