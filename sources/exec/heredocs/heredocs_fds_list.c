/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_fds_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:01:48 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/08 14:46:27 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Comparison array nullelem is of size 20 to not allocate it and to 
	ensure the portability in case size of `int` increases in the future
	nullelem array work with this function for a sizeof int up to 10 bytes
*/
static int	connect_heredoc_fds(int *descriptors_list, const int command_fd, \
const int heredoc_fd)
{
	if (*(descriptors_list) == -1)
	{
		*(descriptors_list) = command_fd;
		*(descriptors_list + 1) = heredoc_fd;
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
const int heredoc_fd)
{
	size_t	len;
	size_t	i;

	len = tablen(descriptors_list, 2 * sizeof * descriptors_list);
	i =  0;
	while (i < 2 * len && *(descriptors_list + i) != -1 \
	&& *(descriptors_list + i) != command_fd)
		i += 2;
	if (i == 2 * len)
		return (1);
	return (connect_heredoc_fds(descriptors_list + i, command_fd, heredoc_fd));
}

/*
static void	print_desc_list(const int *list)
{
	char	nullelem[20];
	size_t	i;

	ft_bzero(nullelem, 2 * sizeof * list);
	i = 0;
	while (ft_memcmp(list + i, nullelem, 2 * sizeof * list) && *(list + i) != -1)
	{
		ft_printf("This is the fd provided as an arguement : %d\n", *(list + i));
		ft_printf("This is the corresponding heredoc fd : %d\n", *(list + i + 1));
		i += 2;
	}
}
*/

int	get_heredocs(int *descriptors_list, \
const struct s_command *command, const struct s_env *env, \
const size_t number)
{
	struct s_heredoc_infos	hd;
	size_t					i;
	int						err;

	i = 0;
	while (i < number)
	{
		err = getheredoc(&hd, *command->heredocs + i, env);
		if (err > 0)
			return (1);
		/*
		if (! err)
		{
			ft_printf("------------Before updating---------------\n");
			print_desc_list(descriptors_list);
		}
		*/
		if (! err && \
		update_list(descriptors_list, (*(command->heredocs + i))->fd, hd.read_fd))
		{
			clear_list(descriptors_list);
			return (1);
		}
		/*
		if (! err)
		{
			ft_printf("--------------Updated----------------------\n");
			print_desc_list(descriptors_list);
		}
		*/
		i ++;
	}
	return (0);
}
