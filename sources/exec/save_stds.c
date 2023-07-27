/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:07:46 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/27 15:35:08 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	print_infos(const int stds[3], const int cp[3], const int mode)
{
	size_t	i;

	i = 0;
	ft_dprintf(STDERR_FILENO, "This is my mode : %c\n", mode);
	if (mode == 's')
	{
		while (i < 3)
		{
			if (stds[i] != -1)
				ft_dprintf(STDERR_FILENO, "I am stds[%u] and fd(%u) is open\n", i, stds[i]);
			else
				ft_dprintf(STDERR_FILENO, "I am stds[%u] and i am closed\n", i);
			i ++;
		}
	}
	if (mode == 'r')
	{
		while (i < 3)
		{
			if (stds[i] != -1)
				ft_dprintf(STDERR_FILENO, "I am stds[%u] and fd(%u) is open\n", i, stds[i]);
			else
				ft_dprintf(STDERR_FILENO, "fd(%u) is closed\n", cp[i]);
			i ++;
		}
	}
}
*/

static int	already_saved(int stds[3])
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if (*(stds + i) != -1)
			return (1);
		i ++;
	}
	return (0);
}

static int	safe_close(int stds[3])
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if (*(stds + i) >= 0 && close(*(stds + i)) == -1)
			return (EXIT_FAILURE);
		*(stds + i) = -1;
		i ++;
	}
	return (EXIT_SUCCESS);
}

static int	safe_save(int stds[3])
{
	if (already_saved(stds))
	{
		ft_dprintf(STDERR_FILENO, "File descriptors where already saved\n");
		return (EXIT_FAILURE);
	}
	stds[0] = dup2(STDIN_FILENO, 112);
	if (stds[0] == -1)
		return (EXIT_FAILURE);
	stds[1] = dup2(STDOUT_FILENO, 113);
	if (stds[1] == -1)
	{
		safe_close(stds);
		return (EXIT_FAILURE);
	}
	stds[2] = dup2(STDERR_FILENO, 114);
	if (stds[2] == -1)
	{
		safe_close(stds);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	put_in_place(int stds[3])
{
	int	err;

	err = (dup2(stds[0], STDIN_FILENO) == -1);
	err = (err || (dup2(stds[1], STDOUT_FILENO) == -1));
	err = (err || (dup2(stds[2], STDERR_FILENO) == -1));
	return (err);
}

int	save_stds(const int mode)
{
	static int	stds[3] = {-1, -1, -1};

	if (mode == 's')
		return (safe_save(stds));
	if (mode == 'r')
		return (put_in_place(stds) || safe_close(stds));
	if (mode == 'c')
		return (safe_close(stds));
	return (EXIT_FAILURE);
}
