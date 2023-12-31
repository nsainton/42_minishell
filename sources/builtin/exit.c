/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:52:52 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/23 13:50:41 by nsainton         ###   ########.fr       */
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

static int	check_args(const char **args, const size_t len)
{
	int				err;
	long long int	status;

	status = (long long int)strtoll_errors(*args, DEC, &err);
	if (err)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", *args, \
		STRING_NUMERIC_REQUIRED);
		exit_free_gc(NUMERIC_REQUIRED);
	}
	if (len == 1)
		exit_free_gc(status % 256);
	if (len > 1)
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s\n", \
		STRING_TOO_MANY);
	return (TOO_MANY_ARGUMENTS);
}

int	exit_builtin(const char **args, struct s_env *env)
{
	size_t	len;
	int		interactive;

	(void)env;
	interactive = (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
	if (interactive)
		ft_dprintf(STDERR_FILENO, "exit\n");
	if (args == NULL)
		exit_free_gc(keep_exit_status(-1));
	len = tablen(args, sizeof * args);
	if (! len)
		exit_free_gc(keep_exit_status(-1));
	return (check_args(args, len));
}
