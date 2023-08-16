/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:07:46 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 10:05:20 by nsainton         ###   ########.fr       */
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
				ft_dprintf(STDERR_FILENO, "I am stds[%u] and \
				fd(%u) is open\n", i, stds[i]);
			else
				ft_dprintf(STDERR_FILENO, "I am \
				stds[%u] and i am closed\n", i);
			i ++;
		}
	}
	if (mode == 'r')
	{
		while (i < 3)
		{
			if (stds[i] != -1)
				ft_dprintf(STDERR_FILENO, "I am stds[%u] \
				and fd(%u) is open\n", i, stds[i]);
			else
				ft_dprintf(STDERR_FILENO, "fd(%u) is \
				closed\n", cp[i]);
			i ++;
		}
	}
}
*/

/*
	new_fd can be arbitrarily high at first. I didn't find
	the maximum integer for a file descriptor yet.
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

int	save_stds(const int	to_open)
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
/*
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
*/

/*
static int	safe_close_dups(int stds[3])
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
		safe_close_dups(stds);
		return (EXIT_FAILURE);
	}
	stds[2] = dup2(STDERR_FILENO, 114);
	if (stds[2] == -1)
	{
		safe_close_dups(stds);
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
		return (put_in_place(stds) || safe_close_dups(stds));
	if (mode == 'c')
		return (safe_close_dups(stds));
	return (EXIT_FAILURE);
}
*/
