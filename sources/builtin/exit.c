/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:52:52 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/23 21:21:48 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ll	store_status(const t_ll new_status)
{
	static t_ll	status;
	t_ll		tmp;

	tmp = status;
	status = new_status;
	if (! tmp)
		return (status);
	return (tmp);
}

static int	check_args(char **args, t_csizet len)
{
	int		err;
	t_ll	status;

	status = (t_ll)strtoll_errors(*args, DEC, &err);
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (err)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", *args, \
		STRING_NUMERIC_REQUIRED);
		exit_free_gc(store_status(NUMERIC_REQUIRED));
	}
	if (len == 1)
		exit_free_gc(store_status(status % 256));
	if (len > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s\n", \
		STRING_TOO_MANY);
		keep_exit_status(store_status(TOO_MANY_ARGUMENTS));
	}
	return (store_status(EXIT_SUCCESS));
}

int	exit_builtin(char **args)
{
	size_t	len;

	if (args == NULL)
		exit_free_gc(store_status(EXIT_SUCCESS));
	len = tablen(args, sizeof * args);
	if (! len)
		exit_free_gc(store_status(EXIT_SUCCESS));
	return (check_args(args, len));
}
