/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:07:46 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 11:04:07 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	new_fd could begin at a arbitrarily high position. I didn't find the
	maximum number that a file descriptor can reach so I went for 100
*/
static int	move_fd(int *fd)
{
	int				new_fd;
	struct s_list	*fdlist;

	fdlist = *get_fdlist();
	new_fd = 100;
	while (new_fd > 2)
	{
		if (! ft_list_find(fdlist, &new_fd, isdifferent_pointer))
			break ;
		new_fd --;
	}
	if (new_fd == 2)
		return (1);
	if ((s_dup2(*fd, new_fd) < 0) || s_close(*fd))
		return (1);
	*fd = new_fd;
	return (0);
}

/*
	This function takes a file descriptor as an argument (which
	is supposed to be save somewhere to be put in place later)
	and a file descriptor that we want to open. If the
	file descriptor we want to_open is the one we used for saving
	we need to move the previously saved file descriptor.
*/
static int	save(int *fd, const int to_open)
{
	if (*fd != to_open)
		return (0);
	return (move_fd(fd));
}

static int	replace_fd(int *fd, const int new_fd)
{
	if (*fd == new_fd)
		return (0);
	if ((s_dup2(*fd, new_fd) < 0) || s_close(*fd))
		return (1);
	*fd = new_fd;
	return (0);
}

static int	replace_stds(int *stds)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (replace_fd(stds + i, i))
			return (1);
		i ++;
	}
	return (0);
}

int	save_stds(const int to_open)
{
	static int	stds[3] = {0, 1, 2};
	int			i;

	if (to_open == -1)
		return (move_fd(stds) || move_fd(stds + 1) || \
		move_fd(stds + 2));
	if (to_open == -2)
		return (replace_stds(stds));
	i = 0;
	while (i < 3)
	{
		if (save(stds + i, to_open))
			return (1);
		i ++;
	}
	return (0);
}
