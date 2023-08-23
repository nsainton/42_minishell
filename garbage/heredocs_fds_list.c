/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_fds_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:01:48 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 13:23:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Comparison array nullelem is of size 20 to not allocate it and to 
	ensure the portability in case size of `int` increases in the future
	nullelem array work with this function for a sizeof int up to 10 bytes
*/
/*
static int	connect_heredoc_fds(int *descriptors_list, const int command_fd, \
const int heredoc_fd, const int command_index)
{
	if (*(descriptors_list) == -1)
	{
		*(descriptors_list) = command_fd;
		*(descriptors_list + 1) = heredoc_fd;
		*(descriptors_list + 2) = command_index;
		return (0);
	}
	if (close(*(descriptors_list + 1)) == -1)
	{
		*(descriptors_list + 1) = -1;
		return (1);
	}
	*(descriptors_list + 1) = heredoc_fd;
	return (0);
}

static int	update_list(int *descriptors_list, const int command_fd, \
const int heredoc_fd, const int command_index)
{
	size_t			len;
	size_t			i;
	const size_t	elem_number = HD_ELEMS_NUMBER;

	len = tablen(descriptors_list, elem_number * sizeof * descriptors_list);
	i =  0;
	while (i < elem_number * len && *(descriptors_list + i + 2) != -1 && \
	*(descriptors_list + i + 2) < command_index)
		i += elem_number;
	while (i < elem_number * len && *(descriptors_list + i) != -1 \
	&& *(descriptors_list + i) != command_fd)
		i += elem_number;
	if (i == elem_number * len)
		return (1);
	return (connect_heredoc_fds(descriptors_list + i, \
	command_fd, heredoc_fd, command_index));
}
*/

/*
static void	print_desc_list(const int *list)
{
	char			nullelem[20];
	size_t			i;
	const size_t	elem_number = HD_ELEMS_NUMBER;

	ft_bzero(nullelem, elem_number * sizeof * list);
	i = 0;
	while (ft_memcmp(list + i, nullelem, elem_number * sizeof * list) && *(list + i) != -1)
	{
		ft_printf("This is the fd provided as an arguement : %d\n", *(list + i));
		ft_printf("This is the corresponding heredoc fd : %d\n", *(list + i + 1));
		ft_printf("This is the command index : %d\n", *(list + i + 2));
		i += elem_number;
	}
}
*/

/*
int	get_heredocs(const struct s_command *command, const struct s_env *env, \
const size_t number, const int command_index)
{
	struct s_heredoc_infos	hd;
	size_t					i;
	int						err;
	int						*descriptors_list;

	descriptors_list = getlist(0, 1);
	i = 0;
	while (i < number)
	{
		err = getheredoc(&hd, *command->heredocs + i, env);
		if (err > 0)
			return (1);
		if (! err)
		{
			ft_printf("------------Before updating---------------\n");
			print_desc_list(descriptors_list);
		}
		if (! err && update_list(descriptors_list, \
		(*(command->heredocs + i))->fd, hd.read_fd, command_index))
		{
			clear_list();
			return (1);
		}
		if (! err)
		{
			ft_printf("--------------Updated----------------------\n");
			print_desc_list(descriptors_list);
		}
		i ++;
	}
	return (0);
}
*/
