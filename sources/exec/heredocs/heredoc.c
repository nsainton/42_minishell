/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:33:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 13:23:26 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Comparison array nullelem is of size 20 to not allocate it and to 
	ensure the portability in case size of `int` increases in the future
	nullelem array work with this function for a sizeof int up to 10 bytes
*/
/*
static void	init_list(int *descriptors_list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(descriptors_list + i) = -1;
		i ++;
	}
}
*/

/*
static int	match_fd(int *command_fd, int *heredoc_fd)
{
	if (dup2(*heredoc_fd, *command_fd) == -1)
	{
		perror("dup2");
		clear_list();
		return (1);
	}
	if (close(*heredoc_fd))
	{
		*heredoc_fd = -1;
		clear_list();
		return (1);
	}
	return (0);
}
*/

/*
int	match_fds(const int command_index)
{
	char			nullelem[20];
	size_t			i;
	const size_t	elem_number = HD_ELEMS_NUMBER;
	int				*descriptors_list;

	descriptors_list = getlist(0, 1);
	ft_bzero(nullelem, elem_number * sizeof * descriptors_list);
	i = 0;
	while (ft_memcmp(descriptors_list + i, nullelem, \
	elem_number * sizeof * descriptors_list) \
	&& *(descriptors_list + i + 2) != -1 \
	&& *(descriptors_list + i + 2) < command_index)
		i += elem_number;
	while (ft_memcmp(descriptors_list + i, nullelem, \
	elem_number * sizeof * descriptors_list) \
	&& *(descriptors_list + i) != -1 \
	&& *(descriptors_list + i + 2) == command_index)
	{
		if (match_fd(descriptors_list + i, descriptors_list + i + 1))
			return (1);
		*/
		/*
		if (dup2(*(descriptors_list + i + 1), *(descriptors_list + i)) == -1)
		{
			perror("dup2");
			clear_list();
			return (1);
		}
		if (close(*(descriptors_list + i + 1)))
		{
			*(descriptors_list + i + 1) = -1;
			clear_list();
			return (1);
		}
		*/
		/*
		*(descriptors_list + i + 1) = *(descriptors_list + i);
		i += elem_number;
	}
	return (0);
}
*/

/*
int	heredoc(const struct s_command *command, const struct s_env *env, \
const int command_index)
{
	size_t			len;
	const size_t	elem_number = HD_ELEMS_NUMBER;
	int				*descriptors_list;

	if (! *command->heredocs)
		return (EXIT_SUCCESS);
	len = tablen(*command->heredocs, sizeof **command->heredocs);
	if (! len)
		return (EXIT_SUCCESS);
	descriptors_list = getlist(len + 1, \
	elem_number * sizeof * descriptors_list);
	if (! descriptors_list)
		return (1);
	if (get_heredocs(command, env, len, command_index))
		return (1);
	init_sigs();
	return (EXIT_SUCCESS);
}
*/

/*
static int get_heredocs_number(const struct s_ncommand *commands, \
const size_t commands_nb)
{
	size_t					number;
	size_t					i;

	number = 0;
	i = 0;
	while (i < commands_nb)
	{
		if (! (commands + i)->heredocs)
		{
			i ++;
			continue ;
		}
		number += tablen((commands + i)->heredocs, sizeof *commands->heredocs);
		i ++;
	}
	return (number);
}
*/

static int	get_heredocs(const struct s_ncommand *command, \
const struct s_env *env)
{
	size_t					i;
	size_t					len;
	int						err;
	struct s_heredoc_infos	hd;

	if (! command->heredocs)
		return (0);
	len = tablen(command->heredocs, sizeof * command->heredocs);
	i = 0;
	while (i < len)
	{
		err = get_heredoc(&hd, command->heredocs + i, env);
		if (err > 0)
			return (1);
		if (! err)
			(command->heredocs + i)->read_fd = hd.read_fd;
		else
			(command->heredocs + i)->read_fd = -1;
		i ++;
	}
	return (0);
}

int	heredocs(const struct s_ncommand *commands, const size_t commands_nb, \
const struct s_env *env)
{
//	size_t			len;
	size_t			i;
	/*
	const size_t	elem_number = HD_ELEMS_NUMBER;
	int				*descriptors_list;
	*/

	/*
	len = get_heredocs_number(commands, commands_nb);
	if (! len)
		return (0);
	descriptors_list = getlist(len + 1, elem_number * sizeof * descriptors_list);
	if (! descriptors_list)
		return (1);
	init_list(descriptors_list, elem_number * len);
	*/
	i = 0;
	while (i < commands_nb)
	{
		if (get_heredocs(commands + i, env))
			return (1);
		i ++;
	}
	return (0);
}
