/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:42:11 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/10 17:51:22 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(t_data *d, t_command *cmd)
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
	d->errnum = 0;
	if (!cmd->options[0])
		printf("\n");
	else if (cmd->options[0][1] != 'n')
	{
		printf("\nminishell doesn't support %s option.\n", cmd->options[0]);
		d->errnum = 2;
		return (2);
	}
	return (0);
}

int	print_exit_status(t_data *d, t_command *cmd)
{
	if (cmd->args[0])
	{
		ft_dprintf(2, "exit status : minishell doesn't support arguments\n");
		return (1);
	}
	else
	{
		ft_printf("%d : %s\n", d->errnum, strerror(d->errnum));
		return (0);
	}
}