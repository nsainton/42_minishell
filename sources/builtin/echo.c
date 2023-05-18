/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:42:11 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/18 16:12:02 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(t_data *d, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] && is_true_optn(cmd->args[i]))
		i++;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i ++;
	}
	d->errnum = 0;
	if (!is_true_optn(cmd->args[0]))
		printf("\n");
	return (0);
}

int	is_true_optn(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
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