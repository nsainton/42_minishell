/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:42:11 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/16 08:45:26 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_opt(const char *variable)
{
	if (*variable != '-')
		return (0);
	variable ++;
	while (*variable)
	{
		if (*variable != 'n')
			return (0);
		variable ++;
	}
	return (1);
}

int	echo(const char **args, struct s_env *env)
{
	int	endl;

	(void)env;
	if (! (args && *args))
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	endl = 1;
	while (*args && is_opt(*args))
	{
		endl = 0;
		args ++;
	}
	while (*args)
	{
		ft_printf("%s ", *args);
		args ++;
	}
	ft_putchar_fd('\b', STDOUT_FILENO);
	if (endl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/*
int	print_echo(t_data *d, t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[0])
	{
		ft_dprintf(1, "\n");
		return (0);
	}
	while (cmd->args[i] && is_true_optn(cmd->args[i]))
		i++;
	while (cmd->args[i])
	{
		ft_dprintf(1, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i ++;
	}
	d->errnum = 0;
	if (!is_true_optn(cmd->args[0]))
		ft_dprintf(1, "\n");
	return (0);
}

int	is_true_optn(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	if (str[0] != '-')
		return (0);
	if (!str[1])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
*/

/*
int	print_exit_status(t_data *d, t_command *cmd)
{
	if (cmd->args[0])
	{
		ft_dprintf(2, "exit status : minishell doesn't support arguments\n");
		return (1);
	}
	else
	{
		ft_dprintf(2, "%d : %s\n", d->errnum, strerror(d->errnum));
		return (0);
	}
}
*/
