/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:07:46 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/24 16:17:26 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int safe_save(int stds[3])
{
	stds[0] = dup(STDIN_FILENO);
	if (stds[0] == -1)
		return (EXIT_FAILURE);
	stds[1] = dup(STDOUT_FILENO);
	if (stds[1] == -1)
	{
		close(stds[0]);
		stds[0] = -1;
		return (EXIT_FAILURE);
	}
	stds[2] = dup(STDERR_FILENO);
	if (stds[2] == -1)
	{
		close(stds[0]);
		close(stds[1]);
		stds[0] = -1;
		stds[1] = -1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int safe_replace(int stds[3])
{
	size_t	i;

	if (dup2(stds[0], STDIN_FILENO) == -1)
	{
		close(stds[1]);
		close(stds[2]);
		return (EXIT_FAILURE);
	}
	if (dup2(stds[1], STDOUT_FILENO) == -1)
	{
		close(stds[2]);
		return (EXIT_FAILURE);
	}
	if (dup2(stds[2], STDERR_FILENO) == -1)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 3)
	{
		*(stds + i) = -1;
		i ++;
	}
	return (EXIT_SUCCESS);
}

int save_stds(const int mode)
{
	static int	stds[3] = {-1};

	if (mode == 's')
		return (safe_save(stds));
	if (mode == 'r')
		return (safe_replace(stds));
	return (EXIT_FAILURE);
}
