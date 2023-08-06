/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:13:15 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 12:16:39 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free_gc(int status)
{
	free_gc();
	rl_clear_history();
	exit(status);
}

int	keep_exit_status(const int exit_status)
{
	static int	status;

	if (exit_status < 0)
		return (status);
	status = exit_status;
	return (0);
}
