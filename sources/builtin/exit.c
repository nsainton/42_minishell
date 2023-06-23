/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:52:52 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/23 01:24:56 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(char **args, t_csizet len)
{
	int		err;
	t_ll	status;

	status = (t_ll)strtoll_errors(*args, DEC, &err);
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (err)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", *args, \
		strerror(errno));
		exit_free_gc(errno);
	}
	if (len == 1)
		exit_free_gc(status % 256);
	if (len > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s\n", strerror(errno));
		keep_exit_status(errno);
	}
	return (errno);
}

int	exit_builtin(char **args)
{
	size_t	len;

	if (args == NULL)
		exit_free_gc(0);
	len = tablen(args, sizeof * args);
	if (! len)
		exit_free_gc(0);
	return (check_args(args, len));
}
