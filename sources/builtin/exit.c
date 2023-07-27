/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:52:52 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 10:22:17 by nsainton         ###   ########.fr       */
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

static int	check_args(char **args, t_csizet len, int *errnum)
{
	int		err;
	t_ll	status;

	status = (t_ll)strtoll_errors(*args, DEC, &err);
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (err)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", *args, \
		STRING_NUMERIC_REQUIRED);
		keep_exit_status(NUMERIC_REQUIRED);
		exit_free_gc(keep_exit_status(-1));
	}
	if (len == 1)
	{
		keep_exit_status(status % 256);
		exit_free_gc(keep_exit_status(-1));
	}
	if (len > 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s\n", \
		STRING_TOO_MANY);
		keep_exit_status(TOO_MANY_ARGUMENTS);
		*errnum = TOO_MANY_ARGUMENTS;
	}
	return (keep_exit_status(-1));
}

int	exit_builtin(char **args, int *errnum)
{
	size_t	len;

	if (args == NULL)
		exit_free_gc(keep_exit_status(-1));
	len = tablen(args, sizeof * args);
	if (! len)
		exit_free_gc(keep_exit_status(-1));
	return (check_args(args, len, errnum));
}
