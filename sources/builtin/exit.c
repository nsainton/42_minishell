/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:52:52 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/24 16:23:40 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static t_ll	store_status(const t_ll new_status)
{
	static t_ll	status;
	t_ll		tmp;

	EPRINT;
	tmp = status;
	status = new_status;
	ft_printf("This is the old status : %d\n", tmp);
	ft_printf("This is the new status : %d\n", status);
	if (! tmp)
		return (status);
	return (tmp);
}
*/

static int	check_args(char **args, t_csizet len)
{
	int		err;
	t_ll	status;

	status = (t_ll)strtoll_errors(*args, DEC, &err);
	ft_dprintf(STDERR_FILENO, "exit\n");
	//ft_dprintf(STDERR_FILENO, "This is the len : %u\n", len);
	if (err)
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", *args, \
		STRING_NUMERIC_REQUIRED);
		keep_exit_status(NUMERIC_REQUIRED);
		exit_free_gc(keep_exit_status(-1));
	}
	if (len == 1)
	{
		ft_dprintf(STDERR_FILENO, "No error and only one argument\n");
		keep_exit_status(status % 256);
		exit_free_gc(keep_exit_status(-1));
	}
	if (len > 1)
	{
		ft_dprintf(STDERR_FILENO, "No error but multiple arguments\n");
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s\n", \
		STRING_TOO_MANY);
		ft_printf("This is the status stored : %d\n", TOO_MANY_ARGUMENTS);
		keep_exit_status(TOO_MANY_ARGUMENTS);
		//return (store_status(TOO_MANY_ARGUMENTS));
	}
	return (keep_exit_status(-1));
}

int	exit_builtin(char **args)
{
	size_t	len;

	if (args == NULL)
	{
		ft_printf("Args is NULL\n");
		exit_free_gc(keep_exit_status(-1));
	}
	len = tablen(args, sizeof * args);
	if (! len)
	{
		ft_printf("No arguments\n");
		exit_free_gc(keep_exit_status(-1));
	}
	//ft_dprintf(2, "This is the len : %u\n", len);
	return (check_args(args, len));
}
